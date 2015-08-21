/*
 * Plantas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef PLANTAS_HPP_
#define PLANTAS_HPP_

#include "Bibliotecas.hpp"

class Carregamento{
public:
	double HorarioInicioCarregamento;
	double HorarioFinalCarregamento;
	Carreta* CarretaUtilizada;
};

class Planta{

public:
	Planta();
	int NumeroDaPlanta;
	int NumeroVeiculos;
	ConjuntoCarretas VeiculosDaPlanta;
	vector < double > DistanciaConstrucoes;
	double TempoPlanta;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;

	vector < Carregamento > Carregamentos;

	void Imprime();

	~Planta();

};

Planta::Planta(){
	NumeroVeiculos = -13;
	TempoPlanta = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
}

void Planta::Imprime(){
	cout << "# Planta " << NumeroDaPlanta << " com " << NumeroVeiculos << " veiculos, funciona de (";
	cout << TempoMinimoDeFuncionamento << ", "<< TempoMaximoDeFuncionamento << ")" << endl;

	if ( Carregamentos.size() != 0 ){
		cout << "   Carregamentos " << endl;
		for( int c = 0; c < Carregamentos.size(); c++){
			cout << "   ( "<< Carregamentos[c].HorarioInicioCarregamento << " , " << Carregamentos[c].HorarioFinalCarregamento << " ) " << endl;
		}
	}


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

bool DecideQualMenorInicioTempoCarregamento ( Carregamento c1, Carregamento c2 ){
	return ( c1.HorarioInicioCarregamento < c2.HorarioInicioCarregamento );
}

#endif /* PLANTAS_HPP_ */
