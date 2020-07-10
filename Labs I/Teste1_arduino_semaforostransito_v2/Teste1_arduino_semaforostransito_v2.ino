// ******************************************************************
// ****     Aplicação arduino de control semaforo transito
// ****     Veiculos e Peoes
// ****     Leds e um Botao para ficar Verde
// ****     Carlos Nunes - 31/08/2019
// ******************************************************************


int PinLedsSemaforo[3] = {11, 10, 9}; // verde, amarelo, vermelho
int PinLedsSemaforoPeoes[2] = {13, 12}; // verde, vermelho
int PinBotao = 8;  //colocar resistencia de 10k
int estadoSistema;
int estadoBotao;
int estadoBotaoAnterior;
int timer;

boolean estadoPisca;
int timerPisca;

void setup() {
  // put your setup code here, to run once:
  int i;
  timer=0;
  for (i=0;i<3;i++) 
      pinMode(PinLedsSemaforo[i], OUTPUT);
  for (i=0;i<2;i++) 
      pinMode(PinLedsSemaforoPeoes[i], OUTPUT);
  pinMode (PinBotao, INPUT_PULLUP);
  estadoSistema=0;
  estadoBotao = !digitalRead(8); // LOW e UP porque é input_pullup
  estadoBotaoAnterior = estadoBotao;
  estadoPisca=true; // Pisca peoes verde intermitente
  timerPisca=200; // Pisca peoes verde intermitente
}


void loop() {

    estadoBotao = !digitalRead(8); // LOW e UP porque é input_pullup
    if((estadoBotao != estadoBotaoAnterior) && (estadoBotao==HIGH)) {  
        estadoBotaoAnterior = estadoBotao;        
        if (estadoSistema==0) 
              estadoSistema++;
        
    }

    switch (estadoSistema) {

        case 0:
            digitalWrite(PinLedsSemaforo[0], HIGH);   
            digitalWrite(PinLedsSemaforo[1], LOW);   
            digitalWrite(PinLedsSemaforo[2], LOW);   
            digitalWrite(PinLedsSemaforoPeoes[0], LOW);   
            digitalWrite(PinLedsSemaforoPeoes[1], HIGH);   
            break;
        case 1:
            digitalWrite(PinLedsSemaforo[0], LOW);   
            digitalWrite(PinLedsSemaforo[1], HIGH);   
            digitalWrite(PinLedsSemaforo[2], LOW);   
            digitalWrite(PinLedsSemaforoPeoes[0], LOW);   
            digitalWrite(PinLedsSemaforoPeoes[1], HIGH);   
            break;
        case 2:
            digitalWrite(PinLedsSemaforo[0], LOW);   
            digitalWrite(PinLedsSemaforo[1], LOW);   
            digitalWrite(PinLedsSemaforo[2], HIGH);   
            digitalWrite(PinLedsSemaforoPeoes[0], HIGH);   
            digitalWrite(PinLedsSemaforoPeoes[1], LOW);   
            break;
        case 3:
            digitalWrite(PinLedsSemaforo[0], LOW);   
            digitalWrite(PinLedsSemaforo[1], LOW);   
            digitalWrite(PinLedsSemaforo[2], HIGH);   
            digitalWrite(PinLedsSemaforoPeoes[1], LOW);
            estadoBotaoAnterior = estadoBotao;     
            if (timerPisca >1) {
                digitalWrite(PinLedsSemaforoPeoes[0], estadoPisca);   
                timerPisca--;
            }
            else {
                timerPisca=200;
                estadoPisca=!estadoPisca;
            }
             break;
        }
        
        if (timer==4000) {
            timer=0;
            if (estadoSistema<3) 
                estadoSistema++;
            else
                estadoSistema=0;
        } 
        else
            timer++;
        
        delay(1);
}
