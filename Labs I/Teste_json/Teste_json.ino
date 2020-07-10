
#include <ArduinoJson.h>


// variables to hold data
StaticJsonDocument<100> jsonDoc;
JsonObject payload = jsonDoc.to<JsonObject>();
JsonObject status = payload.createNestedObject("valores");
static char msg[50];

float t=-10;
float h=0;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  t+=1;
  if (h<99) h++;
    else h=0;

  

// Print Message to console in JSON format
    status["temp"] = t;
    status["humidity"] = h;
    serializeJson(jsonDoc, msg, 50);
    Serial.println(msg);
   
 
 delay(10000);



}
