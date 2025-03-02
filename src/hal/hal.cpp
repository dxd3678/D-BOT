
#include "hal.h"
#include "lvgl.h"
#include "sd_card.h"

#define DISP_BUF_SIZE        CONFIG_SCREEN_BUFFER_SIZE

extern lv_color_t* disp_draw_buf;
SdCard tf;

void HAL::Init()
{
    Serial.begin(115200);

    // Move the malloc process to Init() to make sure that the largest heap can be used for this buffer.
    disp_draw_buf = static_cast<lv_color_t*>(malloc(DISP_BUF_SIZE * sizeof(lv_color_t)));
    if (disp_draw_buf == nullptr)
        Serial.printf("lv_port_disp_init malloc failed!\n");
    // power_init();
    buzz_init();
    buzz_tone(700, 30);
    delay(2000);
    log_i("init system...");
    system_init();
    log_i("init mpu...");
    imu_init();
    log_i("init motor...");
    motor_init();
    
    
    tf.init();
    String test_content = tf.readFileLine("/dingmos_test.txt", 1);        // line-1 for WiFi ssid
    log_i("read test file: %s", test_content.c_str());

    // knob_init();
    // super_dial_init();
}


void HAL::Update()
{
    unsigned long currentMillis = millis();
    // __IntervalExecute(HAL::knob_update(), 10);

    system_led_run(currentMillis);
    // imu_update();
    // HAL::TaskMotorUpdate(NULL);
}
