// This is proposed pinout definition for ESP32-C6 DFR1075 board 
// For this board you should not use GPIO 15(LED), GPIO 9(BOOT BUTTON), GPIO 0, 2, 8, 9 (affect bootup). 
// Firebeetle 2 ESP32-C6 DFR1075 --> https://wiki.dfrobot.com/SKU_DFR1075_FireBeetle_2_Board_ESP32_C6

#define PRODUCT_PID 0x0003
#define VOLT_MEASURE_AVAILABLE 1

#define BUTTON_1      GPIO_NUM_3		// A2
#define BUTTON_2      GPIO_NUM_4		// A3
#define BUTTON_3      GPIO_NUM_5		// A4
#define BUTTON_4      GPIO_NUM_14		// D3
#define BUTTON_5      GPIO_NUM_16		// TX
#define BUTTON_6      GPIO_NUM_17		// RX
#define START_BUTTON  GPIO_NUM_6		// D12
#define SELECT_BUTTON GPIO_NUM_7		// D11
#define DPAD_L        GPIO_NUM_20		// SCL
#define DPAD_R        GPIO_NUM_21		// MI
#define DPAD_UP       GPIO_NUM_22		// MO
#define DPAD_DOWN     GPIO_NUM_23		// SCK

#define LED           GPIO_NUM_15		// the onboard LED pin


// ---------------------- Flashing Guide ----------------------
// Flashing ESP32‑C6 v0.1 chips wasn’t as straightforward as expected.
// I’m not sure if newer chip revisions or software updates fix this, but on the two v0.1 boards I tested, entering programming mode must be done manually using the BOOT and RESET buttons.
// See below for instructions on how to enter programming mode.


// ---- Entering Manual Programming Mode (ESP32‑C6 DFR1075) ----
// On ESP32‑C6 v0.1 chips, the automatic USB reset doesn’t work correctly, so the chip fails to enter or exit boot mode on its own.
// No matter which flashing tool you use, you must manually put the board into programming mode first. 
// Procedure below:

// If a battery is connected:
//   1. Connect USB.
//   2. Hold the BOOT button.
//   3. Quickly press RESET while still holding BOOT.
//   4. Keep holding BOOT for ~5 seconds.
//   5. Flash/upload using your tool.
//   6. When finished, press RESET once.

// If no battery is connected (method 1):
//   1. Connect USB.
//   2. Hold BOOT.
//   3. Quickly press RESET while still holding BOOT.
//   4. Keep holding BOOT for ~5 seconds.
//   5. Flash/upload.
//   6. Press RESET once when done.

// If no battery is connected (method 2):
//   1. Hold BOOT.
//   2. Plug in USB while still holding BOOT.
//   3. Keep holding BOOT for ~5 seconds.
//   4. Flash/upload.
//   5. Press RESET once when done.


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
// Unfortunately, I haven’t found a way to flash ESP32‑C6 v0.1 chips with this tool, because this chip revision requires --no-stub mode.
// Use one of the methods below instead.


// ---- Flashing with Python esptool ----
// Download the correct .bin file from the renegade‑stick GitHub repo.
// On Windows, install Python from the Microsoft Store.
// Then open Command Prompt and install esptool:
//     pip install esptool
//
// ESP32‑C6 v0.1 chips must be flashed using --no-stub mode.
// Prepare (but don’t run yet) a command like:
//
// python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\path\to\renegade-stick_DFR1075_vXX.bin"
//
// Put the board into programming mode (see above), then press Enter.
// When flashing finishes, press RESET once.


// ---- Compile & Flash Using Arduino ----
// Follow the DFRobot wiki to set up Arduino for ESP32‑C6.
// Use the following Arduino Tools/Options:

// Board: esp32 → DFRobot FireBeetle 2 ESP32‑C6
// Port: (select the COM port you identified)
// USB CDC On Boot: Disabled (enable only if debugging)
// Erase All Flash Before Upload: Disabled
// Flash Frequency: 40 MHz
// Flash Mode: DIO
// Flash Size: 4 MB
// JTAG Adapter: Disabled
// Partition Scheme: Default 4MB with spiffs
// Upload Speed: 115200
// Zigbee Mode: Disabled
// Programmer: esptool

// *Note: ESP32‑C6 v0.1 chips cannot be flashed with stub mode,
// which Arduino enables by default when installing ESP libraries.
// To fix this:
//
// 1. Close Arduino.
// 2. Edit the file:
//    C:\Users\xxxx\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.5\platform.txt
// 3. Find: tools.esptool_py.upload.pattern_args=
// 4. Add:  --no-stub   before the --port argument.
//
// Restart Arduino, open your sketch, select the correct settings and COM port enter programming mode, and click Upload. Compilation takes a while.
// When upload finishes, press RESET once.


// ---- Compile in Arduino but Flash with Python esptool ----
// If you prefer using esptool but want Arduino to generate the .merged.bin:
//
// 1. In Arduino Preferences, enable “verbose mode”.
// 2. Click Verify/Compile (not Upload).
// 3. When compilation finishes, look in the log for the path of the .merged.bin file. Note down the path
//    Example:
//    “Wrote 0x400000 bytes to file 'C:\Users\xxxx\AppData\Local\arduino\sketches\...\renegade-stick_v17.ino.merged.bin'”
//
// 4. Prepare a command like (adjust COM port and file path as required):
//
// python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\path\to\renegade-stick_xxxxx.ino.merged.bin"
//
// 5. Enter programming mode, then run the command.
// 6. Press RESET once when flashing is done.











// Flashing Guide
// Flashing ESP32-c6 v0.1 chips was not as straight forward as I expected. 
// I don't know if they have fixed this in newer IC versions or software but for the 2 boards I tried with v0.1, booting into programming mode has to be done manually by pressing the side BOOT and RESEST buttons.
// Read below for instructions on how to enter the board into programming mode

// Entering Manual Programming mode for ESP32-C6 DFR1075
// For ESP32-c6 v0.1 chips I have found that the auto software reset through USB does not happen correctly and the chip cannot enter correct boot mode or even exit from it.
// When flashing ESP32-c6 v0.1 chips (at least on my occasion) no matter what tool you use, you have to MANUALLY enter the chip in Programming mode first in order to flash it. Proceedure below.
// If battery is connected --> First connect USB. Hold BOOT button and promptly press RESET button while keeping BOOT button pressed for another 5 seconds. Then press flash or upload from your software flasher. When finished uploading, click RESET button once.
// If battery is not connected --> Connect USB. Hold BOOT button and promptly press RESET button while keeping BOOT button pressed for another 5 seconds. Then press flash or upload from your software flasher. When finished uploading, click RESET button once.
// OR
// If battery is not connected --> While holding BOOT button, connect the USB, keep holding BOOT button pressed for another 5 seconds. Then press flash or upload from your software flasher. When finished uploading, click RESET button once.


// The flash file
// To acquire the flash file you can either download a precompiled flash file (.bin) from the renegade-stick github repository or compile it yourself using Arduino environment.
// Using Arduino environment also enables you to flash the board directly after compile finishes so no other steps are necessary.
// In any case for flashing you will need to find the USB COM port that your board is coming up. Depending on your system and how many other serial devices you have/had connected this will be a different number.
// Connect your board with a USB type C cable.
// In Windows open your "Device Manager" and find where is says "Ports (COM&LPT)" and expand it. You should be able to see "USB Serial Device(COM X)"
// Mark the COM number for later use. If you see more than one devices and are unsure which is the DFR board, just unplug the USB and you should see it go away.

// ---- Flash using flash_download_tool ----
// Acquire the correct precompiled .bin file from the renegade-stick github repository (select the correct for your board)
// download the official ESP32 flasher here --> https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool.html
// Unfortunately I haven't been able to find a way to flash the particular ESP32-C6 v0.1 chip using this tool. The particular version of chip requires --no-stub mode.
// Use other methods below.

// ---- Flash using Python esptool ----
// Aquire the correct precompiled .bin file from the renegade-stick github repository (select the correct for your board)
// In windows you can download and Install Python from MicrosoftStore
// Once installed, enter command prompt (cmd) and run the command below to download esptool flasher
// pip install esptool
// Assuming you already now have python and esptool installed you have to flash ESP32-C6 DFR1075 v0.1 chips in --no-stub mode like below.
// In your command line, prepare the following command but don't run it. (Select the correct COM port for your device as described above)
// python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash  -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\........yourpath.......\renegade-stick_DFR1075_vXX.bin"
// Enter the board into programming mode (as described above in entering programming mode for ESP32-C6 DFR1075) and then press enter. 
// Don't forget to click RESET when upload finished.


// ---- Compile and flash using Arduino ----
// Use the wiki DFR link above to setup your arduino environment. Select the below Arduino settings upon build

// Arduino Tools/Options for build
// Board : esp32 ->  DFRobot Firebeetle 2 ESP32-C6
// Port : Connect the board to find out which COM# you need to select
// USB CDC On Boot : Disabled (Enabled if you want to do debugging)
// Erase all flash before Sketch Upload : Disabled
// Flash Frequency : 40MHz
// Flash Mode : DIO
// Flash Size : 4MB
// JTAG Adapter : Disabled
// Partition Scheme : Default 4MB with spiffs
// Upload Speed 115200
// Zigbee Mode : Disabled
// Programmer : esptool

// *1 Note : For ESP32-c6 v0.1 chips I found out that they cannot be flashed with stub which is by default set up on Arduino when you install esp libraries. 
// Follow the proceedure below to fix this for Arduino
// Close Arduino and edit the following file "C:\Users\xxxx\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.5\platform.txt"
// Search in file for tools.esptool_py.upload.pattern_args=   then add argument   --no-stub    before the    --port

// Start Arduino and open sketch. Make the necessary selections in Arduino Tools/Options like above and select the correct COM port you identified above.
// Enter the board into programming mode (as described above in entering programming mode for ESP32-C6 DFR1075) and then press the Upload Button. This will compile the project (it takes a while) and upload the code to the board.
// Don't forget to click RESET when upload finished.


// ---- Compile in Arduino but flash using Python esptool ----
// Assuming you already have python and esptool installed you have to flash ESP32-C6 DFR1075 v0.1 chips in --no-stub mode like below.
// In Arduino, check the "verbose mode" in Preferences, then click to compile/verify the sketch (not to upload). 
// When compile finishes, in the log output window you should be able to see where the ".merged.bin" file gets created. You should see something like this "Wrote 0x400000 bytes to file 'C:\Users\xxxx\AppData\Local\arduino\sketches\015DF83F5CBCD4594668734FD7CFEB0D/renegade-stick_v17.ino.merged.bin', ready to flash to offset 0x0."
// Mark the path above.
// In your command line, prepare the following command but don't run it. 
// python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub --before default-reset --after hard-reset write-flash  -z --flash-mode keep --flash-freq keep --flash-size keep 0x0 "C:\........yourpath.......\renegade-stick_xxxxx.ino.merged.bin"
// Enter the board into programming mode (as described above in entering programming mode for ESP32-C6 DFR1075) and then press enter.
// Don't forget to click RESET when upload finished.

