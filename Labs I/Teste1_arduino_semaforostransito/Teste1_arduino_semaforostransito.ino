// aula de arduino 4 
// nao funciona coreectamente 
int PinLedsSemaforo[3] = {11, 10, 9}; // verde, amarelo, vermelho
int PinLedsSemaforoPeoes[2] = {13, 12}; // verde, vermelho
int PinBotao = 8;  //colocar resistencia de 10k
int estado;
int estadoBotao;
int estadoBotaoAnterior;
int valor=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  int i;
  for (i=0;i<3;i++) {
      pinMode(PinLedsSemaforo[i], OUTPUT);
  }
  
  for (i=0;i<2;i++) {
      pinMode(PinLedsSemaforoPeoes[i], OUTPUT);
  }
  pinMode (PinBotao, INPUT_PULLUP);
  estado=0;
  estadoBotao = LOW;
  estadoBotaoAnterior = estadoBotao;
}

void loop() {
  // put your main code here, to run repeatedly:


    estadoBotao = !digitalRead(8); // LOW e UP porque é input_pullup

    if((estadoBotao != estadoBotaoAnterior) && (estadoBotao==HIGH)) {  
        estadoBotaoAnterior = estadoBotao;
    }

    if((estadoBotao != estadoBotaoAnterior) && (estadoBotao==LOW)) {  
        estadoBotaoAnterior = estadoBotao;
        valor++;
        Serial.print("Valor -> ");
        Serial.println (valor);
        delay(100);
        if (estado<3) estado++;
        else estado=0;
   
        
    }
    
    
    if (estado==0) {   // Verde Semaforo
        digitalWrite(PinLedsSemaforo[0], HIGH);   
        digitalWrite(PinLedsSemaforo[1], LOW);   
        digitalWrite(PinLedsSemaforo[2], LOW);   
        digitalWrite(PinLedsSemaforoPeoes[0], LOW);   
        digitalWrite(PinLedsSemaforoPeoes[1], HIGH);   
    }
    if (estado==1) { //Amarelo Semaforo
        digitalWrite(PinLedsSemaforo[0], LOW);   
        digitalWrite(PinLedsSemaforo[1], HIGH);   
        digitalWrite(PinLedsSemaforo[2], LOW);   
        digitalWrite(PinLedsSemaforoPeoes[0], LOW);   
        digitalWrite(PinLedsSemaforoPeoes[1], HIGH);   
      }
    if (estado==2) { //Vermelho Semaforo
        digitalWrite(PinLedsSemaforo[0], LOW);   
        digitalWrite(PinLedsSemaforo[1], LOW);   
        digitalWrite(PinLedsSemaforo[2], HIGH);   
        digitalWrite(PinLedsSemaforoPeoes[0], HIGH);   
        digitalWrite(PinLedsSemaforoPeoes[1], LOW);   
        }
    if (estado==3) { // Verde a piscar peoes
          digitalWrite(PinLedsSemaforo[0], LOW);   
          digitalWrite(PinLedsSemaforo[1], LOW);   
          digitalWrite(PinLedsSemaforo[2], HIGH);   
          digitalWrite(PinLedsSemaforoPeoes[1], LOW);
          
       //   for (int j=0;j<5; j++) {
             digitalWrite(PinLedsSemaforoPeoes[0], HIGH);   
             delay(500); 
             digitalWrite(PinLedsSemaforoPeoes[0], LOW);   
             delay(500); 
         // } 
    }




}
