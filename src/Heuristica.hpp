/*
 * Heuristica.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef HEURISTICA_HPP_
#define HEURISTICA_HPP_

#include "Bibliotecas.hpp"

class Heuristica{

public:
	Heuristica();

	ifstream arq;
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	ConjuntoCarretas CarretasInstancia;

	int  LeDados(char*, int );
	void LeNomeInstancia(int comentarios, string* Instancia);
	void LeNumeroPlantasEntregasVeiculos(int);


    ~Heuristica();

};

Heuristica::Heuristica(){

}

int Heuristica::LeDados(char *a, int comentarios){

	char *b;
	string Instancia;
	string CaminhoArquivo1;


// Abre arquivo das instâncias

	CaminhoArquivo1 = "./InstS/";

	b = new char[CaminhoArquivo1.size()+1];
	b[CaminhoArquivo1.size()]=0;
	memcpy(b,CaminhoArquivo1.c_str(),CaminhoArquivo1.size());
	strcat(b,a);

	cout << " Arquivo a abrir : " << b << endl;

	arq.open(b);
	if (arq.is_open()){
		LeNomeInstancia(comentarios, &Instancia);
		LeNumeroPlantasEntregasVeiculos(comentarios);

		arq.close();
		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << a << endl << endl;
		return 0;
	}
}

void Heuristica::LeNomeInstancia(int comentarios, string* Instancia){
	arq >> *Instancia;
	if( comentarios == 1){
		cout << " Nome instancia "<<  *Instancia << endl;
	}
}

void Heuristica::LeNumeroPlantasEntregasVeiculos(int comentarios){
	arq >> NP;
	PlantasInstancia.IniciaConjuntoPlantas(NP);
	arq >> NE;
	ConstrucoesInstancia.IniciaConjuntoConstrucoes(NE);
	arq >> NV;
	CarretasInstancia.IniciaConjuntoCarretas(NV);

	if( comentarios == 1){
		cout << " Numero de plantas "<<  NP << endl;
		cout << " Numero de Entregas "<< NE << endl;
		cout << " Numero de Veiculos "<< NV << endl;
	}
}

Heuristica::~Heuristica(){

}

#endif /* HEURISTICA_HPP_ */
