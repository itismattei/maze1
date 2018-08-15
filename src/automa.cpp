

#include <list>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include "interval.h"

using namespace std;

#include "cella.h"
#include "TRcmd.h"
#include "define.h"
#include "automa.h"


int Automa::run(TxRxcmd &com, list<Cella> &L1){


  Cella Q1, Q2;
  Cella qTemp;
  unsigned int nextTime ;
  unsigned int microseconds = 600000;   //200 ms

  int d1,i;

  char buff[8] = "salve\0", buff1[8] = "\n";
  char ricBuff[256];

  L1.push_back(qTemp);

  cout << "ID Q1: " << Q1.printID() << endl;
  cout << "ID Q2: " << Q2.printID() << endl;

  /// apro un file in scrittura
	ofstream outF("dati.txt", ios::app);
	cout << "Test Comunicazione!" << endl;
	outF << "\nRegistrazione comunicazioni" << endl;
  int contatore = 0;

  /////
  ///// STATI DI AVVIO
  /////
  //stato = GASREAD;
  stato = RESET;
  //! ciclo principaleAD	256
  recordData = true;

  while(1){
    //! apre il debug su file
    outF.open("dati.txt", ios::app);
    ++contatore;
    int j;


    // 1
    switch(stato){
      case AVANZA:
        statoPrec = AVANZA;
        /// stampa i bytes che inviera'
        cout << contatore << " invio il comando 'F' ";
        outF << contatore <<" invio il comando 'F' ";
        /// AVANZA
        com.sendCmd('F');
        /// attende 5 ms
        nextTime = millis () + 5 ;
        while(millis() < nextTime);
        /// legge il buffer di ricezione e memorizza i bytes disponibili
        if(com.receiveCmd()){
          ///legge l'encoder
          com.sendCmd('D', 10);
          /// attende 5 ms
          nextTime = millis () + 5 ;
          while(millis() < nextTime);

          /// legge il buffer di ricezione e memorizza i bytes disponibili
          if (com.receiveCmd()){
            int valore = com.convertiDatoRaw();
            cout << endl <<  "encoder " << (valore - distEncoder) << endl;
            if ((valore - distEncoder) < 200 && (valore - distEncoder) > 100){
              if (recordData){
                /// registra i dati della cella
                recordData = false;
                registraCella(qTemp, com, outF);
                qTemp.upID();   // aggirna id della cella
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
        com.sendCmd('R');
        /// attende 5 ms
        nextTime = millis () + 5 ;
        while(millis() < nextTime);
        /// legge il buffer di ricezione e memorizza i bytes disponibili
        if (com.receiveCmd()){
          stato = SINISTRA;
        }
        else
          cout<< "errore di comunicazione"<< endl;
        cout << "stato " << stato << endl;
        sleep(2);

      break;


      case SINISTRA:
        ///legge l'encoder
        com.sendCmd('D', 10);
        /// attende 5 ms
        nextTime = millis () + 5 ;
        while(millis() < nextTime);

        /// legge il buffer di ricezione e memorizza i bytes disponibili

        if (com.receiveCmd()){
          int valore = com.convertiDatoRaw();
          cout << endl <<  "encoder " << valore << endl;
          distEncoder = valore;
          stato = 3;

        }
        else
          cout<< "errore di comunicazione"<< endl;

        sleep(1);
      break;

      case FINE:

        com.sendCmd('F');
        /// attende 5 ms
        nextTime = millis () + 5 ;
        while(millis() < nextTime);
        /// legge il buffer di ricezione e memorizza i bytes disponibili

        if (com.receiveCmd()){

          ///legge il sensore di gas
          com.sendCmd('D', 13);
          /// attende 5 ms
          nextTime = millis () + 5 ;
          while(millis() < nextTime);

          if (com.receiveCmd()){
            int valore = com.convertiDatoRaw();
            cout << "valore Alcool " << valore << endl;
            if(valore>3200){
              stato = FINE;
              cout << "stato " << stato << endl;
               }
                else
                stato = STOP;

              }
              else
                cout<< "errore di comunicazione"<< endl;
              /*printf("%d\n", PIPE.convertiDatoRaw());
              d1 = PIPE.convertiDatoRaw();
              outF << d1 << endl;
              if(d1 > 300){
                PIPE.sendCmd('F');

              }*/
            }

      break;


      case STOP:
        sleep(1);
        cout << "Fermo!" << endl;
        stato = STOP;
      break;

      case RESET:
        ///legge l'encoder
        com.sendCmd('D', 10);
        /// attende 5 ms
        nextTime = millis () + 5 ;
        while(millis() < nextTime);

        if (com.receiveCmd()){
          int valore = com.convertiDatoRaw();
          distEncoder = valore;
          cout <<  "encoder reset " << (distEncoder) << endl;
          stato = INIZIO;
          }
          else{
            cout<< "errore di comunicazione"<< endl;
            stato = STOP;
          }


        sleep(1);
        break;


      case GASREAD:
        ///legge il sensore di gas
        com.sendCmd('D', 13);
        /// attende 5 ms
        nextTime = millis () + 5 ;
        while(millis() < nextTime);

        if (com.receiveCmd()){
          int valore = com.convertiDatoRaw();
          cout << "valore Alcool " << valore << endl;

          stato = GASREAD;
        }
        else
          cout<< "errore di comunicazione"<< endl;

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


void Automa::registraCella(Cella &C, TxRxcmd &com, ofstream &outF){

    int nextTime;
    /// muro di sinistra
    stampa(outF, "invio il comando 'D' 2 ");
    com.sendCmd('D', 2);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    int d1, d2;
    /// legge il buffer di ricezione e memorizza i bytes disponibili

    if (com.receiveCmd()){
      d1 = com.convertiDatoRaw();
      cout << d1 << endl;
      outF << d1 << endl;
    }

    stampa(outF, "invio il comando 'D' 3 ");
    com.sendCmd('D', 3);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);

    /// legge il buffer di ricezione e memorizza i bytes disponibili

    if (com.receiveCmd()){
      d2 = com.convertiDatoRaw();
      cout << d2 << endl;
      outF << d2 << endl;
      if (d1 < SPAZIO_LIBERO || d2 < SPAZIO_LIBERO) {
        /// presenza del muro
        C.mLato[0] = 1;
      }
    }

    stampa(outF, "invio il comando 'D' 1 ");
    /// muro anteriore
    com.sendCmd('D', 1);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);

    if (com.receiveCmd()){
      d1 = com.convertiDatoRaw();
      cout << d1 << endl;
      outF << d1 << endl;
      if (d1 < SPAZIO_LIBERO_ANT) {
        /// presenza del muro anteriore
        C.mLato[1] = 1;
      }
    }

    /// muro di destra
    stampa(outF, "invio il comando 'D' 4 ");
    com.sendCmd('D', 4);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);
    /// legge il buffer di ricezione e memorizza i bytes disponibili

    if (com.receiveCmd()){
      d1 = com.convertiDatoRaw();
      cout << d1 << endl;
      outF << d1 << endl;
    }

    stampa(outF, "invio il comando 'D' 5 ");
    com.sendCmd('D', 5);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);

    /// legge il buffer di ricezione e memorizza i bytes disponibili
    if (com.receiveCmd()){
      d2 = com.convertiDatoRaw();
      cout << d2 << endl;
      outF << d2 << endl;
      if (d1 < SPAZIO_LIBERO || d2 < SPAZIO_LIBERO) {
        /// presenza del muro
        C.mLato[2] = 1;
      }
    }

    // qui si valuta la rotazione dell'asse di avanzamento rispetto all'angolo
    // iniziale
    // sensore 6: giroscopio
    stampa(outF, "invio il comando 'D' 6 ");
    com.sendCmd('D', 6);
    /// attende 5 ms
    nextTime = millis () + 10 ;
    while(millis() < nextTime);

    /// legge il buffer di ricezione e memorizza i bytes disponibili
    if (com.receiveCmd()){
      d2 = com.convertiDatoRaw();
      cout << d2 << endl;
      outF << d2 << endl;
      // l'angolo letto non sara' proprio un multiplo di 90 e va quindi
      // arrotondato
      C.mAngolo = rangeAngle(d2);
    }
}


void Automa::stampa(ofstream &outF, string stringa){
  cout << stringa << endl;
  outF << stringa;
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
