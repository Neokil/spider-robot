#include <Arduino.h>
#include <queue>
#include "servoWrapper.cpp"
#include "spiderStates.cpp"
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
        auto states = (new SpiderState("step",
                                       125, 90, 90,
                                       125, 90, 90,
                                       55, 90, 90,
                                       55, 90, 90))
                          ->then(0, 0, 0,
                                 0, 45, -45,
                                 0, 0, 20,
                                 0, 0, 0)
                          ->then(0, 0, 0,
                                 10, 0, 0,
                                 0, 0, 0,
                                 0, 0, 0)
                          ->then(0, 0, 0,
                                 0, -45, 45,
                                 0, 0, -20,
                                 0, 0, 0)
                          ->getStates();

        while (!states.empty())
        {
            queueState(states.front());
            states.pop();
        }
    }

    bool UpdateServos()
    {
        bool done = true;

        for (auto servoWrapper : _servoWrappers)
        {
            servoWrapper->Move(_servoSpeed);
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
        (*_servoWrappers[0]).SetDegree(servoFL1Deg);
        (*_servoWrappers[1]).SetDegree(servoFL2Deg);
        (*_servoWrappers[2]).SetDegree(servoFL3Deg);

        (*_servoWrappers[3]).SetDegree(servoFR1Deg);
        (*_servoWrappers[4]).SetDegree(servoFR2Deg);
        (*_servoWrappers[5]).SetDegree(servoFR3Deg);

        (*_servoWrappers[6]).SetDegree(servoBL1Deg);
        (*_servoWrappers[7]).SetDegree(servoBL2Deg);
        (*_servoWrappers[8]).SetDegree(servoBL3Deg);

        (*_servoWrappers[9]).SetDegree(servoBR1Deg);
        (*_servoWrappers[10]).SetDegree(servoBR2Deg);
        (*_servoWrappers[11]).SetDegree(servoBR3Deg);
    }
};