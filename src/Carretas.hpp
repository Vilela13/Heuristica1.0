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

	~Carreta();

};

Carreta::Carreta(){

}

Carreta::~Carreta(){

}


class ConjuntoCarretas{

public:
	ConjuntoCarretas();
	vector< Carreta > CarretasInstancia;

	void IniciaConjuntoCarretas(int);

	~ConjuntoCarretas();
};

ConjuntoCarretas::ConjuntoCarretas(){

}

void ConjuntoCarretas::IniciaConjuntoCarretas(int Numero){
	CarretasInstancia.resize(Numero);

}

ConjuntoCarretas::~ConjuntoCarretas(){

}



#endif /* CARRETAS_HPP_ */
