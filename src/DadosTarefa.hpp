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
	vector < int >  DadosDasTarefas; 		     // 0 -> NumConstrução ,  1 -> NumPlanta ,     2 -> NumCarreta,           3 -> situação alocação,  4 -> status retirada
	vector < float > HorariosDasTarefas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta
	char 	Status;	// será "r" se foi removido e "a" se foi adicionado

	// Funções

	void 	IniciaConteudo();			// construtora vazia da classe
	void 	InserirConteudo(int NumConstucao, int NumPlanta, int NumCarreta, int Situacao, int SituacaoRetirada, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta, char status);			// Insere dados em estrutura
	void 	Imprimir();				// Imprime dados da estrutura
	~DadosTarefa();
};


int 	RetiraElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor,int NumConstucao, int NumPlanta, int NumCarreta, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta, char status );			// retira um elemento dos dados das tarefas
int 	RetiraElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa > &Vetor, DadosTarefa Dado );			// retira um elemento dos dados das tarefas apartir de estrutura

int 	VerificaElementoVetorDadosTarefa(vector < DadosTarefa > Vetor,int NumConstucao,  int NumPlanta, int NumCarreta, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta);						// verifica se a tarefa passada pela estrutura de dados está presente na estrutura que armazena as tarefas
int 	VerificaElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa >  Vetor,DadosTarefa Dado);			// verifica se a tarefa passada pela estrutura de dados está presente na estrutura que armazena as tarefas

int 	AdicionaElementoVetorDadosTarefa(int VerificaExistencia, vector < DadosTarefa > &Vetor, int NumConstucao, int NumPlanta, int NumCarreta, int Situacao, int SituacaoRetirada, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta, char status);		// adiciona uma tarefa apartir de dados
int 	AdicionaElementoVetorDadosTarefaApartirEstrutura(int VerificaExistencia, vector < DadosTarefa > &Vetor, DadosTarefa Dado);			// adiciona uma tarefa apartir de estrutura de dados

int 	MergeDadosTarefa( vector < DadosTarefa > &VetorBase, vector < DadosTarefa > VetorFonte);			// Adicionaos elementos de VetorFonte ao Vetor Base

void 	ImprimeVetorDadosTarefa( vector < DadosTarefa > Vetor);		// imprime as tarefas
bool 	DecideQualTarefaVemAntes ( DadosTarefa d1, DadosTarefa d2 );



// construtora vazia da classe
DadosTarefa::DadosTarefa(){
	Status = -13;
}

// inicia o conteudo das esruturas vector DadosDasTarefas e HorariosDasTarefas
void 	DadosTarefa::IniciaConteudo(){
	DadosDasTarefas.resize(5);
	HorariosDasTarefas.resize(5);
}

// Insere dados em estrutura
void 	DadosTarefa::InserirConteudo(int NumConstucao, int NumPlanta, int NumCarreta, int Situacao, int SituacaoRetirada, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta, char status){
	// inicia os tipos vector
	IniciaConteudo();

	// preenche o vector DadosDasTarefas
	DadosDasTarefas[0] = NumConstucao;
	DadosDasTarefas[1] = NumPlanta;
	DadosDasTarefas[2] = NumCarreta;
	DadosDasTarefas[3] = Situacao;
	DadosDasTarefas[4] = SituacaoRetirada;

	// preenche o vector HorariosDasTarefas
	HorariosDasTarefas[0] = HoraInicioPlanta;
	HorariosDasTarefas[1] = HoraSaiPlanta;
	HorariosDasTarefas[2] = HoraInicioConstrucao;
	HorariosDasTarefas[3] = HoraSaiConstrucao;
	HorariosDasTarefas[4] = HoraRetornaPlanta;

	// preenche o campo de status se essa tarefa foi adicionada ou removida
	Status = status;
}

// Imprime dados da estrutura
void 	DadosTarefa::Imprimir(){
	printf (" < %c >  ", Status);
	printf (" Planta [%d]",DadosDasTarefas[1] );
	printf (" tempo (%.4f-%.4f)", HorariosDasTarefas[0], HorariosDasTarefas[1]);
	printf (" Construcao [%d]",DadosDasTarefas[0]);
	printf (" tempo (%.4f-%.4f) ", HorariosDasTarefas[2], HorariosDasTarefas[3]);
	printf (" Caminhao [%d-%d]",DadosDasTarefas[1], DadosDasTarefas[2]);
	printf (" tempo (%.4f-%.4f)", HorariosDasTarefas[0], HorariosDasTarefas[4]);
	printf (" Situação [%d], Status Remocao [%d]\n", DadosDasTarefas[3], DadosDasTarefas[4]);
}
// destruidora vazia da classe
DadosTarefa::~DadosTarefa(){
	DadosDasTarefas.clear();
	HorariosDasTarefas.clear();
}

// retira um elemento dos dados das tarefas apartir de dados
int 	RetiraElementoVetorDadosTarefa(vector < DadosTarefa > &Vetor,int NumConstucao, int NumPlanta, int NumCarreta, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta, char status){
	// percorre todas as tarefas
	for( int i = 0; i < (int) Vetor.size(); i++){
		// verifica se os dasdos passados combinam om os dados de uma das tarefas armazenadas
		if( Vetor[i].DadosDasTarefas[0] == NumConstucao && Vetor[i].DadosDasTarefas[1] == NumPlanta && Vetor[i].DadosDasTarefas[2] == NumCarreta){
			// verifica se os horarios passados combinam om os horarios de uma das tarefas armazenadas
			if( Vetor[i].HorariosDasTarefas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefas[4] == HoraRetornaPlanta){
				// verifica se o status de adição ou retirada combinam com o de alguma tarefa
				if(  Vetor[i].Status == status){
					// retira o elemento passado da estrutura de dados
					Vetor.erase (Vetor.begin()+i);
					// retorna 1 caso retirou o elemento passado
					return 1;
				}
			}
		}
	}
	// retorna 0 caso não conseguiu retirar o elemento passado
	return 0;
}

// retira um elemento dos dados das tarefas apartir de estrutura
int 	RetiraElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa > &Vetor, DadosTarefa Dado){
	// percorre todas as tarefas
	for( int i = 0; i < (int) Vetor.size(); i++){
		// verifica se os dasdos da estrutura passada combinam om os dados de uma das tarefas armazenadas
		if( Vetor[i].DadosDasTarefas[0] == Dado.DadosDasTarefas[0] && Vetor[i].DadosDasTarefas[1] == Dado.DadosDasTarefas[1] && Vetor[i].DadosDasTarefas[2] == Dado.DadosDasTarefas[2]){
			// verifica se os horarios  da estrutura passados combinam om os horarios de uma das tarefas armazenadas
			if( Vetor[i].HorariosDasTarefas[0] == Dado.HorariosDasTarefas[0] && Vetor[i].HorariosDasTarefas[1] == Dado.HorariosDasTarefas[1] && Vetor[i].HorariosDasTarefas[2] == Dado.HorariosDasTarefas[2] && Vetor[i].HorariosDasTarefas[3] == Dado.HorariosDasTarefas[3] && Vetor[i].HorariosDasTarefas[4] == Dado.HorariosDasTarefas[4] ){
				// verifica se o status de adição ou retirada combinam com o de alguma tarefa
				if( Vetor[i].Status == Dado.Status){
					// retira o elemento passado da estrutura de dados
					Vetor.erase (Vetor.begin()+i);
					// retorna 1 caso retirou o elemento passado
					return 1;
				}
			}
		}
	}
	// retorna 0 caso não conseguiu retirar o elemento passado
	return 0;
}

// verifica se a tarefa passada está presente na estrutura que armazena as tarefas
int 	VerificaElementoVetorDadosTarefa(vector < DadosTarefa > Vetor,int NumConstucao,  int NumPlanta, int NumCarreta, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta, char status){
	// percorre todas as tarefas
	for( int i = 0; i < (int) Vetor.size(); i++){
		// verifica se os dasdos passados combinam om os dados de uma das tarefas armazenadas
		if( Vetor[i].DadosDasTarefas[0] == NumConstucao  && Vetor[i].DadosDasTarefas[1] == NumPlanta && Vetor[i].DadosDasTarefas[2] == NumCarreta){
			// verifica se os horarios passados combinam om os horarios de uma das tarefas armazenadas
			if( Vetor[i].HorariosDasTarefas[0] == HoraInicioPlanta &&  Vetor[i].HorariosDasTarefas[1] == HoraSaiPlanta && Vetor[i].HorariosDasTarefas[2] == HoraInicioConstrucao && Vetor[i].HorariosDasTarefas[3] == HoraSaiConstrucao && Vetor[i].HorariosDasTarefas[4] == HoraRetornaPlanta){
				// verifica se o status de adição ou retirada combinam com o de alguma tarefa
				if( Vetor[i].Status == status){
					// a tarefa está presente
					return 1;
				}
			}
		}
	}
	// a tarefa não está presente
	return 0;
}

// verifica se a tarefa passada pela estrutura de dados está presente na estrutura que armazena as tarefas
int 	VerificaElementoVetorDadosTarefaApartirEstrutura(vector < DadosTarefa >  Vetor,DadosTarefa Dado){
	// percorre todas as tarefas
	for( int i = 0; i < (int) Vetor.size(); i++){
		// verifica se os dasdos passados combinam om os dados de uma das tarefas armazenadas
		if( Vetor[i].DadosDasTarefas[0] == Dado.DadosDasTarefas[0] && Vetor[i].DadosDasTarefas[1] == Dado.DadosDasTarefas[1] && Vetor[i].DadosDasTarefas[2] == Dado.DadosDasTarefas[2]){
			// verifica se os horarios passados combinam om os horarios de uma das tarefas armazenadas
			if( Vetor[i].HorariosDasTarefas[0] == Dado.HorariosDasTarefas[0] && Vetor[i].HorariosDasTarefas[1] == Dado.HorariosDasTarefas[1] && Vetor[i].HorariosDasTarefas[2] == Dado.HorariosDasTarefas[2] && Vetor[i].HorariosDasTarefas[3] == Dado.HorariosDasTarefas[3] && Vetor[i].HorariosDasTarefas[4] == Dado.HorariosDasTarefas[4] ){
				// verifica se o status de adição ou retirada combinam com o de alguma tarefa
				if(  Vetor[i].Status == Dado.Status){
					// a tarefa está presente
					return 1;
				}
			}
		}
	}
	// a tarefa não está presente
	return 0;
}

// adiciona uma tarefa apartir de dados
int 	AdicionaElementoVetorDadosTarefa(int VerificaExistencia, vector < DadosTarefa > &Vetor, int NumConstucao, int NumPlanta, int NumCarreta, int Situacao, int SituacaoRetirada, float HoraInicioPlanta, float HoraSaiPlanta, float HoraInicioConstrucao, float HoraSaiConstrucao, float HoraRetornaPlanta,char status){
	int 	ParaFuncao;

	// caso tenha que verificar se a tarefa existe antes de adicionala
	if( VerificaExistencia == 1){
		// verifica se ela já existe na estrutura de tarefas
		if( VerificaElementoVetorDadosTarefa(Vetor,NumConstucao, NumPlanta,NumCarreta,  HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta, status) == 1){
			//caso ela já exista se imprime ela na tela
			cout << endl << endl << "    <<<<<<<<<<<<<<<   ERRO! -> AdicionaElementoVetorDadosTarefa >>>>>>>>>>>>>>>>>>>>>" << endl << endl;
			printf (" Planta [%d]",NumPlanta );
			printf (" tempo (%.4f-%.4f)", HoraInicioPlanta, HoraSaiPlanta);
			printf (" Construcao [%d]",NumConstucao);
			printf (" tempo (%.4f-%.4f)", HoraInicioConstrucao, HoraSaiConstrucao);
			printf (" Caminhao [%d-%d]",NumPlanta, NumCarreta);
			printf (" tempo (%.4f-%.4f)", HoraInicioPlanta, HoraRetornaPlanta);
			printf (" status %c \n", status);
			cin >> ParaFuncao;
			// retorna 0 para mostrar que a operação não foi realizada
			return 0;
		}else{
			// adiciona tarefa e retorna o valor 1 demonstrando que a operação foi realizada
			Vetor.resize(Vetor.size() + 1);
			Vetor[Vetor.size() - 1].InserirConteudo(NumConstucao, NumPlanta, NumCarreta, Situacao, SituacaoRetirada, HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta, status);
			return 1;
		}
	}else{
		// adiciona tarefa e retorna o valor 1 demonstrando que a operação foi realizada
		Vetor.resize(Vetor.size() + 1);
		Vetor[Vetor.size() - 1].InserirConteudo(NumConstucao, NumPlanta, NumCarreta, Situacao, SituacaoRetirada, HoraInicioPlanta, HoraSaiPlanta, HoraInicioConstrucao, HoraSaiConstrucao, HoraRetornaPlanta, status);
		return 1;
	}
}

// adiciona uma tarefa apartir de estrutura de dados
int 	AdicionaElementoVetorDadosTarefaApartirEstrutura(int VerificaExistencia, vector < DadosTarefa > &Vetor, DadosTarefa Dado){
	int 	ParaFuncao;

	// caso tenha que verificar se a tarefa existe antes de adicionala
	if( VerificaExistencia == 1){
		// verifica se ela já existe na estrutura de tarefas
		if( VerificaElementoVetorDadosTarefaApartirEstrutura(Vetor,Dado) == 1){
			//caso ela já exista se imprime ela na tela
			cout << endl << endl << "    <<<<<<<<<<<<<<<   ERRO! -> AdicionaElementoVetorDadosTarefaEstrutura >>>>>>>>>>>>>>>>>>>>>" << endl << endl;
			Dado.Imprimir();
			cin >> ParaFuncao;
			// retorna 0 para mostrar que a operação não foi realizada
			return 0;
		}else{
			// adiciona tarefa e retorna o valor 1 demonstrando que a operação foi realizada
			Vetor.resize(Vetor.size() + 1);
			Vetor[Vetor.size() - 1].InserirConteudo(Dado.DadosDasTarefas[0], Dado.DadosDasTarefas[1], Dado.DadosDasTarefas[2], Dado.DadosDasTarefas[3], Dado.DadosDasTarefas[4], Dado.HorariosDasTarefas[0] , Dado.HorariosDasTarefas[1], Dado.HorariosDasTarefas[2] , Dado.HorariosDasTarefas[3], Dado.HorariosDasTarefas[4],Dado.Status);
			return 1;
		}
	}else{
		// adiciona tarefa e retorna o valor 1 demonstrando que a operação foi realizada
		Vetor.resize(Vetor.size() + 1);
		Vetor[Vetor.size() - 1].InserirConteudo(Dado.DadosDasTarefas[0], Dado.DadosDasTarefas[1], Dado.DadosDasTarefas[2], Dado.DadosDasTarefas[3], Dado.DadosDasTarefas[4], Dado.HorariosDasTarefas[0] , Dado.HorariosDasTarefas[1], Dado.HorariosDasTarefas[2] , Dado.HorariosDasTarefas[3], Dado.HorariosDasTarefas[4],Dado.Status);
		return 1;
	}
}

// Adicionaos elementos de VetorFonte ao Vetor Base
int 	MergeDadosTarefa( vector < DadosTarefa > &VetorBase, vector < DadosTarefa > VetorFonte){

	// percorre todos os elementos do VetorFonte
	for( int i = 0; i < (int) VetorFonte.size(); i++){
		// adiciona o elemento corrente do VetorFonte ao VetorBase
		if( AdicionaElementoVetorDadosTarefaApartirEstrutura(0, VetorBase, VetorFonte[i]) == 0){
			cout << endl << endl << " <<<<<<<<<<<<< Problema em adicionar elemeto no VetorBase - elemento " << endl;
			VetorFonte[i].Imprimir();
			cout << "     -> MergeDadosTarefa " << endl << endl;
			// caso não conseguir adicionar o elemento do VetorFonte no VetorBase
			return 0;
		}
	}
	// caso conseguir adicionar todos os elementos do VetorFonte no VetorBase
	return 1;
}

// imprime as tarefas
void 	ImprimeVetorDadosTarefa( vector < DadosTarefa > Vetor){
	// percorre todas as tarefas
	for( int i = 0; i < (int) Vetor.size(); i++){
		cout << "[" << i << "] ";
		// imprime a tarefa corrente
		Vetor[i].Imprimir();
	}
}

bool 	DecideQualTarefaVemAntes ( DadosTarefa d1, DadosTarefa d2 ){
	return ( d1.HorariosDasTarefas[2] < d2.HorariosDasTarefas[2] );
}

#endif /* DADOSTAREFA_HPP_ */
