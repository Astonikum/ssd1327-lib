# MadGrayOLED

`mad::SSD1327` connects MadDisplay to Adafruit SSD1327 1.0.4. It stores 4-bit
pixels and preserves **16 grayscale levels**, using integer luminance conversion.
Both I2C and SPI work through the corresponding Adafruit_SSD1327 constructor.

```cpp
Adafruit_SSD1327 driver(128,128,&Wire,-1);
mad::SSD1327 panel(driver);
mad::Display<mad::SSD1327> display(panel);
// setup: display.begin(0x3d); then register/open MadDisplay pages.
```

The 128x128 frame consumes 8 KiB plus the vendor's 8 KiB native buffer. This is
not suitable for Uno/Mega RAM. Use `examples/gray_ui/gray_ui.ino` and `pio run`
for ESP32. SPI can instead use `Adafruit_SSD1327(128,128,&SPI,dc,rst,cs)`;
its default frequency is 8 MHz. Display-profile IDs are `ssd1327-128x128` and
`ssd1327-128x128-spi`. Dimensions are validated at begin. Presentation redraws
the native buffer and flushes through the vendor library.

Upstream: https://github.com/adafruit/Adafruit_SSD1327

## Installation

Repository: https://github.com/Astonikum/ssd1327-lib

PlatformIO (`platformio.ini`):

```ini
lib_deps =
  https://github.com/Astonikum/ssd1327-lib.git#v0.2.1
```

PlatformIO resolves the core, adapter support and vendor dependencies automatically.

Arduino IDE: download **Code → Download ZIP**, then use **Sketch → Include Library → Add .ZIP Library**.
Install these GitHub ZIP libraries first:

- [MadDisplay](https://github.com/Astonikum/display-lib)
- [MadDisplayAdapters](https://github.com/Astonikum/adapter-common-lib)

Install from Arduino Library Manager: Adafruit SSD1327, Adafruit GFX Library, Adafruit BusIO.

These packages are distributed through GitHub; they are not yet indexed in the Arduino or PlatformIO registries. Arduino IDE does not install a library directly from a Git URL.

Requires C++14 on the host. Embedded examples select their board and its Arduino toolchain in `platformio.ini`. RAM requirements are documented above; a matching controller does not guarantee a board has enough memory.
