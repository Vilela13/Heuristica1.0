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
	int NumeroConstrucao;
	int NumeroDemandaSuprida;
	int NumCarretaUtilizada;
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

	int VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao);
	void AlocaAtividade(double , double, int , int , int);

	void Imprime();

	void ImprimeDistancias();

	~Planta();

};

Planta::Planta(){
	NumeroDaPlanta = -13;
	NumeroVeiculos = -13;
	TempoPlanta = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
}

int Planta::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( FinalPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	for( unsigned int c = 0; c < Carregamentos.size(); c++){
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao >= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao <= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if( FinalPossivelAlocacao > Carregamentos[c].HorarioInicioCarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Carregamentos[c].HorarioFinalCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
	}
	return 1;
}

void Planta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
	Carregamento CarregamentoAux;

	CarregamentoAux.HorarioInicioCarregamento = HoraInicio;
	CarregamentoAux.HorarioFinalCarregamento = HoraFinal;
	CarregamentoAux.NumeroConstrucao = NumConstrucao;
	CarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	CarregamentoAux.NumCarretaUtilizada = Carreta;

	Carregamentos.push_back(CarregamentoAux);
}

void Planta::Imprime(){
	cout << endl;
	cout << "# Planta " << NumeroDaPlanta << " com " << NumeroVeiculos << " veiculos, funciona de (";
	cout << TempoMinimoDeFuncionamento << ", "<< TempoMaximoDeFuncionamento << ")" << endl;

	if ( Carregamentos.size() != 0 ){
		cout << "   Carregamentos " << endl;
		for( unsigned int c = 0; c < Carregamentos.size(); c++){
			cout << "    * Caminhao [" << NumeroDaPlanta << "-" << Carregamentos[c].NumCarretaUtilizada;
			cout << "] para suprir construcao [" << Carregamentos[c].NumeroConstrucao << "-" << Carregamentos[c].NumeroDemandaSuprida;
			cout << "] das ( "<< Carregamentos[c].HorarioInicioCarregamento << " as " << Carregamentos[c].HorarioFinalCarregamento << " ) " << endl;
		}
	}

	cout <<  "    =>  Veiculos da Planta " << NumeroDaPlanta << " <= " << endl;
	VeiculosDaPlanta.Imprime();

}

void Planta::ImprimeDistancias(){
	cout << " +++ Distancias ++++ " << endl;
	cout << "Numero de conatricoes " << DistanciaConstrucoes.size() << endl;
	for ( unsigned int c = 0; c < DistanciaConstrucoes.size(); c++){
		cout << "   Contrucao" << c << " = "<< DistanciaConstrucoes[c] << endl;
	}
}

Planta::~Planta(){

}


class ConjuntoPlantas{

public:
	ConjuntoPlantas();
	vector< Planta > Plantas;

	void IniciaConjuntoPlantas(int);

	void Imprime();


	~ConjuntoPlantas();
};

ConjuntoPlantas::ConjuntoPlantas(){

}

void ConjuntoPlantas::IniciaConjuntoPlantas(int Numero){
	Plantas.resize(Numero);

}

void ConjuntoPlantas::Imprime(){
	cout << endl << endl << " [[[[[[  Imprime plantas  ]]]]]]" << endl;
	for( unsigned int p = 0; p < Plantas.size(); p++){
		Plantas[p].Imprime();
	}
}

ConjuntoPlantas::~ConjuntoPlantas(){

}

bool DecideQualMenorInicioTempoCarregamento ( Carregamento c1, Carregamento c2 ){
	return ( c1.HorarioInicioCarregamento < c2.HorarioInicioCarregamento );
}

#endif /* PLANTAS_HPP_ */
