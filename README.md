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
  
## Observações
- O ESP consegue atuar como server e controlador ao mesmo tempo. Porém, dividir as tarefas com o Mega torna o projeto mais organizado. Além disso, o Mega possui mais pinos que podem ser usados para escalabilizar o projeto no futuro.
- Ao usar pela primeira vez, deve-se conectar o Hardware num dispositivo com o Arduino IDE e usar o monitor serial para ver o IP que foi atribuído pelo roteador (você pode optar por um IP estático, mexendo em algumas funções da biblioteca WiFi do ESP8266). Após isso, é necessário alterar a variável "Host" no código em Python do cliente.

