#include <Arduino.h>
#include <queue>
#include "servoWrapper.cpp"
#include "shared.h"

struct ServoInitData
{
    int Pin;
    int Orientation;
};

class Spider
{
public:
    Spider(int servoSpeed, struct ServoInitData servos[12])
    {
        _servoSpeed = servoSpeed;
        for (int i = 0; i < 12; i++)
        {
            _servoWrappers[i] = new ServoWrapper(servos[i].Pin, servos[i].Orientation);
        }
    }

    void StandUp()
    {
        Serial.println("going into standing position");
        queueState("standing_1",
                   125, 120, 45,
                   125, 120, 45,
                   55, 120, 45,
                   55, 120, 45);

        queueState("standing_2",
                   125, 90, 90,
                   125, 90, 90,
                   55, 90, 90,
                   55, 90, 90);
    }

    void TakeStep()
    {
        queueState("step_0",
                   125, 90, 90,
                   125, 90, 90,
                   55, 90, 90,
                   55, 90, 90);
        queueState("step_1",
                   0, 0, 0,
                   0, 135, 45,
                   0, 0, 110,
                   0, 0, 0);
        queueState("step_2",
                   0, 0, 0,
                   135, 0, 0,
                   0, 0, 0,
                   0, 0, 0);
        queueState("step_3",
                   0, 0, 0,
                   0, 90, 90,
                   0, 0, 90,
                   0, 0, 0);
    }

    bool UpdateServos(float factor)
    {
        bool done = true;

        for (auto servoWrapper : _servoWrappers)
        {
            servoWrapper->Move(_servoSpeed * factor);
            if (servoWrapper->IsMoving())
            {
                done = false;
            }
        }

        if (done)
        {
            return nextStateFromQueue();
        }

        return done;
    }
    void SetServo(int num, int deg)
    {
        (*_servoWrappers[num]).SetDegree(deg);
    }

private:
    int _servoSpeed;
    ServoWrapper *_servoWrappers[12];
    std::queue<ServoState> _stateQueue;

    void queueState(std::string name, int servoFL1Deg, int servoFL2Deg, int servoFL3Deg, int servoFR1Deg, int servoFR2Deg, int servoFR3Deg, int servoBL1Deg, int servoBL2Deg, int servoBL3Deg, int servoBR1Deg, int servoBR2Deg, int servoBR3Deg)
    {
        ServoState newState = {name, servoFL1Deg, servoFL2Deg, servoFL3Deg, servoFR1Deg, servoFR2Deg, servoFR3Deg, servoBL1Deg, servoBL2Deg, servoBL3Deg, servoBR1Deg, servoBR2Deg, servoBR3Deg};

        Serial.print("pushing state to queue: ");
        printServoState(newState);

        _stateQueue.push(newState);
    }
    void queueState(ServoState newState)
    {
        Serial.print("pushing state to queue: ");
        printServoState(newState);

        _stateQueue.push(newState);
    }
    template <size_t N>
    void queueStates(ServoState newStates[N])
    {
        for (auto newState : newStates)
        {
            Serial.print("pushing state to queue: ");
            printServoState(newState);

            _stateQueue.push(newState);
        }
    }

    bool nextStateFromQueue()
    {
        if (!_stateQueue.empty())
        {
            auto newState = _stateQueue.front();
            _stateQueue.pop();

            SetServos(newState.States[0], newState.States[1], newState.States[2],
                      newState.States[3], newState.States[4], newState.States[5],
                      newState.States[6], newState.States[7], newState.States[8],
                      newState.States[9], newState.States[10], newState.States[11]);

            Serial.print("prepared state from queue: ");
            printServoState(newState);
            return false;
        }

        return true;
    }

protected:
    void SetServos(int servoFL1Deg, int servoFL2Deg, int servoFL3Deg, int servoFR1Deg, int servoFR2Deg, int servoFR3Deg, int servoBL1Deg, int servoBL2Deg, int servoBL3Deg, int servoBR1Deg, int servoBR2Deg, int servoBR3Deg)
    {
        if (servoFL1Deg != 0)
        {
            (*_servoWrappers[0]).SetDegree(servoFL1Deg);
        }
        if (servoFL2Deg != 0)
        {
            (*_servoWrappers[1]).SetDegree(servoFL2Deg);
        }
        if (servoFL3Deg != 0)
        {
            (*_servoWrappers[2]).SetDegree(servoFL3Deg);
        }

        if (servoFR1Deg != 0)
        {
            (*_servoWrappers[3]).SetDegree(servoFR1Deg);
        }
        if (servoFR2Deg != 0)
        {
            (*_servoWrappers[4]).SetDegree(servoFR2Deg);
        }
        if (servoFR3Deg != 0)
        {
            (*_servoWrappers[5]).SetDegree(servoFR3Deg);
        }

        if (servoBL1Deg != 0)
        {
            (*_servoWrappers[6]).SetDegree(servoBL1Deg);
        }
        if (servoBL2Deg != 0)
        {
            (*_servoWrappers[7]).SetDegree(servoBL2Deg);
        }
        if (servoBL3Deg != 0)
        {
            (*_servoWrappers[8]).SetDegree(servoBL3Deg);
        }

        if (servoBR1Deg != 0)
        {
            (*_servoWrappers[9]).SetDegree(servoBR1Deg);
        }
        if (servoBR2Deg != 0)
        {
            (*_servoWrappers[10]).SetDegree(servoBR2Deg);
        }
        if (servoBR3Deg != 0)
        {
            (*_servoWrappers[11]).SetDegree(servoBR3Deg);
        }
    }
};