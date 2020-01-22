/*
 * esempio preso dal libro a pagina 135
 */

import java.io.*;
import java.net.*;
import java.util.*;

public class ClientStr {
    String nomeServer = "";
    int portaServer = 6789;
    Socket miosocket;
    BufferedReader tastiera;
    String stringaUtente;
    String stringaRicevutaDalServer;
    DataOutputStream outVersoServer;
    BufferedReader inDalServer;

    public Socket connetti() {

        System.out.println("CLIENT partito in esecuzione ...");
        try {
			//prt l'input da tastiera
			tastiera = new BufferedReader(new InputStreamReader(System.in));
			miosocket = new Socket(nomeServer, portaServer);
			//associo due oggetti al socket per effettuare la scrittura e la lettura
			outVersoServer = new DataOutputStream(miosocket.getOutputStream());
			inDalServer = new BufferedReader(new InputStreamReader(miosocket.getInputStream()));
        } catch (UnknownHostException ue) {
            System.err.println("Host sconosciuto");
        } catch (Exception e) {
            e.printStackTrace();
            System.exit(1);
        }

        return miosocket;
    }

    public void comunica() {
		do {
			try {
				System.out.println("... Inserisci la stringa da trasmettere al server"+'\n');
				stringaUtente = tastiera.readLine();
				//la spedisco al server
				System.out.println("... Invio la stringa al server e attendo ...");
				outVersoServer.writeBytes(stringaUtente+'\n');
				if(stringaUtente != null) {
					//leggo la risposta dal server
					stringaRicevutaDalServer = inDalServer.readLine();
					System.out.println("... Risposta dal server "+'\n'+stringaRicevutaDalServer);
				}
				else {
					//chiudo la connessione
					System.out.println("CLIENT: termina elaborazione e chiude connessione");
					miosocket.close();
				}
			} catch(Exception e) {
				e.printStackTrace();
				System.exit(1);
			}
		} while(stringaUtente != null);
    }

    public static void main(String args[]) {
        ClientStr cliente = new ClientStr();
        cliente.connetti();
        cliente.comunica();
    }
}
