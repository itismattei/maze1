

#ifndef _AUTOMA_H_
#define _AUTOMA_H_

//! viene realizzata la sclasse automa che gestisce il movimento,  le
//! misurazioni del drone e il caricamento dei dati nelle liste del percorso

#include "define.h"
#include <string>
#include <list>

class Automa {

public:
  Automa(){ stato = statoPrec = INIZIO; distEncoder = 0;}
  int run(TxRxcmd &, list<Cella> &);
  void registraCella(Cella &, TxRxcmd &, ofstream &);

  int stato;
  int statoPrec;

  //! distanze
  int distEncoder;
  //! registra dati cella
  int recordData;

private:
  /*! \fn void Automa::stampa(ofstream &, string);
   *  \brief Stampa su file e a video.
   *  \param ofstream e string.
   *  \return void
   */
  void stampa(ofstream &, string);
  /*! \fn void Automa::rangeAngle(int);
   *  \brief Centra nell'intervallo l'angolo al valore piu' prossimo al multiplo di 90°.
   *  \param int.
   *  \return int: angolo arrotondato
   */
  int rangeAngle(int);
};

#endif  //_AUTOMA_H_
