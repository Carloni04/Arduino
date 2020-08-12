//  exercicio que apresenta aleatoriamenete valores no display de leds
// funcoes para aprentar um numero no display (4) entre -999 e 9999

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



// #################### Functions
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


// Conf botao
int numberAle=0;
boolean estadoBotao, estadoBotaoAnt;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  initDisplay7Seg();
 
  //startup botao
  pinMode(PinBotao, INPUT_PULLUP);
  estadoBotao=digitalRead(PinBotao);   
  estadoBotaoAnt=estadoBotao;
  
  // gerar numero
  randomSeed(analogRead(0));

  
}



void loop() {
  // put your main code here, to run repeatedly:

     estadoBotao = !digitalRead(PinBotao); // LOW e UP porque é input_pullup
     if((estadoBotao != estadoBotaoAnt) && (estadoBotao==HIGH)) {  
            numberAle = random(0,9999);
            Serial.print("Numero Aleatorio -> ");
            Serial.println(numberAle);
     }

      showDisplay(numberAle);
      
      estadoBotaoAnt = estadoBotao;  
      delay(6);
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





