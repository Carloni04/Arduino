/*
      Carlos Nunes
      Arduino - Exemplo de um botao normal e um um PMW
      23/09/2017
 */

// liga switch 

// Variaveis Led
int switchPin1 = 8;
int ledPin = 13;

boolean lastButton1 = LOW;
boolean lastButton2 = LOW;
boolean ledOn = false;
boolean currentButton1 = LOW;
boolean currentButton2 = LOW;

//Variaveis LenPWM
int ledPinPWM = 11;
int ledLevel = 0;
int switchPin2 = 7;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin1, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(switchPin2, INPUT);
  pinMode(ledPinPWM, OUTPUT);
  
  

}
/*
boolean debounce(boolean last)
{
  boolean current = digitalRead(switchPin1);
  if (last != current)
  {
    delay(5);
    current = digitalRead(switchPin1);
  }
  return current;
}
*/

boolean debounce(boolean last, int switchPin)
{
  boolean current = digitalRead(switchPin);
  if (last != current)
  {
    delay(5);
    current = digitalRead(switchPin);
  }
  return current;
}




void loop() {
  // put your main code here, to run repeatedly:
  currentButton1 = debounce(lastButton1, switchPin1);
  currentButton2 = debounce(lastButton2, switchPin2);
  if(lastButton1 == LOW && currentButton1 == HIGH)
  {
    ledOn = !ledOn;
    
       
  }

  
   if(lastButton2 == LOW && currentButton2 == HIGH)
  {
  
    ledLevel = ledLevel + 51;
    
       
  }
  
    lastButton1 = currentButton1;
    lastButton2 = currentButton2;
    
    if (ledLevel > 255) 
      ledLevel = 0;
    
    
    digitalWrite(ledPin, ledOn);
    analogWrite(ledPinPWM, ledLevel);
    


}
