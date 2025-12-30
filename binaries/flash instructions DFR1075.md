# Flashing Guide for ESP32‑C6 DFR1075 (v0.1 Chips)

Flashing ESP32‑C6 v0.1 chips isn’t as straightforward as with newer ESP boards.  
On the two v0.1 boards I tested, **automatic USB reset does not work**, so you must manually enter programming mode using the **BOOT** and **RESET** buttons.

Below is a clear step‑by‑step guide.

---

## Entering Manual Programming Mode

On ESP32‑C6 v0.1 chips, the automatic USB reset fails, so the chip cannot reliably enter or exit boot mode.  
No matter which flashing tool you use, you must manually enter programming mode first.

### If a battery *is connected*
- **[Connect USB](guide://action?prefill=Tell%20me%20more%20about%3A%20Connect%20USB)**
- **[Hold BOOT](guide://action?prefill=Tell%20me%20more%20about%3A%20Hold%20BOOT)**
- **[Press RESET briefly while still holding BOOT](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20briefly%20while%20still%20holding%20BOOT)**
- **[Keep holding BOOT for ~5 seconds](guide://action?prefill=Tell%20me%20more%20about%3A%20Keep%20holding%20BOOT%20for%20~5%20seconds)**
- **[Flash/upload using your tool](guide://action?prefill=Tell%20me%20more%20about%3A%20Flash%2Fupload%20using%20your%20tool)**
- **[Press RESET once when finished](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20once%20when%20finished)**

### If no battery is connected (Method 1)
- **[Connect USB](guide://action?prefill=Tell%20me%20more%20about%3A%20Connect%20USB)**
- **[Hold BOOT](guide://action?prefill=Tell%20me%20more%20about%3A%20Hold%20BOOT)**
- **[Press RESET briefly while still holding BOOT](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20briefly%20while%20still%20holding%20BOOT)**
- **[Keep holding BOOT for ~5 seconds](guide://action?prefill=Tell%20me%20more%20about%3A%20Keep%20holding%20BOOT%20for%20~5%20seconds)**
- **[Flash/upload](guide://action?prefill=Tell%20me%20more%20about%3A%20Flash%2Fupload)**
- **[Press RESET once when done](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20once%20when%20done)**

### If no battery is connected (Method 2)
- **[Hold BOOT](guide://action?prefill=Tell%20me%20more%20about%3A%20Hold%20BOOT)**
- **[Plug in USB while still holding BOOT](guide://action?prefill=Tell%20me%20more%20about%3A%20Plug%20in%20USB%20while%20still%20holding%20BOOT)**
- **[Keep holding BOOT for ~5 seconds](guide://action?prefill=Tell%20me%20more%20about%3A%20Keep%20holding%20BOOT%20for%20~5%20seconds)**
- **[Flash/upload](guide://action?prefill=Tell%20me%20more%20about%3A%20Flash%2Fupload)**
- **[Press RESET once when done](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20once%20when%20done)**

---

## Getting the Flash File

You can either:
- **[Download a precompiled `.bin` file from the renegade‑stick GitHub repo](guide://action?prefill=Tell%20me%20more%20about%3A%20Download%20a%20precompiled%20%60.bin%60%20file%20from%20the%20renegade%E2%80%91stick%20GitHub%20repo)**  
- **[Compile it yourself using the Arduino IDE](guide://action?prefill=Tell%20me%20more%20about%3A%20Compile%20it%20yourself%20using%20the%20Arduino%20IDE)**

Arduino can also flash the board automatically after compiling.

### Finding the correct COM port (Windows)
- **[Connect the board via USB‑C](guide://action?prefill=Tell%20me%20more%20about%3A%20Connect%20the%20board%20via%20USB%E2%80%91C)**
- **[Open Device Manager → “Ports (COM & LPT)”](guide://action?prefill=Tell%20me%20more%20about%3A%20Open%20Device%20Manager%20%E2%86%92%20%E2%80%9CPorts%20(COM%20%26%20LPT)%E2%80%9D)**
- **[Look for “USB Serial Device (COM X)”](guide://action?prefill=Tell%20me%20more%20about%3A%20Look%20for%20%E2%80%9CUSB%20Serial%20Device%20(COM%20X)%E2%80%9D)**
- **[Unplug/replug USB if unsure which entry is the board](guide://action?prefill=Tell%20me%20more%20about%3A%20Unplug%2Freplug%20USB%20if%20unsure%20which%20entry%20is%20the%20board)**

---

## Flashing with `flash_download_tool`

- **[Download the correct `.bin` file](guide://action?prefill=Tell%20me%20more%20about%3A%20Download%20the%20correct%20%60.bin%60%20file)**
- **[Download the official ESP32 flasher](guide://action?prefill=Tell%20me%20more%20about%3A%20Download%20the%20official%20ESP32%20flasher)**  
  https://docs.espressif.com/projects/esp-test-tools/en/latest/esp32/production_stage/tools/flash_download_tool.html

Unfortunately, ESP32‑C6 v0.1 chips require `--no-stub` mode, which this tool does not support.  
Use one of the methods below instead.

---

## Flashing with Python `esptool`

### Install Python & esptool (Windows)
- **[Install Python from Microsoft Store](guide://action?prefill=Tell%20me%20more%20about%3A%20Install%20Python%20from%20Microsoft%20Store)**
- **[Open Command Prompt](guide://action?prefill=Tell%20me%20more%20about%3A%20Open%20Command%20Prompt)**
- **[Install esptool: `pip install esptool`](guide://action?prefill=Tell%20me%20more%20about%3A%20Install%20esptool%3A%20%60pip%20install%20esptool%60)**

### Flashing command (prepare but don’t run yet)

```bash
python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub \
  --before default-reset --after hard-reset write-flash -z \
  --flash-mode keep --flash-freq keep --flash-size keep \
  0x0 "C:\path\to\renegade-stick_DFR1075_vXX.bin"
```

### Flashing steps
- **[Enter programming mode](guide://action?prefill=Tell%20me%20more%20about%3A%20Enter%20programming%20mode)**
- **[Run the command](guide://action?prefill=Tell%20me%20more%20about%3A%20Run%20the%20command)**
- **[Press RESET when flashing finishes](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20when%20flashing%20finishes)**

---

## Compile & Flash Using Arduino IDE

Follow the DFRobot wiki to install ESP32‑C6 support.

### Arduino Tools → Options
- **[Board: esp32 → DFRobot FireBeetle 2 ESP32‑C6](guide://action?prefill=Tell%20me%20more%20about%3A%20Board%3A%20esp32%20%E2%86%92%20DFRobot%20FireBeetle%202%20ESP32%E2%80%91C6)**
- **[Port: select your COM port](guide://action?prefill=Tell%20me%20more%20about%3A%20Port%3A%20select%20your%20COM%20port)**
- **[USB CDC On Boot: Disabled](guide://action?prefill=Tell%20me%20more%20about%3A%20USB%20CDC%20On%20Boot%3A%20Disabled)**
- **[Erase Flash Before Upload: Disabled](guide://action?prefill=Tell%20me%20more%20about%3A%20Erase%20Flash%20Before%20Upload%3A%20Disabled)**
- **[Flash Frequency: 40 MHz](guide://action?prefill=Tell%20me%20more%20about%3A%20Flash%20Frequency%3A%2040%20MHz)**
- **[Flash Mode: DIO](guide://action?prefill=Tell%20me%20more%20about%3A%20Flash%20Mode%3A%20DIO)**
- **[Flash Size: 4 MB](guide://action?prefill=Tell%20me%20more%20about%3A%20Flash%20Size%3A%204%20MB)**
- **[JTAG Adapter: Disabled](guide://action?prefill=Tell%20me%20more%20about%3A%20JTAG%20Adapter%3A%20Disabled)**
- **[Partition Scheme: Default 4MB with spiffs](guide://action?prefill=Tell%20me%20more%20about%3A%20Partition%20Scheme%3A%20Default%204MB%20with%20spiffs)**
- **[Upload Speed: 115200](guide://action?prefill=Tell%20me%20more%20about%3A%20Upload%20Speed%3A%20115200)**
- **[Zigbee Mode: Disabled](guide://action?prefill=Tell%20me%20more%20about%3A%20Zigbee%20Mode%3A%20Disabled)**
- **[Programmer: esptool](guide://action?prefill=Tell%20me%20more%20about%3A%20Programmer%3A%20esptool)**

### Important: Disable stub mode for v0.1 chips
Arduino uses stub mode by default, which **does not work** on ESP32‑C6 v0.1.

To fix:
1. **[Close Arduino](guide://action?prefill=Tell%20me%20more%20about%3A%20Close%20Arduino)**
2. **[Edit this file](guide://action?prefill=Tell%20me%20more%20about%3A%20Edit%20this%20file)**  
   `C:\Users\xxxx\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.5\platform.txt`
3. **[Find: `tools.esptool_py.upload.pattern_args=`](guide://action?prefill=Tell%20me%20more%20about%3A%20Find%3A%20%60tools.esptool_py.upload.pattern_args%3D%60)**
4. **[Add `--no-stub` before `--port`](guide://action?prefill=Tell%20me%20more%20about%3A%20Add%20%60--no-stub%60%20before%20%60--port%60)**

Then:
- **[Restart Arduino](guide://action?prefill=Tell%20me%20more%20about%3A%20Restart%20Arduino)**
- **[Select correct settings](guide://action?prefill=Tell%20me%20more%20about%3A%20Select%20correct%20settings)**
- **[Enter programming mode](guide://action?prefill=Tell%20me%20more%20about%3A%20Enter%20programming%20mode)**
- **[Click Upload](guide://action?prefill=Tell%20me%20more%20about%3A%20Click%20Upload)**
- **[Press RESET when done](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20when%20done)**

---

## Compile in Arduino but Flash with Python `esptool`

If you want Arduino to generate the `.merged.bin` but prefer flashing with esptool:

1. **[Enable “verbose mode” in Arduino Preferences](guide://action?prefill=Tell%20me%20more%20about%3A%20Enable%20%E2%80%9Cverbose%20mode%E2%80%9D%20in%20Arduino%20Preferences)**
2. **[Click Verify/Compile (not Upload)](guide://action?prefill=Tell%20me%20more%20about%3A%20Click%20Verify%2FCompile%20(not%20Upload))**
3. **[Find the `.merged.bin` path in the output log](guide://action?prefill=Tell%20me%20more%20about%3A%20Find%20the%20%60.merged.bin%60%20path%20in%20the%20output%20log)**  
   Example:  
   `Wrote 0x400000 bytes to file 'C:\Users\xxxx\AppData\Local\arduino\sketches\...\renegade-stick_v17.ino.merged.bin'`

4. **[Prepare the esptool command](guide://action?prefill=Tell%20me%20more%20about%3A%20Prepare%20the%20esptool%20command)**

```bash
python -m esptool --chip esp32c6 --port COM5 --baud 115200 --no-stub \
  --before default-reset --after hard-reset write-flash -z \
  --flash-mode keep --flash-freq keep --flash-size keep \
  0x0 "C:\path\to\renegade-stick_xxxxx.ino.merged.bin"
```

5. **[Enter programming mode](guide://action?prefill=Tell%20me%20more%20about%3A%20Enter%20programming%20mode)**
6. **[Run the command](guide://action?prefill=Tell%20me%20more%20about%3A%20Run%20the%20command)**
7. **[Press RESET when flashing is done](guide://action?prefill=Tell%20me%20more%20about%3A%20Press%20RESET%20when%20flashing%20is%20done)** 

Just tell me which direction you want to take.
