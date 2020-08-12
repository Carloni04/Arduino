// Projecto para treinar programacao arduino
// Objectivos:
// Control de sinais transito
// Control pela consola
// botao para passar peoes
// mostrar no display 7 seg (1 + 3) os segundos para passar os peoes
// utilizacao de um multiplex 74LS47N
// mostrar no display 7 seg Temperatura
// addons seguintes: medir temp e mostrar num display 7 seg
// com sesnsor de temperatura e escrita no display


#include "DHT.h"
#include "displays.h"

// *******************definiçõs do DHT ********************** 
#define DHTPIN 12     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

#define State0  50000
#define State1   3000
#define State2   6000
#define State3   4000


// multiplex addr
#define PinMultiplexAddr0 8
#define PinMultiplexAddr1 9
#define PinMultiplexAddr2 10
#define PinMultiplexAddr3 11

// display pins
#define PinDP  A5
#define PinAddr3 A4
#define PinAddr2 A3
#define PinAddr1 A2
#define PinAddr0 A1


#define OFF 0
#define ON  1
#define TEST 2

 //colocar resistencia de 10k caso nao seja pullup ou pulldown
#define PinBotton 7   

#define minus 10
#define dot 11
#define Doff 12


// Numero de Caracteres configurados no display 7 seg
#define numDisplays  4
#define  freqDisplayMultiplex 20

int PinLedsSemaforo[3] = {4, 5, 6}; // verde, amarelo, vermelho
int PinLedsSemaforoPeoes[2] = {2, 3}; // verde, vermelho
 
float versaoApp= 0.02;
byte SystemState = OFF;

int timer;
boolean estadoPisca;
int timerPisca;

int estadoBotao;
int estadoBotaoAnterior;

float DHTvalues[2];

int estadoSistema;

String textoRecebido = "";
unsigned long delay1 = 0;
int delay2 = 1000;
unsigned long delaytemp = 0;
String Command = "";



// #################### Functions ##########################
byte menu(String command);


//byte DisplayAddr[numDisplays] = {PinAddr0, PinAddr1, PinAddr2, PinAddr3};

//byte MultiplexAddr[4] = {PinMultiplexAddr0, PinMultiplexAddr1, PinMultiplexAddr2, PinMultiplexAddr3};
display7Segments *display1;
//int subDisplayiD1[] = {0,1,2};
//int subDisplayiD2[] = {3};

int peoescount=0;
int timer2=0;

void setup() {
  // put your setup code here, to run once:




// put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Sistema Integrado de gestão de sinais de transito V"+ String(versaoApp,2));
  Serial.println("System Started......");
  SystemState = ON;
  Serial.println("Command # ");


  pinMode (PinBotton, INPUT_PULLUP);
  
  dht.begin();

  
  
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

  byte DisplayAddr[4] = {PinAddr0, PinAddr1, PinAddr2, PinAddr3};
  byte MultiplexAddr[4] = {PinMultiplexAddr0, PinMultiplexAddr1, PinMultiplexAddr2, PinMultiplexAddr3}; 
  display1 = new display7Segments(4, DisplayAddr, MultiplexAddr, PinDP);
  
  display1->SetNumber(23);


}


void loop() {
  // put your main code here, to run repeatedly:
  int timestats[4] = {State0,State1,State2,State3};
  
  char caracter;
  display1->Show();
  
  estadoBotao = !digitalRead(PinBotton); // LOW e UP porque é input_pullup
  if((estadoBotao != estadoBotaoAnterior) && (estadoBotao==HIGH)) {  
      estadoBotaoAnterior = estadoBotao;        
      if (estadoSistema==0) 
              estadoSistema++; 
              timer=0;            
  }
  estadoBotaoAnterior = estadoBotao;    

peoescount = ((timer2 / 1000) % 10) ;


switch (estadoSistema) {

        case 0:  //vermelho pioes
            digitalWrite(PinLedsSemaforo[0], HIGH);   
            digitalWrite(PinLedsSemaforo[1], LOW);   
            digitalWrite(PinLedsSemaforo[2], LOW);   
            digitalWrite(PinLedsSemaforoPeoes[0], LOW);   
            digitalWrite(PinLedsSemaforoPeoes[1], HIGH); 
            
            //display1->setDigit(3, 0);
            
            
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
            //timer2--;
            display1->setDigit(3, peoescount );
              
            break;
        case 3:
            digitalWrite(PinLedsSemaforo[0], LOW);   
            digitalWrite(PinLedsSemaforo[1], LOW);   
            digitalWrite(PinLedsSemaforo[2], HIGH);   
            digitalWrite(PinLedsSemaforoPeoes[1], LOW);
            estadoBotaoAnterior = estadoBotao;  
            display1->setDigit(3, peoescount );
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
        
        if (timer>=timestats[estadoSistema]) {
            timer=0;
            if (estadoSistema==1) {
              timer2=9999;
            }
            
            if (estadoSistema<3) 
                estadoSistema++;
                
            else {
                estadoSistema=0;
                timer2=0;
            }  
        } 
        else {
            timer++;
            timer2--;
        }

  
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


  if((millis()-delaytemp) > delay2) { 
      display1->SetNumber(int(DHTvalues[0]));
      DHTvalues[0]= dht.readTemperature();
      Serial.print("XXXXXXXXX -> ");
      Serial.println(int(DHTvalues[0]));
      delaytemp = millis();              
  }
 delay(1);
}

byte menu(String command) {

DHTvalues[0]= dht.readTemperature();
DHTvalues[1]= dht.readHumidity();
if (isnan(DHTvalues[0] ) || isnan(DHTvalues[1])) {
  Serial.println(F("Failed to read from DHT sensor!"));
  return;
}

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
      // Read temperature as Celsius (the default)
      Serial.print("Temperature is: ");
      Serial.print(DHTvalues[0]);
      Serial.println("ºC");
      display1->SetNumber(int(DHTvalues[0]));
    }
    if (Command == "HUM") {
      Serial.print("Humidity is: ");            
      Serial.println(DHTvalues[1]);
      
    }
     
    if (Command == "HELP") {
      Serial.println("Command List: \n\tON - Start System\n\tOFF - Stop System\n\tTEST - Test Mode\n\tHELP - Display this message");
      Serial.println("\tTEMP - Temperature\n\tHUM - Humidity");
    }


return 0;
  
}



