
#ifndef _CELLA_H_
#define _CELLA_H_

#include <vector>

using namespace std;

class Cella {
public:
	Cella();
	Cella( const Cella& );
	virtual ~Cella();

	Cella& operator=(const Cella & q);
  inline int const printID(){ return myID; }
	/// imposta il valore del lato (si intende occupato)
	inline void setLato(int lato, int valore){ if (lato < 4 && lato > 0) mLato[lato] = valore;}
	inline int getLato(int lato) { if (lato < 4 && lato > 0) return mLato[lato]; }

public:

	int mLato[4];
	int mColore;
	static int ID;
	int myID;
	int mR;			/// numero riga
	int mC;			/// numero colonna
	int mAngolo;	/// angolo rispetto al  rif assoluto della cella numero 1
};





#endif //_CELLA_H_
