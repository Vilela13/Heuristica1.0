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

	int AlocaIndicesCeD( int&, int&, int, int, string);
	int AlocaIndicesPeV( int&, int&, int, int, string);
	void RetornaIndicePlanta(int, int&);

	void RetornaIndiceVeiculo(int, int, int&);
	int VerificaIteradorDescarregamento( ItDescarregamento, double, double, int, int, int);
	int VerificaIteradorCarregamento( ItCarregamento, int, int, int);

	int VerificaIteradorDeslocamento( ItDeslocamento, int, int);
	void EncontraPlantaMenorDistanciaConstrucao(int, int&, string);
	void CarregaSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);

	int RetornaDadosTarefa(int,int,int&, int&, double&, double&, double&, double&, double&);
	void DeletaTarefaConstrucao(ItDescarregamento,int, int);

	void DeletaTarefaCarreta(ItDeslocamento, int, int);
	void MarcaTarefaDeletadaNoVetor(int, int, int);
	int AdicionaTarefaHorarioInicioDescarregamento( int, int, double, vector < DadosTarefa >&, int) ;

	void AlocaIndicesDadosParaReorganizar(int, int&, int&,  int&, vector < DadosTarefa > );
	void InserirDadosEmEstruturaInstanciasDadosTarefasRetirar( vector < DadosTarefa >&, int, int);
	void RearrumaTarefasParaAdicionalas(int, int&, int, int, double, double, double, double, double, int);

	int ReadicionaTarefasHoraInicioDescarregamento(int, int , double, vector < DadosTarefa >&, int);

// Mudado

	void Imprime(bool, bool, bool);

	int RetornaIndiceConstrucao(int, int&, string);
	int ConstrucaoTarefaRemover(int&, int&, int);
	int DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int, int, vector < DadosTarefa >&);

	int AdicionaTarefa( int, int, vector < DadosTarefa >&, int) ;




	int ProcessoParaAlocarTarefaNaoAtendida( int, int, int&, int&, vector < DadosTarefa >&, int);
	void ReadicionaTarefas(int, vector < DadosTarefa >&, int);

	void MarcaTarefaNaoDeletadaNoVetor(int, int);
	void MarcaTarefaDeletadaNoVetor(int, int);
	int ReadicionaTarefasApartirDeDados( vector < DadosTarefa >, int);

	int DeletaTarefasApartirDeDados( vector < DadosTarefa >);

	void ProcessoViabilizacao1();









	int SelecionaConstrucao(int&, int&, vector < int >);
	int SelecionaPlanta(int&, int&, int, vector < int >);



	void IniciarVetorPlantasPodemAtenderTarefa( vector< int >&);
	void AlocaNovaDemandaParaAtender( int&, int, int&, int&,vector< int >&, int&, int);

	int MoveTarefasParaTentarAlocarTarefa(int, int, vector < DadosTarefa >&, vector < DadosTarefa > &);




	// Mudando
	int  ProcuraConstrucaoNaoAtendida(int&, int&);
	void AlocaTempoSaiDaPlanta(int , vector < double >&, int);
	int DeletaTarefasAposTempoSaiPlanta(vector < double >&, vector < DadosTarefa >&,  int );

	void SinalizaTarefaAdicionadaInicialmente( int, int, int);
	int SelecionaCarreta(int, int, int, int, vector < DadosTarefa >&);
	int SelecionaCarretaComHoraInicio(double, int, int, int, int, vector < DadosTarefa > &);

	int ColocarTarefaAtrazandoAsOutras(int , int , double, vector < DadosTarefa > &);

	void ProcessoViabilizacao2();


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


int Solucao::AlocaIndicesCeD( int &c, int &d, int Construcao, int Demanda, string frase){
	if( RetornaIndiceConstrucao( Construcao, c, " Solucao::ReadicionaTarefas") == 1 ){
			d = Demanda;
			return 1;
	}
	cout << endl << endl << "  preoblema em alocar Construcao [" << Construcao << "] e Demanda [" << Demanda << "]";
	cout << frase << endl << endl;
	return 0;

}
int Solucao::AlocaIndicesPeV( int &p, int &v, int Planta, int Veiculo, string frase){
	AlocaValoresIniciaisIndices(p,v);
	RetornaIndicePlanta(Planta, p);
	RetornaIndiceVeiculo(p, Veiculo, v);
	if(  VerificaInidices2(p,v) == -1 ){
		cout << frase << endl;
		return 0;
	}
	return 1;
}
void Solucao::RetornaIndicePlanta(int planta, int& p){
	for ( int i = 0; i < NP; i++){
		if( PlantasInstancia.Plantas[i].NumeroDaPlanta == planta){
			p = i;
		}
	}
}

void Solucao::RetornaIndiceVeiculo(int p, int Veiculo, int& v){
	for ( int i = 0; i <  PlantasInstancia.Plantas[p].NumeroVeiculos; i++){
		if( PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[i].NumeroDaCarreta == Veiculo){
			v = i;
		}
	}
}
int Solucao::VerificaIteradorDescarregamento( ItDescarregamento it1, double HorarioInicioAuxiliar, double HorarioFinalAuxiliar, int CaminhaoEmAnalise, int PlantaEmAnalise, int DemandaDesalocada ){
	if( it1->HorarioInicioDescarregamento == HorarioInicioAuxiliar){
		if( it1->HorarioFinalDescarregamento == HorarioFinalAuxiliar){
			if( it1->NumCarretaUtilizada == CaminhaoEmAnalise){
				if( it1->NumPlantaFornecedor == PlantaEmAnalise){
						return 1;
				}
			}
		}
	}
	return 0;
}
int Solucao::VerificaIteradorCarregamento( ItCarregamento it2, int  CaminhaoEmAnalise, int ConstrucaoEmAnalise, int DemandaDesalocada){
	if( it2->NumCarretaUtilizada == CaminhaoEmAnalise){
		if( it2->NumeroConstrucao ==  ConstrucaoEmAnalise){
			if( it2->NumeroDemandaSuprida == DemandaDesalocada){
				return 1;
			}
		}
	}
	return 0;
}

int Solucao::VerificaIteradorDeslocamento( ItDeslocamento it3,int ConstrucaoEmAnalise, int DemandaDesalocada){
	if( it3->NumeroConstrucao == ConstrucaoEmAnalise && it3->NumeroDemandaSuprida == DemandaDesalocada){
		return 1;
	}
	return 0;
}
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

int Solucao::RetornaDadosTarefa(int Construcao, int Demanda, int& NumeroCarreta, int& NumeroPlanta,double& HorarioInicioFabrica, double& HorarioSaiFabrica, double& HorarioInicioDescarregamento, double& HorarioFinalDescarregamento,double& HorarioRetornaFabrica){
	int ConstrucaoIndice;
	int ConstrucaoEmAnalise;
	int DemandaDesalocada;
	int PlantaIndice;

	//RetornaIndiceConstrucao(Construcao, ConstrucaoIndice);
	ConstrucoesInstancia.Construcoes[ConstrucaoIndice].RetornaDadosDescarregamento( Demanda, NumeroPlanta, NumeroCarreta, ConstrucaoEmAnalise,  HorarioInicioDescarregamento,HorarioFinalDescarregamento);

	if( ConstrucaoEmAnalise != Construcao || DemandaDesalocada != Demanda){
		cout << "<<<<<<<<<<<<<<<<<<<<<<< ERRO! -> Solucao::RetornaDadosTarefa >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << endl << endl;
		return 0;
	}

	RetornaIndicePlanta(NumeroPlanta, PlantaIndice);
	HorarioSaiFabrica = HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[ConstrucaoIndice].DistanciaPlantas[PlantaIndice].Distancia;
	HorarioInicioFabrica = HorarioSaiFabrica - PlantasInstancia.Plantas[PlantaIndice].TempoPlanta;

	HorarioRetornaFabrica = HorarioFinalDescarregamento + ConstrucoesInstancia.Construcoes[ConstrucaoIndice].DistanciaPlantas[PlantaIndice].Distancia;

	return 1;


}
void Solucao::DeletaTarefaConstrucao(ItDescarregamento 	It1Aux, int c, int d ) {
	ConstrucoesInstancia.Construcoes[c].Descarregamentos.erase( It1Aux );
	ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento - 1;
	ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[d] = 0;
	ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade + 1;

	cout << endl << endl << " Colocar uma função que reorganiza tarefas alocadas " << endl << endl;

	ConstrucoesInstancia.CalculaMakespansConstrucoes();
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
}

void Solucao::DeletaTarefaCarreta(ItDeslocamento  	It3Aux, int p, int v ) {
	PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.erase(It3Aux);
	PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDeDemandasAntendidas--;
}
void Solucao::MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda, int Situacao){
	int c;

	RetornaIndiceConstrucao(Construcao, c, "Solucao::MarcaTarefaDeletadaNoVetor");

	ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[Demanda] = Situacao;
}
int Solucao::AdicionaTarefaHorarioInicioDescarregamento( int Construcao, int Demanda , double HorarioInicioDescarregamento,vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda){
	cout << endl << endl << "  reimplementar - > Solucao::AdicionaTarefaHorarioInicioDescarregamento " << endl << endl;

	/*
	int c;
	int d;

	int NumPlantaAnalisando;

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	AlocaIndicesCeD( c,d, Construcao, Demanda,1, "  <<<<    Solucao::AdicionaTarefaHorarioInicioDescarregamento  >>>>>>>>>> ");

	if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
		PlantasInstancia.InicializaPlantasAnalizadas();
		do{
			EncontraPlantaMenorDistanciaConstrucao(c, NumPlantaAnalisando, "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  -> AdicionaTarefaHorarioInicioDescarregamento &&&&&&&&&&&&& ");
			PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();
			for( int v = 0; v < PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){
				HorarioChegaContrucao = HorarioInicioDescarregamento;
				HorarioInicioPlanta = HorarioChegaContrucao - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;

				if( HorarioInicioPlanta < PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento){
					HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento;
				}
				do{
					HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
					HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
					HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][d];
					HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];

					DisponibilidadePlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
					DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
					DisponibilidadeCarreta = PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
					if( DisponibilidadePlanta == 1){
						if( DisponibilidadeCarreta == 1){
							if( DisponibilidadeConstrucao == 1){
								ConstrucoesInstancia.Construcoes[c].AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao,   PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta,0, SituacaoDemanda, PlantasInstancia);
								ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;

								DadosTarefasAdicionadas.resize(DadosTarefasAdicionadas.size()+1);
								DadosTarefasAdicionadas[DadosTarefasAdicionadas.size()-1].InserirConteudo(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta,PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, HorarioInicioPlanta, HorarioSaiDaPlanta,HorarioChegaContrucao, HorarioSaiConstrucao,HorarioRetornaPlanta);
								return 1;
							}else{
								if( DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
									cout << endl << endl << "  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      Possivel Alocação";
									if( DisponibilidadeConstrucao == 2){
										cout << " antes das tarefas ";
									}else{
										cout << " no meio de tarefas ";
									}
									cout << "-> Solucao::AdicionaTarefaHorarioInicioDescarregamento >>>>>>>>>>>>> " << endl << endl;
									RearrumaTarefasParaAdicionalas(c, d, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta, PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta , HorarioInicioPlanta, HorarioSaiDaPlanta, HorarioChegaContrucao, HorarioSaiConstrucao, HorarioRetornaPlanta, SituacaoDemanda);
									return 1;
								}else{
									if( DisponibilidadeConstrucao == -1){
										return -1;
									}
								}
							}
						}
					}
					HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
				}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
			}
			PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] = 1;
		}while( PlantasInstancia.AnalizouTodasPLanats() == 0);
		return 0;
	}else{
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Construcao [" << c << "-" << d << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}
	*/
}

void Solucao::AlocaIndicesDadosParaReorganizar(int t, int &ConstrucaoIndice, int &PlantaIndice,  int &CaminhaoIndice, vector < DadosTarefa > Instancia){
	for( unsigned int c = 0; c < ConstrucoesInstancia.Construcoes.size(); c++){
		if( ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao == Instancia[t].DadosDasTarefas[0] ){
			ConstrucaoIndice = c;
		}
	}

	for( unsigned int p = 0; p < PlantasInstancia.Plantas.size(); p++){
		if( PlantasInstancia.Plantas[p].NumeroDaPlanta ==  Instancia[t].DadosDasTarefas[2] ){
			PlantaIndice = p;
		}
	}

	for( unsigned int v = 0; v < PlantasInstancia.Plantas[PlantaIndice].VeiculosDaPlanta.Carretas.size(); v++){
		if(  PlantasInstancia.Plantas[PlantaIndice].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta ==  Instancia[t].DadosDasTarefas[3] ){
			CaminhaoIndice = v;
		}
	}

	if( ConstrucaoIndice == -13 || PlantaIndice == -13 || CaminhaoIndice == -13){
		cout << endl << endl << "  ########################## Problema em alocar os valores de ConstrucaoIndice, PlantaIndice e CaminhaoIndice  -> Procedimento1::RearrumaTarefasParaAdicionalas:: AlocaIndicesDadosParaReorganizar ########################## " << endl << endl ;
	}
}
void Solucao::InserirDadosEmEstruturaInstanciasDadosTarefasRetirar( vector < DadosTarefa > &Instancia, int ConstrucaoIndice, int Imprime){

	Planta PlantaAuxiliarRemocao;

	for( unsigned int d = 0; d < ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos.size(); d++){
		Instancia[d].IniciaConteudo();
		Instancia[d].DadosDasTarefas[0] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].NumeroDaConstrucao;
		Instancia[d].DadosDasTarefas[1] = d;
		Instancia[d].DadosDasTarefas[2] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].NumPlantaFornecedor;
		Instancia[d].DadosDasTarefas[3] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].NumCarretaUtilizada;

		Instancia[d].HorariosDasTarefas[2] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].HorarioInicioDescarregamento;
		Instancia[d].HorariosDasTarefas[3] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].HorarioFinalDescarregamento;

		for( unsigned int p = 0; p < PlantasInstancia.Plantas.size(); p++){
			if( PlantasInstancia.Plantas[p].NumeroDaPlanta == Instancia[d].DadosDasTarefas[2] ){
				PlantaAuxiliarRemocao = PlantasInstancia.Plantas[p];
			}
		}

		Instancia[d].HorariosDasTarefas[0] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].HorarioInicioDescarregamento - PlantaAuxiliarRemocao.DistanciaConstrucoes[ Instancia[d].DadosDasTarefas[0] ] - PlantaAuxiliarRemocao.TempoPlanta;
		Instancia[d].HorariosDasTarefas[1] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].HorarioInicioDescarregamento - PlantaAuxiliarRemocao.DistanciaConstrucoes[ Instancia[d].DadosDasTarefas[0] ];
		Instancia[d].HorariosDasTarefas[4] = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos[d].HorarioFinalDescarregamento + PlantaAuxiliarRemocao.DistanciaConstrucoes[ Instancia[d].DadosDasTarefas[0] ];

	}

	if( Imprime == 1){
		cout << endl << endl << "  Dados Gravados " << endl << endl;
		for( unsigned int d = 0; d < ConstrucoesInstancia.Construcoes[ConstrucaoIndice].Descarregamentos.size(); d++){
			Instancia[d].Imprimir();
		}
	}
}
void Solucao::RearrumaTarefasParaAdicionalas(int ConstrucaoIndice, int &NumDemanda, int NumPlanta, int NumCarreta, double HorarioInicioPlanta, double HorarioSaiDaPlanta, double HorarioChegaContrucao, double HorarioSaiConstrucao, double HorarioRetornaPlanta, int SituacaoDemanda){
	cout << endl << endl << "  reimplementar -> Solucao::RearrumaTarefasParaAdicionalas " << endl << endl;
	/*
	vector < DadosTarefa > Instancia;

	int  ParaPrograma;
	int	Imprime;
	Imprime = 0;

	if( Imprime == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
	}

// Armazena Tarefas em estrutura

	Instancia.resize( ConstrucoesInstancia.Construcoes[ConstrucaoIndice].StatusAtendimento + 1 );
	InserirDadosEmEstruturaInstanciasDadosTarefasRetirar( Instancia, ConstrucoesInstancia.Construcoes[ConstrucaoIndice].NumeroDaConstrucao, Imprime);

// Deleta tarefas
	for( unsigned int d = 0; d < ( Instancia.size() - 1 ); d++){
		PlantasInstancia.DeletaTarefa( Instancia[d].DadosDasTarefas[2], Instancia[d].HorariosDasTarefas[0], Instancia[d].HorariosDasTarefas[1], Instancia[d].DadosDasTarefas[0], Instancia[d].DadosDasTarefas[1], Instancia[d].DadosDasTarefas[3],Instancia[d].HorariosDasTarefas[0],  Instancia[d].HorariosDasTarefas[4]);
		ConstrucoesInstancia.DeletaTarefa(Instancia[d].DadosDasTarefas[0], Instancia[d].HorariosDasTarefas[2], Instancia[d].HorariosDasTarefas[3], Instancia[d].DadosDasTarefas[1],  Instancia[d].DadosDasTarefas[2], Instancia[d].DadosDasTarefas[3], PlantasInstancia);
	}

	if( Imprime == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
	}

// Insere Tarfea que está fora da ordem em estrutura
	Instancia[ (Instancia.size()-1) ].InserirConteudo( ConstrucoesInstancia.Construcoes[ConstrucaoIndice].NumeroDaConstrucao , NumPlanta, NumCarreta, HorarioInicioPlanta, HorarioSaiDaPlanta, HorarioChegaContrucao, HorarioSaiConstrucao, HorarioRetornaPlanta);
			// Obs: o valor -1 é para sinalizar que é está a tarefa que esta sendo adicionada ao sequenciamento.

	if( Imprime == 2){
		for( unsigned int d = 0; d < Instancia.size(); d++){
			Instancia[d].Imprimir();
		}
	}

// Ordena Tarfeas
	sort( Instancia.begin(), Instancia.end(), DecideQualTarefaVemAntes );

	if( Imprime == 2){
		cout << endl << endl << "      Ordenou " << endl << endl;
		for( unsigned int d = 0; d < Instancia.size(); d++){
			Instancia[d].Imprimir();
		}
	}


	int PlantaIndice;
	int CaminhaoIndice;
	int aux;


	PlantaIndice = -13;
	CaminhaoIndice = -13;



// Reinsere Tarefas que foram retiradas, só que agora em ordem
	//cout << endl << "  Pau!!!!!!  [" << Instancia.size() << "]" << endl;
	for( unsigned int t = 0; t < Instancia.size(); t++){
		//cout << endl << "  Ui ( "<< t << ")!!!!!!  " << endl;

		AlocaIndicesDadosParaReorganizar(t, aux, PlantaIndice, CaminhaoIndice, Instancia);
		if( Instancia[t].DadosDasTarefas[1] == -1 ){
			//cout << "   merda (" << t << ")" << endl;
			NumDemanda = t;
			//cout << "   cagou" << endl;
		}

		//cout << " aqui1" << endl;
		ConstrucoesInstancia.Construcoes[ConstrucaoIndice].AlocaAtividade( Instancia[t].HorariosDasTarefas[2], Instancia[t].HorariosDasTarefas[3] ,  Instancia[t].DadosDasTarefas[3], Instancia[t].DadosDasTarefas[2],0, SituacaoDemanda, PlantasInstancia);

		//cout << " aqui2" << endl;
	}

	if( Imprime == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
		cout << "                 Ta indo " << endl;
		cin >> ParaPrograma;
	}
*/
}

int Solucao::ReadicionaTarefasHoraInicioDescarregamento(int Construcao, int Demanda, double HoraInicioDescarregamento,vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda){
	int c;
	int d;

	int Alocou;
	int Ativa;

	vector < DadosTarefa > AuxiliarLixo;

	Ativa = 0;

	AlocaIndicesCeD( c, d, Construcao, Demanda, "  <<<<    Solucao::ReadicionaTarefasHoraInicioDescarregamento  >>>>>>>>>> ");


	//cout << endl << " situacao alocacao [";
	for ( int demandas = d; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
		//cout << " ->[" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
		if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
			Alocou = AdicionaTarefaHorarioInicioDescarregamento(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, HoraInicioDescarregamento, DadosTarefasAdicionadas, SituacaoDemanda);
			//cout << " " << Alocou << " ";

			if( Alocou == 1){
				//cout << "   +++ Realocou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
				Ativa = 1;
			}else{
				if( Alocou == -1){
					//cout << "]"<< endl;
					return -1;
				}else{
					//cout << "   *** Nao Realocou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
				}
			}
		}
	}
	//cout << "]"<< endl;
	if( Ativa == 1){
		return 1;
	}else{
		return 0;
	}
}

// Mudado

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


int Solucao::AdicionaTarefa( int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda){

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
				PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();
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



int Solucao::ProcessoParaAlocarTarefaNaoAtendida( int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda){
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
					Alocou = AdicionaTarefa(ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas, DadosTarefasAdicionadas, SituacaoDemanda);

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

void Solucao::ReadicionaTarefas( int construcao, vector < DadosTarefa > &DadosTarefasAdicionadas, int SituacaoDemanda){
	int c;

	if( RetornaIndiceConstrucao( construcao, c, " Solucao::ReadicionaTarefas") == 1 ){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
				//cout << " entrei " << endl;
				if( AdicionaTarefa(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, DadosTarefasAdicionadas, SituacaoDemanda) == 1 ){
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

void Solucao::MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda){
	int c;

	if( RetornaIndiceConstrucao( Construcao, c, " Solucao::ReadicionaTarefas") == 1 ){
		ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[Demanda] = 1;
		//cout << endl << endl << "  marquei " << endl << endl;
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


void Solucao::ProcessoViabilizacao1(){

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

				TarefaAlocada = ProcessoParaAlocarTarefaNaoAtendida( ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovaTarefaAlocadaConstrucao , NovaTarefaAlocadaDemanda,  DadosTarefasAdicionadas, 0);
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

					ReadicionaTarefas( ConstrucaoAnalisandoRetirada, DadosTarefasAdicionadas, 0);
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

						MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

						//ConstrucoesInstancia.ImprimeContrucoes();
						//PlantasInstancia.Imprime(1,1);

						//cin >> PararPrograma;

					}
				}else{
					//cout << endl << endl << "            Nao consegui adicionar nova tarefa" << endl << endl;
					ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas, 1);
					DadosTarefasDesalocadas.clear();

					MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

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


void Solucao::IniciarVetorPlantasPodemAtenderTarefa( vector< int > &PlantasPodemAtenderTarefa ){
	PlantasPodemAtenderTarefa.resize(NP);
	for(int p = 0; p < NP; p++){
		PlantasPodemAtenderTarefa[p] = 0;
	}
}



void Solucao::AlocaNovaDemandaParaAtender( int &d, int ConstrucaoParaAtenderIndice, int &PlantaAtender, int &PlantaAtenderIndice,vector< int > &PlantasPodemAtenderTarefa, int &ExistePlanta, int Imprime){
	d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;
	if( Imprime == 1){
		cout << " Demanda [" << d << "]" << endl;
	}
	PlantasInstancia.InicializaPlantasAnalizadas();
	IniciarVetorPlantasPodemAtenderTarefa( PlantasPodemAtenderTarefa );
	ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
}


int Solucao::MoveTarefasParaTentarAlocarTarefa(int IndiceConstrucaoNaoAtendida, int Demanda, vector < DadosTarefa > &DadosTarefasAdicionadas, vector < DadosTarefa > &DadosTarefasDesalocadas){


	int NumeroCarreta;
	int NumeroPlanta;
	double HorarioInicioFabrica;
	double HorarioSaiFabrica;
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	double HorarioRetornaFabrica;

	int DemandaAnterior;

	double Horario;

	int Retirou;


	int ParaPrograma;

	vector < int > Adicionou;
	int AdicionouPosicao;

	//ConstrucoesInstancia.ImprimeContrucoes();
	//PlantasInstancia.Imprime(1,1);

	DemandaAnterior = Demanda;








	cout << " ----------------------------------------------------------------------------------------------" << endl << endl;
	do{
		DemandaAnterior = DemandaAnterior - 1;			// atualiza as tarefas que serão atrazadas.
		//DeletaAlocacaoTarefa( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, DemandaAnterior, NumeroCarreta, NumeroPlanta,HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento,HorarioRetornaFabrica, DadosTarefasDesalocadas, DadosTarefasAdicionadas);
		/*

		 if( RetiraElementoVetorDadosTarefa(DadosTarefasAdicionadas, ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, DemandaAnterior) == 0){
			DadosTarefasDesalocadas.resize(DadosTarefasDesalocadas.size() + 1);
			DadosTarefasDesalocadas[DadosTarefasDesalocadas.size() - 1].InserirConteudo(ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, DemandaAnterior, NumeroCarreta, NumeroPlanta,HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento,HorarioRetornaFabrica);
		}
		*/
		Horario = HorarioInicioDescarregamento;



		do{
			Horario = Horario + IntervaloDeTempo;					// Atualiza o horario que a primeira tarefa a ser atrazada ira podoer ser alocada
			Adicionou.resize( Demanda - DemandaAnterior + 1);		// Vetor que representa se as tarefas que estão sendo deslocadas foram alocadas ou não
			AdicionouPosicao = 0;									// contador do vetor acima citado (Adicionou)

			for( int d = DemandaAnterior; d <= Demanda; d++){		// Tenta alocar as tarefas
				Adicionou[AdicionouPosicao] = AdicionaTarefaHorarioInicioDescarregamento( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, d , Horario, DadosTarefasAdicionadas, 3);
				AdicionouPosicao++;
				//cout << " d = " << d << endl;
			}
			cout << " Horario " << Horario << " ";
			ImprimeVetorInt(Adicionou);

			if( VerificaValorUmVetorInt(Adicionou) != 1 ){			// verifica se todas as tarefas forma alocadas. Caso não forem, ele ira deletar as tarefas que foram alocadas.
				AdicionouPosicao = 0;
				for( int d = DemandaAnterior; d <= Demanda; d++){
					if ( Adicionou[AdicionouPosicao] == 1 ){
						//DeletaAlocacaoTarefa( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, d , NumeroCarreta, NumeroPlanta,HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento,HorarioRetornaFabrica, DadosTarefasDesalocadas, DadosTarefasAdicionadas);
					}
					AdicionouPosicao++;
				}
			}

		}while(VerificaValorUmVetorInt(Adicionou) != 1 || Horario > ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMaximoDeFuncionamento);

		if( VerificaValorUmVetorInt(Adicionou) == 1){
			for( int d = DemandaAnterior; d <= Demanda; d++){
				RetornaDadosTarefa(ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, d , NumeroCarreta, NumeroPlanta,HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento,HorarioRetornaFabrica);
				DadosTarefasAdicionadas.resize( DadosTarefasAdicionadas.size()+1);
				DadosTarefasAdicionadas[DadosTarefasAdicionadas.size()-1].InserirConteudo(ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].NumeroDaConstrucao, d , NumeroCarreta, NumeroPlanta,HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento,HorarioRetornaFabrica);
			}
			cout << endl << endl << "   deu certo" << endl << endl;
			//cin >> ParaPrograma;
			return 1;
		}

	}while( VerificaValorUmVetorInt(Adicionou) != 1 || DemandaAnterior != 0);

	cout << " ----------------------------------------------------------------------------------------------" << endl << endl;

	//ConstrucoesInstancia.ImprimeContrucoes();
	//PlantasInstancia.Imprime(1,1);


	//cin >> ParaPrograma;


	return 0;
}



//  Mudando


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

int Solucao::SelecionaCarreta(int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas ){

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

		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();

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

int Solucao::SelecionaCarretaComHoraInicio( double HoraInicio, int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas ){

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

		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();

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

int Solucao::ColocarTarefaAtrazandoAsOutras(int ConstrucaoParaAtenderIndice, int demanda , double HoraInicio, vector < DadosTarefa > & DadosAdicionaAux){
	vector < int > SituacaoPlantas;
	vector < int > SituacaoDemandas;
	double HorarioInicioConstrucao;

	int ExistePlanta;
	int PlantaAtender;
	int PlantaAtenderIndice;

	int PermiteAtendimentoDemanda;

	vector < DadosTarefa > Auxiliar;
	vector < DadosTarefa > AuxiliarRetira;

	HorarioInicioConstrucao = HoraInicio + IntervaloDeTempo;

	SituacaoPlantas.resize(NP);
	SituacaoDemandas.resize(demanda + 1);

	while(HorarioInicioConstrucao <  ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento ){

		cout << "  HorarioInicioConstrucao " << HorarioInicioConstrucao << endl;
		IniciaVetorIntComZero(SituacaoDemandas);
		for( int d = 0; d <= demanda; d++){
			IniciaVetorIntComZero(SituacaoPlantas);
			ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );
			PermiteAtendimentoDemanda = 0;
			while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < demanda + 1 && PermiteAtendimentoDemanda == 0){
				SituacaoPlantas[PlantaAtenderIndice] = 1;
				PermiteAtendimentoDemanda = SelecionaCarretaComHoraInicio( HorarioInicioConstrucao, ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, Auxiliar );
				if( PermiteAtendimentoDemanda == 1){
					IniciaVetorIntComZero(SituacaoPlantas);
					SituacaoDemandas[d] = 1;
					ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );
				}else{
					if( PermiteAtendimentoDemanda == 0){
						SituacaoPlantas[PlantaAtender] = 1;
						ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );
					}
					if ( PermiteAtendimentoDemanda == -2){
						SituacaoPlantas[PlantaAtender] = -2;
						ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );
					}
				}
			}
			if ( VerificaTodosValoresVetorInt( 1, SituacaoDemandas) == 1){
				DadosAdicionaAux = Auxiliar;
				return 1;
			}
		}
		if ( VerificaSeTemUmValorVetorInt( -2, SituacaoPlantas) == 1){
			ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);
			Auxiliar.clear();
			HorarioInicioConstrucao = HorarioInicioConstrucao + IntervaloDeTempo;
		}else{
			ImprimeVetorInt( SituacaoPlantas);
			ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);
			Auxiliar.clear();
			return 0;
		}
	}
	Auxiliar.clear();
	return 0;

}

void Solucao::ProcessoViabilizacao2(){

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
	Imprime = 0;
	int PararPrograma;

// Encontra demanda ainda não atendida

	ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();

	while( ConstrucoesInstancia.VerificaConstrucaoPodeAtender() == 1){
		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
		ConstrucoesInstancia.ReiniciaTarefasRetiradas();
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);
		TempoSaiPlanta.resize(NP);
		//cout << " ConstrucaoNaoAtendida = " << ConstrucaoNaoAtendida <<" DemandaNaoAtendida = " << DemandaNaoAtendida << endl << endl;
		RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );
	// deleta tarefas que são atendidas antes desta tarefa não alocada
		AlocaTempoSaiDaPlanta(IndiceConstrucaoNaoAtendida,TempoSaiPlanta, 0);
		DeletouAlgumaTarefa = DeletaTarefasAposTempoSaiPlanta(TempoSaiPlanta, DadosTarefasDesalocadas,  0);
	// Adiciona a tarefa que não era alocada antes
		TarefaAdicionada = AdicionaTarefa( ConstrucaoNaoAtendida, DemandaNaoAtendida, DadosTarefasAdicionadas, 2);
		SinalizaTarefaAdicionadaInicialmente( TarefaAdicionada, IndiceConstrucaoNaoAtendida, DemandaNaoAtendida);
		if( ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] == -1){
			cout << endl << endl << "   Não consigo alocar tarefa [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] que não foi alocada antes -> Solucao::ProcessoViabilizacao2 " << endl << endl;
			ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas, 1);
			DadosTarefasDesalocadas.clear();
			ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();
			ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 4;
		}else{

			//ConstrucoesInstancia.ImprimeContrucoes();
			//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);
			//cin >> PararPrograma;

	// marca construções com tarefas a alocar
			ConstrucoesInstancia.InicializaConstrucaosAnalizadas();
			ConstrucoesInstancia.AlocaValoresConstrucaosAnalizadas( IndiceConstrucaoNaoAtendida);
	// Verifica se tem tarefa a se colocar
			PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucaosAnalizadas);
			//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1, ConstrucoesInstancia.ConstrucaosAnalizadas, 0);
			//cout << " ConstrucaoParaAtender " << ConstrucaoParaAtender << " [" << ConstrucaoParaAtenderIndice << "]     << Inico >> " << endl << endl;
			//cin >> PararPrograma;

			while( PossuiConstrucaoParaAnalisar == 1){
				//cout << endl << "   >>>>>>>>>>>>  construcao a se recolocar tarefas => " << ConstrucaoParaAtender << "(" << ConstrucaoParaAtenderIndice << ")" << endl;
				ConstrucoesInstancia.ConstrucaosAnalizadas[ConstrucaoParaAtenderIndice] = 1;
				d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;
				if( Imprime == 1){
					cout << " Demanda [" << d << "]" << endl;
				}
				PlantasInstancia.InicializaPlantasAnalizadas();
				ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);
				//cin >> PararPrograma;
				while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
					//cout << "     		Tenta Planta " << PlantaAtender << " [" << PlantaAtenderIndice << "]" << endl;
					PlantasInstancia.PlantasAnalizadas[PlantaAtenderIndice] = 1;
					PermiteAtendimentoDemanda = SelecionaCarreta(ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, DadosTarefasAdicionadas );
					//ConstrucoesInstancia.ImprimeContrucoes();
					//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucaosAnalizadas, 0);

					if( PermiteAtendimentoDemanda == 1){
						//cout << "             +++++   Planta [" << PlantaAtenderIndice << "] " << PlantasInstancia.Plantas[PlantaAtenderIndice].NumeroDaPlanta << "  atende demanda " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
							d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;
								if( Imprime == 1){
									cout << " Demanda [" << d << "]" << endl;
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



						if( ExistePlanta == 0 && PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeatrazar() && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento > 1){
							cout << endl << endl << "   	Pode atrazar tarefas da construção " << ConstrucaoParaAtender << " [" << ConstrucaoParaAtenderIndice << "] - d = " << d << " para alocar outra " << endl << endl;

							ConstrucoesInstancia.ImprimeContrucoes();
							//PlantasInstancia.Imprime(1,1);

							cin >> PararPrograma;
							ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, DadosRetirandoAux);

							ConstrucoesInstancia.ImprimeContrucoes();
							//PlantasInstancia.Imprime(1,1);

							cout << endl << endl << "        Atraza e tenta alocar " << ConstrucaoParaAtender << " [" << ConstrucaoParaAtenderIndice << "]- d = " << d <<  endl << endl;

							ConseguiAlocarTarefa = ColocarTarefaAtrazandoAsOutras( ConstrucaoParaAtenderIndice, d , HoraInicio, DadosAdicionaAux);

							cout << endl << endl << " ConseguiAlocarTarefa " << ConseguiAlocarTarefa << endl << endl;

							cin >> PararPrograma;

							ConstrucoesInstancia.ImprimeContrucoes();
							//PlantasInstancia.Imprime(1,1);

							cin >> PararPrograma;



						}

						/*
						 *   A novo procedimento para atrazar as tarefas tem que entrar aqui!!!!!!!!!!!!!
						 */





					}
					if( ExistePlanta == 0 ){
						cout << " Nao se pode colocar tarefa da construcao [" << ConstrucaoParaAtenderIndice << "] " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						ConstrucoesInstancia.ConstrucaosAnalizadas[ConstrucaoParaAtenderIndice] = 4;
						ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
						ConstrucoesInstancia.ImprimeContrucoes();

						/*
							if( ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento > 0){
							TarefaAdicionadaAposDeslocamentoTarefas = MoveTarefasParaTentarAlocarTarefa( ConstrucaoParaAtenderIndice, d, DadosTarefasAdicionadas, DadosTarefasDesalocadas);

							cin >> PararPrograma;


							if(TarefaAdicionadaAposDeslocamentoTarefas == 1){
								//OrganizaSolucao(ConstrucaoParaAtenderIndice);

								ConstrucoesInstancia.ImprimeContrucoes();

								if( ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
									AlocaNovaDemandaParaAtender( d, ConstrucaoParaAtenderIndice, PlantaAtender,PlantaAtenderIndice, PlantasPodemAtenderTarefa,ExistePlanta, 1);
								}
							}
						}
						*/
					}
				}
				PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucaosAnalizadas);
				//ConstrucoesInstancia.ImprimeContrucoes();
				//PlantasInstancia.Imprime(1,1);
				//cin >> PararPrograma;



			}
			ConstrucoesInstancia.ImprimeContrucoes();
			//PlantasInstancia.Imprime(1,1);

			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			if( InviabilidadeSolucaoAnterior < ConstrucoesInstancia.NivelDeInviabilidade){
				cout << endl << endl << "    Melhoru !!!!!!" << endl << endl;
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();

			}else{
				cout << endl << endl << "    Não melhoru !!!!!!" << endl << endl;
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
