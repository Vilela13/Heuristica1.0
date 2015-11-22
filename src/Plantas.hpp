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

	int verifica(int NumCarreta, int construcao, int Demanda, double HorarioInicioPlanta, double HorarioFimPlanta);
};

int Carregamento::verifica( int NumCarreta, int construcao, int Demanda, double HorarioInicioPlanta, double HorarioFimPlanta){		// Verifica se estes dados representão o carregamento em questão
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

	int VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao);
	void AlocaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta);
	int DeletaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta);
	void CalculaMakespan();
	void Imprime(int OrdenaPlantas, int OrdenaCarretas);
	void ImprimeDistancias();

	~Planta();

};

Planta::Planta(){		// Construtora
	NumeroDaPlanta = -13;
	NumeroVeiculos = -13;
	TempoPlanta = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	Carregamentos.clear();
	Makespan = -13;
}

int Planta::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){			// Verifica a possibilidade de alocação da demanda
	//verifica se respeita os intervalos de atendimento da planta
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	// verifica se não viola outros acrregamentos que são realizados pela planta
	for( unsigned int c = 0; c < Carregamentos.size(); c++){
		// carregamento a alocar está dentro de outro carregamento
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		// carregamento a alocar contem outro carregamento
		if( InicioPossivelAlocacao >= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao <= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		// Carregamento possui sua parte final conflitando com a parte fronteira de outro carregamento
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if( FinalPossivelAlocacao > Carregamentos[c].HorarioInicioCarregamento){
				return 0;
			}
		}
		// Carregamento possui sua parte inicial conflitando com a parte posterior de outro carregamento
		if( InicioPossivelAlocacao < Carregamentos[c].HorarioFinalCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
	}
	return 1;
}

void Planta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){		// Aloca tarefa na planta
	Carregamento CarregamentoAux;

	CarregamentoAux.HorarioInicioCarregamento = HoraInicio;
	CarregamentoAux.HorarioFinalCarregamento = HoraFinal;
	CarregamentoAux.NumeroConstrucao = NumConstrucao;
	CarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	CarregamentoAux.NumCarretaUtilizada = Carreta;

	Carregamentos.insert(Carregamentos.begin(), CarregamentoAux );

}

int Planta::DeletaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){		// Deleta tarefa na planta
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

void Planta::CalculaMakespan(){			// calcula o Makes pan da Planta
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

void Planta::Imprime(int OrdenaPlantas, int OrdenaCarretas){		// Imprime dados da planta
	printf ("\n# Planta %d com %d veiculos, funciona de (%.4f - %.4f)\n", NumeroDaPlanta,NumeroVeiculos,TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento);
// Imprime os carregamentos das plantas
	if(OrdenaPlantas == 1){
		sort (Carregamentos.begin(), Carregamentos.end(), DecideQualMenorInicioTempoCarregamento);
	}
	if ( Carregamentos.size() != 0 ){
		cout << "   Carregamentos " << endl;
		for( unsigned int c = 0; c < Carregamentos.size(); c++){
			printf ("    * Caminhao [%d - %d] para suprir construcao [%d - %d] das ( %.4f as %.4f)\n", NumeroDaPlanta, Carregamentos[c].NumCarretaUtilizada, Carregamentos[c].NumeroConstrucao, Carregamentos[c].NumeroDemandaSuprida, Carregamentos[c].HorarioInicioCarregamento, Carregamentos[c].HorarioFinalCarregamento);
		}
	}
// Imprime os veículos da planta
	cout <<  "    =>  Veiculos da Planta " << NumeroDaPlanta << " <= " << endl;
	VeiculosDaPlanta.Imprime(OrdenaCarretas);

	cout << "   Makespan = " << Makespan << endl;

}

void Planta::ImprimeDistancias(){		// Imprime as distancias da planta as construções
	cout << " +++ Distancias ++++ " << endl;
	cout << "Numero de conatricoes " << DistanciaConstrucoes.size() << endl;
	for ( unsigned int c = 0; c < DistanciaConstrucoes.size(); c++){
		printf("   Contrucao %d = %.4f", c, DistanciaConstrucoes[c]);
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
	void IniciaConjuntoPlantas(int Numero);

	int DeletaTarefa( int NumPlanta, double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, double HoraInicioCarreta, double HoraFinalCarreta);
	void CalculaMakespanPlantas();
	int AlocaInidiceFabrica( int Planta, int &IndicePlanta);

	int CorrigeReferenciaCarregamentoDeslocamentoMaisUm(int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, double HorarioInicioDescarregamento,  double HorarioFinalDescarregamento);
	int CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento);
	void Imprime(int OrdenaPlantas,int OrdenaCarrtas);

	int VerificaPlantasAnalizadasPodemAtenderSeAtrazar();

	~ConjuntoPlantas();
};

ConjuntoPlantas::ConjuntoPlantas(){			// Cosntrutora da classe
	MakespanPLantas = -13;
}


void ConjuntoPlantas::InicializaPlantasAnalizadas(){ 			// Faz que nenhuma planta tenha sido analisada pelos algoritmos
	PlantasAnalizadas.resize(Plantas.size());
	for( unsigned  int p = 0; p < Plantas.size(); p++){
		PlantasAnalizadas[p] = 0;
	}
}

int ConjuntoPlantas::AnalizouTodasPLanats(){					// Verifica se já analisou todas as plantas
	for ( unsigned  int p = 0; p < Plantas.size(); p++){
		if( PlantasAnalizadas[p] == 0){
			return 0;
		}
	}
	return 1;
}

void ConjuntoPlantas::IniciaConjuntoPlantas(int Numero){		// Inicia o vetor de plantas da classe com o número de palnats que se quer
	Plantas.resize(Numero);

}


int ConjuntoPlantas::DeletaTarefa( int NumPlanta, double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, double HoraInicioCarreta, double HoraFinalCarreta){		// deleta tarefa tanto na planta e no veiculo que executa a tarefa
	// variaveis de controle
	int RetirouCarregamento;
	RetirouCarregamento = 0;

	int RetirouDeslocamento;
	RetirouDeslocamento = 0;


	for( unsigned int p = 0; p < Plantas.size(); p++){
		if( Plantas[p].NumeroDaPlanta == NumPlanta){
			// retira tarefa da planta
			RetirouCarregamento = Plantas[p].DeletaAtividade( HoraInicio, HoraFinal, NumConstrucao, NumDemanda, Carreta);
			// retira tarefa do caminhão
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

void ConjuntoPlantas::CalculaMakespanPlantas(){		// Calcula o Makespan de todas as Plantas
	MakespanPLantas = 0;

	for( unsigned int p = 0; p < Plantas.size(); p++){
		Plantas[p].CalculaMakespan();
		MakespanPLantas = MakespanPLantas + Plantas[p].Makespan;
	}
}

int ConjuntoPlantas::AlocaInidiceFabrica(int Planta, int &IndicePlanta){		// Aloca o inice da planta que corresponde a planat que se passa como parametro
	for ( unsigned int i  = 0; i < Plantas.size(); i ++){
		if( Plantas[i].NumeroDaPlanta == Planta){
			IndicePlanta = i;
			return 1;
		}
	}
	return 0;
}


int ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm( int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, double HorarioInicioDescarregamento,  double HorarioFinalDescarregamento ){ // corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em mais um
// Emcontra o indice da planta
	int p;
	if( AlocaInidiceFabrica(NumPlantaFornecedor,p) == 0){
		cout << endl << endl << " <<<<<<<< probelam com indice planta [" << NumPlantaFornecedor << "] => " << p << " -> ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa na planta
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].DistanciaConstrucoes[construcao] -  Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta + Plantas[p].TempoPlanta;

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
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarretaUtilizada, v) == 0 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarretaUtilizada << "] => " << v << " ->CorrigeReferenciaCarregamentoDeslocamentoMaisUm  >>>>>>>>>>>>> " << endl << endl ;
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
		if( ModificouCarregamento == 0 ){
			cout << endl << endl << " <<<<<<<< probelam em corrigir carregamento [" << construcao << "-" << NumeroDemandaSuprida << "] ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		if( ModificouDeslocamento == 0){
			cout << endl << endl << " <<<<<<<< probelam em corrigir deslocamento [" << construcao << "-" << NumeroDemandaSuprida << "]  ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		return 0;
	}

}

int ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento){		// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em menos um

// Emcontra o indice da planta
	int p;
	if( AlocaInidiceFabrica(NumPlanta,p) == 0){
		cout << endl << endl << " <<<<<<<< problema com indice planta [" << NumPlanta << "] => " << p << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa na planta
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].DistanciaConstrucoes[Construcao] -  Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  Plantas[p].TempoPlanta;

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
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarreta, v) == 0 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarreta << "] => " << v << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
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
		if( ModificouCarregamento == 0 ){
			cout << endl << endl << " <<<<<<<< probelam em corrigir carregamento [" << Construcao << "-" << Demanda << "] ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		if( ModificouDeslocamento == 0){
			cout << endl << endl << " <<<<<<<< probelam em corrigir deslocamento [" << Construcao << "-" << Demanda << "]  ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		return 0;
	}
}

void ConjuntoPlantas::Imprime(int OrdenaPlantas,int OrdenaCarrtas){		// Imprime os dados das plantas
	cout << endl << endl << " [[[[[[  Imprime plantas  ]]]]]]" << endl;
	for( unsigned int p = 0; p < Plantas.size(); p++){
		Plantas[p].Imprime(OrdenaPlantas, OrdenaCarrtas);
	}

	printf ("\n  Makespan Geral das Plantas = %.4f\n", MakespanPLantas);
}

int ConjuntoPlantas::VerificaPlantasAnalizadasPodemAtenderSeAtrazar(){		// verifica se uma das plantas em questão pode atender a demanda em questão caso de atrazar o atendimento das outras demandas da construção que se quer atender
	for ( unsigned  int p = 0; p < Plantas.size(); p++){
		if( PlantasAnalizadas[p] == -2){
			return 1;
		}
	}
	return 0;

}

ConjuntoPlantas::~ConjuntoPlantas(){

}

#endif /* PLANTAS_HPP_ */
