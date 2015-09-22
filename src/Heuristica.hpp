/*
 * Heuristica.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef HEURISTICA_HPP_
#define HEURISTICA_HPP_

#include "Bibliotecas.hpp"

class Heuristica{

public:
	Heuristica();

	ifstream arq;
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	int  LeDados(string, int );

	void ExecutaProcedimentoHeuristico1();

	void LeNomeInstancia(int , string& );
	void LeNumeroPlantasEntregasVeiculos(int);
	void LeVelocidade(int);
	void LeTempoDeVidaConcreto(int);
	void LeVeiculosPorPlanta(int);
	void LeNumeroDemandas(int);
	void LeDistancias(int);
	void LeTempoConstrucao(int);
	void LeTempoPlanta(int);
	void LeTempoMaximoEntreDescargas(int);
	void LeTempoMaximoMinimoConstrucoes(int);
	void LeTempoMaximoMinimoPlantas(int);
	void CalculoRankTempoDemanda(int);


    ~Heuristica();

};

Heuristica::Heuristica(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;

}

int Heuristica::LeDados(string Nome, int comentarios){

	string Instancia;
	string CaminhoArquivo1;


// Abre arquivo das instâncias

	CaminhoArquivo1 = "./InstS/";
	CaminhoArquivo1 += Nome;

	cout << " Arquivo a abrir : " << CaminhoArquivo1.c_str() << endl;

	arq.open(CaminhoArquivo1.c_str());
	if (arq.is_open()){
		LeNomeInstancia(comentarios, Instancia);
		LeNumeroPlantasEntregasVeiculos(comentarios);
		LeVelocidade(comentarios);
		LeTempoDeVidaConcreto(comentarios);
		LeVeiculosPorPlanta( comentarios);
		LeNumeroDemandas(comentarios);
		LeDistancias(comentarios);
		LeTempoConstrucao(comentarios);
		LeTempoPlanta(comentarios);
		LeTempoMaximoEntreDescargas(comentarios);
		LeTempoMaximoMinimoConstrucoes(comentarios);
		LeTempoMaximoMinimoPlantas(comentarios);
		CalculoRankTempoDemanda(comentarios);

		arq.close();

		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << CaminhoArquivo1 << endl << endl;
		return 0;
	}
}

void Heuristica::ExecutaProcedimentoHeuristico1(){
	Procedimento1 Prod1;
	int Solucao;
	Solucao = 0;

	bool TarefaDeletada;
	bool TarefaAlocada;

	ConjuntoSolucoes Solucoes;

	int NovatarefaAlocadaConstrucao;
	int NovatarefaAlocadaDemanda;

	int InviabilidadeSolucaoAnterior;

	int Readicionou;

	int ConstrucaoAnalisandoRetirada;
	int DemandaAnalisandoRetirada;

	bool ExisteTarefa;

	int PararPrograma;


	Prod1.CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

// Define a ordem de seleção da alocação inicial das atividades

	//sort ( Prod1.ConstrucoesInstancia.Construcoes.begin(), Prod1.ConstrucoesInstancia.Construcoes.end(), DecideQualContrucaoTemMaiorRank );
	sort ( Prod1.ConstrucoesInstancia.Construcoes.begin(), Prod1.ConstrucoesInstancia.Construcoes.end(), DecideQualContrucaoTemMenorInicioDepoisMaiorRank );

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

	Solucao = Prod1.Executa();

	if( Solucao == 1 ){
		cout << endl << endl << "  Solucao viavel!    " << endl << endl;
	}else{
		cout << endl << endl << "  Solucao inviavel!    " << endl << endl;
	}


	Solucoes.InsereSolucao(Prod1.NP, Prod1.PlantasInstancia, Prod1.NE, Prod1.ConstrucoesInstancia, Prod1.NV, Prod1.Velocidade, Prod1.TempoDeVidaConcreto);
	Solucoes.Imprime(0,1,0);


	InviabilidadeSolucaoAnterior = Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade;
	ExisteTarefa = Solucoes.Solucoes[0].ConstrucaoTarefaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

	do{

		cout << endl << "   Deleta tarefas [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl ;

		TarefaDeletada = Solucoes.Solucoes[0].DeletaAlocacaoTarefasPosteriores(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
		//TarefaDeletada = Solucoes.Solucoes[0].DetetaAlocacaoTarefa(0,0);
		Solucoes.Solucoes[0].MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

		//Solucoes.Imprime(0,1,0);


		if ( TarefaDeletada == 1){

			NovatarefaAlocadaConstrucao = -13;
			NovatarefaAlocadaDemanda = -13;

			cout << endl << "   Tenta adicionar " << endl ;

			TarefaAlocada = Solucoes.Solucoes[0].ProcessoParaAlocarTarefa( ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovatarefaAlocadaConstrucao , NovatarefaAlocadaDemanda);
			//Solucoes.Imprime(0,1,0);

			if( TarefaAlocada == 1){
				cout << "       -----> Tarefa alocada no novo espaço [" << NovatarefaAlocadaConstrucao << "-" << NovatarefaAlocadaDemanda << "]" << endl;
				Readicionou = Solucoes.Solucoes[0].ReadicionaTarefas(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
				//Solucoes.Imprime(0,1,0);

				if( InviabilidadeSolucaoAnterior > Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade){
					cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;
					Solucoes.Solucoes[0].MarcaTarefaNaoDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
					//Solucoes.Imprime(0,1,0);
				}else{
					cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;
					if( Readicionou == 1) {
						cout <<  endl << "  Deleta tarefas antigas recolocadas [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" <<  endl;
						TarefaDeletada = Solucoes.Solucoes[0].DeletaAlocacaoTarefasPosteriores(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
						//Solucoes.Imprime(0,1,0);
					}
					cout <<  endl << "  Deleta tarefa adicionada [" << NovatarefaAlocadaConstrucao << "-" << NovatarefaAlocadaDemanda << "]" <<  endl;
					TarefaDeletada = Solucoes.Solucoes[0].DetetaAlocacaoTarefa(NovatarefaAlocadaConstrucao , NovatarefaAlocadaDemanda);
					//Solucoes.Imprime(0,1,0);
					cout <<  endl << "  Recoloca tarefas antigas para refazer solucao inicial [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" <<  endl;
					Solucoes.Solucoes[0].ReadicionaTarefas(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
					//Solucoes.Imprime(0,1,0);
				}
			}else{
				cout << endl << endl << "   Nao consegui adicionar nova tarefa" << endl << endl;
				//Solucoes.Imprime(0,1,0);
				Solucoes.Solucoes[0].ReadicionaTarefas(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
				Solucoes.Imprime(0,1,0);
			}
		}else{
			 cout << endl << endl << endl << "   #######################  Tarefa nao deletada ######################## " << endl << endl << endl;
		}



		InviabilidadeSolucaoAnterior = Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade;

		ExisteTarefa = Solucoes.Solucoes[0].ConstrucaoTarefaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

		if( ExisteTarefa == 1){
			cout << " Selecionou a Analisar [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "] ";
			cout << "( situacao demanda = " << Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[ConstrucaoAnalisandoRetirada].SituacaoDemanda[DemandaAnalisandoRetirada] << " e ";
			cout << "situacao remocao = " << Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[ConstrucaoAnalisandoRetirada].SituacaoRemocao[DemandaAnalisandoRetirada]  << ")" << endl;
		}
		Solucoes.Imprime(1,1,0);

		cin >> PararPrograma;

	}while( ExisteTarefa == 1);

	Solucoes.Imprime(1,1,0);

}


void Heuristica::LeNomeInstancia(int comentarios, string& Instancia){
	arq >> Instancia;
	if( comentarios == 1){
		cout << " Nome instancia "<<  Instancia << endl;
	}
}

void Heuristica::LeNumeroPlantasEntregasVeiculos(int comentarios){
	arq >> NP;
	PlantasInstancia.IniciaConjuntoPlantas(NP);
	for( int p = 0; p < NP; p++){
		PlantasInstancia.Plantas[p].NumeroDaPlanta = p;
		//cout << "    Imputa numero planta = " << p+1 << endl;
	}
	arq >> NE;
	ConstrucoesInstancia.IniciaConjuntoConstrucoes(NE);
	for( int c = 0; c < NE; c++){
		ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao = c;
		//cout << "    Imputa numero construcao = " << c+1 << endl;
	}
	arq >> NV;

	if( comentarios == 1){
		cout << " Numero de plantas "<<  NP << endl;
		cout << " Numero de Entregas "<< NE << endl;
		cout << " Numero de Veiculos "<< NV << endl;
	}
}

void Heuristica::LeVelocidade(int comentarios){
	arq >> Velocidade;
	if( comentarios == 1){
		cout << " Velocidade "<<  Velocidade << endl;
	}
}

void Heuristica::LeTempoDeVidaConcreto(int comentarios){
	arq >> TempoDeVidaConcreto;
	if( comentarios == 1){
		cout << " Tempo De Vida Concreto "<<  TempoDeVidaConcreto << endl;
	}
}

void Heuristica::LeVeiculosPorPlanta(int comentarios){
	int aux;
	for (int i = 0; i < NP ; i++){
		arq >> PlantasInstancia.Plantas[i].NumeroVeiculos;
		PlantasInstancia.Plantas[i].VeiculosDaPlanta.IniciaConjuntoCarretas( PlantasInstancia.Plantas[i].NumeroVeiculos, PlantasInstancia.Plantas[i].NumeroDaPlanta );
		if( comentarios == 1){
			cout << " Numero de veiculo na planta  " << i + 1 << " = " << PlantasInstancia.Plantas[i].NumeroVeiculos << "  ( ";
		}
		for ( int j = 0; j < PlantasInstancia.Plantas[i].NumeroVeiculos; j++){
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}

}

void Heuristica::LeNumeroDemandas(int comentarios){
	int aux;
	for (int i = 0; i < NE ; i++){
		arq >> ConstrucoesInstancia.Construcoes[i].NumeroDemandas;
		ConstrucoesInstancia.Construcoes[i].SituacaoDemanda.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		ConstrucoesInstancia.Construcoes[i].SituacaoRemocao.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		for( int d = 0; d < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; d++){
			ConstrucoesInstancia.Construcoes[i].SituacaoDemanda[d] = 0;
			ConstrucoesInstancia.Construcoes[i].SituacaoRemocao[d] = 0;
		}
		if( comentarios == 1){
			cout << " Numero de demandas na construção " << i + 1 << " = " << ConstrucoesInstancia.Construcoes[i].NumeroDemandas << "  ( ";
		}
		for ( int j = 0; j < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; j++){
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}
}

void Heuristica::LeDistancias(int comentarios){
	if( comentarios == 1){
		cout << "     Distancia Planta para Construcoes"<< endl;
	}
	for (int p = 0; p < NP ; p++){
		PlantasInstancia.Plantas[p].DistanciaConstrucoes.resize(NE);
		for ( int c = 0; c < NE; c++){
			arq >> PlantasInstancia.Plantas[p].DistanciaConstrucoes[c];
			if( comentarios == 1){
				cout << PlantasInstancia.Plantas[p].DistanciaConstrucoes[c] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	}
	if( comentarios == 1){
		cout << "     Distancia Construcoes para Plantas"<< endl;
	}
	for (int c = 0; c < NE ; c++){
		ConstrucoesInstancia.Construcoes[c].DistanciaPlantas.resize(NP);
		for ( int p = 0; p < NP; p++){
			arq >> ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
			ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].PlantaComparada = &PlantasInstancia.Plantas[p];
			if( comentarios == 1){
				cout <<  ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}

}

void Heuristica::LeTempoConstrucao(int comentarios){
	int aux;

	if( comentarios == 1){
		cout << "     Tempo de cada veiculo em cada cosntrucao "<< endl;
	}
	for (int p = 0; p < NP ; p++){
		for (int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos ; v++){
			arq >> aux;
			if( comentarios == 1){
				cout << " Veiculo  " << aux << endl;
			}
			PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao.resize( NE);
			for ( int c = 0; c < NE; c++){
				arq >> aux;
				if ( aux != ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
					cout << "        ############## Dados Incosistentes ############## " << endl << endl;
				}
				PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c].resize( ConstrucoesInstancia.Construcoes[c].NumeroDemandas );
				for ( int d = 0; d < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; d++){
					arq >> PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c][d];
					if( comentarios == 1){
						cout << PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c][d] << "  ";
					}
				}
				if( comentarios == 1){
					cout << endl;
				}
			}
		}

	}
}

void Heuristica::LeTempoPlanta(int comentarios){
	for (int p = 0; p < NP ; p++){
		arq >> PlantasInstancia.Plantas[p].TempoPlanta;
		if( comentarios == 1){
			cout << " Tempo na Planta " << p +1 << " = " <<  PlantasInstancia.Plantas[p].TempoPlanta << endl;
		}
	}
}

void Heuristica::LeTempoMaximoEntreDescargas(int comentarios){
	if( comentarios == 1){
		cout << "     Tempo maximo entre descargas " << endl;
	}
	for ( int c = 0; c < NE; c++){
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas;
		if( comentarios == 1){
			cout << " Construcao " << c + 1 << " = " <<  ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas << endl;
		}
	}
}

void Heuristica::LeTempoMaximoMinimoConstrucoes(int comentarios){
	for ( int c = 0; c < NE; c++){
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento;
	}
	for ( int c = 0; c < NE; c++){
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento;
	}
	if( comentarios == 1){
		cout << "     Intervalo de Funcionamento Construcoes " << endl;
		for ( int c = 0; c < NE; c++){
			cout << c + 1 << " ( " << ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento << " - " << ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento << " ) " << endl;
		}
	}
}

void Heuristica::LeTempoMaximoMinimoPlantas(int comentarios){
	for ( int p = 0; p < NP; p++){
		arq >> PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
	}
	for ( int p = 0; p < NP; p++){
		arq >> PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento;
	}
	if( comentarios == 1){
		cout << "     Intervalo de Funcionamento Plantas " << endl;
		for ( int p = 0; p < NP; p++){
			cout << p + 1 << " ( " << PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento << " - " << PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento << " ) " << endl;
		}
	}
}

void Heuristica::CalculoRankTempoDemanda(int comentarios){
	for ( int c = 0; c < NE; c++){
		if( comentarios == 1){
			cout << " Construcao " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " com";
		}
		ConstrucoesInstancia.Construcoes[c].CalculaRankTempoDemandas( comentarios );
	}
}

Heuristica::~Heuristica(){

}

#endif /* HEURISTICA_HPP_ */
