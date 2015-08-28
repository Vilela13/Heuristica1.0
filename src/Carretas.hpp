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
	int NumeroPlanta;
	vector < vector < double > > TempoParaDescarregarNaConstrucao;
	vector < Deslocamento > Deslocamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, int);

	void Imprime();


	~Carreta();

};

Carreta::Carreta(){
	NumeroDaCarreta = -13;
	NumeroDeDemandasAntendidas = -13;
	NumeroPlanta = -13;

}

int Carreta::VerificaDisponibilidade(double InicioPossivelAlocacao, double FinalPossivelAlocacao){

	for( unsigned int d = 0; d < Deslocamentos.size(); d ++){
		if( InicioPossivelAlocacao <= Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao >= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao >= Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao <= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao <= Deslocamentos[d].HorarioInicioDeslocamento){
			if( FinalPossivelAlocacao > Deslocamentos[d].HorarioInicioDeslocamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Deslocamentos[d].HorarioFinalDeslocamento){
			if ( FinalPossivelAlocacao >= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
	}

	return 1;

}

void Carreta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){

	NumeroDeDemandasAntendidas = NumeroDeDemandasAntendidas + 1;

	Deslocamento DeslocamentoAux;

	DeslocamentoAux.HorarioInicioDeslocamento = HoraInicio;
	DeslocamentoAux.HorarioFinalDeslocamento = HoraFinal;
	DeslocamentoAux.NumeroConstrucao = NumContrucao;
	DeslocamentoAux.NumeroDemandaSuprida = NumDemanda;

	//cout << endl << endl << "     ******** aloca  caminhao ********* " << endl;
	//cout << " inicio " << HoraInicio << " final " << HoraFinal <<endl;

	Deslocamentos.push_back( DeslocamentoAux );
}

void Carreta::Imprime(){
	cout << "# Carreta [" << NumeroPlanta << "-" << NumeroDaCarreta << "] que atendeu " << NumeroDeDemandasAntendidas << " demandas" << endl;
	for( int d = 0; d < NumeroDeDemandasAntendidas; d++){
		cout << "    *  Atender a [" << Deslocamentos[d].NumeroConstrucao << "-"<< Deslocamentos[d].NumeroDemandaSuprida << "]" ;
		cout << " de ( " << Deslocamentos[d].HorarioInicioDeslocamento << " - " << Deslocamentos[d].HorarioFinalDeslocamento << " ) "<< endl;
	}

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

	void IniciaConjuntoCarretas(int, int);

	void OrdenaCarretasPorNumeroDeTarefasRealizadas();

	void Imprime();

	~ConjuntoCarretas();
};

ConjuntoCarretas::ConjuntoCarretas(){

}

void ConjuntoCarretas::IniciaConjuntoCarretas(int NumeroCaminhoes, int NumeroDaPlanta){
	Carretas.resize(NumeroCaminhoes);
	for(int v = 0; v < NumeroCaminhoes; v++){
		Carretas[v].NumeroDaCarreta = v;
		Carretas[v].NumeroDeDemandasAntendidas = 0;
		Carretas[v].NumeroPlanta = NumeroDaPlanta;
	}

}

void ConjuntoCarretas::OrdenaCarretasPorNumeroDeTarefasRealizadas(){
	sort (Carretas.begin(), Carretas.end(), DecideQualCarretaTemMenosTarefasRealizadas);
}

void ConjuntoCarretas::Imprime(){
	cout  << " [[[[[[  Imprime carretas  ]]]]]]" << endl;
	for( unsigned int c = 0; c < Carretas.size(); c++){
		Carretas[c].Imprime();
	}
}

ConjuntoCarretas::~ConjuntoCarretas(){

}


bool DecideQualMenorInicioTempoDeslocamento ( Deslocamento c1, Deslocamento c2 ){
	return ( c1.HorarioInicioDeslocamento < c2.HorarioInicioDeslocamento );
}




#endif /* CARRETAS_HPP_ */
