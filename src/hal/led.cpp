#include "hal.h"


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