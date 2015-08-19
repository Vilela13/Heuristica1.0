/*
 * Construcoes.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CONSTRUCOES_HPP_
#define CONSTRUCOES_HPP_

#include "Bibliotecas.hpp"



class Construcao{

public:
	Construcao();
	int NumeroDemandas;
	vector < double > DistanciaPlantas;
	double TempoMaximoEntreDescargas;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;

	~Construcao();

};

Construcao::Construcao(){

}

Construcao::~Construcao(){

}


class ConjuntoConstrucoes{

public:
	ConjuntoConstrucoes();
	vector< Construcao > Construcoes;

	void IniciaConjuntoConstrucoes(int);

	~ConjuntoConstrucoes();
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){

}

void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	Construcoes.resize(Numero);

}

ConjuntoConstrucoes::~ConjuntoConstrucoes(){

}



#endif /* CONSTRUCOES_HPP_ */
