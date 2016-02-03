#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <wiringPi.h> 

#define LED 18 


int main (void)
{
    int i;
    if (wiringPiSetupGpio() == -1) 
    return 1;	
    pinMode(LED,OUTPUT);
    digitalWrite(LED,LOW);
    
    pinMode(LED, PWM_OUTPUT); 
  
    while(1)     
  {
    for(i=0;i<1024;++i)
    {
        pwmWrite(LED,i);
        delay(1);
    }
    for(i=1023;i>=0;--i)
    {
        pwmWrite(LED,i);
        delay(1);
    }
  }
  return 0;
}