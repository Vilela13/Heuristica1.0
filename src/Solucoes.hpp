/*
 * Solucoes.hpp
 *
 *  Created on: Sep 11, 2015
 *      Author: mateus.vilela
 */

#ifndef SOLUCOES_HPP_
#define SOLUCOES_HPP_

#include "Bibliotecas.hpp"


class Solucao{
public:

// estruturas que armazenam os dados da instancia
	int		NP;
	ConjuntoPlantas		PlantasInstancia;
	int		NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int		NV;
	double	Velocidade;
	double	TempoDeVidaConcreto;

	double	Makespan;

	Solucao();

	void	CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);		// Carrega os dados da instancia e a solução até o momento
	void	Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);									// imprime os dados da solução
	int		DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas);					// deleta demandas atendidas na construção após certa demanda que é passada com parametro


	void	ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int EscolhaVeiculo,int EscolhaPlanta, int imprime);						// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
	int		ConstrucaoTemTarefaParaRemover(int& Construcao, int& Demanda, int Imprimir);	// Usado em ProcessoViabilizacao1. Verifica se possui uma construção que possui demandas que ainda não foram retiradas para se tentar a viabilização da solução. Caso possuir, retorna 1 a função e é retornado os dados da construção e da demanda por parametro.

	int		Viabilidade1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);
	void	ProcessoViabilizacao1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);


	int		DeletaUltimaDemandaConstrucaoEmAnalise( int ConstrucaoNaoAtendida, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendidaInicio, vector < DadosTarefa > &DadosTarefasDemandasAnteriores);		// deleta a demanda passada na função e as demandas seguintes a está na construção, mas só armazena na estrutura a demanda passada na função

	int		SelecionaConstrucao(int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice);	// seleciona a construção a ser analisada no momento
	int		ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida);																	// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas
	void	AlocaTempoPlantaPodeAtenderDemanda(int IndiceConstrucaoNaoAtendida, vector < double > &TempoPlantaConsegueAtender, int Imprime);					// Aloca o tempo inicial que se pode sair uma carreta da planta para suprir a construção passada

	int		DeletaTarefasAposTempoPlantaPodeAtender(vector < double > &TempoPlantaPodeAtender, vector < DadosTarefa > &DadosTarefasMovidas,  int Imprime );		// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender

	int		Viabilidade2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);
	void	ProcessoViabilizacao2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);

	void	CalculaMakespan();				// calcula o makespan geral da solução
	void	CalculaNiveisViabilidade();		// calcula o nivel de viabilidade da solução

	void 	RealizarBuscaLocalCaminhao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);
	void 	RealizarBuscaLocalConstrucao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);
	void 	RealizarBuscaLocalPlanta(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);

	~Solucao();
};

// construtora da classe
Solucao::Solucao(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
	Makespan = -13;
}


// Carrega os dados da instancia e a solução até o momento
void	Solucao::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
}

// imprime os dados da solução
void 	Solucao::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade ,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){


	// Imprime os dados das plantas
	if( ImprimePlanta == 1 ){
		PlantasInstancia.Imprime(1,1, ImprimeSolucao, ImprimeArquivo, Arquivo);
	}
	// Imprime os dados das construções
	if( ImprimeConstrucao == 1){
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao, ImprimeArquivo, Arquivo);
	}

	if( ImprimeSolucao == 1){
		printf("     MAKESPAN GERAL = %.4f \n", PlantasInstancia.MakespanPLantas + ConstrucoesInstancia.MakespanConstrucoes);
	}
	if(ImprimeArquivo == 1){
		fprintf(Arquivo, "     MAKESPAN GERAL = %.4f \n", PlantasInstancia.MakespanPLantas + ConstrucoesInstancia.MakespanConstrucoes);
	}

}

// deleta demandas atendidas na construção após certa demanda que é passada com parametro
int		Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas){
	int c;

	// verifica se a construção passada existe
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, " -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao" ) == 1){
		// deleta demandas que estavam alocadas apos a demnada passada, e inclusive a demanda passada
		if( ConstrucoesInstancia.Construcoes[c].DeletaTarefas( VerificaExistencia, Demanda, DadosTarefasMovidas, PlantasInstancia) == 0 ){
			cout << endl << endl << "   problema em retirar tarefas -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao " << endl << endl;
			return 0;
		}
		//cout << endl << endl;
		//ConstrucoesInstancia.Construcoes[c].ImprimeContrucao();

		//consegui retirar as demandas
		return 1;
	}
	cout << endl << endl << " <<<<<<<<<< Não encontrei a construção [" << Construcao << "] passada -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao  >>>>>>>>>>>> "<< endl << endl;
	return 0;

}




// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
void	Solucao::ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int EscolhaVeiculo,int EscolhaPlanta, int imprime){
	// indice da cosntrução passada
	int c;

	if( imprime == 1){
		cout << " Tenta readicionar demandas a construção [" << construcao << "]" << endl << endl;
	}
	// verifica se existe a construção passada
	if( ConstrucoesInstancia.RetornaIndiceConstrucao( construcao, c, " <<<<<<<<<<<<<<<<<<<<<<< Solucao::ReadicionaTarefas >>>>>>>>>>>>>>>>>>>>") == 1 ){
		// percorre as demanda da cosntrução
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
			// caso a demanda corrente não tenha sido atendida
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
				// readiciona a demanda corrente na construção
				if( ConstrucoesInstancia.AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo,EscolhaPlanta, PlantasInstancia, imprime, "Solucao::ReadicionaTarefas") == 1 ){
					if( imprime == 1){
						cout << " adicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
					}
				}else{
					if( imprime == 1){
						cout << " Nao readicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
					}
					// caso não se consiga readicionar uma demanda, se para o programa
					return;
				}
			}
		}
	}

}

// Usado em ProcessoViabilizacao1. Verifica se possui uma construção que possui demandas que ainda não foram retiradas para se tentar a viabilização da solução. Caso possuir, retorna 1 a função e é retornado os dados da construção e da demanda por parametro.
int		Solucao::ConstrucaoTemTarefaParaRemover(int& Construcao, int& Demanda, int Imprimir){

	// inicia os valores dessas variaveis
	Construcao = -13;
	Demanda = -13;

	// percorre todas as construções
	for( int c = 0; c < NE; c++){
		// percorre as demandas da construção em ordem decerscente
		for( int d = ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas - 1); d >= 0 ; d--){
			// so entra caso a demanda tenha sido atendida
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[d] == 1){
				// so entrra caso ela não tenha sido removida anteriormente
				if( ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] == 0){
					// aloc a construção corrente, a demanda e o rank da construção
					Construcao = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					Demanda = d;
					return 1;
				}
			}
		}
	}
	// não encontrou uma demanda a remover
	return 0;
}


int		Solucao::Viabilidade1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){

	// Imprime os dados das tarefas armazenadas durante o processo
	int ImprimeDadosTarefasArmazenados;
	ImprimeDadosTarefasArmazenados = 0;

	// armazena o nivel de inviabilidade anterior
	int InviabilidadeSolucaoAnterior;
	// armazana os dados da tarefa a ser retirada
	int ConstrucaoAnalisandoRetirada;
	int DemandaAnalisandoRetirada;

	// armazena as tarefas da solução que foram retiradas e adicionadas para permitir que se retorne ao estado inicial da solução depoois
	vector < DadosTarefa > DadosTarefasMovidas;
	vector < DadosTarefa > DadosTarefasMovidasPlantaVeiculo;

	//se deve realizar a verificação da viabilidade da solução corrente
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	// vetores que armazenam as ordens das plantas e dos veiculos
	vector < int > VetorOrdemPlanta;
	vector < int > VetorOrdemVeiculo;
	// inidice da planta da planta em questão no VetorOrdemPlanta
	int IndicePlanta;

	// dados da demanda que temq ue ser inserida na solução e que não era inserida anteriormente
	int ConstrucaoParaInserir;
	int DemandaParaInserir;

	// variavel para parar o programa
	int PararPrograma;

	// ordena cosntruções  (foi tirada para se manter a ordem realizado na heuristica constrututiva)
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// faz que nenhuma tarefa tenha sido removida
	ConstrucoesInstancia.ReiniciaTarefasRetiradas();
	// guarda o nivel de inviabilidade da solução anterior para ser utilizado posteriormente para ver se a solução melhorou
	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;

	if( Imprime == 1){
		cin >> PararPrograma;
	}
// enquanto existir uma tarefa que pode ser retirada
	while( ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, Imprime) == 1 ){
		if( Imprime == 1){
			cout << endl << endl << "        Inicia procediemnto " << endl << endl;
		}
		// limpa o vetor de dados que foram removidos no processo
		DadosTarefasMovidas.clear();
		if( Imprime == 1){
			cout << endl << endl << "  ========== Deleta tarefas apos a demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;
			if( ImprimeDadosTarefasArmazenados == 1){
				cout << "DadosTarefasMovidas" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasMovidas);
			}
			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
			//PlantasInstancia.Imprime(1,1);
			cin >> PararPrograma;
		}
		// caso conseguiu deletar a demanda e suas posteriores entra no if
		if ( DeletaAlocacaoTarefasPosterioresMesmaConstrucao(0, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, DadosTarefasMovidas) == 1){
			// marca as cosntruções que possuem demandas que podem ser atendidas, essa construção não pode ser a ConstrucaoAnalisandoRetirada que é marcada com 5 para não ser analisada
			ConstrucoesInstancia.InicializaConstrucoesComDemandasNaoAtendidas( ConstrucaoAnalisandoRetirada, Imprime);
			// enaquanto se puder analisar uma construção que se pode atender uma demanda se continua
			while( ConstrucoesInstancia.ExisteConstrucaoComDemandaNaoAtendida(  ConstrucaoParaInserir, DemandaParaInserir, Imprime) == 1){
				// ordena as plantas com o tipo de ordenação escolhida
				PlantasInstancia.OrdenaPlantas( EscolhaPlanta);
				// armazena a ordem escolhida das plantas
				PlantasInstancia.ArmazenaVetorIntComOrdem( VetorOrdemPlanta);
				// percorre por todas as plantas
				for( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++ ){
					if( Imprime == 1){
						cout << " Planta " << VetorOrdemPlanta[p] << endl << endl;
					}
					// aloca indice da planta
					PlantasInstancia.AlocaInidiceFabrica( VetorOrdemPlanta[p], IndicePlanta);
					// ordena os veículos com o tipo de ordenação escolhida
					PlantasInstancia.Plantas[IndicePlanta].VeiculosDaPlanta.OrdenaCarretas(EscolhaVeiculo);
					// armazena a ordem escolhida dos veículos
					PlantasInstancia.Plantas[IndicePlanta].VeiculosDaPlanta.ArmazenaVetorIntComOrdem( VetorOrdemVeiculo);
					// percorre por todos os veículo
					for( int v = 0; v < (int) PlantasInstancia.Plantas[IndicePlanta].VeiculosDaPlanta.Carretas.size(); v++){
						if( Imprime == 1){
							cout << " veiculo [" << VetorOrdemPlanta[p] << "-" << VetorOrdemVeiculo[v] << "]" << endl;
						}
						// limpa o conteudo das tarefas movidas na analise de uma planta e veiculo fixo
						DadosTarefasMovidasPlantaVeiculo.clear();
						// caso conseguir alocar a demanda que não era atendida antes
						if( ConstrucoesInstancia.AdicionaTarefaComVeiculoFixo(0, ConstrucaoParaInserir,DemandaParaInserir, VetorOrdemPlanta[p], VetorOrdemVeiculo[v], DadosTarefasMovidasPlantaVeiculo, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, Imprime, "Solucao::Viabilidade1") == 1){
							if( Imprime == 1){
								cout << endl << endl << "         Aloca demanda não atendida anteriormente [ " << ConstrucaoParaInserir << "-" << DemandaParaInserir << "]" << endl << endl;
								cout << endl << "  tenta alocar tarefa" << endl;
								if( ImprimeDadosTarefasArmazenados == 1){
									cout << "DadosTarefasMovidas" << endl;
									ImprimeVetorDadosTarefa( DadosTarefasMovidas);
								}
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
								//PlantasInstancia.Imprime(1,1);
								cin >> PararPrograma;
							}
							// tento readicionar as demandas que foram retiradas
							ReadicionaTarefas(0, ConstrucaoAnalisandoRetirada,DadosTarefasMovidasPlantaVeiculo, 1, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, Imprime);
							// calcula o nível de iniviabilidade da solução
							ConstrucoesInstancia.CalcularNivelDeInviabilidade();
							if( Imprime == 1){
								cout << endl << endl << "         Readicionou tarefas deletadas no inicio do procedimento " << endl << endl;
								if( ImprimeDadosTarefasArmazenados == 1){
									cout << "DadosTarefasMovidasPlantaVeiculo" << endl;
									ImprimeVetorDadosTarefa(DadosTarefasMovidasPlantaVeiculo);
								}
								ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
								//PlantasInstancia.Imprime(1,1);
								cin >> PararPrograma;
							}
							// verifica se melhorou a solução
							if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){

								if( Imprime == 1){
									cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;
									if( ImprimeDadosTarefasArmazenados == 1){
										cout << "DadosTarefasMovidas" << endl;
										ImprimeVetorDadosTarefa( DadosTarefasMovidas);
										cout << "DadosTarefasMovidasPlantaVeiculo" << endl;
										ImprimeVetorDadosTarefa(DadosTarefasMovidasPlantaVeiculo);
									}
									ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
									//PlantasInstancia.Imprime(1,1);

									cin >> PararPrograma;
								}
								if( ImprimeSolucao == 1){
									printf(  "  -> Nivel de inviabilidade = %d com a inserção da demanda [%d-%d] \n", ConstrucoesInstancia.NivelDeInviabilidade, ConstrucaoParaInserir, DemandaParaInserir);
								}
								if( ImprimeArquivo == 1){
									fprintf( Arquivo, "  -> Nivel de inviabilidade = %d com a inserção da demanda [%d-%d] \n", ConstrucoesInstancia.NivelDeInviabilidade, ConstrucaoParaInserir, DemandaParaInserir);
								}

								// deleta o armazenamento d etarefas adicionadas e deletadas, pois a solução que se encontrou é melhor uqe a solução anterior
								DadosTarefasMovidas.clear();
								DadosTarefasMovidasPlantaVeiculo.clear();
								return 1;
							}else{
								if( Imprime == 1){
									cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;
									if( ImprimeDadosTarefasArmazenados == 1){
										cout << "DadosTarefasMovidasPlantaVeiculo" << endl;
										ImprimeVetorDadosTarefa( DadosTarefasMovidasPlantaVeiculo);
									}
									ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
									//PlantasInstancia.Imprime(1,1);

									cin >> PararPrograma;
								}
								// retorna a solução a  consição inicial após deletar as demandas
								if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasPlantaVeiculo, PlantasInstancia ) == 0){
									cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
								}
							}
						}
					}
				}

			}

			// marca que a demanda corrente já foi retirada
			ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);
			if( Imprime == 1){
				cout << endl << endl << "          Deleta tarefas adicionadas, readiciona as deletadas e marca demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;

				if( ImprimeDadosTarefasArmazenados == 1){
					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);
				}
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
				//PlantasInstancia.Imprime(1,1);

				cin >> PararPrograma;
			}
			// retorna a solução a  condição inicial
			if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia ) == 0){
				cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
			}
			// marca que a demanda corrente já foi retirada
			ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);
			if( Imprime == 1){
				cout << endl << endl << "            Nao consegui adicionar nova tarefa - readiciona tarefas e marca terafa como removida" << endl << endl;

				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
				//PlantasInstancia.Imprime(1,1);

				cin >> PararPrograma;
			}

		}else{
			 cout << endl << endl << endl << "   #######################  Problema! => Tarefa não deletada -> Solucao::Viabilidade1  ######################## " << endl << endl << endl;
		}
	}
	// deleta o armazenamento d etarefas adicionadas e deletadas, pois a solução que se encontrou é melhor uqe a solução anterior
	DadosTarefasMovidas.clear();
	DadosTarefasMovidasPlantaVeiculo.clear();
	return 0;
}

void	Solucao::ProcessoViabilizacao1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){

	// calcula o nível de iniviabilidade da solução
	CalculaNiveisViabilidade();

	// escreve o nivel de inviabilidade antes de entrar no processo de viabilização
	if( ImprimeSolucao == 1){
		printf( "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}

	// Executa o processo de viabilização e escreve na tela caso melhorou a solução
	while( Viabilidade1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,Imprime, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas) == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){

	}


}


// deleta a demanda passada na função e as demandas seguintes a está na construção, mas só armazena na estrutura a demanda passada na função
int		Solucao::DeletaUltimaDemandaConstrucaoEmAnalise( int ConstrucaoNaoAtendida, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendidaInicio, vector < DadosTarefa > &DadosTarefasDemandasAnteriores){
	// variaveis que armazena os dados da tarefa deletada e que será armazenada
	int PlantaEmAnalise;
	int CaminhaoEmAnalise;
	int ConstrucaoEmAnalise;

	// variaveis que armazena os horarios da tarefa deletada e que será armazenada
	double HorarioInicioConstrucao;
	double HorarioFinalConstrucao;

	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	// inidices da planta e do veiculo
	int p;
	int v;

	// tarefas deletadas mas que não tem necessidad de serem armazenadas
	vector < DadosTarefa > DadosTarefasLixo;

	// aramzena os dados e os horarios da tarefa que se quer armazenar
	ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].RetornaDadosDescarregamento( DemandaNaoAtendidaInicio, PlantaEmAnalise, CaminhaoEmAnalise, ConstrucaoEmAnalise, HorarioInicioConstrucao,HorarioFinalConstrucao);

	// aloca os indices da planta e da carreta
	if( PlantasInstancia.AlocaInidiceFabrica( PlantaEmAnalise, p) == 0 || 	PlantasInstancia.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(CaminhaoEmAnalise,v) == 0){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Alocar indice planta [" << PlantaEmAnalise << "] => " << p << " ou veiculo [" << CaminhaoEmAnalise << "] => " << v << " ->Solucao::DeletaUltimaDemandaConstrucaoEmAnalise >>>>>>>>>> " << endl << endl;
		// retorna 0, pois não encontrou o indice da planta
		return 0;
	}

	// aloca horarios da planta
	HorarioInicioPlanta = HorarioInicioConstrucao - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucaoNaoAtendida] -  PlantasInstancia.Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  PlantasInstancia.Plantas[p].TempoPlanta;

	// aloca horarios da carreta
	HorarioInicioCarreta = HorarioInicioPlanta;
	HorarioFimCarreta = HorarioFinalConstrucao + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucaoNaoAtendida];

	if( AdicionaElementoVetorDadosTarefa(0, DadosTarefasDemandasAnteriores, ConstrucaoNaoAtendida, PlantaEmAnalise, CaminhaoEmAnalise, 1,0, HorarioInicioPlanta, HorarioFimPlanta, HorarioInicioConstrucao,HorarioFinalConstrucao, HorarioFimCarreta,'r') == 0){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Problema em alocar a tarefa da cosntrução [" << ConstrucaoNaoAtendida << "] (" << HorarioInicioConstrucao << "-" << HorarioFinalConstrucao << ") da planta [" << PlantaEmAnalise << "] (" << HorarioInicioPlanta << "-" << HorarioFimPlanta << ") caminhão [" << CaminhaoEmAnalise << "] (" << HorarioInicioCarreta << "-" << HorarioFimCarreta << ") ->Solucao::DeletaUltimaDemandaConstrucaoEmAnalise >>>>>>>>>> " << endl << endl;
		// retorna 0, pois não encontrou o indice da planta
		return 0;
	}
	// limpa o vetor das tarefas que não precisam ser armazenadas
	DadosTarefasLixo.clear();
	// deleta todaas as tarefas apos a demanda passada na função, deleta inculive a demanda passasda na função
	ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DeletaTarefas( 0, DemandaNaoAtendidaInicio, DadosTarefasLixo,  PlantasInstancia);
	// limpa o vetor das tarefas que não precisam ser armazenadas
	DadosTarefasLixo.clear();

	//cout << endl << endl << " 		+-+- Demanda deletada 1 = [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendidaInicio << "]  para atender [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendidaFim << "] +-+- "<< endl << endl;
	//ImprimeVetorDadosTarefa(DadosTarefasDemandasAnteriores);

	return 1;
}

// seleciona a construção a ser analisada no momento
int		Solucao::SelecionaConstrucao( int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice){

	// passa por todas as construções
	for( int c = 0; c < NE; c++){
		// verifica se ela ainda tem demandas a serem atendidas
		if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
			// verifica se a construção ainda pode ser analisada
			if( ConstrucoesInstancia.Construcoes[c].ConstrucaoAnalizada == 0){
				// armazena os dados da cosntrução corrente
				ConstrucaoParaAtender = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
				ConstrucaoParaAtenderIndice = c;
				// retorna 1 caso encontrou uma construção
				return 1;
			}
		}
	}

	// retorna 0 caso não encontrou uma construção
	return 0;
}

// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas
int		Solucao::ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida){

	// variaveis que armazenam os valores temporarios da construção, da demanda  e da distancia minima da construção a uma planta
	int ConstrucaoTemporario;
	int DemandaTemporaria;


	// inicia valores das variaveis cosntrução e demanda
	ConstrucaoTemporario = -13;
	DemandaTemporaria = -13;

	// percorre por todas as construções
	for ( int c = 0; c < NE; c++){
		// entra se a construção possa ser analisada ainda pelo procedimento
		if( ConstrucoesInstancia.Construcoes[c].ConstrucaoPodeSerSuprida == 0){
			// percorre por todas as demandas iniciando da maior para a menor, isso tem o intuito de pegar a demanda não atendida logo após a ultima que foi atendida
			if( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento ){
				if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[ ConstrucoesInstancia.Construcoes[c].StatusAtendimento] == 0){
					DemandaNaoAtendida = ConstrucoesInstancia.Construcoes[c].StatusAtendimento;
					ConstrucaoNaoAtendida = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					return 1;
				}
			}
		}
	}
	return 0;




	// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas
	/*

	double DistanciaPlantaTemporaria;
	// inicia o valor da variavel com o maior valor para que qualquer valor de uma distancia de uma construção a uma planat sejáa ceito inicialmente
	DistanciaPlantaTemporaria = DBL_MAX;

	// percorre por todas as construções
	for ( int c = 0; c < NE; c++){
		// entra se a construção possa ser analisada ainda pelo procedimento
		if( ConstrucoesInstancia.Construcoes[c].ConstrucaoPodeSerSuprida == 0){
			// percorre por todas as demandas iniciando da maior para a menor, isso tem o intuito de pegar a demanda não atendida logo após a ultima que foi atendida
			for ( int d = ConstrucoesInstancia.Construcoes[c].NumeroDemandas - 1; d >= 0  ; d--){
				// verifioca se a demanda corrente não foi atendida
				if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[d] == 0){
					// percorre todas as plantas para pegar a demanda não atendida que esteja mais perto de uma planta
					for ( int p = 0; p < NP; p++){
						// caso a distancia da planta a demanda corrente for menor que a distancia corrente, se entra no if
						if( DistanciaPlantaTemporaria >= ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
							// atualiza as variaveis com a demanda corrente
							DistanciaPlantaTemporaria = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
							ConstrucaoTemporario = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
							DemandaTemporaria = d;
						}
					}
				}
			}
		}
	}

	// se verifica se não conseguiu alocar nenhuma demanda não atendida no processo
	if( ConstrucaoTemporario == -13 || DemandaTemporaria == -13 ){
		// retorna 0, não conseguiu encontrar uma demanda
		cout << endl << endl << "      >>>>>>>>> Problema! Não encontrou demanda que deveria ter sido encontrada! -> Solucao::ProcuraConstrucaoNaoAtendida  " << endl << endl;
		return 0;
	}
	// retorna a demanda que não é atendida e que esta mais perto de uma planta
	ConstrucaoNaoAtendida = ConstrucaoTemporario;
	DemandaNaoAtendida = DemandaTemporaria;
	// retorna 1, foi encontrado a demanda
	return 1;

	*/
}

// Aloca o tempo que se pode começar a carregar uma carreta da planta para suprir a construção passada
void	Solucao::AlocaTempoPlantaPodeAtenderDemanda(int IndiceConstrucaoNaoAtendida, vector < double > &TempoPlantaConsegueAtender, int Imprime){

	// percorre todas as plantas
	for( int p = 0; p < NP; p++){
		// se o tempo minimo de funcionamento da planta for menor que o tempo que uma carreta partindo dela pode atender a cosntrução no inicio de seu funcioanmento, entra no if
		if( PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento  < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia - PlantasInstancia.Plantas[p].TempoPlanta){
			// atualiza o tempo que a planta pode atender a cosntrução como sendo o tempo que a carreta pode atender a construção no inicio do funcionamento da construção
			TempoPlantaConsegueAtender[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia - PlantasInstancia.Plantas[p].TempoPlanta;
		}else{
			// atualiza o tempo que a planta pode atender a construção como sendo o tempo que a planta começa a funcionar
			TempoPlantaConsegueAtender[p] = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
		}
	}

// Aloca o tempo que se pode começar a carregar uma carreta da planta como sendo o tempo da ultima carreta que realizou o ultimo carregamento naquela planta para está construção

	// caso a construção tenha uma demanda já atendida
	if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento > 0){
		// percorre por todas as demandas da cosntrução
		for( int d = 0; d < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento; d++ ){
			// percorre por todas as plantas
			for( int p = 0; p < NP; p++){
				// caso a planta corrente conseguir atender uma demanda anterior em relação a que se quer atender e em um horario maior que o já assinalado, se atualiza o tempo que a planta pode atender a construção
				if( TempoPlantaConsegueAtender[p] < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia){
					// atualiza o tempo que a planta pode atender a construção
					TempoPlantaConsegueAtender[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia;
				}
			}
		}
	}

// Imprimir o conteudo do vetor Tempo de saida da planta
	if( Imprime == 1){
		// passa por todas as plantas
		cout << endl << "           TempoPlantaConsegueAtender " << endl << endl;
		for( int p = 0; p < NP; p++){
			cout << " TempoPlantaConsegueAtender[" << p << "] = " << TempoPlantaConsegueAtender[p] << endl;
		}
		cout << endl << endl;
	}
}


// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender
int		Solucao::DeletaTarefasAposTempoPlantaPodeAtender(vector < double > &TempoPlantaPodeAtender, vector < DadosTarefa > &DadosTarefasMovidas,  int Imprime){

	int TarefaDeletada;
	int PlantaAux;
	int IndicePlantaAux;
	double DistanciaAux;
	int Ativa;

	int construcao;

	// inicializa variaveis
	Ativa = 0;

	//cout << endl << endl << "   Galo 1" << endl << endl;

	if( Imprime == 1){
		cout << endl << endl << "          <<<<<<<<<<< Inicio Deleta Tarefas >>>>>>>>>>>>>> " << endl << endl;
	}

	// percorre todas as construções
	for( int c = 0; c < NE; c++){
		//cout << endl << endl << "  Construcao " << c << endl << endl;

		// percorre todas as demandas da construção vingente
		for( int d = ConstrucoesInstancia.Construcoes[c].StatusAtendimento - 1; d >= 0 ; d--){
			//cout << " demanda = " << d << endl;

			// armazena os dados e a diastancia da planta que atende a demanda corrente
			PlantaAux = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;
			DistanciaAux = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[ PlantaAux ].Distancia;
			// pega o indice da planta
			if( PlantasInstancia.AlocaInidiceFabrica( PlantaAux, IndicePlantaAux) == 0){
				cout << endl << endl << "     >>>>>>>> Problema! Não encontrou a planta [" << PlantaAux << "]"<< endl << endl;
			}
			// verifica se a demanda corrente é atendida após o tempo que a planta pode atender a deamnda não atendida, ou se a deamnda corrente é atendia em um horario que irá confrontar com o atendiemnto da demanda não atendida ( a demanda corrente é atendida antes da demanda que se quer atender, mas seu termino de atendimento inviabiliza o atendimento da demnada não atendida no horario que a planta pode atende-la)
			if( ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento - DistanciaAux  > TempoPlantaPodeAtender[PlantaAux]){
				if( Imprime == 1){
					cout << "	-> Planta = " << PlantaAux << "   Demanda = [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "] indice construção (" << c << ")" << endl;
					ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].Imprime();
				}
				// pega a construção corrente
				construcao = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
				// deleta a demanda corrente
				TarefaDeletada =  DeletaAlocacaoTarefasPosterioresMesmaConstrucao(0, construcao, d,  DadosTarefasMovidas);
				// aumenta o nivel de inviabilidade, pois deletou uma demanda atendida
				ConstrucoesInstancia.NivelDeInviabilidade++;
				//cout << endl << endl << "   Galo 2" << endl << endl;

				if( TarefaDeletada == 1){
					// marca que se conseguiu deletar uma demanda
					Ativa = 1;
					if( Imprime == 1 ){
						cout << "        DELETADO -> Tarefa [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]  " << endl << endl;
					}
				}else{
					cout << "     >>>>>>>>>>>> Problema! Tarefa [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "] NÃO foi deletada " << endl << endl;
				}
			}
		}
	}

	if( Ativa == 1){
		// retorna 1 se deletou alguma tarefa
		return 1;
	}
	// retorna 0 se não deletou nenhuma tarefa
	return 0;

}



int		Solucao::Viabilidade2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){

	// armazena o nivel de inviabilidade anterior
	int InviabilidadeSolucaoAnterior;
	// dados da demanda não atendida
	int	ConstrucaoNaoAtendida;
	int IndiceConstrucaoNaoAtendida;
	int DemandaNaoAtendidaInicio;
	int DemandaNaoAtendidaFim;
	// dados da construção que será atendida
	int ConstrucaoParaAtender;
	int IndiceConstrucaoParaAtender;
	// indice da demanda da construção que será atendida
	int d2;

	// dados das plantas que podem atender a demanda em questão
	vector< int > PlantasPodemAtenderTarefa;
	vector < double > TempoPlantaPodeAtender;

	// variaveis de controle
	int TarefaAdicionada;

	// armazena as tarefas da solução que foram retiradas e adicionadas para permitir que se retorne ao estado inicial da solução depoois
	vector < DadosTarefa > DadosTarefasMovidasTentandoAlocar1;
	vector < DadosTarefa > DadosTarefasMovidasTentandoAlocar2;
	// armazena as tarefas deletadas na construção corrente para depois se retornar ao estado original da construção
	vector < DadosTarefa > DadosTarefasDemandasAnteriores;

	// vetores que armazena as plantas e dos veiculos antes de entrar em uma função de adição de tarefa
	vector < int > VetorOrdemPlanta;
	vector < int > VetorOrdemVeiculo;

	// indice da planta a ser utilizada
	int IndicePlanta;

	// se deve realizar a verificação da viabilidade da solução corrente
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	// variavel que informa se ainda é possivel analizar a cosntrução corrente
	int PermiteAnalisarCosntrucao;

	int PararPrograma;

	// ordena as cosntruções na ordem em que elas devem ser escolhidas com prioridade  (foi tirada para se manter a ordem realizado na heuristica constrututiva)
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// inicia o tamanho do vetor de tempo do inicio das plantas com 0
	TempoPlantaPodeAtender.resize(NP);

	if( Imprime == 1){
		cout << endl << endl << "                        Situacao ao entra no Viabilidade2 " << endl << endl;
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
	}

// Encontra demanda ainda não atendida

	// calcula o nivel de inviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	// guarda o nivel de inviabilidade
	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;

	// Marca as construções que já foram completamente atenddidas com 1, as que não forma com 0
	ConstrucoesInstancia.AlocaValoresConstrucaoPodeSerSuprida();

	// Verifica se pode atender uma construção ainda, se tem uma com demanda não atendida
	while( ConstrucoesInstancia.VerificaConstrucaoPodeSerSuprida() == 1 ){
		// retorna a demanda e a construção que serão analisados inicialmente
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendidaFim);
		// retorna o incide da cosntrução que tem qeu ser analisada no momento
		ConstrucoesInstancia.RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );
		// faz a primeira demanda analisada na construção como sendo a mesma da ultima analisada
		DemandaNaoAtendidaInicio = DemandaNaoAtendidaFim;
		// faz a variavel sinalisar que ainda é possivel analisar a construção corrente
		PermiteAnalisarCosntrucao = 1;
		// limpa o vetor que armazena as demandas deletadas na construção para tentar alocar a demanda corrente
		DadosTarefasDemandasAnteriores.clear();
		// enquanto for possivel analisar a construção se continua no loop
		while( PermiteAnalisarCosntrucao == 1){

// deleta tarefas que são atendidas depois desta tarefa não alocada

			// se limpa o vetor com as tarefas movidas durante o processo de se tentar atender a ultima demanda (DemandaNaoAtendidaFim)
			DadosTarefasMovidasTentandoAlocar1.clear();
			// aloca no vetor TempoSaiPlanta os tempos que as plantas podem atender
			AlocaTempoPlantaPodeAtenderDemanda(IndiceConstrucaoNaoAtendida,TempoPlantaPodeAtender, Imprime);
			// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender
			DeletaTarefasAposTempoPlantaPodeAtender(TempoPlantaPodeAtender, DadosTarefasMovidasTentandoAlocar1, Imprime);
			// caso não se tenha deletado nenhuma demanda anterior a demanda que se quer colocar na construção, se inicia essa variavel com 1 para entrar no procedimento
			TarefaAdicionada = 1;
			// caso se tenha demandas anteriores a demanda que se quer colocar, se tem que adicionar as demandas anteriores a esta que foram deletadas
			if( DemandaNaoAtendidaInicio < DemandaNaoAtendidaFim){
				// tenta adiciona a tarefa que não era alocada antes
				for( int d1 = DemandaNaoAtendidaInicio; d1 <= DemandaNaoAtendidaFim - 1; d1++){
					// tenta adicionar a demanda não atendida anteriormente. Caso consegui retorna 1, caso contrario retorna 0.
					TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefa(0, ConstrucaoNaoAtendida, d1, DadosTarefasMovidasTentandoAlocar1, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, Imprime, " adiciona tarefa não adicionada -> Solucao::ProcessoViabilizacao2 ");
				}
			}
			// se entra no if caso se tenha adicionado as demandas anteriores a demanda que se quer colocar, caso elas existam
			if( TarefaAdicionada == 1){
				// ordena as plantas com o tipo de ordenação escolhida
				PlantasInstancia.OrdenaPlantas( EscolhaPlanta);
				// armazena a ordem escolhida das plantas
				PlantasInstancia.ArmazenaVetorIntComOrdem( VetorOrdemPlanta);
				// percorre todas as plantas
				for ( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
					// aloca indice da planta
					PlantasInstancia.AlocaInidiceFabrica( VetorOrdemPlanta[p], IndicePlanta);
					// ordena os veículos com o tipo de ordenação escolhida
					PlantasInstancia.Plantas[IndicePlanta].VeiculosDaPlanta.OrdenaCarretas(EscolhaVeiculo);
					// armazena a ordem escolhida dos veículos
					PlantasInstancia.Plantas[IndicePlanta].VeiculosDaPlanta.ArmazenaVetorIntComOrdem( VetorOrdemVeiculo);
					// percorre todos os veículos d aplanta corrente
					for( int v = 0; v < (int) PlantasInstancia.Plantas[IndicePlanta].VeiculosDaPlanta.Carretas.size(); v++ ){
						// limpa o vetor de tarefas atendidas ao se tentar atender a demanda não atendida com o veículo corrente
						DadosTarefasMovidasTentandoAlocar2.clear();
						// tenta atender a demnada não atendida com o veículo corrente
						TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefaComVeiculoFixo(0, ConstrucaoNaoAtendida, DemandaNaoAtendidaFim, VetorOrdemPlanta[p], VetorOrdemVeiculo[v], DadosTarefasMovidasTentandoAlocar2, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, Imprime, " adiciona tarefa não adicionada -> Solucao::ProcessoViabilizacao2 ");
						// caso tenha conseguido atender a dmenada não atendida corrente se entra no if
						if( TarefaAdicionada == 1){
							// marca todas as construções como possiveis a alocar demandas, todas com 0 em ConstrucoesAnalisadas ( IMPORTANTE!!!!!!!!! Construções analizadas é diferente que ConstrucaoPodeSerSuprida. Elas desempenham funçẽos diferentes apesar de parecerem iguais)
							ConstrucoesInstancia.InicializaConstrucoesAnalizadas();
							// marca as construções com todas suas demandas atendidas com 2, e a construção que tinha uma demanda sem atender e que agora foi atendida com 3
							ConstrucoesInstancia.AlocaValoresConstrucoesAnalizadas( IndiceConstrucaoNaoAtendida);

							// Verifica se tem tarefa a se colocar

							// escolhe a construção com o menor indice e que pode ser atendida ( todas as construções com 0 em CosntruçõesAnalisadas, estas são as que não tem suas demandas todas atendidas e que não sejá a que passou a ter uma demanda que não era atendida antes e agora é atendida)
							while( SelecionaConstrucao( ConstrucaoParaAtender, IndiceConstrucaoParaAtender) == 1){
								// coloca a demanda que se tem que alocar no momento
								d2 = ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].StatusAtendimento;
								// faz que ainda é possivel se adicionar uma demanda na cosntrução corrente
								TarefaAdicionada = 1;
								// enquanto for possivel adicionar uma demanda na construção corrente e que a cosntrução ainda não tenha todas as suas demandas supridas, se mantem no loop
								while( d2 < ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].NumeroDemandas && TarefaAdicionada == 1){
									// tenta adicionar a demanda corrente (d2) a cosntrução
									TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefa( 0, ConstrucaoParaAtender, d2, DadosTarefasMovidasTentandoAlocar2, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, Imprime , " Readicionando -> Solucao::ProcessoViabilizacao2 ");
									// passa para a proxima demnada que se pode adicionar na construção
									d2++;
								}
								// caso se atendeu a todas as demandas da construção corrrente se entra no if
								if( TarefaAdicionada == 1){
									// caso todas as demandas da construção corrente tenham sido supridas, se entra no if
									if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].StatusAtendimento == ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].NumeroDemandas){
										// marca a construção como já atendida todas as suas demandas
										ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].ConstrucaoAnalizada = 1;
									}else{
										cout << endl << endl << "                  Não deveria ter entrado! Merda! " << endl << endl;
									}
								// caso não se atendeu a todas as demandas da construção corrrente se entra no else
								}else{
									// marca a construção como sendo que não se consegue atender suas demandas
									ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].ConstrucaoAnalizada = -1;
								}
							}
							// calcula o nivel de inviabilidade que ira mostrar se a soluçpão melhorou ou não
							ConstrucoesInstancia.CalcularNivelDeInviabilidade();
							// verifica se o nivel de inviabilidade foi melhorado com o procedimento
							if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
								// se escreve que melhorou
								if( Imprime == 1){
									cout << endl << endl << "    Melhorou !!!!!!" << endl << endl;
								}
								// se qescreve o novo nivel de inviabilidade após a melhora
								if( ImprimeSolucao == 1){
									printf(  "  -> Nivel de inviabilidade = %d com a inserção da demanda [%d-%d] \n", ConstrucoesInstancia.NivelDeInviabilidade, ConstrucaoNaoAtendida, DemandaNaoAtendidaFim);
								}
								if( ImprimeArquivo == 1){
									fprintf( Arquivo, "  -> Nivel de inviabilidade = %d com a inserção da demanda [%d-%d] \n", ConstrucoesInstancia.NivelDeInviabilidade, ConstrucaoNaoAtendida, DemandaNaoAtendidaFim);
								}

								//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0,1,0,Arquivo);

								// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
								DadosTarefasMovidasTentandoAlocar1.clear();
								DadosTarefasMovidasTentandoAlocar2.clear();
								DadosTarefasDemandasAnteriores.clear();
								VetorOrdemPlanta.clear();
								VetorOrdemVeiculo.clear();
								// retorna 1, sinalizando que se melhorou a solução
								return 1;
							}else{
								// se escreve que não melhorou a solução
								if( Imprime == 1){
									cout << endl << endl << "    Não melhorou !!!!!!" << endl << endl;
								}
								// retorna a solução a  condição inicial
								if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasTentandoAlocar2, PlantasInstancia ) == 0){
									cout << endl << endl << "   problema em adicionar e deletar tarefas DadosTarefasMovidasTentandoAlocar ->  Solucao::ProcessoViabilizacao2" << endl << endl;
								}
							}
						}
					}
				}
				// se reinicia a configuração antes de deletar e adicionar demandas antes da demanda que se quer colocar
				if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasTentandoAlocar1, PlantasInstancia ) == 0){
					cout << endl << endl << "   problema em adicionar e deletar tarefas DadosTarefasDemandasAnteriores ->  Solucao::ProcessoViabilizacao2" << endl << endl;
				}
				// se dimeinui a demanda inicial que é analisada na construção que se quer que a demanda sejaa atendida
				DemandaNaoAtendidaInicio--;
				// caso a demanda inicial não for valida, menor que 0, entra no if
				if( DemandaNaoAtendidaInicio < 0){
					// faz que não se pode mais analisar está construção
					PermiteAnalisarCosntrucao = 0;
				}else{
					// caso ainda de para analisar a construção, se deleta a demanda inicial da solução corrente, se guarda essa tarefa em uma estrutura de dados e trabalha com a solução sem a demanda inicial deletada
					DeletaUltimaDemandaConstrucaoEmAnalise( ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, DemandaNaoAtendidaInicio, DadosTarefasDemandasAnteriores);
				}
			}else{
				// se reinicia a configuração antes de deletar e adicionar demandas antes da demanda que se quer colocar
				if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasTentandoAlocar1, PlantasInstancia ) == 0){
					cout << endl << endl << "   problema em adicionar e deletar tarefas DadosTarefasDemandasAnteriores ->  Solucao::ProcessoViabilizacao2" << endl << endl;
				}
				// se dimeinui a demanda inicial que é analisada na construção que se quer que a demanda sejaa atendida
				DemandaNaoAtendidaInicio--;
				// caso a demanda inicial não for valida, menor que 0, entra no if
				if( DemandaNaoAtendidaInicio < 0){
					// faz que não se pode mais analisar está construção
					PermiteAnalisarCosntrucao = 0;
				}else{
					// caso ainda de para analisar a construção, se deleta a demanda inicial da solução corrente, se guarda essa tarefa em uma estrutura de dados e trabalha com a solução sem a demanda inicial deletada
					DeletaUltimaDemandaConstrucaoEmAnalise( ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, DemandaNaoAtendidaInicio, DadosTarefasDemandasAnteriores);
				}
			}
		}
		// recoloca as demandas anteriores na construção corrente
		if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasDemandasAnteriores, PlantasInstancia ) == 0){
			// probelam em readicionar as demandas
			cout << endl << endl << "   problema em adicionar e deletar tarefas DadosTarefasDemandasAnteriores ->  Solucao::ProcessoViabilizacao2" << endl << endl;
		}
		// não consegui atender a demanda da cosntrução, marco ela com 4
		ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].ConstrucaoPodeSerSuprida = 4;
	}

	//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0,1,0,Arquivo);
	DadosTarefasMovidasTentandoAlocar1.clear();
	DadosTarefasMovidasTentandoAlocar2.clear();
	DadosTarefasDemandasAnteriores.clear();
	VetorOrdemPlanta.clear();
	VetorOrdemVeiculo.clear();
	return 0;
}

void	Solucao::ProcessoViabilizacao2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){
	//int PararPrograma;

	// calcula o nível de iniviabilidade da solução
	CalculaNiveisViabilidade();
	// escreve o nivel de inviabilidade antes de entrar no processo de viabilização
	if( ImprimeSolucao == 1){
		printf( "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}

	// Executa o processo de viabilização e escreve na tela caso melhorou a solução
	while( Viabilidade2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,Imprime, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas) == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){
		//cout << endl << endl << endl << " Melhorou solução " << endl << endl << endl;
		//cin >> PararPrograma;
	}

}

// calcula o makespan geral da solução
void	Solucao::CalculaMakespan(){
	// calcula makespan das cosntruções e das plantas
	PlantasInstancia.CalculaMakespanPlantas();
	ConstrucoesInstancia.CalculaMakespansConstrucoes();
	 // caculo o makespan geral da solução
	Makespan = PlantasInstancia.MakespanPLantas + ConstrucoesInstancia.MakespanConstrucoes;
}

void	Solucao::CalculaNiveisViabilidade(){
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
}

void	Solucao::RealizarBuscaLocalCaminhao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){
	// calsse da busca local
	BuscaLocal busca;

	// variaveis de controle do processo, para contar o numero de iterações e para parar o programa
	int NumeroDeVezes;
	//int ParaPrograma;
	int ImprimeEstruturas;
	int ImprimeProcedimento;

	// inicializa o numero de iterações como zero
	NumeroDeVezes = 0;
	ImprimeEstruturas = 0;
	ImprimeProcedimento = 0;

	// carrega os dados da solução para a classe da busca local
	busca.CarregaSolucao( NP, PlantasInstancia, NE,	ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	// equanto o procediemnto da busca local melhorar a solução que se tem, se continua no while
	while ( busca.BuscaLocalTentaRealizarTarefasComOutosVeiculos(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeProcedimento, ImprimeEstruturas, RealizaProcessoDeAtrazarTarefas) == 1){
		// carrega a nova solução que se obteve
		CarregaSolucao(busca.NP, busca.PlantasInstancia, busca.NE, busca.ConstrucoesInstancia, busca.NV , busca.Velocidade , busca.TempoDeVidaConcreto);

		// calcula o makespan geral
		CalculaMakespan();
		// aumenta o numero de iterações em 1
		NumeroDeVezes++;

		// cacula o nivel de iniviabilidade para se verificar se a solução continua viavel
		ConstrucoesInstancia.CalcularNivelDeInviabilidade();
		// verifica status da da solução
		if( ConstrucoesInstancia.NivelDeInviabilidade != 0 ){
			cout << endl << endl << endl << "         >>>>>>>>>>>>>  Probelam com a viabilidade da solução na busca local 1 (caminhão) <<<<<<<<<<<< " << endl << endl << endl;
		}

		if( imprime == 1){
			if( ImprimeSolucao == 1){
				cout << " iteração " << NumeroDeVezes << "    Solução = " << Makespan << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo, "  Iteração %d     Solução = %f \n",  NumeroDeVezes , Makespan);
			}
		}

	}
}

void	Solucao::RealizarBuscaLocalConstrucao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){
	// calsse da busca local
	BuscaLocal busca;

	// variaveis d econtrole do processo, para contar o numero de iterações e para parar o programa
	int NumeroDeVezes;
	//int ParaPrograma;
	int ImprimeEstruturas;
	int ImprimeProcedimento;

	// inicializa o numero de iterações como zero
	NumeroDeVezes = 0;
	ImprimeEstruturas = 0;
	ImprimeProcedimento = 0;

	// carrega os dados da solução para a classe da busca local
	busca.CarregaSolucao( NP, PlantasInstancia, NE,	ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	// equanto o procediemnto da busca local melhorar a solução que se tem, se continua no while
	while ( busca.BuscaLocalMudaOrdemAtendiemntoConstrucoes(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeProcedimento, ImprimeEstruturas, RealizaProcessoDeAtrazarTarefas) == 1){
		// carrega a nova solução que se obteve
		CarregaSolucao(busca.NP, busca.PlantasInstancia, busca.NE, busca.ConstrucoesInstancia, busca.NV , busca.Velocidade , busca.TempoDeVidaConcreto);

		// calcula o makespan geral
		CalculaMakespan();
		// aumenta o numero de iterações em 1
		NumeroDeVezes++;

		// cacula o nivel de iniviabilidade para se verificar se a solução continua viavel
		ConstrucoesInstancia.CalcularNivelDeInviabilidade();
		// verifica status da da solução
		if( ConstrucoesInstancia.NivelDeInviabilidade != 0 ){
			cout << endl << endl << endl << "         >>>>>>>>>>>>>  Probelam com a viabilidade da solução na busca local 2 (construções) <<<<<<<<<<<< " << endl << endl << endl;
		}

		if( imprime == 1){
			if( ImprimeSolucao == 1){
				cout << " iteração " << NumeroDeVezes << "    Solução = " << Makespan << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo, "  Iteração %d     Solução = %f \n",  NumeroDeVezes , Makespan);
			}
		}

	}
}


void	Solucao::RealizarBuscaLocalPlanta(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){
	// calsse da busca local
	BuscaLocal busca;

	// variaveis d econtrole do processo, para contar o numero de iterações e para parar o programa
	int NumeroDeVezes;
	//int ParaPrograma;
	int ImprimeEstruturas;
	int ImprimeProcedimento;

	// inicializa o numero de iterações como zero
	NumeroDeVezes = 0;
	ImprimeEstruturas = 0;
	ImprimeProcedimento = 0;

	// carrega os dados da solução para a classe da busca local
	busca.CarregaSolucao( NP, PlantasInstancia, NE,	ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	// equanto o procediemnto da busca local melhorar a solução que se tem, se continua no while
	while ( busca.BuscaLocalTrocaPlantaAtendimento(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeProcedimento, ImprimeEstruturas, RealizaProcessoDeAtrazarTarefas) == 1){
		// carrega a nova solução que se obteve
		CarregaSolucao(busca.NP, busca.PlantasInstancia, busca.NE, busca.ConstrucoesInstancia, busca.NV , busca.Velocidade , busca.TempoDeVidaConcreto);

		// calcula o makespan geral
		CalculaMakespan();
		// aumenta o numero de iterações em 1
		NumeroDeVezes++;

		// cacula o nivel de iniviabilidade para se verificar se a solução continua viavel
		ConstrucoesInstancia.CalcularNivelDeInviabilidade();
		// verifica status da da solução
		if( ConstrucoesInstancia.NivelDeInviabilidade != 0 ){
			cout << endl << endl << endl << "         >>>>>>>>>>>>>  Probelam com a viabilidade da solução na busca local 3 (planta) <<<<<<<<<<<< " << endl << endl << endl;
		}

		if( imprime == 1){
			if( ImprimeSolucao == 1){
				cout << " iteração " << NumeroDeVezes << "    Solução = " << Makespan << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo, "  Iteração %d     Solução = %f \n",  NumeroDeVezes , Makespan);
			}
		}

	}
}

Solucao::~Solucao(){

}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class ConjuntoSolucoes{
public:
	vector < Solucao > Solucoes;
	ConjuntoSolucoes();			// classe construtoora
	void	InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);			// carrega uma solução ao vetor das soluções
	void	CalculaMakespanSolucoes();		// calcula o makespan das soluções
	void	CalculaNiveisViabilidadeSolucoes();		// calcula o niveis de viabilidade das solução
	void	Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade, int ImprimeSolucao , int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// imprime as soluções
	~ConjuntoSolucoes();

};

// classe construtoora
ConjuntoSolucoes::ConjuntoSolucoes(){
}

// carrega uma solução ao vetor das soluções
void	ConjuntoSolucoes::InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	Solucao S1;
	// carrega dasos da solução
	S1.CarregaSolucao( np, Plantas, ne, Construcoes, nv, v, TDVC);
	// colocar a solução carregada nbo vetor de soluções
	Solucoes.push_back(S1);
}

// calcula o makespan das soluções
void	ConjuntoSolucoes::CalculaMakespanSolucoes(){
	// percorre por todas as soluções
	for( int s = 0; s <  (int) Solucoes.size(); s++){
		// calcula o makespan da solução corrente de suas construções
		Solucoes[s].CalculaMakespan();
	}
}

// calcula o makespan das soluções
void	ConjuntoSolucoes::CalculaNiveisViabilidadeSolucoes(){
	// percorre por todas as soluções
	for( int s = 0; s <  (int) Solucoes.size(); s++){
		// calcula o nivel de viabilidade da solução
		Solucoes[s].CalculaNiveisViabilidade();
	}
}

// imprime as soluções
void	ConjuntoSolucoes::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade, int ImprimeSolucao ,int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// percorre por todas as soluções
	for( int s = 0; s <  (int) Solucoes.size(); s++){
		if( ImprimeSolucao == 1){
			// imprime a solução corrente
			cout << endl << endl << "   Solucao " << s << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo, "\n\n   Solucao %d \n\n", s);
		}
		 Solucoes[s].Imprime(ImprimePlanta,ImprimeConstrucao, VerificaViabilidade, ImprimeSolucao, ImprimeArquivo, Arquivo);
		 // escreve o makespan total da solução
		 if( ImprimeSolucao == 1){
			 cout << "         Makespan total = " << Solucoes[s].Makespan << endl ;
		 }
		 if( ImprimeArquivo == 1){
			fprintf( Arquivo, "         Makespan total = %f", Solucoes[s].Makespan);
		}
	}
}



ConjuntoSolucoes::~ConjuntoSolucoes(){

}



#endif /* SOLUCOES_HPP_ */
