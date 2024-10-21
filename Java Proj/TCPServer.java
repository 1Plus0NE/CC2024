// TCPServer.java

import java.net.*;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;

public class TCPServer{
  public static void main(String[] args) throws IOException{
    // Criamos uma nova instância do socket
    ServerSocket serverSocket = new ServerSocket(9090);
    System.out.println("Listening for clients...");
    Socket clientSocket = serverSocket.accept();
    String clientSocketIP = clientSocket.getInetAddress().toString();
    int clientSocketPort = clientSocket.getPort();
    System.out.println("[IP: " + clientSocketIP + " ,Port: " + clientSocketPort +"]  " + "Conexão com o cliente com sucesso!");

    // Troca de mensagens
    DataInputStream dataIn = new DataInputStream(clientSocket.getInputStream());
    DataOutputStream dataOut = new DataOutputStream(clientSocket.getOutputStream());

    // O servidor recebe a mensagem do cliente
    String clientMessage = dataIn.readUTF();
    System.out.println(clientMessage);
    // O servidor envia uma mensagem ao cliente
    String serverMessage = "Olá, mensagem do servidor!";
    dataOut.writeUTF(serverMessage);

    dataIn.close();
    dataOut.close();
    serverSocket.close();
    clientSocket.close();

  }
}