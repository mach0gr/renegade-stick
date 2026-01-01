// This is proposed pinout definition for ESP32-S3 DFR1145 board 
// For this board, do not use GPIO 21 (onboard LED) and avoid GPIO 0 (used by the BOOT button). 
// Firebeetle 2 ESP32-S3(N4) DFR1145 --> https://wiki.dfrobot.com/_SKU_DFR1145_FireBeetle_2_ESP32_S3_N4_IoT_development_board

#define PRODUCT_PID 0x0002
#define VOLT_MEASURE_AVAILABLE 0

#define BUTTON_1      GPIO_NUM_4		// A0
#define BUTTON_2      GPIO_NUM_5		// A1
#define BUTTON_3      GPIO_NUM_6		// A2
#define BUTTON_4      GPIO_NUM_8		// A3
#define BUTTON_5      GPIO_NUM_10		// A4
#define BUTTON_6      GPIO_NUM_11		// A5
#define START_BUTTON  GPIO_NUM_9		// D7
#define SELECT_BUTTON GPIO_NUM_0		// D9    //currently wired to (0/D9) proposed 12/D12
#define DPAD_L        GPIO_NUM_18		// D6
#define DPAD_R        GPIO_NUM_7		// D5
#define DPAD_UP       GPIO_NUM_38		// D3
#define DPAD_DOWN     GPIO_NUM_3		// D2

#define LED           GPIO_NUM_21   // the onboard LED pin

// ---------------------- Flashing Guide ----------------------
// Flashing the ESP32-S3 DFR1145 board is generally straightforward.
// Programming mode is entered automatically during flashing, manual intervention is usually not required.
//
// If you encounter issues, instructions for manually entering programming mode are provided below.

// Automatic Programming Mode
// In normal operation, the board enters programming mode automatically.
// You typically only need to press Flash or Upload in your flashing tool.


// ---- Entering Manual Programming Mode for ESP32-S3 DFR1145 ----
//
// If a battery is connected:
//   1. Connect USB.
//   2. Hold the BOOT button.
//   3. Press RESET briefly while continuing to hold BOOT.
//   4. Keep holding BOOT for another 5 seconds.
//   5. Press Flash/Upload in your flashing software.
//   6. When flashing finishes, press RESET once.
//
// If no battery is connected (method 1):
//   1. Connect USB.
//   2. Hold BOOT.
//   3. Press RESET briefly while continuing to hold BOOT.
//   4. Keep holding BOOT for another 5 seconds.
//   5. Press Flash/Upload.
//   6. Press RESET once when finished.
//
// If no battery is connected (method 2):
//   1. Hold BOOT.
//   2. Connect USB while continuing to hold BOOT.
//   3. Keep holding BOOT for another 5 seconds.
//   4. Press Flash/Upload.
//   5. Press RESET once when finished.


// ---------------------- Flash File ----------------------
// You can either download a precompiled .bin file from the renegade‑stick GitHub repo or compile it yourself using the Arduino environment.
// Arduino can also flash the board automatically after compiling.

// You’ll need to identify the USB COM port your board appears on.
// Connect the board with a USB‑C cable.
// On Windows, open Device Manager → “Ports (COM & LPT)”.
// Look for “USB Serial Device (COM X)”. Note the COM number.
// If unsure which device is the board, unplug USB and see which entry disappears.


// ---- Flashing with flash_download_tool ----
// Download the correct .bin file from the renegade‑stick GitHub repo.
// Download the official ESP32 flasher here:
// https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool.html
// Unfortunately, flashing the ESP32-S3 DFR1145 using Espressif's Flash Download Tool was not successful on my side.
// Use one of the methods below instead..

// ---- Flash using Python esptool ----
// Acquire the correct precompiled .bin file from the Renegade Stick GitHub repository.
//
// On Windows, install Python from the Microsoft Store.
// Then install esptool using:
//   pip install esptool
//
// Example command (adjust COM port and file path as needed):
// python -m esptool --chip esp32s3 --port COM3 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\path\to\renegade-stick_DFR1145_vXX.bin"
//
// The board will enter programming mode automatically and flash.
// When flashing finishes, press RESET once.

// ---- Compile and flash using Arduino ----
// Use the DFRobot wiki link above to set up your Arduino environment.
// Select the following Arduino Tools/Options settings:
//
// Arduino Tools/Options for build
// Board: esp32 -> DFRobot FireBeetle 2 ESP32-S3
// Port: Select the correct COM port
// USB CDC On Boot: Disabled (enable for debugging)
// USB DFU On Boot: Disabled
// Erase Flash Before Upload: Disabled
// Flash Mode: QIO 80MHz
// Flash Size: 4MB
// USB Firmware MSC On Boot: Disabled
// Partition Scheme: Default 4MB with SPIFFS
// PSRAM: Disabled
// Upload Mode: UART0 / Hardware CDC
// Upload Speed: 115200
// USB Mode: Hardware CDC and JTAG
// Programmer: esptool


// Start Arduino and open the sketch.
// Make the required selections in Arduino Tools/Options as described above and select the correct COM port.
// Press the Upload button. The project will compile and automatically and upload to the board.
// When the upload finishes, press RESET once.


// ---- Compile in Arduino but Flash with Python esptool ----
// If you prefer using esptool but want Arduino to generate the .merged.bin:
//
// 1. In Arduino Preferences, enable “verbose mode”.
// 2. Click Verify/Compile (not Upload).
// 3. When compilation finishes, look in the log for the path of the .merged.bin file. Note down the path
//    Example:
//    “Wrote 0x400000 bytes to file 'C:\Users\xxxx\AppData\Local\arduino\sketches\...\renegade-stick_v17.ino.merged.bin'”
//
// 4. Example command to run (adjust COM port and file path as required):
//
// python -m esptool --chip esp32s3 --port COM3 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\path\to\renegade-stick_xxxxx.ino.merged.bin"
//
// 5. The board will enter programming mode automatically.
// 6. Press RESET once when flashing is done.