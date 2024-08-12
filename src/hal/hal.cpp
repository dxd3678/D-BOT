
#include "hal.h"
#include "lvgl.h"
#include "sd_card.h"

#define DISP_BUF_SIZE        CONFIG_SCREEN_BUFFER_SIZE

extern lv_color_t* disp_draw_buf;
SdCard tf;

void HAL::Init()
{
    Serial.begin(115200);

    Serial.printf("Deafult free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_DEFAULT));
    Serial.printf("PSRAM free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM));
    Serial.printf("Flash size: %d bytes\n", ESP.getFlashChipSize());

    // Move the malloc process to Init() to make sure that the largest heap can be used for this buffer.
    disp_draw_buf = static_cast<lv_color_t*>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (disp_draw_buf == nullptr)
        Serial.printf("lv_port_disp_init malloc failed!\n");
    // power_init();
    motor_init();
    system_led_init();
    buzz_init();
    buzz_tone(700, 30);
    tf.init();
    String test_content = tf.readFileLine("/dingmos_test.txt", 1);        // line-1 for WiFi ssid
    log_i("read test file: %s", test_content.c_str());

    log_i("init mpu...");
    imu_init();
    // knob_init();
    // super_dial_init();
}


void HAL::Update()
{
    unsigned long currentMillis = millis();
    // __IntervalExecute(HAL::knob_update(), 10);

    system_led_run(currentMillis);
    imu_update();
    // HAL::TaskMotorUpdate(NULL);
}
