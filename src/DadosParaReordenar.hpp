/*
 * DadosParaReordenar.hpp
 *
 *  Created on: Oct 22, 2015
 *      Author: mateus.vilela
 */

#ifndef DADOSPARAREORDENAR_HPP_
#define DADOSPARAREORDENAR_HPP_

#include "Bibliotecas.hpp"


class DadosParaReordenar{
public:
	DadosParaReordenar();
	 vector < int >  DadosDasTarefasRetiradas; 		// 0 -> NumConstrução , 1 -> NumDemanda , 2 -> NumPlanta , 3 -> NumCarreta
	 vector < double > HorariosDasTarefasRetiradas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta
	void IniciaConteudo();
	void InserirConteudo(int, int, int, int, double, double, double, double, double);
	void Imprimir();
	~DadosParaReordenar();
};

DadosParaReordenar::DadosParaReordenar(){

}

void DadosParaReordenar::IniciaConteudo(){
	DadosDasTarefasRetiradas.resize(4);
	HorariosDasTarefasRetiradas.resize(5);
}

void DadosParaReordenar::InserirConteudo(int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta ){
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

void DadosParaReordenar::Imprimir(){
	cout << " Construcao [" << DadosDasTarefasRetiradas[0] << "-" << DadosDasTarefasRetiradas[1] << "]";
	cout << "tempo (" << HorariosDasTarefasRetiradas[2] << "-" << HorariosDasTarefasRetiradas[3] << ") ";
	cout << " Planta [" << DadosDasTarefasRetiradas[2] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[1] << ") ";
	cout << " Caminhao [" << DadosDasTarefasRetiradas[2] << "-" << DadosDasTarefasRetiradas[3] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[4] << ") " << endl;
}

DadosParaReordenar::~DadosParaReordenar(){

}

bool DecideQualTarefaVemAntesReordenar ( DadosParaReordenar d1, DadosParaReordenar d2 ){
	return ( d1.HorariosDasTarefasRetiradas[2] < d2.HorariosDasTarefasRetiradas[2] );
}



#endif /* DADOSPARAREORDENAR_HPP_ */
