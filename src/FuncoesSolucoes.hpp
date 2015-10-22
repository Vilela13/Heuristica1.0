/*
 * FuncoesSolucoes.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mateus.vilela
 */

#ifndef FUNCOESSOLUCOES_HPP_
#define FUNCOESSOLUCOES_HPP_

#include "Bibliotecas.hpp"


void AlocaValoresIniciaisIndices(int&, int&);
int VerificaInidices( int, int);
int VerificaInidices2( int, int);
int VerificaValorUmVetorInt( vector< int > );
void ImprimeVetorInt( vector< int > );

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

int VerificaValorUmVetorInt( vector< int > VetorInt){
	for(int i = 0; i < VetorInt.size(); i++){
		if( VetorInt[i] != 1){
			return 0;
		}
	}
	return 1;
}

void ImprimeVetorInt( vector< int > VetorInt){
	cout << " Conteudo Vetor "<< endl;
	for(int i = 0; i < VetorInt.size(); i++){
		cout << " [" << i << "] " << VetorInt[i] << " ";
	}
	cout << endl;
}

#endif /* FUNCOESSOLUCOES_HPP_ */
