import java.io.*;
import java.net.*;

public class Client{
    private Socket clientSocket;
    private PrintWriter out;
    private BufferedReader in;

    public void startConnection(String ip, int port){
        clientSocket = new Socket(ip, port);
        out = new PrintWriter(clientSocket.getOutputStream(), true);
        in = new BufferedReader(new InputStreamReader(client.Socket.getInputStream()));
    }

    public void stopConnection(){
        in.close();
        out.close();
        clientSocket.close();
    }

    public String addSocket(String IP, int port, int ms){
        StringBuilder str = new StringBuilder();
        str.append("ADD:");
        str.append(IP);
        str.append(":");
        str.append(port);
        str.append(":");
        str.append(ms);

        out.println(str);
    }

    public String deleteSocket(String IP, int port, int ms){
        StringBuilder str = new StringBuilder();
        str.append("DEL:");
        str.append(IP);
        str.append(":");
        str.append(port);
        str.append(":");
        str.append(ms);

        out.println(str);        
    }

    public static void main(String[] args){
        startConnection("185.85.188.58", 8888);
        addSocket("185.85.188.58", 1923, 500);
            
        while(){
            try{

               Thread.sleep(1000);     
            }catch(InterruptedException e){
                e.printStackTrace();
            }
        }

        stopConnection();
    }

}
