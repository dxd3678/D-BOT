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

#include <SimpleFOC.h>


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

class XBot {
public:
    XBot(double position = 0.0, double heading = 0.0)
        :_position(position), _heading(heading) {}
    void init();

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
    double _heading;
    double _position;
    std::vector<Command> commandQueue; 
    double target_yaw;
};


extern XBot x_rebot;
#endif 