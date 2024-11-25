import java.rmi.Naming;

public class Client {
    public static void main(String[] args) {
        try {
            // Conectando ao servidor RMI
            RemoteInterface stub = (RemoteInterface) Naming.lookup("rmi://localhost/ServidorRMI");

            // Enviar comandos
            System.out.println(stub.enviarComando("ligar lampada"));
            
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
