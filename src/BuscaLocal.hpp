/*
 * BuscaLocal.hpp
 *
 *  Created on: Dec 15, 2015
 *      Author: mateus.vilela
 */

#ifndef BUSCALOCAL_HPP_
#define BUSCALOCAL_HPP_

#include "Bibliotecas.hpp"


class BuscaLocal{
public:

// estruturas que armazenam os dados da instancia
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	double Makespan;


	BuscaLocal();

	void CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);		// Carrega os dados da instancia e a solução até o momento
	int SelecionaConstrucao( int &ConstrucaoEscolhida, int &IndiceConstrucaoEscolhida);


	int AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao , int imprime, string frase);		// função que tenta alocar uma demanda
	double CalculaMakespanSolucoes();				// calcula o makespan
	int ExisteConstrucaoParaRetirar( int IndiceConstrucaoEscolhida, int &ConstrucaoComDeandaRetirar, int &IndiceConstrucaoComDeandaRetirar);

	int BuscaLocalRetiraTarefasUmaConstrucao(int Imprime);

	~BuscaLocal();
};

// construtora da classe
BuscaLocal::BuscaLocal(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
	Makespan = -13;
}


// Carrega os dados da instancia e a solução até o momento
void BuscaLocal::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
}

int BuscaLocal::SelecionaConstrucao( int &ConstrucaoEscolhida, int &IndiceConstrucaoEscolhida ){
	double RankInicial;
	int Ativo;

	// inicia variaveis
	Ativo = 0;
	RankInicial = DBL_MAX;

	// passa por todas as construções
	for( int c = 0; c < NE; c++){
		// seleciona a que tem um rank maior que a selecionada no momento
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			// verifica se a construção ainda pode ser analisada
			if( ConstrucoesInstancia.ConstrucoesAnalizadas[c] == 0){
				// armazena os dados da cosntrução corrente
				ConstrucaoEscolhida = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
				IndiceConstrucaoEscolhida = c;
				RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
				// marca que encontrou uma construção
				Ativo = 1;
			}
		}
	}
	if( Ativo == 1){
		// retorna 1 caso encontrou uma construção
		return 1;
	}else{
		// retorna 0 caso não encontrou uma construção
		return 0;
	}

}





// calcula o makespan
double BuscaLocal::CalculaMakespanSolucoes(){
	// calcula o makespan da solução corrente de suas construções
	ConstrucoesInstancia.CalculaMakespansConstrucoes();
	// calcula o makespan da solução corrente de suas plantas
	PlantasInstancia.CalculaMakespanPlantas();
	// calcula o makespan da solução
	Makespan = ConstrucoesInstancia.MakespanConstrucoes + PlantasInstancia.MakespanPLantas;
	return Makespan;

}

int BuscaLocal::ExisteConstrucaoParaRetirar( int IndiceConstrucaoEscolhida, int &ConstrucaoComDeandaRetirar, int &IndiceConstrucaoComDeandaRetirar){
	for( int c = 0; c < NE; c++){
		if( c != IndiceConstrucaoEscolhida ){
			for( int d = 0; d < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; d++){
				if( ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] == 0){
					ConstrucaoComDeandaRetirar = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					IndiceConstrucaoComDeandaRetirar = c;
					return 1;
				}
			}
		}
	}
	return 0;
}

int BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao(int Imprime){

	int ConstrucaoEscolhida;
	int IndiceConstrucaoEscolhida;

	int ConstrucaoComDeandaRetirar;
	int IndiceConstrucaoComDeandaRetirar;


	vector < DadosTarefa > DadosTarefasMovidas;

	double MakespanAnterior;

	int ParaPrograma;


	if( ConstrucoesInstancia.Construcoes.size() > 1){
		// Faz com que nenhuma construção tenha sido retirada no procedimento
		ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

		if( Imprime == 1){
			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
			PlantasInstancia.Imprime(1,1);
			cin >> ParaPrograma;
		}

		while( VerificaSeTemUmValorVetorInt( 0, ConstrucoesInstancia.ConstrucoesAnalizadas ) == 1){
			// reinicia o estado de deslocamento e remoção de todas as demandas de todas as construções
			ConstrucoesInstancia.ReiniciaTarefasRetiradas();

			if( SelecionaConstrucao( ConstrucaoEscolhida, IndiceConstrucaoEscolhida) == 0){
				cout << endl << endl << "       >>>>>>>>>> Problema! Não encontrou uma construção para ser analisada na busca local! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
			}

			if( Imprime == 1){
				cout << endl <<  "  >>>>>>>>>>>>>>>>>>>>  Escolheu a construção [" << ConstrucaoEscolhida << "] para retirar suas demandas " << endl ;
			}

			for( int DemandaRetirar = 0; DemandaRetirar < ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].StatusAtendimento; DemandaRetirar++){
				DadosTarefasMovidas.clear();
				MakespanAnterior = CalculaMakespanSolucoes();

				if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].DeletaTarefas(0, DemandaRetirar,DadosTarefasMovidas, PlantasInstancia) == 0){
					cout << endl << endl << "       >>>>>>>>>> Problema! Não consegui deletar todas as demandas da construção [" << ConstrucaoEscolhida << "] ! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
				}

				if( Imprime == 1){
					cout << endl <<  "  >>>>>>  Deletou demandas apartir de [" << ConstrucaoEscolhida << "-" << DemandaRetirar << "] " << endl ;
					cout << endl <<  "         Dados das tarefas movidas" << endl;
					ImprimeVetorDadosTarefa(DadosTarefasMovidas);
					cin >> ParaPrograma;
				}

				if( CalculaMakespanSolucoes() < MakespanAnterior ){
					// retorna um caso consiga melhorar a solução
					if( Imprime == 1){
						cout << endl << endl << " [[[[[[[[[[[[[[[[[[[ Melhorou a Solução ]]]]]]]]]]]]]]]]]]]]]" << endl << endl;
					}
					return 1;
				}else{
					cout << endl << endl << " Inicio Retorna solução inicial" << endl << endl;
					ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia );
					cout << endl << endl << " Final Retorna solução inicial" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
					PlantasInstancia.Imprime(1,1);
					cin >> ParaPrograma;

				}

			}
			ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoEscolhida] = 1;
			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia,0);

		}
		// retorna zero caso não consiga melhorar a solução
		return 0;
	}
	if( Imprime == 1){
		cout << endl << endl << "       >>>>>>>>>>>>>>>>>>>>> Não possui construções suficientes para realizar este procedimento! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao <<<<<<<<<<<<<<<<<<< " << endl << endl;
	}
	return 0;
}

BuscaLocal::~BuscaLocal(){

}


#endif /* BUSCALOCAL_HPP_ */
