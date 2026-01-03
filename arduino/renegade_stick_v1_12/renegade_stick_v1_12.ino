// Renegade Stick
// A DIY arcade-style, retro, wireless Bluetooth joystick.
// https://github.com/mach0gr/renegade-stick/tree/main

// Code was originally written for Firebeetle 2 esp32-S3(N4) and was tested on the following boards
// Firebeetle 2 ESP32-S3(N4) DFR1145 --> https://wiki.dfrobot.com/_SKU_DFR1145_FireBeetle_2_ESP32_S3_N4_IoT_development_board#target_0
// Firebeetle 2 ESP32-E (N16R2) DFR1139 --> https://wiki.dfrobot.com/_SKU_DFR1139_FireBeetle_2_ESP32_E_N16R2_IoT_Microcontroller
// Firebeetle 2 ESP32-C6 DFR1075 --> https://wiki.dfrobot.com/SKU_DFR1075_FireBeetle_2_Board_ESP32_C6

// Changelog
// v1_0 Github initial Release version
// v1_02 Cleaned DPAD processing code. Now Sending a one off update for centering axes as it connets. Raised debounce by 10msec for some false bouncing
// v1_03 removed overall pacing delay, brought down debouncing to 5 ms. Set ble power to 9.
// v1_10 some code cleanup. 4 Buttons each side edition. New Combo button press to flip hand held mode from Right hand side to Left hand side(button mapping)
// v1_11 Code refactor and debounce optimization
// v1_12 further code refactor on DPADs

#include <Arduino.h>
#include <BleGamepad.h> // using library from https://github.com/lemmingDev/ESP32-BLE-Gamepad/tree/master
#include <driver/rtc_io.h> // needed for rtc api deep sleep

//constexpr bool DEBUG_SERIAL = true;   // set to false to disable serial debug output to console
#define DEBUG_SERIAL 0   // set to 0 to disable serial debug output to console

#if CONFIG_IDF_TARGET_ESP32C6
  #include "pinout_esp32_c6.h"    // pinout Definitions for Firebeetle 2 ESP32-C6 DFR1075

#elif CONFIG_IDF_TARGET_ESP32S3
  #include "pinout_esp32_s3.h"    // pinout Definitions for Firebeetle 2 ESP32-S3(N4) DFR1145

#elif CONFIG_IDF_TARGET_ESP32
  #include "pinout_esp32_e.h"     // pinout Definitions for Firebeetle 2 ESP32-E (N16R2) DFR1139

#else
  #error "Unsupported ESP32 target"
#endif

#if DEBUG_SERIAL    // Define debug serial console macros so they can be disabled with above definition at compile time.
  #define DEBUG_BEGIN(...)    Serial.begin(__VA_ARGS__)
  #define DEBUG_PRINTF(...)   Serial.printf(__VA_ARGS__)
  #define DEBUG_PRINT(...)    Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else   
  #define DEBUG_BEGIN(...)    do {} while (0)   // this actually just quits/does nothing
  #define DEBUG_PRINTF(...)   do {} while (0)
  #define DEBUG_PRINT(...)    do {} while (0)
  #define DEBUG_PRINTLN(...)  do {} while (0)
#endif

// ---------------------------------------------------------------
// Led Configuration
unsigned long BLINK_INTERVAL = 1000;   // LED blink time interval 1000 milliseconds (slow blink when unpaired)
unsigned long lastBlinkTime = 0;       // Variable to be used as a global counter for LED blink interval
bool ledState = LOW;                   // Keep last LED led State

// ---------------------------------------------------------------
// Battery Measurement Configuration
#if VOLT_MEASURE_AVAILABLE
  unsigned long lastBattMeasureTime = 0;    // Variable to be used as a global time counter for polling
  #define BATT_MIN_MV 3300    // minimum value for the li-po battery ~ 3.3V
  #define BATT_MAX_MV 4152    // maximum value for the charged li-po battery ~ 4.2V
#endif

// ---------------------------------------------------------------
// Deep Sleep config
bool bleWasConnected = false;   // variable to be used as state in order to send a BLE report just once on initial connect.
constexpr unsigned long Sleep_Inactivity_INTERVAL = 300000;   // Sleep time interval (If inactive for x milliseconds, it will enter sleep mode) 300000 milliseconds = 5 minutes
unsigned long lastSleepTime = 0;                          // Variable to be used as a global counter for sleep timer

// ---------------------------------------------------------------
// Button configuration
constexpr uint8_t NUM_BUTTONS = 10;
constexpr unsigned long DEBOUNCE_DELAY = 5;   // debounce in milliseconds

//The order of these three arrays matters a lot, be carefully when changing them
const int buttonPins[NUM_BUTTONS] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, BUTTON_7, BUTTON_8, START_BUTTON, SELECT_BUTTON};
static const uint8_t gamepadMapRightHand[NUM_BUTTONS] = {1, 2, 3, 4, 5, 6, 7, 8, 12, 11};    // Right Hand Joystick. 4 keys from the left side (1234) and 4 keys from the right side (5678)
static const uint8_t gamepadMapLeftHand[NUM_BUTTONS] = {5, 6, 7, 8, 1, 2, 3, 4, 12, 11};   // Left Hand Joystick. 4 keys from the left side (5678) and 4 keys from the right side (1234)
const uint8_t* activeGamepadMap = gamepadMapRightHand;    // Default condition Right hand Joystick.

// Track button state and timing.
bool buttonRawRead[NUM_BUTTONS];   // used to momentary store the button pins state
bool buttonDebouncedState[NUM_BUTTONS];   // used to store the button debounced state
bool buttonLastDebouncedState[NUM_BUTTONS];   // used to store the last button debounced state in order to compare changes
unsigned long buttonLastDebounceTime[NUM_BUTTONS];  // counter for debounce delay


// ---------------------------------------------------------------
// DPAD and Stick axis configuration
enum {                // enumerate the DPAD
  DPAD_UP_IDX = 0,
  DPAD_DOWN_IDX,
  DPAD_LEFT_IDX,
  DPAD_RIGHT_IDX,
  NUM_DPAD
};

const int dpadPins[NUM_DPAD] = {DPAD_UP, DPAD_DOWN, DPAD_L, DPAD_R}; // fix the DPADs into an array 

bool dpadRawRead[NUM_DPAD];   // used to momentary store the DPAD pins state
bool dpadDebouncedState[NUM_DPAD];    // used to store the DPAD debounced state
unsigned long dpadLastDebounceTime[NUM_DPAD];    // counter for debounce delay

// --------------------------------------------------
// Stick mode handling

constexpr int16_t AXIS_MIN = 0;   // Axis min value (using setAxesMin:setAxesMax 0:32767)
constexpr int16_t AXIS_CENTER = 16383;  // Centered value (using setAxesMin:setAxesMax 0:32767)
constexpr int16_t AXIS_MAX = 32767;   // Axis max value (using setAxesMin:setAxesMax 0:32767)

enum StickMode {    // enumerate mode ( AXIS vs HAT)
  STICK_MODE_HAT,
  STICK_MODE_AXIS
};
StickMode stickMode = STICK_MODE_AXIS;   // default mode is Axis

// Dpad stick state handling
struct StickState {   // structured variable to keep DPAD and x,y positioning data
  uint8_t hat;       // hat takes values 0–8
  int16_t x;        // x and y take values 0-32767 as found above
  int16_t y;
};

StickState currentStick = {0, AXIS_CENTER, AXIS_CENTER};    // variable to store positioning data
StickState lastStick    = {0, AXIS_CENTER, AXIS_CENTER};    // variable to store the last stick positioning data for comparison
       
// --------------------------------------------------

//Generate a unique Serial Number for each controller. This ensures two or more can be paired as they will have different Serial Numbers
char serialNumber[16];   // Enough space for serial string
uint64_t mac = ESP.getEfuseMac();   // 48-bit unique MAC, extract a unique byte from board IC
uint16_t shortID = (mac >> 8) & 0xFFFF;  // extract part of MAC

BleGamepad bleGamepad("Renegade Stick", "mach0gr", 100);  // Declare bleGamepad Bluetooth Name to init the device.
BleGamepadConfiguration bleGamepadConfig; // Create a BleGamepadConfiguration object to store all of the options

void setup() {    // setup code here, runs once:
  delay(1000);
  DEBUG_BEGIN(115200);   // will be using this for debug/monitoring to Seria Console. You can switch it on/off from #define DEBUG_SERIAL 0 set at top.
  DEBUG_PRINTLN("Starting BLE Gamepad...");

  sprintf(serialNumber, "%010u", shortID); // create zero-padded 10-digit serial
  DEBUG_PRINTF("Board Serial No: %s \n", serialNumber);

  for(int i=0; i<NUM_BUTTONS; i++){  // Init buttonStates and Pins. We init to High. Button trigger is active LOW)
    buttonRawRead[i] = HIGH;
    buttonDebouncedState[i] = HIGH;
    buttonLastDebouncedState[i] = HIGH;
    buttonLastDebounceTime[i] = 0;
    pinMode(buttonPins[i], INPUT_PULLUP); // setup pullup resistor for all our inputs (input pins have been selected to be compatible with pull_up/not used with other functions of esp32)
  }

  for (int i = 0; i < NUM_DPAD; i++) {  // Init DPAD and Pins. We init to High. Button trigger is active LOW)
  dpadRawRead[i] = HIGH;
  dpadDebouncedState[i] = HIGH;
  dpadLastDebounceTime[i] = 0;
  pinMode(dpadPins[i], INPUT_PULLUP); // setup pullup resistor for all our inputs (input pins have been selected to be compatible with pull_up/not used with other functions of esp32)
  }

  pinMode(LED, OUTPUT);  // this is the board's LED, will act like an activity led
  
  // On startup we check if both buttons are pressed at the same time. Board can wake from a single button press, here we make sure both buttons are pressed so we can wake up the board
  delay(200); // debounce for pullups
  if (digitalRead(START_BUTTON) == LOW && digitalRead(SELECT_BUTTON) == LOW) {
    DEBUG_PRINTLN("Valid wake: both buttons pressed. Ready for play !");
  } 
  else {
    DEBUG_PRINTLN("Invalid wake: going back to sleep");
    delay(1000);
    go_deep_sleep();  // call deep sleep procedure
  }

  // Setup the analog resolution used for battery measurement to 12 bits (0-4096)
  #if VOLT_MEASURE_AVAILABLE
    analogReadResolution(12);
  #endif

  //BLE config through ESP32-BLE-Gamepad Library
  // configuring the BleGamepad library
  bleGamepadConfig.setAutoReport(false);  // we will be sending report when we want it
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setButtonCount(12);
  bleGamepadConfig.setVid(0xe502);    // I picked up an unused Vid
  bleGamepadConfig.setPid(PRODUCT_PID);   // We have 3 different Pids for the different esp32 boards that are compatible and have been tested.
  bleGamepadConfig.setHatSwitchCount(1);
  bleGamepadConfig.setTXPowerLevel(9);  // Defaults to 9 if not set. The only valid values are: -12, -9, -6, -3, 0, 3, 6 and 9 (Values correlate to dbm)
  bleGamepadConfig.setModelNumber("1.0");
  bleGamepadConfig.setSoftwareRevision("Software Rev v1.12");
  bleGamepadConfig.setSerialNumber(serialNumber);
  bleGamepadConfig.setFirmwareRevision("2.0");
  bleGamepadConfig.setHardwareRevision("1.7");
  // Some non-Windows operating systems and web based gamepad testers don't like min axis set below 0, so we set 0 by default
  //bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setAxesMin(0x0000); // 0 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setWhichAxes(1, 1, 0, 0, 0, 0, 0, 0); // enable X and Y axes only
  // Now start BLE with the above config
  bleGamepad.begin(&bleGamepadConfig);
  delay(3000);  // let a few seconds to setup the BLE
}


// Function to convert analog read battery mv value to percentage.
#if VOLT_MEASURE_AVAILABLE
  uint8_t batteryMvToPercent(int mv) {
    if (mv <= BATT_MIN_MV) return 0;     
    if (mv >= BATT_MAX_MV) return 100;   
    return (uint8_t)((mv - BATT_MIN_MV) * 100L / (BATT_MAX_MV - BATT_MIN_MV));    // create a percentage out of it
  }
#endif

// Function to compute hat and axis values based on DPAD state
StickState readDpadState() {
  bool up    = (dpadDebouncedState[DPAD_UP_IDX]    == LOW);
  bool down  = (dpadDebouncedState[DPAD_DOWN_IDX]  == LOW);
  bool left  = (dpadDebouncedState[DPAD_LEFT_IDX]  == LOW);
  bool right = (dpadDebouncedState[DPAD_RIGHT_IDX] == LOW);

  // Determine hat value (0 = center, 1-8 = directions)
  // HAT values (per BLE Gamepad spec):
  // 0 = center
  // 1 = up
  // 2 = up-right
  // 3 = right
  // 4 = down-right
  // 5 = down
  // 6 = down-left
  // 7 = left
  // 8 = up-left
  StickState s = {0, AXIS_CENTER, AXIS_CENTER};

  if (up && right)      { s.hat = 2; s.x = AXIS_MAX; s.y = AXIS_MIN; }
  else if (up && left)  { s.hat = 8; s.x = AXIS_MIN; s.y = AXIS_MIN; }
  else if (down && right){ s.hat = 4; s.x = AXIS_MAX; s.y = AXIS_MAX; }
  else if (down && left){ s.hat = 6; s.x = AXIS_MIN; s.y = AXIS_MAX; }
  else if (up)          { s.hat = 1; s.y = AXIS_MIN; }
  else if (right)       { s.hat = 3; s.x = AXIS_MAX; }
  else if (down)        { s.hat = 5; s.y = AXIS_MAX; }
  else if (left)        { s.hat = 7; s.x = AXIS_MIN; }

  return s;   // return positioning data
}


// Function to call to go to sleep
void go_deep_sleep() {
  // Entering deep sleep procedure
  DEBUG_PRINTLN("Beginning deep sleep procedure ...");
  delay(5); //delay so we can print the serial message above.

  // Configure Wake up by pushing either SELECT OR START Buttons 
  // START button RTC setup
  rtc_gpio_init(START_BUTTON);
  rtc_gpio_set_direction(START_BUTTON, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_pulldown_dis(START_BUTTON);
  rtc_gpio_pullup_en(START_BUTTON);
 
  // SELECT button RTC setup
  rtc_gpio_init(SELECT_BUTTON);
  rtc_gpio_set_direction(SELECT_BUTTON, RTC_GPIO_MODE_INPUT_ONLY);
  rtc_gpio_pulldown_dis(SELECT_BUTTON);
  rtc_gpio_pullup_en(SELECT_BUTTON);
    
  // Wake when either buttons are LOW
  // Use ESP_EXT1_WAKEUP_ANY_LOW if you want to Wake up by single push from either of the buttons. 
  // Use ESP_EXT1_WAKEUP_ALL_LOW to wake up when both buttons are pressed, however physical pull-up resistors 10K to 3.3V are required on those pins.
  // Use ESP_EXT1_WAKEUP_ANY_LOW is not available for ESP32-E DFR1139 board so we'll be using ESP_EXT1_WAKEUP_ALL_LOW for compatibility with all boards.
  // Even if we don't have physical pull-ups, the board wakes up with either of the buttons and then on setup() we check if both buttons are pressed or we sleep again
  esp_sleep_enable_ext1_wakeup((1ULL << START_BUTTON) | (1ULL << SELECT_BUTTON), ESP_EXT1_WAKEUP_ALL_LOW);    // we use the ALL_LOW however it works as either when no physical pull-ups
    
  DEBUG_PRINTLN("Goodbye ... ");
  delay(5); //delay so we can print the serial message above.
  esp_deep_sleep_start(); // bye bye ..................
}

// Function to update the Button states
void updateButtons() {
  unsigned long now = millis();

  for (int i = 0; i < NUM_BUTTONS; i++) {
    bool reading = digitalRead(buttonPins[i]);

    if (reading != buttonRawRead[i]) {
      buttonRawRead[i] = reading;
      buttonLastDebounceTime[i] = now;
    }

    if ((now - buttonLastDebounceTime[i]) >= DEBOUNCE_DELAY) {
        buttonDebouncedState[i] = reading;
    }
  }
}

// Function to update the DPAD states
void updateDpad() {
  unsigned long now = millis();

  for (int i = 0; i < NUM_DPAD; i++) {
    bool reading = digitalRead(dpadPins[i]);

    if (reading != dpadRawRead[i]) {
      dpadRawRead[i] = reading;
      dpadLastDebounceTime[i] = now;
    }

    if ((now - dpadLastDebounceTime[i]) >= DEBOUNCE_DELAY) {
      dpadDebouncedState[i] = reading;
    }
  }
}

// Function to catch the combo key combination presses
void handleCombos() {
  static bool combo1PressedLast = false;  // keep state from previous loop
  static bool combo2PressedLast = false;  // keep state from previous loop

  // ---- Combo 1 detection (Hand Side Toggle): buttons 1,2,5,6 ----
  bool combo1PressedNow = (buttonDebouncedState[0] == LOW && buttonDebouncedState[1] == LOW && buttonDebouncedState[4] == LOW && buttonDebouncedState[5] == LOW);   // Evaluate to true when all are LOW
  // ---- Combo 2 detection (Mode Toggle): buttons 3,4,7,8 ----
  bool combo2PressedNow = (buttonDebouncedState[2] == LOW && buttonDebouncedState[3] == LOW && buttonDebouncedState[6] == LOW && buttonDebouncedState[7] == LOW);   // Evaluate to true when all are LOW

  // ---- Combo 1 Edge detection: toggle once per press ----
  if (combo1PressedNow && !combo1PressedLast) {
    activeGamepadMap = (activeGamepadMap == gamepadMapRightHand)
          ? gamepadMapLeftHand
          : gamepadMapRightHand;
    DEBUG_PRINTLN("Button mapping toggled");
  }

  // ---- Combo 2 Edge detection: toggle once per press ----  
  if (combo2PressedNow && !combo2PressedLast) {
      // Combo was just pressed
      stickMode = (stickMode == STICK_MODE_HAT)
                    ? STICK_MODE_AXIS
                    : STICK_MODE_HAT;

      DEBUG_PRINTLN(stickMode == STICK_MODE_HAT
                    ? "Switched to HAT mode"
                    : "Switched to AXIS mode");
  }

  combo1PressedLast = combo1PressedNow;     // We make sure combo is not run again
  combo2PressedLast = combo2PressedNow;     // We make sure combo is not run again
}

// Function for the LED blinker
void handleLEDBlink() {
  // LED heartbeat
  unsigned long now = millis();
  if (now - lastBlinkTime >= BLINK_INTERVAL) {
    lastBlinkTime = now;
    ledState = !ledState;  // toggle LED state
    digitalWrite(LED, ledState);
  }
  
  if (stickMode == STICK_MODE_HAT){   // change LED blinking depending on stick mode
    BLINK_INTERVAL = 200;
  }else{
    BLINK_INTERVAL = 50;
    }
}

// Function for handling the BLE lib
void handleBLE(){
  // ---- Bluetooth actions ----
  if (bleGamepad.isConnected()){    // This runs whenever there is an active connection with a host
    
    if (!bleWasConnected) {   // Send an initial neutral state only once
      bleGamepad.setHat1(0);  // centered HAT
      bleGamepad.setLeftThumb(AXIS_CENTER, AXIS_CENTER);    //centered x,y axis
      bleGamepad.sendReport();
      bleWasConnected = true;   //set flag so we don't run this again
    }

    bool stateChanged = false;

    // --- Process button debounced states ---
    for (int i = 0; i < NUM_BUTTONS; i++) {
      if (buttonDebouncedState[i] != buttonLastDebouncedState[i]) {
        if (buttonDebouncedState[i] == LOW) {
          bleGamepad.press(activeGamepadMap[i]);    // trigger the specific key on the active key map
          DEBUG_PRINTF("Button pressed : %d\n", activeGamepadMap[i]);
        } else {
          bleGamepad.release(activeGamepadMap[i]);    // release the specific key on the active key map
          DEBUG_PRINTF("Button released : %d\n", activeGamepadMap[i]);
        }
        buttonLastDebouncedState[i] = buttonDebouncedState[i];
        stateChanged = true;  // raise flag as we need to send a report
      }
    }

    // --- Process DPAD debounced states ---
    StickState newStick = readDpadState();
    if (newStick.hat != lastStick.hat) {    // check for any change in dpad
      if (stickMode == STICK_MODE_HAT) {
        bleGamepad.setHat1(newStick.hat);   // set the new hat value
        DEBUG_PRINTF("HAT changed to : %d\n", newStick.hat);
      } else {
        bleGamepad.setLeftThumb(newStick.x, newStick.y);   // set the new axis coordinates
        DEBUG_PRINTF("Axis is x: %d   y: %d  \n", newStick.x, newStick.y);
      }
      lastStick = newStick; // this is now the last known DPAD state
      stateChanged = true;  // raise flag as we need to send a report
    }

    // Send a BLE report only when something changed
    if (stateChanged) {
      bleGamepad.sendReport();
      lastSleepTime = millis(); //reset inactivity timer 
    }
  }
  else {
    BLINK_INTERVAL = 1000;  // if noone is connected LED should blink at slow rate
  }

}

void loop() {         // main code here runs repeatedly

  updateButtons();  // refresh button states

  updateDpad();   // refresh DPAD state

  handleBLE();    // Send BLE report if anything has changed

  handleCombos();    // check if a combo key was pressed and take action

  handleLEDBlink();   // Blink happily 

  // Battery State measure and advertise (Only applicable for ESP32-C6 DFR1075 Board)
  #if VOLT_MEASURE_AVAILABLE
    unsigned long now = millis();
    if (now - lastBattMeasureTime >= 10000) {   // check and advertise battery level every 10 seconds
      lastBattMeasureTime = now;
      int adcMv = analogReadMilliVolts(0);    // read form Analog GPIO 0 port which for FireBeetle 2 ESP32-C6 and Beetle ESP32-C6 is connected to the battery
      int batteryMv = adcMv * 2;  // Voltage divider compensation adjust if divider ratio changes
      uint8_t batteryPercent = batteryMvToPercent(batteryMv);   // call function to convert to %
      DEBUG_PRINTF("Battery Stats -- ADC millivolts value : %d mV     Battery millivolts : %d mV      Battery level : %d %% \n", adcMv,batteryMv,batteryPercent);

      bleGamepad.setBatteryPowerInformation(POWER_STATE_PRESENT);   // send BLE Battery reports
      bleGamepad.setBatteryLevel(batteryPercent);                   // send BLE Battery reports
    }
  #endif

  // Log Inactivity counter
  #if DEBUG_SERIAL
    static unsigned long lastInactivityLog = 0;   // timer for the inactivity log
    unsigned long inactiveMs = millis() - lastSleepTime;
    if (inactiveMs >= lastInactivityLog + 30000) {    // update every 30 seconds we don't spam serial console
      lastInactivityLog += 30000;
      DEBUG_PRINTF("Inactive for : %lu seconds\n", inactiveMs / 1000);
    }
  #endif

  // --- Deep sleep: enter deep sleep if inactive for 15 minutes ---
  if (millis() - lastSleepTime >= Sleep_Inactivity_INTERVAL) {
  go_deep_sleep();
  }
  
}
