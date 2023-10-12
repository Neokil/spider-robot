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

  spider = new Spider(20, initData);
  spider->StandUp();
  // spider->TakeStep();
  //  spider->TakeStep();

  Serial.println("Setup end");
}

String command = "";

void loop()
{
  bool stateReached = spider->UpdateServos();

  if (Serial.available() <= 0)
  {
    return;
  }

  while (Serial.available() > 0)
  {
    int inChar = Serial.read();
    if (isAlphaNumeric(inChar) || inChar == ' ')
    {
      command += (char)inChar;
      Serial.write((char)inChar);
    }
    if (inChar == '\n')
    {
      executeCommand();
      command = "";
    }
  }

  // if (stateReached)
  //{
  //   state++;
  //   // if (state > 1)
  //   //{
  //   //   state = 0;
  //   // }
  //   Serial.print("going into state ");
  //   Serial.println(state);
  //   switch (state)
  //   {
  //   case 0:
  //     Serial.println("standing up");
  //     spider->StandUp();
  //     break;
  //   case 1:
  //     Serial.println("taking a step");
  //     spider->TakeStep();
  //     break;
  //   case 2:
  //     Serial.println("finished");
  //   }
  // }
}

void executeCommand()
{
  command.trim();
  if (command.length() < 4)
  {
    Serial.print("command too short: ");
    Serial.println(command);
    return;
  }

  String servo = command.substring(0, 3);
  servo.trim();
  long deg = command.substring(4).toInt();
  Serial.print("Setting servo ");
  Serial.print(servo);
  Serial.print(" to ");
  Serial.print(deg);
  Serial.println("deg");

  if (servo == "FL1")
  {
    spider->SetServo(0, deg);
  }
  else if (servo == "FL2")
  {
    spider->SetServo(1, deg);
  }
  else if (servo == "FL3")
  {
    spider->SetServo(2, deg);
  }
  else if (servo == "FR1")
  {
    spider->SetServo(3, deg);
  }
  else if (servo == "FR2")
  {
    spider->SetServo(4, deg);
  }
  else if (servo == "FR3")
  {
    spider->SetServo(5, deg);
  }
  else if (servo == "BL1")
  {
    spider->SetServo(6, deg);
  }
  else if (servo == "BL2")
  {
    spider->SetServo(7, deg);
  }
  else if (servo == "BL3")
  {
    spider->SetServo(8, deg);
  }
  else if (servo == "BR1")
  {
    spider->SetServo(9, deg);
  }
  else if (servo == "BR2")
  {
    spider->SetServo(10, deg);
  }
  else if (servo == "BR3")
  {
    spider->SetServo(11, deg);
  }
  else
  {
    Serial.println("Invalid Servo");
  }
}
