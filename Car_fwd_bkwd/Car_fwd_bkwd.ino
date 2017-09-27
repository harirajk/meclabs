#include <AFMotor.h>
F_DCMotor motor1(1, MOTOR12_64KHZ); // create motor #2, 64KHz pwm
AF_DCMotor motor2(2, MOTOR12_64KHZ); // create motor #2, 64KHz pwm

int long sensorValue = 0;

void setup() {
 Serial.begin(9600);           // set up Serial library at 9600 bps
 Serial.println("Motor test!");
 
 motor1.setSpeed(2000);     // set the speed to 200/255
 motor2.setSpeed(150);     // set the speed to 200/255  /// change commits to be up to date
 
}

void loop() {
 Serial.print("tick");
 sensorValue = analogRead(A0);
   Serial.print(sensorValue);

  if (sensorValue > 520) { // I dont know if your sensor's readings get larger when it gets close to the wall or smaller so you might have to change > to < 
  
 motor1.run(FORWARD);
 motor2.run(BACKWARD);      // turn it on going backward
 delay(1000);
 
 
   motor1.run(FORWARD);
 motor2.run(FORWARD); 
  delay(500); //play around with the delay to make it turn the right amount
 
  }
  
  else {
  
 motor1.run(BACKWARD);
 motor2.setSpeed(150);
 motor2.run(FORWARD);      // turn it on going forward
 delay(1000);
 
 
  }
} 
