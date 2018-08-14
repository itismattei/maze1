/*
 * cercaLato.h
 *
 *  Created on: 20/mag/2017
 *      Author: tps8
 */

#ifndef CERCA_H_
#define CERCA_H_

#include "cella.h"


/// definisco una classe funzione cioè che effettua l'overloadd di ()
/// questo oggetto è un funtore o oggetto funzionale e potra' essere
/// usato come predicato nella find_if. Il predicato della find_if deve essere unario
/// e quindi non può essere del tipo : bool operator()(<typename T> , <typenanme T> ) {return
/// "confronto tra primo e secondo parametro"}
/// Il predicato deve essere del tipo bool operator()(<typename T>){ return ....}
/// Per ottenere ciò che vuole il compilatore occorre quindi che il parametro di confronto per un oggetto
/// generico sia già presente e cio' puo' accadere se e' gia' nella classe funzionale.
/// Il predicato può essere un puntatore a funzione: bool (* nome)(<typename T>) { return true; .....},
/// ma non aiuta poiché non si riesce a
/// passare il parametro di confronto. Per far ciò servirebbe un operatore binario che non è ammesso dalla find_if
/// esempio: itQuad = find_if(++itQuad, Vq.end(), cercaLato(10));


struct cercaLato {
public:

	/// Il costruttore mi permette di memorizzare nell'oggetto il parametro di confronto
	cercaLato(int valoreLato) : valore(valoreLato) {}
	int valore;
	/// ridefinisco l'operatore()
  /// quando viene usato nella find_if riceve il parametro su cui scorre l'iteratore della find_if
  /*
  template<class InputIt, class UnaryPredicate>
  InputIt find_if(InputIt first, InputIt last, UnaryPredicate p)
  {
      for (; first != last; ++first) {
          if (p(*first)) { // <- viene chiamato l'operatore () sull'ogetto p che ha come parametro
                           // in ingresso l'oggetto che sta nella lista.
              return first;
          }
      }
      return last;
  }
  */
	inline bool operator()(Cella &q) const { for (int i = 0; i < 4; i++) if (valore == q.mLato[i]) return true;
										return false;}

	~cercaLato();
};

/// Notare l'uso di class ppure di struct
struct cercaRiga {
public:

	/// Il costruttore mi permette di memorizzare nell'oggetto il parametro di confronto
	cercaRiga(int valoreR) : valore(valoreR) {}
	int valore;
	/// ridefinisco l'operatore()
	bool operator()(Cella &q) const { if (valore == q.mR) return true;
										return false;}

};

///oggettto funzionale per ricerca dei vaori di riga e colonna nella list
class cercaPos{
public:
	cercaPos(int R, int C): riga(R), col(C) {}
	int riga;
	int col;

	/// ridefinizione operatore()
	bool operator()(Cella &q) const {if (riga == q.mR && col == q.mC)
										return true;
										else return false;
										}
};

#endif /* CERCA_H_ */
