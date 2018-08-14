

#ifndef _AUTOMA_H_
#define _AUTOMA_H_

//! viene realizzata la sclasse automa che gestisce il movimento,  le
//! misurazioni del drone e il caricamento dei dati nelle liste del percorso

#include "define.h"

class Automa {

public:
  Automa(){ stato = statoPrec = INIZIO; distEncoder = 0;}
  int run(TxRxcmd &);
  void registraCella(Cella &, TxRxcmd &, ofstream &);

  int stato;
  int statoPrec;

  //! distanze
  int distEncoder;
  //! registra dati cella
  int recordData;
};

#endif  //_AUTOMA_H_
