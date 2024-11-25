import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.net.Socket;
import java.io.PrintWriter;

public class Server extends UnicastRemoteObject implements RemoteInterface {
    protected Server() throws RemoteException {
        super();
    }

    @Override
    public String enviarComando(String comando) throws RemoteException {
        try {
            // Conectando ao ESP (substitua pelo IP do ESP)
            Socket socket = new Socket("192.168.100.189", 80);
            PrintWriter out = new PrintWriter(socket.getOutputStream(), true);

            // Enviando o comando
            out.println(comando);
            socket.close();
            return "Comando enviado: " + comando;
        } catch (Exception e) {
            return "Erro ao enviar comando: " + e.getMessage();
        }
    }

    public static void main(String[] args) {
        try {
            java.rmi.registry.LocateRegistry.createRegistry(1099); // Porta padrão do RMI
            Server server = new Server();
            java.rmi.Naming.rebind("ServidorRMI", server);
            System.out.println("Servidor RMI iniciado...");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
