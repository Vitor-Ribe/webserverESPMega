import java.rmi.Remote;
import java.rmi.RemoteException;

public interface InterfaceServidor extends Remote {
    String enviarComando(String comando) throws RemoteException;
}
