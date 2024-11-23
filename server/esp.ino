#include <ESP8266WiFi.h>
WiFiServer server(80);

void setup() {
  Serial.begin(9600);  // Comunicação com o Mega
  WiFi.begin("ssid", "senha");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  server.begin();
  Serial.println("ESP inicializado!");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String command = client.readStringUntil('\n');
    Serial.println(command);  // Para depuração no monitor serial do ESP

    // Envia o comando para o Mega
    Serial.println(command);  
    delay(500);  // Espera resposta do Mega
    if (Serial.available()) {
      String response = Serial.readStringUntil('\n');
      client.println(response);  // Envia a resposta para o cliente
    }
    client.stop();
  }
}
