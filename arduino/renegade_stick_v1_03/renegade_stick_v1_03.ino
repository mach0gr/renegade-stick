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

#include <Arduino.h>
#include <BleGamepad.h> // using library from https://github.com/lemmingDev/ESP32-BLE-Gamepad/tree/master
#include <driver/rtc_io.h> // needed for rtc api deep sleep

#if CONFIG_IDF_TARGET_ESP32C6
  #include "pinout_esp32_c6.h"    // pinout Definitions for Firebeetle 2 ESP32-C6 DFR1075

#elif CONFIG_IDF_TARGET_ESP32S3
  #include "pinout_esp32_s3.h"    // pinout Definitions for Firebeetle 2 ESP32-S3(N4) DFR1145

#elif CONFIG_IDF_TARGET_ESP32
  #include "pinout_esp32_e.h"     // pinout Definitions for Firebeetle 2 ESP32-E (N16R2) DFR1139

#else
  #error "Unsupported ESP32 target"
#endif

#define DEBUG_SERIAL 0   // set to 0 to disable serial debug output

#if DEBUG_SERIAL    // Define debug serial console macros so they can be disabled with above definition at compile time.
  #define DEBUG_BEGIN(...)    Serial.begin(__VA_ARGS__)
  #define DEBUG_PRINTF(...)   Serial.printf(__VA_ARGS__)
  #define DEBUG_PRINT(...)    Serial.print(__VA_ARGS__)
  #define DEBUG_PRINTLN(...)  Serial.println(__VA_ARGS__)
#else
  #define DEBUG_BEGIN(...)    do {} while (0)
  #define DEBUG_PRINTF(...)   do {} while (0)
  #define DEBUG_PRINT(...)    do {} while (0)
  #define DEBUG_PRINTLN(...)  do {} while (0)
#endif

// ---------------------------------------------------------------
// Led Configuration
unsigned long BLINK_INTERVAL = 1000;   // LED blink time interval 500 milliseconds
unsigned long lastBlinkTime = 0;       // Variable to be used as a global counter for LED blink interval
bool ledState = LOW;                   // Keep last LED led State

// ---------------------------------------------------------------
// Battery Measurement Configuration
#if VOLT_MEASURE_AVAILABLE
  unsigned long lastBattMeasureTime = 0;    // Variable to be used as a global counter for Measuring battery
  #define BATT_MIN_MV 3300    // minimum value for the li-po battery ~ 3.3V
  #define BATT_MAX_MV 4152    // maximum value for the charged li-po battery ~ 4.2V
#endif

// ---------------------------------------------------------------
// Deep Sleep config
bool bleWasConnected = false;   // used to sent an initial state once connected.
constexpr unsigned long Sleep_Inactivity_INTERVAL = 300000;   // Sleep time interval (If inactive for x milliseconds, it will enter sleep mode) 300000 milliseconds = 5 minutes
unsigned long lastSleepTime = 0;                          // Variable to be used as a global counter for sleep timer

// ---------------------------------------------------------------
// Button configuration
constexpr uint8_t NUM_BUTTONS = 8;
constexpr unsigned long DEBOUNCE_DELAY = 5;   // debounce in milliseconds

//The order of these three arrays matters a lot, be carefully when changing them
int buttonPins[NUM_BUTTONS] = {BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4, BUTTON_5, BUTTON_6, START_BUTTON, SELECT_BUTTON};
int androidGamepadButtons[NUM_BUTTONS] = {1, 2, 3, 4, 5, 6, 12, 11};

// Track button state and timing. (We're coding to detect an active LOW so we init everything with PULLUP resistor)
// If you want to put these definitions in a loop rather than manually, they have to be put under setup(). I'll be doing it manually here
bool lastStableState[NUM_BUTTONS] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};   // last known good state
bool lastReading[NUM_BUTTONS]     = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};   // most recent raw read
unsigned long lastDebounceTime[NUM_BUTTONS] = {0, 0, 0, 0, 0, 0, 0, 0};  // timestamp of last change

bool lastStableDPAD[4] = {HIGH, HIGH, HIGH, HIGH}; 
bool lastReadingDPAD[4] = {HIGH, HIGH, HIGH, HIGH};
unsigned long lastDebounceDPAD[4] = {0};

constexpr int16_t AXIS_MIN = 0;   // Axis min value (using setAxesMin:setAxesMax 0:32767)
constexpr int16_t AXIS_CENTER = 16383;  // Centered value (using setAxesMin:setAxesMax 0:32767)
constexpr int16_t AXIS_MAX = 32767;   // Axis max value (using setAxesMin:setAxesMax 0:32767)


// --------------------------------------------------
// Stick mode handling
enum StickMode {
  STICK_MODE_HAT,
  STICK_MODE_AXIS
};
StickMode stickMode = STICK_MODE_AXIS;   // default mode is Axis

// Dpad stick state handling
struct StickState {
  uint8_t hat;       // 0–8
  int16_t x;
  int16_t y;
};

StickState currentStick = {0, AXIS_CENTER, AXIS_CENTER};
StickState lastStick    = {0, AXIS_CENTER, AXIS_CENTER};
       
unsigned long comboPressTime = 0;   // for edge detection
const unsigned long COMBO_HOLD_TIME = 300; // ms (optional safety)
// --------------------------------------------------

//Generate a unique Serial Number for each controller. This ensures two or more can be paired as they will have different Serial Numbers
char serialNumber[16];   // Enough space for serial string
uint64_t mac = ESP.getEfuseMac();   // 48-bit unique MAC, extract a unique byte from board IC
uint16_t shortID = (mac >> 8) & 0xFFFF;  // extract part of MAC

BleGamepad bleGamepad("Renegade Stick", "mach0gr", 100);  // Declare bleGamepad Bluetooth Name to init the device.
BleGamepadConfiguration bleGamepadConfig; // Create a BleGamepadConfiguration object to store all of the options

void setup() {    // setup code here, runs once:
  delay(1000);
  DEBUG_BEGIN(115200);   // will be using this for debug/monitoring. Maybe for final version we disable it for performance reasons.
  DEBUG_PRINTLN("Starting BLE Gamepad...");

  sprintf(serialNumber, "%010u", shortID); // create zero-padded 10-digit serial
  DEBUG_PRINTF("Board Serial No: %s \n", serialNumber);

  for(int i=0; i<NUM_BUTTONS; i++){  // setup pullup resistor for all our inputs (input pins have been selected to be compatible with pull_up, not used with other functions of esp32)
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Hereby we check on startup if both buttons were pressed at the same time so we can wake up the board
  delay(200); // debounce for pullups
  if (digitalRead(START_BUTTON) == LOW && digitalRead(SELECT_BUTTON) == LOW) {
    DEBUG_PRINTLN("Valid wake: both buttons pressed");
  } 
  else {
    DEBUG_PRINTLN("Invalid wake: going back to sleep");
    delay(1000);
    go_deep_sleep();
  }

  // Setup the analog resolution used for battery measurement to 12 bits (0-4096)
  #if VOLT_MEASURE_AVAILABLE
    analogReadResolution(12);
  #endif


  // Setup DPAD pins
  pinMode(DPAD_L, INPUT_PULLUP);
  pinMode(DPAD_R, INPUT_PULLUP);
  pinMode(DPAD_UP, INPUT_PULLUP);
  pinMode(DPAD_DOWN, INPUT_PULLUP);

  pinMode(LED, OUTPUT);  // this is the board's LED, will be used to flash everytime a button is pressed to act like an activity led

  //BLE config through ESP32-BLE-Gamepad Library
  // configuring the BleGamepad library
  bleGamepadConfig.setAutoReport(false);  // we will be sending report when we want it
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setButtonCount(12);
  bleGamepadConfig.setVid(0xe502);
  bleGamepadConfig.setPid(PRODUCT_PID);
  bleGamepadConfig.setHatSwitchCount(1);
  bleGamepadConfig.setTXPowerLevel(9);  // Defaults to 9 if not set. The only valid values are: -12, -9, -6, -3, 0, 3, 6 and 9 (Values correlate to dbm)
  bleGamepadConfig.setModelNumber("1.0");
  bleGamepadConfig.setSoftwareRevision("Software Rev v1.03");
  bleGamepadConfig.setSerialNumber(serialNumber);
  bleGamepadConfig.setFirmwareRevision("2.0");
  bleGamepadConfig.setHardwareRevision("1.7");
  // Some non-Windows operating systems and web based gamepad testers don't like min axis set below 0, so 0 is set by default
  //bleGamepadConfig.setAxesMin(0x8001); // -32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setAxesMin(0x0000); // 0 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setAxesMax(0x7FFF); // 32767 --> int16_t - 16 bit signed integer - Can be in decimal or hexadecimal
  bleGamepadConfig.setWhichAxes(1, 1, 0, 0, 0, 0, 0, 0); // enable X and Y axes only
  // Now start BLE with your config
  bleGamepad.begin(&bleGamepadConfig);
  delay(3000);  // let a few seconds to setup the BLE
}


// Function to convert analog read battery mv value to percentage.
#if VOLT_MEASURE_AVAILABLE
  uint8_t batteryMvToPercent(int mv) {
    if (mv <= BATT_MIN_MV) return 0;     
    if (mv >= BATT_MAX_MV) return 100;   
    return (uint8_t)((mv - BATT_MIN_MV) * 100L / (BATT_MAX_MV - BATT_MIN_MV));
  }
#endif

// Function to compute hat value based on DPAD pins
StickState readDpadState() {
  bool up    = !digitalRead(DPAD_UP);
  bool down  = !digitalRead(DPAD_DOWN);
  bool left  = !digitalRead(DPAD_L);
  bool right = !digitalRead(DPAD_R);

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
  StickState s;
  s.hat = 0;
  s.x = AXIS_CENTER;
  s.y = AXIS_CENTER;

  if (up && right)      { s.hat = 2; s.x = AXIS_MAX;   s.y = AXIS_MIN; }
  else if (up && left)  { s.hat = 8; s.x = AXIS_MIN;   s.y = AXIS_MIN; }
  else if (down && right){ s.hat = 4; s.x = AXIS_MAX; s.y = AXIS_MAX; }
  else if (down && left){ s.hat = 6; s.x = AXIS_MIN;  s.y = AXIS_MAX; }
  else if (up)          { s.hat = 1; s.y = AXIS_MIN; }
  else if (right)       { s.hat = 3; s.x = AXIS_MAX; }
  else if (down)        { s.hat = 5; s.y = AXIS_MAX; }
  else if (left)        { s.hat = 7; s.x = AXIS_MIN; }

  return s;
}


// Function to call to go to sleep
void go_deep_sleep() {
  // Entering deep sleep procedure
  DEBUG_PRINTLN("Beginning deep sleep procedure ...");
  delay(5); //delay so we can print the serial message above.

  // Configure Wake up by pushing both SELECT and START Buttons at the same time 
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
  // Use ESP_EXT1_WAKEUP_ALL_LOW to wake up of both button press, however physical pull-up resistors 10K to 3.3V are required on those pins.
  // Use ESP_EXT1_WAKEUP_ANY_LOW is not available for ESP32-E DFR1139 board so we'll be using ESP_EXT1_WAKEUP_ALL_LOW for compatibility with all boards.
  // Even if we don't have physical pull-ups, the board wakes up with either of the buttons and then on setup() we check if both buttons are pressed or we sleep again
  esp_sleep_enable_ext1_wakeup((1ULL << START_BUTTON) | (1ULL << SELECT_BUTTON), ESP_EXT1_WAKEUP_ALL_LOW);
    
  DEBUG_PRINTLN("Goodbye ... ");
  delay(5); //delay so we can print the serial message above.
  esp_deep_sleep_start(); // bye bye ..................
}

void loop() {
  // put your main code here, to run repeatedly:

  // ---- Combo detection: buttons 1 to 6 ----
  bool comboPressedNow = true;
  for (int i = 0; i < 6; i++) {
    if (digitalRead(buttonPins[i]) != LOW) { // active LOW
      comboPressedNow = false;
      break;
    }
  }

  // ---- Edge detection: toggle once per press ----
  static bool comboPressedLast = false;  // static so it retains value across loop()

  if (comboPressedNow && !comboPressedLast) {
      // Combo was just pressed
      stickMode = (stickMode == STICK_MODE_HAT)
                    ? STICK_MODE_AXIS
                    : STICK_MODE_HAT;

      DEBUG_PRINTLN(stickMode == STICK_MODE_HAT
                    ? "Switched to HAT mode"
                    : "Switched to AXIS mode");
  }

  // Update state for next loop
  comboPressedLast = comboPressedNow;

  if (bleGamepad.isConnected()){    // This runs whenever there is an active connection with a host
    
    if (stickMode == STICK_MODE_HAT){   // change LED blinking depending on mode
      BLINK_INTERVAL = 200;
    }else{
      BLINK_INTERVAL = 50;
    }
    
    if (!bleWasConnected) {   // Send initial neutral state only once
      bleGamepad.setHat1(0);  // centered / released
      bleGamepad.setLeftThumb(AXIS_CENTER, AXIS_CENTER);
      bleGamepad.sendReport();
      bleWasConnected = true;   //set flag so we don't run this again
    }

    bool stateChanged = false;

    for (int i=0; i<NUM_BUTTONS; i++){
      bool currentReading = digitalRead(buttonPins[i]);

      // If reading changed since last time, reset debounce timer
      if (currentReading != lastReading[i]) {
        lastDebounceTime[i] = millis();
        lastReading[i] = currentReading;
      }

      // If stable for longer than debounce delay, treat as new state
      if ((millis() - lastDebounceTime[i]) > DEBOUNCE_DELAY) {
        if (currentReading != lastStableState[i]) {
          lastStableState[i] = currentReading;

          if(!digitalRead(buttonPins[i])){
              bleGamepad.press(androidGamepadButtons[i]);
              //digitalWrite(LED, HIGH);
              DEBUG_PRINTF("Button pressed : %d \n", androidGamepadButtons[i]);   
          }
          else{
              bleGamepad.release(androidGamepadButtons[i]);
              //digitalWrite(LED, LOW);
              DEBUG_PRINTF("Button released : %d \n", androidGamepadButtons[i]);     
          }
          stateChanged = true;
        }
      }
    }

    // --- Process DPAD with debounce ---
    bool dpadChanged = false;
    bool dpadStates[4] = {digitalRead(DPAD_UP), digitalRead(DPAD_DOWN), digitalRead(DPAD_L), digitalRead(DPAD_R)};

    for(int i=0; i<4; i++){
      if(dpadStates[i] != lastReadingDPAD[i]){
        lastDebounceDPAD[i] = millis();
        lastReadingDPAD[i] = dpadStates[i];
      }
      if((millis() - lastDebounceDPAD[i]) > DEBOUNCE_DELAY){
        if(dpadStates[i] != lastStableDPAD[i]){
          lastStableDPAD[i] = dpadStates[i];
          dpadChanged = true;
        }
      }
    }

    if (dpadChanged) {
      currentStick = readDpadState();
      if (currentStick.hat != lastStick.hat) {
        if (stickMode == STICK_MODE_HAT) {
          bleGamepad.setHat1(currentStick.hat);
        } else {
          bleGamepad.setLeftThumb(currentStick.x, currentStick.y);
        }
      lastStick = currentStick;
      stateChanged = true;
      DEBUG_PRINTF("DPAD -> hat:%d x:%d y:%d\n", currentStick.hat, currentStick.x, currentStick.y);
      }
    }

    // Send a BLE report only when something changed
    if (stateChanged) {
      bleGamepad.sendReport();
      lastSleepTime = millis(); //reset inactivity timer 
    }
  }
  else {
    BLINK_INTERVAL = 1000;
  }

  // LED heartbeat:
  unsigned long currentMillis = millis();
  if (currentMillis - lastBlinkTime >= BLINK_INTERVAL) {
    lastBlinkTime = currentMillis;
    ledState = !ledState;  // toggle
    digitalWrite(LED, ledState);
  }

  // Battery State measure and advertise (Only applicable for ESP32-C6 DFR1075 Board)
#if VOLT_MEASURE_AVAILABLE
  if (currentMillis - lastBattMeasureTime >= 10000) {   // check and advertise battery level every 10 seconds
    lastBattMeasureTime = currentMillis;
    int adcMv = analogReadMilliVolts(0);    // read form Analog GPIO 0 port which for FireBeetle 2 ESP32-C6 and Beetle ESP32-C6 is connected to the battery
    int batteryMv = adcMv * 2;  // Voltage divider compensation adjust if divider ratio changes
    uint8_t batteryPercent = batteryMvToPercent(batteryMv);
    DEBUG_PRINTF("Battery Stats -- ADC millivolts value : %d mV     Battery millivolts : %d mV      Battery level : %d %% \n", adcMv,batteryMv,batteryPercent);

    bleGamepad.setBatteryPowerInformation(POWER_STATE_PRESENT);
    bleGamepad.setBatteryLevel(batteryPercent);
  }
#endif

  if ((millis() - lastSleepTime + 1) % 30000 == 0) {   // print inactivity counter every 30 second (we add +1 because when millis=lastSleepTime and the equation is 0 it trigers)
    DEBUG_PRINTF("Inactive for : %d seconds \n", (millis() - lastSleepTime)/1000 );
  }


  // --- Deep sleep: enter deep sleep if inactive for 15 minutes ---
  if (millis() - lastSleepTime >= Sleep_Inactivity_INTERVAL) {
  go_deep_sleep();
  }
  
  //delay(1); // Small pacing delay (not part of debounce)
}
