#include "shared.h"

void printServoState(ServoState ss)
{
    Serial.print("[ ");
    Serial.print(ss.name.c_str());
    Serial.print(": ");
    for (int i = 0; i < 12; i++)
    {
        Serial.print(ss.States[i]);
        Serial.print(" ");
    }
    Serial.println("]");
}