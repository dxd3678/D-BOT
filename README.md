<h1 align="center">BOK: The Bot Of Knob</h1>
<div align="center">

</div>


# 一些工具

批量转换图片为 bin 格式工具： [W-Mai/lvgl_image_converter](https://github.com/W-Mai/lvgl_image_converter)

```bash
image_path="/d/Workspaces/Resources/KnobBot/Images/"
python lv_img_conv.py -f true_color_alpha -cf RGB565SWAP -ff BIN -o $image_path/out/ $image_path
```