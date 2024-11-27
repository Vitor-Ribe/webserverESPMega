## Trabalho desenvolvido para a disciplina de Sistemas Distribuídos do 7º período em Ciência da Computação
Implementação de RPC (Remote Procedure Call), e RMI (Remote Method Invocation) para comunicação com dispositivos embarcados em redes locais.

### Introdução
O projeto consiste no uso de um ESP8266 conectado a uma rede Wireless, e atuando como um servidor na porta 80. O acesso a esse servidor pode ser realizado através de um cliente. 
Ele executa comandos simples, que são enviados via protocolo TCP e acionam alguma funcionalidade de um Arduino Mega 2560. 

## Hardwares
### Microcontroladores
- ESP8266 (atuando como server)
- Arduino Mega 2560 (atuando como controlador dos periféricos)
  
### Sensores
- Módulo Relé 5v
- Sensor de temperatura e umidade DHT11

## Comandos
- __ligar lampada__    (define PIN13 como HIGH, acionando o relé e ligando a lâmpada)
- __desligar lampada__    (define PIN13 como LOW, desativando o relé e desligando a lâmpada)
- __temperatura__    (imprime a temperatura, umidade, ponto de orrvalho e status na tela do cliente)

## RPC
- Cliente Python <-> ESP8266 <-> MEGA2560 <-> Sensores

## RMI
- Cliente Java <-> Servidor Java <-> ESP8266 <-> MEGA2560 <-> Sensores

## Como implementar o projeto
### Arduino IDE
- Para utilização, baixe o [Arduino IDE](https://www.arduino.cc/en/software) no site oficial.
- Adicione ao projeto, as placas esp8266: https://github.com/esp8266/Arduino/releases/download/2.3.0/package_esp8266com_index.json
  e mega2560 (já inclusa no Arduino IDE).
### Gravação do ESP  
- Altere o código [esp.ino](https://github.com/Vitor-Ribe/webserverESPMega/blob/main/RPC/server/esp.ino), adicionando o SSID e Senha da sua rede local.
- Suba o código para o ESP8266.
- Abra o monitor serial do Arduino IDE e confira se o ESP foi inicializado e qual endereço IP lhe foi atribuído.
### Gravação do Mega
- Suba o código [mega.ino](https://github.com/Vitor-Ribe/webserverESPMega/blob/main/RPC/server/mega.ino) no Arduino Mega 2560.
### RPC
- Para a comunicação RPC, altere o [cliente python](https://github.com/Vitor-Ribe/webserverESPMega/blob/main/RPC/client/cliente.py) trocando o Host para o endereço IP do ESP.
- Execute o programa cliente, digite e envie os comandos.
### RMI
- Para a comunicação RMI, Altere o código [Server.java](https://github.com/Vitor-Ribe/webserverESPMega/blob/main/RMI/src/Server.java) trocando a String "ESP_IP" para o endereço IP do ESP.
- Para compilar: Abra um terminal na pasta do projeto, e execute o comando: `java *.java`.
- Execute o ServidorRMI com `java ServidorRMI`. Deverá aparecer a mensagem: "Servidor RMI iniciado"
- Abra um novo terminal na mesma pasta do projeto e execute: `java ClienteRMI`.
- Seu cliente já pronto e aguardando comandos.
## Observações
- O ESP consegue atuar como server e controlador ao mesmo tempo. Porém, dividir as tarefas com o Mega torna o projeto mais organizado. Além disso, o Mega possui mais pinos que podem ser usados para escalabilizar o projeto no futuro.
- Ao usar pela primeira vez, deve-se conectar o Hardware num dispositivo com o Arduino IDE e usar o monitor serial para ver o IP que foi atribuído pelo roteador (você pode optar por um IP estático, mexendo em algumas funções da biblioteca WiFi do ESP8266). Após isso, é necessário alterar a variável "Host" no código em Python do cliente.

