import socket

host = "192.168.100.189"  # IP do servidor (ESP)
port = 80  # Porta de comunicação (deve ser a mesma que o servidor usa)

def enviar_comando(comando):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(comando.encode())  # Envia o comando para o servidor
        resposta = s.recv(1024).decode()  # Recebe a resposta do servidor
        print(resposta)  # Exibe a resposta no cliente

while True:
    comando = input(": ")
    enviar_comando(comando)
