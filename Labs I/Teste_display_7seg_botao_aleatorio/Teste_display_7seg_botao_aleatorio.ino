//  exercicio que apresenta aleatoriamenete valores no display de leds

// Portas dos Pins do Display 8 seg
#define PinA  2
#define PinB  3
#define PinC  4
#define PinD  5
#define PinE  6
#define PinF  7
#define PinG  9
#define PinDP  10
#define PinBotao 8


byte PinLeds[8] = {PinA, PinB, PinC, PinD, PinE, PinF, PinG, PinDP};
byte Numbers[11][8] = {{1, 1, 1, 1, 1, 1, 0, 0},
                      {0, 1, 1, 0, 0, 0, 0, 0},
                      {1, 1, 0, 1, 1, 0, 1, 0},
                      {1, 1, 1, 1, 0, 0, 1, 0},
                      {0, 1, 1, 0, 0, 1, 1, 0},
                      {1, 0, 1, 1, 0, 1, 1, 0},
                      {1, 0, 1, 1, 1, 1, 1, 0},
                      {1, 1, 1, 0, 0, 0, 0, 0},
                      {1, 1, 1, 1, 1, 1, 1, 0},
                      {1, 1, 1, 1, 0, 1, 1, 0},
                      {0, 0, 0, 0, 0, 0, 0, 1}};


int numberAle=0;
boolean estadoBotao, estadoBotaoAnt;



void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

 for (int i=0;i<8;i++) {
      pinMode(PinLeds[i], OUTPUT);
      digitalWrite(PinLeds[i], !Numbers[numberAle][i]); 
  }
  pinMode(PinBotao, INPUT_PULLUP);
  estadoBotao=digitalRead(PinBotao);   
  estadoBotaoAnt=estadoBotao;
  randomSeed(analogRead(0));
}

void loop() {
  // put your main code here, to run repeatedly:

     estadoBotao = !digitalRead(PinBotao); // LOW e UP porque é input_pullup
     if((estadoBotao != estadoBotaoAnt) && (estadoBotao==HIGH)) {  
            numberAle = random(0,9);
            Serial.print("Numero Aleatorio -> ");
            Serial.println(numberAle);
           
           for (int i=0;i<8;i++) {
                digitalWrite(PinLeds[i], !Numbers[numberAle][i]);       
            }                   
    }

      delay(10);
      estadoBotaoAnt = estadoBotao;  
}

