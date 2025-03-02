#include "button_event.h"
#include <Arduino.h>
#include "hal.h"

bool g_system_calibration = false;
static ButtonEvent btn_boot(5000);
static unsigned long pixelPrevious = 0;        // Previous Pixel Millis
#define LED_INTERVAL  500;       // Pixel Interval (ms)



void HAL::system_led_init(void)
{
    pinMode(CONFIG_SYSTEM_LED_PIN, OUTPUT);
}

void HAL::system_led_run(unsigned long currentMillis)
{
    static int val = 1;
    if (currentMillis - pixelPrevious >= 500) { 
        pixelPrevious = currentMillis;                       //  Run current frame
        digitalWrite(CONFIG_SYSTEM_LED_PIN, val);
        val = !val;
    }
}

int HAL::system_init(void)
{
    system_led_init();

    pinMode(SYSTEM_CALIBRATION_BUTTON_PIN, INPUT_PULLUP);
    if (digitalRead(SYSTEM_CALIBRATION_BUTTON_PIN) == LOW) {
        g_system_calibration = true;
    }
    log_i("start with calibration %s", g_system_calibration? "true": "false");
    return 0;
}
