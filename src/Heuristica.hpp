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
	double Velocidade;
	double TempoDeVidaConcreto;

	int  LeDados(string, int );
	void LeNomeInstancia(int , string& );
	void LeNumeroPlantasEntregasVeiculos(int);
	void LeVelocidade(int);
	void LeTempoDeVidaConcreto(int);
	void LeVeiculosPorPlanta(int);
	void LeNumeroDemandas(int);
	void LeDistancias(int);
	void LeTempoConstrucao(int);


    ~Heuristica();

};

Heuristica::Heuristica(){

}

int Heuristica::LeDados(string Nome, int comentarios){

	string Instancia;
	string CaminhoArquivo1;

	char *cstr;


// Abre arquivo das instâncias

	CaminhoArquivo1 = "./InstS/";
	CaminhoArquivo1 += Nome;

	cstr = new char[CaminhoArquivo1.length() + 1];
	strcpy(cstr, CaminhoArquivo1.c_str());


	cout << " Arquivo a abrir : " << cstr << endl;

	arq.open(cstr);
	delete [] cstr;
	if (arq.is_open()){
		LeNomeInstancia(comentarios, Instancia);
		LeNumeroPlantasEntregasVeiculos(comentarios);
		LeVelocidade(comentarios);
		LeTempoDeVidaConcreto(comentarios);
		LeVeiculosPorPlanta( comentarios);
		LeNumeroDemandas(comentarios);
		LeDistancias(comentarios);
		LeTempoConstrucao(comentarios);

		arq.close();
		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << CaminhoArquivo1 << endl << endl;
		return 0;
	}
}

void Heuristica::LeNomeInstancia(int comentarios, string& Instancia){
	arq >> Instancia;
	if( comentarios == 1){
		cout << " Nome instancia "<<  Instancia << endl;
	}
}

void Heuristica::LeNumeroPlantasEntregasVeiculos(int comentarios){
	arq >> NP;
	PlantasInstancia.IniciaConjuntoPlantas(NP);
	arq >> NE;
	ConstrucoesInstancia.IniciaConjuntoConstrucoes(NE);
	arq >> NV;

	if( comentarios == 1){
		cout << " Numero de plantas "<<  NP << endl;
		cout << " Numero de Entregas "<< NE << endl;
		cout << " Numero de Veiculos "<< NV << endl;
	}
}

void Heuristica::LeVelocidade(int comentarios){
	arq >> Velocidade;
	if( comentarios == 1){
		cout << " Velocidade "<<  Velocidade << endl;
	}
}

void Heuristica::LeTempoDeVidaConcreto(int comentarios){
	arq >> TempoDeVidaConcreto;
	if( comentarios == 1){
		cout << " Tempo De Vida Concreto "<<  TempoDeVidaConcreto << endl;
	}
}

void Heuristica::LeVeiculosPorPlanta(int comentarios){
	int aux;
	for (int i = 0; i < NP ; i++){
		arq >> PlantasInstancia.Plantas[i].NumeroVeiculos;
		PlantasInstancia.Plantas[i].VeiculosDaPlanta.IniciaConjuntoCarretas( PlantasInstancia.Plantas[i].NumeroVeiculos );
		if( comentarios == 1){
			cout << " Numero de veiculo na planta  " << i + 1 << " = " << PlantasInstancia.Plantas[i].NumeroVeiculos << "  ( ";
		}
		for ( int j = 0; j < PlantasInstancia.Plantas[i].NumeroVeiculos; j++){
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}

}

void Heuristica::LeNumeroDemandas(int comentarios){
	int aux;
	for (int i = 0; i < NE ; i++){
		arq >> ConstrucoesInstancia.Construcoes[i].NumeroDemandas;
		if( comentarios == 1){
			cout << " Numero de demandas na construção " << i + 1 << " = " << ConstrucoesInstancia.Construcoes[i].NumeroDemandas << "  ( ";
		}
		for ( int j = 0; j < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; j++){
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}
}

void Heuristica::LeDistancias(int comentarios){
	if( comentarios == 1){
		cout << "     Distancia Planta para Construcoes"<< endl;
	}
	for (int i = 0; i < NP ; i++){
		PlantasInstancia.Plantas[i].DistanciaConstrucoes.resize(NE);
		for ( int j = 0; j < NE; j++){
			arq >> PlantasInstancia.Plantas[i].DistanciaConstrucoes[j];
			if( comentarios == 1){
				cout << PlantasInstancia.Plantas[i].DistanciaConstrucoes[j] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	}
	if( comentarios == 1){
		cout << "     Distancia Construcoes para Plantas"<< endl;
	}
	for (int i = 0; i < NE ; i++){
		ConstrucoesInstancia.Construcoes[i].DistanciaPlantas.resize(NP);
		for ( int j = 0; j < NP; j++){
			arq >> ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[j];
			if( comentarios == 1){
				cout <<  ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[j] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}

}

void Heuristica::LeTempoConstrucao(int comentarios){
	int aux;

	if( comentarios == 1){
		cout << "     Tempo de cada veiculo em cada cosntrucao "<< endl;
	}
	for (int p = 0; p < NP ; p++){
		for (int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos ; v++){
			arq >> aux;
			if( comentarios == 1){
				cout << " Veiculo  " << aux << endl;
			}
			PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoConstrucao.resize( NE);
			for ( int c = 0; c < NE; c++){
				arq >> aux;
				if ( aux != ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
					cout << "        ############## Dados Incosistentes ############## " << endl << endl;
				}
				PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoConstrucao[c].resize( ConstrucoesInstancia.Construcoes[c].NumeroDemandas );
				for ( int d = 0; d < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; d++){
					arq >> PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoConstrucao[c][d];
					if( comentarios == 1){
						cout << PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoConstrucao[c][d] << "  ";
					}
				}
				if( comentarios == 1){
					cout << endl;
				}
			}
		}

	}
}

Heuristica::~Heuristica(){

}

#endif /* HEURISTICA_HPP_ */
