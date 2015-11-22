/*
 * FuncoesSolucoes.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mateus.vilela
 */

#ifndef FUNCOESSOLUCOES_HPP_
#define FUNCOESSOLUCOES_HPP_

#include "Bibliotecas.hpp"


void AlocaValoresIniciaisIndices(int& c, int& d);
int VerificaInidices( int c, int d);
int VerificaInidices2( int p, int v);

void ImprimeVetorInt( vector< int > VetorInt );
void ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( int ImprimeDesalocados, vector < DadosTarefa > DadosTarefasDesalocadas, int ImprimeAlocados, vector < DadosTarefa > DadosTarefasAdicionadas, int ImprimeVetorCosntrucoes, vector < int > ConstrucaosAnalizadas, int ParaPrograma);
void IniciaVetorIntComZero(vector< int > &VetorInt);

int VerificaSeTemUmValorVetorInt( int Valor, vector< int > VetorInt);
int VerificaTodosValoresVetorInt( int Valor, vector< int > VetorInt);

void AlocaValoresIniciaisIndices( int& c, int& d){
	c = -13;
	d = -13;
}

int VerificaInidices( int c, int d){
	if( c == -13 || d == -13 ){
			cout  << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao &&&&&&&&&&&&& " << endl << endl << endl;
			return -1;
		}
	return 1;
}

int VerificaInidices2( int p, int v){
	if( p == -13 || v == -13 ){
			cout  << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a planta ou caminhao &&&&&&&&&&&&& " << endl << endl << endl;
			return -1;
		}
	return 1;
}

void ImprimeVetorInt( vector< int > VetorInt){
	cout << " Conteudo Vetor "<< endl;
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		cout << " [" << i << "] " << VetorInt[i] << " ";
	}
	cout << endl;
}

void ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( int ImprimeDesalocados, vector < DadosTarefa > DadosTarefasDesalocadas, int ImprimeAlocados, vector < DadosTarefa > DadosTarefasAdicionadas, int ImprimeVetorCosntrucoes, vector < int > ConstrucaosAnalizadas, int ParaPrograma){
	int numero;

	if ( ImprimeDesalocados == 1){
		cout << "DadosTarefasDesalocadas" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasDesalocadas);
	}

	if ( ImprimeAlocados == 1){
		cout << "DadosTarefasAdicionadas" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasAdicionadas);
	}

	if( ImprimeVetorCosntrucoes == 1){
		cout << "  ConstrucaosAnalizadas " << endl;
		ImprimeVetorInt(ConstrucaosAnalizadas);
	}

	if( ParaPrograma == 1){
		cin >> numero;
	}
}

void IniciaVetorIntComZero(vector< int > &VetorInt){
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		 VetorInt[i] = 0;
	}
}

int VerificaSeTemUmValorVetorInt( int Valor, vector< int > VetorInt){
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		 if( VetorInt[i] == Valor){
			 return 1;
		 }
	}
	return 0;
}

int VerificaTodosValoresVetorInt( int Valor, vector< int > VetorInt){
	for(unsigned int i = 0; i < VetorInt.size(); i++){
		 if( VetorInt[i] != Valor){
			 return 0;
		 }
	}
	return 1;
}

#endif /* FUNCOESSOLUCOES_HPP_ */
