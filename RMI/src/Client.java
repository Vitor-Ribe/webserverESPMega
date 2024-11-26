import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.util.Scanner;

public class ClienteRMI {

    public static void main(String[] args) {
        try {
            // Conecta ao servidor RMI
            Registry registry = LocateRegistry.getRegistry("localhost", 1099); // Substitua localhost pelo IP do servidor se necessário
            InterfaceServidor servidor = (InterfaceServidor) registry.lookup("ServidorRMI");

            Scanner scanner = new Scanner(System.in);
            String comando;

            System.out.println("Cliente RMI iniciado. Digite os comandos ('sair' para encerrar):");
            while (true) {
                System.out.print("\nComando: ");
                comando = scanner.nextLine();

                if (comando.equalsIgnoreCase("sair")) {
                    break;
                }

                // Envia o comando e recebe a resposta
                String resposta = servidor.enviarComando(comando);
                System.out.println("\nResposta do Servidor:\n" + resposta);
            }

            scanner.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
