/*
 * DadosTarefa.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mateus.vilela
 */

#ifndef DADOSTAREFA_HPP_
#define DADOSTAREFA_HPP_

#include "Bibliotecas.hpp"

// Foi modificado

class DadosTarefa{
public:
	DadosTarefa();
	 vector < int >  DadosDasTarefas; 		// 0 -> NumConstrução , 1 -> NumPlanta , 2 -> NumCarreta, 3 -> situação retirada
	 vector < double > HorariosDasTarefas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta
	void IniciaConteudo();
	void InserirConteudo(int, int, int, int, double, double, double, double, double);
	void Imprimir();
	~DadosTarefa();
};


int RetiraElementoVetorDadosTarefa(vector < DadosTarefa >&,int, int, int, double, double, double, double, double);
int RetiraElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa >&, DadosTarefa );

int VerificaElementoVetorDadosTarefa(vector < DadosTarefa >,int, int, int, double, double, double, double, double);
int VerificaElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa >,DadosTarefa);

int AdicionaElementoVetorDadosTarefa(vector < DadosTarefa >&, int, int, int, int, double, double, double, double, double);
int AdicionaElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa >&, DadosTarefa);


void ImprimeVetorDadosTarefa( vector < DadosTarefa >);
bool DecideQualTarefaVemAntes ( DadosTarefa, DadosTarefa );



// construtora vazia da classe
DadosTarefa::DadosTarefa(){
}
// inicia o conteudo das esruturas
void DadosTarefa::IniciaConteudo(){
	DadosDasTarefas.resize(4);
	HorariosDasTarefas.resize(5);
}
// Insere dados em estrutura
void DadosTarefa::InserirConteudo(int NumConstucao, int NumPlanta, int NumCarreta, int SituacaoRetirada, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta ){
	IniciaConteudo();

	DadosDasTarefas[0] = NumConstucao;
	DadosDasTarefas[1] = NumPlanta;
	DadosDasTarefas[2] = NumCarreta;
	DadosDasTarefas[3] = SituacaoRetirada;

	HorariosDasTarefas[0] = HoraInicioPlanta;
	HorariosDasTarefas[1] = HoraSaiPlanta;
	HorariosDasTarefas[2] = HoraInicioConstrucao;
	HorariosDasTarefas[3] = HoraSaiConstrucao;
	HorariosDasTarefas[4] = HoraRetornaPlanta;
}
// Imprime dados da estrutura
void DadosTarefa::Imprimir(){
	cout << " Planta [" << DadosDasTarefas[1] << "]";
	cout << " tempo (" << HorariosDasTarefas[0] << "-" << HorariosDasTarefas[1] << ") ";
	cout << " Construcao [" << DadosDasTarefas[0]  << "]";
	cout << "tempo (" << HorariosDasTarefas[2] << "-" << HorariosDasTarefas[3] << ") ";
	cout << " Caminhao [" << DadosDasTarefas[1] << "-" << DadosDasTarefas[2] << "]";
	cout << " tempo (" << HorariosDasTarefas[0] << "-" << HorariosDasTarefas[4] << ") ";
	cout << " Situação [" << DadosDasTarefas[3] << "]" << endl;
}
// destruidora vazia da classe
DadosTarefa::~DadosTarefa(){
}


int RetiraElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor,int NumConstucao, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefas[0] == NumConstucao && Vetor[i].DadosDasTarefas[1] == NumPlanta && Vetor[i].DadosDasTarefas[2] == NumCarreta){
			if( Vetor[i].HorariosDasTarefas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefas[4] == HoraRetornaPlanta){
				Vetor.erase (Vetor.begin()+i);
				return 1;
			}
		}
	}
	return 0;
}

int RetiraElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa > &Vetor, DadosTarefa Dado){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefas[0] == Dado.DadosDasTarefas[0] && Vetor[i].DadosDasTarefas[1] == Dado.DadosDasTarefas[1] && Vetor[i].DadosDasTarefas[2] == Dado.DadosDasTarefas[2]){
			if( Vetor[i].HorariosDasTarefas[0] == Dado.HorariosDasTarefas[0] && Vetor[i].HorariosDasTarefas[1] == Dado.HorariosDasTarefas[1] && Vetor[i].HorariosDasTarefas[2] == Dado.HorariosDasTarefas[2] && Vetor[i].HorariosDasTarefas[3] == Dado.HorariosDasTarefas[3] && Vetor[i].HorariosDasTarefas[4] == Dado.HorariosDasTarefas[4] ){
				Vetor.erase (Vetor.begin()+i);
				return 1;
			}
		}
	}
	return 0;
}

int VerificaElementoVetorDadosTarefa(vector < DadosTarefa > Vetor,int NumConstucao,  int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefas[0] == NumConstucao  && Vetor[i].DadosDasTarefas[1] == NumPlanta && Vetor[i].DadosDasTarefas[2] == NumCarreta){
			if( Vetor[i].HorariosDasTarefas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefas[4] == HoraRetornaPlanta){
				return 1;
			}
		}
	}
	return 0;

}

int VerificaElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa >  Vetor,DadosTarefa Dado){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		if( Vetor[i].DadosDasTarefas[0] == Dado.DadosDasTarefas[0] && Vetor[i].DadosDasTarefas[1] == Dado.DadosDasTarefas[1] && Vetor[i].DadosDasTarefas[2] == Dado.DadosDasTarefas[2]){
			if( Vetor[i].HorariosDasTarefas[0] == Dado.HorariosDasTarefas[0] && Vetor[i].HorariosDasTarefas[1] == Dado.HorariosDasTarefas[1] && Vetor[i].HorariosDasTarefas[2] == Dado.HorariosDasTarefas[2] && Vetor[i].HorariosDasTarefas[3] == Dado.HorariosDasTarefas[3] && Vetor[i].HorariosDasTarefas[4] == Dado.HorariosDasTarefas[4] ){
				return 1;
			}
		}
	}
	return 0;
}

int AdicionaElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor, int NumConstucao, int NumPlanta, int NumCarreta,  int SituacaoRetirada, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta){
	int ParaFuncao;
	if( VerificaElementoVetorDadosTarefa(Vetor,NumConstucao, NumPlanta,NumCarreta,  HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta) == 1){
		cout << endl << endl << "    <<<<<<<<<<<<<<<   ERRO! -> AdicionaElementoVetorDadosTarefa >>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		cout << " Planta [" << NumPlanta << "]";
		cout << " tempo (" << HoraInicioPlanta << "-" << HoraSaiPlanta << ") ";
		cout << " Construcao [" << NumConstucao  << "]";
		cout << "tempo (" << HoraInicioConstrucao << "-" << HoraSaiConstrucao << ") ";
		cout << " Caminhao [" << NumPlanta << "-" << NumCarreta << "]";
		cout << " tempo (" << HoraInicioPlanta << "-" << HoraRetornaPlanta << ") " << endl;
		cin >> ParaFuncao;
		return 0;
	}else{
		Vetor.resize(Vetor.size() + 1);
		Vetor[Vetor.size() - 1].InserirConteudo(NumConstucao, NumPlanta, NumCarreta, SituacaoRetirada, HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta);
		return 1;
	}
}

int AdicionaElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa > &Vetor, DadosTarefa Dado){
	int ParaFuncao;
	if( VerificaElementoVetorDadosTarefaApartirEstrutura(Vetor,Dado) == 1){
		cout << endl << endl << "    <<<<<<<<<<<<<<<   ERRO! -> AdicionaElementoVetorDadosTarefaEstrutura >>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		Dado.Imprimir();
		cin >> ParaFuncao;
		return 0;
	}else{
		Vetor.resize(Vetor.size() + 1);
		Vetor[Vetor.size() - 1].InserirConteudo(Dado.DadosDasTarefas[0], Dado.DadosDasTarefas[1], Dado.DadosDasTarefas[2], Dado.DadosDasTarefas[3], Dado.HorariosDasTarefas[0] , Dado.HorariosDasTarefas[1], Dado.HorariosDasTarefas[2] , Dado.HorariosDasTarefas[3], Dado.HorariosDasTarefas[4]);
		return 1;
	}
}




void ImprimeVetorDadosTarefa( vector < DadosTarefa > Vetor){
	for( unsigned int i = 0; i < Vetor.size(); i++){
		cout << "[" << i << "] ";
		Vetor[i].Imprimir();
	}
}

bool DecideQualTarefaVemAntes ( DadosTarefa d1, DadosTarefa d2 ){
	return ( d1.HorariosDasTarefas[2] < d2.HorariosDasTarefas[2] );
}

#endif /* DADOSTAREFA_HPP_ */
