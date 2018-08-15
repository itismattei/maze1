
/* classe che impelmenta una classe che mantiene una lettura di sensori */

#ifndef _SENSORI_H_
#define _SENSORI_H_

#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <iostream>
using namespace std;

class Sensori{
public:
  Sensori(){ for (int i = 0; i < 7; i++) valore[i] = 0; time(&timeStamp); }
  Sensori(const Sensori& S){ for (int i = 0; i < 7; i++) valore[i] = S.valore[i];
                              timeStamp = S.timeStamp;}

  /// da 0 a 4 sono i sensori di distanza
  /// 5 angolo
  /// 6 distanza distEncoder

  int valore[7];
  time_t timeStamp;

  inline void setTime(void){ time(&timeStamp); }
  void timeP(){ cout << "timestamp: " << timeStamp << endl;}
};

#endif
