// Projecto para treinar programacao arduino
// Objectivos:
// Control de sinais transito
// Control pela consola
// botao para passar peoes
// mostrar no display 7 seg (1 + 3) os segundos para passar os peoes
// mostrar no display 7 seg Temperatura
// addons seguintes: medir temp e mostrar num display 7 seg

#define OFF 0
#define ON  1
#define TEST 2

 //colocar resistencia de 10k caso nao seja pullup ou pulldown
#define PinBotton 8   

// Portas dos Pins do Display 8 seg
#define PinA  9
#define PinB  8
#define PinC  A4
#define PinD  A2
#define PinE  A3
#define PinF  10
#define PinG  11
#define PinDP  A5
#define PinBotao 7
#define PinAddr0 12
#define PinAddr1 13
#define PinAddr2 A1
#define PinAddr3 A0
#define minus 10
#define dot 11
#define Doff 12

// Numero de Caracteres configurados no display 7 seg
#define numberDisplayCaracteres  13
#define numDisplays  4
#define freqDisplayMultiplex 2





int PinLedsSemaforo[3] = {4, 5, 6}; // verde, amarelo, vermelho
int PinLedsSemaforoPeoes[2] = {2, 3}; // verde, vermelho
 
float versaoApp= 0.01;
byte SystemState = OFF;

int timer;
boolean estadoPisca;
int timerPisca;

int estadoBotao;
int estadoBotaoAnterior;


int estadoSistema;

String textoRecebido = "";
unsigned long delay1 = 0;
String Command = "";

// #################### Functions
byte menu(String command);
void showNumber(int id);
void beginLed (int port);
void initDisplay7Seg ();
void showDisplays();
void showDigit(int digitId, boolean value);
void showDisplay(int number);
void identifyDigits(int number);


// Configuracao display 7 seg
byte DisplayNumbers[numberDisplayCaracteres] = {  0b11111100,  //0
                                                 0b01100000,   //1
                                                 0b11011010,   //2                     
                                                 0b11110010,   //3
                                                 0b01100110,   //4
                                                 0b10110110,   //5
                                                 0b10111110,   //6
                                                 0b11100000,   //7
                                                 0b11111110,   //8
                                                 0b11110110,   //9
                                                 0b00000010,   //-
                                                 0b00000001,   //.
                                                 0b00000000};   //
  
  
// Pins do display 7 seg
byte PinDisplay7Seg[8] = {PinA, PinB, PinC, PinD, PinE, PinF, PinG, PinDP};


byte DisplayAddr[numDisplays] = {PinAddr0, PinAddr1, PinAddr2, PinAddr3};
byte digitos[numDisplays];







void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Sistema Integrado de gestão de sinais de transito V"+ String(versaoApp,2));
  Serial.println("System Started......");
  SystemState = ON;
  Serial.println("Command # ");


  pinMode (PinBotton, INPUT_PULLUP);
  initDisplay7Seg();
  
  estadoBotao = !digitalRead(PinBotton); // LOW e UP porque é input_pullup
  estadoBotaoAnterior = estadoBotao;
  Serial.println(estadoBotao);

  int i;
  timer=0;
  for (i=0;i<3;i++) 
      pinMode(PinLedsSemaforo[i], OUTPUT);
  for (i=0;i<2;i++) 
      pinMode(PinLedsSemaforoPeoes[i], OUTPUT);
  estadoPisca=true; // Pisca peoes verde intermitente
  timerPisca=200; // Pisca peoes verde intermitente









}

void loop() {
  // put your main code here, to run repeatedly:
  
  char caracter;
  
  showDisplay(5159);
  
  estadoBotao = !digitalRead(PinBotton); // LOW e UP porque é input_pullup
  if((estadoBotao != estadoBotaoAnterior) && (estadoBotao==HIGH)) {  
      estadoBotaoAnterior = estadoBotao;        
      if (estadoSistema==0) 
              estadoSistema++;
        
      

  }
  estadoBotaoAnterior = estadoBotao;    

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





  
  
  
  // Le valores da porta serie
  if (Serial.available()) {
    caracter = Serial.read();
    textoRecebido += caracter;
    delay1 = millis();
  }
  // escreve no output o valor enviado e processo comando
  if (((millis() - delay1) > 10) && (textoRecebido != "")) {
    Serial.print("Command # ");
    Serial.println(textoRecebido);
    Command = textoRecebido;
    Command.toUpperCase();
    //Command.toUpperCase();
    byte commandChoice = menu (Command);
    textoRecebido="";
    Command="";
    
  }



 delay(1);
}







      






byte menu(String command) {


if (Command == "ON") {
      Serial.println("System ON");
    }
    if (Command == "OFF") {
      Serial.println("System OFF");
    }
    if (Command == "TEST") {
      Serial.println("System in Test Mode");
    }
    if (Command == "TEMP") {
      Serial.println("Temperature is: ");
    }
    if (Command == "HUM") {
      Serial.println("Humidity is: ");
    }
     
    if (Command == "HELP") {
      Serial.println("Command List: \n\tON - Start System\n\tOFF - Stop System\n\tTEST - Test Mode\n\tHELP - Display this message");
      Serial.println("\tTEMP - Temperature\n\tHUM - Humidity");
    }


return 0;


  
}


// ##### Funcoes do Display 7seg

void showNumber(int id) {
  // display a number in 7seg led
 for (int nL=0;nL<8;nL++) {
      digitalWrite(PinDisplay7Seg[nL], !bitRead(DisplayNumbers[id], 7-nL));              
  }    
}

void initLed (int port) {
// begin Led Port
  pinMode(port, OUTPUT);
}

void initDisplay7Seg () {
  // Iniciate the display 7 seg pins
 for (int i=0;i<8;i++) {    
      initLed(PinDisplay7Seg[i]);     
 }
 for (int i=0;i<numDisplays;i++) {      
    initLed(DisplayAddr[i]);
    digitalWrite(DisplayAddr[i], false); 
 }

}


void showDigit(int digitId, boolean value){
  digitalWrite(DisplayAddr[digitId], value);
}

void identifyDigits(int number){
            // identifica os digitos
            int numDigits=3;
            if (number >= 0) { 
              digitos[3] = ((number / 1000) % 10);
              digitos[2] = ((number / 100) % 10);
              digitos[1] = ((number / 10) % 10);
              digitos[0] = number % 10;
            }
            else {
              // falta corrigir para numeros negativos
              number = number * -1;
              digitos[3] = ((number / 1000) % 10);                            
              digitos[2] = ((number / 100) % 10);              
              digitos[1] = ((number / 10) % 10);              
              digitos[0] = number % 10;
              digitos[3]=minus;
              int cD = 2;
              while (cD>=1){
                if(digitos[cD]==0) {
                  numDigits=cD;
                  digitos[cD+1]=Doff;
                  digitos[cD]=minus;
                }
                else
                  cD=0;
                cD--;
              }          
           }
}


void showDisplay(int number) {
            static byte digSelect = 0;
            static unsigned long delayDisplayMultiplex = 0;

            identifyDigits(number);            
            if((millis()-delayDisplayMultiplex) > freqDisplayMultiplex) {             
                showDigit(digSelect, LOW);                          
                digSelect++;
                if (digSelect >= numDisplays) 
                  digSelect=0;              
                showDigit(digSelect, HIGH);
                showNumber(digitos[digSelect]);                           
                delayDisplayMultiplex = millis();              
            }

}




