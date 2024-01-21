#include <L298NX2.h>

const int base_speed = 120;
char dir = '_';

const unsigned int EN_A = 3;
const unsigned int IN1_A = 5;
const unsigned int IN2_A = 6;

const unsigned int IN1_B = 7;
const unsigned int IN2_B = 8;
const unsigned int EN_B = 9;

const unsigned int ECHO = 13;
const unsigned int TRIG = 12;

long duration;
int distance;

L298NX2 motors(EN_A, IN1_A, IN2_A, EN_B, IN1_B, IN2_B);


void setup() {
  // put your setup code here, to run once:
  // Used to display information
  Serial.begin(9600);
  pinMode(IN1_A, OUTPUT);
  pinMode(IN2_A, OUTPUT);
  pinMode(IN1_B, OUTPUT);
  pinMode(IN2_B, OUTPUT);
  pinMode(EN_A, OUTPUT);
  pinMode(EN_B, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG, OUTPUT);

}

void motorMoveL(int speed, bool dir)
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

void motorMoveR(int speed, bool dir)
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

void turnLeft(){
  motorMoveL(0,1);
  motorMoveR(base_speed,1);
}
void turnRight(){
  motorMoveL(base_speed,1);
  motorMoveR(0,1);
}

void loop() {
  // put your main code here, to run repeatedly:
  //to complete a maze automatically, follow the right wall, so if the bot encounters a wall or nearly, it should try and turn right
  // fidn out a way to complete stop the bot, turn it right, and then continue, like a roomba
  // 

  motors.setSpeed(80);

  motorMoveL(base_speed-50, 1);
  motorMoveR(base_speed-30, 1);
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);

  //trigger the ultrasonic

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);



  //read waves from echo
  duration = pulseIn(ECHO, HIGH);

  //calculate distance (distance = speed / time)
  distance = duration * 0.034 /2;

  if (distance <= 20){
    Serial.println("Obstacle Detected");
    
    turnRight();
    Serial.println("A...B");

  }

  Serial.print("Distance: " );
  Serial.print(distance);
  Serial.println(" cm");

}
