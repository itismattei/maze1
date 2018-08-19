/*
 * Questo programma implementa un automa di controllonvia
 * per rover.
 */


#include <iostream>
#include <fstream>
using namespace std;

#include "SerialComm.h"
#include "TRcmd.h"
#include "cella.h"
#include "automa.h"
#include <stdio.h>
#include <stdlib.h>
#include <wiringSerial.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>

#include <unistd.h>
#include "interval.h"
#include <dirent.h>

#include <list>

#include <stdio.h>      /* printf */
#include <sys/time.h>       /* time_t, struct tm, difftime, time, mktime */

/// programma principale
///



int main(){

	SerialComm uart;
	TxRxcmd PIPE;
	Automa A;
	list<Cella> L1;
	list<Cella>::iterator itC;
	Cella tc, tc1;


	cout << tc.myID << endl;
	cout << tc1.myID << endl;

	millisInit();
  time_t timer;
	cout << "millis " << millis() << endl;
	sleepMs(50);
	cout << "millis " << millis() << endl;

	struct timeval tempo;
  struct tm y2k = {0};
	struct tm * timeinfo;
  double seconds;


  y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
  y2k.tm_year = 100; y2k.tm_mon = 0; y2k.tm_mday = 1;

  // timestamp
  //time(&timer);  /* get current time; same as: timer = time(NULL)  */
	gettimeofday(&tempo, NULL);
	timer = tempo.tv_sec;
  timeinfo = localtime (&timer);
	cout << (int)timer << " " << timeinfo->tm_mday << "/" << timeinfo->tm_mon << endl;
	cout << timeinfo->tm_year + 1900 << " " << timeinfo->tm_hour << " " <<timeinfo->tm_min << endl;
  cout << asctime(timeinfo) << endl;
	//gettimeofday(&tempo, NULL);
	cout << timeinfo->tm_sec << " ";
	cout << tempo.tv_sec << " " << tempo.tv_usec << endl;
	/// la differenza tra tv_sec fornisce il tempo in secondi; la differenza tra
	/// tv_usec fornisce la differenza in microsecondi

	L1.push_back(tc);
	L1.push_back(tc1);
	tc.upID();
	L1.push_back(tc);

	for(itC = L1.begin(); itC != L1.end(); ++itC){
		cout << "from iterator: " << (*itC).myID << endl;
	}



	/// collego PIPE ad uart
	PIPE.connect(&uart);
	/// passo il PIPE al metodo run();
	A.setCOM(&PIPE);
	A.run(L1);
	exit(0);

  /// avvia l'esecuzione dell'automa
	if (A.run(L1) != 0){
		cout << "Automa improvvisamente interrotto!" <<endl;
		exit (-1);
	}

	return 0;
}
