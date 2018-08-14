
#ifndef _DEFINE_H_
#define _DEFINE_H_

//#define		RESET 		      255
#define		GASREAD		      256
//#define		STOPP			      4
#define  	CERCAGAS    	  0x8D
//#define   AVANZAM         0
//#define   CAMPIONACELLA   1
//#define   DESTRAD         15

enum STATI{
  INIZIO,  FINE, AVANZA, DESTRA, SINISTRA, STOP, CAMPIONACELLA, RESET
};


#endif //_DEFINE_H_
