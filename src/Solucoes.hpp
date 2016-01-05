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

	int ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia,  int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao, int imprime);				// Tenta alocar uma demanda que não era alocada anteriormente
	void ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao, int imprime);						// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
	void ProcessoViabilizacao1(int TipoOrdenacao,int Imprime);

	int SelecionaConstrucao(int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucoesAnalizadas);	// seleciona a construção a ser analisada no momento
	int  ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida);																	// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas
	void AlocaTempoPlantaPodeAtenderDemanda(int IndiceConstrucaoNaoAtendida, vector < double > &TempoPlantaConsegueAtender, int Imprime);					// Aloca o tempo inicial que se pode sair uma carreta da planta para suprir a construção passada

	int DeletaTarefasAposTempoPlantaPodeAtender(vector < double > &TempoPlantaPodeAtender, vector < DadosTarefa > &DadosTarefasMovidas,  int Imprime );		// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender
	void SinalizaTarefaAdicionadaInicialmente( int TarefaAdicionada, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendida);					// Sinalisa se a tarefa foi antendida colocando os valores 2 em sua situação remoção. Caso não, está demanda e suas posteriores na emsma construção recebem o valor -1 na situação demanda e 3 na situção remoção.
	void ProcessoViabilizacao2(int TipoOrdenacao, int Imprime);

	void RealizarBuscaLocalCaminhao(int imprime);
	void RealizarBuscaLocalConstrucao(int imprime);
	void RealizarBuscaLocalPlanta(int imprime);

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
int Solucao::ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia, int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao, int imprime){
	// indice da construção
	int c;

	// variavel que guarda a situação da demanda corrente. se ela foi alocada ou não
	int Alocou;
	Alocou = 0;

	// verifica se a construção passada existe na instancia
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, "  <<<<    Solucao::ProcessoParaAlocarTarefaNaoAtendida  >>>>>") == 0){
		return -1;
	}

	// percorre todas as construções
	for(  int contrucoes = 0; contrucoes < (int) ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		// percorre todas as demandas da construção corrente
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas; demandas++){
			// não tenta aloca demandas da construçãoq ue teve uma demanda retirada anteriormente
			if( contrucoes != c){
				// verifica se a demnada corrente ainda não foi alocada
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					//cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "]  -> Solucao::ProcessoParaAlocarTarefa";

					// tenta alocar a demanda
					Alocou = ConstrucoesInstancia.AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, SituacaoRetirada, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, PlantasInstancia, imprime, "Solucao::ProcessoParaAlocarTarefaNaoAtendida");
					//caso alocar a demanda
					if( Alocou == 1){
						//cout << " => Alocou [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ProcessoParaAlocarTarefa" << endl;

						// retorna a cosntruçãoq ue teve uma demanda alocada
						NovaTarefaAlocadaConstrucao = ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao;
						// retorna a demanda adicionada
						NovaTarefaAlocadaDemanda = demandas;
						// sai da função e avisa que consegui alocar uma demanda
						return 1;
					}else{
						//cout << " => Falhou! " << endl;
					}
				}
			}
		}
	}
	// não conseguir alocar a demanda da função, retorna 0
	return 0;
}

// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
void Solucao::ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao, int imprime){
	int c;

	// verifica se existe a construção passada
	if( ConstrucoesInstancia.RetornaIndiceConstrucao( construcao, c, " <<<<<<<<<<<<<<<<<<<<<<< Solucao::ReadicionaTarefas >>>>>>>>>>>>>>>>>>>>") == 1 ){
		// percorre as demanda da cosntrução
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
			// caso a demanda corrente não tenha sido atendida
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
				//cout << " entrei " << endl;

				// readiciona a demanda corrente na construção
				if( ConstrucoesInstancia.AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, PlantasInstancia, imprime, "Solucao::ReadicionaTarefas") == 1 ){
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


void Solucao::ProcessoViabilizacao1(int TipoOrdenacao,int Imprime){

	// ponteiro para o arquivo que se irá salvar os dados
		PonteiroArquivo  Arquivo;
		// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
		int ImprimeArquivo;
		ImprimeArquivo = 0;

		int ImprimeSolucao;
		ImprimeSolucao = 1;

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

	int PararPrograma;

// armazena as tarefas da solução que foram retiradas e adicionadas para permitir que se retorne ao estado inicial da solução depoois
	vector < DadosTarefa > DadosTarefasMovidas;

// ( AINDA NÂO IMPLEMENTADA) variavel que controla se deve realizar o processo de atraso de tarefas para tentar atrazar uma outra mais posterior que pode ser atendida caso se atraze as tarefas anteriores a ela
	int RealizaProcessoDeAtrazarTarefas;

	RealizaProcessoDeAtrazarTarefas = 1;

	//se deve realizar a verificação da viabilidade da solução corrente
	int VerificaViabilidade;
	VerificaViabilidade = 0;


	// guarda o nivel de inviabilidade da solução anterior para ser utilizado posteriormente para ver se a solução melhorou
	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	// Encontra primeira tarefa que pode ser retirada
	ExisteTarefa = ConstrucoesInstancia.ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, Imprime);
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
			cout << endl << endl << "    deleta tarefas apos a demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;
			cout << "DadosTarefasMovidas" << endl;
			ImprimeVetorDadosTarefa( DadosTarefasMovidas);
			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
			//PlantasInstancia.Imprime(1,1);
			cin >> PararPrograma;
		}
		// caso conseguiu deletar a demanda e suas posteriores entra no if
		if ( TarefaDeletada == 1){
			// Aloca valores aos inidices da construção e da demanda que não era atendida antes  equa passara a ser atendia
			AlocaValoresIniciaisIndices( NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);
			// tenta alocar a demanda que não era atendida antes
			TarefaAlocada = ProcessoParaAlocarTarefaNaoAtendida(0, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovaTarefaAlocadaConstrucao , NovaTarefaAlocadaDemanda,  DadosTarefasMovidas, 1, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, Imprime);
			// calcula o nível de iniviabilidade da solução
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();
			// caso conseguir alocar a demanda que não era atendida antes
			if( TarefaAlocada == 1){
				if( Imprime == 1){
					cout << endl << endl << "         Aloca demanda não atendida anteriormente [ " << NovaTarefaAlocadaConstrucao << "-" << NovaTarefaAlocadaDemanda << "]" << endl << endl;
					cout << endl << "  tenta alocar tarefa" << endl;
					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
					//PlantasInstancia.Imprime(1,1);
					cin >> PararPrograma;
				}
				// tento readicionar as demandas que foram retiradas
				ReadicionaTarefas(0, ConstrucaoAnalisandoRetirada,DadosTarefasMovidas, 1, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, Imprime);
				// calcula o nível de iniviabilidade da solução
				ConstrucoesInstancia.CalcularNivelDeInviabilidade();
				if( Imprime == 1){
					cout << endl << endl << "         Readicionou tarefas deletadas no inicio do procedimento " << endl << endl;
					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
					//PlantasInstancia.Imprime(1,1);
					cin >> PararPrograma;
				}
				// verifica se melhorou a solução
				if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
					if( Imprime == 1){
						cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
						ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}
					// marca a demanda retirada
					ConstrucoesInstancia.MarcaTarefaNaoRemovidaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, "ProcessoViabilizacao1" );
					// deleta o armazenamento d etarefas adicionadas e deletadas, pois a solução que se encontrou é melhor uqe a solução anterior
					DadosTarefasMovidas.clear();
				}else{
					if( Imprime == 1){
						cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
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

						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
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

					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);

					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
					//PlantasInstancia.Imprime(1,1);

					cin >> PararPrograma;
				}
			}
		}else{
			 cout << endl << endl << endl << "   #######################  Tarefa não deletada ######################## " << endl << endl << endl;
		}
		// guarda o nivel de inviabilidade da solução anterior para ser utilizado posteriormente para ver se a solução melhorou
		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
		// Encontra proxima tarefa que pode ser retirada caso existir
		ExisteTarefa = ConstrucoesInstancia.ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 0);
	}

}


// seleciona a construção a ser analisada no momento
int Solucao::SelecionaConstrucao( int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucoesAnalizadas){
	double RankInicial;
	int Ativo;

	// inicia variaveis
	Ativo = 0;
	RankInicial = DBL_MAX;

	// passa por todas as construções
	for( int c = 0; c < NE; c++){
		// seleciona a que tem um rank maior que a selecionada no momento
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			// verifica se ela ainda tem demandas a serem atendidas
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
				// verifica se a construção ainda pode ser analisada
				if( ConstrucoesAnalizadas[c] == 0){
					// armazena os dados da cosntrução corrente
					ConstrucaoParaAtender = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					ConstrucaoParaAtenderIndice = c;
					RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
					// marca que encontrou uma construção
					Ativo = 1;
				}
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

// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas
int  Solucao::ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida){

	int ConstrucaoTemporario;
	int DemandaTemporaria;
	double DistanciaPlantaTemporaria;

	// inicia valores das variaveis
	ConstrucaoTemporario = -13;
	DemandaTemporaria = -13;
	DistanciaPlantaTemporaria = DBL_MAX;

	// percorre por todas as construções
	for ( int i = 0; i < NE; i++){
		// percorre por todas as demandas iniciando da maior para a menor, isso tem o intuito de pegar a demanda não atendida logo após a ultima que foi atendida
		for ( int d = ConstrucoesInstancia.Construcoes[i].NumeroDemandas - 1; d >= 0  ; d--){
			// verifioca se a demanda corrente não foi atendida
			if( ConstrucoesInstancia.Construcoes[i].SituacaoDemanda[d] == 0){
				// percorre todas as plantas para pegar a demanda não atendida que esteja mais perto de uma planta
				for ( int p = 0; p < NP; p++){
					// caso a distancia da planta a demanda corrente for menor que a distancia corrente, se entra no if
					if( DistanciaPlantaTemporaria >= ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[p].Distancia){
						// atualiza as variaveis com a demanda corrente
						DistanciaPlantaTemporaria = ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[p].Distancia;
						ConstrucaoTemporario = ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao;
						DemandaTemporaria = d;
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
	// retorna a demanda que não é atendida e que esta mais perto de uma planat
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

// Sinalisa se a tarefa foi antendida colocando os valores 2 em sua situação remoção. Caso não, está demanda e suas posteriores na emsma construção recebem o valor -1 na situação demanda e 3 na situção remoção.
void Solucao::SinalizaTarefaAdicionadaInicialmente( int TarefaAdicionada, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendida){
	// caso a tarefa foi adicionada entra no if
	if( TarefaAdicionada == 1){
			//cout << "                  Tarefa adicionada    -> Solucao::SinalizaTarefaAdicionadaInicialmente" << endl << endl;

			// coloca o valor 2 em sua situação demanda e situação remoção
			ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] = 2;
			ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoRemocao[ DemandaNaoAtendida ] = 2;
		}else{
			//cout << "                  Tarefa NAO adicionada " << endl << endl;

			// marca a demanda que não pode ser atendida, e as demanda que vem depois dela, com -1 na sua situação e 3 na sua situação remoção
			for( int d = DemandaNaoAtendida; d < ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDemandas; d++){
				// marca com -1, já tento alocar mas não conseguiu
				ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ d ] = -1;
				// marca com 3 a situação remoção
				ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoRemocao[ d ] = 3;
			}
		}
}


void Solucao::ProcessoViabilizacao2(int TipoOrdenacao, int Imprime){
	// ponteiro para o arquivo que se irá salvar os dados
			PonteiroArquivo  Arquivo;
			// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
			int ImprimeArquivo;
			ImprimeArquivo = 0;

			int ImprimeSolucao;
			ImprimeSolucao = 1;

			// armazena o nivel de inviabilidade anterior
	int InviabilidadeSolucaoAnterior;
	// dados da demanda não atendida
	int	ConstrucaoNaoAtendida;
	int IndiceConstrucaoNaoAtendida;
	int DemandaNaoAtendida;
	// dados da construção que será atendida
	int ConstrucaoParaAtender;
	int IndiceConstrucaoParaAtender;
	// indice da demanda da construção que será atendida
	int d;

	// dados das plantas que podem atender a demanda em questão
	vector< int > PlantasPodemAtenderTarefa;
	vector < double > TempoPlantaPodeAtender;

	// variaveis de controle
	int DeletouAlgumaTarefa;
	int TarefaAdicionada;
	int PossuiConstrucaoParaAnalisar;

	// armazena as tarefas da solução que foram retiradas e adicionadas para permitir que se retorne ao estado inicial da solução depoois
	vector < DadosTarefa > DadosTarefasMovidas;

	// se deve realizar a verificação da viabilidade da solução corrente
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	int PararPrograma;

// ( AINDA NÂO IMPLEMENTADA) variavel que controla se deve realizar o processo de atraso de tarefas para tentar atrazar uma outra mais posterior que pode ser atendida caso se atraze as tarefas anteriores a ela
	int RealizaProcessoDeAtrazarTarefas;

	RealizaProcessoDeAtrazarTarefas = 0;

	if( Imprime == 1){
		cout << endl << endl << "                        Situacao ao entra no Viabilidade2 " << endl << endl;
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
	}

// Encontra demanda ainda não atendida

	// Marca as construções que já foram completamente atenddidas com 1, as que não forma com 0
	ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();
	// Verifica se pode atender uma construção ainda, se tem uma com demanda não atendida
	while( ConstrucoesInstancia.VerificaConstrucaoPodeAtender() == 1){
		// guarda o nivel de inviabilidade
		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
		// reinicia o estado de deslocamento e remoção de todas as demandas de todas as construções
		ConstrucoesInstancia.ReiniciaTarefasRetiradas();
		// retorna a demanda e a construção que serão analisados inicialmente
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);
		// inicia o tamanho do vetor de tempo do inicio das plantas com 0
		TempoPlantaPodeAtender.resize(NP);
		if( Imprime == 1){
			cout << endl << endl << " ---- Demanda Nao Atendida = [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] ---- "<< endl << endl;
		}
		// retorna o incide da cosntrução que tem qeu ser analisada no momento
		ConstrucoesInstancia.RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );

// deleta tarefas que são atendidas antes desta tarefa não alocada

		// aloca no vetor TempoSaiPlanta os tempos que as plantas podem atender
		AlocaTempoPlantaPodeAtenderDemanda(IndiceConstrucaoNaoAtendida,TempoPlantaPodeAtender, Imprime);
		// deleta todas as tarefas que são atendidas após os horarios armazenados da TempoPlantaPodeAtender
		DeletouAlgumaTarefa = DeletaTarefasAposTempoPlantaPodeAtender(TempoPlantaPodeAtender, DadosTarefasMovidas,  Imprime );
		if( Imprime == 1){
			cout << "          <<<<<<<<<<< Detetou tarefas => " << DeletouAlgumaTarefa << " >>>>>>>>>>>>>> ";
			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
			cin >> PararPrograma;
		}

// Adiciona a tarefa que não era alocada antes
		// tenta adicionar a demanda não atendida anteriormente. Caso consegui retorna 1, caso contrario retorna 0.
		TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefa(0, ConstrucaoNaoAtendida, DemandaNaoAtendida, DadosTarefasMovidas, 2, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, PlantasInstancia, Imprime, " adiciona tarefa não adicionada -> Solucao::ProcessoViabilizacao2 ");
		// atualiza os valores de situação e remoção da demanda. caso for atendida coloca 2 em ambos, caso não, a situação tem valor -1 e a remoção 3
		SinalizaTarefaAdicionadaInicialmente( TarefaAdicionada, IndiceConstrucaoNaoAtendida, DemandaNaoAtendida);
		if( Imprime == 1){
			cout << "   							<<<<<<<<<<< Tenta alocar tarefa [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] >>>>>>>>>>>>>> ";
			//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0);
			cin >> PararPrograma;
		}
		// Verifa se conseguiu alocar a demnada não alocada antes.
		if( ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] == -1){
			// Caos não aloque a demanda
			if( Imprime == 1){
				cout << endl << endl << "   Não consigo alocar tarefa [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] que não foi alocada antes -> Solucao::ProcessoViabilizacao2 " << endl << endl;
			}
			// retorna a solução a  consição inicial
			if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia ) == 0){
				cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
			}
			// deleta o armazenamento de tarefas adicionadas e deletadas
			DadosTarefasMovidas.clear();
			// marca cosntrução como já analisada e que não se consegue alocar a demanda utilizando esse procedimento já no inicio após deletar todas as tarefas. Ou seja, não se consegue alocar essa tarefa usando as plantas que se tem.
			ConstrucoesInstancia.ConstrucaoPodeSerSuprida[IndiceConstrucaoNaoAtendida] = 4;
		}else{
			if( Imprime == 1){
				cout << "   						<<<<<<<<<<< Coloca tarefa não alocada anterioremnte [" <<  ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "]  >>>>>>>>>>>>>>> ";
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
				ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1, DadosTarefasMovidas, 1, ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cin >> PararPrograma;
			}
// marca construções com tarefas a alocar

			// marca todas as construções como possiveis a alocar demandas, todas com 0 em ConstrucoesAnalisadas ( IMPORTANTE!!!!!!!!! Construções analizadas é diferente que ConstrucaoPodeSerSuprida. Elas desempenham funçẽos diferentes apesar de parecerem iguais)
			ConstrucoesInstancia.InicializaConstrucoesAnalizadas();
			// marca as construções com todas suas demandas atendidas com 2, e a construção que tinha uma demanda sem atender e que agora foi atendida com 3
			ConstrucoesInstancia.AlocaValoresConstrucoesAnalizadas( IndiceConstrucaoNaoAtendida);

// Verifica se tem tarefa a se colocar
			// escolhe a construção com o menor indice e que pode ser atendida ( todas as construções com 0 em CosntruçõesAnalisadas, estas são as que não tem suas demandas todas atendidas e que não sejá a que passou a ter uma demanda que não era atendida antes e agora é atendida)
			PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, IndiceConstrucaoParaAtender, ConstrucoesInstancia.ConstrucoesAnalizadas);
			if( Imprime == 1){
				cout << "   <<<<<<<<<<< Inicia Processo Readiciona Demandas   >>>>>>>>>>>>>>> " << endl;
				ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0, DadosTarefasMovidas, 1, ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cin >> PararPrograma;
			}
			// caso se tenha uma construção que ainda se pode alocar demandas
			while( PossuiConstrucaoParaAnalisar == 1){
				// coloca a demanda que se tem que alocar no momento
				d = ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].StatusAtendimento;
				if( Imprime == 1){
					cout << " tenta alocar Demanda [" << ConstrucaoParaAtender << "-" << d << "]"<< endl;
				}
				// tenta adicionar a demanda corrente
				TarefaAdicionada = ConstrucoesInstancia.AdicionaTarefa( 0, ConstrucaoParaAtender, d, DadosTarefasMovidas, 1, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, PlantasInstancia, Imprime , " Readicionando -> Solucao::ProcessoViabilizacao2 ");
				// caso se atendeu a demanda, entra no if
				if( TarefaAdicionada == 1){
					if( Imprime == 1){
						cout  << endl << "  +++++++ Alocou demanda [" << ConstrucaoParaAtender << "-" << d << "]";
					}
					// caso todas as demandas da construção corrente tenham sido supridas, se entra no if
					if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].StatusAtendimento == ConstrucoesInstancia.Construcoes[IndiceConstrucaoParaAtender].NumeroDaConstrucao){
						// marca a construção como já atendida todas as suas demandas
						ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoParaAtender] = 1;
						if( Imprime == 1){
							cout << endl << endl << "        Construção [" << ConstrucaoParaAtender << "] com demandas atendidas";
						}
					}
				}else{
					// caso não tenha atendida a demanda corrente
					if( TarefaAdicionada == 0){
						// marca a construção como sendo que não se consegue atender suas demandas
						ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoParaAtender] = -1;
						if( Imprime == 1){
							cout << endl << endl << "        Construção [" << ConstrucaoParaAtender << "] Não da para atender demandas";
						}
					}
				}
				if( Imprime == 1){
					cout << endl << endl << "Vetor Construções analizadas" << endl;
					ImprimeVetorInt( ConstrucoesInstancia.ConstrucoesAnalizadas );
					cin >> PararPrograma;
				}
				// se passa para a proxima construção que se pode atender
				PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, IndiceConstrucaoParaAtender, ConstrucoesInstancia.ConstrucoesAnalizadas);

			}
			// calcula o nivel de inviabilidade que ira mostrar se a soluçpão melhorou ou não
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();
			if( Imprime == 1){
				cout << endl << endl << "   <<<<<<<<<<< Finaliza Processo Readiciona Demandas   >>>>>>>>>>>>>>> " << endl << endl;
				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
				cin >> PararPrograma;
				//PlantasInstancia.Imprime(1,1);
			}
			// verifica se a solução melhorou
			if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
				if( Imprime == 1){
					cout << endl << endl << "    Melhorou !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
				}
				// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
				DadosTarefasMovidas.clear();
				// atualiza a situação da construçãoq ue teve todas as suas demandas atendidas
				ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();
			}else{
				if( Imprime == 1){
					cout << endl << endl << "    Não melhorou !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);
					cin >> PararPrograma;
				}
				// retorna a solução a  consição inicial
				if(ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas, PlantasInstancia ) == 0){
					cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
				}
				// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
				DadosTarefasMovidas.clear();
				// atualiza a situação da construçãoq ue teve todas as suas demandas atendidas
				ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();
				// Marca a construção qeu logo após deletar as tarefas, adicionar a demanda não alocada dela e depois readicionar as demandas deletadas antes, não se chegou em um sequenciamento melhor.
				ConstrucoesInstancia.ConstrucaoPodeSerSuprida[IndiceConstrucaoNaoAtendida] = 3;
			}
			//cin >> PararPrograma;
		}
	}
}


void Solucao::RealizarBuscaLocalCaminhao(int imprime){
	// calsse da busca local
	BuscaLocal busca;

	// variaveis d econtrole do processo, para contar o numero de iterações e para parar o programa
	int NumeroDeVezes;
	int ParaPrograma;
	int ImprimeEstruturas;

	// inicializa o numero de iterações como zero
	NumeroDeVezes = 0;
	ImprimeEstruturas = 0;

	// carrega os dados da solução para a classe da busca local
	busca.CarregaSolucao( NP, PlantasInstancia, NE,	ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	// equanto o procediemnto da busca local melhorar a solução que se tem, se continua no while
	while ( busca.BuscaLocalTentaRealizarTarefasComOutosVeiculos(imprime, ImprimeEstruturas) == 1){
		// carrega a nova solução que se obteve
		CarregaSolucao(busca.NP, busca.PlantasInstancia, busca.NE, busca.ConstrucoesInstancia, busca.NV , busca.Velocidade , busca.TempoDeVidaConcreto);
		// aumenta o numero de iterações em 1
		NumeroDeVezes++;

		if( imprime == 1){
			cout << " iteração " << NumeroDeVezes << endl;
			cin >> ParaPrograma;
		}

	}
}

void Solucao::RealizarBuscaLocalConstrucao(int imprime){
	// calsse da busca local
	BuscaLocal busca;

	// variaveis d econtrole do processo, para contar o numero de iterações e para parar o programa
	int NumeroDeVezes;
	int ParaPrograma;
	int ImprimeEstruturas;

	// inicializa o numero de iterações como zero
	NumeroDeVezes = 0;
	ImprimeEstruturas = 0;

	// carrega os dados da solução para a classe da busca local
	busca.CarregaSolucao( NP, PlantasInstancia, NE,	ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	// equanto o procediemnto da busca local melhorar a solução que se tem, se continua no while
	while ( busca.BuscaLocalMudaOrdemAtendiemntoConstrucoes(imprime, ImprimeEstruturas) == 1){
		// carrega a nova solução que se obteve
		CarregaSolucao(busca.NP, busca.PlantasInstancia, busca.NE, busca.ConstrucoesInstancia, busca.NV , busca.Velocidade , busca.TempoDeVidaConcreto);
		// aumenta o numero de iterações em 1
		NumeroDeVezes++;

		if( imprime == 1){
			cout << " iteração " << NumeroDeVezes << endl;
			cin >> ParaPrograma;
		}

	}
}


void Solucao::RealizarBuscaLocalPlanta(int imprime){
	// calsse da busca local
	BuscaLocal busca;

	// variaveis d econtrole do processo, para contar o numero de iterações e para parar o programa
	int NumeroDeVezes;
	int ParaPrograma;
	int ImprimeEstruturas;

	// inicializa o numero de iterações como zero
	NumeroDeVezes = 0;
	ImprimeEstruturas = 0;

	// carrega os dados da solução para a classe da busca local
	busca.CarregaSolucao( NP, PlantasInstancia, NE,	ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	// equanto o procediemnto da busca local melhorar a solução que se tem, se continua no while
	while ( busca.BuscaLocalTrocaPlantaAtendimento(imprime, ImprimeEstruturas) == 1){
		// carrega a nova solução que se obteve
		CarregaSolucao(busca.NP, busca.PlantasInstancia, busca.NE, busca.ConstrucoesInstancia, busca.NV , busca.Velocidade , busca.TempoDeVidaConcreto);
		// aumenta o numero de iterações em 1
		NumeroDeVezes++;

		if( imprime == 1){
			cout << " iteração " << NumeroDeVezes << endl;
			cin >> ParaPrograma;
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
