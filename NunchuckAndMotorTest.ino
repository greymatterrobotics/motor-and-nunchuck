#include <Wire.h>
#include <ArduinoNunchuk.h>
#include <AFMotor.h>

#define BAUDRATE 9600
int motorSpeed;
boolean cPressedLast;
boolean zPressedLast;
ArduinoNunchuk nunchuk = ArduinoNunchuk();
AF_DCMotor motor(1, MOTOR12_64KHZ); // !!IMPORTANT!! Change this line depending on motor

void setup()
{
  Serial.begin(BAUDRATE);
  nunchuk.init();
  cPressedLast = false;
  zPressedLast = false;
  
  motorSpeed = 15;
  motor.setSpeed(motorSpeed);
}

void loop()
{
  nunchuk.update();
  
  if (nunchuk.cButton == 1 && motorSpeed < 255 && cPressedLast == false)
  {
    setRelMotorSpeed(15);
    Serial.println(motorSpeed);
    cPressedLast = true;
  }
  else if (nunchuk.zButton == 1 && motorSpeed > 0 && zPressedLast == false)
  {
    setRelMotorSpeed(-15);
    zPressedLast = true;
    motor.setSpeed(motorSpeed);
  }
  else
  {
    cPressedLast = false; 
    zPressedLast = false;
  }
  
  if (nunchuk.analogY > 204)
  {
    motor.run(FORWARD);
  }
  else if (nunchuk.analogY < 102)
  {
    motor.run(BACKWARD);
  }
  else
  {
    motor.run(RELEASE);
  }
}

void setRelMotorSpeed(int relSpeed)
{
  motorSpeed += relSpeed;
  motor.setSpeed(motorSpeed);
  Serial.println(motorSpeed);
}

