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

float versaoApp= 0.01;
byte SystemState = OFF;


String textoRecebido = "";
unsigned long delay1 = 0;
String Command = "";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Sistema Integrado de gestão de sinais de transito V"+ String(versaoApp,2));
  Serial.println("System Started......");
  SystemState = ON;
  Serial.println("Command # ");


}

void loop() {
  // put your main code here, to run repeatedly:
  
  char caracter;
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
    
    
    textoRecebido="";
    Command="";
    
  }






}
