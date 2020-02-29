/* MIT License*/
/* */
/* Copyright (c) 2020 Lince99*/
/* */
/* Permission is hereby granted, free of charge, to any person obtaining a copy*/
/* of this software and associated documentation files (the "Software"), to deal*/
/* in the Software without restriction, including without limitation the rights*/
/* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell*/
/* copies of the Software, and to permit persons to whom the Software is*/
/* furnished to do so, subject to the following conditions:*/
/* */
/* The above copyright notice and this permission notice shall be included in all*/
/* copies or substantial portions of the Software.*/
/* */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR*/
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,*/
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE*/
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER*/
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,*/
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE*/
/* SOFTWARE.*/

/*
 * 
 * fonti:
 * https://stackoverflow.com/questions/2541597/how-to-gracefully-handle-the-sigkill-signal-in-java
 */

/* 
//gestice CTRL+C
Runtime.getRuntime().addShutdownHook(
	new Thread() {
		@Override
		public void run() {
			System.out.println("\nCTRL+C rilevato ...");
			//chiude connessioni
		}
	}
);
*/

import java.io.*;
import java.net.*;
import java.util.*;

public class ServerStr {
	
    ServerSocket server = null;
    Socket client = null;
    String client_header = null;
    String webpage = null;
    BufferedReader buffer_in;
    DataOutputStream buffer_out;
    
    public Socket listen(int port) {
		try {
			//TODO
		} catch() {
			
		}
		return client;
	}

    //public Socket attendi(int port) {

        //try {
            //System.out.println("SERVER partito in esecuzione ...");
            ////creo un server sulla porta 6789
            //server = new ServerSocket(port);
            ////rimane in attesa di un client
            //client = server.accept();
            ////chiudo il server per inibire altri client
            //server.close();
            ////associo due oggetti al socket del client per effettuare la scrittura e la lettura
            //inDalClient = new BufferedReader(new InputStreamReader(client.getInputStream()));
            //outVersoClient = new DataOutputStream(client.getOutputStream());
        //} catch(Exception e) {
            //e.printStackTrace();
            //System.exit(1);
        //}

        //return client;
    //}

    //public void comunica() {
		//do {
			//try {
				////rimango in attesa della riga trasmessa dal client
				//System.out.println("Benvenuto client, scrivi una frase e la trasformo in maiuscola. Attendo ...");
				//stringaRicevuta = inDalClient.readLine();
				////gestice CTRL+D
				//if(stringaRicevuta != null) {
					//System.out.println("Ricevuta la stringa dal client : "+stringaRicevuta);
					////la modifico e la spedisco al client
					//stringaModificata = stringaRicevuta.toUpperCase();
					//System.out.println("Invio la stringa modificata al client ...");
					//try {
						//outVersoClient.writeBytes(stringaModificata+'\n');
					//} catch(SocketException e) {
						//System.out.println("Client disconnesso con CTRL+D ...");
						//client.close();
						//System.exit(0);
					//}
				//}
				//else {
					//System.out.println("EOF ricevuto, chiusura connessione ...");
					////termina elaborazione sul server : chiudo la connessione del client
					//System.out.println("SERVER: fine elaborazione ...");
					//client.close();
				//}
			//} catch(Exception e) {
				//e.printStackTrace();
			//}
		//} while(stringaRicevuta != null);
    //}

    public static void main(String args[]) throws InterruptedException {
		ServerStr servente = new ServerStr();
		int port = 8080; //porta di default
        
        if(args.length > 0)
			port = Integer.parseInt(args[0]);
		System.out.println("Server listening in port "+port);
        
        servente.attendi();
        //attende client successivi
        while(true) {
            servente.comunica();
        }
    }
}
