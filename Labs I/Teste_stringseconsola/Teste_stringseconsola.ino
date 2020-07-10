// Utilização e manupulação de strings no arduino


String textoRecebido = "";
unsigned long delay1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Benvindo Carloni!!!");
  Serial.println("Tipos de casts entre strings e variaveis");
  int numero = 280;
  float numero2 = 345.3456;
  String texto;
  String texto1 = "Brincando";
  String texto2 = " com ideias";
  
  // coloca o valor numerico de numero em formato string
  texto = String(numero);
  //texto = String(numero, BIN);
  //texto = String(numero, HEX);
  Serial.print("Numero convertido: ");
  Serial.println(texto);  

  // concatnacao de strings
  Serial.print("Concatenacao de strings: ");
  texto1.concat(texto2);
  //texto1 = texto1 + texto2;
  //texto1 += texto2;
  //texto1 = texto1 + texto2 + " " + 2020;
  Serial.println(texto1); 

  texto = String(numero2);
  //texto = String(numero2, 4); // transf o valor em string com 4 posicoes decimais
  Serial.print("Numero convertido: ");
  Serial.println(texto);  

  // identificacao de caracteres na string
  String texto3 = "Brincando com Ideias";
  Serial.print("Caracter na posicao (2): ");
  Serial.println(texto3.charAt(2));
  //Serial.println(texto3[2]);  

// substituicao de caracteres na string
  texto3.setCharAt(10, 'C');
  //texto3[10] = 'C';
  Serial.print("Texto modificado: ");
  Serial.println(texto3);

  // search
  Serial.println("Search :");
  texto3 = "Brincando com Ideias";
  
  Serial.println(texto3);
  Serial.println("0123456789012345678901234567890");
  Serial.println("          1         2         3");
  Serial.println("");

  Serial.print("Posicao do texto procurado (com): ");
  Serial.println(texto3.indexOf("com"));
  Serial.print("Posicao do texto procurado (Ideias): ");
  Serial.println(texto3.indexOf("Ideias"));
  Serial.print("Posicao do texto procurado (a): ");
  Serial.println(texto3.indexOf('a'));
  //Serial.println(texto3.indexOf('a',10));
  Serial.print("Ultima Ocorrencia de (n): ");
  Serial.println(texto3.lastIndexOf('n'));
  //Serial.println(texto3.lastIndexOf('n',5));

  // retirar string dentro de outra string 
   Serial.print("Texto entre os indices 4 e 8: ");
  Serial.println(texto3.substring(4, 8));
  
  // Modificar texto
  texto3.replace ("com", "nas minhas");
  Serial.print("Texto Modificado: ");
  Serial.println(texto3);
  
  // Remover texto
  texto3 = "Brincando com Ideias";
  texto3.remove (10, 4);
  Serial.print("Texto Modificado: ");
  Serial.println(texto3);
  texto3.remove (9);
  Serial.print("Texto Modificado: ");
  Serial.println(texto3);
  // Lowercase e Uplowercase
    texto3 = "Brincando com Ideias";
  texto3.toUpperCase();
  Serial.print("Texto Modificado: ");
  Serial.println(texto3);
  texto3.toLowerCase();
  Serial.print("Texto Modificado: ");
  Serial.println(texto3);

  
  // trim 
  texto3 = "    Ideias     ";
  Serial.print("|");
  Serial.print(texto3);
  Serial.print("|");
  
  texto3.trim();
  Serial.print("Texto Modificado: ");
  Serial.print("|");
  Serial.print(texto3);
  Serial.println("|");

  


  Serial.println("Introduza o texto # ");
}

void loop() {
  // put your main code here, to run repeatedly:
  char caracter;
  String texto1 = "brincando";

  // Le valores da porta serie
  if (Serial.available()) {
    caracter = Serial.read();
    textoRecebido += caracter;
    delay1 = millis();
  }
  // escreve no output o valor enviado
  if (((millis() - delay1) > 10) && (textoRecebido != "")) {
    Serial.print("Texto recebido: ");
    Serial.println(textoRecebido);

    // tamanho da string
    Serial.print("     Tamanho do texto: ");
    Serial.println(textoRecebido.length());
 

    // comparacao de strings
    // compara se iguais ou diferentes
    if (textoRecebido == texto1) {
      Serial.println("IGUAL");
    }
    else {
      Serial.println("DIFERENTE");
    }
    // valida se a string e maior ou menor
    if (textoRecebido > texto1) {
      Serial.println("MAIOR");
    }
    else {
      Serial.println("NAO E MAIOR");
    }
    // comparar se o texto comeca ou acaba com valor
    if (texto1.startsWith(textoRecebido)) {
      Serial.println("Comeco Igual");
    }
    else {
      Serial.println("Comeco Diferente");
    }
    if (texto1.endsWith(textoRecebido)) {
      Serial.println("Final Igual");
    }
    else {
      Serial.println("Final Diferente");
    }

    Serial.println("Converter strings em outras variaveis");
    //int convertido = textoRecebido.toInt();
    float convertido = textoRecebido.toFloat();
    Serial.print("Texto cconcatenado: "); 
    Serial.println(textoRecebido + 200);
    Serial.print("Texto recebido e calculado: "); 
    Serial.println(convertido + 200, 4);



       textoRecebido = "";
  }

}
