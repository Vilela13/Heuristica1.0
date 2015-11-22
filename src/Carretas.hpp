/*
 * Carretas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CARRETAS_HPP_
#define CARRETAS_HPP_

#include "Bibliotecas.hpp"

class Deslocamento{
public:
	double HorarioInicioDeslocamento;
	double HorarioFinalDeslocamento;
	int NumeroConstrucao;
	int NumeroDemandaSuprida;

	int verifica(int construcao,int NumeroDemandaSuprida, double HorarioInicioVeiculo,double HorarioFimVeiculo);

};

int Deslocamento::verifica(int construcao,int Demanda, double HorarioInicioVeiculo,double HorarioFimVeiculo){
	if( construcao == NumeroConstrucao && Demanda == NumeroDemandaSuprida && HorarioInicioVeiculo == HorarioInicioDeslocamento && HorarioFimVeiculo == HorarioFinalDeslocamento){
		return 1;
	}
	return 0;
}

bool DecideQualMenorInicioTempoDeslocamento ( Deslocamento c1, Deslocamento c2 ){
	return ( c1.HorarioInicioDeslocamento < c2.HorarioInicioDeslocamento );
}

class Carreta{

public:
	Carreta();
	int NumeroDaCarreta;
	int NumeroDeDemandasAntendidas;
	int NumeroPlanta;
	vector < vector < double > > TempoParaDescarregarNaConstrucao;
	vector < Deslocamento > Deslocamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, int);

	int DeletaAtividade(double, double, int, int);

	void Imprime(int);


	~Carreta();

};

Carreta::Carreta(){						// Construtora
	NumeroDaCarreta = -13;
	NumeroDeDemandasAntendidas = -13;
	NumeroPlanta = -13;

}

int Carreta::VerificaDisponibilidade(double InicioPossivelAlocacao, double FinalPossivelAlocacao){		// verifica a disponibilidade do veículo para atender a demanda

	for( unsigned int d = 0; d < Deslocamentos.size(); d ++){
		// verifica se o deslocamento que se quer colocar possui dentro de se um deslocamento já alocado
		if( InicioPossivelAlocacao <= Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao >= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		// verifica se o deslocamento que se quer colocar está dentro de se um deslocamento já alocado
		if( InicioPossivelAlocacao >= Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao <= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		// verifica se o deslocamento que se quer colocar possui a parte posterior dentro de um deslocamento alocado
		if( InicioPossivelAlocacao <= Deslocamentos[d].HorarioInicioDeslocamento){
			if( FinalPossivelAlocacao > Deslocamentos[d].HorarioInicioDeslocamento){
				return 0;
			}
		}
		// verifica se o deslocamento que se quer colocar possui a parte anterior dentro de um deslocamento alocado
		if( InicioPossivelAlocacao < Deslocamentos[d].HorarioFinalDeslocamento){
			if ( FinalPossivelAlocacao >= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
	}

	return 1;

}

void Carreta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){	// Aloca veículo para atender a demanda

	NumeroDeDemandasAntendidas = NumeroDeDemandasAntendidas + 1;

	Deslocamento DeslocamentoAux;

	DeslocamentoAux.HorarioInicioDeslocamento = HoraInicio;
	DeslocamentoAux.HorarioFinalDeslocamento = HoraFinal;
	DeslocamentoAux.NumeroConstrucao = NumContrucao;
	DeslocamentoAux.NumeroDemandaSuprida = NumDemanda;

	//cout << endl << endl << "     ******** aloca  caminhao ********* " << endl;
	//cout << " inicio " << HoraInicio << " final " << HoraFinal <<endl;

	Deslocamentos.insert(Deslocamentos.begin(), DeslocamentoAux );

}

int Carreta::DeletaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){	// Deleta alocação de demanda alocada ao veículo
	for( vector < Deslocamento >::iterator it = Deslocamentos.begin(); it != Deslocamentos.end(); it++){
		if( it->HorarioInicioDeslocamento == HoraInicio){
			if( it->HorarioFinalDeslocamento == HoraFinal){
				if( it->NumeroConstrucao == NumContrucao){
					if( it->NumeroDemandaSuprida == NumDemanda){
						NumeroDeDemandasAntendidas = NumeroDeDemandasAntendidas - 1;
						Deslocamentos.erase(it);
						//cout << endl << endl << " ************* deletou " << Deslocamentos.size() << endl << endl ;
						return 1;
					}
				}
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou elemento deslocamento [" << NumContrucao << "-" << NumDemanda << "] a deletar !  -> Carreta::DeletaAtividade ################## " << endl << endl;
	return 0;
}

void Carreta::Imprime(int Ordena){			// Imprime as atividades realizadas pelo veículo

	if( Ordena == 1){
		sort (Deslocamentos.begin(), Deslocamentos.end(), DecideQualMenorInicioTempoDeslocamento);
	}
	cout << "# Carreta [" << NumeroPlanta << "-" << NumeroDaCarreta << "] que atendeu " << NumeroDeDemandasAntendidas << " demandas" << endl;
	for( int d = 0; d < NumeroDeDemandasAntendidas; d++){
		printf( "    *  Atender a [%d-%d] de (%.4f - %.4f)\n", Deslocamentos[d].NumeroConstrucao, Deslocamentos[d].NumeroDemandaSuprida, Deslocamentos[d].HorarioInicioDeslocamento, Deslocamentos[d].HorarioFinalDeslocamento);
	}
}

Carreta::~Carreta(){						// Destruidora

}

bool DecideQualCarretaTemMenosTarefasRealizadas ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDeDemandasAntendidas < c2.NumeroDeDemandasAntendidas );
}
bool DecideQualCarretaTemMaisTarefasRealizadas ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDeDemandasAntendidas > c2.NumeroDeDemandasAntendidas );
}


class ConjuntoCarretas{

public:
	ConjuntoCarretas();
	vector< Carreta > Carretas;

	void IniciaConjuntoCarretas(int, int);

	void OrdenaCarretasPorNumeroDeTarefasRealizadas(int);

	int DeletaTarefa( int, double, double, int, int);

	int AlocaInidiceVeiculo( int, int&);

	void Imprime(int);

	~ConjuntoCarretas();
};

bool DecideCarretaAnterior ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDaCarreta < c2.NumeroDaCarreta );
}

ConjuntoCarretas::ConjuntoCarretas(){

}

void ConjuntoCarretas::IniciaConjuntoCarretas(int NumeroCaminhoes, int NumeroDaPlanta){		// inicia os dados e as estruturas dos veículos
	Carretas.resize(NumeroCaminhoes);
	for(int v = 0; v < NumeroCaminhoes; v++){
		Carretas[v].NumeroDaCarreta = v;
		Carretas[v].NumeroDeDemandasAntendidas = 0;
		Carretas[v].Deslocamentos.clear();
		Carretas[v].NumeroPlanta = NumeroDaPlanta;
	}

}

// ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
void ConjuntoCarretas::OrdenaCarretasPorNumeroDeTarefasRealizadas(int TipoOrdenacao){
	if( TipoOrdenacao == 1){
		sort (Carretas.begin(), Carretas.end(), DecideQualCarretaTemMenosTarefasRealizadas);
	}
	if( TipoOrdenacao == 2){
			sort (Carretas.begin(), Carretas.end(),DecideQualCarretaTemMaisTarefasRealizadas);
	}
}

int ConjuntoCarretas::DeletaTarefa( int NumeroCaminhao, double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){		// deleta tarefa realizada por um veiculo
	int Retirou;
	Retirou = 0;
	for( unsigned int c = 0; c < Carretas.size(); c++){
		if( Carretas[c].NumeroDaCarreta == NumeroCaminhao){
			Retirou = Carretas[c].DeletaAtividade(HoraInicio, HoraFinal, NumContrucao, NumDemanda);
			if( Retirou == 1){
				return 1;
			}else{
				cout << endl << endl << " ###########################   Problema! Não encontrou elemento deslocamento [" << NumContrucao << "-" << NumDemanda << "] a deletar !  -> ConjuntoCarretas::DeletaTarefa ################## " << endl << endl;
				return 0;
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou caminhao [" << NumeroCaminhao << "] a deletar !  -> ConjuntoCarretas::DeletaTarefa ################## " << endl << endl;
	return 0;
}

int ConjuntoCarretas::AlocaInidiceVeiculo( int NumCarretaUtilizada, int &v){
	for( unsigned int i = 0; i < Carretas.size(); i++){
		if ( Carretas[i].NumeroDaCarreta == NumCarretaUtilizada ){
			v = i;
			return 1;
		}
	}
	return 0;
}

void ConjuntoCarretas::Imprime(int Ordena){		// Imprime os dados dos veiculos
	if(Ordena == 1){
		sort (Carretas.begin(), Carretas.end(), DecideCarretaAnterior);
	}
	cout  << " [[[[[[  Imprime carretas  ]]]]]]" << endl;
	for( unsigned int c = 0; c < Carretas.size(); c++){
		Carretas[c].Imprime(Ordena);
	}
}

ConjuntoCarretas::~ConjuntoCarretas(){

}


#endif /* CARRETAS_HPP_ */
