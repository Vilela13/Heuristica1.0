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

	BuscaLocal();	// construtora da classe

	void CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);		// Carrega os dados da instancia e a solução até o momento
	int SelecionaConstrucao( int &ConstrucaoEscolhida, int &IndiceConstrucaoEscolhida);					// seleciona a construção ainda não avaliada que tera suas demandas atendidas avaliadas pela busca local

	int AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao , int imprime, string frase);		// função que tenta alocar uma demanda
	double CalculaMakespanSolucao();				// calcula o makespan


	int BuscaLocalTentaRealizarTarefasComOutosVeiculos(int Imprime, int ImprimeEstruturas);			// busca local que se verifica se a demanda pode ser melhor atendida caso se realize o seu atendimento com outro caminhão/veículo
	int BuscaLocalMudaOrdemAtendiemntoConstrucoes(int Imprime, int ImprimeEstruturas);
	int BuscaLocalTrocaPlantaAtendimento(int Imprime, int ImprimeEstruturas);

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

// seleciona a construção ainda não avaliada que tera suas demandas atendidas avaliadas pela busca local
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
double BuscaLocal::CalculaMakespanSolucao(){
	// calcula o makespan da solução corrente de suas construções
	ConstrucoesInstancia.CalculaMakespansConstrucoes();
	// calcula o makespan da solução corrente de suas plantas
	PlantasInstancia.CalculaMakespanPlantas();
	// calcula o makespan da solução
	Makespan = ConstrucoesInstancia.MakespanConstrucoes + PlantasInstancia.MakespanPLantas;
	// retorna o valor do makespan
	return Makespan;

}


// busca local que se verifica se a demanda pode ser melhor atendida caso se realize o seu atendimento com outro caminhão/veículo
int BuscaLocal::BuscaLocalTentaRealizarTarefasComOutosVeiculos(int Imprime, int ImprimeEstruturas){

	// daods da cosntrução e da demanda
	int ConstrucaoEscolhida;
	int IndiceConstrucaoEscolhida;
	int DemandaRecolocar;

	// dados das tarefas movidas duarante o procedimento que serão utilizadas ara retornar ao estado anterior da solução caso se piore a solução que se tinha
	vector < DadosTarefa > DadosTarefasMovidas;
	vector < DadosTarefa > DadosTarefasMovidasAdicionaTarefa;

	// makespan da solução anterior que se tinha
	double MakespanAnterior;

	// verifica se atendeu a demanda que será reatendida ou não
	int Recolocar;

	// variavel para se parar o programa
	int ParaPrograma;

	// imprime os dados dos processos de adicionar as tarefas caso for 1, 0 caso vontrario
	int ImprimeDadosAdicionaTarefa;
	ImprimeDadosAdicionaTarefa = 0;

	// faz com que nenhuma construção tenha sido analizada
	ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

	if( Imprime == 1){
		cout << endl << endl << "############################### BuscaLocalTentaRealizarTarefasComOutosVeiculos #####################################" << endl << endl;
	}
	if( ImprimeEstruturas == 1){
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
		PlantasInstancia.Imprime(1,1);
		cin >> ParaPrograma;
	}

	// armazena o makespan da solução corrente
	MakespanAnterior = CalculaMakespanSolucao();

	// enquanto tiver uma construção que ainda possa ser analisada se continua no while
	while( VerificaSeTemUmValorVetorInt( 0, ConstrucoesInstancia.ConstrucoesAnalizadas ) == 1){
		// seleciona uma construção que ainda não foi analisada
		if( SelecionaConstrucao( ConstrucaoEscolhida, IndiceConstrucaoEscolhida) == 0){
			cout << endl << endl << "       >>>>>>>>>> Problema! Não encontrou uma construção para ser analisada na busca local! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
		}

		if( Imprime == 1){
			cout << endl <<  "  >>>>>>>>>>>>>>>>>>>>  Escolheu a construção [" << ConstrucaoEscolhida << "] para retirar suas demandas " << endl ;
		}
		// percorre por todas as demanda da construção selecionada
		for( int DemandaRetirar = 0; DemandaRetirar < ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDemandas; DemandaRetirar++){
			// limpa o conteudo do vetor que guarda os dados da tarefas movidas durante o processo
			DadosTarefasMovidas.clear();
			//deleta todas as tarefas na construção partindo como inicio a demanda corrente
			if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].DeletaTarefas(0, DemandaRetirar,DadosTarefasMovidas, PlantasInstancia) == 0){
				cout << endl << endl << "       >>>>>>>>>> Problema! Não consegui deletar todas as demandas da construção [" << ConstrucaoEscolhida << "] ! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
			}
			// calcula o nivel de inviabilidade da solução
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			if( Imprime == 1){
				cout << endl <<  "  >>>>>>  Deletou demandas apartir de [" << ConstrucaoEscolhida << "-" << DemandaRetirar << "] " << endl ;
			}
			if( ImprimeEstruturas == 1){
				cout << endl <<  "         Dados das tarefas movidas" << endl;
				ImprimeVetorDadosTarefa(DadosTarefasMovidas);
				cin >> ParaPrograma;
			}

			// percorre por todas as plantas
			for ( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
				// percorre por todos os veículos da planta
				for( int v = 0; v < (int) PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas.size(); v++){

					if( Imprime == 1){
						cout << endl << endl << "            +++ Tenta planta e veiculo [" << PlantasInstancia.Plantas[p].NumeroDaPlanta << "-" << PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "]  ++++ " << endl << endl;
					}
					// limpa o conteudo do vetor que guarda os dados das terefas qeu serão movidas durante o processo de adição das tarefas
					DadosTarefasMovidasAdicionaTarefa.clear();
					// tenta adicionar a demanda corrente que foi retirada com o veiculo e com a planta correntes
					if( ConstrucoesInstancia.AdicionaTarefaComVeiculoFixo( 0 , ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDaConstrucao, DemandaRetirar , PlantasInstancia.Plantas[p].NumeroDaPlanta, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, DadosTarefasMovidasAdicionaTarefa, 1, 0, 1, 1 , PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ") == 1){

						if( Imprime == 1){
							cout << endl << endl << " >+< Adicionou [" << ConstrucaoEscolhida << "-" << DemandaRetirar << "]" << endl;
						}
						if( ImprimeEstruturas == 1){
							ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
							PlantasInstancia.Imprime(1,1);
							cout << "      DadosTarefasMovidasAdicionaTarefa " << endl ;
							ImprimeVetorDadosTarefa(DadosTarefasMovidasAdicionaTarefa);
							cin >> ParaPrograma;
						}
						// o indice da demanda que será recolocada é proximo em relação ao que foi adicionada anteriormente
						DemandaRecolocar = DemandaRetirar + 1;
						// inicia a variavel de controle como se a demanda foi recolocada
						Recolocar = 1;
						// enquanto se consegue recolocar demandas e se tem demandas para se recolocar se continua no while
						while( Recolocar == 1 && DemandaRecolocar <   ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDemandas){
							// se tenta recolocar a demanda corrente
							Recolocar = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDaConstrucao, DemandaRecolocar , DadosTarefasMovidasAdicionaTarefa, 1, 0, 1, 1 , PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ");

							if( Imprime == 1){
								cout << endl << endl << " >+< Recoloca [" << ConstrucaoEscolhida << "-" << DemandaRecolocar << "] -> " << Recolocar << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
								PlantasInstancia.Imprime(1,1);
								cout << "      DadosTarefasMovidasAdicionaTarefa " << endl ;
								ImprimeVetorDadosTarefa(DadosTarefasMovidasAdicionaTarefa);
								cin >> ParaPrograma;
							}
							// se aumenta o inidice da demanda que se ira recolocar
							DemandaRecolocar++;
						}
						// calcula o nivel de inviabilidade da solução até o momento
						ConstrucoesInstancia.CalcularNivelDeInviabilidade();
						// verifica se a soluçãoq ue se tem até o momento é melhor que a solução que se tinha inicialmente
						if( CalculaMakespanSolucao() < MakespanAnterior && Recolocar == 1){
							// retorna um caso consiga melhorar a solução

							if( Imprime == 1){
								cout << endl << endl << " [[[[[[[[[[[[[[[[[[[ Melhorou a Solução ]]]]]]]]]]]]]]]]]]]]]" << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 1);
								PlantasInstancia.Imprime(1,1);
								cin >> ParaPrograma;
							}
							// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
							DadosTarefasMovidas.clear();
							DadosTarefasMovidasAdicionaTarefa.clear();
							// se retorna 1, sinalizando que se melhorou a solução que se tinha
							return 1;
						}else{
							// se retorna a solução até o ponto onde se deletou as demandas da construção corrente
							ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasAdicionaTarefa, PlantasInstancia );

							if( Imprime == 1){
								cout << endl << endl << "     ----  Não melhorou, continua" << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
								PlantasInstancia.Imprime(1,1);
								cin >> ParaPrograma;
							}

						}
					}
				}
			}
			// se retorna a solução inicial
			ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia );

			if( Imprime == 1){
				cout << endl << endl << " Final Retorna solução inicial" << endl << endl;
			}
			if( ImprimeEstruturas == 1){
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
				PlantasInstancia.Imprime(1,1);
				cin >> ParaPrograma;
			}

		}
		// marca a solução corrente como já analisada
		ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoEscolhida] = 1;
	}


	if( Imprime == 1){
		cout << endl << endl << "        -------- Não melhorou a solução ------ " << endl << endl;
	}
	// calcula o nivel de inviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	// retona 0 mostrando que não se conseguiu melhorar a solução que se tinha
	return 0;
}

int BuscaLocal::BuscaLocalMudaOrdemAtendiemntoConstrucoes(int Imprime, int ImprimeEstruturas){

	// verifica se atendeu a demanda que será reatendida ou não
	int Recolocar;
	// indice da demanda a ser recolocada
	int DemandaRecolocar;

	// dados das tarefas movidas duarante o procedimento que serão utilizadas ara retornar ao estado anterior da solução caso se piore a solução que se tinha
	vector < DadosTarefa > DadosTarefasMovidasEtapa1;
	vector < DadosTarefa > DadosTarefasMovidasEtapa2;

	// makespan da solução anterior que se tinha
	double MakespanAnterior;

	// variavel que controla se ira imprimir o procedimento de locação de tarefas
	int ImprimeDadosAdicionaTarefa;

	ImprimeDadosAdicionaTarefa = 0;

	int ParaPrograma;

	// armazena o makespan da solução corrente
	MakespanAnterior = CalculaMakespanSolucao();

	// percorre todas as construções
	for( int c1 = 0; c1 < (int) ConstrucoesInstancia.Construcoes.size(); c1++){
		// percorre todas as demandas da construção
		for( int d1 = 0; d1 < (int) ConstrucoesInstancia.Construcoes[c1].NumeroDemandas; d1++ ){
			// limpa o conteudo do vetor que guarda os dados da tarefas movidas durante a etapa 1
			DadosTarefasMovidasEtapa1.clear();
			//deleta todas as tarefas na construção partindo como inicio a demanda corrente
			if( ConstrucoesInstancia.Construcoes[c1].DeletaTarefas(0, d1,DadosTarefasMovidasEtapa1, PlantasInstancia) == 0){
				cout << endl << endl << "       >>>>>>>>>> Problema! Não consegui deletar todas as demandas da construção [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "] ! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
			}
			if( Imprime == 1){
				cout << endl << endl << "	Etapa 1 -> Deleta tarefas da construção [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << d1 << "]" << endl << endl;
			}

			// percorre todas as demandas da construção
			for( int c2 = 0; c2 < (int) ConstrucoesInstancia.Construcoes.size(); c2++){
				// só não analisa a construção que é a mesma que a do primeiro loop
				if( c1 != c2){
					// limpa o conteudo do vetor que guarda os dados da tarefas movidas durante a etapa 2
					DadosTarefasMovidasEtapa2.clear();
					//deleta todas as tarefas na construção corrente no segundo loop
					if( ConstrucoesInstancia.Construcoes[c2].DeletaTarefas(0, 0,DadosTarefasMovidasEtapa2, PlantasInstancia) == 0){
						cout << endl << endl << "       >>>>>>>>>> Problema! Não consegui deletar todas as demandas da construção [" << ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << "] ! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
					}

					if( Imprime == 1){
						cout << endl << endl << "		Etapa 2 -> Deleta tarefas da construção [" << ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << "]" << endl << endl;
					}

					//recoloca demandas da construção 2

					// inicia a variavel da demanda a recolocar como a primeira demanda da construção dois
					DemandaRecolocar = 0;
					// inicia a variavel de controle como se a demanda foi recolocada
					Recolocar = 1;
					// enquanto se consegue recolocar demandas e se tem demandas para se recolocar se continua no while
					while( Recolocar == 1 && DemandaRecolocar <   ConstrucoesInstancia.Construcoes[c2].NumeroDemandas){
						// se tenta recolocar a demanda corrente
						Recolocar = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao, DemandaRecolocar , DadosTarefasMovidasEtapa2, 1, 0, 1, 1 , PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ");

						if( Imprime == 1){
							cout << endl << endl << "			>+< Recoloca [" << ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << "-" << DemandaRecolocar << "] -> " << Recolocar << endl << endl;
						}
						if( ImprimeEstruturas == 1){
							ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
							PlantasInstancia.Imprime(1,1);
							cout << "      DadosTarefasMovidasEtapa2 " << endl ;
							ImprimeVetorDadosTarefa(DadosTarefasMovidasEtapa2);
							cin >> ParaPrograma;
						}
						// se aumenta o inidice da demanda que se ira recolocar
						DemandaRecolocar++;
					}

					//recoloca demandas da construção 1
					DemandaRecolocar = d1;
					// enquanto se consegue recolocar demandas e se tem demandas para se recolocar se continua no while
					while( Recolocar == 1 && DemandaRecolocar <   ConstrucoesInstancia.Construcoes[c1].NumeroDemandas){
						// se tenta recolocar a demanda corrente
						Recolocar = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao, DemandaRecolocar , DadosTarefasMovidasEtapa2, 1, 0, 1, 1 , PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ");

						if( Imprime == 1){
							cout << endl << endl << "				>+++< Recoloca [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaRecolocar << "] -> " << Recolocar << endl << endl;
						}
						if( ImprimeEstruturas == 1){
							ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
							PlantasInstancia.Imprime(1,1);
							cout << "      DadosTarefasMovidasEtapa2 " << endl ;
							ImprimeVetorDadosTarefa(DadosTarefasMovidasEtapa2);
							cin >> ParaPrograma;
						}
						// se aumenta o inidice da demanda que se ira recolocar
						DemandaRecolocar++;
					}
					// calcula o nivel de inviabilidade da solução até o momento
					ConstrucoesInstancia.CalcularNivelDeInviabilidade();

					// caso se melhorar a solução se entra no if
					if( CalculaMakespanSolucao() < MakespanAnterior && Recolocar == 1){
						if( Imprime == 1){
							cout << endl << endl << "  [[[[[[[[[[[[ Melhorou a solução ]]]]]]]]]]]]]]]] " << endl << endl;
						}
						// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
						DadosTarefasMovidasEtapa1.clear();
						DadosTarefasMovidasEtapa2.clear();
						// retorna 1 que corresponde que melhorou a solução
						return 1;
					}
					// se retorna a solução até o ponto onde se deletou as demandas da construção corrente
					ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEtapa2, PlantasInstancia );
					if( Imprime == 1){
						cout << endl << endl << "		Fim da Etapa 2 " << endl << endl;
					}
				}
			}
			// se retorna a solução inicial
			ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEtapa1, PlantasInstancia );
			if( Imprime == 1){
				cout << endl << endl << "	Fim da Etapa 1 " << endl << endl;
			}

		}

	}
	if( Imprime == 1){
		cout << endl << endl << "        -------- Não melhorou a solução ------ " << endl << endl;
	}
	// calcula o nivel de inviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	// retona 0 mostrando que não se conseguiu melhorar a solução que se tinha
	return 0;


}


int BuscaLocal::BuscaLocalTrocaPlantaAtendimento(int Imprime, int ImprimeEstruturas){

	int DemandaAnalise;
	int DeletouDemanda;

	int NumPlanta;
	int NumCarreta;

	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	double HorarioInicioCarregamento;
	double HorarioFinalCarregamento;
	double HorarioInicioDeslocamento;
	double HorarioFinalDeslocamento;

	// dados das tarefas movidas duarante o procedimento que serão utilizadas ara retornar ao estado anterior da solução caso se piore a solução que se tinha
	vector < DadosTarefa > DadosTarefasMovidasEtapa1;
	vector < DadosTarefa > DadosTarefasMovidasEtapa2;

	int DemandaNaoAtendida;

	// imprime os dados dos processos de adicionar as tarefas caso for 1, 0 caso vontrario
	int ImprimeDadosAdicionaTarefa;

	ImprimeDadosAdicionaTarefa = 0;

	// variavel que controla se a demanda foi reinserida
	int ReadicionouDemanda;

	int ConstrucaoAtender;
	int IndiceConstrucaoAtender;

	double MakespanAnterior;

	int ParaPrograma;

	MakespanAnterior = CalculaMakespanSolucao();

	// percorre todas as plantas
	for( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
		DadosTarefasMovidasEtapa1.clear();
		// percorre todas as construções
		if( Imprime == 1){
			cout << endl << endl << "	Inicio Etapa 1 -> Planta [" << PlantasInstancia.Plantas[p].NumeroDaPlanta << "]" << endl << endl;
			cin >> ParaPrograma;
		}

		for( int c1 = 0; c1 < (int) ConstrucoesInstancia.Construcoes.size();c1++){
			// inicializa as variaveis de controle da demanda analisada e se deletou a demanda analisada como zero
			DemandaAnalise = 0;
			DeletouDemanda = 0;
			// faz enquanto não se encontrar uma deamnda para excluir ou se percorrer todas as demandas da construção corrente
			while( DeletouDemanda == 0 || DemandaAnalise < ConstrucoesInstancia.Construcoes[c1].NumeroDemandas){
				// verifica os dados da demanda corrente
				if( ConstrucoesInstancia.RetornaDadosDemandaAtendida( ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao, DemandaAnalise,  NumPlanta, NumCarreta, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioInicioCarregamento, HorarioFinalCarregamento, HorarioInicioDeslocamento, HorarioFinalDeslocamento, PlantasInstancia) == 0){
					cout << endl << endl << "   <<<<<<<<<< Problema em encontrar a tarefa da construção [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaAnalise << "]" << endl << endl;
				}
				// verifica se a deamnda corrente é atendida pela planta em questão
				if( NumPlanta == PlantasInstancia.Plantas[p].NumeroDaPlanta ){
					// deleta a tarefa que é atendida pela planta em questão e as demandas posteriores a sestá na construção
					DeletouDemanda = ConstrucoesInstancia.Construcoes[c1].DeletaTarefas( 0, DemandaAnalise, DadosTarefasMovidasEtapa1, PlantasInstancia);

					if( Imprime == 1){
						cout << endl << endl << "		Deletou construção [" <<  ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaAnalise << "]" << endl << endl;
						cin >> ParaPrograma;
					}

				}
				// passa para a proxima demanda para se analisa-la
				DemandaAnalise++;
			}



			// percorre todas as construções
			for( int c2 = 0; c2 < (int) ConstrucoesInstancia.Construcoes.size();c2++){
				if( ConstrucoesInstancia.Construcoes[c2].DemandaNaoatendida( DemandaNaoAtendida) == 1){

					if( Imprime == 1){
						cout << endl << endl << "		Inicio Etapa 2 -> Construcao [" <<ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "]" << endl << endl;
						cin >> ParaPrograma;
					}

					// percorre todos dos veículos da planta ecorrente
					for( int v = 0; v < (int) PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas.size(); v++){

						DadosTarefasMovidasEtapa2.clear();

						if( ConstrucoesInstancia.AdicionaTarefaComVeiculoFixo( 0 , ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao, DemandaNaoAtendida , PlantasInstancia.Plantas[p].NumeroDaPlanta, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, DadosTarefasMovidasEtapa2, 1, 0, 1, 1 , PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalTrocaPlantaAtendimento >>> ") == 1){

							if( Imprime == 1){
								cout << endl << endl << "			>+ v +< Readicionou Construcao [" <<ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "] com veiculo [" << PlantasInstancia.Plantas[p].NumeroDaPlanta << "-" << v << "]" << endl << endl;
								cin >> ParaPrograma;
							}


							ReadicionouDemanda = 1;
							ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();

							while( VerificaTodosValoresVetorInt( 1, ConstrucoesInstancia.ConstrucaoPodeSerSuprida) == 0 && ReadicionouDemanda == 1){

								if( ConstrucoesInstancia.RetornaConstrucaoQuePodeSerAtendidaComMenorIndice( ConstrucaoAtender, IndiceConstrucaoAtender) == 0){
									cout << endl << endl << " <<<<<<<<<<<<  Problema em encontrar construção  >>>>>>>>>>>>> " << endl << endl;
								}
								if( ConstrucoesInstancia.Construcoes[c2].DemandaNaoatendida( DemandaNaoAtendida) == 0){
									cout << endl << endl << " <<<<<<<<<<<<  Problema em encontrar construção  >>>>>>>>>>>>> " << endl << endl;
								}

								while( DemandaNaoAtendida < ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].NumeroDemandas && ReadicionouDemanda == 1){
									ReadicionouDemanda = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].NumeroDaConstrucao,  DemandaNaoAtendida , DadosTarefasMovidasEtapa2, 1, 0, 1, 1 , PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalTrocaPlantaAtendimento >>> ");

									if( Imprime == 1 && ReadicionouDemanda == 1){
										cout << endl << endl << "				>+< Readicionou Construcao [" << ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "] com veiculo [" << PlantasInstancia.Plantas[p].NumeroDaPlanta << "-" << v << "]" << endl << endl;
										cin >> ParaPrograma;
									}

									DemandaNaoAtendida++;
								}

								ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();

							}

							if( ReadicionouDemanda == 1 && CalculaMakespanSolucao() < MakespanAnterior){
								if( Imprime == 1){
									cout << endl << endl << "  [[[[[[[[[[[[ Melhorou a solução ]]]]]]]]]]]]]]]] " << endl << endl;
								}
								// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
								DadosTarefasMovidasEtapa1.clear();
								DadosTarefasMovidasEtapa2.clear();
								// retorna 1 que corresponde que melhorou a solução
								return 1;
							}else{
								// se retorna a solução até o ponto onde se deletou as demandas da construção corrente
								ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEtapa2, PlantasInstancia );
								if( Imprime == 1){
									cout << endl << endl << "		Fim da Etapa 2 " << endl << endl;
									cin >> ParaPrograma;
								}
							}
						}
					}
				}
			}






		}

		// se retorna a solução até o ponto onde se deletou as demandas da construção corrente
		ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEtapa1, PlantasInstancia );
		if( Imprime == 1){
			cout << endl << endl << "	Fim da Etapa 1 " << endl << endl;
			cin >> ParaPrograma;
		}
	}




	// retona 0 mostrando que não se conseguiu melhorar a solução que se tinha
	return 0;
}

BuscaLocal::~BuscaLocal(){

}


#endif /* BUSCALOCAL_HPP_ */
