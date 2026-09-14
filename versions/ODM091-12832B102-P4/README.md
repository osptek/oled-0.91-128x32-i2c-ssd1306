<p align="left"><img alt="OSPTEK" src="./images/logo.png" width="200" /></p>

<h1 align="center">OSPTEK 0.91″ OLED 128×32（SSD1306 · I2C）</h1>

<p align="center"><b>单色 OLED 模组 · I2C · 小尺寸状态显示</b></p>

<p align="center"><a href="./README_EN.md">English</a> | 简体中文 · <a href="../../README.md">规格族索引</a></p>

<p align="center">
  <img alt="Size: 0.91 inch" src="https://img.shields.io/badge/Size-0.91%22-3498DB?style=flat-square" />
  <img alt="Resolution: 128x32" src="https://img.shields.io/badge/Resolution-128%C3%9732-8E44AD?style=flat-square" />
  <img alt="Interface: I2C" src="https://img.shields.io/badge/Interface-I2C-27AE60?style=flat-square" />
  <img alt="Driver: SSD1306" src="https://img.shields.io/badge/Driver-SSD1306-E7352C?style=flat-square" />
</p>

<p align="center"><img alt="OSPTEK 0.91 寸 OLED 128×32 模组（SSD1306）产品图" src="./images/product.png" width="640" /></p>

## 目录

- [产品简介](#产品简介)
- [规格参数](#规格参数)
- [示例工程](#示例工程)
- [仓库结构](#仓库结构)
- [相关资料](#相关资料)
- [购买链接](#购买链接)
- [技术支持](#技术支持)

---

## 产品简介

OSPTEK **0.91 寸 128×32 OLED** 是一款 **I2C** 单色显示模组，驱动芯片为 **SSD1306**。体积小、接线少，适合状态栏、菜单提示、调试信息等低信息密度显示场景。

规格标识（仓库名）：`oled-0.91-128x32-i2c-ssd1306`

当前模组版本：**ODM091-12832B102-P4**。电气与外形细节以 [`docs/ODM091-12832B102-P4.pdf`](./docs/ODM091-12832B102-P4.pdf) 为准。

## 规格参数

| 项目 | 规格 |
| ---- | ---- |
| 尺寸 | 0.91 英寸 |
| 类型 | OLED（单色） |
| 分辨率 | 128×32 |
| 接口 | I2C |
| 驱动 IC | SSD1306 |

> 完整外形尺寸、引脚定义、供电与电气特性以产品规格书 / 驱动手册为准。

## 示例工程

| 说明 | 路径 |
| ---- | ---- |
| ESP32-S3 · SSD1306 I2C bringup（频谱可视化） | [`examples/esp32s3-oled-0.91-128x32-i2c-ssd1306-bringup/`](./examples/esp32s3-oled-0.91-128x32-i2c-ssd1306-bringup/) |

## 仓库结构

```text
oled-0.91-128x32-i2c-ssd1306/  # 仓库根（导航见 ../../README.md）
└── versions/
    └── ODM091-12832B102-P4/   # 本料号完整资料
        ├── README.md
        ├── README_EN.md
        ├── images/
        ├── docs/
        └── examples/
```

## 相关资料

### 本产品资料

| 资料 | 链接 |
| ---- | ---- |
| 产品规格书（ODM091-12832B102-P4） | [`docs/ODM091-12832B102-P4.pdf`](./docs/ODM091-12832B102-P4.pdf) |
| 驱动 IC 数据手册（SSD1306） | [`docs/SSD_1306_1_5_e7033cb611.pdf`](./docs/SSD_1306_1_5_e7033cb611.pdf) |

### 示例工程

- [ESP32-S3 SSD1306 I2C bringup](./examples/esp32s3-oled-0.91-128x32-i2c-ssd1306-bringup/)

## 购买链接

<p align="center">
  <a href="https://shop110742373.taobao.com/"><img alt="淘宝官方店铺" src="https://img.shields.io/badge/淘宝-官方店铺-FF6A00?style=for-the-badge" /></a>
  &nbsp;&nbsp;
  <a href="https://www.aliexpress.com/store/1105701619"><img alt="速卖通官方店铺" src="https://img.shields.io/badge/速卖通-官方店铺-E62E04?style=for-the-badge&logo=aliexpress&logoColor=white" /></a>
</p>

**国内（淘宝）**

- 店铺：[鱼鹰光电工厂店](https://shop110742373.taobao.com/)

**海外（AliExpress）**

- 店铺：[OSPTEK Official Store](https://www.aliexpress.com/store/1105701619)

## 技术支持

- 技术支持 / 产品咨询：<luyu@osptek.com>
- QQ 技术交流群：**985881096**
- 公司官网：<https://osptek.com/>
- 有任何问题，都可以在本仓库 Issues 中提问

---

<p align="center"><sub>© 2026 OSPTEK 鱼鹰光电 · 本仓库资料采用 CC BY 4.0 许可</sub></p>
