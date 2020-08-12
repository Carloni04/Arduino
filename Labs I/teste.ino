// Projecto para treinar programacao arduino
// Objectivos:
// Control de sinais transito
// Control pela consola
// botao para passar peoes
// mostrar no display 7 seg os segundos para passar os peoes
//
// addons seguintes: medir temp e mostrar num display 7 seg

#define OFF 0
#define ON  1
#define TEST 2
 
 //colocar resistencia de 10k caso nao seja pullup ou pulldown
#define PinBotton 8   

 
float versaoApp= 0.01;
byte SystemState = OFF;


int estadoBotao;
int estadoBotaoAnterior;

boolean teste = false;


String textoRecebido = "";
unsigned long delay1 = 0;
String Command = "";

byte menu(String command);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Sistema Integrado de gestão de sinais de transito V"+ String(versaoApp,2));
  Serial.println("System Started......");
  SystemState = ON;
  Serial.println("Command # ");


  pinMode (PinBotton, INPUT_PULLUP);
  
  estadoBotao = !digitalRead(PinBotton); // LOW e UP porque é input_pullup
  estadoBotaoAnterior = estadoBotao;
  Serial.println(estadoBotao);











}

void loop() {
  // put your main code here, to run repeatedly:
  
  char caracter;
  
  
  
  estadoBotao = !digitalRead(PinBotton); // LOW e UP porque é input_pullup
  if((estadoBotao != estadoBotaoAnterior) && (estadoBotao==HIGH)) {  
      estadoBotaoAnterior = estadoBotao;        
     
      teste = !teste;
      Serial.println("Ping");
      if (teste == true) {
        Serial.println("Estado ON");
      }
      else {
          Serial.println("Estado OFF");
      }

  }
  estadoBotaoAnterior = estadoBotao;    
  
  
  
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



 delay(10);
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
