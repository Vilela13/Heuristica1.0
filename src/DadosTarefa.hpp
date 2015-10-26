/*
 * DadosTarefa.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mateus.vilela
 */

#ifndef DADOSTAREFA_HPP_
#define DADOSTAREFA_HPP_

#include "Bibliotecas.hpp"


class DadosTarefa{
public:
	DadosTarefa();
	 vector < int >  DadosDasTarefasRetiradas; 		// 0 -> NumConstrução , 1 -> NumDemanda , 2 -> NumPlanta , 3 -> NumCarreta
	 vector < double > HorariosDasTarefasRetiradas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta
	void IniciaConteudo();
	void InserirConteudo(int, int, int, int, double, double, double, double, double);
	void Imprimir();
	~DadosTarefa();
};

int RetiraElementoVetorDadosTarefa (vector < DadosTarefa >&, int, int );
int RetiraElementoVetorDadosTarefa(vector < DadosTarefa >&,int, int, int, double, double, double, double, double);
int RetiraElementoVetorDadosTarefaComDemanda(vector < DadosTarefa >&,int, int, int, int, double, double, double, double, double);
int AdicionaElementoVetorDadosTarefa(vector < DadosTarefa >&, int, int, int, int, double, double, double, double, double);
int AdicionaElementoVetorDadosTarefaUsandoDemanda(vector < DadosTarefa >&,int, int, int, int, double, double, double, double, double);
int VerificaElementoVetorDadosTarefa(vector < DadosTarefa >,int, int, int, int, double, double, double, double, double);
void ImprimeVetorDadosTarefa( vector < DadosTarefa >);
bool DecideQualTarefaVemAntes ( DadosTarefa, DadosTarefa );


DadosTarefa::DadosTarefa(){

}

void DadosTarefa::IniciaConteudo(){
	DadosDasTarefasRetiradas.resize(4);
	HorariosDasTarefasRetiradas.resize(5);
}

void DadosTarefa::InserirConteudo(int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta ){
	IniciaConteudo();

	DadosDasTarefasRetiradas[0] = NumConstucao;
	DadosDasTarefasRetiradas[1] = NumDemanda;
	DadosDasTarefasRetiradas[2] = NumPlanta;
	DadosDasTarefasRetiradas[3] = NumCarreta;

	HorariosDasTarefasRetiradas[0] = HoraInicioPlanta;
	HorariosDasTarefasRetiradas[1] = HoraSaiPlanta;
	HorariosDasTarefasRetiradas[2] = HoraInicioConstrucao;
	HorariosDasTarefasRetiradas[3] = HoraSaiConstrucao;
	HorariosDasTarefasRetiradas[4] = HoraRetornaPlanta;
}

void DadosTarefa::Imprimir(){
	cout << " Construcao [" << DadosDasTarefasRetiradas[0] << "-" << DadosDasTarefasRetiradas[1] << "]";
	cout << "tempo (" << HorariosDasTarefasRetiradas[2] << "-" << HorariosDasTarefasRetiradas[3] << ") ";
	cout << " Planta [" << DadosDasTarefasRetiradas[2] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[1] << ") ";
	cout << " Caminhao [" << DadosDasTarefasRetiradas[2] << "-" << DadosDasTarefasRetiradas[3] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[4] << ") " << endl;
}

DadosTarefa::~DadosTarefa(){

}

int RetiraElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor, int Construcao, int Demanda){
	for( int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefasRetiradas[0] == Construcao && Vetor[i].DadosDasTarefasRetiradas[1] == Demanda){
			Vetor.erase (Vetor.begin()+i);
			return 1;
		}
	}
	return 0;
}

int RetiraElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor,int NumConstucao, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefasRetiradas[0] == NumConstucao && Vetor[i].DadosDasTarefasRetiradas[2] == NumPlanta && Vetor[i].DadosDasTarefasRetiradas[3] == NumCarreta){
			if( Vetor[i].HorariosDasTarefasRetiradas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefasRetiradas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefasRetiradas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefasRetiradas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefasRetiradas[4] == HoraRetornaPlanta){
				Vetor.erase (Vetor.begin()+i);
				return 1;
			}
		}
	}
	return 0;
}

int RetiraElementoVetorDadosTarefaComDemanda(vector < DadosTarefa > &Vetor,int NumConstucao, int Demanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefasRetiradas[0] == NumConstucao && Vetor[i].DadosDasTarefasRetiradas[1] == Demanda && Vetor[i].DadosDasTarefasRetiradas[2] == NumPlanta && Vetor[i].DadosDasTarefasRetiradas[3] == NumCarreta){
			if( Vetor[i].HorariosDasTarefasRetiradas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefasRetiradas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefasRetiradas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefasRetiradas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefasRetiradas[4] == HoraRetornaPlanta){
				Vetor.erase (Vetor.begin()+i);
				return 1;
			}
		}
	}
	return 0;
}

int AdicionaElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor,int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	if( RetiraElementoVetorDadosTarefa(Vetor,NumConstucao, NumPlanta,NumCarreta,HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta) == 1){
		cout << endl << endl << "    <<<<<<<<<<<<<<<   ERRO! -> AdicionaElementoVetorDadosTarefa >>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		return 0;
	}else{
		Vetor.resize(Vetor.size()+1);
		Vetor[Vetor.size()-1].InserirConteudo(NumConstucao,NumDemanda, NumPlanta,NumCarreta,HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta);
		return 1;
	}
}

int AdicionaElementoVetorDadosTarefaUsandoDemanda(vector < DadosTarefa > &Vetor,int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	if( RetiraElementoVetorDadosTarefaComDemanda(Vetor,NumConstucao, NumDemanda, NumPlanta,NumCarreta,HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta) == 1){
		cout << endl << endl << "    <<<<<<<<<<<<<<<   ERRO! -> AdicionaElementoVetorDadosTarefa usando demanda >>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		return 0;
	}else{
		Vetor.resize(Vetor.size()+1);
		Vetor[Vetor.size()-1].InserirConteudo(NumConstucao,NumDemanda, NumPlanta,NumCarreta,HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta);
		return 1;
	}

}

int VerificaElementoVetorDadosTarefa(vector < DadosTarefa > Vetor,int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefasRetiradas[0] == NumConstucao && Vetor[i].DadosDasTarefasRetiradas[1] == NumDemanda && Vetor[i].DadosDasTarefasRetiradas[2] == NumPlanta && Vetor[i].DadosDasTarefasRetiradas[3] == NumCarreta){
			if( Vetor[i].HorariosDasTarefasRetiradas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefasRetiradas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefasRetiradas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefasRetiradas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefasRetiradas[4] == HoraRetornaPlanta){
				return 1;
			}
		}
	}
	return 0;

}


void ImprimeVetorDadosTarefa( vector < DadosTarefa > Vetor){
	for( int i = 0; i < Vetor.size(); i++){
		cout << "[" << i << "] ";
		Vetor[i].Imprimir();
	}
}

bool DecideQualTarefaVemAntes ( DadosTarefa d1, DadosTarefa d2 ){
	return ( d1.HorariosDasTarefasRetiradas[2] < d2.HorariosDasTarefasRetiradas[2] );
}

#endif /* DADOSTAREFA_HPP_ */
