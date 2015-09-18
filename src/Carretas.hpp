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

bool DecideQualMenorInicioTempoDeslocamento ( Deslocamento c1, Deslocamento c2 ){
	return ( c1.HorarioInicioDeslocamento < c2.HorarioInicioDeslocamento );
}

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

	int DeletaAtividade(double, double, int, int);

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

	Deslocamentos.insert(Deslocamentos.begin(), DeslocamentoAux );

}

int Carreta::DeletaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){
	for( vector < Deslocamento >::iterator it = Deslocamentos.begin(); it != Deslocamentos.end(); it++){
		if( it->HorarioInicioDeslocamento == HoraInicio){
			if( it->HorarioFinalDeslocamento == HoraFinal){
				if( it->NumeroConstrucao == NumContrucao){
					if( it->NumeroDemandaSuprida == NumDemanda){
						NumeroDeDemandasAntendidas = NumeroDeDemandasAntendidas - 1;
						Deslocamentos.erase(it);
						//cout << endl << endl << " ************* deletou " << Deslocamentos.size() << endl << endl ;
						return 1;
					}
				}
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou elemento deslocamento [" << NumContrucao << "-" << NumDemanda << "] a deletar !  -> Carreta::DeletaAtividade ################## " << endl << endl;
	return 0;
}

void Carreta::Imprime(){

	sort (Deslocamentos.begin(), Deslocamentos.end(), DecideQualMenorInicioTempoDeslocamento);
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

	int DeletaTarefa( int, double, double, int, int);

	void Imprime();

	~ConjuntoCarretas();
};

bool DecideCarretaAnterior ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDaCarreta < c2.NumeroDaCarreta );
}



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

int ConjuntoCarretas::DeletaTarefa( int NumeroCaminhao, double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){
	int Retirou;
	Retirou = 0;
	for( int c = 0; c < Carretas.size(); c++){
		if( Carretas[c].NumeroDaCarreta == NumeroCaminhao){
			Retirou = Carretas[c].DeletaAtividade(HoraInicio, HoraFinal, NumContrucao, NumDemanda);
			if( Retirou == 1){
				return 1;
			}else{
				cout << endl << endl << " ###########################   Problema! Não encontrou elemento deslocamento [" << NumContrucao << "-" << NumDemanda << "] a deletar !  -> ConjuntoCarretas::DeletaTarefa ################## " << endl << endl;
				return 0;
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou caminhao [" << NumeroCaminhao << "] a deletar !  -> ConjuntoCarretas::DeletaTarefa ################## " << endl << endl;
	return 0;
}

void ConjuntoCarretas::Imprime(){
	sort (Carretas.begin(), Carretas.end(), DecideCarretaAnterior);
	cout  << " [[[[[[  Imprime carretas  ]]]]]]" << endl;
	for( unsigned int c = 0; c < Carretas.size(); c++){
		Carretas[c].Imprime();
	}
}

ConjuntoCarretas::~ConjuntoCarretas(){

}





#endif /* CARRETAS_HPP_ */
