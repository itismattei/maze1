


#include "cella.h"

/*
 * cella.cpp
 *
 *  Created on: 07/mag/2017
 *      Author: tps8
 */

 /// inizializzazione di una proprieta' statica
int Cella::ID = 0;

Cella::Cella() {
	// TODO Auto-generated constructor stub
	mColore = 0;
	myID = ID += 1;
	mAngolo = 0;
	mC = mR = -100;
	//! inizializza i lati a 0 (liberi)
	for (int i = 0; i < 4; i++)
		mLato[i] = 0;
}

Cella::~Cella() {
	// TODO Auto-generated destructor stub
}

/// costruttore di copia
Cella::Cella( const Cella & q){
	if (this != & q){
		mColore = q.mColore;
		for (int i = 0 ; i < 4; i++)
		mLato[i]  = q.mLato[i];
		myID = q.myID;
		mC = q.mC;
		mR = q.mR;
		mAngolo = q.mAngolo;
		// la copia ha comunque identificatore differente
	}
}

///
/// operatore =
Cella& Cella::operator=(const Cella & q){

	if (this != &q){
		myID = q.myID;
		mC = q.mC;
		mR = q.mR;
		mAngolo = q.mAngolo;
		mColore = q.mColore;
		for (int i = 0; i < 4 ; i++)
			mLato[i] = q.mLato[i];

	}
	return *this;

}
