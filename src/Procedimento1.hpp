/*
 * Procedimento1.hpp
 *
 *  Created on: Aug 20, 2015
 *      Author: mateus.vilela
 */

#ifndef PROCEDIMENTO1_HPP_
#define PROCEDIMENTO1_HPP_

class Procedimento1{

public:
	Procedimento1();

	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	void CarregaDados(int , ConjuntoPlantas, int, ConjuntoConstrucoes, int, double, double );

	int Executa();

    ~Procedimento1();

};

Procedimento1::Procedimento1(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
}

void Procedimento1::CarregaDados(int InstNP, ConjuntoPlantas InstPlantasInstancia, int InstNE, ConjuntoConstrucoes InstConstrucoesInstancia, int InstNV, double InstVelocidade, double InstTempoDeVidaConcreto){
	NP = InstNP;
	PlantasInstancia = InstPlantasInstancia;
	NE = InstNE;
	ConstrucoesInstancia  = InstConstrucoesInstancia;
	NV = InstNV;
	Velocidade = InstVelocidade;
	TempoDeVidaConcreto = InstTempoDeVidaConcreto;
}

int Procedimento1::Executa(){
	Planta* PlantaMaisPerto;
	Construcao* ConstrucaoVaiSerSuprida;
	double DistanciaPLanta;

	DistanciaPLanta= DBL_MAX;

	for( int c = 0; c < NE; c++){
		for( int p = 0; p < NP; p++){
			if ( DistanciaPLanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia && ConstrucoesInstancia.Construcoes[c].StatusAtendimento == 0){
				PlantaMaisPerto = &PlantasInstancia.Plantas[p];
				ConstrucaoVaiSerSuprida = &ConstrucoesInstancia.Construcoes[c];
				DistanciaPLanta = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
			}
		}
	}
	ConstrucaoVaiSerSuprida->ImprimeContrucao();
	PlantaMaisPerto->Imprime();
	for( int d = 0; d < ConstrucaoVaiSerSuprida->NumeroDemandas; d++){
	}
	return 1;
}

Procedimento1::~Procedimento1(){

}




#endif /* PROCEDIMENTO1_HPP_ */
