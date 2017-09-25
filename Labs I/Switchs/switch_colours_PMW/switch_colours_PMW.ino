/*
      Carlos Nunes
      Arduino - Exemplo de três botoes normal e 3 leds + 1 led RGD (PMW)
      25/09/2017
 */

// Ports  

int switchPin1 = 5;
int switchPin2 = 6;
int switchPin3 = 7;

int ledPin1 = 11;
int ledPin2 = 9;
int ledPin3 = 10;

boolean lastButton1 = LOW;
boolean lastButton2 = LOW;
boolean lastButton3 = LOW;

boolean currentButton1 = LOW;
boolean currentButton2 = LOW;
boolean currentButton3 = LOW;

int ledLevel1 = 0;
int ledLevel2 = 0;
int ledLevel3 = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);

  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
//  pinMode(ledRGB, OUTPUT);

  

}

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
  currentButton3 = debounce(lastButton3, switchPin3);

  if(lastButton1 == LOW && currentButton1 == HIGH)
  {
    ledLevel1 = ledLevel1 + 21;
  }
  
  if(lastButton2 == LOW && currentButton2 == HIGH)
  {
    ledLevel2 = ledLevel2 + 21;
  }
  if(lastButton3 == LOW && currentButton3 == HIGH)
  {
    ledLevel3 = ledLevel3 + 21;
  }

  
    lastButton1 = currentButton1;
    lastButton2 = currentButton2;
    lastButton3 = currentButton3;
    
    if (ledLevel1 > 255) 
      ledLevel1 = 0;
    if (ledLevel2 > 255) 
      ledLevel2 = 0;
    if (ledLevel3 > 255) 
      ledLevel3 = 0;
    
  
    analogWrite(ledPin1, ledLevel1);
    analogWrite(ledPin2, ledLevel2);
    analogWrite(ledPin3, ledLevel3);

}
