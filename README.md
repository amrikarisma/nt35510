# MRB3971 — NT35510 800×480 LCD Driver for ESP32/ESP32-S3

8-bit parallel (8080) driver for NT35510-based 800×480 displays on ESP32 and ESP32-S3.
Based on [hi631/LCD_NT35510-MRB3971](https://github.com/hi631/LCD_NT35510-MRB3971), adapted for ESP32-S3 with `REG_WRITE/REG_READ` GPIO access.

## Wiring

| Signal | Description         |
|--------|---------------------|
| CS     | Chip select         |
| RS/DC  | Register / Data     |
| RD     | Read strobe         |
| WR     | Write strobe        |
| RST    | Reset (active low)  |
| BL     | Backlight           |
| D0–D7  | 8-bit data bus      |

## Usage

```cpp
#include "MRB3971.h"

static const uint8_t dataPins[8] = {10, 11, 12, 13, 14, 15, 16, 17};

MRB3971 lcd(
    /*cs*/  4,
    /*rs*/  5,
    /*rd*/  6,
    /*wr*/  7,
    /*rst*/ 8,
    dataPins,
    /*bus_width*/ 8,
    /*bl*/ 9
);

void setup() {
    lcd.Init();
    lcd.Clear(0, BLACK);
}
```

## Key Methods

| Method | Description |
|--------|-------------|
| `Init()` | Initialize display |
| `Clear(dir, color)` | Fill screen with color |
| `SetWindow(x1, y1, x2, y2)` | Set draw region |
| `FlushBuffer(buf, len)` | Bulk RGB565 write (for LVGL / sprite flush) |
| `FillPixels(color, count)` | Fill N pixels efficiently |
| `ledon()` / `ledoff()` | Backlight control |

## Compatibility

- ESP32 (classic) — GPIO bank 0 & 1
- ESP32-S3 — GPIO bank 0 & 1
- **Not compatible with ESP32-C3** (only has GPIO 0–21, no bank 1)

## PlatformIO

```ini
lib_deps =
    https://github.com/amrikarisma/nt35510.git
```
