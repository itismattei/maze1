
#include "sensori.h"

/// operatore=

Sensori & Sensori::operator=(const Sensori & S){

  if (this != &S){
    for (int i = 0; i < 7; i++)
      valore[i] = S.valore[i];

    timeStamp = S.timeStamp;
    usec = S.usec;

  }
  return *this;
}
