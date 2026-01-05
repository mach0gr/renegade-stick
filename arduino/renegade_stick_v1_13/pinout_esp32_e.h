// This is proposed pinout definition for ESP32-E DFR1139 board 
// For this board you should not use GPIO 34, 35, 36, 39(no pullups), GPIO 2(LED) 
// Firebeetle 2 ESP32-E (N16R2) DFR1139 --> https://wiki.dfrobot.com/_SKU_DFR1139_FireBeetle_2_ESP32_E_N16R2_IoT_Microcontroller

#define PRODUCT_PID 0x0001
#define VOLT_MEASURE_AVAILABLE 0

#define BUTTON_1      GPIO_NUM_22 	// SCL
#define BUTTON_2      GPIO_NUM_21 	// SDA
#define BUTTON_3      GPIO_NUM_15 	// A4
#define BUTTON_4      GPIO_NUM_12 	// D13
#define BUTTON_5      GPIO_NUM_4  	// D12
#define BUTTON_6      GPIO_NUM_17 	// D10
#define BUTTON_7      GPIO_NUM_19		// MISO
#define BUTTON_8      GPIO_NUM_23		// MOSI
#define START_BUTTON  GPIO_NUM_13  	// D7
#define SELECT_BUTTON GPIO_NUM_14  	// D6
#define DPAD_L        GPIO_NUM_0 		// D5
#define DPAD_R        GPIO_NUM_26		// D3
#define DPAD_UP       GPIO_NUM_25		// D2
#define DPAD_DOWN     GPIO_NUM_1 		// TX

#define LED           GPIO_NUM_2		// the onboard LED pin

// ---------------------- Flashing Guide ----------------------
// Flashing ESP32-E (N16R2) DFR1139 board is slightly tricky, but not too difficult. 
// Entering programming mode must be done manually using the RESET button.
// Read the instructions below carefully.

// ---- Entering Manual Programming Mode for ESP32-E (N16R2) DFR1139 ----
// Entering programming mode can be timing-sensitive. Follow the procedure below.
//
// If a battery is connected:
//   1. First connect USB.
//   2. Press Flash/Upload in your flashing software.
//   3. When you see "Connecting...........", press and hold the RESET button for at least one second.
//   4. If it times out, try again.(Sometimes double clicking the RESET instead of holding it for a second does the job)
//   5. When the upload finishes, press RESET once.
//
// If no battery is connected:
//   1. Connect USB.
//   2. Press Flash/Upload in your flashing software.
//   3. When you see "Connecting...........", press and hold RESET for at least one second.
//   4. If it times out, try again.(Sometimes double clicking the RESET instead of holding it for a second does the job)
//   5. When the upload finishes, press RESET once.

// ---------------------- Flash File ----------------------
// You can either download a precompiled .bin file from the renegade‑stick GitHub repo or compile it yourself using the Arduino environment.
// Arduino can also flash the board automatically after compiling.

// You’ll need to identify the USB COM port your board appears on.
// Connect the board with a USB‑C cable.
// On Windows, open Device Manager → “Ports (COM & LPT)”.
// Look for “USB Serial Device (COM X)”. Note the COM number.
// If unsure which device is the board, unplug USB and see which entry disappears.


// ---- Flash using flash_download_tool ----
// Acquire the correct precompiled .bin file from the Renegade Stick GitHub repository
// (make sure to select the correct board version).
//
// Download the official ESP32 Flash Download Tool:
// https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool.html
//
// Steps:
//   1. Run the tool and select board "ESP32", Workmode "Develop", then press OK.
//   2. Click the "..." button and select the downloaded .bin file.
//   3. Enter 0x0 as the address and enable the checkbox.
//   4. Select the correct COM port.
//   5. Click START.
//   6. When you see "........", press and hold RESET for at least one second.
//   7. If it times out, try again.(Sometimes double clicking the RESET instead of holding it for a second does the job)
//   8. When flashing completes, press RESET once.

// ---- Flash using Python esptool ----
// Acquire the correct precompiled .bin file from the Renegade Stick GitHub repository.
//
// On Windows, install Python from the Microsoft Store.
// Then install esptool using:
//   pip install esptool
//
// Example command (replace COM port and file path as needed):
// python -m esptool --chip esp32 --port COM4 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\path\to\renegade-stick_DFR1139_vXX.bin"
//
// Enter programming mode as described above.
// Press RESET when the upload finishes.


// ---- Compile and flash using Arduino ----
// Use the DFRobot wiki link above to set up your Arduino environment.
// Select the following settings:
//
// Board: esp32 -> FireBeetle 2 ESP32-E
// Port: Select the correct COM port
// Erase Flash Before Upload: Disabled
// Flash Frequency: 80MHz
// Flash Mode: QIO
// Flash Size: 16MB
// Partition Scheme: 16MB Flash (2MB APP / 12.5MB FAT)
// PSRAM: Enabled
// Upload Speed: 115200
// Programmer: esptool

// Start Arduino and open the sketch.
// Make the required selections in Arduino Tools/Options as described above and select the correct COM port.
// Press the Compile and Upload button. This will compile the project (which may take some time) and upload it to the board.
//
// When the console displays "Connecting...........", press and hold the RESET button for at least one second. In some cases, a double-click on RESET may be required. If the upload times out, try again.
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
// python -m esptool --chip esp32 --port COM4 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\path\to\renegade-stick_xxxxx.ino.merged.bin""
//
// 5. When the console displays "Connecting...........", press and hold RESET for at least one second to enter programming mode. A double-click may be required.
// 6. Press RESET once when flashing is done.

