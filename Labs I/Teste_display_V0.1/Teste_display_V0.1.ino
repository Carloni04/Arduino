// Utilizacao de um digito 7seg
// vai contando e mostra na consola e no segmento


// Portas dos Pins do Display 8 seg
#define PinA  2
#define PinB  3
#define PinC  4
#define PinD  5
#define PinE  6
#define PinF  7
#define PinG  9
#define PinDP  10



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

int number=0;
void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

 for (int i=0;i<8;i++) {
      pinMode(PinLeds[i], OUTPUT);
      digitalWrite(PinLeds[i], HIGH);   
      delay (50);
  }

}

void loop() {
  // put your main code here, to run repeatedly:



    Serial.println(number);

    for (int i=0;i<8;i++) {
      digitalWrite(PinLeds[i], !Numbers[number][i]);       
    }
    

    if(number<9) 
      number++;
    else
      number=0;

delay(300);

}


