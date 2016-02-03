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
  
   
    digitalWrite(Lvin2, 0);
    digitalWrite(Rvin2, 0);
    digitalWrite(Lvin1, 1);
    digitalWrite(Rvin1, 1);
    delay(3000);   

    digitalWrite(Lvin1, 0);
    digitalWrite(Rvin1, 0);
    digitalWrite(Lvin2, 1);
    digitalWrite(Rvin2, 1);
    delay(3000); 

    digitalWrite(Lvin2, 1);
    digitalWrite(Rvin2, 0);
    digitalWrite(Lvin1, 0);
    digitalWrite(Rvin1, 1);
    delay(3000);   

    digitalWrite(Lvin1, 1);
    digitalWrite(Rvin1, 0);
    digitalWrite(Lvin2, 0);
    digitalWrite(Rvin2, 1);
    delay(3000);    
 
    digitalWrite(Lvin1, 0);
    digitalWrite(Rvin1, 0);
    digitalWrite(Lvin2, 0);
    digitalWrite(Rvin2, 0);
     
  
  return 0;
}