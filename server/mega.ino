#include <Adafruit_Sensor.h>
#include <DHT.h>

#define DHTPIN 11
#define RELEPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
String msg;

void setup(){
  Serial.begin(115200);  // Comunicação com o computador
  Serial3.begin(57600);   // Comunicação com o ESP
  dht.begin();
  pinMode(RELEPIN, OUTPUT);
  Serial.println("\nMega inicializado!");
}

void loop() {
  if (Serial3.available()) {
    char data = Serial3.read();
    msg += data;
    
    if (data == '\n' || data == '\r'){
      msg.trim(); // remove espaços no inicio e fim

      if(msg.length() > 0){

          if (msg == "ligar lampada") {
            digitalWrite(RELEPIN, HIGH);
            Serial3.println("Lâmpada ligada!");
            
          } else if (msg == "desligar lampada") {
            digitalWrite(RELEPIN, LOW);
            Serial3.println("Lâmpada desligada!");
            
          } else if (msg == "temperatura") {
            float temp = dht.readTemperature();
            float umid = dht.readHumidity();

            if(isnan(temp) || isnan(umid))
              Serial3.println("\nErro ao receber dados do sensor DHT11!");
            else
              Serial3.println("Temperatura: " + String(temp) + " °C\nUmidade: " + String(umid) + " %");
          
          } else if(msg.startsWith(".") || msg == "ESP inicializado!" || msg.startsWith("192") || msg.startsWith("IP")) {
            Serial.println(msg);
          } else{
            Serial3.println("Comando inválido!");
          }
          msg = "";
      }
    }
  }
}
