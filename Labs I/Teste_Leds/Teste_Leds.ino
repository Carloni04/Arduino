// exercicio para controlar 9 leds
// o led vai sfwitando para tras e para a frente
// botao = run / pause
// utilização do millis
// aula de arduino milles



#define PinBotao 8
#define Esquerda 0
#define Direita  1




int PinLeds[9] = {12, 13, 2, 3, 4, 5, 6, 7, 9};
boolean estadoBotao, estadoBotaoAnt;
boolean sistemaON;
unsigned long millesCont=0;
boolean estadoPisca = false;
int PiscaCurr=0;
boolean direccao = Esquerda;

void setup() {
  // put your setup code here, to run once:
  int i;
  Serial.begin(9600);
  for (int i=0;i<9;i++) {
      pinMode(PinLeds[i], OUTPUT);
      digitalWrite(PinLeds[i], LOW);   
  }
  pinMode(PinBotao, INPUT_PULLUP);
  estadoBotao=digitalRead(PinBotao);   
  estadoBotaoAnt=estadoBotao;
  sistemaON = true;
}

void loop() {
  // put your main code here, to run repeatedly:

    

    estadoBotao = !digitalRead(PinBotao); // LOW e UP porque é input_pullup
     if((estadoBotao != estadoBotaoAnt) && (estadoBotao==HIGH)) {  
        
        sistemaON=!sistemaON;
              
                   
    }
        
    


    if(sistemaON) {

        if ((millis()-millesCont)>200) {
            digitalWrite(PinLeds[PiscaCurr], estadoPisca);

        
            if ((PiscaCurr<9) && (!direccao))
              PiscaCurr++;
            
            else if ((PiscaCurr>0) && (direccao))
              PiscaCurr--;
                else {
                    estadoPisca=!estadoPisca;   
                    direccao=!direccao;
                }
   
            millesCont=millis();
        }                
    }


  
    estadoBotaoAnt = estadoBotao;     
    delay(30);
    Serial.print("millesCont -> ");
    Serial.println(millesCont);
}
