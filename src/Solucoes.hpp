/*
 * Solucoes.hpp
 *
 *  Created on: Sep 11, 2015
 *      Author: mateus.vilela
 */

#ifndef SOLUCOES_HPP_
#define SOLUCOES_HPP_

#include "Bibliotecas.hpp"

#define ItCarregamento 		vector< Carregamento 	>::iterator
#define ItDeslocamento 		vector< Deslocamento 	>::iterator
#define ItDescarregamento 	vector< Descarregamento >::iterator

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


	void CarregaSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);
	void Imprime(bool, bool, bool);

	int VerificaRespeitoIntervalos();
	int DetetaAlocacaoTarefa(int,int);
	int DeletaAlocacaoTarefasPosteriores(int, int);
	void MarcaTarefaDeletadaNoVetor(int, int);

	int AdicionaTarefa( int, int) ;
	int ProcessoParaAlocarTarefa( int, int, int&, int&);

	int ReadicionaTarefas(int, int);
	void MarcaTarefaNaoDeletadaNoVetor(int, int);
	int ConstrucaoTarefaRemover(int&, int&);


	~Solucao();
};

Solucao::Solucao(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
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

void Solucao::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes ){
	ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
	if( ImprimePlanta == 1 ){
		PlantasInstancia.Imprime();
	}
	if( ImprimeConstrucao == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
	}
	if( IntervalosRespeitadosConstrucaoes == 1){
		ConstrucoesInstancia.VerificaIntervaloContrucoes();
	}

}

int Solucao::DetetaAlocacaoTarefa(int Construcao, int Demanda){

	int 	PlantaEmAnalise;
	int 	CaminhaoEmAnalise;
	int 	ConstrucaoEmAnalise;
	int 	DemandaDesalocada;
	double 	HorarioInicioAuxiliar;
	double 	HorarioFinalAuxiliar;

	ItDescarregamento 	It1Aux;
	ItCarregamento 		It2Aux;
	ItDeslocamento 		It3Aux;

	bool 			AlocouPonteiroCarregamento;
	vector < bool > AlocouPonteiroDeslocamento;

	int c;
	int d;

	c = -13;
	d = -13;

	int 	AlocouAux;
	bool 	DesalocadoDescarregamento;
	int 	pAxu;
	int 	vAux;


	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	for( unsigned int j = 0; j < ConstrucoesInstancia.Construcoes[c].Descarregamentos.size(); j++){
		if( Demanda == ConstrucoesInstancia.Construcoes[c].Descarregamentos[j].NumeroDemandaSuprida){
			d = j;
		}
	}
	if( c == -13 || d == -13 ){
		cout << cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao &&&&&&&&&&&&& " << endl << endl << endl;
		return -1;
	}

// Carrega dados da tarefa
	PlantaEmAnalise 		=	ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;
	CaminhaoEmAnalise 		=	ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada;
	ConstrucaoEmAnalise 	= 	ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
	DemandaDesalocada 		= 	ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumeroDemandaSuprida;
	HorarioInicioAuxiliar 	= 	ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento;
	HorarioFinalAuxiliar 	= 	ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento;

	//cout << endl << endl << "  Planta " << PlantaEmAnalise << " Caminhao " << CaminhaoEmAnalise << " Construcao " << ConstrucaoEmAnalise;
	//cout << " Demanda " << DemandaDesalocada << " HorarioInicio " << HorarioInicioAuxiliar << " HorarioFinalAuxiliar " << HorarioFinalAuxiliar << endl;

// Desaloca descarregamento na construção
	DesalocadoDescarregamento = 0;
	for( ItDescarregamento it1 = ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin(); it1 != ConstrucoesInstancia.Construcoes[c].Descarregamentos.end(); it1++){
		if( it1->HorarioInicioDescarregamento == HorarioInicioAuxiliar){
			if( it1->HorarioFinalDescarregamento == HorarioFinalAuxiliar){
				if( it1->NumCarretaUtilizada == CaminhaoEmAnalise){
					if( it1->NumPlantaFornecedor == PlantaEmAnalise){
						if( it1->NumCarretaUtilizada ==  CaminhaoEmAnalise ){
							It1Aux = it1;
							DesalocadoDescarregamento = 1;
							//cout << " ++++++++++++++++= ### Dados: carreta " << it1->NumCarretaUtilizada << "  demanda "<< it1->NumeroDemandaSuprida << "  ("<< it1->HorarioInicioDescarregamento << "-"<< it1->HorarioFinalDescarregamento << ")"<< endl;
						}
					}
				}
			}
		}
	}

	if( DesalocadoDescarregamento == 0){
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao conseguiu desalocar &&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}
	ConstrucoesInstancia.Construcoes[c].Descarregamentos.erase( It1Aux );
	ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento - 1;
	ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[DemandaDesalocada] = 0;
	ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade + 1;
	//ConstrucoesInstancia.Construcoes[c].ImprimeContrucao();

// Desaloca Carregamentos da Planta
	AlocouPonteiroCarregamento = 0;
	AlocouPonteiroDeslocamento.resize(NP+1);
	for( int p = 0; p < NP; p++){
		if( PlantasInstancia.Plantas[p].NumeroDaPlanta == PlantaEmAnalise ){
			for (ItCarregamento it2 = PlantasInstancia.Plantas[p].Carregamentos.begin() ; it2 != PlantasInstancia.Plantas[p].Carregamentos.end(); it2++){
				if( it2->NumCarretaUtilizada == CaminhaoEmAnalise){
					if( it2->NumeroConstrucao ==  ConstrucaoEmAnalise){
						if( it2->NumeroDemandaSuprida == DemandaDesalocada){
							//cout <<  "        Deleta planta " << endl;
							It2Aux = it2;
							pAxu = p;
							AlocouPonteiroCarregamento = 1;
						}
					}
				}
			}
// Deleta deslocamento do caminhão
			AlocouPonteiroDeslocamento[p] = 0;
			for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){
				if( PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta == CaminhaoEmAnalise ){
					//cout << endl << endl << " Tem caminhao " << v << " (" << PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << ") " << endl << endl;
					//PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Imprime();
					for (ItDeslocamento it3 = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.begin(); it3 != PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.end(); it3++){
						//cout << "      ->    " << it3->NumeroConstrucao << " (" << ConstrucaoEmAnalise << ") e " << it3->NumeroDemandaSuprida << " (" << DemandaDesalocada << ") "  << endl;
						if( it3->NumeroConstrucao == ConstrucaoEmAnalise){
							if( it3->NumeroDemandaSuprida == DemandaDesalocada){
								It3Aux = it3;
								vAux = v;
								AlocouPonteiroDeslocamento[p] = 1;
							}
						}
					}
					if( AlocouPonteiroDeslocamento[p] == 1){
						PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[vAux].Deslocamentos.erase(It3Aux);
						PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[vAux].NumeroDeDemandasAntendidas = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[vAux].NumeroDeDemandasAntendidas - 1;
						//cout << endl << endl << "   Entrou para desalocar " << endl << endl;

					}
				}
			}
		}
	}

	if( AlocouPonteiroCarregamento == 1){
		PlantasInstancia.Plantas[pAxu].Carregamentos.erase(It2Aux);
		//cout <<  "        Deletou na planta " << endl;
	}else{
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Carregamento nao desalocado &&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}


	AlocouAux = 0;
	for( int p = 0; p < NP; p++){
		if( AlocouPonteiroDeslocamento[p] == 1){
			AlocouAux = 1;
		}
	}

	if( AlocouAux == 1 ){
		ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
		return 1;
	}else{
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Deslocamento nao desalocado &&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}
}

int Solucao::DeletaAlocacaoTarefasPosteriores(int Construcao, int Demanda ){

	int c;
	int d;
	vector < int > DemandaDesalocar;

	bool ConseguiDesalocar;

	c = -13;
	d = -13;

	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	for( unsigned int j = 0; j < ConstrucoesInstancia.Construcoes[c].Descarregamentos.size(); j++){
		if( Demanda == ConstrucoesInstancia.Construcoes[c].Descarregamentos[j].NumeroDemandaSuprida){
			d = j;
		}
	}
	if( c == -13 || d == -13 ){
		cout << cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao &&&&&&&&&&&&& " << endl << endl << endl;
		return -1;
	}


	ConstrucoesInstancia.OrdenaDescarregamentosConstrucoesOrdemCrescente();
	//ConstrucoesInstancia.Construcoes[c].ImprimeContrucao();
	bool EncontrouDeslocamento;
	EncontrouDeslocamento = 0;
	for( ItDescarregamento it1 = ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin(); it1 != ConstrucoesInstancia.Construcoes[c].Descarregamentos.end(); it1++ ){
		//cout << endl << " ## Passou por Construcao = " << Construcao << " e Demanda = " << it1->NumeroDemandaSuprida << endl;
		if( it1->NumeroDemandaSuprida == Demanda){
			EncontrouDeslocamento = 1;
		}
		if( EncontrouDeslocamento == 1){
			DemandaDesalocar.push_back (it1->NumeroDemandaSuprida);
			//cout << " %%%%%%%%%%%%%%%%% Entrou e deletou ConstrucaoEmAnalise = " << Construcao << " e Demanda = " << it1->NumeroDemandaSuprida << endl;
		}
	}
	if( EncontrouDeslocamento == 1){
		for( unsigned int i = 0; i < DemandaDesalocar.size(); i++){
			//cout << "   i = " << DemandaDesalocar[i] << endl;
			ConseguiDesalocar = DetetaAlocacaoTarefa(Construcao, DemandaDesalocar[i]);
			if( ConseguiDesalocar == 0){
				cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao conseguiu desalocar [" << Construcao << "-" << DemandaDesalocar[i] << "]  na função desloca posteriores &&&&&&&&&&&&& " << endl << endl << endl;
			}
		}
		DemandaDesalocar.erase (DemandaDesalocar.begin(),DemandaDesalocar.end());
		return 1;
	}else{
		return 0;
	}
}

void Solucao::MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda){
	int c;
	int d;

	c = -13;
	d = -13;

	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	if( Demanda < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
		d = Demanda;
	}
	if( c == -13 || d == -13 ){
		 cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao &&&&&&&&&&&&& " << endl << endl << endl;
	}
	ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] = 1;
}

int Solucao::AdicionaTarefa( int Construcao, int Demanda ){
	int c;
	int d;

	int NumPlantaAnalisando;

	double DistanciaConstrucaoPlanta;

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	c = -13;
	d = -13;
	NumPlantaAnalisando = -13;

	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[Demanda] == 0){
		d = Demanda;
	}
	if( c == -13 || d == -13 ){
		 cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao -> AdicionaTarefa &&&&&&&&&&&&& " << endl << endl << endl;
		return -1;
	}

	if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
		PlantasInstancia.InicializaPlantasAnalizadas();

		do{
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
				cout << cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  -> AdicionaTarefa &&&&&&&&&&&&& " << endl << endl << endl;
			}



			PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();
			for( int v = 0; v < PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){
				if( (ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta) > PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento){
					HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
				}else{
					HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento;
				}
				//cout << "    Carreta usada [" << PlantaMaisPerto.NumeroDaPlanta << "-" << PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "] Construcao e Demanda [" << ConstrucaoVaiSerSuprida.NumeroDaConstrucao << "-" <<  NumeroDemanda << "]" << endl;
				do{
					HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
					HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
					HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][d];
					HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
					DisponibilidadePlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
					DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
					DisponibilidadeCarreta = PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
					if( DisponibilidadePlanta == 1){
						if( DisponibilidadeConstrucao == 1){
							if( DisponibilidadeCarreta == 1){
								ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento + 1;
								PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].AlocaAtividade(HorarioInicioPlanta, HorarioRetornaPlanta, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , d);
								PlantasInstancia.Plantas[NumPlantaAnalisando].AlocaAtividade(HorarioInicioPlanta, HorarioSaiDaPlanta, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , d,  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta);
								ConstrucoesInstancia.Construcoes[c].AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, d,  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta,0,0,0);
								ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
								//cout << "		PLanta (" <<  HorarioInicioPlanta << "-" << HorarioSaiDaPlanta << " trajeto " << HorarioChegaContrucao << " - " << HorarioSaiConstrucao << " trajeto " << HorarioRetornaPlanta << ") " << endl;

								ConstrucoesInstancia.OrdenaDescarregamentosConstrucoesOrdemCrescente();
								ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
								cout << "      -> Adicionou construcao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]";
								cout << " construcao ("<< HorarioChegaContrucao <<"-" << HorarioSaiConstrucao << ")";
								cout << " planta " << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << " (" << HorarioInicioPlanta << "-" << HorarioSaiDaPlanta <<")";
								cout << " caminhao  " << PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << " (" << HorarioInicioPlanta << "-" << HorarioRetornaPlanta << ")" << endl;
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
		cout << cout << endl << endl << endl << "   &&&&&&&&&&&&& Construcao [" << c << "-" << d << "] com demanda ja atendida &&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}

}

int Solucao::ProcessoParaAlocarTarefa( int Construcao, int Demanda, int& NovatarefaAlocadaConstrucao , int& NovatarefaAlocadaDemanda ){
	int c;
	int d;

	bool Alocou;

	c = -13;
	d = -13;

	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[Demanda] == 0){
		d = Demanda;
	}
	if( c == -13 || d == -13 ){
		 cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao -> ProcessoParaAlocarTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		return -1;
	}

	for( unsigned int contrucoes = 0; contrucoes < ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas; demandas++){
			if( contrucoes != c){
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] ";
					Alocou = AdicionaTarefa(ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas);
					if( Alocou == 1){
						cout << " => Alocou [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> ProcessoParaAlocarTarefa" << endl;
						NovatarefaAlocadaConstrucao = ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao;
						NovatarefaAlocadaDemanda = demandas;
						return 1;
					}else{
						cout << " => Falhou! " << endl;
					}
				}
			}
		}
	}
	return 0;
}

int Solucao::ReadicionaTarefas(int Construcao, int Demanda){
	int c;
	int d;

	int Alocou;
	int Ativa;

	Ativa = 0;

	c = -13;
	d = -13;

	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	if( Demanda < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
		d = Demanda;
	}
	if( c == -13 || d == -13 ){
		 cout  << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao -> ReadicionaTarefas &&&&&&&&&&&&& " << endl;
		 return 0;
	}
	for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
		cout << " ->[" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> ReadicionaTarefas" << endl;
		if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
			Alocou = AdicionaTarefa(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas);
			//Alocou = 1;
			if( Alocou == 1){
				cout << "   +++ Realocou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> ReadicionaTarefas" << endl;
				Ativa = 1;
			}else{
				cout << "   *** Nao Realocou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> ReadicionaTarefas" << endl;
			}
		}
	}
	if( Ativa == 1){
		return 1;
	}else{
		return 0;
	}
}

void Solucao::MarcaTarefaNaoDeletadaNoVetor(int Construcao, int Demanda){
	int c;
	int d;

	c = -13;
	d = -13;

	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			c = i;
		}
	}
	if( Demanda < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
		d = Demanda;
	}
	if( c == -13 || d == -13 ){
		 cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao -> MarcaTarefaNaoDeletadaNoVetor &&&&&&&&&&&&& " << endl << endl << endl;
	}
	ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] = 0;
}

int Solucao::ConstrucaoTarefaRemover(int& Construcao, int& Demanda){

	//ConstrucoesInstancia.ImprimeContrucoes();

	double RankInicial;
	int Ativo;

	Construcao = -13;
	Demanda = -13;

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
		cout << " Selecionou construcao " << Construcao << "-" << Demanda << " com janela de tempo ";
		cout <<  ConstrucoesInstancia.Construcoes[Construcao].TempoMinimoDeFuncionamento << "-" << ConstrucoesInstancia.Construcoes[Construcao].TempoMaximoDeFuncionamento;
		cout << " -> ConstrucaoTarefaRemover" << endl ;
		return 1;
	}else{
		return 0;
	}
}

Solucao::~Solucao(){

}

class ConjuntoSolucoes{
public:
	ConjuntoSolucoes();
	vector < Solucao > Solucoes;
	void InsereSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);
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

void ConjuntoSolucoes::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes){
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		cout << endl << endl << "   Solucao " << s << endl << endl;
		 Solucoes[s].Imprime(ImprimePlanta,ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);
	}
}

ConjuntoSolucoes::~ConjuntoSolucoes(){

}
void InsereSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double, int);





#endif /* SOLUCOES_HPP_ */
