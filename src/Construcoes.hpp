/*
 * Construcoes.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CONSTRUCOES_HPP_
#define CONSTRUCOES_HPP_

#include "Bibliotecas.hpp"

class Descarregamento{
public:
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	int NumeroDemandaSuprida;
	Carreta* CarretaUtilizada;
};

class DistanciaPlanta{
public:
	double Distancia;
	Planta* PlantaComparada;
};


class Construcao{

public:
	Construcao();
	int NumeroDaConstrucao;
	int NumeroDemandas;
	vector < DistanciaPlanta > DistanciaPlantas;
	double TempoMaximoEntreDescargas;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;
	double RankTempoDemandas;
	int StatusAtendimento;

	void CalculaRankTempoDemandas(int);

	vector < Descarregamento > Descarregamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, Carreta*);

	void ImprimeContrucao();

	~Construcao();

};

Construcao::Construcao(){
	NumeroDaConstrucao = -13;
	NumeroDemandas = -13;
	TempoMaximoEntreDescargas = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	RankTempoDemandas = -13;
	StatusAtendimento = 0;
}

void Construcao::CalculaRankTempoDemandas(int comentarios){
	RankTempoDemandas = ( TempoMaximoDeFuncionamento - TempoMinimoDeFuncionamento) / NumeroDemandas ;
	if( comentarios == 1){
		cout << " Rank ( Tempo / Demandas ) = " << RankTempoDemandas << endl;
	}
}

int Construcao::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){

	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( FinalPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	for( unsigned int d = 0; d < Descarregamentos.size(); d ++){
		if( InicioPossivelAlocacao < Descarregamentos[d].HorarioInicioDescarregamento){
			if( FinalPossivelAlocacao > Descarregamentos[d].HorarioInicioDescarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Descarregamentos[d].HorarioFinalDescarregamento){
			if ( FinalPossivelAlocacao > Descarregamentos[d].HorarioFinalDescarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Descarregamentos[d].HorarioInicioDescarregamento){
			if ( FinalPossivelAlocacao > Descarregamentos[d].HorarioFinalDescarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao > Descarregamentos[d].HorarioInicioDescarregamento){
			if ( FinalPossivelAlocacao < Descarregamentos[d].HorarioFinalDescarregamento){
				return 0;
			}
		}
	}

	if( StatusAtendimento == 0) {
		return 1;
	}else{
		for( unsigned int d = 0; d < Descarregamentos.size(); d ++){
			if( InicioPossivelAlocacao >= Descarregamentos[d].HorarioFinalDescarregamento){
				if( InicioPossivelAlocacao < Descarregamentos[d].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
					return 1;
				}
			}
		}
		return 0;
	}
}

void Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int NumDemanda, Carreta* Carreta){
	Descarregamento DescarregamentoAux;

	DescarregamentoAux.HorarioInicioDescarregamento = HoraInicio;
	DescarregamentoAux.HorarioFinalDescarregamento = HoraFinal;
	DescarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	DescarregamentoAux.CarretaUtilizada = Carreta;

	Descarregamentos.push_back( DescarregamentoAux );
}

void Construcao::ImprimeContrucao(){
	cout << endl;
	cout << "# Contrucao " << NumeroDaConstrucao << " com " << NumeroDemandas << " demandas, janela de tempo (" <<  TempoMinimoDeFuncionamento;
	cout << "," << TempoMaximoDeFuncionamento << "), com rank = " << RankTempoDemandas << endl;
	if( StatusAtendimento != 0){
		for( unsigned int d = 0; d < Descarregamentos.size(); d++){
			cout << "     * Carreta " << Descarregamentos[d].CarretaUtilizada->NumeroDaCarreta;
			cout << " atende demanda " << Descarregamentos[d].NumeroDemandaSuprida;
			cout << " de ( " << Descarregamentos[d].HorarioInicioDescarregamento;
			cout << " as " << Descarregamentos[d].HorarioFinalDescarregamento  << " ) " << endl;
		}
	}
}


Construcao::~Construcao(){

}


class ConjuntoConstrucoes{

public:
	ConjuntoConstrucoes();
	vector< Construcao > Construcoes;
	int NumeroConstrucoes;

	void IniciaConjuntoConstrucoes(int);
	void ImprimeContrucoes();



	~ConjuntoConstrucoes();
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){
	NumeroConstrucoes = -13;
}

void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	Construcoes.resize(Numero);
	NumeroConstrucoes = Numero;

}

void ConjuntoConstrucoes::ImprimeContrucoes(){
	cout << endl << endl << " [[[[[[  Imprime construcoes  ]]]]]]" << endl;
	for(int c = 0; c < NumeroConstrucoes; c++){
		Construcoes[c].ImprimeContrucao();
	}

}

ConjuntoConstrucoes::~ConjuntoConstrucoes(){

}


bool DecideQualContrucaoTemMaiorRank (Construcao c1,Construcao c2) {
	return ( c1.RankTempoDemandas < c2.RankTempoDemandas );
}

bool DecideQualMenorInicioTempoDescarregamento ( Descarregamento d1, Descarregamento d2){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}


#endif /* CONSTRUCOES_HPP_ */
