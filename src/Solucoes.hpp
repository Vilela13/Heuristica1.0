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
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	double Makespan;

	Solucao();

	void CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);		// Carrega os dados da instancia e a solução até o momento
	void Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);									// imprime os dados da solução
	int DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas);					// deleta demandas atendidas na construção após certa demanda que é passada com parametro

	int ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia,  int Construcao,  int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int EscolhaVeiculo, int EscolhaPlanta, int imprime);				// Tenta alocar uma demanda que não era alocada anteriormente
	void ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int EscolhaVeiculo,int EscolhaPlanta, int imprime);						// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
	int ConstrucaoTemTarefaParaRemover(int& Construcao, int& Demanda, int Imprimir);	// Usado em ProcessoViabilizacao1. Verifica se possui uma construção que possui demandas que ainda não foram retiradas para se tentar a viabilização da solução. Caso possuir, retorna 1 a função e é retornado os dados da construção e da demanda por parametro.

	int Viabilidade1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);
	void ProcessoViabilizacao1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);


	int DeletaUltimaDemandaConstrucaoEmAnalise( int ConstrucaoNaoAtendida, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendidaInicio, vector < DadosTarefa > &DadosTarefasDemandasAnteriores);		// deleta a demanda passada na função e as demandas seguintes a está na construção, mas só armazena na estrutura a demanda passada na função

	int SelecionaConstrucao(int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucoesAnalizadas);	// seleciona a construção a ser analisada no momento
	int  ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida);																	// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas
	void AlocaTempoPlantaPodeAtenderDemanda(int IndiceConstrucaoNaoAtendida, vector < double > &TempoPlantaConsegueAtender, int Imprime);					// Aloca o tempo inicial que se pode sair uma carreta da planta para suprir a construção passada

	int DeletaTarefasAposTempoPlantaPodeAtender(vector < double > &TempoPlantaPodeAtender, vector < DadosTarefa > &DadosTarefasMovidas,  int Imprime );		// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender

	int Viabilidade2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);
	void ProcessoViabilizacao2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);

	void CalculaMakespan();		// calcula o makespan geral da solução

	void RealizarBuscaLocalCaminhao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);
	void RealizarBuscaLocalConstrucao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);
	void RealizarBuscaLocalPlanta(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);

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
void Solucao::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
}

// imprime os dados da solução
void Solucao::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade ,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){


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
int Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas){
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


// Tenta alocar uma demanda que não era alocada anteriormente
int Solucao::ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia, int Construcao,  int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int EscolhaVeiculo, int EscolhaPlanta, int imprime){
	// indice da construção
	int c;

	// variavel que representa a demanda analisada no momento
	int demandas;
	// variavel constrole para avaliar se consegue atender as demandas da construção. caso não se consiga atender a uma anterior, não se irá conseguir atender as posteriores a essa
	int Ativa;


	// verifica se a construção passada existe na instancia
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, "  <<<<    Solucao::ProcessoParaAlocarTarefaNaoAtendida  >>>>>") == 0){
		return -1;
	}

	// percorre todas as construções
	for(  int contrucoes = 0; contrucoes < (int) ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		// não tenta aloca demandas da construçãoq ue teve uma demanda retirada anteriormente
		if( contrucoes != c){
			// inicializa com a primeira demanda da cosntrução
			demandas = 0;
			// sinaliza que ainda pode atender as demandas seguintes
			Ativa = 0;
			// percorre todas as demandas da construção corrente
			while( demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas && Ativa == 0){
				// verifica se a demnada corrente ainda não foi alocada
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					if( imprime == 1){
						cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "]  -> Solucao::ProcessoParaAlocarTarefa";
					}
					//caso alocar a demanda
					if( ConstrucoesInstancia.AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, SituacaoRetirada, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, imprime, "Solucao::ProcessoParaAlocarTarefaNaoAtendida") == 1){
						if( imprime == 1){
							cout << " => Alocou [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ProcessoParaAlocarTarefa" << endl;
						}
						// retorna a cosntruçãoq ue teve uma demanda alocada
						NovaTarefaAlocadaConstrucao = ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao;
						// retorna a demanda adicionada
						NovaTarefaAlocadaDemanda = demandas;
						// sai da função e avisa que consegui alocar uma demanda
						return 1;
					}else{
						// caso a demanda corrente que não tenha sido alocada ainda e não se conseguiu atende-lá pelo método, se atribui o valor 1 a variavel "Ativa" sinalizando que as proximas demandas da construção também não se conseguira atender. Isso é pelo fato de que a demanda anterior não foi atendida ainda, as proximas também não se conseguira atender. Isso faz fugir do loop do while da construção para analisar as demandas da cosntrução corrente
						Ativa = 1;
						if( imprime == 1){
							cout << " = (      Não consegue alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ProcessoParaAlocarTarefa" << endl;
						}
					}
				}else{
					// passa para a proxima demanda a se analisar
					demandas++;
				}
			}
		}
	}
	// não conseguir alocar a demanda da função, retorna 0
	return 0;
}

// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
void Solucao::ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int EscolhaVeiculo,int EscolhaPlanta, int imprime){
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
int Solucao::ConstrucaoTemTarefaParaRemover(int& Construcao, int& Demanda, int Imprimir){

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


int Solucao::Viabilidade1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){

	// Imprime os dados das tarefas armazenadas durante o processo
	int ImprimeDadosTarefasArmazenados;
	ImprimeDadosTarefasArmazenados = 0;


	// armazena o nivel de inviabilidade anterior
	int InviabilidadeSolucaoAnterior;
	// armazana os dados da tarefa a ser retirada
	int ConstrucaoAnalisandoRetirada;
	int DemandaAnalisandoRetirada;

	// armazena os dados da tarefa a ser alocada
	int NovaTarefaAlocadaConstrucao;
	int NovaTarefaAlocadaDemanda;

	// variaveis de controle
	bool ExisteTarefa;
	bool TarefaDeletada;
	bool TarefaAlocada;

	// armazena as tarefas da solução que foram retiradas e adicionadas para permitir que se retorne ao estado inicial da solução depoois
	vector < DadosTarefa > DadosTarefasMovidas;

	//  variavel que controla se deve realizar o processo de atraso de tarefas para tentar atrazar uma outra mais posterior que pode ser atendida caso se atraze as tarefas anteriores a ela
	int RealizaProcessoDeAtrazarTarefas;
	RealizaProcessoDeAtrazarTarefas = 1;

	//se deve realizar a verificação da viabilidade da solução corrente
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	// variavel para parar o programa
	int PararPrograma;

	// ordena cosntruções
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// faz que nenhuma tarefa tenha sido removida
	ConstrucoesInstancia.ReiniciaTarefasRetiradas();
	// guarda o nivel de inviabilidade da solução anterior para ser utilizado posteriormente para ver se a solução melhorou
	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;

	// Encontra primeira tarefa que pode ser retirada
	ExisteTarefa = ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, Imprime);

	if( Imprime == 1){
		cin >> PararPrograma;
	}
// enquanto existir uma tarefa que pode ser retirada
	while( ExisteTarefa == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){
		if( Imprime == 1){
			cout << endl << endl << "        Inicia procediemnto " << endl << endl;
		}
		// limpa o vetor de dados que foram removidos no processo
		DadosTarefasMovidas.clear();
// deleta demanda alocada e as demandas posteriores a esta nesta construção corrente
		TarefaDeletada = DeletaAlocacaoTarefasPosterioresMesmaConstrucao(0, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, DadosTarefasMovidas);	// Deleta tarefa
		// calcula o nível de iniviabilidade da solução
		ConstrucoesInstancia.CalcularNivelDeInviabilidade();
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
		if ( TarefaDeletada == 1){
			// Aloca valores aos inidices da construção e da demanda que não era atendida antes  equa passara a ser atendia
			AlocaValoresIniciaisIndices( NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);
			// tenta alocar a demanda que não era atendida antes
			TarefaAlocada = ProcessoParaAlocarTarefaNaoAtendida(0, ConstrucaoAnalisandoRetirada, NovaTarefaAlocadaConstrucao , NovaTarefaAlocadaDemanda,  DadosTarefasMovidas, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, Imprime);
			// calcula o nível de iniviabilidade da solução
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();
			// caso conseguir alocar a demanda que não era atendida antes
			if( TarefaAlocada == 1){
				if( Imprime == 1){
					cout << endl << endl << "         Aloca demanda não atendida anteriormente [ " << NovaTarefaAlocadaConstrucao << "-" << NovaTarefaAlocadaDemanda << "]" << endl << endl;
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
				ReadicionaTarefas(0, ConstrucaoAnalisandoRetirada,DadosTarefasMovidas, 1, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, Imprime);
				// calcula o nível de iniviabilidade da solução
				ConstrucoesInstancia.CalcularNivelDeInviabilidade();
				if( Imprime == 1){
					cout << endl << endl << "         Readicionou tarefas deletadas no inicio do procedimento " << endl << endl;
					if( ImprimeDadosTarefasArmazenados == 1){
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
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
						}
						ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}
					// deleta o armazenamento d etarefas adicionadas e deletadas, pois a solução que se encontrou é melhor uqe a solução anterior
					DadosTarefasMovidas.clear();

					if( ImprimeSolucao == 1){
						printf(  "  -> Nivel de inviabilidade = %d com a inserção da demanda [%d-%d] \n", ConstrucoesInstancia.NivelDeInviabilidade, NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);
					}
					if( ImprimeArquivo == 1){
						fprintf( Arquivo, "  -> Nivel de inviabilidade = %d com a inserção da demanda [%d-%d] \n", ConstrucoesInstancia.NivelDeInviabilidade, NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);
					}

					return 1;
				}else{
					if( Imprime == 1){
						cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;
						if( ImprimeDadosTarefasArmazenados == 1){
							cout << "DadosTarefasMovidas" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidas);
						}
						ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}
					// retorna a solução a  consição inicial
					if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia ) == 0){
						cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
					}
					// deleta o armazenamento de tarefas adicionadas e deletadas
					DadosTarefasMovidas.clear();
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
				}
			}else{
				// retorna a solução a  consição inicial
				if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia ) == 0){
					cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
				}
				// deleta o armazenamento d etarefas adicionadas e deletadas
				DadosTarefasMovidas.clear();
				// marca que a demanda corrente já foi retirada
				ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);
				if( Imprime == 1){
					cout << endl << endl << "            Nao consegui adicionar nova tarefa - readiciona tarefas e marca terafa como removida" << endl << endl;

					if( ImprimeDadosTarefasArmazenados == 1){
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
					}

					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
					//PlantasInstancia.Imprime(1,1);

					cin >> PararPrograma;
				}
			}
		}else{
			 cout << endl << endl << endl << "   #######################  Problema! => Tarefa não deletada -> Solucao::Viabilidade1  ######################## " << endl << endl << endl;
		}

		// Encontra proxima tarefa que pode ser retirada caso existir
		ExisteTarefa = ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 0);
	}
	return 0;
}

void Solucao::ProcessoViabilizacao1(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){

	// calcula o nível de iniviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();

	// escreve o nivel de inviabilidade antes de entrar no processo de viabilização
	if( ImprimeSolucao == 1){
		printf( "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}

	// Executa o processo de viabilização e escreve na tela caso melhorou a solução
	while( Viabilidade1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,Imprime, ImprimeSolucao, ImprimeArquivo, Arquivo) == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){

	}


}


// deleta a demanda passada na função e as demandas seguintes a está na construção, mas só armazena na estrutura a demanda passada na função
int Solucao::DeletaUltimaDemandaConstrucaoEmAnalise( int ConstrucaoNaoAtendida, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendidaInicio, vector < DadosTarefa > &DadosTarefasDemandasAnteriores){
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
int Solucao::SelecionaConstrucao( int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucoesAnalizadas){

	// passa por todas as construções
	for( int c = 0; c < NE; c++){
		// verifica se ela ainda tem demandas a serem atendidas
		if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
			// verifica se a construção ainda pode ser analisada
			if( ConstrucoesAnalizadas[c] == 0){
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
int  Solucao::ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida){

	// variaveis que armazenam os valores temporarios da construção, da demanda  e da distancia minima da construção a uma planta
	int ConstrucaoTemporario;
	int DemandaTemporaria;
	double DistanciaPlantaTemporaria;

	// inicia valores das variaveis cosntrução e demanda
	ConstrucaoTemporario = -13;
	DemandaTemporaria = -13;
	// inicia o valor da variavel com o maior valor para que qualquer valor de uma distancia de uma construção a uma planat sejáa ceito inicialmente
	DistanciaPlantaTemporaria = DBL_MAX;

	// percorre por todas as construções
	for ( int c = 0; c < NE; c++){
		// entra se a construção possa ser analisada ainda pelo procedimento
		if( ConstrucoesInstancia.ConstrucaoPodeSerSuprida[c] == 0){
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
}

// Aloca o tempo que se pode começar a carregar uma carreta da planta para suprir a construção passada
void Solucao::AlocaTempoPlantaPodeAtenderDemanda(int IndiceConstrucaoNaoAtendida, vector < double > &TempoPlantaConsegueAtender, int Imprime){

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
int Solucao::DeletaTarefasAposTempoPlantaPodeAtender(vector < double > &TempoPlantaPodeAtender, vector < DadosTarefa > &DadosTarefasMovidas,  int Imprime){

	int TarefaDeletada;
	int PlantaAux;
	int IndicePlantaAux;
	double DistanciaAux;
	int Ativa;

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
				// deleta a demanda corrente
				TarefaDeletada = ConstrucoesInstancia.Construcoes[c].DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados( 0                    , ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento, d,           ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada,                 PlantasInstancia,                        DadosTarefasMovidas);
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



int Solucao::Viabilidade2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){

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
	int DeletouAlgumaTarefa;
	int TarefaAdicionada;
	int PossuiConstrucaoParaAnalisar;

	// armazena as tarefas da solução que foram retiradas e adicionadas para permitir que se retorne ao estado inicial da solução depoois
	vector < DadosTarefa > DadosTarefasMovidasTentandoAlocar;
	// armazena as tarefas deletadas na construção corrente para depois se retornar ao estado original da construção
	vector < DadosTarefa > DadosTarefasDemandasAnteriores;


	// se deve realizar a verificação da viabilidade da solução corrente
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	// variavel que informa se ainda é possivel analizar a cosntrução corrente
	int PermiteAnalisarCosntrucao;

	int PararPrograma;

// ( AINDA NÂO IMPLEMENTADA) variavel que controla se deve realizar o processo de atraso de tarefas para tentar atrazar uma outra mais posterior que pode ser atendida caso se atraze as tarefas anteriores a ela
	int RealizaProcessoDeAtrazarTarefas;
	RealizaProcessoDeAtrazarTarefas = 1;

	// ordena as cosntruções na ordem em que elas devem ser escolhidas com prioridade
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	if( Imprime == 1){
		cout << endl << endl << "                        Situacao ao entra no Viabilidade2 " << endl << endl;
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
	}

// Encontra demanda ainda não atendida

	// Marca as construções que já foram completamente atenddidas com 1, as que não forma com 0
	ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();
	// calcula o nivel de inviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	// guarda o nivel de inviabilidade
	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	// Verifica se pode atender uma construção ainda, se tem uma com demanda não atendida
	while( ConstrucoesInstancia.VerificaConstrucaoPodeAtender() == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){
		// retorna a demanda e a construção que serão analisados inicialmente
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendidaFim);

		//cout << endl << endl << "           >>>>>>>>>> ENTRA da construção [" <<  ConstrucaoNaoAtendida << "] " << endl << endl;

		// faz a primeira demanda analisada na construção como sendo a mesma da ultima analisada
		DemandaNaoAtendidaInicio = DemandaNaoAtendidaFim;
		// inicia o tamanho do vetor de tempo do inicio das plantas com 0
		TempoPlantaPodeAtender.resize(NP);
		// retorna o incide da cosntrução que tem qeu ser analisada no momento
		ConstrucoesInstancia.RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );

		//cout << endl << endl << " ---- Demanda Nao Atendida = [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendidaFim << "] ---- "<< endl << endl;

		// faz a variavel sinalisar que ainda é possivel analisar a construção corrente
		PermiteAnalisarCosntrucao = 1;
		// limpa o vetor que armazena as demandas deletadas na construção para tentar alocar a demanda corrente
		DadosTarefasDemandasAnteriores.clear();
		// enquanto for possivel analisar a construção se continua no loop
		while( PermiteAnalisarCosntrucao == 1){

	// deleta tarefas que são atendidas antes desta tarefa não alocada
			// se limpa o vetor com as tarefas movidas durante o processo de se tentar atender a ultima demanda (DemandaNaoAtendidaFim)
			DadosTarefasMovidasTentandoAlocar.clear();
			// aloca no vetor TempoSaiPlanta os tempos que as plantas podem atender
			AlocaTempoPlantaPodeAtenderDemanda(IndiceConstrucaoNaoAtendida,TempoPlantaPodeAtender, Imprime);
			// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender
			DeletouAlgumaTarefa = DeletaTarefasAposTempoPlantaPodeAtender(TempoPlantaPodeAtender, DadosTarefasMovidasTentandoAlocar, Imprime);

			//cout << endl << endl << "      -))))))))))) tarefas deletadas " << endl;
			//ImprimeVetorDadosTarefa(DadosTarefasMovidasTentandoAlocar);

	// tenta adiciona a tarefa que não era alocada antes
			for( int d1 = DemandaNaoAtendidaInicio; d1 <= DemandaNaoAtendidaFim; d1++){
				// tenta adicionar a demanda não atendida anteriormente. Caso consegui retorna 1, caso contrario retorna 0.
				TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefa(0, ConstrucaoNaoAtendida, d1, DadosTarefasMovidasTentandoAlocar, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, Imprime, " adiciona tarefa não adicionada -> Solucao::ProcessoViabilizacao2 ");

				//cout << endl << endl << " 				+ (" << TarefaAdicionada << ") Adiciona  [" << ConstrucaoNaoAtendida << "-" << d1 << "] "<< endl << endl;

			}
			// Verifa se conseguiu alocar a demanda não alocada antes.
			if( TarefaAdicionada == 0){
				// se retorna a situação inical antes de se deletar as demandas da
				if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasTentandoAlocar, PlantasInstancia ) == 0){
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
			// caso se conseguiu colocar todas as demandas na construção corrente que se queria ( a demanda DemandaNaoAtendidaInicio até a DemandaNaoAtendidaFim)
			}else{
				// marca todas as construções como possiveis a alocar demandas, todas com 0 em ConstrucoesAnalisadas ( IMPORTANTE!!!!!!!!! Construções analizadas é diferente que ConstrucaoPodeSerSuprida. Elas desempenham funçẽos diferentes apesar de parecerem iguais)
				ConstrucoesInstancia.InicializaConstrucoesAnalizadas();
				// marca as construções com todas suas demandas atendidas com 2, e a construção que tinha uma demanda sem atender e que agora foi atendida com 3
				ConstrucoesInstancia.AlocaValoresConstrucoesAnalizadas( IndiceConstrucaoNaoAtendida);

	// Verifica se tem tarefa a se colocar
				// escolhe a construção com o menor indice e que pode ser atendida ( todas as construções com 0 em CosntruçõesAnalisadas, estas são as que não tem suas demandas todas atendidas e que não sejá a que passou a ter uma demanda que não era atendida antes e agora é atendida)
				PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, IndiceConstrucaoParaAtender, ConstrucoesInstancia.ConstrucoesAnalizadas);

				//cout << endl << "  Readiciona as ";

				// caso se tenha uma construção que ainda se pode alocar demandas
				while( PossuiConstrucaoParaAnalisar == 1){

					//cout << " const [" << ConstrucaoParaAtender << "] ";

					// coloca a demanda que se tem que alocar no momento
					d2 = ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].StatusAtendimento;
			// tenta adicionar a demanda corrente
					// faz que ainda é possivel se adicionar uma demanda na cosntrução corrente
					TarefaAdicionada = 1;
					// enquanto for possivel adicionar uma demanda na construção corrente e que a cosntrução ainda não tenha todas as suas demandas supridas, se mantem no loop
					while( d2 < ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].NumeroDemandas && TarefaAdicionada == 1){
						// tenta adicionar a demanda corrente (d2) a cosntrução
						TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefa( 0, ConstrucaoParaAtender, d2, DadosTarefasMovidasTentandoAlocar, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo, EscolhaPlanta, PlantasInstancia, Imprime , " Readicionando -> Solucao::ProcessoViabilizacao2 ");
						// passa para a proxima demnada que se pode adicionar na construção
						d2++;
					}
					// caso se atendeu a todas as demandas da construção corrrente se entra no if
					if( TarefaAdicionada == 1){
						// caso todas as demandas da construção corrente tenham sido supridas, se entra no if
						if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].StatusAtendimento == ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].NumeroDemandas){
							// marca a construção como já atendida todas as suas demandas
							ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoParaAtender] = 1;
						}else{
							cout << endl << endl << "                  Não deveria ter entrado! Merda! " << endl << endl;
						}
					// caso não se atendeu a todas as demandas da construção corrrente se entra no else
					}else{
						// marca a construção como sendo que não se consegue atender suas demandas
						ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoParaAtender] = -1;
					}
					// se passa para a proxima construção que se pode atender
					PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, IndiceConstrucaoParaAtender, ConstrucoesInstancia.ConstrucoesAnalizadas);
				}

				//cout << endl;

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
					DadosTarefasMovidasTentandoAlocar.clear();
					DadosTarefasDemandasAnteriores.clear();
					// retorna 1, sinalizando que se melhorou a solução
					return 1;
				}else{
					// se escreve que não melhorou a solução
					if( Imprime == 1){
						cout << endl << endl << "    Não melhorou !!!!!!" << endl << endl;
					}
					//cout << endl << endl << "    Não melhorou !!!!!!" << endl << endl;

					// retorna a solução a  consição inicial
					if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasTentandoAlocar, PlantasInstancia ) == 0){
						cout << endl << endl << "   problema em adicionar e deletar tarefas DadosTarefasMovidasTentandoAlocar ->  Solucao::ProcessoViabilizacao2" << endl << endl;
					}

					//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0,1,0,Arquivo);
					//cin >> PararPrograma;

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
		}

		//cout << endl << endl << "           >>>>>>>>>> sai da construção [" <<  ConstrucaoNaoAtendida << "] " << endl << endl;
		//cin >> PararPrograma;

		// se readiciona as demandas deletadas na cosntrução com a finalidade que se readicionassem elas se poderia conseguir atender a demanda que se queria adicionar na solução
		if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasDemandasAnteriores, PlantasInstancia ) == 0){
			// probelam em readicionar as demandas
			cout << endl << endl << "   problema em adicionar e deletar tarefas DadosTarefasDemandasAnteriores ->  Solucao::ProcessoViabilizacao2" << endl << endl;
		}
		// não consegui atender a demanda da cosntrução, marco ela com 4
		ConstrucoesInstancia.ConstrucaoPodeSerSuprida[IndiceConstrucaoNaoAtendida] = 4;
	}
	//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0,1,0,Arquivo);
	return 0;
}

void Solucao::ProcessoViabilizacao2(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int Imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	//int PararPrograma;

	// calcula o nível de iniviabilidade da solução
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	// escreve o nivel de inviabilidade antes de entrar no processo de viabilização
	if( ImprimeSolucao == 1){
		printf( "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "   nivel de inviabilidade inicial = %d \n", ConstrucoesInstancia.NivelDeInviabilidade);
	}

	// Executa o processo de viabilização e escreve na tela caso melhorou a solução
	while( Viabilidade2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,Imprime, ImprimeSolucao, ImprimeArquivo, Arquivo) == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){
		//cout << endl << endl << endl << " Melhorou solução " << endl << endl << endl;
		//cin >> PararPrograma;
	}

}

// calcula o makespan geral da solução
void Solucao::CalculaMakespan(){
	 // caculo o makespan geral da solução
	Makespan = PlantasInstancia.MakespanPLantas + ConstrucoesInstancia.MakespanConstrucoes;
}

void Solucao::RealizarBuscaLocalCaminhao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
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
	while ( busca.BuscaLocalTentaRealizarTarefasComOutosVeiculos(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeProcedimento, ImprimeEstruturas) == 1){
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

void Solucao::RealizarBuscaLocalConstrucao(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
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
	while ( busca.BuscaLocalMudaOrdemAtendiemntoConstrucoes(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeProcedimento, ImprimeEstruturas) == 1){
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


void Solucao::RealizarBuscaLocalPlanta(int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
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
	while ( busca.BuscaLocalTrocaPlantaAtendimento(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeProcedimento, ImprimeEstruturas) == 1){
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
	void InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);			// carrega uma solução ao vetor das soluções
	void CalculaMakespanSolucoes();		// calcula o makespan das soluções
	void Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade, int ImprimeSolucao , int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// imprime as soluções
	~ConjuntoSolucoes();

};

// classe construtoora
ConjuntoSolucoes::ConjuntoSolucoes(){
}

// carrega uma solução ao vetor das soluções
void ConjuntoSolucoes::InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	Solucao S1;
	// carrega dasos da solução
	S1.CarregaSolucao( np, Plantas, ne, Construcoes, nv, v, TDVC);
	// colocar a solução carregada nbo vetor de soluções
	Solucoes.push_back(S1);
}

// calcula o makespan das soluções
void ConjuntoSolucoes::CalculaMakespanSolucoes(){
	// percorre por todas as soluções
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		// calcula o makespan da solução corrente de suas construções
		Solucoes[s].ConstrucoesInstancia.CalculaMakespansConstrucoes();
		// calcula o makespan da solução corrente de suas plantas
		Solucoes[s].PlantasInstancia.CalculaMakespanPlantas();
		// calcula o makespan da solução
		Solucoes[s].Makespan = Solucoes[s].ConstrucoesInstancia.MakespanConstrucoes + Solucoes[s].PlantasInstancia.MakespanPLantas;
	}
}

// imprime as soluções
void ConjuntoSolucoes::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool VerificaViabilidade, int ImprimeSolucao ,int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// percorre por todas as soluções
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
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
