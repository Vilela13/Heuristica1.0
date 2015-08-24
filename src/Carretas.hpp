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
	int NumeroConstrucao;
	int NumeroDemandaSuprida;

};

class Carreta{

public:
	Carreta();
	int NumeroDaCarreta;
	int NumeroDeDemandasAntendidas;
	vector < vector < double > > TempoParaDescarregarNaConstrucao;
	vector < Deslocamento > Deslocamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, int);




	~Carreta();

};

Carreta::Carreta(){
	NumeroDaCarreta = -13;
	NumeroDeDemandasAntendidas = -13;

}

int Carreta::VerificaDisponibilidade(double InicioPossivelAlocacao, double FinalPossivelAlocacao){

	for( int d = 0; d < Deslocamentos.size(); d ++){
		if( InicioPossivelAlocacao < Deslocamentos[d].HorarioInicioDeslocamento){
			if( FinalPossivelAlocacao > Deslocamentos[d].HorarioInicioDeslocamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Deslocamentos[d].HorarioFinalDeslocamento){
			if ( FinalPossivelAlocacao > Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao > Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao > Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao < Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
	}

	return 1;

}

void Carreta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){
	Deslocamento DeslocamentoAux;

	DeslocamentoAux.HorarioInicioDeslocamento = HoraInicio;
	DeslocamentoAux.HorarioFinalDeslocamento = HoraFinal;
	DeslocamentoAux.NumeroConstrucao = NumContrucao;
	DeslocamentoAux.NumeroDemandaSuprida = NumDemanda;

	Deslocamentos.push_back( DeslocamentoAux );
}

Carreta::~Carreta(){

}

bool DecideQualCarretaTemMenosTarefasRealizadas ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDeDemandasAntendidas < c2.NumeroDeDemandasAntendidas );
}


class ConjuntoCarretas{

public:
	ConjuntoCarretas();
	vector< Carreta > Carretas;

	void IniciaConjuntoCarretas(int);

	void OrdenaCarretasPorNUmeroDeTarefasRealizadas();

	~ConjuntoCarretas();
};

ConjuntoCarretas::ConjuntoCarretas(){

}

void ConjuntoCarretas::IniciaConjuntoCarretas(int Numero){
	Carretas.resize(Numero);
	for(int v = 0; v < Numero; v++){
		Carretas[v].NumeroDaCarreta = v + 1;
		Carretas[v].NumeroDeDemandasAntendidas = 0;
	}

}

void ConjuntoCarretas::OrdenaCarretasPorNUmeroDeTarefasRealizadas(){
	sort (Carretas.begin(), Carretas.end(), DecideQualCarretaTemMenosTarefasRealizadas);
}

ConjuntoCarretas::~ConjuntoCarretas(){

}


bool DecideQualMenorInicioTempoDeslocamento ( Deslocamento c1, Deslocamento c2 ){
	return ( c1.HorarioInicioDeslocamento < c2.HorarioInicioDeslocamento );
}




#endif /* CARRETAS_HPP_ */
