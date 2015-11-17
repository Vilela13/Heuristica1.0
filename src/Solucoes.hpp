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



#define ItCarregamento 		vector< Carregamento 	>::iterator
#define ItDescarregamento 	vector< Descarregamento >::iterator
#define ItDeslocamento 		vector< Deslocamento 	>::iterator

class Solucao{
public:
	Solucao();

	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	double Makespan;

// Funções interanas


// Mudado

	void EncontraPlantaMenorDistanciaConstrucao(int, int&, string);
	void CarregaSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);

	void MarcaTarefaDeletadaNoVetor(int, int, int);

	void Imprime(bool, bool, bool);

	int RetornaIndiceConstrucao(int, int&, string);
	int ConstrucaoTarefaRemover(int&, int&, int);
	int DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int, int, vector < DadosTarefa >&);

	int AdicionaTarefa( int, int, vector < DadosTarefa >&, int, int) ;

	int ProcessoParaAlocarTarefaNaoAtendida( int, int, int&, int&, vector < DadosTarefa >&, int, int);
	void ReadicionaTarefas(int, vector < DadosTarefa >&, int, int);

	void MarcaTarefaNaoDeletadaNoVetor(int, int);

	int ReadicionaTarefasApartirDeDados( vector < DadosTarefa >, int);

	int DeletaTarefasApartirDeDados( vector < DadosTarefa >);

	void ProcessoViabilizacao1(int );


	// Mudando

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


// Mudado

void Solucao::EncontraPlantaMenorDistanciaConstrucao( int c, int& NumPlantaAnalisando, string frase){
	double DistanciaConstrucaoPlanta;

	NumPlantaAnalisando = -13;
	DistanciaConstrucaoPlanta = DBL_MAX;
	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
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
void Solucao::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
}

void Solucao::MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda, int Situacao){
	int c;

	if( RetornaIndiceConstrucao(Construcao, c, "Solucao::MarcaTarefaDeletadaNoVetor")== 1 ){

		ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[Demanda] = Situacao;
		//cout << endl << endl << "  marquei " << endl << endl;
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

int Solucao::RetornaIndiceConstrucao(int Construcao, int& Indice, string frase){
	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			Indice = i;
			return 1;
		}
	}
	cout << endl << endl << "   Não encontrou indice construção [" << Construcao << "]";
	cout << frase << endl << endl;
	return 0;
}

int Solucao::ConstrucaoTarefaRemover(int& Construcao, int& Demanda, int Imprimir){
	// Verifica se possui uma construção que possui demandas que ainda não foram retiradas para se tentar a viabilização da solução. Caso possuir, retorna 1 a função e é retornado os dados da construção e da demanda por parametro.

	//ConstrucoesInstancia.ImprimeContrucoes();
	int Ativo;
	double RankInicial;
	AlocaValoresIniciaisIndices( Construcao, Demanda );

	Ativo = 0;
	RankInicial = DBL_MAX;

	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			for( int d = (ConstrucoesInstancia.Construcoes[c].NumeroDemandas - 1); d >= 0 ; d--){
				if(ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[d] == 1){
					if( ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] == 0){
						Construcao = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
						Demanda = d;
						RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
						Ativo = 1;
					}
				}
			}
		}
	}
	if( Ativo == 1){
		if( Imprimir == 1){
			cout << " Selecionou construcao " << Construcao << "-" << Demanda << " com janela de tempo ";
			cout <<  ConstrucoesInstancia.Construcoes[Construcao].TempoMinimoDeFuncionamento << "-" << ConstrucoesInstancia.Construcoes[Construcao].TempoMaximoDeFuncionamento;
			cout << " -> ConstrucaoTarefaRemover" << endl ;
		}
		return 1;
	}else{
		return 0;
	}
}

int Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasDesalocadas){
		 int c;

		 if( RetornaIndiceConstrucao(Construcao, c, " -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao" ) == 1){
			 if( ConstrucoesInstancia.Construcoes[c].DeletaTarefas(  Demanda, DadosTarefasDesalocadas, PlantasInstancia) == 0 ){
				 cout << endl << endl << "   problema em retirar tarefas -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao " << endl << endl;
				 return 0;
			 }

			 //cout << endl << endl;
			 //ConstrucoesInstancia.Construcoes[c].ImprimeContrucao();

			 return 1;
		 }
		 return 0;

}


int Solucao::AdicionaTarefa( int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda, int TipoOrdenacao){

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
	if( RetornaIndiceConstrucao(Construcao, c, " Solucao::AdicionaTarefa") == 1 ){

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
									ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta, 0, SituacaoDemanda, PlantasInstancia, DadosTarefasAdicionadas);
									ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
									return 1;
								}

							}
						}
						HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
					}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
				}
				PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] = 1;
			}while( PlantasInstancia.AnalizouTodasPLanats() == 0);
			//cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]   -> AdicionaTarefa &&&&&&&&&&&&& " << endl;
			return 0;

		}else{
			cout << endl << endl << endl << "   &&&&&&&&&&&&& Construcao [" << c << "-" << Demanda << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
			return 0;
		}

	}
	return 0;

}


int Solucao::ProcessoParaAlocarTarefaNaoAtendida( int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda, int TipoOrdenacao){
	int c;
	int d;

	int Alocou;
	Alocou = 0;

	if( RetornaIndiceConstrucao(Construcao, c, "  <<<<    Solucao::ProcessoParaAlocarTarefa  >>>>>") == 0){
		return -1;
	}


	for( unsigned int contrucoes = 0; contrucoes < ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas; demandas++){
			if( contrucoes != c){
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					//cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "]  -> Solucao::ProcessoParaAlocarTarefa";
					Alocou = AdicionaTarefa(ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas, DadosTarefasAdicionadas, SituacaoDemanda, TipoOrdenacao);

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

void Solucao::ReadicionaTarefas( int construcao, vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda, int TipoOrdenacao){
	int c;

	if( RetornaIndiceConstrucao( construcao, c, " Solucao::ReadicionaTarefas") == 1 ){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
				//cout << " entrei " << endl;
				if( AdicionaTarefa(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, DadosTarefasAdicionadas, SituacaoDemanda, TipoOrdenacao) == 1 ){
					//cout << " adicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
				}else{
					//cout << " Nao readicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
				}
			}
		}
	}

}

void Solucao::MarcaTarefaNaoDeletadaNoVetor(int Construcao, int Demanda){
	int c;

	if( RetornaIndiceConstrucao( Construcao, c, " Solucao::ReadicionaTarefas") == 1 ){
		ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[Demanda] = 0;
	}
}

int Solucao::ReadicionaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasDesalocadas, int SituacaoDemanda){

	int c;

	for(unsigned int i = 0; i < DadosTarefasDesalocadas.size(); i++){

		if( RetornaIndiceConstrucao( DadosTarefasDesalocadas[i].DadosDasTarefas[0]  , c, " Solucao::DeletaTarefasApartirDeDados") == 0 ){
			return 0;
		}
		ConstrucoesInstancia.Construcoes[c].AlocaAtividade( DadosTarefasDesalocadas[i].HorariosDasTarefas[2],DadosTarefasDesalocadas[i].HorariosDasTarefas[3], DadosTarefasDesalocadas[i].DadosDasTarefas[2], DadosTarefasDesalocadas[i].DadosDasTarefas[1], 0, SituacaoDemanda, PlantasInstancia);
		ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;

	}
	//ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	return 1;

}


int Solucao::DeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasAdicionadas ){
	int c;

	for(unsigned int i = 0; i < DadosTarefasAdicionadas.size(); i++){

	// encontra indices
		if( RetornaIndiceConstrucao( DadosTarefasAdicionadas[i].DadosDasTarefas[0]  , c, " Solucao::DeletaTarefasApartirDeDados") == 0 ){
			return 0;
		}

		ConstrucoesInstancia.Construcoes[c].DeletaTarefasAnteriormenteAdicionadasDados( DadosTarefasAdicionadas[i], PlantasInstancia);
		ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade + 1;
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

	vector < DadosTarefa > DadosTarefasDesalocadas;
	vector < DadosTarefa > DadosTarefasAdicionadas;
	vector < DadosTarefa > AuxiliarLixo;


	//ConstrucoesInstancia.ImprimeContrucoes();
	//PlantasInstancia.Imprime(1,1);

	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	ExisteTarefa = ConstrucaoTarefaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 0);		// Encontra primeira tarefa que pode ser retirada

	if( ExisteTarefa == 1){
		do{
			DadosTarefasDesalocadas.clear();
			TarefaDeletada = DeletaAlocacaoTarefasPosterioresMesmaConstrucao(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, DadosTarefasDesalocadas);	// Deleta tarefa
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			/*
			cout << "DadosTarefasDesalocadas" << endl;
			ImprimeVetorDadosTarefa( DadosTarefasDesalocadas);
			cout << "DadosTarefasAdicionadas" << endl;
			ImprimeVetorDadosTarefa( DadosTarefasAdicionadas);

			ConstrucoesInstancia.ImprimeContrucoes();
			PlantasInstancia.Imprime(1,1);
			*/

			if ( TarefaDeletada == 1){
				// Aloca nova tarefa que não era alocada antes
				AlocaValoresIniciaisIndices( NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);

				//ConstrucoesInstancia.ImprimeContrucoes();

				//cout << endl << endl << "       Aloca tarefa " << endl << endl;

				TarefaAlocada = ProcessoParaAlocarTarefaNaoAtendida( ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovaTarefaAlocadaConstrucao , NovaTarefaAlocadaDemanda,  DadosTarefasAdicionadas, 0, TipoOrdenacao);
				ConstrucoesInstancia.CalcularNivelDeInviabilidade();

				/*
				 ConstrucoesInstancia.ImprimeContrucoes();

				cout << endl << "  tenta alocar tarefa" << endl;
				cout << "DadosTarefasDesalocadas" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasDesalocadas);
				cout << "DadosTarefasAdicionadas" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasAdicionadas);

				cin >> PararPrograma;
				 */

				if( TarefaAlocada == 1){

					//cout << endl << endl << "         Readiciona " << endl << endl;

					ReadicionaTarefas( ConstrucaoAnalisandoRetirada, DadosTarefasAdicionadas, 0, TipoOrdenacao);
					ConstrucoesInstancia.CalcularNivelDeInviabilidade();

					/*
					cout << endl << "  Realocar tarefas" << endl;
					cout << "DadosTarefasDesalocadas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasDesalocadas);
					cout << "DadosTarefasAdicionadas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasAdicionadas);

					ConstrucoesInstancia.ImprimeContrucoes();

*/
					//cin >> PararPrograma;


					if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
						cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;

						ConstrucoesInstancia.ImprimeContrucoes();
						PlantasInstancia.Imprime(1,1);

						MarcaTarefaNaoDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
						DadosTarefasDesalocadas.clear();
						DadosTarefasAdicionadas.clear();

					}else{
						//cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;

/*
						cout << "DadosTarefasDesalocadas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasDesalocadas);
						cout << "DadosTarefasAdicionadas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasAdicionadas);
*/

						//cout << endl <<" aqui1" << endl ;

						if( DeletaTarefasApartirDeDados(  DadosTarefasAdicionadas ) == 0){
							cout << endl << endl << "   problema em deletar " << endl << endl;
						}
						//cout << endl <<" aqui2" << endl ;
						if( ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas, 1) == 0){
							cout << endl << endl << "   problema em realocar " << endl << endl;
						}
						//cout << endl <<" aqui3" << endl ;
						DadosTarefasDesalocadas.clear();
						DadosTarefasAdicionadas.clear();

						MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);

						//ConstrucoesInstancia.ImprimeContrucoes();
						//PlantasInstancia.Imprime(1,1);

						//cin >> PararPrograma;

					}
				}else{
					//cout << endl << endl << "            Nao consegui adicionar nova tarefa" << endl << endl;
					ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas, 1);
					DadosTarefasDesalocadas.clear();

					MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);

					//ConstrucoesInstancia.ImprimeContrucoes();
					//PlantasInstancia.Imprime(1,1);

					//cin >> PararPrograma;
				}
			}else{
				 cout << endl << endl << endl << "   #######################  Tarefa nao deletada ######################## " << endl << endl << endl;
			}

			InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
			ExisteTarefa = ConstrucaoTarefaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 0);

			//cout << endl << endl << " ExisteTarefa = " << ExisteTarefa << " ConstrucoesInstancia.NivelDeInviabilidade = " << ConstrucoesInstancia.NivelDeInviabilidade << endl << endl;

		}while( ExisteTarefa == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0);
	}




}

//  Mudando

int Solucao::SelecionaConstrucao( int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucaosAnalizadas){
	double RankInicial;
	int Ativo;

	Ativo = 0;
	RankInicial = DBL_MAX;


	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
				if( ConstrucaosAnalizadas[c] == 0){
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

// Aloca o tempo inicial que se pode sair da planta como sendo o tempo da ultima carreta que realizou o ultimo carregamento na quela planta para está construção
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

void Solucao::SinalizaTarefaAdicionadaInicialmente( int TarefaAdicionada, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendida){
		if( TarefaAdicionada == 1){
			//cout << "                  Tarefa adicionada    -> Solucao::SinalizaTarefaAdicionadaInicialmente" << endl << endl;
			ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] = 2;
			MarcaTarefaDeletadaNoVetor(ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDaConstrucao, DemandaNaoAtendida, 2);
		}else{
			cout << "                  Tarefa NAO adicionada " << endl << endl;
			for( int d = DemandaNaoAtendida; d < ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDemandas; d++){
				ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ d ] = -1;
				MarcaTarefaDeletadaNoVetor(ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDaConstrucao, d, 3);
			}
		}
}

int Solucao::SelecionaCarreta(int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas, int TipoOrdenacao ){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	int ParaPrograma;

	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[NumeroDemanda] == 0){

		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);

		for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){

			if( (ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta) > PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta;
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

int Solucao::SelecionaCarretaComHoraInicio( double HoraInicio, int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas , int TipoOrdenacao){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	int ParaPrograma;

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

	HorarioInicioConstrucao = HoraInicio + IntervaloDeTempo;

	SituacaoPlantas.resize(NP);					// Vetor que armazena se a planta foi analisada ou não para atender certa demanda
	SituacaoDemandas.resize(demanda + 1); 		// Tem que somar mais um pelo fato de se contar o 0 como um elemento

	while(HorarioInicioConstrucao <  ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento ){

		if ( Imprime == 1){
			cout << "  HorarioInicioConstrucao " << HorarioInicioConstrucao << " / " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento << endl;
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
			ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);
			TemporarioAdiciona.clear();
			HorarioInicioConstrucao = HorarioInicioConstrucao + IntervaloDeTempo;
		}else{
			ImprimeVetorInt( SituacaoPlantas);
			ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);
			TemporarioAdiciona.clear();
			return 0;
		}
	}

	if ( Imprime == 1){
		cout << endl << endl << "  Não da para atrazar " << endl << endl;
	}
	TemporarioAdiciona.clear();
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

	int TarefaAdicionadaAposDeslocamentoTarefas;

	int Imprime;
	int PararPrograma;

	Imprime = 1;

// Encontra demanda ainda não atendida

	ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();

	while( ConstrucoesInstancia.VerificaConstrucaoPodeAtender() == 1){


		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
		ConstrucoesInstancia.ReiniciaTarefasRetiradas();
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);
		TempoSaiPlanta.resize(NP);
		if( Imprime == 1){
			cout << " ConstrucaoNaoAtendida = " << ConstrucaoNaoAtendida <<" DemandaNaoAtendida = " << DemandaNaoAtendida << endl << endl;
		}
		RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );

	// deleta tarefas que são atendidas antes desta tarefa não alocada
		AlocaTempoSaiDaPlanta(IndiceConstrucaoNaoAtendida,TempoSaiPlanta, 0);
		DeletouAlgumaTarefa = DeletaTarefasAposTempoSaiPlanta(TempoSaiPlanta, DadosTarefasDesalocadas,  0);
		if( Imprime == 1){
			cout << "   <<<<<<<<<<< Deteta tarefas >>>>>>>>>>>>>> ";
			ConstrucoesInstancia.ImprimeContrucoes();
			cin >> PararPrograma;
		}


	// Adiciona a tarefa que não era alocada antes
		TarefaAdicionada = AdicionaTarefa( ConstrucaoNaoAtendida, DemandaNaoAtendida, DadosTarefasAdicionadas, 2, TipoOrdenacao);
		SinalizaTarefaAdicionadaInicialmente( TarefaAdicionada, IndiceConstrucaoNaoAtendida, DemandaNaoAtendida);
		if( ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] == -1){
			if( Imprime == 1){
				cout << endl << endl << "   Não consigo alocar tarefa [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] que não foi alocada antes -> Solucao::ProcessoViabilizacao2 " << endl << endl;
			}
			ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas, 1);
			DadosTarefasDesalocadas.clear();
			ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();
			ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 4;
		}else{

			if( Imprime == 1){
				cout << "   <<<<<<<<<<< Coloca tarfea não alocada anterioremnte [" <<  ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "]  >>>>>>>>>>>>>>> ";
				ConstrucoesInstancia.ImprimeContrucoes();
				ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);
				cin >> PararPrograma;
			}

	// marca construções com tarefas a alocar
			ConstrucoesInstancia.InicializaConstrucaosAnalizadas();
			ConstrucoesInstancia.AlocaValoresConstrucaosAnalizadas( IndiceConstrucaoNaoAtendida);
	// Verifica se tem tarefa a se colocar
			PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucaosAnalizadas);
			//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1, ConstrucoesInstancia.ConstrucaosAnalizadas, 0);
			if( Imprime == 1){
				cout << "   <<<<<<<<<<< Readiciona demandas   >>>>>>>>>>>>>>> " << endl;
			}
			//cin >> PararPrograma;

			while( PossuiConstrucaoParaAnalisar == 1){
				ConstrucoesInstancia.ConstrucaosAnalizadas[ConstrucaoParaAtenderIndice] = 1;
				d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;
				if( Imprime == 1){
					cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]";
				}
				PlantasInstancia.InicializaPlantasAnalizadas();
				ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);
				//cin >> PararPrograma;
				while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
					//cout << "     		Tenta Planta " << PlantaAtender << " [" << PlantaAtenderIndice << "]" << endl;
					PlantasInstancia.PlantasAnalizadas[PlantaAtenderIndice] = 1;
					PermiteAtendimentoDemanda = SelecionaCarreta(ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, DadosTarefasAdicionadas , TipoOrdenacao);
					//ConstrucoesInstancia.ImprimeContrucoes();
					//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);

					if( PermiteAtendimentoDemanda == 1){
						cout << "      Atendida " << endl;
						//cout << "             +++++   Planta [" << PlantaAtenderIndice << "] " << PlantasInstancia.Plantas[PlantaAtenderIndice].NumeroDaPlanta << "  atende demanda " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
							d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;
								if( Imprime == 1){
									if( d != ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
										cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]" ;
									}
								}
								PlantasInstancia.InicializaPlantasAnalizadas();
								ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
						}else{
							PlantasInstancia.InicializaPlantasAnalizadas();
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
						}
					}else{
						if( PermiteAtendimentoDemanda == 0){
							PlantasInstancia.PlantasAnalizadas[PlantaAtender] = 1;
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
						}
						if ( PermiteAtendimentoDemanda == -2){
							PlantasInstancia.PlantasAnalizadas[PlantaAtender] = -2;
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
						}


// Verifica se pode atrazar

						if( ConstrucaoParaAtender == 0 && d == 1 ){
							cout << endl << endl << "                Antes de entrar [" << ConstrucaoParaAtender << "-" << d << "]" << endl;
							ImprimeVetorInt(PlantasInstancia.PlantasAnalizadas);
						}



						if( ExistePlanta == 0 && PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento >= 1){
							if( Imprime == 1){
								cout << endl << endl << "   	Pode atrazar tarefas da construção " << ConstrucaoParaAtender << " [" << ConstrucaoParaAtenderIndice << "] - d = " << d << " para alocar outra " << endl << endl;
							}

							ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, DadosRetirandoAux);
							ConseguiAlocarTarefa = ColocarTarefaAtrazandoAsOutras( ConstrucaoParaAtenderIndice, d , HoraInicio, DadosAdicionaAux, TipoOrdenacao, Imprime);

							if( ConseguiAlocarTarefa == 1){

								PermiteAtendimentoDemanda = 1;
								cout << endl << "      Atendida apos atrazar" << endl;
								if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
									d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;
									if( Imprime == 1){
										if( d != ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
											cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]" ;
										}
									}
									PlantasInstancia.InicializaPlantasAnalizadas();
									ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
								}else{
									PlantasInstancia.InicializaPlantasAnalizadas();
									ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
								}



								for( int i = 0; i < DadosRetirandoAux.size();i++){
									if( VerificaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas ,DadosRetirandoAux[i] ) == 1){
										if( RetiraElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas, DadosRetirandoAux[i]) == 0){
											cout << "    Não retirou " << endl;
											//DadosRetirandoAux[i].Imprimir();
											//cout << "             DadosRetirandoAux" << endl ;
										}
									}else{
										if( AdicionaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas, DadosRetirandoAux[i]) == 0){
											cout << "    Naõ adicionou " << endl;
											//DadosRetirandoAux[i].Imprimir();
											//cout << "             DadosRetirandoAux" << endl ;
										}
									}
								}
								for( int i = 0; i < DadosAdicionaAux.size();i++){
									if( AdicionaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas, DadosAdicionaAux[i] ) == 0){
										//cout << "    Naõ adicionou " << endl;
										//DadosRetirandoAux[i].Imprimir();
										//cout << "             DadosAdicionaAux" << endl ;
									}
								}
							}else{
								ReadicionaTarefasApartirDeDados( DadosRetirandoAux, 1);
							}

							//cout << endl << endl << "    depois de atualizar vetores " << endl << endl;
							//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);

							//cin >> PararPrograma;


						}

					}


					if( ExistePlanta == 0 ){
						cout << "     -> Não atendida" << endl;
						//cout << " Nao se pode colocar tarefa da construcao [" << ConstrucaoParaAtenderIndice << "] " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						ConstrucoesInstancia.ConstrucaosAnalizadas[ConstrucaoParaAtenderIndice] = 4;
						//ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
						//ConstrucoesInstancia.ImprimeContrucoes();


					}
				}
				PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucaosAnalizadas);
				//ConstrucoesInstancia.ImprimeContrucoes();
				//PlantasInstancia.Imprime(1,1);
				//cin >> PararPrograma;



			}

			cin >> PararPrograma;
			ConstrucoesInstancia.ImprimeContrucoes();
			//PlantasInstancia.Imprime(1,1);

			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			if( InviabilidadeSolucaoAnterior < ConstrucoesInstancia.NivelDeInviabilidade){
				cout << endl << endl << "    Melhoru !!!!!!" << endl << endl;
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();

			}else{
				if( Imprime == 1){
					cout << endl << endl << "    Não melhoru !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes();
					cin >> PararPrograma;
				}
				if( DeletaTarefasApartirDeDados(  DadosTarefasAdicionadas ) == 0){
					cout << endl << endl << "   problema em deletar " << endl << endl;
				}
				//cout << endl <<" aqui2" << endl ;
				if( ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas, 1) == 0){
					cout << endl << endl << "   problema em realocar " << endl << endl;
				}
				//cout << endl <<" aqui3" << endl ;
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();
				ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 3;
			}

			//cin >> PararPrograma;
		}

	}


}


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
