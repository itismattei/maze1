

#include <list>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include "interval.h"

using namespace std;

#include "cella.h"
#include "TRcmd.h"
#include "define.h"
#include "automa.h"


int Automa::run(list<Cella> &L1){

  Cella     qTemp;
  Sensori   S;
  unsigned int nextTime ;
  unsigned int microseconds = 600000;   //200 ms

  int d1,i;

  char buff[8] = "salve\0", buff1[8] = "\n";
  char ricBuff[256];

  L1.push_back(qTemp);

  if (COM == NULL){
    /// manca il canale di Comunicazione
    cerr << "canale di comunicazione assente" << endl;
    exit(-2);
  }

  /// apro un file in scrittura
	ofstream outF("dati.txt", ios::app);
	cout << "Test Comunicazione!" << endl;
	outF << "\nRegistrazione comunicazioni" << endl;
  int contatore = 0;

  /////
  ///// STATI DI AVVIO
  /////
  //stato = GASREAD;
  stato = AVANZA;
  //! ciclo principaleAD	256
  recordData = true;

  while(1){
    //! apre il debug su file
    outF.open("dati.txt", ios::app);
    ++contatore;

    recordData = isToRecord();

    // 1
    switch(stato){
      case AVANZA:
        statoPrec = AVANZA;
        /// stampa i bytes che inviera'
        cout << contatore << " invio il comando 'F' ";
        outF << contatore <<" invio il comando 'F' ";
        /// AVANZA
        COM->sendCmd('F');
        /// attende 5 ms
        sleepMs(5); /// verificarne il reale funzionamento. Finisce di inviare
        // il comando oppure si ferma prima????
        //nextTime = millis () + 5 ;
        //while(millis() < nextTime);
        /// legge il buffer di ricezione e memorizza i bytes disponibili
        if(COM->receiveCmd()){
          /// avendo ricevuto conferma dell'avanzamento si mette a riposo
          /// per 200 ms
          sleepMs(200);
          /// legge tutti i Sensori e memorizza il risultato in VS1
          /// restituisce una copia delle letture in S
          leggiSensori(S);

          /// legge il buffer di ricezione e memorizza i bytes disponibili
          if (COM->receiveCmd()){
            int valore = COM->convertiDatoRaw();
            cout << endl <<  "encoder " << (valore - distEncoder) << endl;
            if ((valore - distEncoder) < 200 && (valore - distEncoder) > 100){
              if (recordData){
                /// registra i dati della cella
                recordData = false;
                registraCella(qTemp, S, outF);
                L1.push_back(qTemp);
              }
            }
            if ((valore - distEncoder) > 270){
              stato = DESTRA;
              cout << "stato " << stato << endl;
              distEncoder = valore;
            }
            else
              stato = AVANZA;
          }
          else

            cout<< "errore di comunicazione"<< endl;
        }
      break;

      case DESTRA:

      break;


      case SINISTRA:

        sleep(1);
      break;

      case FINE:



      break;


      case STOP:

        sleep(1);
        break;


      case GASREAD:
        ///legge il sensore di gas

        sleep(1);
      break;

    }/// switch(stato)


  /*		// 2
    printf("%d invio il comando 'D' 2 ", contatore);
    outF << contatore <<" invio il comando 'D' 2 ";
    PIPE.sendCmd('D', 2);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j){
      printf("%d\n", PIPE.convertiDatoRaw());
      outF << PIPE.convertiDatoRaw() << endl;
    }

    // 3
    printf("%d invio il comando 'D' 3 ", contatore);
    PIPE.sendCmd('D', 3);
    /// attende 5 ms
    nextTime = millis () + 20 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j)
      printf("%d\n", PIPE.convertiDatoRaw());

    // 4
    printf("%d invio il comando 'D' 4 ", contatore);
    PIPE.sendCmd('D', 4);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j)
      printf("%d\n", PIPE.convertiDatoRaw());

    // 5
    printf("%d invio il comando 'D' 5 ", contatore);
    PIPE.sendCmd('D', 5);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j)
      printf("%d\n", PIPE.convertiDatoRaw());

    // 6 giroscopio
    printf("----\n%d invio il comando 'D' 6 ", contatore);
    outF << "----\n";
    outF << contatore <<" invio il comando 'D' 6 ";
    PIPE.sendCmd('D', 6);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j){
      printf("%d\n", PIPE.convertiDatoRaw());
      outF << PIPE.convertiDatoRaw() << endl;
    }

    // 7 luminosita'
    printf("----\n%d invio il comando 'D' 7 ", contatore);
    outF << "----\n";
    outF << contatore <<" invio il comando 'D' 7 ";
    PIPE.sendCmd('D', 7);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j){
      printf("%d\n", PIPE.convertiDatoRaw());
      outF << PIPE.convertiDatoRaw() << endl;
    }

    // 12 audio
    printf("----\n%d invio il comando 'D' 12 ", contatore);
    outF << "----\n";
    outF << contatore <<" invio il comando 'D' 12 ";
    PIPE.sendCmd('D', 12);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j){
      printf("%d\n", PIPE.convertiDatoRaw());
      outF << PIPE.convertiDatoRaw() << endl;
    }

    // 13 gas
    printf("----\n%d invio il comando 'D' 13 ", contatore);
    outF << "----\n";
    outF << contatore <<" invio il comando 'D' 13 ";
    PIPE.sendCmd('D', 13);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j){
      printf("%d\n", PIPE.convertiDatoRaw());
      outF << PIPE.convertiDatoRaw() << endl;
    }


    // 10 distnaza
    printf("----\n%d invio il comando 'D' 10 ", contatore);
    outF << "----\n";
    outF << contatore <<" invio il comando 'D' 10 ";
    PIPE.sendCmd('D', 10);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili
    j = PIPE.receiveCmd();
    if (j){
      printf("%d\n", PIPE.convertiDatoRaw());
      outF << PIPE.convertiDatoRaw() << endl;
    }

  */
    printf("*** ***\n");
    outF << "*** ***" << endl;
    outF.close();
    //sleep(1);
    usleep(100000);
  } /// while(1)
  return 0;
}

//! Assegna la disposizione degli ostacoli, l'agolo di percorrenza rispetto
//! al sistema di riferimento assoluto, le coordinate di cella.
void Automa::registraCella(Cella &C, Sensori &s, ofstream &outF){

  /// muro di sinistra
  if (s.valore[1] < SPAZIO_LIBERO || s.valore[2] < SPAZIO_LIBERO) {
    /// presenza del muro
    C.mLato[0] = 1;
  }

  if (s.valore[0] < SPAZIO_LIBERO_ANT) {
    /// presenza del muro anteriore
    C.mLato[1] = 1;
  }

  if (s.valore[3] < SPAZIO_LIBERO || s.valore[4] < SPAZIO_LIBERO) {
    /// presenza del muro
    C.mLato[2] = 1;
  }
    int nextTime;
  // l'angolo letto non sara' proprio un multiplo di 90 e va quindi
  // arrotondato
  C.mAngolo = rangeAngle(s.valore[5]);

  /// valuta se e' la prima cella ad essere memorizzata oppure una successiva
  if (Prec.mR == -100)
    /// prima registrazione
    C.mR = C.mC = 0;
  else
    /// registrazioni successive
    setCoordCella(C);

  C.upID();   // aggirna id della cella
  Prec = C;  /// copia la cella attuale in quella precedente
  gettimeofday(&tempo, NULL); // imposta il timestamp attuale
  /// stampa un po' di output su file di log
  outF << "Registata cella R: " << C.mR << " C: " << C.mC;
  outF << "angolo: " <<C.mAngolo <<  " | ts: " << tempo.tv_sec << endl;
}


void Automa::stampa(ofstream &outF, string stringa){
  cout << stringa << endl;
  outF << stringa << endl;
}


/*! \fn void Automa::rangeAngle(int);
 *  \brief Centra nell'intervallo l'angolo al valore piu' prossimo al multiplo di 90°.
 *  \param int.
 *  \return int: angolo arrotondato
 */
int Automa::rangeAngle(int val){

  if (val < 95 && val > 85)
    return 90;

  if (val < 185 && val > 175)
    return 180;

  if (val < -85 && val > -95)
    return -90;

  if (val < -175 && val > -185)
    return -180;

  if (val < 275 && val > 265)
    return 270;
}

//! Legge tutti i sensori e memorizza il risultato in una classe che e'
//! poi immagazzinata in un std::vector, insieme alla marca temporale
void Automa::leggiSensori(Sensori &S){
  int d2;
  unsigned int nextTime ;
  // legge tutti i sensori, assegna un time stamp e li memorizza nel vettore S1
  for (int i = 0; i < 6; i++){
    //stampa(outF, "invio il comando 'D' 3 ");
    COM->sendCmd('D', i);
    /// attende 5 ms
    //sleepMs(5);
    nextTime = millis () + 5 ;
    while(millis() < nextTime);

    /// legge il buffer di ricezione e memorizza i bytes disponibili
    if (COM->receiveCmd()){
      d2 = COM->convertiDatoRaw();
      S.valore[i] = d2;
    }
    else
      S.valore[i] = -30000;
  }
  /// legge l'encoder
  COM->sendCmd('D', 10);
  /// attende 5 ms
  //sleepMs(5);
  nextTime = millis () + 5 ;
  while(millis() < nextTime);

  /// legge il buffer di ricezione e memorizza i bytes disponibili
  if (COM->receiveCmd()){
    d2 = COM->convertiDatoRaw();
    S.valore[6] = d2;
  }
  else
    S.valore[6] = -30000;

  S.setTime();  // imposta il timestamp
  VS1.push_back(S);
}

//! Imposta le coordinate di cella confrontando da quella precedente
//! e dall'angolo di orientamento.
void Automa::setCoordCella(Cella &C){
  /*
  0°      :   xk+1 = xk      ===  yk+1 = yk + 1
  90°     :   xk+1 = xk + 1  ===  yk+1 = yk
  -90°    :   xk+1 = xk - 1  ===  yk+1 = yk
  +/-180° :   xk+1 = xk      ===  yk+1 = yk - 1
  */
  switch(C.mAngolo){

    case 0:
      C.mR = Prec.mR; C.mC = Prec.mC + 1;
    break;

    case 90:
      C.mR = Prec.mR + 1; C.mC = Prec.mC;
    break;

    case -90:
      C.mR = Prec.mR - 1; C.mC = Prec.mC;
    break;

    case 180:
    case -180:
      C.mR = Prec.mR; C.mC = Prec.mC - 1;
    break;

    default:
    cout << " Impossibile assegnare le coordinate di cella" << endl;
  }
}

/*! \fn void Automa::isToRecord(void);
 *  \brief Algoritmo che stabilisce quando e' ora di registrare una cella.
 *  \param int.
 *  \return void
 */
int Automa::isToRecord(void){

  /*  per capire se una cella e' nuova rispetto alla precedente si potrebbero usare
  *   i seguenti criteri:
  *   1. differenza di lunghezza misurata dall'encoder,
  *   2. differenza di lunghezza registata dal sensore 1
  *   Dati da usare:
  *   a. std::vector VS1 aggiornata ad ogni lettura sui sensori e con indicazione
          del timeStamp
      b. std::list L1 come parametro del metodo run() che contiene tutte le celle
          registrate. Il caricamento avviene con push_back e quindi l'ultima Cella
          della lista e' anche l'ultima cella caricata.
      c. un copia dell'ultima cella registrata e' presente nell'oggetto Cella
          denominato Prec
  */

  /// controlla il tempo attuale con quello dell'ultima lettura dei Sensori
  uint64_t usecSTime, usec;
  int numElem = VS1.size();
  Sensori S_0, S_1;
  if (numElem > 1)
    S_0 = VS1[numElem - 2];
  if (numElem > 0)
    S_1 = VS1[numElem - 1];
  gettimeofday(&tempo, NULL);
  usecSTime = S_1.timeStamp * 1000000 + S_1.usec;
  usec = tempo.tv_sec * 1000000 + tempo.tv_usec;
  if (usec - usecSTime > 100000){
    // sono passati piu' di 100 ms e serve campionare i sensori
    S_0 = S_1;
    leggiSensori(S_1);  ///aggiorna anche VS1 inserendo l'elemento in fondo
  }
  /// S_0 ed S_1 contengono le ultime due letture ma non sono associati a nessuna
  /// cella e quindi con le utlime due letture potrei vendere sempre una distanza
  /// inferiore alla lunghezza di cella e sbagliare deducendo che non ho mai
  /// cambiato cella.
}
