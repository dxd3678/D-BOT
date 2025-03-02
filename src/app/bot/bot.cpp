/**
  *   Copyright (C) 2025 dingmos. All rights reserved.
  * @file    bot.c
  * @author  dingmos
  * @version V0.1.0
  * @date    2025-02-23
  * @brief   Bot 状态控制
*/
#include "bot.h"
#include "hal/hal.h"

XBot x_rebot(0, 0);
int g_bot_ctrl_type = BOT_CONTROL_TYPE_AI;

#define WHEEL_DIAMETER 6
#define WHEEL_CIRCUMFERENCE (WHEEL_DIAMETER * M_PI)
#define BOT_MOVE_END_OFFSET (10)
#define BOT_SPIN_END_OFFSET (2)
PIDController pid_bot_s {
    .P = 5, .I = 0, .D = 0.005, .ramp = 100000, 
    .limit = BOT_MAX_STEERING
};

PIDController pid_bot_m {
    .P = 0.5, .I = 0, .D = 0.005, .ramp = 100000, 
    .limit = MOTOR_MAX_SPEED
}; 

static int execute_cmd(Command& cmd) 
{
    int rc = 0;
    float abs_yaw = 0;
    float cur = 0;
    switch (cmd.type) {
        case CommandType::SPIN:
            abs_yaw = HAL::imu_get_abs_yaw();
            x_rebot.setTargetValue(cmd, cmd.value + abs_yaw);
            cmd.status = CommandStatus::EXECUTING;
            cur = abs_yaw;
            break;
        case CommandType::MOVE:
            cur = HAL::motor_get_cur_angle();
            // log_e("move set target: %lf, cur: %lf.", cmd.value + cur, cur);
            x_rebot.setTargetValue(cmd, cmd.value + cur);
            cmd.status = CommandStatus::EXECUTING;
            break;
    }

    rc = x_rebot.cmdExe(cmd, cur);
    if (rc == 0) {
        cmd.status = CommandStatus::COMPLETED;
    }
    return rc;
}

void xbot_thread(void* argument)
{
    int rc = 0;
    bool ready = true;
    Command cmd;
    while(1) {
        if (x_rebot.hasCmd()) {
            cmd = x_rebot.popCommand();
            HAL::audio_play_music("DeviceInsert");
            while (cmd.status != CommandStatus::COMPLETED) {
                rc = execute_cmd(cmd);
                vTaskDelay(pdMS_TO_TICKS(5));
            }
            HAL::audio_play_music("DevicePullout");
        } else {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void XBot::init(void)
{
    TaskHandle_t handleXBotThread;
    xTaskCreate(
        xbot_thread,
        "BuzzerThread",
        4096,
        nullptr,
        ESP32_RUNNING_CORE,
        &handleXBotThread);
}

int XBot::setTargetValue(Command& cmd, double target)
{
    if (cmd.status != CommandStatus::PENDING) {
        return -1;
    }
    log_d("set target: %lf, CUR %lf .", target, HAL::motor_get_cur_angle());
    cmd.target_value = target;
    return 0;
}

int XBot::cmdExe(const Command &cmd, double cur)
{
    float speed = 0, steering = 0;
    float end_offset = 0;
    bool done = false;

    switch (cmd.type) {
        case CommandType::SPIN:
            steering = pid_bot_s(cur - cmd.target_value);
            end_offset = BOT_SPIN_END_OFFSET;
            break;
        case CommandType::MOVE:
            speed = pid_bot_m(cur - cmd.target_value);;
            end_offset = BOT_MOVE_END_OFFSET;
            break;
    }

    // Tmp cmd end condition
    if (abs(cmd.target_value - cur) <= end_offset) {
        done = true;
        speed = 0;
        steering = 0;
    }

    HAL::motor_set_speed(speed, steering);
    if (done) {
        return 0;
    }
    return -1;
}

void XBot::spin(double angel)
{
    commandQueue.push_back({CommandType::SPIN, angel, CommandStatus::PENDING});
}

void XBot::move(double distance)
{
    double motor_angle;
    motor_angle = distanceToAngel(distance);
    commandQueue.push_back({CommandType::MOVE, motor_angle, CommandStatus::PENDING});
}

double XBot::distanceToAngel(double distance)
{
    return distance/WHEEL_CIRCUMFERENCE*360.0;
}

bool XBot::hasCmd(void)
{
    return !commandQueue.empty();
}

Command XBot::popCommand(void) 
{
    Command cmd = commandQueue.front(); 
    commandQueue.erase(commandQueue.begin());
    return cmd;
}