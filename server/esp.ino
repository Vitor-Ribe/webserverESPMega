#include <ESP8266WiFi.h>
WiFiServer server(80);

void setup() {
  Serial.begin(57600);  // Comunicação com o Mega
  WiFi.begin("MICROTELL-CASA-2G", "ribeiro.23");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  server.begin();
  Serial.println("\nESP inicializado!\nIP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    // Lê o comando enviado pelo cliente
    String command = client.readStringUntil('\n');

    // Envia o comando para o Mega
    Serial.println(command);  
    delay(100);  // Pequeno atraso para o Mega processar

    // Aguarda resposta do Mega
    String response = "";
    unsigned long startTime = millis();
    while (millis() - startTime < 500) {  // Timeout de 1/2 segundos
      if (Serial.available()) {
        response += char(Serial.read());
      }
    }

    // Se não houver resposta do Mega, notifica o cliente
    if (response.length() == 0) {
      response = "Nenhuma resposta do Mega.";
    }

    // Envia a resposta de volta ao cliente
    client.println(response);

    // Finaliza a conexão
    client.stop();
  }
}
