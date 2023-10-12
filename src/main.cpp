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
  // spider->TakeStep();
  //  spider->TakeStep();

  Serial.println("Setup end");
}

String command = "";

long lastUpdate = 0;
void loop()
{
  long timeTaken = millis() - lastUpdate;
  lastUpdate = millis();

  bool stateReached = spider->UpdateServos(timeTaken / 10);
  delay(10);

  if (stateReached)
  {
    delay(1000);
    Serial.println("taking step");
    spider->TakeStep();
  }
}
