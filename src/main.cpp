#include <Arduino.h>
#include "spider.cpp"

void executeCommand();

Spider *spider;

int state = 0;

void setup()
{
  Serial.begin(115200);

  // delay(5000);
  Serial.println("Setup start");
  struct ServoInitData initData[12] = {
      {2, -1},
      {3, 1},
      {4, 1},
      {5, 1},
      {6, -1},
      {7, -1},
      {8, -1},
      {9, -1},
      {10, -1},
      {11, 1},
      {12, 1},
      {13, 1},
  };

  spider = new Spider(5, initData);
  spider->StandUp();

  Serial.println("Setup end");
}

long lastUpdate = 0;
void loop()
{
  long timeTaken = millis() - lastUpdate;
  lastUpdate = millis();
  bool stateReached;

  if (spider != NULL)
  {
    stateReached = spider->UpdateServos(timeTaken / 10);
  }

  if (stateReached)
  {
    state++;

    switch (state)
    {
    case 1:
      Serial.println("taking step 1");
      spider->TakeStep1();
      break;
    case 2:
      Serial.println("taking step 2");
      spider->TakeStep2();
      break;
    case 3:
      Serial.println("taking step 3");
      spider->TakeStep3();
      break;
    case 4:
      Serial.println("taking step 4");
      spider->TakeStep4();
      break;
    case 5:
      delay(2500);
      spider->~Spider();
      spider = NULL;
      break;
    }
  }

  delay(10);
}
