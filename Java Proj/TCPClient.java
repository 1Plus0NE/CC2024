// TCPClient.java
import java.net.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class TCPClient{
  public static void main(String[] args) throws IOException{
    // Criamos uma nova instância de socket para o cliente
    Socket clientSocket = new Socket("localhost", 9090);
    System.out.println("Conectado ao servidor!");

    // Troca de mensagens
    DataInputStream dataIn = new DataInputStream(clientSocket.getInputStream());
    DataOutputStream dataOut = new DataOutputStream(clientSocket.getOutputStream());

    // O cliente envia uma mensagem ao servidor
    String clientMessage = "Olá, mensagem do cliente!";
    dataOut.writeUTF(clientMessage);

    // O cliente recebe a mensagem do servidor
    String serverMessage = dataIn.readUTF();
    System.out.println("Servidor: " + serverMessage);

    dataIn.close();
    dataOut.close();
    clientSocket.close();
  }
}