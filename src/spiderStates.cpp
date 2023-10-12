#include <queue>
#include <string>
#include <iostream>
#include <sstream>
#include "shared.h"

using namespace std;

class SpiderState
{
public:
    SpiderState(string name, int servoFL1Deg, int servoFL2Deg, int servoFL3Deg, int servoFR1Deg, int servoFR2Deg, int servoFR3Deg, int servoBL1Deg, int servoBL2Deg, int servoBL3Deg, int servoBR1Deg, int servoBR2Deg, int servoBR3Deg)
    {
        _name = name.append("_");

        _lastState = {getName(), servoFL1Deg, servoFL2Deg, servoFL3Deg, servoFR1Deg, servoFR2Deg, servoFR3Deg, servoBL1Deg, servoBL2Deg, servoBL3Deg, servoBR1Deg, servoBR2Deg, servoBR3Deg};
        _stateQueue.push(_lastState);
    }
    SpiderState *then(int servoFL1Deg, int servoFL2Deg, int servoFL3Deg, int servoFR1Deg, int servoFR2Deg, int servoFR3Deg, int servoBL1Deg, int servoBL2Deg, int servoBL3Deg, int servoBR1Deg, int servoBR2Deg, int servoBR3Deg)
    {
        _lastState.name = getName();
        _lastState.States[0] = servoFL1Deg;
        _lastState.States[1] = servoFL2Deg;
        _lastState.States[2] = servoFL3Deg;
        _lastState.States[3] = servoFR1Deg;
        _lastState.States[4] = servoFR2Deg;
        _lastState.States[5] = servoFR3Deg;
        _lastState.States[6] = servoBL1Deg;
        _lastState.States[7] = servoBL2Deg;
        _lastState.States[8] = servoBL3Deg;
        _lastState.States[9] = servoBR1Deg;
        _lastState.States[10] = servoBR2Deg;
        _lastState.States[11] = servoBR3Deg;

        _stateQueue.push(_lastState);

        return this;
    }
    std::queue<ServoState> getStates()
    {
        return _stateQueue;
    }

private:
    ServoState _lastState;
    queue<ServoState> _stateQueue;
    string _name;
    int _counter;

    string getName()
    {
        stringstream stream;
        stream << _name;
        stream << _counter;

        string result;
        stream >> result;

        _counter++;

        return result;
    }
};