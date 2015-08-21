/*
 * Carretas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CARRETAS_HPP_
#define CARRETAS_HPP_

#include "Bibliotecas.hpp"

class Deslocamento{
public:
	double HorarioInicioDeslocamento;
	double HorarioFinalDeslocamento;

};

class Carreta{

public:
	Carreta();
	int NumerosDaCarreta;
	vector < vector < double > > TempoParaDescarregarNaConstrucao;

	vector < Deslocamento > Deslocamentos;



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
	for(int v = 0; v < Numero; v++){
		Carretas[v].NumerosDaCarreta = v + 1;
	}

}

ConjuntoCarretas::~ConjuntoCarretas(){

}


bool DecideQualMenorInicioTempoDeslocamento ( Deslocamento c1, Deslocamento c2 ){
	return ( c1.HorarioInicioDeslocamento < c2.HorarioInicioDeslocamento );
}


#endif /* CARRETAS_HPP_ */
