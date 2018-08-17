
/* classe che impelmenta una classe che mantiene una lettura di sensori */

#ifndef _SENSORI_H_
#define _SENSORI_H_

#include <time.h>       /* time_t, struct tm, difftime, time, mktime */
#include <iostream>
#include <stdint.h>
#include <sys/time.h>       /* time_t, struct tm, difftime, time, mktime */
using namespace std;

class Sensori{
public:
  Sensori(){ for (int i = 0; i < 7; i++) valore[i] = 0; setTime(); }
  Sensori(const Sensori& S){ for (int i = 0; i < 7; i++) valore[i] = S.valore[i];
                              timeStamp = S.timeStamp; usec = S.usec;}
  Sensori & operator=(const Sensori & s);
  /// da 0 a 4 sono i sensori di distanza
  /// 5 angolo
  /// 6 distanza distEncoder

  int       valore[7];
  time_t    timeStamp;
  uint32_t  usec;

  inline void setTime(void){ //time(&timeStamp);
    struct timeval tempo;  gettimeofday(&tempo, NULL);
    timeStamp = tempo.tv_sec; usec = tempo.tv_usec;
  }
  void timeP(){ cout << "timestamp: " << timeStamp << endl;}
};

#endif
