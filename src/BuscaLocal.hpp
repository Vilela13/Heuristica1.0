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
	int RetornaConstrucaoQuePodeSerAtendida( int &Construcao, int &IndiceConstrucao);		// retorna a construção que possui o menor inidice e que ainda pode ser atendida


	double CalculaMakespanSolucao();				// calcula o makespan


	int BuscaLocalTentaRealizarTarefasComOutosVeiculos(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeEstruturas);			// busca local que se verifica se a demanda pode ser melhor atendida caso se realize o seu atendimento com outro caminhão/veículo
	int BuscaLocalMudaOrdemAtendiemntoConstrucoes(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeEstruturas);
	int BuscaLocalTrocaPlantaAtendimento(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeEstruturas);

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

	// passa por todas as construções
	for( int c = 0; c < NE; c++){
		// verifica se a construção ainda pode ser analisada
		if( ConstrucoesInstancia.ConstrucoesAnalizadas[c] == 0){
			// armazena os dados da cosntrução corrente
			ConstrucaoEscolhida = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
			IndiceConstrucaoEscolhida = c;
			// retorna 1 caso encontrou uma construção
			return 1;
		}
	}

	// retorna 0 caso não encontrou uma construção
	return 0;


}

// retorna a construção que possui o menor inidice e que ainda pode ser atendida
int BuscaLocal::RetornaConstrucaoQuePodeSerAtendida( int &Construcao, int &IndiceConstrucao){

	// passa por todas as cosntruções
	for( int c = 0; c < (int)  NE; c++){
		// Seleciona a construção que não possui todas as suas demandas já atendidas e que ainda não foi analisada
		if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas &&  ConstrucoesInstancia.ConstrucaoPodeSerSuprida[c] == 0){
			// atuaiza os dados da construção com menor rank, seu número ou seu indice
			Construcao = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
			IndiceConstrucao = c;
			// retorn 1 sinalizando que encontrou uma construção
			return 1;
		}
	}
	// retorna 0 sinalizando que não encontrou uma cosntrução
	return 0;

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
int BuscaLocal::BuscaLocalTentaRealizarTarefasComOutosVeiculos(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeEstruturas){















	CalculaMakespanSolucao();

	int ativa;
	ativa = 0;

	if( 115.879267 < Makespan && Makespan < 115.879269){
		printf( "\n\n         Entrei busaca Makespan [%f] \n\n", Makespan);
		ativa = 1;
	}





















	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int ImprimeArquivo;
	ImprimeArquivo = 0;

	int ImprimeSolucao;
	ImprimeSolucao = 0;

	// daods da cosntrução e da demanda
	int ConstrucaoEscolhida;
	int IndiceConstrucaoEscolhida;
	int DemandaRecolocar;

	// dados das tarefas movidas duarante o procedimento que serão utilizadas ara retornar ao estado anterior da solução caso se piore a solução que se tinha
	vector < DadosTarefa > DadosTarefasMovidasVeiculoFixo;
	vector < DadosTarefa > DadosTarefasMovidasReadicaoDeDemandas;

	// makespan da solução anterior que se tinha
	double MakespanAnterior;

	// verifica se atendeu a demanda que será reatendida ou não
	int Recolocar;

	// realiza o processo de atrazar as demandas quando for inserir uma nova demanda em uma construção
	int RealizaProcessoDeAtrazarTarefas;
	RealizaProcessoDeAtrazarTarefas = 1;


	// variavel para se parar o programa
	int ParaPrograma;

	// imprime os dados dos processos de adicionar as tarefas caso for 1, 0 caso vontrario
	int ImprimeDadosAdicionaTarefa;
	ImprimeDadosAdicionaTarefa = 0;

	// ordena as cosntruções na ordem em que elas devem ser escolhidas com prioridade
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// faz com que nenhuma construção tenha sido analizada
	ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

	if( Imprime == 1){
		cout << endl << endl << "############################### BuscaLocalTentaRealizarTarefasComOutosVeiculos #####################################" << endl << endl;
	}
	if( ImprimeEstruturas == 1){
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
		PlantasInstancia.Imprime(1,1,ImprimeSolucao, ImprimeArquivo, Arquivo);
		cin >> ParaPrograma;
	}

	// armazena o makespan da solução corrente
	MakespanAnterior = CalculaMakespanSolucao();

	// enquanto tiver uma construção que ainda possa ser analisada se continua no while
	while( VerificaSeTemUmValorVetorInt( 0, ConstrucoesInstancia.ConstrucoesAnalizadas ) == 1){

// retira tarefa realizad pela solução inicial

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
			DadosTarefasMovidasVeiculoFixo.clear();
			//deleta todas as tarefas na construção partindo como inicio a demanda corrente
			if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].DeletaTarefas(0, DemandaRetirar,DadosTarefasMovidasVeiculoFixo, PlantasInstancia) == 0){
				cout << endl << endl << "       >>>>>>>>>> Problema! Não consegui deletar todas as demandas da construção [" << ConstrucaoEscolhida << "] ! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
			}
			// calcula o nivel de inviabilidade da solução
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			if( Imprime == 1){
				cout << endl <<  "  >>>>>>  Deletou demandas apartir de [" << ConstrucaoEscolhida << "-" << DemandaRetirar << "] " << endl ;
			}
			if( ImprimeEstruturas == 1){
				cout << endl <<  "         Dados das tarefas movidas" << endl;
				ImprimeVetorDadosTarefa(DadosTarefasMovidasVeiculoFixo);
				cin >> ParaPrograma;
			}

			// percorre por todas as plantas
			for ( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
				// percorre por todos os veículos da planta
				for( int v = 0; v < (int) PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas.size(); v++){

// tenta atender a demanda retirada anteriormente com um outro veiculo do que o que era realizado na solução inicial

					if( Imprime == 1){
						cout << endl << endl << "            +++ Tenta planta e veiculo [" << PlantasInstancia.Plantas[p].NumeroDaPlanta << "-" << PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "]  ++++ " << endl << endl;
					}
					// limpa o conteudo do vetor que guarda os dados das terefas qeu serão movidas durante o processo de adição das tarefas
					DadosTarefasMovidasReadicaoDeDemandas.clear();

					// tenta adicionar a demanda corrente que foi retirada com o veiculo e com a planta correntes
					if( ConstrucoesInstancia.AdicionaTarefaComVeiculoFixo( 0 , ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDaConstrucao, DemandaRetirar , PlantasInstancia.Plantas[p].NumeroDaPlanta, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, DadosTarefasMovidasReadicaoDeDemandas, 1, 0, RealizaProcessoDeAtrazarTarefas,  EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ") == 1){


						if( Imprime == 1){
							cout << endl << endl << " >+< Adicionou [" << ConstrucaoEscolhida << "-" << DemandaRetirar << "]" << endl;
						}
						if( ImprimeEstruturas == 1){
							ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
							PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
							cout << "      DadosTarefasMovidasAdicionaTarefa " << endl ;
							ImprimeVetorDadosTarefa( DadosTarefasMovidasReadicaoDeDemandas );
							cin >> ParaPrograma;
						}

// tenta readicionar a demandas que foram desalocadas após a demanda que teve sua demanda atendida por outro veiculo

						// o indice da demanda que será recolocada é proximo em relação ao que foi adicionada anteriormente
						DemandaRecolocar = DemandaRetirar + 1;
						// inicia a variavel de controle como se a demanda foi recolocada
						Recolocar = 1;
						// enquanto se consegue recolocar demandas e se tem demandas para se recolocar se continua no while
						while( Recolocar == 1 && DemandaRecolocar <   ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDemandas){








							if( ativa == 1 && ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDaConstrucao == 6 && DemandaRecolocar == 3 && PlantasInstancia.Plantas[p].NumeroDaPlanta == 0 && PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta == 6){
								ImprimeDadosAdicionaTarefa = 1;

								cout << endl << endl << endl << endl << "                (((((((((((<<<<<<<<< Começa AdicionaTarefa >>>>>>>>>>>>>>>)))))))))))))))) " << endl << endl << endl << endl;

							}

							// se tenta recolocar a demanda corrente
							Recolocar = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDaConstrucao, DemandaRecolocar , DadosTarefasMovidasReadicaoDeDemandas, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo , EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ");


							if( ativa == 1 && ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].NumeroDaConstrucao == 6 && DemandaRecolocar == 3 && PlantasInstancia.Plantas[p].NumeroDaPlanta == 0 && PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta == 6){
								ImprimeDadosAdicionaTarefa = 0;

								cout << endl << endl << endl << endl << "                (((((((((((<<<<<<<<< Termina AdicionaTarefa >>>>>>>>>>>>>>>)))))))))))))))) " << endl << endl << endl << endl;

							}



							if( Imprime == 1){
								cout << endl << endl << " >+< Recoloca [" << ConstrucaoEscolhida << "-" << DemandaRecolocar << "] -> " << Recolocar << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
								PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
								cout << "      DadosTarefasMovidasAdicionaTarefa " << endl ;
								ImprimeVetorDadosTarefa( DadosTarefasMovidasReadicaoDeDemandas );
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
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 1, ImprimeSolucao,ImprimeArquivo,Arquivo);
								PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
								cin >> ParaPrograma;
							}
							// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
							DadosTarefasMovidasVeiculoFixo.clear();
							DadosTarefasMovidasReadicaoDeDemandas.clear();
							// se retorna 1, sinalizando que se melhorou a solução que se tinha
							return 1;
						}else{
							// se retorna a solução até o ponto onde se deletou as demandas da construção corrente
							ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasReadicaoDeDemandas, PlantasInstancia );

							if( Imprime == 1){
								cout << endl << endl << "     ----  Não melhorou, continua" << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
								PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
								cin >> ParaPrograma;
							}

						}
					}



				}
			}
			// se retorna a solução inicial
			ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasVeiculoFixo, PlantasInstancia );

			if( Imprime == 1){
				cout << endl << endl << " Final Retorna solução inicial" << endl << endl;
			}
			if( ImprimeEstruturas == 1){
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
				PlantasInstancia.Imprime(1,1, ImprimeSolucao , ImprimeArquivo, Arquivo);
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
	// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
	DadosTarefasMovidasVeiculoFixo.clear();
	DadosTarefasMovidasReadicaoDeDemandas.clear();
	// retona 0 mostrando que não se conseguiu melhorar a solução que se tinha
	return 0;
}

// busca local que se verifica caso a ordem de decisão de atendiemnto das demandas de duas construções forem invertidas se irá obter uma melhor solução para o problema
int BuscaLocal::BuscaLocalMudaOrdemAtendiemntoConstrucoes(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeEstruturas){

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int ImprimeArquivo;
	ImprimeArquivo = 0;

	int ImprimeSolucao;
	ImprimeSolucao = 1;

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

	// realiza o processo de atrazar as demandas quando for inserir uma nova demanda em uma construção
	int RealizaProcessoDeAtrazarTarefas;
	RealizaProcessoDeAtrazarTarefas = 1;

	int ParaPrograma;

	// ordena as cosntruções na ordem em que elas devem ser escolhidas com prioridade
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// verifica se possui mais de uma construção, caso só setiver uma não faz sentido realizar o procedimento da busca local de troca de ordem de atendiemnto das construções
	if ( (int) ConstrucoesInstancia.Construcoes.size() > 1){

		// armazena o makespan da solução corrente
		MakespanAnterior = CalculaMakespanSolucao();

		// percorre todas as construções
		for( int c1 = 0; c1 < (int) ConstrucoesInstancia.Construcoes.size(); c1++){
			// percorre todas as demandas da construção
			for( int d1 = 0; d1 < (int) ConstrucoesInstancia.Construcoes[c1].NumeroDemandas; d1++ ){
				// limpa o conteudo do vetor que guarda os dados da tarefas movidas durante a etapa 1
				DadosTarefasMovidasEtapa1.clear();

	// deleta as demandas da construção 1

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

	// deleta as demandas da construção 2

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

	// readiciona as demandas da construção 2

						// enquanto se consegue recolocar demandas e se tem demandas para se recolocar se continua no while
						while( Recolocar == 1 && DemandaRecolocar <   ConstrucoesInstancia.Construcoes[c2].NumeroDemandas){
							// se tenta recolocar a demanda corrente
							Recolocar = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao, DemandaRecolocar , DadosTarefasMovidasEtapa2, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo , EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ");

							if( Imprime == 1){
								cout << endl << endl << "			>+< Recoloca [" << ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << "-" << DemandaRecolocar << "] -> " << Recolocar << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
								PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
								cout << "      DadosTarefasMovidasEtapa2 " << endl ;
								ImprimeVetorDadosTarefa(DadosTarefasMovidasEtapa2);
								cin >> ParaPrograma;
							}
							// se aumenta o inidice da demanda que se ira recolocar
							DemandaRecolocar++;
						}

						//recoloca demandas da construção 1
						DemandaRecolocar = d1;

	// readiciona as demandas da construção 2

						// enquanto se consegue recolocar demandas e se tem demandas para se recolocar se continua no while
						while( Recolocar == 1 && DemandaRecolocar <   ConstrucoesInstancia.Construcoes[c1].NumeroDemandas){
							// se tenta recolocar a demanda corrente
							Recolocar = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao, DemandaRecolocar , DadosTarefasMovidasEtapa2, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo , EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao >>> ");

							if( Imprime == 1){
								cout << endl << endl << "				>+++< Recoloca [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaRecolocar << "] -> " << Recolocar << endl << endl;
							}
							if( ImprimeEstruturas == 1){
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
								PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
								cout << "      DadosTarefasMovidasEtapa2 " << endl ;
								ImprimeVetorDadosTarefa(DadosTarefasMovidasEtapa2);
								cin >> ParaPrograma;
							}
							// se aumenta o inidice da demanda que se ira recolocar
							DemandaRecolocar++;
						}
						// calcula o nivel de inviabilidade da solução até o momento
						ConstrucoesInstancia.CalcularNivelDeInviabilidade();

	// verifica se a solução melhorou

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
	}
	// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
	DadosTarefasMovidasEtapa1.clear();
	DadosTarefasMovidasEtapa2.clear();
	// retona 0 mostrando que não se conseguiu melhorar a solução que se tinha
	return 0;
}


int BuscaLocal::BuscaLocalTrocaPlantaAtendimento(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeEstruturas){

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int ImprimeArquivo;
	ImprimeArquivo = 0;

	int ImprimeSolucao;
	ImprimeSolucao = 1;

	// makespan da solução anterior que se tinha
	double MakespanAnterior;

	// variaveis que guardam a demanda deletada na etapa um e o status do procedimento de se deletar tal demanda
	int DemandaAnalise;
	int DeletouDemanda;

	// variaveis que armazenam a planta e a carreta da tarefa analisada para ser deletada caso for atendida pela planta em questão
	int NumPlanta;
	int NumCarreta;

	// variaveis que armazenam os horarios da tarefa analisada para ser deletada caso for atendida pela planta em questão
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	double HorarioInicioCarregamento;
	double HorarioFinalCarregamento;
	double HorarioInicioDeslocamento;
	double HorarioFinalDeslocamento;

	// dados das tarefas movidas duarante o procedimento que serão utilizadas ara retornar ao estado anterior da solução caso se piore a solução que se tinha
	vector < DadosTarefa > DadosTarefasMovidasEtapa1;
	vector < DadosTarefa > DadosTarefasMovidasEtapa2;
	// dados das tarefas movidas entre as etapas 1 e 2
	vector < DadosTarefa > DadosTarefasMovidasEmUmaConstrucaoEtapa1;

	// demanda não atendida na etapa 2 que se tentara reatender
	int DemandaNaoAtendida;

	// variavel que controla se a demanda foi reinserida
	int ReadicionouDemanda;

	int ReadicionouDemandaProcessoEtapa1;

	// dados da cosntrução que terá suas demandas reinseridas na etapa 2
	int ConstrucaoAtender;
	int IndiceConstrucaoAtender;
	// demanda que será reinserida na etapa dois mas que não possui um veículo do qual ela tem que ser atendida obrigatoriamente
	int  DemandaNaoAtendidaSemPlantaFixa;

	// realiza o processo de atrazar as demandas quando for inserir uma nova demanda em uma construção
	int RealizaProcessoDeAtrazarTarefas;
	RealizaProcessoDeAtrazarTarefas = 1;

	int ParaPrograma;

	// imprime os dados dos processos de adicionar as tarefas caso for 1, 0 caso vontrario
	int ImprimeDadosAdicionaTarefa;
	ImprimeDadosAdicionaTarefa = 0;

	// ordena as cosntruções na ordem em que elas devem ser escolhidas com prioridade
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// armazena o makespan da solução corrente
	MakespanAnterior = CalculaMakespanSolucao();

	// verifica se a instancia tem mais de uma planta
	if( (int) PlantasInstancia.Plantas.size() > 1){

		// percorre todas as plantas
		for( int p1 = 0; p1 < (int) PlantasInstancia.Plantas.size(); p1++){
			// limpa o conteudo do vetor que guarda os dados da tarefas movidas durante a etapa 1
			DadosTarefasMovidasEtapa1.clear();
			if( Imprime == 1){
				cout << endl << endl << "	Inicio Etapa 1 -> Planta [" << PlantasInstancia.Plantas[p1].NumeroDaPlanta << "]" << endl << endl;
				cin >> ParaPrograma;
			}


 // deleta as demandas atendidas pela planta corrente

			// percorre todas as construções
			for( int c1 = 0; c1 < (int) ConstrucoesInstancia.Construcoes.size(); c1++){
				// inicializa as variaveis de controle da demanda analisada e se deletou a demanda analisada como zero
				DemandaAnalise = 0;
				DeletouDemanda = 0;
				// faz enquanto não se encontrar uma deamnda para excluir ou se percorrer todas as demandas da construção corrente
				while( DeletouDemanda == 0 && DemandaAnalise < ConstrucoesInstancia.Construcoes[c1].NumeroDemandas){
					// verifica os dados da demanda corrente
					if( ConstrucoesInstancia.RetornaDadosDemandaAtendida( ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao, DemandaAnalise,  NumPlanta, NumCarreta, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioInicioCarregamento, HorarioFinalCarregamento, HorarioInicioDeslocamento, HorarioFinalDeslocamento, PlantasInstancia) == 0){
						cout << endl << endl << "   <<<<<<<<<< Problema em encontrar a tarefa da construção [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaAnalise << "]" << endl << endl;
					}
					// verifica se a deamnda corrente é atendida pela planta em questão
					if( NumPlanta == PlantasInstancia.Plantas[p1].NumeroDaPlanta ){
						// deleta a tarefa que é atendida pela planta em questão e as demandas posteriores a sestá na construção
						DeletouDemanda = ConstrucoesInstancia.Construcoes[c1].DeletaTarefas( 0, DemandaAnalise, DadosTarefasMovidasEtapa1, PlantasInstancia);

						if( Imprime == 1){
							cout << endl << endl << "		Deletou construção [" <<  ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaAnalise << "]  => DeletouDemanda (" << DeletouDemanda << ")" << endl << endl;
						}

					}
					// passa para a proxima demanda para se analisa-la
					DemandaAnalise++;
				}
			}
			// calcula o nivel de inviabilidade da solução
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();
			if( Imprime == 1){
				cout << endl << endl << "		Deletou tarefas realizadas pela planta [" << p1 << "] " << endl << endl;
				PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia , 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
				cin >> ParaPrograma;
			}
			// percorre todas as construções
			for( int c1 = 0; c1 < (int) ConstrucoesInstancia.Construcoes.size();c1++){
				// limpa as demandas que são colocadas durante o processo da Etapa 1 e antes de cada Etapa 2
				DadosTarefasMovidasEmUmaConstrucaoEtapa1.clear();

				if( Imprime == 1){
					cout << endl << endl << "		Inicio Etapa 2 -> Construcao [" <<ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "]" << endl ;
					cin >> ParaPrograma;
				}


				ReadicionouDemandaProcessoEtapa1 = 1;

				// enquanto a cosntrução corrente tiver uma demanda que foi deltada no processo anterior se continua no while
				while( ConstrucoesInstancia.Construcoes[c1].DemandaNaoatendida( DemandaNaoAtendida) == 1 && ReadicionouDemandaProcessoEtapa1 == 1){

					if( Imprime == 1){
						cout << endl << endl << "			Analise demanda [" <<ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "]" << endl ;
						cin >> ParaPrograma;
					}

					// percorre todas as plantas
					for( int p2 = 0; p2 < (int) PlantasInstancia.Plantas.size(); p2++){
						// só não é avaliado a planta que é a mesma planta da etapa 1
						if( p1 != p2){
							// percorre todos dos veículos da planta corrente
							for( int v = 0; v < (int) PlantasInstancia.Plantas[p2].VeiculosDaPlanta.Carretas.size(); v++){
								// limpa o conteudo do vetor que guarda os dados da tarefas movidas durante a etapa 2
								DadosTarefasMovidasEtapa2.clear();

// reacrescenta a primeira demanda tirada com uma certa planta que não é a que ela foi atendida na solução inicial

								// tenta alocar a demanda corrente com um certo veiculo, caso se consiga alocar a demanda se entra no if
								if( ConstrucoesInstancia.AdicionaTarefaComVeiculoFixo( 0 , ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao, DemandaNaoAtendida , PlantasInstancia.Plantas[p2].NumeroDaPlanta, PlantasInstancia.Plantas[p2].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, DadosTarefasMovidasEtapa2, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalTrocaPlantaAtendimento >>> ") == 1){
									if( Imprime == 1){
										cout  << endl << "				>+ v +< Readicionou Construcao [" <<ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "] com veiculo [" << PlantasInstancia.Plantas[p2].NumeroDaPlanta << "-" << v << "]" << endl ;
										cin >> ParaPrograma;
									}
									// calcula o nivel de inviabilidade da solução
									ConstrucoesInstancia.CalcularNivelDeInviabilidade();
									// marac a variavel como se conseguiu alicar a demanda
									ReadicionouDemanda = 1;
									// marca as construções que possuem demandas que ainda não foram atendidas como candidadtas a serem avaliadas para o atenidmento de suas demandas
									ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();
									// caso se tenha uma construção que ainda possa ter uma demanda atendida e se tenha conseguido atender a ultima demanda analisada, se entra no while. Este processo é realizado até que todas as demnadas tenham sido atendidas ou não se consiga se recolocar alguma demanda que foi desalocada.
									while( VerificaTodosValoresVetorInt( 1, ConstrucoesInstancia.ConstrucaoPodeSerSuprida) == 0 && ReadicionouDemanda == 1){
										// se armazena os dados da construção mais proeminente a se ter uma demanda reinserida no momento
										if( RetornaConstrucaoQuePodeSerAtendida(  ConstrucaoAtender, IndiceConstrucaoAtender) == 0){
											cout << endl << endl << " <<<<<<<<<<<<  Problema em encontrar construção  >>>>>>>>>>>>> " << endl << endl;
										}
										// se armazena a primeira demanda na cosntrução corrente que terá suas demandas reinseridas
										if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].DemandaNaoatendida( DemandaNaoAtendidaSemPlantaFixa) == 0){
											cout << endl << endl << " <<<<<<<<<<<<  Problema em encontrar construção  >>>>>>>>>>>>> " << endl << endl;
										}

										// enquanto todas as demandas da construção corrente não tiverem sido atendidas ou se não consiga atender uma dessas demandas, se continua no while
										while( DemandaNaoAtendidaSemPlantaFixa < ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].NumeroDemandas && ReadicionouDemanda == 1){
											// tenta readicionar a demanda corrente que foi retirada na etapa 1, sendo que não precisa ser utilizando um veículo especifico
											ReadicionouDemanda = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].NumeroDaConstrucao,   DemandaNaoAtendidaSemPlantaFixa , DadosTarefasMovidasEtapa2, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo , EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalTrocaPlantaAtendimento >>> ");

											if( Imprime == 1 && ReadicionouDemanda == 1){
												cout  << endl << "					>+< Readicionou Construcao [" << ConstrucoesInstancia.Construcoes[IndiceConstrucaoAtender].NumeroDaConstrucao << "-" <<  DemandaNaoAtendidaSemPlantaFixa << "] "<< endl ;
												cin >> ParaPrograma;
											}
											// se passa para a proxima demanda que tem que ser reinserida na cosntrução corrente
											DemandaNaoAtendidaSemPlantaFixa++;
										}
										// calcula o nivel de inviabilidade da solução
										ConstrucoesInstancia.CalcularNivelDeInviabilidade();
										// se atualizia as construções que ainda tem demandas que temq ue ser reinseridas
										ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();
									}
									// verifica se foi readicionado todas as demandas e se o novo makespan da solução corrente é melhor que o makespan da solução antiga, caso sim, entra no if
									if( ReadicionouDemanda == 1 && CalculaMakespanSolucao() < MakespanAnterior){
										if( Imprime == 1){
											cout << endl << endl << "  [[[[[[[[[[[[ Melhorou a solução ]]]]]]]]]]]]]]]] " << endl << endl;
										}
										// calcula o nivel de inviabilidade da solução
										ConstrucoesInstancia.CalcularNivelDeInviabilidade();
										// se limpa os vetores que armazenavam os dados de tarefas movidas durante o processo
										DadosTarefasMovidasEtapa1.clear();
										DadosTarefasMovidasEmUmaConstrucaoEtapa1.clear();
										DadosTarefasMovidasEtapa2.clear();
										// retorna 1 que corresponde que melhorou a solução
										return 1;
									}
								}else{
									if( Imprime == 1){
										cout << endl << "               			Não consegui alocar demanda [" << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "] com o veículo [" << PlantasInstancia.Plantas[p2].NumeroDaPlanta << "-" << PlantasInstancia.Plantas[p2].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "] " << endl;
									}

								}
								// caso não se conseguiu melhorar a solução, se retorna o estado da solução antes de se realizar os procediemntos da etapa 2 corrente
								ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEtapa2, PlantasInstancia );
								if( Imprime == 1){
									cout << endl << endl << "			Fim analise demanda " << endl ;
									cin >> ParaPrograma;
								}
							}
						}
					}
					// readiciono a demanda que se estava se querendo colocar com um veiculo fixo utilizando o processo normal de se adicionar uma tarefa. *********** -> IMPORTANTE: apesar de se registrar a alocação dessa demanda na estrutura das tarefas movidas na etapa 2, ela não será considerada no processo de retorno para a solução antes da etapa 2 que será realizada em seguida. Pois a estrutura DadosTarefasMovidasEtapa2 é zerada ao se reiniciar a etapa 2. com isso essa demanda será considerada no procediemnto seguinte da etapa 2 como sendo parte da solução inicial fornecida pela etapa 1
					ReadicionouDemandaProcessoEtapa1 = ConstrucoesInstancia.AdicionaTarefa( 0 , ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao,   DemandaNaoAtendida , DadosTarefasMovidasEmUmaConstrucaoEtapa1, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo , EscolhaPlanta, PlantasInstancia, ImprimeDadosAdicionaTarefa,"  <<<<< BuscaLocal::BuscaLocalTrocaPlantaAtendimento >>> ");

					if( Imprime == 1){
						cout << endl << endl << "     ReadicionouDemandaProcessoEtapa1 [" << ReadicionouDemandaProcessoEtapa1 << "] a demanda [ " << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "-" << DemandaNaoAtendida << "]" << endl << endl;
					}

				}

				if( Imprime == 1){
					cout << endl << endl << "		Fim Etapa 2 -> Construcao [" <<ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << "]" << endl ;
					cin >> ParaPrograma;
				}
// após se tentar realizar o processo de se atender as demandas de uma cosntrução com uma planta que sejá diferente que a que ela é atendida na construção inicial e não se conseguiu melhorar o makespan da solução, se deleta as demandas que foram reinseridas no processo da Etapa 2 e não foram contabilizadas nos movimentos de retorno da solução antes de se realizar a etapa 2. Estas foram guardadas em DadosTarefasMovidasEmUmaConstrucaoEtapa1

				// caso não se conseguiu melhorar a solução, se retorna o estado da solução antes de se realizar os procediemntos da etapa 2 que foram realizados na cosntrução corrente tentando atender as demandas dessa construção com um veículo fixo
				if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEmUmaConstrucaoEtapa1, PlantasInstancia ) == 0) {
					cout << endl << endl << "                     <<<<<<<< Problema em retornar a solução entre a etapa 1 e 2 -> BuscaLocal::BuscaLocalTrocaPlantaAtendimento >>>>>>>>>>>>> " << endl << endl;
				}
			}

			// se retorna a solução até o ponto onde se deletou as demandas da construção corrente
			ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasEtapa1, PlantasInstancia );
			if( Imprime == 1){
				cout << endl << endl << "	Fim da Etapa 1 -> Planta [" << PlantasInstancia.Plantas[p1].NumeroDaPlanta << "]" << endl << endl;
				PlantasInstancia.Imprime(1,1,ImprimeSolucao, ImprimeArquivo, Arquivo);
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia , 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
				cin >> ParaPrograma;
			}
		}


	}
	// calcula o nivel de inviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	// Limpa as estruturas que guarda os dados de demandas deletadas
	DadosTarefasMovidasEtapa1.clear();
	DadosTarefasMovidasEmUmaConstrucaoEtapa1.clear();
	DadosTarefasMovidasEtapa2.clear();
	// retona 0 mostrando que não se conseguiu melhorar a solução que se tinha
	return 0;
}

BuscaLocal::~BuscaLocal(){

}


#endif /* BUSCALOCAL_HPP_ */
