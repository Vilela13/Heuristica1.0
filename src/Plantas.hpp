/*
 * Plantas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef PLANTAS_HPP_
#define PLANTAS_HPP_

#include "Bibliotecas.hpp"


class Planta{

public:
	Planta();
	int NumeroVeiculos;
	ConjuntoCarretas VeiculosDaPlanta;
	vector < double > DistanciaConstrucoes;
	double TempoPlanta;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;


	~Planta();

};

Planta::Planta(){

}

Planta::~Planta(){

}


class ConjuntoPlantas{

public:
	ConjuntoPlantas();
	vector< Planta > Plantas;

	void IniciaConjuntoPlantas(int);

	~ConjuntoPlantas();
};

ConjuntoPlantas::ConjuntoPlantas(){

}

void ConjuntoPlantas::IniciaConjuntoPlantas(int Numero){
	Plantas.resize(Numero);

}

ConjuntoPlantas::~ConjuntoPlantas(){

}


#endif /* PLANTAS_HPP_ */
