/*
 * ModeloInicioHeuristica.hpp
 *
 *  Created on: 15 de mar de 2017
 *      Author: mavus
 */

#ifndef MODELOINICIOHEURISTICA_HPP_
#define MODELOINICIOHEURISTICA_HPP_

#include "Bibliotecas.hpp"

class ClasseModeloInicioHeuristica : public ClasseModelo{
	public:

	// variaveis para exportar os resultados
	bool HeuristicaResposta;
	double SolucaoHeuristica;
	double TempoHeuristica;

	int CplexInicia(string, int, long int, long int, int, int, int, int, int&, double&, double&, double&, double&, double&);

};



// Resolve modelo
int ClasseModeloInicioHeuristica::CplexInicia(string Nome, int RealizaProcessoDeAtrazarTarefas, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int  TempoExecucao, int &status, double &primal, double &dual, double& SolucaoReal,   double &gap, double &tempo){

	int Escreve;				// Escreve variaveis criadas

	int EscreveVariaveis;
	int OutPut1;
	int OutPut2;
	int SaidaPastaSeparada;
	int EscreveArquivoComRespostas;
	int EscreveNaTelaResultados;
	vector < int > EscreveRestricao;
	EscreveRestricao.resize(20+1);
	for( int i = 0; i <= 20; i++){
		EscreveRestricao[i] = 0;
	}

	vector < int > TamanhoPenalidade;
	TamanhoPenalidade.resize(2+1);
	for( int i = 0; i <= 2; i++){
		TamanhoPenalidade[i] = 2;
	}

	Escreve = 0;				// Escreve as variaveis criadas
	EscreveVariaveis = 1;
	OutPut1 = 1;
	OutPut2 = 1;
	SaidaPastaSeparada = 1;
	EscreveArquivoComRespostas = 1;
	EscreveNaTelaResultados = 0;

// Começa a escrever modelo do Cplex
	IloModel 	model(env);

/* Declara variaveis */

// Variavel ALFA
	TipoAlfa 	Alfa(env, NV);
	CriaAlfa(Alfa,Escreve);

// Variavel BETA
	TipoBeta 	Beta(env, NV);
	CriaBeta(Beta,Escreve);

// Variavel BETAProducao
	TipoBeta 	BetaProducao(env, NV);
	CriaBetaProducao(BetaProducao,Escreve);


// Variavel Ze
	TipoZe 		Ze(env,NE);
	CriaZe(Ze ,Escreve);



// Variavel Tvei
	TipoTvei 	Tvei(env,NV);
	CriaTvei( Tvei, Escreve);

// Variavel TPvei
	TipoTPvei 	TPvei(env,NV);
	CriaTPvei( TPvei, Escreve);




// Calcula variaveis de adiantamento e postergamento dos limites de tempo
	CalculaTempoPodeAdiantarOuPostergarEmpresa(Escreve);



// Funcao Objetivo
	FuncaoObjetivo(Ze, model, EscreveRestricao[0]);

// Restrição 1 : Antendimento das Demandas
	Restricao_AtendimentoDasDemandas(Alfa, model, EscreveRestricao[1]);
// Restrição  2 : Lower bound Ze
	Restricao_LowerBoundZe(Ze, Tvei, Alfa, model, EscreveRestricao[2]);
// Restrição  3 : Vinculo Tvei e TPvei
	Restricao_VinculoTveiTPvei( Alfa, TPvei, Tvei,model, EscreveRestricao[3] );
// Restrição  5 e 6 : de precedencia Tvei
	Restricao_PrecedenciaTvei(  Alfa, Beta, Tvei, model,  EscreveRestricao[5], EscreveRestricao[6]);
// Restrição  7:
	Restricao_TempoMaximoEntreDescarregamentosSeguidosNaMesmaEntrega( Alfa, Tvei, model, EscreveRestricao[7] );
// Restrição 8
    Restricao_TempoMinimoEntreDescarregamentosSeguidosNaMesmaEntrega( Alfa, Tvei, model, EscreveRestricao[10] );
// Restrição 9
    Restricao_PrecedenciaTPvei( Alfa, BetaProducao, TPvei, model, EscreveRestricao[11],EscreveRestricao[12]);
// Restrição 10
    Restricao_TempoDeVidaDoConcreto( Alfa,Tvei,TPvei, model,EscreveRestricao[13]);
// Restrição  11
	Restricao_LimiteDeTempoNaEntrega( Tvei,  Alfa, model, EscreveRestricao[14] );
// Restrição  12
	Restricao_LimiteDeTempoNaPlanta(  TPvei,  Alfa, model, EscreveRestricao[15] );




// Modelo
	IloCplex *cplex;

	cplex = new IloCplex(model);
	//cplex->exportModel("model.lp");

// Cria pasta OUT
	VerificaOuCriaPastaOut(EscreveNaTelaResultados);

	Nome1 = "./Out/";
	Nome1 += Nome;

	//cout << endl << endl << " arquivo a gravar a saida " << c1 << endl << endl;

	ofstream logfile1(Nome1.c_str());

	if(SaidaPastaSeparada == 1){
		cplex->setOut(logfile1);
	}
	cplex->setParam(IloCplex::TiLim,  TempoExecucao);
	cplex->setParam(IloCplex::Threads, 12);

// heuristica inicio

	Heuristica *Instancia2;

	Instancia2 = new Heuristica;

	if( Instancia2->LeDados(Nome, 0) == 1){

//		cout << "NumeroIteracoes  " << NumeroIteracoes << "  TempoExecucaoMaximo  " << TempoExecucaoMaximo ;
//		cout << "  EscolhaVeiculo  " << EscolhaVeiculo << " EscolhaConstrucao  " << EscolhaConstrucao << " EscolhaPlanta " << EscolhaPlanta;
//		cout << "  RealizaProcessoDeAtrazarTarefas" << RealizaProcessoDeAtrazarTarefas << endl;
		Instancia2->ExecutaConsBuscasVeiConsPlan(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);

		HeuristicaResposta = 0;


		TempoHeuristica = Instancia2->TempoExecucao;

		if( Instancia2->ConstrucoesInstancia.NivelDeInviabilidade == 0){

			HeuristicaResposta = 1;
			SolucaoHeuristica = Instancia2->ConstrucoesInstancia.MakespanConstrucoes;
			TempoHeuristica = Instancia2->TempoExecucao;

			Instancia2->IniciaVariaveisDoModelo();
			Instancia2->AlocaVariaveisDoModelo();


			/*
					IloNumVarArray startVar(env);
					IloNumArray startVal(env);

					for(int i=0; i<n; i++){
						int a = solucao_heuristica[ i ];
						int b = solucao_heuristica[ (i+1) % n ];
						startVar.add(x[a][b]);
						startVal.add(1);
					}

					cplex->addMIPStart(startVar, startVal);

					startVal.end();
					startVar.end();
			*/
			// TVvei
			IloNumVarArray startVarTVvei(env);
			IloNumArray startValTVvei(env);

			for( int v = 0; v < NV; v++){
				for( int e = 0; e < NE; e++){
					for( int d = 0; d < Instancia2->DM.Demandas[e]; d++){
						startVarTVvei.add(Tvei[v][e][d]);
						startValTVvei.add(Instancia2->TVvei[v][e][d]);
					}
				}
			}
			cplex->addMIPStart(startVarTVvei,startValTVvei);
			startVarTVvei.end();
			startValTVvei.end();

			// TPvei
			IloNumVarArray startVarTVPvei(env);
			IloNumArray startValTVPvei(env);

			for( int v = 0; v < NV; v++){
				for( int e = 0; e < NE; e++){
					for( int d = 0; d < Instancia2->DM.Demandas[e]; d++){
						startVarTVPvei.add(TPvei[v][e][d]);
						startValTVPvei.add(Instancia2->TVPvei[v][e][d]);
					}
				}
			}
			cplex->addMIPStart(startVarTVPvei,startValTVPvei);
			startVarTVPvei.end();
			startValTVPvei.end();

			// ALFAvei
			IloNumVarArray startVarALFAvei(env);
			IloNumArray startValALFAvei(env);

			for( int v = 0; v < NV; v++){
				for( int e = 0; e < NE; e++){
					for( int d = 0; d < Instancia2->DM.Demandas[e]; d++){
						startVarALFAvei.add(Alfa[v][e][d]);
						startValALFAvei.add(Instancia2->ALFAvei[v][e][d]);
					}
				}
			}
			cplex->addMIPStart(startVarALFAvei,startValALFAvei);
			startVarALFAvei.end();
			startValALFAvei.end();

			// BETAveiei
			IloNumVarArray startVarBETAveiei(env);
			IloNumArray startValBETAveiei(env);

			for( int v = 0; v < NV; v++){
				for( int e1 = 0; e1 < NE; e1++){
					for( int d1 = 0; d1 < Instancia2->DM.Demandas[e1]; d1++){
						for( int e2 = 0; e2 < NE; e2++){
							for( int d2 = 0; d2 < Instancia2->DM.Demandas[e2]; d2++){
								if( e1 == e2 && d1 == d2){

								}else{
									startVarBETAveiei.add(Beta[v][e1][d1][e2][d2]);
									startValBETAveiei.add(Instancia2->BETAveiei[v][e1][d1][e2][d2]);
								}
							}
						}
					}
				}
			}
			cplex->addMIPStart(startVarBETAveiei,startValBETAveiei);
			startVarBETAveiei.end();
			startValBETAveiei.end();

			// BETAPpeiei
			IloNumVarArray startVarBETAPpeiei(env);
			IloNumArray startValBETAPpeiei(env);

			for( int p = 0; p < NP; p++){
				for( int e1 = 0; e1 < NE; e1++){
					for( int d1 = 0; d1 < Instancia2->DM.Demandas[e1]; d1++){
						for( int e2 = 0; e2 < NE; e2++){
							for( int d2 = 0; d2 < Instancia2->DM.Demandas[e2]; d2++){
								if( e1 == e2 && d1 == d2){

								}else{

									//cout << " BETAPpeiei[" << p <<"][" << e1 << "][" << d1 << "][" << e2 << "][" << d2 << "] = " << Instancia2->BETAPpeiei[p][e1][d1][e2][d2] << endl;

									startVarBETAPpeiei.add(BetaProducao[p][e1][d1][e2][d2]);
									startValBETAPpeiei.add(Instancia2->BETAPpeiei[p][e1][d1][e2][d2]);
								}
							}
						}
					}
				}
			}
			cplex->addMIPStart(startVarBETAPpeiei,startValBETAPpeiei);
			startVarBETAPpeiei.end();
			startValBETAPpeiei.end();


			// Ze
			IloNumVarArray startVarZe(env);
			IloNumArray startValZe(env);


			for( int e = 0; e < NE; e++){

				//cout << "   Ze[" << e << "] = " << Instancia2->Ze[e] << endl;

				startVarZe.add( Ze[e] );
				startValZe.add( Instancia2->Ze[e] );
			}

			cplex->addMIPStart( startVarZe, startValZe);
			startVarZe.end();
			startValZe.end();
			//cout << endl << " passando " << endl;
		}
	}


// heuristica fim


	Tempo1 = cplex->getCplexTime();

	//cout << endl << " setou tempo" << endl << endl;
	primal = -1;
	dual = -1;
	SolucaoReal = -1;
	gap = -1;

// Resolve o modelo.
	if (!cplex->solve()) {
		cerr << "Failed to optimize LP." << endl;
		status = cplex->getStatus();
		cout << " status = (" << status << ")" << endl;
		tempo = cplex->getCplexTime() - Tempo1;
		logfile1.close();
		//throw(-1);                                                   // Olhar!!!!!!!!!!!!!!!!!!

		//model.end();				// problema, trava o programa. olhar! falam que demora muito. que é melhor deletar o objeto IloClpex

		delete(cplex);

		Alfa.clear();
		Beta.clear();
		BetaProducao.clear();
		Ze.clear();
		Tvei.clear();
		TPvei.clear();
		TPvei.clear();
		EscreveRestricao.clear();

		return (0);
	}else{

		//cout << endl << " rodou " << endl << endl;

		Tempo2 = cplex->getCplexTime();

		VerificaOuCriaPastaSol(EscreveNaTelaResultados);

		Nome2 = "./Sol/";
		Nome2 += Nome;

		//cout << endl << endl << " arquivo a gravar a solucao " << Nome2 << endl << endl;

		ofstream logfile2(Nome2.c_str());

		status = cplex->getStatus();
		primal = cplex->getObjValue();
		dual = cplex->getBestObjValue();
		if( cplex->getStatus() == 1 || cplex->getStatus() == 2 || cplex->getStatus() == 4 ){
			CalculaFuncaoObjetivo(		*cplex, Ze, 	SolucaoReal);
		}
		gap =  100 * ( cplex->getObjValue() - cplex->getBestObjValue() ) / cplex->getObjValue();
		tempo = Tempo2 - Tempo1;

		if( EscreveNaTelaResultados == 1){
			cout << "Solution status = " << status << " [" << cplex->getStatus() << "] "<< endl;
			cout << "Solution primal cost = " << primal << endl;
			cout << "Solution dual cost = " << dual << endl ;
			cout << "Soution with delay = " << SolucaoReal << endl;
			cout << "Gap = " << gap << "%" << endl ;
			cout << "Tempo = " << tempo << " segundos. " << endl<< endl;
		}

		if( EscreveArquivoComRespostas == 1){
			logfile2 <<  "Solution status = " << " [" << cplex->getStatus() << "] "<< endl;
			logfile2 << "Solution primal cost = " << primal << endl;
			logfile2 << "Solution dual cost = " << dual << endl ;
			logfile2 << "Soution with delay = " << SolucaoReal << endl;
			logfile2 << "Gap = " << gap  << "%" << endl ;
			logfile2 << "Tempo = " << tempo << " segundos. " << endl << endl;
		}

		if( EscreveVariaveis == 1){
	// Imprimi Variaveis
			EscreveVariaveisAlfaDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Alfa);
			EscreveVariaveisBetaDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Beta);
			EscreveVariaveisBetaProducaoDoModeloAposResolucao(		EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, BetaProducao);
			EscreveVariaveisTveiDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Tvei);
			EscreveVariaveisTPveiDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, TPvei);
			EscreveVariaveisZeDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Ze);

		}

		if( OutPut1 == 1){
	// Itinerario dos veiculos
			EscreveItinerarioVeiculos( EscreveNaTelaResultados, EscreveArquivoComRespostas, logfile2,	*cplex, Alfa,  Tvei, TPvei);
		}

		if( OutPut2 == 1){
	// Tempo de cada entrega em cada cliente
			EscreveEntregasNosClientes(EscreveNaTelaResultados,EscreveArquivoComRespostas, logfile2,	*cplex, Alfa,  Tvei);
	// Veiculos usados
			EscreveUtilizacaoVeiculos( EscreveNaTelaResultados,EscreveArquivoComRespostas, logfile2,	*cplex, Alfa,  Tvei);
		}

		logfile1.close();
		logfile2.close();

		//model.end();				// problema, trava o programa. olhar! falam que demora muito. que é melhor deletar o objeto IloClpex

		delete(cplex);

		Alfa.clear();
		Beta.clear();
		BetaProducao.clear();
		Ze.clear();
		Tvei.clear();
		TPvei.clear();
		TPvei.clear();
		EscreveRestricao.clear();



		return (1);
	}
}

#endif /* MODELOINICIOHEURISTICA_HPP_ */
