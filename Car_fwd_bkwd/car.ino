
/*#####Parts#####
* Motor Shield (L298N)
* Ultrasonic sensor (HC-SR04)
*#####Pins#####
* 5 --> ENA
* 6 --> ENB
* 2 --> Right Front
* 2 --> Left Front
* 4 --> VMotor
* 7 --> IN4
* 8 --> Trig
* 9 --> Echo
*/
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8
int frequency = pulseIn(sensorOut, LOW);


#include <Servo.h>

Servo servo1; // Create object servo1

const int TrigPin=8; //trigger pin for the sensor
const int ReciPin=9; // echo pin for data recive from the sensor
const int DangerT=10; // min distange to the wall

// Left side
int ENA=10; //ENA anf ENB controlls speed of the motors
int IN1=2; 
int IN2=2; 
int VM=4;
/*Here is the controlls for the motors
* RF: HIGH; IN2: LOW --> Direction1 (Left side forward) 
* IN1: LOW; IN2: HIGH --> Direction2 (left side backward
* IN3: HIGH; IN4: LOW --> Direction1 (right side forward)
* IN3: LOW; IN4: HIGH --> Direction2 (right side backward)
*/
//right side
int ENB=6;

int Rdis;                //variable for right side sensor value
int Ldis;                //variable for left side sensor value
long duration;           //distange to wall in centimetres
int motorSpeed=80;       // speed for going forward 
int motorTurnSpeed=110;  // speed for turning



void setup()
{
   servo1.attach(10);
   servo1.write(90);
   pinMode(ENA,OUTPUT);   //set pin modes
   pinMode(IN1,OUTPUT); 
   pinMode(IN2,OUTPUT);

   pinMode(ENB,OUTPUT);

  
   pinMode(TrigPin,OUTPUT);
   pinMode(ReciPin,INPUT);
   pinMode(S0, OUTPUT);
   pinMode(S1, OUTPUT);
   pinMode(S2, OUTPUT);
   pinMode(S3, OUTPUT);
   pinMode(sensorOut, INPUT);

}
void loop()
{
   int distange = ping();
   if(distange>DangerT)// go forward if there isn't wall in front of the car
   {
     void forward();
   }
   else //if there is wall 
   {
     void motorStop();
     servo1.write(0); //turn the servo to right
     delay(500);      // wait for the servo to turn
     Rdis = ping(); //ping right and save it to var Rdis
     delay(100);   // wait for the sensor to ping 
     servo1.write(180); // turn servo left
     delay(700);    //wait longer because the servo has to turn 180 degrees
     Ldis = ping(); //ping left and save it to var Ldis
     delay(100);  // wait for the sensor to ping
     servo1.write(90); // senter the servo
     delay(500); //wait for the servo to senter
     cdis();  // goto compare distange
   } 
}
void cdis()
{
  if(Ldis>DangerT) // if left is more than DangerT (10)
  {
    left(); // turn left
    delay(500); // wait for the car to turn (you might need to adjust these timings for tunrnig)
    motorStop(); // stop 
  }
  else if(Rdis>DangerT) // if left where less than DangerT (10) check if right is less than DangerT (10)
  {
    right(); // turn right
    delay(500); //wait for the car to turn
    motorStop(); // stop
  }
  else // if right and left where less than DangerT turn around
  {
      left(); //turn left 
      delay(1000); //wait for the car to turn around
      motorStop();//stop
  }
}
long ping()
{
  digitalWrite(TrigPin,LOW);//set the pn to low just in case
  delayMicroseconds(2); //wait for it to turn
  digitalWrite(TrigPin,HIGH); //set it high for 5 microseconds
  delayMicroseconds(5);
  digitalWrite(TrigPin,LOW);//and back to low again
  
  duration = pulseIn(ReciPin,HIGH); // measure the time it took the sound to bounce back
  return duration / 29 / 2; // calculate the distange (in centimetres)
}
void forward()  // from here starts the motor controlls at the start if this sketch there where instructions on how to control the motors
{   if(pulseIn(sensorOut, LOW)== frequency)
{
    digitalWrite(IN1,HIGH); 
    digitalWrite(IN2,LOW);
    analogWrite(ENA,motorSpeed);
}
else
{
  digitalWrite(VM,HIGH);
  delay(10000);
}
}


void backward()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,motorSpeed);
    

}
 
  
void left()
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    analogWrite(ENA,motorTurnSpeed);
    
}
  
  
void right()
{
    analogWrite(ENA,motorTurnSpeed);  
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    
    analogWrite(ENB,motorTurnSpeed);
}

  
void motorStop()
{
    analogWrite(ENA,0);
    analogWrite(ENB,0);
}

