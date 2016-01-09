/*
 * FuncoesSolucoes.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mateus.vilela
 */

#ifndef FUNCOESSOLUCOES_HPP_
#define FUNCOESSOLUCOES_HPP_

#include "Bibliotecas.hpp"


void AlocaValoresIniciaisIndices(int& c, int& d);		// inicia os valores de c e d com -13
int VerificaInidices( int c, int d);					// verifica se os indices c e d não possuem o valor -13
int VerificaInidices2( int p, int v);					// verifica se os indices p e v não possuem o valor -13

void ImprimeVetorInt( vector< int > VetorInt );			// imprime o vector de int
void ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( int ImprimeDadosTarefasMovidas, vector < DadosTarefa > DadosTarefasMovidas,  int ImprimeVetorCosntrucoes, vector < int > ConstrucaosAnalizadas, int ParaPrograma);		// imprime as tarefas movidas e as cosntruçĩoes caso forem para serem impressos
void IniciaVetorIntComZero(vector< int > &VetorInt);	// inicia o vector de int com todos os seus valores como 0

int VerificaSeTemUmValorVetorInt( int Valor, vector< int > VetorInt);			// verifica se existe um valor no vector igual ao valor passado
int VerificaTodosValoresVetorInt( int Valor, vector< int > VetorInt);			// verifica se todos os valores do vector são iguais ao valor passado
void ImprimeVetorDouble( vector< double > VetorDouble); 						// imprime os valores do vector de elementos double


// inicia os valores de c e d com -13
void AlocaValoresIniciaisIndices( int& c, int& d){
	c = -13;
	d = -13;
}

// verifica se os indices c e d não possuem o valor -13
int VerificaInidices( int c, int d){
	if( c == -13 || d == -13 ){
			cout  << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao &&&&&&&&&&&&& " << endl << endl << endl;
			return -1;
		}
	return 1;
}

// verifica se os indices p e v não possuem o valor -13
int VerificaInidices2( int p, int v){
	if( p == -13 || v == -13 ){
			cout  << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a planta ou caminhao &&&&&&&&&&&&& " << endl << endl << endl;
			return -1;
		}
	return 1;
}

// imprime o vector de int
void ImprimeVetorInt( vector< int > VetorInt){
	cout << " Conteudo Vetor "<< endl;
	// percorre os elementos do vector
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		cout << " [" << i << "] " << VetorInt[i] << " ";
	}
	cout << endl;
}

// imprime as tarefas movidas e as cosntruçĩoes caso forem para serem impressos
void ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( int ImprimeDadosTarefasMovidas, vector < DadosTarefa > DadosTarefasMovidas,  int ImprimeVetorCosntrucoes, vector < int > ConstrucaosAnalizadas, int ParaPrograma){
	int numero;

	// caso tiver que imprimir os DadosTarefasMovidas entra no if
	if ( ImprimeDadosTarefasMovidas == 1){
		// imprime os DadosTarefasMovidas
		cout << "DadosTarefasMovidas" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidas);
	}

	// caso tiver que imprimir as construções entra no if
	if( ImprimeVetorCosntrucoes == 1){
		// imprime as cosntruções
		cout << "  ConstrucaosAnalizadas " << endl;
		ImprimeVetorInt(ConstrucaosAnalizadas);
	}

	if( ParaPrograma == 1){
		cin >> numero;
	}
}

// inicia o vector de int com todos os seus valores como 0
void IniciaVetorIntComZero(vector< int > &VetorInt){
	// percorre todo os elementos do  vector
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		 // aloca o valor 0 ao elemento do vector corrente
		VetorInt[i] = 0;
	}
}



// verifica se existe um valor no vector igual ao valor passado
int VerificaSeTemUmValorVetorInt( int Valor, vector< int > VetorInt){
	// percorre todo os elementos do  vector
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		// verifica se o elemento do vector é igual ao valor passado
		if( VetorInt[i] == Valor){
			// retorna 1 caso se tenha um valor igual ao valor passado
			 return 1;
		 }
	}
	// retorna 0, não tem nenhum elemento com o mesmo valor do valor passado
	return 0;
}

// verifica se todos os valores do vector são iguais ao valor passado
int VerificaTodosValoresVetorInt( int Valor, vector< int > VetorInt){
	// percorre todo os elementos do  vector
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		// verifica se o elemento do vector não é igual ao valor passado
		if( VetorInt[i] != Valor){
			// retorna 0 caso se tenha um valor diferente ao valor passado
			 return 0;
		 }
	}
	// retorna 1, todos os valores são iguais ao valor passado
	return 1;
}

// imprime os valores do vector de elementos double
void ImprimeVetorDouble( vector< double > VetorDouble){
	cout << " Conteudo Vetor "<< endl;
	// percorre todo os elementos do  vector
	for(unsigned int i = 0; i < VetorDouble.size(); i++){
		cout << " [" << i << "] " << VetorDouble[i] << " ";
	}
	cout << endl;
}

#endif /* FUNCOESSOLUCOES_HPP_ */
