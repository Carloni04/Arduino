/*
      Carlos Nunes
      Arduino - Exemplo de três botoes normal e 3 leds + 1 led RGD
      23/09/2017
 */


// Ports  


int switchPin1 = 5;
int switchPin2 = 6;
int switchPin3 = 7;

int ledPin1 = 8;
int ledPin2 = 9;
int ledPin3 = 10;
int ledRGB = 11;


boolean lastButton1 = LOW;
boolean lastButton2 = LOW;
boolean lastButton3 = LOW;

boolean ledOn1 = false;
boolean ledOn2 = false;
boolean ledOn3 = false;

boolean currentButton1 = LOW;
boolean currentButton2 = LOW;
boolean currentButton3 = LOW;



void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin1, INPUT);
  pinMode(switchPin2, INPUT);
  pinMode(switchPin3, INPUT);

  
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledRGB, OUTPUT);

  

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
    ledOn1 = !ledOn1;
  }
  
  if(lastButton2 == LOW && currentButton2 == HIGH)
  {
    ledOn2 = !ledOn2;
  }
  if(lastButton3 == LOW && currentButton3 == HIGH)
  {
    ledOn3 = !ledOn3;
  }

  
  
    lastButton1 = currentButton1;
    lastButton2 = currentButton2;
    lastButton3 = currentButton3;
    
    
 

    digitalWrite(ledPin1, ledOn1);
    digitalWrite(ledPin2, ledOn2);
    digitalWrite(ledPin3, ledOn3);
    

}
