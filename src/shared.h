#pragma once
#include <Arduino.h>
#include <string>

struct ServoState
{
    std::string name;
    int States[12];
};

void printServoState(ServoState ss);
