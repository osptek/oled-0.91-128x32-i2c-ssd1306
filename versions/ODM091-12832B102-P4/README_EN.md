<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 0.91″ OLED 128×32 (SSD1306 · I2C)</h1>

<p align="center"><b>Monochrome OLED module · I2C · compact status display</b></p>

<p align="center"><a href="./README.md">简体中文</a> | English · <a href="../../README_EN.md">Family index</a></p>

<p align="center">
  <img alt="Size: 0.91 inch" src="https://img.shields.io/badge/Size-0.91%22-3498DB?style=flat-square" />
  <img alt="Resolution: 128x32" src="https://img.shields.io/badge/Resolution-128%C3%9732-8E44AD?style=flat-square" />
  <img alt="Interface: I2C" src="https://img.shields.io/badge/Interface-I2C-27AE60?style=flat-square" />
  <img alt="Driver: SSD1306" src="https://img.shields.io/badge/Driver-SSD1306-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 0.91&quot; OLED 128×32 module (SSD1306) product image" src="./images/product.png" width="640" /></p>

## Contents

- [Overview](#overview)
- [Specifications](#specifications)
- [Sample projects](#sample-projects)
- [Repository layout](#repository-layout)
- [Resources](#resources)
- [Buy](#buy)
- [Support](#support)

---

## Overview

OSPTEK **0.91″ 128×32 OLED** is a **monochrome I2C** display module driven by **SSD1306**. Small footprint and few wires make it a fit for status bars, menu hints, and debug text.

Spec ID (repository name): `0.91-oled-128x32-i2c-ssd1306`

Current module version: **ODM091-12832B102-P4**. Electrical and mechanical details follow [`docs/ODM091-12832B102-P4.pdf`](./docs/ODM091-12832B102-P4.pdf).

## Specifications

| Item | Spec |
| ---- | ---- |
| Size | 0.91 inch |
| Type | OLED (monochrome) |
| Resolution | 128×32 |
| Interface | I2C |
| Driver IC | SSD1306 |

> Full outline, pinout, power, and electrical limits follow the product datasheet / driver IC datasheet.

## Sample projects

| Description | Path |
| ---- | ---- |
| ESP32-S3 · SSD1306 I2C bringup (spectrum viz) | [`examples/esp32s3-0.91-oled-128x32-i2c-ssd1306-bringup/`](./examples/esp32s3-0.91-oled-128x32-i2c-ssd1306-bringup/) |

## Repository layout

```text
0.91-oled-128x32-i2c-ssd1306/  # repo root (nav: ../../README_EN.md)
└── versions/
    └── ODM091-12832B102-P4/   # full materials for this part number
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## Resources

### Product files

| Resource | Link |
| ---- | ---- |
| Product datasheet (ODM091-12832B102-P4) | [`docs/ODM091-12832B102-P4.pdf`](./docs/ODM091-12832B102-P4.pdf) |
| Driver IC datasheet (SSD1306) | [`docs/SSD_1306_1_5_e7033cb611.pdf`](./docs/SSD_1306_1_5_e7033cb611.pdf) |

### Samples

- [ESP32-S3 SSD1306 I2C bringup](./examples/esp32s3-0.91-oled-128x32-i2c-ssd1306-bringup/)

## Buy

<p align="center">
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="AliExpress store" src="https://img.shields.io/badge/AliExpress-Official_Store-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://shop110742373.taobao.com/"><img alt="Taobao store" src="https://img.shields.io/badge/Taobao-Official_Store-FF6A00?style=for-the-badge" /></a>
</p>

**Overseas (AliExpress)**

- Store: [OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

**China (Taobao)**

- Store: [鱼鹰光电工厂店](https://shop110742373.taobao.com/)

## Support

- Technical support / product inquiry: <luyu@osptek.com>
- QQ group (China): **985881096**
- Website: <https://osptek.com/>
- Feel free to open an Issue in this repository if you have any questions

---

<p align="center"><sub>© 2026 OSPTEK · Materials in this repository are licensed under CC BY 4.0</sub></p>
