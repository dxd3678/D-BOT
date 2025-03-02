<h1 align="center">D-Bot: Discovery Rebot</h1>
<div align="center">

</div>


# 无线调参

| 对象 | 命令 | 示例 |
| :-----| ----: | :----: |
| 直立环 | S | SP0.2——直立环 P 项设置为 0.2 |
| 速度环 | V | VP0.2——速度环 P 项设置为 0.2 |
| 转向环 | T | TP0.2——转向环 P 项设置为 0.2 |
| Bot 前后移动闭环控制 | R | RP0.2|
| Bot 转向闭环控制 | B | BP0.2|
| 机械中值 | X | X-3——机械中值设置为 -3 |

## 命令实例

```c
// 调参， 直立环
SP0.2
// 调参， 速度环
VP1
// imu offset
X2

// 开启 Verb
@
```

# 开发过程的一些问题记录

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

# 致谢开源

- [Super_Balance](https://gitee.com/handmade-rice/Super_Balance): 手工饭开源平衡车；本项目的结构和小车平衡控制主要参考此项目



# 一些工具

1. 批量转换图片为 bin 格式工具： [W-Mai/lvgl_image_converter](https://github.com/W-Mai/lvgl_image_converter)

```bash
image_path="/d/Workspaces/Resources/DBot/Images/"
python lv_img_conv.py -f true_color_alpha -cf RGB565SWAP -ff BIN -o $image_path/out/ $image_path

# 快速重命名
counter=1; for file in wink*; do new_name=$(printf "wink%04d.bin" $counter); mv $file $new_name; ((counter++)); done
```

2. [在线钢琴模拟器](https://www.xiwnn.com/piano/)