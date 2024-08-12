#ifndef __HAL_H__
#define __HAL_H__
#include "button_event.h"
#include "HAL_Def.h"
#include <Arduino.h>
#include "config.h"
#include "CommonMacro.h"

typedef enum {
    SUPER_DIAL_NULL = 0,
    SUPER_DIAL_LEFT = 1,
    SUPER_DIAL_RIGHT= 2,
} SuperDialMotion;

typedef enum {
    HASS_LEFT = 1,
    HASS_RIGHT= 2,
    HASS_PUSH = 3,
    HASS_MAX,
} HassMotion;

namespace HAL
{
    void Init();
    void Update();

    void knob_init();
    void knob_update(void);
    bool encoder_is_pushed(void);

    void motor_init(void);
    // void TaskMotorUpdate(void *pvParameters);
    int get_motor_position(void);
    void update_motor_mode(int id, int mode , int init_position);
    void motor_shake(int id, int strength, int delay_time);

    void surface_dial_init(void);
    void surface_dial_update(SuperDialMotion direction);
    void surface_dial_release(void);
    void surface_dial_press(void);
    bool surface_dial_is_connected(void);

    void power_init(void);
    void power_off(void);

    bool is_encoder_enabled(void);
    void encoder_disable(void);
    void encoder_enable(void);

    void mqtt_init(void);
    int mqtt_publish(const char *topic, const char *playload);
    int mqtt_subscribe(const char *topic);

    void lcd_brightness_init();
    void set_lcd_brightness(int value);

    void buzz_set_enable(bool en);
    void buzz_init(void);
    void buzz_tone(uint32_t _freq, int32_t _duration);

    void system_led_init(void);
    void system_led_run(unsigned long currentMillis);

    void  imu_init(void);
    void  imu_update(void);
    float imu_get_yaw(void);

}


#endif