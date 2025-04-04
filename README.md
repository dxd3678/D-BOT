<h1 align="center">D-BOT: 一个可 AI 控制的无刷平衡车——X-Knob 智能旋钮的变换形态</h1>
<div align="center">

<i>喜欢这个项目吗？请考虑给 Star ⭐️ 以帮助改进！</i>

</div>

D-BOT 是一个桌面机器人（Desktop Bot），可通过 AI 精确控制，同时具备 [X-Knob](https://github.com/SmallPond/X-Knob) 的全功能。我同时更想称 D-BOT 为小探索家（Discovery Bot），它能探索这个世界，同时也是我对我自己的一次探索：第一次完整尝试 3D 建模和 PCB 设计。

D-BOT 支持的特性：
- [x] [X-Knob](https://github.com/SmallPond/X-Knob) 原生全功能支持;
- [x] 手柄遥控控制（蓝牙）;
- [x] 无线调参数：
  - [x] 基于 [SimpleFOCStudio](https://github.com/SmallPond/SimpleFOCStudio) （尝试合入到 upstream 中，但作者太忙一直没时间 review，暂时使用我 fork 的仓库）修改了上位机，通过无线网络连接;
  - [x] 在 D-BOT 端通过 [WirelessTuning](https://github.com/SmallPond/WirelessTuning) 库，作为胶水层无缝适配 SimpleFOC 的 monitor 库；
- [x] 小智 AI 控制，化身 AI 机器人（狗头；


![](https://pic-mos-1255408269.cos.ap-guangzhou.myqcloud.com/D-BOT-1.jpg)

### 演示视频

- [【开源】我做了一个不一样的桌面机器人](https://www.bilibili.com/video/BV15FXpYoEGG/)

### 硬件

主要硬件列表：
- 4 块 PCB：主控板 + 驱动板 \* 2 + 屏幕板；
- 电池板: 直接使用饭佬开源平衡车的电池板，**但不用焊接任何元件**；
- MCU: ESP32-S3 WROOM-1U-N16R8；
- 屏幕: 240x240 圆形 LCD GC9A01 (1.28 寸)
- 磁编码器：MT6701CT；
- 3205a 无刷直流电机（无限位）；

已经上传到嘉立创开源平台：[硬件开源链接](https://oshwhub.com/dingmos/kbc)

### 3D 结构

3D 结构的打印件已经上传到 Maker World ： [D-BOT 3D 模型](https://makerworld.com.cn/zh/models/1061527-d-bot-ge-ke-ai-kong-zhi-de-wu-shua-ping-heng-che-x#profileId-1100492)，总共包含 5 个打印件：

- 车架-3205a_v1.1
- 车轮适配件_v0.2
- 电池卡扣+底座接口_v0.9
- 屏幕架_v0.4
- 支撑件_v0.1

## Getting Started

基本环境：
- VScode + PlatformIO

1. 下载代码

```
git clone https://github.com/SmallPond/D-BOT  
```

2. 编译 && flash 

3. 首次启动

- 配置 WiFi，连接 **DBOT_xxx** 的 WiFi，访问 192.168.4.1 进入网页配置并保存，D-BOT 将会自动重启
- 启动后会自动进行陀螺仪（MPU6050）自动校准和电机自动校准（左右电机依次顺逆时针转动）；如果你在完全固定组装前启动过，电机将可能不会再校准导致电机工作不正常；
  - **强制校准方法**：在启动听到“叮”一声后，立马按住 boot 键（主控板最外侧的按键）2 秒不动，等待一会应该能看到电机开始校准；或者**直接 0 地址重刷 merge 固件，这将清除所有配置**。
- 因为 mpu6050 不是直接板载在主控板的，焊接的差异可能导致平衡（机械）中值有差异，可以通过无线调参修改，有能力的同学也可以直接修改代码后重新编译；

4. enjoy 

## AI 控制

D-BOT 的 AI 控制代码开源在 [xiaozhi-esp32](https://github.com/SmallPond/xiaozhi-esp32) 仓库，当前仅优先支持 [45coll-sparkbot](https://gitee.com/coll45/sparkbot-45coll) 开发板。

如果你有其他版本的小智，可以在 [xiaozhi-esp32](https://github.com/SmallPond/xiaozhi-esp32) 的 issue 里提交申请，详细描述板子型号。我统一支持后发 release 固件。当然有能力的同学也可以参考我的修改自行增加其他开发板的支持。

## 无线调参

1. 配置 [SimpleFOCStudio](https://github.com/SmallPond/SimpleFOCStudio)基本环境 ；
2. 通过串口获取 D-BOT 启动日志打印的 IP 地址；
3. 在 SimpleFOCStudio 界面中配置 IP 和端口号（默认为 4242），连接成功后，在 Command Line interface 处输入以下指令调参；

| 对象 | 命令 | 示例 |
| :-----| ----: | :----: |
| 直立环 | S | SP0.2——直立环 P 项设置为 0.2， SP不带参数则为获取当前 P 项 |
| 速度环 | V | VP0.2——速度环 P 项设置为 0.2 |
| 转向环 | T | TP0.2——转向环 P 项设置为 0.2 |
| D-BOT 前后移动闭环控制 | R | RP0.2|
| D-BOT 转向闭环控制 | B | BP0.2|
| 机械中值 | X | X-3——机械中值设置为 -3（默认值为 -2，正常直立时 D-BOT 向前走，应该减小该值） |
|保存所有参数|C|C|

## 致谢开源

- [Super_Balance](https://gitee.com/handmade-rice/Super_Balance): 手工饭开源平衡车；本项目的结构和小车平衡控制主要参考此项目

### 相关项目

- [sparkbot-45coll](https://gitee.com/coll45/sparkbot-45coll)
- [SimpleFOCStudio](https://github.com/JorgeMaker/SimpleFOCStudio)
- [xiaozhi-esp32](https://github.com/78/xiaozhi-esp32)
  

## 其他

### 开发过程的一些问题记录

1. Stack canary watchpoint triggered 通常是因为 FreeRTOS 的 task 栈设置得太小，适当增大 stack depth 即可解决。

- [Why do I get the Debug exception reason: Stack canary watchpoint triggered (main)?](https://stackoverflow.com/questions/56779459/why-do-i-get-the-debug-exception-reason-stack-canary-watchpoint-triggered-main)

```
Guru Meditation Error: Core  1 panic'ed (Unhandled debug exception). 
Debug exception reason: Stack canary watchpoint triggered (BuzzerThread)
```

2. esp32 debug，打印出错的栈信息

```bash
export PATH=$PATH:~/.platformio/packages/toolchain-xtensa-esp32s3/bin
xtensa-esp32s3-elf-addr2line.exe -pfiaC -e .pio/build/esp32-s3-devkitc-1/firmware.elf 0x42007e97
```

3. MPU6050 Z 轴（YAW）零漂问题，最好每次都进行陀螺仪的静止校准`mpu.calcGyroOffsets(true);`，不然在控制指定角度转动时会不准（yaw 角会不断上涨/下降）；
  
### 一些工具

1. [在线钢琴模拟器](https://www.xiwnn.com/piano/)