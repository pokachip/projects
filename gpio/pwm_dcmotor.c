#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h> 

#define Lvin1 23
#define Lvin2 24
#define Rvin1 27
#define Rvin2 22

int main (void)
{ 
  if (wiringPiSetupGpio() == -1) 
  return 1;

  pinMode(Lvin1,OUTPUT); 
  pinMode(Lvin2,OUTPUT);
  pinMode(Rvin1,OUTPUT);
  pinMode(Rvin2,OUTPUT);

  digitalWrite(Lvin1,LOW);
  digitalWrite(Lvin2,LOW);
  digitalWrite(Rvin1,LOW);
  digitalWrite(Rvin2,LOW);


    while(1)     
  {
    digitalWrite(Lvin2,LOW);
    digitalWrite(Rvin2,LOW);
    pinMode(Lvin1,PWM_OUTPUT);
    pinMode(Rvin1,PWM_OUTPUT);
    pwmWrite(Lvin1,100);
    pwmWrite(Rvin1,100);

    delay(4000);   

    digitalWrite(Lvin1,LOW);
    digitalWrite(Rvin1,LOW);
    pinMode(Lvin2,PWM_OUTPUT);
    pinMode(Rvin2,PWM_OUTPUT);
    pwmWrite(Lvin2,100);
    pwmWrite(Rvin2,100);

    delay(4000); 
  }
  return 0;
}