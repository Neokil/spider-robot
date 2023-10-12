#include <Arduino.h>
#include <Servo.h>

class ServoWrapper
{
public:
    ServoWrapper(int pin, int orientation)
    {
        _orientation = orientation;
        _targetFrequency = 1500;
        _pin = pin;
        _servo.attach(pin);
        _servo.write(_targetFrequency);
        Serial.print("Initialized Servo at pin ");
        Serial.print(pin);
        Serial.println(" with 90deg");
    }
    void SetDegree(int deg)
    {
        deg = 90 - ((90 - deg) * _orientation);

        _targetFrequency = 500 + (double(deg) / 180 * 2000);
    }
    void Move(int x)
    {

        int currentFrequency = _servo.readMicroseconds();
        int diff = _targetFrequency - currentFrequency;
        if (diff < 0)
        {
            // diff is less than step so we reach the target
            if (diff > -x)
            {
                currentFrequency = _targetFrequency;
            }
            else
            {
                currentFrequency -= x;
            }
        }
        else if (diff > 0)
        {
            // diff is less than step so we reach the target
            if (diff < x)
            {
                currentFrequency = _targetFrequency;
            }
            else
            {
                currentFrequency += x;
            }
        }

        _servo.write(currentFrequency);
    }
    bool IsMoving()
    {
        return _servo.readMicroseconds() != _targetFrequency;
    }

private:
    Servo _servo;
    int _orientation;
    int _targetFrequency;
    int _pin;
};
