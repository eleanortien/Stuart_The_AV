
/*
Author  : Andrea Lombardo
Site    : https://www.lombardoandrea.com
Source  : https://github.com/AndreaLombardo/L298N/

Here you can see how to work in a common configuration.
Expand
Untitled.txt
4 KB
﻿
/*
Author  : Andrea Lombardo
Site    : https://www.lombardoandrea.com
Source  : https://github.com/AndreaLombardo/L298N/

Here you can see how to work in a common configuration.

L298NX2 is not a new version of module or IC, 
but it stands for a double implementation of L298N library.

With L298NX2 is possible to initialize two motors at once.

Speed range go from 0 to 255, default is 100.
Use setSpeed(speed) to change speed for both motors,
setSpeedA(speed) or setSpeedB(speed) for individual changes.

Sometimes at lower speed motors seems not running.
It's normal, may depends by motor and power supply.

Wiring schema in file "L298NX2 - Schema_with_EN_pin.png"
*/

//65 is good base speed

// Include the (new) library
#include <L298NX2.h>

const int base_speedA = 100;
const int base_speedB = 120;
char dir = '_';
bool start = false;
bool returning = false;

// Pin definition
const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;

const unsigned int line_sensor = 10;
// const int time_check = 5000;
// unsigned long previousMillis = 0;

// Initialize both motors
L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);

void setup()
{
  // Used to display information
  Serial.begin(9600);
  pinMode(line_sensor, INPUT);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);





}

void pwmA(int speed, bool dir)
{
  motors.setSpeedA(speed);

  if (dir)
  {
    motors.forwardA();
  }
  else
  {
    motors.backwardA();
  }


}

void pwmB(int speed, bool dir)
{
   motors.setSpeedB(speed);

  if (dir)
  {
    motors.forwardB();
  }
  else
  {
    motors.backwardB();
  }

}


void loop()
{
  //print the motor status in the serial monitor
  //printSomeInfo();
  //Black = 1
  //White = 0

  switch(dir)
  {
    // case 'f'://b right, a left
    //  pwmA(base_speedB, 1);
    //  pwmB(base_speedA, 1);
    // // break;
    case 'l':
    pwmB(base_speedB, 1);
    pwmA(0, 1);
    break;
    case 'r':
    pwmA(base_speedA, 1);
    pwmB(0, 1);
    break;
    //case 'b':
    // pwmA(base_speed, 0);
    // pwmB(base_speed, 0);
    // break;

    default:
    motors.stop();
    break;
  }
  
  int val = digitalRead(line_sensor); // read value from sensor
  
  Serial.println(dir);

  
  if (val == 0) {
    if (!returning)
    {
       returning = true ;
      switch (dir)
      {
        case 'l':
          dir = 'r';
          break;
        case 'r':
          dir = 'l';
          break;
      }

    }
   

    // unsigned long currentMillis = millis();

    // if (currentMillis - previousMillis >= time_check) {
    // // save the last time you left to white

    //   previousMillis = currentMillis;
    //   dir = "_";
    //   start = false;
    // }


    
  } else {
    if (!start)
    {
      dir = 'r';
      start = true;
    }
    if (returning)
    {
      returning = false;
    }
    
    
  
  }

  
 
}

/*
Print some informations in Serial Monitor
*/
void printSomeInfo()
{
  Serial.print("Motor A is moving = ");
  Serial.print(motors.isMovingA() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedA());
  Serial.print("Motor B is moving = ");
  Serial.print(motors.isMovingB() ? "YES" : "NO");
  Serial.print(" at speed = ");
  Serial.println(motors.getSpeedB());
}
