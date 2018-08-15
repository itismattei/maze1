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

	L1.push_back(tc);
	L1.push_back(tc1);
	tc.upID();
	L1.push_back(tc);

	for(itC = L1.begin(); itC != L1.end(); ++itC){
		cout << "from iterator: " << (*itC).myID << endl;
	}
	exit(0);

	/// collego PIPE ad uart
	PIPE.connect(&uart);

  /// avvia l'esecuzione dell'automa
	if (A.run(PIPE, L1) != 0){
		cout << "Automa improvvisamente interrotto!" <<endl;
		exit (-1);
	}

	return 0;
}
