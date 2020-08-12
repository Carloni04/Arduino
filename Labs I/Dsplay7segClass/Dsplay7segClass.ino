// class display7seg
// Objectivos:
// criar class para controlar display 7 seg

#include "displays.h"




// Display 7 segments with multiplex 74LS47N
// multiplex addr
#define PinMultiplexAddr0 8
#define PinMultiplexAddr1 9
#define PinMultiplexAddr2 10
#define PinMultiplexAddr3 11

// display pins
#define PinDP  A0
// #define PinDP  A5
#define PinAddr3 A4
#define PinAddr2 A3
#define PinAddr1 A2
#define PinAddr0 A1


#define  freqDisplayMultiplex 20


#define delay1  1000


display7Segments *display1, *display2;
led *led1;
int subDisplayiD1[] = {0,1,2};
int subDisplayiD2[] = {3};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  byte DisplayAddr[4] = {PinAddr0, PinAddr1, PinAddr2, PinAddr3};
  byte MultiplexAddr[4] = {PinMultiplexAddr0, PinMultiplexAddr1, PinMultiplexAddr2, PinMultiplexAddr3}; 
  display1 = new display7Segments(4, DisplayAddr, MultiplexAddr, PinDP);
  
  display1->SetNumber(23);
  

  
/*
  // Teste a class led
  led1 = new led(); 
  led1->setAddr(5);
*/

  
  
}

int y=9;
void loop() {
   static unsigned long delayDigito3 = 0;
  // put your main code here, to run repeatedly:
  //int x = display1->showDisplayNumbers();
  //Serial.print("Numero de displays -> ");
  //Serial.println(x);

  
  display1->Show();
  
  
 
  


 
 
  if((millis()-delayDigito3) > delay1) { 
      Serial.print("countdown -> ");            
      Serial.println(y);            
      display1->setDigit(3,y);
      y--;
      
      
      if (y < 0) 
        y=9;
                              
      delayDigito3 = millis();              
  }


delay(1);









  
}








