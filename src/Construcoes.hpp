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

	~Construcao();

};

Construcao::Construcao(){

}

Construcao::~Construcao(){

}


class ConjuntoConstrucoes{

public:
	ConjuntoConstrucoes();
	vector< Construcao > ConstrucoesInstancia;

	void IniciaConjuntoConstrucoes(int);

	~ConjuntoConstrucoes();
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){

}

void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	ConstrucoesInstancia.resize(Numero);

}

ConjuntoConstrucoes::~ConjuntoConstrucoes(){

}



#endif /* CONSTRUCOES_HPP_ */
