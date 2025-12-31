# Flashing Guide – Renegade Stick

This document describes how to flash the Renegade Stick firmware onto supported FireBeetle 2 ESP32 boards.

## Supported Boards

* **FireBeetle 2 ESP32-E (N16R2)** – DFR1139
* **FireBeetle 2 ESP32-S3 (N4)** – DFR1145
* **FireBeetle 2 ESP32-C6** – DFR1075 (⚠️ v0.1 chip revision notes apply)

---

## Prerequisites

* USB-C cable
* Windows, macOS, or Linux PC
* One of the following:

  * Arduino IDE
  * Python + `esptool`
  * Espressif Flash Download Tool (not supported on all of the boards)

### Identifying the COM Port (Windows)

1. Connect the board via USB.
2. Open **Device Manager** → **Ports (COM & LPT)**.
3. Look for:

   * `USB-SERIAL CH340K` (ESP32-E)
   * `USB Serial Device (COM X)` (ESP32-S3 / ESP32-C6)
4. Note the COM number.
5. If unsure, unplug the board and see which entry disappears.

---

## Flash Files

You may either:

* Download a **precompiled `.bin` file** from the Renegade Stick GitHub repository
* Compile the firmware yourself using **Arduino IDE**

Arduino can also flash the board automatically after compilation.

---

## ESP32-E (DFR1139) Flashing Notes

* Automatic reset **does not work reliably**
* Programming mode **must be entered manually**
* If altering the code or GPIO ports, not down not to use the following : 34, 35, 36, 39 (no pull-ups) and GPIO 2 should not be used

### Entering Manual Programming Mode (ESP32-E)

**With or without battery connected:**

1. Connect USB.
2. Start flashing/uploading from your tool.
3. When you see `Connecting...........`
4. Press and hold **RESET** for ~1 second.
5. If it times out, try again. (try double clicking on RESET)
6. When flashing completes, press **RESET** once.

---

## ESP32-S3 (DFR1145) Flashing Notes

* Programming mode is **automatic**
* Manual mode is rarely needed

### Optional Manual Programming Mode (ESP32-S3)

If required:

1. Hold **BOOT**.
2. Press **RESET** briefly.
3. Keep holding **BOOT** for ~5 seconds.
4. Release BOOT and flash.
5. Press **RESET** once when finished.

---

## ESP32-C6 (DFR1075) ⚠️ IMPORTANT

> **ESP32-C6 v0.1 chips require manual programming mode and must be flashed using `--no-stub`.** option
> Automatic USB reset does **not** work correctly on this revision.

### Entering Manual Programming Mode (ESP32-C6)

**With battery connected or not (recommended method):**

1. Connect USB.
2. Hold **BOOT**.
3. Quickly press **RESET** while holding BOOT.
4. Keep holding **BOOT** for ~5 seconds.
5. Start flashing.
6. When done, press **RESET** once.

**Alternative (no battery):**

1. Hold **BOOT**.
2. Plug in USB while holding BOOT.
3. Keep holding for ~5 seconds.
4. Flash and press RESET when finished.

---

## Flashing Methods

### Method 1 – Arduino IDE (Recommended)

#### Arduino Setup (ESP32-C6 Example)

```
Board: esp32 → DFRobot FireBeetle 2 ESP32-C6
Port: Your COM port
USB CDC On Boot: Disabled
Erase All Flash Before Upload: Disabled
Flash Frequency: 40 MHz (Recommended)
Flash Mode: DIO (Recommended)
Flash Size: 4 MB
Partition Scheme: Default 4MB with spiffs
Upload Speed: 115200
Programmer: esptool
```

#### ESP32-C6 v0.1 Arduino Fix (Required)

Arduino enables **stub mode by default**, which does **not work** on ESP32-C6 v0.1.

1. Close Arduino IDE.
2. Edit:

```
C:\Users\xxxx\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.5\platform.txt
```

3. Find:

```
tools.esptool_py.upload.pattern_args=
```

4. Add `--no-stub` **after** `--port`
5. Save file and restart Arduino.

Now:

1. Open the sketch.
2. Select correct board and COM port.
3. Manually enter programming mode.
4. Click **Upload**.
5. Press **RESET** once flashing finishes.

---

### Method 2 – Python `esptool`

#### Install esptool

```bash
pip install esptool
```

#### Example Command (ESP32-C6)  
* change to your COM port
* change --chip to one of (esp32, esp32s3, esp32c6)

```bash
python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub \
--before default-reset --after hard-reset write-flash -z \
--flash-mode keep --flash-freq keep --flash-size keep \
0x0 "C:\path\to\renegade-stick_DFR1075_vXX.bin"
```

Steps:

1. Prepare the command (don’t run yet).
2. Enter manual programming mode.
3. Press **Enter** to run command.
4. When finished, press **RESET** once.

---

### Method 3 – Compile in Arduino but Flash with esptool

1. In Arduino **Preferences**, enable **Verbose output**.
2. Click **Verify** (not Upload).
3. Find the `.merged.bin` path in the output, e.g.:

```
...renegade-stick_v17.ino.merged.bin
```

4. Flash using :
* change to your COM port
* change --chip to one of (esp32, esp32s3, esp32c6)

```bash
python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub \
--before default-reset --after hard-reset write-flash -z \
--flash-mode keep --flash-freq keep --flash-size keep \
0x0 "C:\path\to\renegade-stick_xxxxx.ino.merged.bin"
```

5. Press **RESET** when done.

---

## Flash Download Tool (Espressif)

* ❌ **Not supported** on ESP32-C6 v0.1 (requires stub mode) - Haven't found a way to enable it
* ❌ Not reliable on ESP32-S3 DFR1145 - Didn't manage to get it to flash
* ✅ May work on ESP32-E

Use Arduino or `esptool` instead.

---

## Final Notes

* Always press **RESET** once flashing completes
* If flashing fails, retry manual programming mode
* ESP32-C6 v0.1 behavior may improve with newer silicon revisions - so I have read
