#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 11
#define RELEPIN 13
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
String msg;

void setup(){
  Serial.begin(115200);  // Comunicação com o computador
  Serial3.begin(9600);   // Comunicação com o ESP
  dht.begin();
  pinMode(RELEPIN, OUTPUT);
  Serial.println("\nMega inicializado!");
}

void loop() {
  if (Serial3.available()) {
    char data = Serial3.read();
    msg += data;

    // Verifica se a mensagem completa foi recebida
    if (data == '\n' || data == '\r') {
      msg.trim();  // Remove espaços e caracteres extras no início/fim
      if (msg == "ligar lampada") {
        digitalWrite(RELEPIN, HIGH);
        Serial3.println("Lâmpada ligada!");
      } else if (msg == "desligar lampada") {
        digitalWrite(RELEPIN, LOW);
        Serial3.println("Lâmpada desligada!");
      } else if (msg == "temperatura") {
        float temp = dht.readTemperature();
        float umid = dht.readHumidity();
        Serial3.println("Temperatura: " + String(temp) + " °C\nUmidade: " + String(umid) + " %");

      } else {
        Serial3.println("Comando inválido!");
      }
      msg = "";  // Limpa a mensagem após o processamento
    }
  }
}
