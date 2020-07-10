int teste(int , int );
int teste1(int , int );
int teste2(int &, int );
int teste3(int &, int );


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

 int a= 10;
  int b=5;
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(teste(a,b));



}

void loop() {
  // put your main code here, to run repeatedly:
 
  int a= 10;
  int b=5;
  Serial.print(a);
  Serial.print(" + ");
  Serial.print(b);
  Serial.print(" = ");
  Serial.println(teste2(a,b));
  Serial.print(" Valor de A = ");
  Serial.println(a);
Serial.println(teste2(a,b));
  Serial.print(" Valor de A = ");
  Serial.println(a);
Serial.println(teste2(a,b));
  Serial.print(" Valor de A = ");
  Serial.println(a);
Serial.println(teste3(a,b));
  Serial.print(" Valor de A = ");
  Serial.println(a);





  delay(5000); 

}

int teste(int val1, int val2) {
  return val1+val2;
}

int teste1(int val1, int val2) {
  val1=40;
  return val1+val2;
}

int teste2(int &val1, int val2) {
  val1+=5;;
  return val1+val2;
}


int teste3(int &val1, int val2) {
  static int total;
  total+= val1;
  val1+=5;;
  Serial.println(total);
  return val1+val2;
}

