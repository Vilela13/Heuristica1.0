/*
 * Carretas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CARRETAS_HPP_
#define CARRETAS_HPP_

#include "Bibliotecas.hpp"



class Carreta{

public:
	Carreta();
	vector < vector < double > > TempoConstrucao;

	~Carreta();

};

Carreta::Carreta(){

}

Carreta::~Carreta(){

}


class ConjuntoCarretas{

public:
	ConjuntoCarretas();
	vector< Carreta > Carretas;

	void IniciaConjuntoCarretas(int);

	~ConjuntoCarretas();
};

ConjuntoCarretas::ConjuntoCarretas(){

}

void ConjuntoCarretas::IniciaConjuntoCarretas(int Numero){
	Carretas.resize(Numero);

}

ConjuntoCarretas::~ConjuntoCarretas(){

}



#endif /* CARRETAS_HPP_ */
