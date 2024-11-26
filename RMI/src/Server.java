import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.io.*;
import java.net.*;

public class ServidorRMI extends UnicastRemoteObject implements InterfaceServidor {

    private static final String ESP_IP = "192.168.98.36"; // Substitua pelo IP do ESP
    private static final int ESP_PORT = 80;

    protected ServidorRMI() throws RemoteException {
        super();
    }

    @Override
    public String enviarComando(String comando) throws RemoteException {
        try (Socket socket = new Socket(ESP_IP, ESP_PORT);
             PrintWriter out = new PrintWriter(socket.getOutputStream(), true);
             BufferedReader in = new BufferedReader(new InputStreamReader(socket.getInputStream()))) {

            // Envia o comando para o ESP
            out.println(comando);

            // Recebe a resposta do ESP
            StringBuilder resposta = new StringBuilder();
            String linha;
            while ((linha = in.readLine()) != null) {
                resposta.append(linha).append("\n");
            }
            return resposta.toString().trim();

        } catch (IOException e) {
            e.printStackTrace();
            return "Erro ao comunicar com o ESP: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        try {
            Registry registry = LocateRegistry.createRegistry(1099); // Porta padrão RMI
            registry.rebind("ServidorRMI", new ServidorRMI());
            System.out.println("Servidor RMI iniciado.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
