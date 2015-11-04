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

	int verifica( int , int , int , double , double );
};

int Carregamento::verifica( int NumCarreta, int construcao, int Demanda, double HorarioInicioPlanta, double HorarioFimPlanta){
	if( NumCarreta == NumCarretaUtilizada &&  construcao == NumeroConstrucao && Demanda == NumeroDemandaSuprida && HorarioInicioPlanta == HorarioInicioCarregamento && HorarioFimPlanta == HorarioFinalCarregamento){
		return 1;
	}
	return 0;
}

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

	double Makespan;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double , double, int , int , int);
	int DeletaAtividade(double , double, int , int , int);
	void CalculaMakespan();
	void Imprime(int,int);
	void ImprimeDistancias();

	~Planta();

};

Planta::Planta(){
	NumeroDaPlanta = -13;
	NumeroVeiculos = -13;
	TempoPlanta = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	Makespan = -13;
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

void Planta::CalculaMakespan(){
	Makespan = 0;

	if( Makespan > TempoMinimoDeFuncionamento){
		Makespan = TempoMinimoDeFuncionamento;
	}
	for( unsigned int v = 0; v < VeiculosDaPlanta.Carretas.size(); v++){
		for( unsigned int d = 0; d < VeiculosDaPlanta.Carretas[v].Deslocamentos.size(); d++){
			if( Makespan < VeiculosDaPlanta.Carretas[v].Deslocamentos[d].HorarioFinalDeslocamento){
				Makespan = VeiculosDaPlanta.Carretas[v].Deslocamentos[d].HorarioFinalDeslocamento;
			}
		}
	}


}

void Planta::Imprime(int OrdenaPlantas, int OrdenaCarretas){
	cout << endl;
	cout << "# Planta " << NumeroDaPlanta << " com " << NumeroVeiculos << " veiculos, funciona de (";
	cout << TempoMinimoDeFuncionamento << ", "<< TempoMaximoDeFuncionamento << ")" << endl;

	if(OrdenaPlantas == 1){
		sort (Carregamentos.begin(), Carregamentos.end(), DecideQualMenorInicioTempoCarregamento);
	}
	if ( Carregamentos.size() != 0 ){
		cout << "   Carregamentos " << endl;
		for( unsigned int c = 0; c < Carregamentos.size(); c++){
			cout << "    * Caminhao [" << NumeroDaPlanta << "-" << Carregamentos[c].NumCarretaUtilizada;
			cout << "] para suprir construcao [" << Carregamentos[c].NumeroConstrucao << "-" << Carregamentos[c].NumeroDemandaSuprida;
			cout << "] das ( "<< Carregamentos[c].HorarioInicioCarregamento << " as " << Carregamentos[c].HorarioFinalCarregamento << " ) " << endl;
		}
	}

	cout <<  "    =>  Veiculos da Planta " << NumeroDaPlanta << " <= " << endl;
	VeiculosDaPlanta.Imprime(OrdenaCarretas);

	cout << "   Makespan = " << Makespan << endl;

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

	double MakespanPLantas;

	void InicializaPlantasAnalizadas();
	int AnalizouTodasPLanats();
	void IniciaConjuntoPlantas(int);
	int DeletaTarefa( int, double , double, int , int , int, double, double);
	void CalculaMakespanPlantas();
	int AlocaInidiceFabrica( int, int&);
	int CorrigeReferenciaCarregamentoDeslocamentoMaisUm(int, int, int, int, double, double);
	int CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int, int, int, int, double, double);
	void Imprime(int, int);

	~ConjuntoPlantas();
};

ConjuntoPlantas::ConjuntoPlantas(){
	MakespanPLantas = -13;
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

	for( unsigned int p = 0; p < Plantas.size(); p++){
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

void ConjuntoPlantas::CalculaMakespanPlantas(){
	MakespanPLantas = 0;

	for( unsigned int p = 0; p < Plantas.size(); p++){
		Plantas[p].CalculaMakespan();
		MakespanPLantas = MakespanPLantas + Plantas[p].Makespan;
	}
}

int ConjuntoPlantas::AlocaInidiceFabrica(int Planta, int &IndicePlanta){
	for ( unsigned int i  = 0; i < Plantas.size(); i ++){
		if( Plantas[i].NumeroDaPlanta == Planta){
			IndicePlanta = i;
			return 1;
		}
	}
	return 0;
}

int ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm( int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, double HorarioInicioDescarregamento,  double HorarioFinalDescarregamento ){
	// Emcontra o indice da planta
	int p;
	if( AlocaInidiceFabrica(NumPlantaFornecedor,p) == 0){
		cout << endl << endl << " <<<<<<<< probelam com indice planta [" << NumPlantaFornecedor << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamento  >>>>>>>>>>>>> " << endl << endl ;
	}

	// Encontra os tempos relativos da tarefa na planta
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].DistanciaConstrucoes[construcao];
	HorarioFimPlanta = HorarioInicioPlanta -  Plantas[p].TempoPlanta;

	// Modifica o número da demanda suprida pela planta em questão em mais um
	int ModificouCarregamento;
	ModificouCarregamento = 0;

	for( unsigned int c = 0; c < Plantas[p].Carregamentos.size() ; c++){
		if( Plantas[p].Carregamentos[c].verifica( NumCarretaUtilizada, construcao, NumeroDemandaSuprida, HorarioInicioPlanta, HorarioFimPlanta) == 1 && ModificouCarregamento == 0){
			Plantas[p].Carregamentos[c].NumeroDemandaSuprida = Plantas[p].Carregamentos[c].NumeroDemandaSuprida + 1;
			ModificouCarregamento = 1;
		}
	}

	// Emcontra o indice do veículo
	int v;
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarretaUtilizada, v) == 1 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarretaUtilizada << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamento  >>>>>>>>>>>>> " << endl << endl ;
	}

	// Encontra os tempos relativos da tarefa no caminhão (veículo)
	double HorarioInicioVeiculo;
	double HorarioFimVeiculo;

	HorarioInicioVeiculo = HorarioInicioPlanta;
	HorarioFimVeiculo = HorarioFinalDescarregamento + Plantas[p].DistanciaConstrucoes[construcao];

	// Modifica o número da demanda suprida pelo caminhão (veículo) em questão em mais um
	int ModificouDeslocamento;
	ModificouDeslocamento = 0;

	for( unsigned int d = 0; d < Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.size() ; d++){
		if( Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].verifica( construcao, NumeroDemandaSuprida, HorarioInicioVeiculo, HorarioFimVeiculo) == 1 && ModificouDeslocamento == 0){
			Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida = Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida + 1;
			ModificouDeslocamento = 1;
		}
	}

	// verifica se realizou as mudanças desejadas
	if( ModificouCarregamento == 1 && ModificouDeslocamento == 1){
		return 1;
	}else{
		return 0;
	}

}

int ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento){

	// Emcontra o indice da planta
	int p;
	if( AlocaInidiceFabrica(NumPlanta,p) == 0){
		cout << endl << endl << " <<<<<<<< probelam com indice planta [" << NumPlanta << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamento  >>>>>>>>>>>>> " << endl << endl ;
	}

	// Encontra os tempos relativos da tarefa na planta
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].DistanciaConstrucoes[Construcao];
	HorarioFimPlanta = HorarioInicioPlanta -  Plantas[p].TempoPlanta;

	// Modifica o número da demanda suprida pela planta em questão em mais um
	int ModificouCarregamento;
	ModificouCarregamento = 0;

	for( unsigned int c = 0; c < Plantas[p].Carregamentos.size() ; c++){
		if( Plantas[p].Carregamentos[c].verifica(NumCarreta, Construcao, Demanda, HorarioInicioPlanta, HorarioFimPlanta) == 1 && ModificouCarregamento == 0){
			Plantas[p].Carregamentos[c].NumeroDemandaSuprida = Plantas[p].Carregamentos[c].NumeroDemandaSuprida - 1;
			ModificouCarregamento = 1;
		}
	}

	// Emcontra o indice do veículo
	int v;
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarreta, v) == 1 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarreta << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamento  >>>>>>>>>>>>> " << endl << endl ;
	}

	// Encontra os tempos relativos da tarefa no caminhão (veículo)
	double HorarioInicioVeiculo;
	double HorarioFimVeiculo;

	HorarioInicioVeiculo = HorarioInicioPlanta;
	HorarioFimVeiculo = HorarioFinalDescarregamento + Plantas[p].DistanciaConstrucoes[Construcao];

	// Modifica o número da demanda suprida pelo caminhão (veículo) em questão em mais um
	int ModificouDeslocamento;
	ModificouDeslocamento = 0;

	for( unsigned int d = 0; d < Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.size() ; d++){
		if( Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].verifica( Construcao, Demanda, HorarioInicioVeiculo, HorarioFimVeiculo) == 1 && ModificouDeslocamento == 0){
			Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida = Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida - 1;
			ModificouDeslocamento = 1;
		}
	}

	// verifica se realizou as mudanças desejadas
	if( ModificouCarregamento == 1 && ModificouDeslocamento == 1){
		return 1;
	}else{
		return 0;
	}
}

void ConjuntoPlantas::Imprime(int OrdenaPlantas,int OrdenaCarrtas){
	cout << endl << endl << " [[[[[[  Imprime plantas  ]]]]]]" << endl;
	for( unsigned int p = 0; p < Plantas.size(); p++){
		Plantas[p].Imprime(OrdenaPlantas, OrdenaCarrtas);
	}

	cout << endl << "  Makespan Geral das Plantas = "<< MakespanPLantas << endl;
}

ConjuntoPlantas::~ConjuntoPlantas(){

}

#endif /* PLANTAS_HPP_ */
