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

float calcularPontoDeOrvalho(float temperatura, float umidade) {
  double a = 17.27;
  double b = 237.7;
  double alfa = (a * temperatura) / (b + temperatura) + log(umidade / 100.0);
  return (b * alfa) / (a - alfa);
}

String determinarStatus(float temperatura, float umidade){
  String a, b;
  
  if (temperatura > 16 && temperatura < 30){
    a = "\033[32mTemperatura agradável\033[0m";
  } else if (temperatura <= 16){
      a = "\033[34mFrio\033[0m";
    } else if (temperatura > 30){
        a = "\033[31mQuente\033[0m";
      }

  if (umidade >= 40 && umidade < 70){
    b = "\033[32mUmidade agradável\033[0m";
  } else if (umidade >= 70){
      b = "\033[34mÚmido\033[0m";
    } else if (umidade < 40){
       b ="\033[33mSeco\033[0m";
    }

  return a + " e " + b;
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
            Serial3.println("\033[32mLâmpada ligada!\033[0m");
            
          } else if (msg == "desligar lampada") {
            digitalWrite(RELEPIN, LOW);
            Serial3.println("\033[31mLâmpada desligada!\033[0m");
            
          } else if (msg == "temperatura") {
            float temp = dht.readTemperature();
            float umid = dht.readHumidity();
            float pontoOrvalho = calcularPontoDeOrvalho(temp, umid);
            String status = determinarStatus(temp, umid);

            if(isnan(temp) || isnan(umid))
              Serial3.println("\033[31mErro ao receber dados do sensor DHT11!\033[0m");
            else
              Serial3.println("Temperatura: " + String(temp) + " °C\nUmidade: " + String(umid) + " %\nPonto de Orvalho " + String(pontoOrvalho) + " °C\nStatus: " + String(status));
          
          } else if(msg.startsWith(".") || msg == "ESP inicializado!" || msg.startsWith("192") || msg.startsWith("IP")) {
            Serial.println(msg);
          } else{
            Serial3.println("\033[33mComando inválido!\033[0m");
          }
          msg = "";
      }
    }
  }
}
