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
