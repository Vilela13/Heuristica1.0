/*
 * Solucoes.hpp
 *
 *  Created on: Sep 11, 2015
 *      Author: mateus.vilela
 */

#ifndef SOLUCOES_HPP_
#define SOLUCOES_HPP_

#include "Bibliotecas.hpp"
#include "DadosTarefa.hpp"
#include "FuncoesSolucoes.hpp"

class Solucao{
public:
	Solucao();

// estruturas que armazenam os dados da instancia
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	double Makespan;

	void CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);
	void EncontraPlantaMenorDistanciaConstrucao(int c, int& NumPlantaAnalisando, string frase);

	void Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes);

	int DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas);
	int AdicionaTarefa(int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao );

	int ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia,  int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao);
	void ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao);

	int ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas);		// readiciona tarefas deletadas e deleta tarefas adicionadas visando restaurar a configuração inicial da solução

	void ProcessoViabilizacao1(int );


	// M###################################################################################################
/*
	int SelecionaConstrucao(int&, int&, vector < int >);
	int SelecionaPlanta(int&, int&, int, vector < int >);

	int  ProcuraConstrucaoNaoAtendida(int&, int&);
	void AlocaTempoSaiDaPlanta(int , vector < double >&, int);
	int DeletaTarefasAposTempoSaiPlanta(vector < double >&, vector < DadosTarefa >&,  int );

	void SinalizaTarefaAdicionadaInicialmente( int, int, int);
	int SelecionaCarreta(int, int, int, int, vector < DadosTarefa >&, int);
	int SelecionaCarretaComHoraInicio(double, int, int, int, int, vector < DadosTarefa > &, int);

	int ColocarTarefaAtrazandoAsOutras(int , int , double, vector < DadosTarefa > &, int, int);

	void ProcessoViabilizacao2(int);
*/

	~Solucao();
};

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

// encontra a planta mais perto da construção que ainda não foi analisada
void Solucao::EncontraPlantaMenorDistanciaConstrucao( int c, int& NumPlantaAnalisando, string frase){
	double DistanciaConstrucaoPlanta;

	NumPlantaAnalisando = -13;
	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
			// planta que ainda não foi analisada
			if( PlantasInstancia.PlantasAnalizadas[p] == 0){
				NumPlantaAnalisando = p;
				DistanciaConstrucaoPlanta = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
			}
		}
	}
	if(NumPlantaAnalisando == -13){
		cout << endl << endl << endl << frase << endl << endl << endl;
	}
}



void Solucao::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes ){
	if( ImprimePlanta == 1 ){
		PlantasInstancia.Imprime(1,1);
	}
	if( ImprimeConstrucao == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
	}
	if( IntervalosRespeitadosConstrucaoes == 1){
		ConstrucoesInstancia.VerificaIntervaloContrucoes();
	}

}



int Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas){
		 int c;

		 if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, " -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao" ) == 1){
			 if( ConstrucoesInstancia.Construcoes[c].DeletaTarefas( VerificaExistencia, Demanda, DadosTarefasMovidas, PlantasInstancia) == 0 ){
				 cout << endl << endl << "   problema em retirar tarefas -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao " << endl << endl;
				 return 0;
			 }

			 //cout << endl << endl;
			 //ConstrucoesInstancia.Construcoes[c].ImprimeContrucao();

			 return 1;
		 }
		 return 0;

}


int Solucao::AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao ){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	int c;
	int NumPlantaAnalisando;

	PlantasInstancia.InicializaVetorHorarioQuePlantaPodeAtender();

	int ParaPrograma;

	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;
	int SituacaoAlocacao;



	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, " Solucao::AdicionaTarefa") == 1 ){

		if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
			PlantasInstancia.InicializaPlantasAnalizadas();
			do{
				EncontraPlantaMenorDistanciaConstrucao(c, NumPlantaAnalisando, "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  ->Solucao::AdicionaTarefa &&&&&&&&&&&&& ");
				PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
				for( int v = 0; v < PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){
					if( ( ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta ) > PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento ){
						HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
					}else{
						HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento;
					}
					do{
						HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
						HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
						HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][Demanda];
						HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];

						DisponibilidadePlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
						DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
						DisponibilidadeCarreta = PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
						if( DisponibilidadePlanta == 1){
							if( DisponibilidadeCarreta == 1){
								if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
									ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(VerificaExistencia, HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, DadosTarefasMovidas);
									ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
									return 1;
								}else{
									if( DisponibilidadeConstrucao == -2){
										cout <<  "                     Caso atrazar da para alocar, demanda em analise [" << Construcao << "-" << Demanda<< "] no horario " << HorarioChegaContrucao << endl;
										if( PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] == 0){
											PlantasInstancia.HorarioQuePlantaPodeAtender[NumPlantaAnalisando] = HorarioInicioPlanta;
											PlantasInstancia.HorarioQueConstrucaoPodeAtenderDemanda[NumPlantaAnalisando] = HorarioChegaContrucao;
										}
										PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] = -2;
										HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento;
									}
								}

							}
						}
						HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
					}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
				}
				if (PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] != -2){
					PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] = 1;
				}
			}while( PlantasInstancia.AnalizouTodasPLanats() == 0);
			cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   -> AdicionaTarefa &&&&&&&&&&&&& " << endl;

			cout << endl << endl <<  " Imprimir SituacaoPlantaAtenderCasoAtrazar" << endl;
			ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
			ImprimeVetorDouble( PlantasInstancia.HorarioQuePlantaPodeAtender);
			ImprimeVetorDouble( PlantasInstancia.HorarioQueConstrucaoPodeAtenderDemanda);
			cin >> ParaPrograma;

			if( PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() == 1){
				DadosTarefasMovidasAuxiliar.clear();


				/* problema aqui. falta adicionar a ultima tarefa (a demanda corrente). só adiciona até uma antes dela. */



				cout << endl << endl << "      Função que atraza demandas - horario que pode atender construção = " << PlantasInstancia.RetornaMenorHorarioQueConstrucaoPode() << endl << endl;
				ConstrucoesInstancia.Construcoes[c].AtrazaDemandasParaAtender( Demanda, PlantasInstancia.RetornaMenorHorarioQueConstrucaoPode() - ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas + IntervaloDeTempo,DadosTarefasMovidasAuxiliar, PlantasInstancia, SituacaoAlocacao, TipoOrdenacao);
					cout << endl << endl <<  " Fim do atraza tarefas" << endl;

					cout << "DadosTarefasMovidasAuxiliar" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

					ConstrucoesInstancia.ImprimeContrucoes();

					cin >> ParaPrograma;


			}

			return 0;

		}else{
			cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema -> Construcao [" << c << "-" << Demanda << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
			return 0;
		}

	}
	return 0;

}


int Solucao::ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia, int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao){
	int c;

	int Alocou;
	Alocou = 0;

	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, "  <<<<    Solucao::ProcessoParaAlocarTarefa  >>>>>") == 0){
		return -1;
	}


	for( unsigned int contrucoes = 0; contrucoes < ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas; demandas++){
			if( contrucoes != c){
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					//cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "]  -> Solucao::ProcessoParaAlocarTarefa";
					Alocou = AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, SituacaoRetirada, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);

					if( Alocou == 1){

						//cout << " => Alocou [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ProcessoParaAlocarTarefa" << endl;
						NovaTarefaAlocadaConstrucao = ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao;
						NovaTarefaAlocadaDemanda = demandas;

						return 1;
					}else{
						//cout << " => Falhou! " << endl;
					}
				}
			}
		}
	}
	return 0;
}

// preciso testar o procedimento de Viabilidade1
void Solucao::ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao){
	int c;

	if( ConstrucoesInstancia.RetornaIndiceConstrucao( construcao, c, " Solucao::ReadicionaTarefas") == 1 ){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
				//cout << " entrei " << endl;
				if( AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao) == 1 ){
					cout << " adicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
				}else{
					cout << " Nao readicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
					return;
				}
			}
		}
	}

}

// readiciona tarefas deletadas e deleta tarefas adicionadas visando restaurar a configuração inicial da solução
int Solucao::ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas){
	int c;

	// percorre trodos os elementos das tarefas que foram removidas e adicionadas no vetor
	for( int i = DadosTarefasMovidas.size() - 1 ; i >= 0; i--){

		// caso a tarefa tenha sido retirada da solução, ela é adicionada novamente
		if( DadosTarefasMovidas[i].Status == 'r'){
			// coleta o inidice da construção
			if(ConstrucoesInstancia.RetornaIndiceConstrucao( DadosTarefasMovidas[i].DadosDasTarefas[0]  , c, " Solucao::DeletaTarefasApartirDeDados") == 0 ){
				return 0;
			}
			// Aloca a tarefa caso possivel
			if( ConstrucoesInstancia.Construcoes[c].AlocaAtividade( DadosTarefasMovidas[i].HorariosDasTarefas[2],DadosTarefasMovidas[i].HorariosDasTarefas[3], DadosTarefasMovidas[i].DadosDasTarefas[2], DadosTarefasMovidas[i].DadosDasTarefas[1], DadosTarefasMovidas[i].DadosDasTarefas[3], DadosTarefasMovidas[i].DadosDasTarefas[4], PlantasInstancia) == 0 ){
				cout << endl << endl << "       <<<<<<<<<<< Problema em adicionar -> Solucao::ReadicionaDeletaTarefasApartirDeDados >>>>>>>>>>>>>>>>> " << endl;
				DadosTarefasMovidas[i].Imprimir();
				cout << endl;
				return 0;
			}
			//Atualiza o Indice de Inviabilidade da solução
			ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
		}

		// caso a tarefa tenha sido adicionada a solução, ela é retirada da solução
		if( DadosTarefasMovidas[i].Status == 'a'){
			// coleta o inidice da construção
			if(ConstrucoesInstancia.RetornaIndiceConstrucao( DadosTarefasMovidas[i].DadosDasTarefas[0]  , c, " Solucao::DeletaTarefasApartirDeDados") == 0 ){
				return 0;
			}
			// deleta a tarefa caso possivel
			if( ConstrucoesInstancia.Construcoes[c].DeletaTarefasAnteriormenteAdicionadasDados( DadosTarefasMovidas[i], PlantasInstancia) == 0){
				cout << endl << endl << "       <<<<<<<<<<< Problema em remover -> Solucao::ReadicionaDeletaTarefasApartirDeDados >>>>>>>>>>>>>>>>> " << endl;
				DadosTarefasMovidas[i].Imprimir();
				cout << endl;
				return 0;
			}
			//Atualiza o Indice de Inviabilidade da solução
			ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade + 1;
		}
	}
	return 1;
}




void Solucao::ProcessoViabilizacao1(int TipoOrdenacao){

	int InviabilidadeSolucaoAnterior;
	bool ExisteTarefa;
	bool TarefaDeletada;
	int NovaTarefaAlocadaConstrucao;
	int NovaTarefaAlocadaDemanda;
	bool TarefaAlocada;
	int Readicionou;
	int ConstrucaoAnalisandoRetirada;
	int DemandaAnalisandoRetirada;

	int PararPrograma;

	vector < DadosTarefa > DadosTarefasMovidas;
	vector < DadosTarefa > AuxiliarLixo;

	int Imprime;

	Imprime = 0;

	int RealizaProcessoDeAtrazarTarefas;

	RealizaProcessoDeAtrazarTarefas = 1;


	//ConstrucoesInstancia.ImprimeContrucoes();
	//PlantasInstancia.Imprime(1,1);

	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	ExisteTarefa = ConstrucoesInstancia.ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, Imprime);		// Encontra primeira tarefa que pode ser retirada
	if( Imprime == 1){
		cin >> PararPrograma;
	}

	if( ExisteTarefa == 1){
		do{
			if( Imprime == 1){
				cout << endl << endl << "        Inicia procediemnto " << endl << endl;
			}
			DadosTarefasMovidas.clear();
			TarefaDeletada = DeletaAlocacaoTarefasPosterioresMesmaConstrucao(1, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, DadosTarefasMovidas);	// Deleta tarefa
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			if( Imprime == 1){
				cout << endl << endl << "    deleta tarefas apos a demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;

				cout << "DadosTarefasMovidas" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasMovidas);

				ConstrucoesInstancia.ImprimeContrucoes();
				//PlantasInstancia.Imprime(1,1);

				cin >> PararPrograma;
			}


			if ( TarefaDeletada == 1){
				// Aloca nova tarefa que não era alocada antes
				AlocaValoresIniciaisIndices( NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);

				//ConstrucoesInstancia.ImprimeContrucoes();


				TarefaAlocada = ProcessoParaAlocarTarefaNaoAtendida(1, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovaTarefaAlocadaConstrucao , NovaTarefaAlocadaDemanda,  DadosTarefasMovidas, 1, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);
				ConstrucoesInstancia.CalcularNivelDeInviabilidade();


				if( TarefaAlocada == 1){

					if( Imprime == 1){
						cout << endl << endl << "         Aloca demanda não atendida anteriormente [ " << NovaTarefaAlocadaConstrucao << "-" << NovaTarefaAlocadaDemanda << "]" << endl << endl;

						cout << endl << "  tenta alocar tarefa" << endl;
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);

						ConstrucoesInstancia.ImprimeContrucoes();
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}

					ReadicionaTarefas(1, ConstrucaoAnalisandoRetirada,DadosTarefasMovidas, 1, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);
					ConstrucoesInstancia.CalcularNivelDeInviabilidade();

					if( Imprime == 1){
						cout << endl << endl << "         Readiciona tarefas deletadas " << endl << endl;

						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);

						ConstrucoesInstancia.ImprimeContrucoes();
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}
					if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
						if( Imprime == 1){
							cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;

							cout << "DadosTarefasMovidas" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidas);

							ConstrucoesInstancia.ImprimeContrucoes();
							//PlantasInstancia.Imprime(1,1);

							cin >> PararPrograma;
						}

						ConstrucoesInstancia.MarcaTarefaNaoDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, "ProcessoViabilizacao1" );
						DadosTarefasMovidas.clear();

					}else{
						if( Imprime == 1){
							cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;

							cout << "DadosTarefasMovidas" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidas);

							ConstrucoesInstancia.ImprimeContrucoes();
							//PlantasInstancia.Imprime(1,1);

							cin >> PararPrograma;
						}

						if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas ) == 0){
							cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
						}
						DadosTarefasMovidas.clear();

						ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);

						if( Imprime == 1){
							cout << endl << endl << "          Deleta tarefas adicionadas, readiciona as deletadas e marca demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;

							cout << "DadosTarefasMovidas" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidas);

							ConstrucoesInstancia.ImprimeContrucoes();
							//PlantasInstancia.Imprime(1,1);

							cin >> PararPrograma;
						}
					}
				}else{


					if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas ) == 0){
						cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
					}
					DadosTarefasMovidas.clear();

					ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);

					if( Imprime == 1){
						cout << endl << endl << "            Nao consegui adicionar nova tarefa - readiciona tarefas e marca terafa como removida" << endl << endl;

						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);

						ConstrucoesInstancia.ImprimeContrucoes();
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}
				}
			}else{
				 cout << endl << endl << endl << "   #######################  Tarefa não deletada ######################## " << endl << endl << endl;
			}

			InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
			ExisteTarefa = ConstrucoesInstancia.ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 0);

			//cout << endl << endl << " ExisteTarefa = " << ExisteTarefa << " ConstrucoesInstancia.NivelDeInviabilidade = " << ConstrucoesInstancia.NivelDeInviabilidade << endl << endl;

		}while( ExisteTarefa == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0);
	}
}

//  Mudando
/*
int Solucao::SelecionaConstrucao( int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucoesAnalizadas){
	double RankInicial;
	int Ativo;

	Ativo = 0;
	RankInicial = DBL_MAX;


	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
				if( ConstrucoesAnalizadas[c] == 0){
					ConstrucaoParaAtender = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					ConstrucaoParaAtenderIndice = c;
					RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
					Ativo = 1;
				}
			}
		}
	}
	if( Ativo == 1){
		return 1;
	}else{
		return 0;
	}
}

int Solucao::SelecionaPlanta( int &PlantaAtender, int &PlantaAtenderIndice, int c, vector < int > PlantasAnalizadas ){
	double DistanciaConstrucaoPlanta;
	int Ativo;

	Ativo = 0;
	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
			if( PlantasAnalizadas[p] == 0){
				PlantaAtenderIndice = p;
				PlantaAtender = PlantasInstancia.Plantas[p].NumeroDaPlanta;
				DistanciaConstrucaoPlanta = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
				Ativo = 1;
			}
		}
	}
	if( Ativo == 1){
		return 1;
	}else{
		return 0;
	}
}

int  Solucao::ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida){

	// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas

	int ConstrucaoTemporario;
	int IndiceConstrucaoTemporario;
	int DemandaTemporaria;

	ConstrucaoTemporario = -13;
	DemandaTemporaria = -13;

	double DistanciaPlantaTemporaria;

	DistanciaPlantaTemporaria = DBL_MAX;

	for ( int i = 0; i < NE; i++){
		for ( int d = ConstrucoesInstancia.Construcoes[i].NumeroDemandas - 1; d >= 0  ; d--){
			if( ConstrucoesInstancia.Construcoes[i].SituacaoDemanda[d] == 0){
				for ( int p = 0; p < NP; p++){
					if( DistanciaPlantaTemporaria > ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[p].Distancia){
						DistanciaPlantaTemporaria = ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[p].Distancia;
						ConstrucaoTemporario = ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao;
						IndiceConstrucaoTemporario = i;
						DemandaTemporaria = d;
					}
				}
			}
		}
	}

	if( ConstrucaoTemporario == -13 || DemandaTemporaria == -13 ){
		return 0;
	}
	ConstrucaoNaoAtendida = ConstrucaoTemporario;
	DemandaNaoAtendida = DemandaTemporaria;

	return 1;
}

void Solucao::AlocaTempoSaiDaPlanta(int IndiceConstrucaoNaoAtendida, vector < double > &TempoSaiPlanta, int Imprime){

// Aloca o tempo inicial que se pode sair uma carreta da planta para suprir a construção.

	for( int p = 0; p < NP; p++){
		if( PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento  < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia){
			TempoSaiPlanta[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia;
		}else{
			TempoSaiPlanta[p] = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
		}
	}

// Aloca o tempo inicial que se pode sair da planta como sendo o tempo da ultima carreta que realizou o ultimo carregamento naquela planta para está construção
	if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento > 0){
		for( int d = 0; d < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento; d++ ){
			for( int p = 0; p < NP; p++){
				if( TempoSaiPlanta[p] < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia){
					TempoSaiPlanta[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia;
				}
			}
		}
	}

// Imprimir o conteudo do vetor Tempo de saida da planta
	if( Imprime == 1){
		for( int p = 0; p < NP; p++){
			cout << " TempoSaiPlanta[" << p << "] = " << TempoSaiPlanta[p] << endl;
		}
	}
}

int Solucao::DeletaTarefasAposTempoSaiPlanta(vector < double > &TempoSaiPlanta, vector < DadosTarefa > &DadosTarefasDesalocadas,  int Imprime){

	int TarefaDeletada;
	int PlantaAux;
	double DistanciaAux;
	int Ativa;

	Ativa = 0;

	//cout << endl << endl << "   Galo 1" << endl << endl;

	for( int c = 0; c < NE; c++){
		//cout << endl << endl << "  Construcao " << c << endl << endl;
		for( int d = ConstrucoesInstancia.Construcoes[c].StatusAtendimento - 1; d >= 0 ; d--){
			//cout << " demanda = " << d << endl;
			PlantaAux = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;
			DistanciaAux = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[ PlantaAux ].Distancia;


			if( ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento - DistanciaAux > TempoSaiPlanta[PlantaAux]){
				if( Imprime == 1){
					cout << "	-> Planta = " << PlantaAux << "   Construcao = " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " (" << c << ")" << endl;
					ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].Imprime();
				}
				TarefaDeletada = ConstrucoesInstancia.Construcoes[c].DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados( ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento, d,  ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada,PlantasInstancia,  DadosTarefasDesalocadas);
				ConstrucoesInstancia.NivelDeInviabilidade++;
				//cout << endl << endl << "   Galo 2" << endl << endl;

				if( TarefaDeletada == 1){
					Ativa = 1;
					if( Imprime == 1 ){
						cout << "                  Tarefa deletada " << endl << endl;
					}
				}
			}
		}
	}

	if( Ativa == 1){
		return 1;
	}
	return 0;

}

void Solucao::SinalizaTarefaAdicionadaInicialmente( int TarefaAdicionada, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendida){		// Sinalisa se a tarefa foi antendida colocando os valores 2 em sua situação remoção. Caso não, a situação tem valor -1 e a remoção 3.
		if( TarefaAdicionada == 1){
			//cout << "                  Tarefa adicionada    -> Solucao::SinalizaTarefaAdicionadaInicialmente" << endl << endl;
			ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] = 2;
			ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDaConstrucao, DemandaNaoAtendida, 2);		// coloca o valor 2 em sua situação remoção
		}else{
			//cout << "                  Tarefa NAO adicionada " << endl << endl;
			for( int d = DemandaNaoAtendida; d < ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDemandas; d++){
				ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ d ] = -1;									// marca com -1, já tento alocar mas não conseguiu
				ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDaConstrucao, d, 3);		// marca com 3 a situação remoção
			}
		}
}

int Solucao::SelecionaCarreta(int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas, int TipoOrdenacao ){		//verifica se é possivel alocar a demanda da construção pela planta em questão
// dados a armazenar
	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;
// decisões a tomar
	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[NumeroDemanda] == 0){		// verifica se a demanda não foi atendida ainda
		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);			// ordena os veiculos da planta que serão analisados
		for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){
			// fixa o horario inicial que se inicia o carregamento na planta
			if( (ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta) > PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta;
			}else{
				HorarioInicioPlanta = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
			}

			do{
				// aloca valores dos horarios
				HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[p].TempoPlanta;
				HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][NumeroDemanda];
				HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				// verifica a viabilidades da alocação que está sendo analisada no momento
				DisponibilidadePlanta = PlantasInstancia.Plantas[p].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeCarreta = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
				DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);

				if( DisponibilidadePlanta == 1){		// possivel o atendimento pela planta
					if( DisponibilidadeCarreta == 1){		// possivel o atendimento pelo carregamento
						if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){	// Possivel alocação pela construção, os números 1, 2 e 3 são referentes a posição onde a demanda será alocada em relação as outras demandas já alocadas na construção
							ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[p].NumeroDaPlanta,  1,0, PlantasInstancia, DadosTarefasAdicionadas);	// aloca a demanda tanto no veículo, construção e planta
							return 1;
						}
						if( DisponibilidadeConstrucao == -2){	// sinaliza que no momento não é possivel alocar a demanda, mas caso atrazar as outras demandas já atendidas talvéz seja possivel atender essa demanda
							return -2;
						}
					}
				}
				HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;	// acrescenta o horario que se ira analizar a colocação da demanda
			}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);		// verifica se violou os tempos maximos de funcionamento tanto da construção ou da planta. caso se violar ele sai do loop e informa que a demanda em analise não pode ser atendida pela planat em analise
		}
		return 0;
	}else{
		cout << endl << endl << " Está tentando alocar uma demanda que já foi alocada -> construção " <<  ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " [" << c << " - " << NumeroDemanda << "] " << endl << endl;
		return -13;
	}
}

int Solucao::SelecionaCarretaComHoraInicio( double HoraInicio, int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas , int TipoOrdenacao){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	//int ParaPrograma;

	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[NumeroDemanda] == 0){

		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);

		for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){

			if( (HoraInicio - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta) > PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = HoraInicio - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta;
			}else{
				HorarioInicioPlanta = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
			}
			do{
				HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[p].TempoPlanta;

				HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][NumeroDemanda];
				HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				DisponibilidadePlanta = PlantasInstancia.Plantas[p].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeCarreta = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
				DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);

				if( DisponibilidadePlanta == 1){
					if( DisponibilidadeCarreta == 1){
						if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
							ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[p].NumeroDaPlanta,  0, 1, PlantasInstancia, DadosTarefasAdicionadas);
							return 1;
						}
						if( DisponibilidadeConstrucao == -2){
							return -2;
						}
					}
				}
				HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
			}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
		}
	}

	return 0;
}

int Solucao::ColocarTarefaAtrazandoAsOutras(int ConstrucaoParaAtenderIndice, int demanda , double HoraInicio, vector < DadosTarefa > & DadosAdicionaAux, int TipoOrdenacao, int Imprime){
	vector < int > SituacaoPlantas;
	vector < int > SituacaoDemandas;
	double HorarioInicioConstrucao;

	int ExistePlanta;
	int PlantaAtender;
	int PlantaAtenderIndice;

	int PermiteAtendimentoDemanda;

	vector < DadosTarefa > TemporarioAdiciona;
	vector < DadosTarefa > AuxiliarRetira;

	HorarioInicioConstrucao = HoraInicio + IntervaloDeTempo;	// aumenta o tempo que a primeira demanda pode ser atendida

	SituacaoPlantas.resize(NP);					// Vetor que armazena se a planta foi analisada ou não para atender certa demanda
	SituacaoDemandas.resize(demanda + 1); 		// Tem que somar mais um pelo fato de se contar o 0 como um elemento

	while(HorarioInicioConstrucao <  ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento ){

		if ( Imprime == 1){
			//cout << "  HorarioInicioConstrucao " << HorarioInicioConstrucao << " / " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento << endl;
		}
		IniciaVetorIntComZero(SituacaoDemandas);
		for( int d = 0; d <= demanda; d++){
			IniciaVetorIntComZero(SituacaoPlantas);
			ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );		// seleciona planta a atender
			PermiteAtendimentoDemanda = 0;
			while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < demanda + 1 && PermiteAtendimentoDemanda == 0){
				SituacaoPlantas[PlantaAtenderIndice] = 1;							// Marca planta atendida
				PermiteAtendimentoDemanda = SelecionaCarretaComHoraInicio( HorarioInicioConstrucao, ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, TemporarioAdiciona, TipoOrdenacao); 		// aloca atendimento da demanda se 1, 0 se não
				if( PermiteAtendimentoDemanda == 1){		// se alocou a demanda
					IniciaVetorIntComZero(SituacaoPlantas);		// zera o vetor do status das plantas
					SituacaoDemandas[d] = 1;					// coloca a demanda como atendida
				}else{
					if( PermiteAtendimentoDemanda == 0){
						SituacaoPlantas[PlantaAtender] = 1;			// marca planta já analisada
					}
					if ( PermiteAtendimentoDemanda == -2){
						SituacaoPlantas[PlantaAtender] = -2;		// marca planata já analisada, mas que poderia atender a demnada caso a demanda anterior fosse mais tarde
					}
				}
				ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );	// retorna a planta que ira atender a proxima demanda
			}
			if ( VerificaTodosValoresVetorInt( 1, SituacaoDemandas) == 1){
				DadosAdicionaAux = TemporarioAdiciona;		// retorna as tarefas adicionadas no procediemnto
				return 1;
			}
		}
		if ( VerificaSeTemUmValorVetorInt( -2, SituacaoPlantas) == 1){
			ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);		//deleta tarefas anteriores ao horario inicio, pois ainda há possibilidade de atender a demanda que ainda não conseguimos atender
			TemporarioAdiciona.clear();													// deleta conteudo do vetor de tarefas adicionadas, pois elas forma deletadas no procedimento acima
			HorarioInicioConstrucao = HorarioInicioConstrucao + IntervaloDeTempo;		// aumenta o tempo que se começa a alocar as tarefas
		}else{
			// Não se consegue adicionar a demanda mesmo atrazando as atnteriores
			//ImprimeVetorInt( SituacaoPlantas);
			//ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);		// deleta todas as tarefas adicionadas
			TemporarioAdiciona.clear();			// limpa vetor com as tarefas adicionadas durante o procedimento
			return 0;
		}
	}
	// ultrapassou o limite de tempo na construção
	if ( Imprime == 1){
		cout << endl << endl << "  Não da para atrazar " << endl << endl;
	}
	TemporarioAdiciona.clear();				// limpa vetor com as tarefas adicionadas durante o procedimento
	return 0;

}

void Solucao::ProcessoViabilizacao2(int TipoOrdenacao){

	int InviabilidadeSolucaoAnterior;


	int	ConstrucaoNaoAtendida;
	int IndiceConstrucaoNaoAtendida;
	int DemandaNaoAtendida;

	int DeletouAlgumaTarefa;

	vector < double > TempoSaiPlanta;

	vector < DadosTarefa > DadosTarefasDesalocadas;
	vector < DadosTarefa > DadosTarefasAdicionadas;

	int TarefaAdicionada;

	int ConstrucaoParaAtender;
	int ConstrucaoParaAtenderIndice;
	int PossuiConstrucaoParaAnalisar;

	int d;

	int PlantaAtender;
	int PlantaAtenderIndice;
	int ExistePlanta;

	int PermiteAtendimentoDemanda;


	vector< int > PlantasPodemAtenderTarefa;

// estrutura para processo de atrazar tarefas
	double HoraInicio;
	vector < DadosTarefa > DadosRetirandoAux;
	vector < DadosTarefa > DadosAdicionaAux;
	int ConseguiAlocarTarefa;

	//Plantas que podem atender as tarefas caso as tarefas posteriores forem atrasadas

	int Imprime;
	int PararPrograma;

	Imprime = 1;

	int RealizaProcessoDeAtrazarTarefas;

	RealizaProcessoDeAtrazarTarefas = 0;

// Encontra demanda ainda não atendida

	ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();		// Marca as construções que já foram completamente atenddidas com 1, as que não forma com 0

	while( ConstrucoesInstancia.VerificaConstrucaoPodeAtender() == 1){			// Verifica se pode atender uma construção ainda, se tem uma com demanda não atendida

		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;		// guarda o nivel de inviabilidade
		ConstrucoesInstancia.ReiniciaTarefasRetiradas();								// reinicia o estado de deslocamento e remoção de todas as demandas de todas as construções
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);		// retorna a demanda e a construção que serão analisados inicialmente
		TempoSaiPlanta.resize(NP);														// inicia o tamanho do vetor de tempo do inicio das plantas com 0
		if( Imprime == 1){
			cout << " ConstrucaoNaoAtendida = " << ConstrucaoNaoAtendida <<" DemandaNaoAtendida = " << DemandaNaoAtendida << endl << endl;
		}
		ConstrucoesInstancia.RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );		// retorna o incide da cosntrução que tem qeu ser analisada no momento
	// deleta tarefas que são atendidas antes desta tarefa não alocada
		AlocaTempoSaiDaPlanta(IndiceConstrucaoNaoAtendida,TempoSaiPlanta, 0);		// aloca no vetor TempoSaiPlanta os tempos que as plantas podem atender
		DeletouAlgumaTarefa = DeletaTarefasAposTempoSaiPlanta(TempoSaiPlanta, DadosTarefasDesalocadas,  0);		// deleta tarefas que são atendidas antes dos tempos armazenadaos no vetor TempoSaiPlanta
		if( Imprime == 1){
			cout << "   							<<<<<<<<<<< Deteta tarefas >>>>>>>>>>>>>> ";
			ConstrucoesInstancia.ImprimeContrucoes();
			cin >> PararPrograma;
		}
	// Adiciona a tarefa que não era alocada antes
		TarefaAdicionada = AdicionaTarefa( ConstrucaoNaoAtendida, DemandaNaoAtendida, DadosTarefasAdicionadas,DadosTarefasAdicionadas, 2, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);		// tenta adicionar a demanda não atendida anteriormente. Caso consegui retorna 1, caso contrario retorna 0.
		SinalizaTarefaAdicionadaInicialmente( TarefaAdicionada, IndiceConstrucaoNaoAtendida, DemandaNaoAtendida);						// atualiza os valores de situação e remoção da demanda. caso for atendida coloca 2 em ambos, caso não, a situação tem valor -1 e a remoção 3
		if( ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] == -1){		// Verifa se conseguiu alocar a demnada não alocada antes.
			// Caos não aloque a demanda
			if( Imprime == 1){
				cout << endl << endl << "   Não consigo alocar tarefa [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] que não foi alocada antes -> Solucao::ProcessoViabilizacao2 " << endl << endl;
			}
			ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas);	// retorna a solução inicial
			DadosTarefasDesalocadas.clear();								// deleta conteudo do vetor

			//ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();		// Marca as construções que já foram completamente atendidas com 1, as que não forma com 0

			ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 4;		// marca cosntrução como já analisada e que não se consegue alocar a demanda utilizando esse procedimento já no inicio após deletar todas as tarefas. Ou seja, não se consegue alocar essa tarefa usando as plantas que se tem.
		}else{

			if( Imprime == 1){
				cout << "   						<<<<<<<<<<< Coloca tarfea não alocada anterioremnte [" <<  ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "]  >>>>>>>>>>>>>>> ";
				ConstrucoesInstancia.ImprimeContrucoes();
				ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cin >> PararPrograma;
			}

	// marca construções com tarefas a alocar
			ConstrucoesInstancia.InicializaConstrucoesAnalizadas();										// marca todas as construções como possiveis a alocar demandas, todas com 0 em ConstrucoesAnalisadas
			ConstrucoesInstancia.AlocaValoresConstrucoesAnalizadas( IndiceConstrucaoNaoAtendida);		// marca as construções com todas suas demandas atendidas com 2, e a construção que tinha uma demanda sem atender e que agora foi atendida com 3
	// Verifica se tem tarefa a se colocar
			PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucoesAnalizadas);					// escolhe a construção com o menor indice e que pode ser atendida ( todas as construções com 0 em CosntruçõesAnalisadas, estas são as que não tem suas demandas todas atendidas e que não sejá a que passou a ter uma demanda que não era atendida antes e agora é atendida)
			if( Imprime == 1){
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1, ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cout << "   <<<<<<<<<<< Readiciona demandas   >>>>>>>>>>>>>>> " << endl;
				//cin >> PararPrograma;
			}
			while( PossuiConstrucaoParaAnalisar == 1){				// caso se tenha uma construção ainda para se adicionar demnadas
				ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucaoParaAtenderIndice] = 1;			// marca cosntrução como analisada
				d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;	// coloca a demanda que se tem que alocar no momento
				if( Imprime == 1){
					cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]";
				}
				PlantasInstancia.InicializaPlantasAnalizadas();											// faz com que nenhuma planta tenha sido analisada
				ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a planta mais proxima que pode atender a planta
				if( Imprime == 1){
					//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
					//cin >> PararPrograma;
				}
				while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){		//  caso ainda for possivel atender uma demanda da construção continuar
					PlantasInstancia.PlantasAnalizadas[PlantaAtenderIndice] = 1;					// marca planta como já analisada
					PermiteAtendimentoDemanda = SelecionaCarreta(ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, DadosTarefasAdicionadas , TipoOrdenacao);		// verifica se a demanda pode ser atendida por essa planta, caso for retorna 1, caso não, retorna -2 se é possivel caso atraze as demandas já alocadas ou 0 caso a planta não possa ser utilizada para atender essa demnada com as demandas que ela atende no momento
					if( Imprime == 1){
						//cout << "     		Tenta Planta " << PlantaAtender << " [" << PlantaAtenderIndice << "]" << endl;
						//ConstrucoesInstancia.ImprimeContrucoes();
						//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
					}
					if( PermiteAtendimentoDemanda == 1){	// demanda é alocada
						if( Imprime == 1){
							cout << "      Atendida " << endl;
							//cout << "             +++++   Planta [" << PlantaAtenderIndice << "] " << PlantasInstancia.Plantas[PlantaAtenderIndice].NumeroDaPlanta << "  atende demanda " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						}
						if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){			// caso a demanda não for a ultima que temq eu ser alocada na construção. isto se dá pois temq eu se contra com a dmenada 0
							d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;		// atualiza a variavel "d" com a proxima demanda que temq eu ser atendida
								if( Imprime == 1){
									if( d != ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
										cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]" ;
									}
								}
								PlantasInstancia.InicializaPlantasAnalizadas();		// faz com que nenhuma planta tenah sido atendida
								ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );	// seleciona a primeira planta que pode atender a demanda referente a demnada "d"
						}else{
							// caso for a demnada que foi alocada ser a ultima que tem que ser atendida na construção
							PlantasInstancia.InicializaPlantasAnalizadas();		// faz com que nenhuma planta tenah sido atendida, isto qtem que ser feito para fugir do "if" que pega as demnadas não atendidas
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a primeira planta que pode atender
						}
					}else{
						if( PermiteAtendimentoDemanda == 0){		// não é possivel atender a demanda com essa planta
							PlantasInstancia.PlantasAnalizadas[PlantaAtender] = 1;		// maraca planta como analisada
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a primeira planta que pode atender
						}
						if ( PermiteAtendimentoDemanda == -2){		// no momento não é possivel atender a demanda, mas caso atarzar as demandas que já foram alocadas na cosntrução pode ser possivel que ela possa ser atendida por essa planta
							PlantasInstancia.PlantasAnalizadas[PlantaAtender] = -2;		// marca planta como sendo possivel atender a demanda em questão caso atraze as outras demandas ja atendidas na cosntrução
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a primeira planta que pode atender
						}


// Verifica se pode atrazar

						if( ExistePlanta == 0 && PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento >= 1){		// verifica se pode atrazar. isto é, caso não se tenha mais nenhuma planta para se analisar se pode atender a demanda, caso se tenha uma planat que pode atender a demnada caso se atraze suas demandas e caso a construção tenha uma ou mais demandas já atendidas
							if( Imprime == 1){
								cout << endl << endl << "   	Pode atrazar tarefas da construção " << ConstrucaoParaAtender << " [" << ConstrucaoParaAtenderIndice << "] - d = " << d << " para alocar outra " << endl;
								ImprimeVetorInt(PlantasInstancia.PlantasAnalizadas);
								ConstrucoesInstancia.ImprimeContrucoes();
								cout  << endl << endl;
							}

							ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, DadosRetirandoAux);		// deleta todas as demandas atendidas na construção
							ConseguiAlocarTarefa = ColocarTarefaAtrazandoAsOutras( ConstrucaoParaAtenderIndice, d , HoraInicio, DadosAdicionaAux, TipoOrdenacao, Imprime);						// Tenta recolocar as demandas deletadas acima ao atrazar o atendimento das demandas iniciais

							if( ConseguiAlocarTarefa == 1){			// consegui alocara demanda
								PermiteAtendimentoDemanda = 1;		// marco que consegui alocar a demanda não atendida inicialmente
								if( Imprime == 1){
									cout << endl << "      Atendida apos atrazar" << endl;
								}
								if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){		// atualizo a variável "d" com a proxima demanda da construção caso está existir
									d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;	// atualizo a variável "d"
									if( Imprime == 1){
										if( d != ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
											cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]" ;
										}
									}
									PlantasInstancia.InicializaPlantasAnalizadas();				// faz com que nenhuma planta tenah sido atendida
									ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );	// seleciona a primeira planta que pode atender a demanda referente a demnada "d"
								}else{
									PlantasInstancia.InicializaPlantasAnalizadas();				// faz com que nenhuma planta tenah sido atendida
									ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );	// seleciona a primeira planta que pode atender a demanda referente a demnada "d"
								}

								cout << endl << endl << " depois processo de tentar atrazar terefas " << endl << endl;

								ConstrucoesInstancia.ImprimeContrucoes();

								cout << endl << endl << "    Antes na função " << endl << endl;

								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cout << endl << endl << "    Dados da função " << endl << endl;

								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1, DadosRetirandoAux, 1,  DadosAdicionaAux, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cin >> PararPrograma;

								for( unsigned int i = 0; i < DadosRetirandoAux.size();i++){

									if( VerificaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas ,DadosRetirandoAux[i] ) == 1){
										// caso eu retire uma tarefa no procedimento atraza, se está tarefa já tiver sido colocada no vetor de tarefas adicionadas, eu a retiro desse vetor (é como se essa tarefa nunca tivesse existido )
										if( RetiraElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas, DadosRetirandoAux[i]) == 0){
											cout << "    Não retirou " << endl;
											if( Imprime == 1){
												//DadosRetirandoAux[i].Imprimir();
												//cout << "             DadosRetirandoAux" << endl ;
											}
										}
									}else{
										// caso eu retire uma tarefa no procedimento atraza, se está tarefa não já tiver sido colocada no vetor de tarefas adicionadas anteriormente, ela é originaria do sequencimanto original. Logo eu a coloco no vetor de tarefas retiradas
										if( AdicionaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasDesalocadas, DadosRetirandoAux[i]) == 0){
											cout << "    Não adicionou " << endl;
											if( Imprime == 1){
												//DadosRetirandoAux[i].Imprimir();
												//cout << "             DadosRetirandoAux" << endl ;
											}
										}
									}
								}

								for( unsigned int i = 0; i < DadosAdicionaAux.size();i++){
									// Todas as tarefas  adicionadas no procedimento no vetor de tarefas que foram adicionadas
									if( AdicionaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas, DadosAdicionaAux[i] ) == 0){
										cout << "    Naõ adicionou " << endl;
										if( Imprime == 1){
											//DadosRetirandoAux[i].Imprimir();
											//cout << "             DadosAdicionaAux" << endl ;
										}
									}
								}

								cout << endl << endl << "    Depois na função " << endl << endl;


								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cout << endl << endl << "    Dados da função " << endl << endl;

								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1, DadosRetirandoAux, 1,  DadosAdicionaAux, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cin >> PararPrograma;

							}else{
								// neste caso, não foi possivel adicionar a demanda. O procedimento já deleta as tarefas alocadas nele para a construção. Aqui se é readicionado as demandas deletadas inicialmente para que o sequenciamento fique como era antes de se executar o procedimento.
								ReadicionaTarefasApartirDeDados( DadosRetirandoAux, 1);
								DadosRetirandoAux.clear();
							}

							//cout << endl << endl << "    depois de atualizar vetores " << endl << endl;
							//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

							//cin >> PararPrograma;


						}


					}

					// Entra aqui caso não se consiga atender a demanda em questão por nenhuma planta
					if( ExistePlanta == 0 ){
						if( Imprime == 1){
							cout << "     -> Não atendida" << endl;
							//cout << " Nao se pode colocar tarefa da construcao [" << ConstrucaoParaAtenderIndice << "] " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						}
						ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucaoParaAtenderIndice] = 4;		// marca a cosntrução com 4, para saber que não se consegue alocar mais demandas nela com a configuração atual do sequenciamento.
						if( Imprime == 1){
							//ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
							//ConstrucoesInstancia.ImprimeContrucoes();
						}
					}
				}
				PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucoesAnalizadas);	// se passa para a proxima construção que se pode atender
				if( Imprime == 1){
					//ConstrucoesInstancia.ImprimeContrucoes();
					//PlantasInstancia.Imprime(1,1);
					//cin >> PararPrograma;
				}

			}

			ConstrucoesInstancia.CalcularNivelDeInviabilidade();		// calcula o nivel de inviabilidade que ira mostrar se a soluçpão melhorou ou não

			if( Imprime == 1){
				cin >> PararPrograma;
				ConstrucoesInstancia.ImprimeContrucoes();
				//PlantasInstancia.Imprime(1,1);
			}

			// verifica se a solução melhorou
			if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
				if( Imprime == 1){
					cout << endl << endl << "    Melhorou !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes();
				}
				// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();		// atualiza a situação da construçãoq ue teve todas as suas demandas atendidas

			}else{
				if( Imprime == 1){
					cout << endl << endl << "    Não melhorou !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes();
					cin >> PararPrograma;
				}

				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

				cout << endl << " aqui 1" << endl;
				if( DeletaTarefasApartirDeDados(  DadosTarefasAdicionadas ) == 0){			// deleta as tarefas adicionadas durante o procedimento
					if( Imprime == 1){
						cout << endl << endl << "   problema em deletar " << endl << endl;
					}
				}
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cout << endl << " aqui 2" << endl;

				if( ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas) == 0){		// readiciona as tarefas que foram deletadas anteriormente, visando a retornar ao sequenciamento que se tinha inicialmente
					if( Imprime == 1){
						cout << endl << endl << "   problema em realocar " << endl << endl;
					}
				}
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cout << endl << " aqui 3" << endl;
				// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();		// atualiza a situação da construçãoq ue teve todas as suas demandas atendidas
				ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 3;	// Marca a construção qeu logo após deletar as tarefas, adicionar a demanda não alocada dela e depois readicionar as demandas deletadas antes, não se chegou em um sequenciamento melhor.
			}

			//cin >> PararPrograma;
		}
	}
}

*/
Solucao::~Solucao(){

}

class ConjuntoSolucoes{
public:
	ConjuntoSolucoes();
	vector < Solucao > Solucoes;
	void InsereSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);
	void CalculaMakespanSolucoes();
	void Imprime(bool, bool, bool);
	~ConjuntoSolucoes();

};

ConjuntoSolucoes::ConjuntoSolucoes(){
}

void ConjuntoSolucoes::InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	Solucao S1;
	S1.CarregaSolucao( np, Plantas, ne, Construcoes, nv, v, TDVC);
	Solucoes.push_back(S1);
}

void ConjuntoSolucoes::CalculaMakespanSolucoes(){
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		Solucoes[s].ConstrucoesInstancia.CalculaMakespansConstrucoes();
		Solucoes[s].PlantasInstancia.CalculaMakespanPlantas();
		Solucoes[s].Makespan = Solucoes[s].ConstrucoesInstancia.MakespanConstrucoes + Solucoes[s].PlantasInstancia.MakespanPLantas;
	}
}

void ConjuntoSolucoes::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes){
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		cout << endl << endl << "   Solucao " << s << endl << endl;
		 Solucoes[s].Imprime(ImprimePlanta,ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);
		 cout << "         Makespan total = " << Solucoes[s].Makespan << endl ;
	}
}



ConjuntoSolucoes::~ConjuntoSolucoes(){

}



#endif /* SOLUCOES_HPP_ */
