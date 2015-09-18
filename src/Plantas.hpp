/*
 * Plantas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef PLANTAS_HPP_
#define PLANTAS_HPP_

#include "Bibliotecas.hpp"

class Carregamento{
public:
	double HorarioInicioCarregamento;
	double HorarioFinalCarregamento;
	int NumeroConstrucao;
	int NumeroDemandaSuprida;
	int NumCarretaUtilizada;
};

bool DecideQualMenorInicioTempoCarregamento ( Carregamento c1, Carregamento c2 ){
	return ( c1.HorarioInicioCarregamento < c2.HorarioInicioCarregamento );
}

class Planta{

public:
	Planta();
	int NumeroDaPlanta;
	int NumeroVeiculos;
	ConjuntoCarretas VeiculosDaPlanta;
	vector < double > DistanciaConstrucoes;
	double TempoPlanta;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;

	vector < Carregamento > Carregamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double , double, int , int , int);
	int DeletaAtividade(double , double, int , int , int);

	void Imprime();

	void ImprimeDistancias();

	~Planta();

};

Planta::Planta(){
	NumeroDaPlanta = -13;
	NumeroVeiculos = -13;
	TempoPlanta = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
}

int Planta::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	for( unsigned int c = 0; c < Carregamentos.size(); c++){
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao >= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao <= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if( FinalPossivelAlocacao > Carregamentos[c].HorarioInicioCarregamento){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Carregamentos[c].HorarioFinalCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
	}
	return 1;
}

void Planta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
	Carregamento CarregamentoAux;

	CarregamentoAux.HorarioInicioCarregamento = HoraInicio;
	CarregamentoAux.HorarioFinalCarregamento = HoraFinal;
	CarregamentoAux.NumeroConstrucao = NumConstrucao;
	CarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	CarregamentoAux.NumCarretaUtilizada = Carreta;

	Carregamentos.insert(Carregamentos.begin(), CarregamentoAux );

}

int Planta::DeletaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
	for( vector < Carregamento >::iterator it = Carregamentos.begin(); it != Carregamentos.end(); it++){
		if( it->HorarioInicioCarregamento == HoraInicio){
			if( it->HorarioFinalCarregamento == HoraFinal){
				if( it->NumeroConstrucao == NumConstrucao){
					if( it->NumeroDemandaSuprida == NumDemanda){
						if( it->NumCarretaUtilizada == Carreta){
							Carregamentos.erase(it);
							return 1;
						}
					}
				}
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou elemento carregamento [" << NumConstrucao << "-" << NumDemanda << "] a deletar !  -> Planta::DeletaAtividade ################## " << endl << endl;
	return 0;
}

void Planta::Imprime(){
	cout << endl;
	cout << "# Planta " << NumeroDaPlanta << " com " << NumeroVeiculos << " veiculos, funciona de (";
	cout << TempoMinimoDeFuncionamento << ", "<< TempoMaximoDeFuncionamento << ")" << endl;

	sort (Carregamentos.begin(), Carregamentos.end(), DecideQualMenorInicioTempoCarregamento);
	if ( Carregamentos.size() != 0 ){
		cout << "   Carregamentos " << endl;
		for( unsigned int c = 0; c < Carregamentos.size(); c++){
			cout << "    * Caminhao [" << NumeroDaPlanta << "-" << Carregamentos[c].NumCarretaUtilizada;
			cout << "] para suprir construcao [" << Carregamentos[c].NumeroConstrucao << "-" << Carregamentos[c].NumeroDemandaSuprida;
			cout << "] das ( "<< Carregamentos[c].HorarioInicioCarregamento << " as " << Carregamentos[c].HorarioFinalCarregamento << " ) " << endl;
		}
	}

	cout <<  "    =>  Veiculos da Planta " << NumeroDaPlanta << " <= " << endl;
	VeiculosDaPlanta.Imprime();

}

void Planta::ImprimeDistancias(){
	cout << " +++ Distancias ++++ " << endl;
	cout << "Numero de conatricoes " << DistanciaConstrucoes.size() << endl;
	for ( unsigned int c = 0; c < DistanciaConstrucoes.size(); c++){
		cout << "   Contrucao" << c << " = "<< DistanciaConstrucoes[c] << endl;
	}
}

Planta::~Planta(){

}


class ConjuntoPlantas{

public:
	ConjuntoPlantas();
	vector< Planta > Plantas;

	vector < int > PlantasAnalizadas;
	void InicializaPlantasAnalizadas();
	int AnalizouTodasPLanats();

	void IniciaConjuntoPlantas(int);

	int DeletaTarefa( int, double , double, int , int , int, double, double);

	void Imprime();


	~ConjuntoPlantas();
};

ConjuntoPlantas::ConjuntoPlantas(){

}

void ConjuntoPlantas::InicializaPlantasAnalizadas(){
	PlantasAnalizadas.resize(Plantas.size());
	for( unsigned  int p = 0; p < Plantas.size(); p++){
		PlantasAnalizadas[p] = 0;
	}
}

int ConjuntoPlantas::AnalizouTodasPLanats(){
	for ( unsigned  int p = 0; p < Plantas.size(); p++){
		if( PlantasAnalizadas[p] == 0){
			return 0;
		}
	}
	return 1;
}

void ConjuntoPlantas::IniciaConjuntoPlantas(int Numero){
	Plantas.resize(Numero);

}

int ConjuntoPlantas::DeletaTarefa( int NumPlanta, double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, double HoraInicioCarreta, double HoraFinalCarreta){
	int RetirouCarregamento;
	RetirouCarregamento = 0;

	int RetirouDeslocamento;
	RetirouDeslocamento = 0;

	for( int p = 0; p < Plantas.size(); p++){
		if( Plantas[p].NumeroDaPlanta == NumPlanta){
			RetirouCarregamento = Plantas[p].DeletaAtividade( HoraInicio, HoraFinal, NumConstrucao, NumDemanda, Carreta);
			RetirouDeslocamento = Plantas[p].VeiculosDaPlanta.DeletaTarefa(Carreta, HoraInicioCarreta, HoraFinalCarreta, NumConstrucao, NumDemanda);
			if( RetirouCarregamento == 1 && RetirouDeslocamento == 1){
				return 1;
			}else{
				if( RetirouCarregamento != 1){
					cout << endl << endl << " ###########################   Problema! Não encontrou elemento carregamento [" << NumConstrucao << "-" << NumDemanda << "] a deletar !  -> ConjuntoPlantas::DeletaTarefa ################## " << endl << endl;
				}
				if( RetirouDeslocamento != 1){
					cout << endl << endl << " ###########################   Problema! Não encontrou elemento delocamento [" << NumConstrucao << "-" << NumDemanda << "] da carreta [" << Carreta << "] a deletar !  -> ConjuntoPlantas::DeletaTarefa ################## " << endl << endl;
				}
				return 0;
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou planta [" << NumPlanta << "] a deletar !  -> ConjuntoPlantas::DeletaTarefa ################## " << endl << endl;
	return 0;

}

void ConjuntoPlantas::Imprime(){
	cout << endl << endl << " [[[[[[  Imprime plantas  ]]]]]]" << endl;
	for( unsigned int p = 0; p < Plantas.size(); p++){
		Plantas[p].Imprime();
	}
}

ConjuntoPlantas::~ConjuntoPlantas(){

}

#endif /* PLANTAS_HPP_ */
