/**
  *   Copyright (C) 2025 dingmos. All rights reserved.
  * @file    bot.h
  * @author  dingmos
  * @version V0.1.0
  * @date    2025-02-23
  * @brief   Bot 状态控制
*/
#ifndef __BOT_H__
#define __BOT_H__

#include <iostream>
#include <vector>
#include <memory>

#include <SimpleFOC.h>
#include "comm/simple_comm.h"

enum bot_control_type {
    BOT_CONTROL_TYPE_AI,
    BOT_CONTROL_TYPE_JOYSTICKS,
    BOT_CONTROL_TYPE_MAX,
};

extern int g_bot_ctrl_type;

enum class CommandType {
    SPIN,
    MOVE
};

enum class CommandStatus {
    PENDING,   
    EXECUTING,  
    COMPLETED,  
    FAILED
};

struct Command {
    CommandType type; 
    double value;
    CommandStatus status;
    double target_value;
};

class DBot {
public:
    DBot() {};

    // 删除拷贝构造函数和赋值运算符
    DBot(const DBot&) = delete;
    DBot& operator=(const DBot&) = delete;

    // 工厂函数，返回 DBot 的单例实例
    static DBot& getInstance();

    void init();

    void addComm(iot::SimpleComm *comm);
    void loop();
    void spin(double angel);
    void move(double distance);

    int spinExe(double angel);
    int moveExe(double angel);
    bool hasCmd(void);
    Command popCommand(void);
    int setTargetValue(Command& cmd, double target);
    int cmdExe(const Command &cmd, double cur);

private:
    double distanceToAngel(double distance);
    std::vector<Command> commandQueue; 
    double target_yaw;
    void handleMessage(const JsonDocument& json);
    std::vector<iot::SimpleComm *> _comms;
};

#endif 