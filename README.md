<h1 align="center">BOK: The Bot Of Knob</h1>
<div align="center">

</div>


# 一些工具

批量转换图片为 bin 格式工具： [W-Mai/lvgl_image_converter](https://github.com/W-Mai/lvgl_image_converter)

```bash
image_path="/d/Workspaces/Resources/KnobBot/Images/"
python lv_img_conv.py -f true_color_alpha -cf RGB565SWAP -ff BIN -o $image_path/out/ $image_path

# 快速重命名
counter=1; for file in wink*; do new_name=$(printf "wink%04d.bin" $counter); mv $file $new_name; ((counter++)); done
```

esp32 debug

```bash
export PATH=$PATH:~/.platformio/packages/toolchain-xtensa-esp32s3/bin
xtensa-esp32s3-elf-addr2line.exe -pfiaC -e .pio/build/esp32-s3-devkitc-1/firmware.elf 0x42007e97
```

# 一些常见的问题

Stack canary watchpoint triggered 通常是因为 FreeRTOS 的 task 栈设置得太小，适当增大 stack depth 即可解决。

- [Why do I get the Debug exception reason: Stack canary watchpoint triggered (main)?](https://stackoverflow.com/questions/56779459/why-do-i-get-the-debug-exception-reason-stack-canary-watchpoint-triggered-main)

```
Guru Meditation Error: Core  1 panic'ed (Unhandled debug exception). 
Debug exception reason: Stack canary watchpoint triggered (BuzzerThread)
```

# 致谢开源

-[Balance_Bot_DengFOC](https://github.com/ToanTech/Balance_Bot_DengFOC)