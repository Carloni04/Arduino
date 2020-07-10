// retira valor do LDR e coloca na consola
//consoante a intensidad da luz acente o determinado numero de leds

#define PinLDR A0

int PinLeds[9] = {12, 13, 2, 3, 4, 5, 6, 7, 9};


float LDRValue;
float lum;
float min, max;


void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  pinMode(A0, INPUT);
  min=1;
  max=1000;
  for (int i=0;i<9;i++) {
      pinMode(PinLeds[i], OUTPUT);
      digitalWrite(PinLeds[i], LOW);   
  }


}

void loop() {
  // put your main code here, to run repeatedly:


    LDRValue = analogRead(A0);
    lum = (LDRValue/max) * 10;
    lum = (lum -10) * -1;
    

    for (int i=0;i<9;i++) {
          if (lum<i) 
          digitalWrite(PinLeds[i], HIGH);
          else   
          digitalWrite(PinLeds[i], LOW);
    }


    
    Serial.print("Valor do LDR -> ");
    Serial.println(LDRValue);
    Serial.print("Luminosidade -> ");
    Serial.println(lum);
    
    
    
    delay(500);

}
