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


class DadosTarefa{
public:
	DadosTarefa();
	 vector < int >  DadosDasTarefasRetiradas; 		// 0 -> NumConstrução , 1 -> NumDemanda , 2 -> NumPlanta , 3 -> NumCarreta
	 vector < double > HorariosDasTarefasRetiradas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta
	void IniciaConteudo();
	void InserirConteudo(int, int, int, int, double, double, double, double, double);
	void Imprimir();
	~DadosTarefa();
};

DadosTarefa::DadosTarefa(){

}

void DadosTarefa::IniciaConteudo(){
	DadosDasTarefasRetiradas.resize(4);
	HorariosDasTarefasRetiradas.resize(5);
}

void DadosTarefa::InserirConteudo(int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta ){
	DadosDasTarefasRetiradas[0] = NumConstucao;
	DadosDasTarefasRetiradas[1] = NumDemanda;
	DadosDasTarefasRetiradas[2] = NumPlanta;
	DadosDasTarefasRetiradas[3] = NumCarreta;

	HorariosDasTarefasRetiradas[0] = HoraInicioPlanta;
	HorariosDasTarefasRetiradas[1] = HoraSaiPlanta;
	HorariosDasTarefasRetiradas[2] = HoraInicioConstrucao;
	HorariosDasTarefasRetiradas[3] = HoraSaiConstrucao;
	HorariosDasTarefasRetiradas[4] = HoraRetornaPlanta;
}

void DadosTarefa::Imprimir(){
	cout << " Construcao [" << DadosDasTarefasRetiradas[0] << "-" << DadosDasTarefasRetiradas[1] << "]";
	cout << "tempo (" << HorariosDasTarefasRetiradas[2] << "-" << HorariosDasTarefasRetiradas[3] << ") ";
	cout << " Planta [" << DadosDasTarefasRetiradas[2] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[1] << ") ";
	cout << " Caminhao [" << DadosDasTarefasRetiradas[2] << "-" << DadosDasTarefasRetiradas[3] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[4] << ") " << endl;
}

DadosTarefa::~DadosTarefa(){

}


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
	void AlocaValoresIniciaisIndices(int&, int&);
	void RetornaIndiceConstrucao(int, int&);
	void RetornaIndiceDemanda(int, int, int&);
	void RetornaIndicePlanta(int, int&);
	void RetornaIndiceVeiculo(int, int, int&);
	void VerificaIndiceDemanda(int, int, int&);
	void VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(int, int, int&);
	int VerificaInidices( int, int);
	int VerificaInidices2( int, int);
	int VerificaIteradorDescarregamento( ItDescarregamento, double, double, int, int, int);
	int VerificaIteradorCarregamento( ItCarregamento, int, int, int);
	void EncontraPlantaMenorDistanciaConstrucao(int, int&);

	void CarregaSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);
	void Imprime(bool, bool, bool);

	int VerificaRespeitoIntervalos();
	int DetetaAlocacaoTarefa(int,int,int&, int&, double&, double&, double&, double&, double&);
	int DeletaAlocacaoTarefasPosteriores(int, int, vector < DadosTarefa >& );
	void MarcaTarefaDeletadaNoVetor(int, int);

	int AdicionaTarefaHorarioInicioDescarregamento( int, int, double) ;
	int AdicionaTarefa( int, int) ;
	int ProcessoParaAlocarTarefa( int, int, int&, int&);

	int ReadicionaTarefasHoraInicioDescarregamento(int, int , double);
	int ReadicionaTarefas(int, int);
	int ReadicionaTarefasApartirDeDados( vector < DadosTarefa >);
	void MarcaTarefaNaoDeletadaNoVetor(int, int);
	int ConstrucaoTarefaRemover(int&, int&);

	void ProcessoViabilizacao1();

	int  ProcuraConstrucaoNaoAtendida(int&, int&);
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

void Solucao::AlocaValoresIniciaisIndices( int& c, int& d){
	c = -13;
	d = -13;
}
void Solucao::RetornaIndiceConstrucao(int Construcao, int& Indice){
	for ( int i = 0; i < NE; i++){
		if( Construcao == ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao){
			Indice = i;
		}
	}
}

void Solucao::RetornaIndiceDemanda(int c, int Demanda, int& Indice){
	for( unsigned int j = 0; j < ConstrucoesInstancia.Construcoes[c].Descarregamentos.size(); j++){
		if( Demanda == ConstrucoesInstancia.Construcoes[c].Descarregamentos[j].NumeroDemandaSuprida){
			Indice = j;
		}
	}
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

void Solucao::VerificaIndiceDemanda(int c, int Demanda, int& Indice){
	if( Demanda < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
		Indice = Demanda;
	}
}
void Solucao::VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(int c, int Demanda, int& Indice){
	if( Demanda < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
		if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[Demanda] == 0){
			Indice = Demanda;
		}
	}
}

int Solucao::VerificaInidices( int c, int d){
	if( c == -13 || d == -13 ){
			cout  << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a demanda ou construcao &&&&&&&&&&&&& " << endl << endl << endl;
			return -1;
		}
	return 1;
}

int Solucao::VerificaInidices2( int p, int v){
	if( p == -13 || v == -13 ){
			cout  << endl << endl << endl << "   &&&&&&&&&&&&& Nao encontrei a planta ou caminhao &&&&&&&&&&&&& " << endl << endl << endl;
			return -1;
		}
	return 1;
}

int Solucao::VerificaIteradorDescarregamento( ItDescarregamento it1, double HorarioInicioAuxiliar, double HorarioFinalAuxiliar, int CaminhaoEmAnalise, int PlantaEmAnalise, int DemandaDesalocada ){
	if( it1->HorarioInicioDescarregamento == HorarioInicioAuxiliar){
		if( it1->HorarioFinalDescarregamento == HorarioFinalAuxiliar){
			if( it1->NumCarretaUtilizada == CaminhaoEmAnalise){
				if( it1->NumPlantaFornecedor == PlantaEmAnalise){
					if( it1->NumeroDemandaSuprida == DemandaDesalocada){
						return 1;
					}
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
void Solucao::EncontraPlantaMenorDistanciaConstrucao( int c, int& NumPlantaAnalisando){
	double DistanciaConstrucaoPlanta;

	DistanciaConstrucaoPlanta = DBL_MAX;
	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
			if( PlantasInstancia.PlantasAnalizadas[p] == 0){
				NumPlantaAnalisando = p;
				DistanciaConstrucaoPlanta = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
			}
		}
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

void Solucao::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes ){
	ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
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

int Solucao::DetetaAlocacaoTarefa(int Construcao, int Demanda, int& NumeroCarreta, int& NumeroPlanta,double& HorarioInicioFabrica, double& HorarioSaiFabrica, double& HorarioInicioDescarregamento, double& HorarioFinalDescarregamento,double& HorarioRetornaFabrica){

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

	int 	AlocouAux;
	bool 	DesalocadoDescarregamento;
	int 	pAxu;
	int 	vAux;

//Inicializa
	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	RetornaIndiceDemanda(c, Demanda,d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::DetetaAlocacaoTarefa  [" << Construcao << "-" << Demanda << "] >>>>>>>>>>> " << endl;
		return -1;
	}

// Carrega dados da tarefa
	ConstrucoesInstancia.Construcoes[c].RetornaDadosDescarregamento( d,PlantaEmAnalise, CaminhaoEmAnalise, ConstrucaoEmAnalise, DemandaDesalocada, HorarioInicioAuxiliar, HorarioFinalAuxiliar);

	//cout << endl << endl << "  Planta " << PlantaEmAnalise << " Caminhao " << CaminhaoEmAnalise << " Construcao " << ConstrucaoEmAnalise;
	//cout << " Demanda " << DemandaDesalocada << " HorarioInicio " << HorarioInicioAuxiliar << " HorarioFinalAuxiliar " << HorarioFinalAuxiliar << endl;

// Desaloca descarregamento na construção
	DesalocadoDescarregamento = 0;
	for( ItDescarregamento it1 = ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin(); it1 != ConstrucoesInstancia.Construcoes[c].Descarregamentos.end(); it1++){
		if ( VerificaIteradorDescarregamento(it1, HorarioInicioAuxiliar, HorarioFinalAuxiliar, CaminhaoEmAnalise, PlantaEmAnalise, DemandaDesalocada ) == 1){
			It1Aux = it1;
			DesalocadoDescarregamento = 1;
			//cout << " ++++++++++++++++= ### Dados: carreta " << it1->NumCarretaUtilizada << "  demanda "<< it1->NumeroDemandaSuprida << "  ("<< it1->HorarioInicioDescarregamento << "-"<< it1->HorarioFinalDescarregamento << ")"<< endl;
		}
	}

	if( DesalocadoDescarregamento == 0){
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Nao conseguiu desalocar &&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}

	HorarioInicioDescarregamento = It1Aux->HorarioInicioDescarregamento;
	HorarioFinalDescarregamento = It1Aux->HorarioFinalDescarregamento;
	NumeroCarreta = It1Aux->NumCarretaUtilizada;
	NumeroPlanta = It1Aux->NumPlantaFornecedor;


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
				if( VerificaIteradorCarregamento( it2, CaminhaoEmAnalise, ConstrucaoEmAnalise, DemandaDesalocada) == 1){
					//cout <<  "        Deleta planta " << endl;
					It2Aux = it2;
					pAxu = p;
					AlocouPonteiroCarregamento = 1;
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
						if( it3->NumeroConstrucao == ConstrucaoEmAnalise && it3->NumeroDemandaSuprida == DemandaDesalocada){
								It3Aux = it3;
								vAux = v;
								AlocouPonteiroDeslocamento[p] = 1;
						}
					}
					if( AlocouPonteiroDeslocamento[p] == 1){

						HorarioInicioFabrica = It3Aux->HorarioInicioDeslocamento;
						HorarioRetornaFabrica = It3Aux->HorarioFinalDeslocamento;

						PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[vAux].Deslocamentos.erase(It3Aux);
						PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[vAux].NumeroDeDemandasAntendidas = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[vAux].NumeroDeDemandasAntendidas - 1;
						//cout << endl << endl << "   Entrou para desalocar " << endl << endl;

					}
				}
			}
		}
	}

	if( AlocouPonteiroCarregamento == 1){

		HorarioSaiFabrica = It2Aux->HorarioFinalCarregamento;

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

int Solucao::DeletaAlocacaoTarefasPosteriores(int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasDesalocadas){

	int c;
	int d;

	int NumeroCarreta;
	int NumeroPlanta;
	double HorarioInicioFabrica;
	double HorarioSaiFabrica;
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	double HorarioRetornaFabrica;

	vector < int > DemandaDesalocar;

	bool ConseguiDesalocar;

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	RetornaIndiceDemanda(c, Demanda,d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::MarcaTarefaDeletadaNoVetor  >>>>>>>>>> " << endl;
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
			ConseguiDesalocar = DetetaAlocacaoTarefa(Construcao, DemandaDesalocar[i], NumeroCarreta, NumeroPlanta, HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioRetornaFabrica);

			DadosTarefasDesalocadas.resize(DadosTarefasDesalocadas.size() + 1);
			DadosTarefasDesalocadas[DadosTarefasDesalocadas.size() - 1].IniciaConteudo();
			DadosTarefasDesalocadas[DadosTarefasDesalocadas.size() - 1].InserirConteudo(Construcao, DemandaDesalocar[i],NumeroPlanta,NumeroCarreta,HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento,HorarioRetornaFabrica);

			//cout << endl << " Delteou Carreta [" << NumeroPlanta << "-" << NumeroCarreta;
			//cout << " da construcao [" << Construcao << "-" << DemandaDesalocar[i] << "]";
			//cout << " do periodo de descarregamento (" << HorarioInicioDescarregamento << "-" << HorarioFinalDescarregamento << ") -> Solucao::DeletaAlocacaoTarefasPosteriores" << endl;
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

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::MarcaTarefaDeletadaNoVetor  >>>>>>>>>> " << endl;
	}

	ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] = 1;
}

int Solucao::AdicionaTarefaHorarioInicioDescarregamento( int Construcao, int Demanda , double HorarioInicioDescarregamento){
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

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::AdicionaTarefaHorarioInicioDescarregamento  >>>>>>>>>> " << endl;
		return -1;
	}



	if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
		PlantasInstancia.InicializaPlantasAnalizadas();

		do{
			EncontraPlantaMenorDistanciaConstrucao(c, NumPlantaAnalisando);
			if(NumPlantaAnalisando == -13){
				cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  -> AdicionaTarefa &&&&&&&&&&&&& " << endl << endl << endl;
			}


			PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();

			//cout << endl << endl << "    (((((+++ Situação carragamentos " << endl ;
			//PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Imprime(0);
			//cout << endl << endl;

			for( int v = 0; v < PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){
				HorarioChegaContrucao = HorarioInicioDescarregamento;
				HorarioInicioPlanta = HorarioChegaContrucao - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;

				if( HorarioInicioPlanta < PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento){
					HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento;
				}
				//cout << "    Carreta usada [" << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << "-" << PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "]";
				//out << " Construcao e Demanda [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" <<  Demanda << "]" << endl;
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
								ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento + 1;
								PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].AlocaAtividade(HorarioInicioPlanta, HorarioRetornaPlanta, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , d);
								PlantasInstancia.Plantas[NumPlantaAnalisando].AlocaAtividade(HorarioInicioPlanta, HorarioSaiDaPlanta, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , d,  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta);
								ConstrucoesInstancia.Construcoes[c].AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, d,  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta,0,0,0);
								ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
								//cout << "		PLanta (" <<  HorarioInicioPlanta << "-" << HorarioSaiDaPlanta << " trajeto " << HorarioChegaContrucao << " - " << HorarioSaiConstrucao << " trajeto " << HorarioRetornaPlanta << ") " << endl;

								ConstrucoesInstancia.OrdenaDescarregamentosConstrucoesOrdemCrescente();
								ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
								//cout << "      -> Adicionou construcao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]";
								//cout << " construcao ("<< HorarioChegaContrucao <<"-" << HorarioSaiConstrucao << ")";
								//cout << " planta [" << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << "] (" << HorarioInicioPlanta << "-" << HorarioSaiDaPlanta <<")";
								//cout << " caminhao  [" << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << "-"<< PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "]";
								//cout << " (" << HorarioInicioPlanta << "-" << HorarioRetornaPlanta << ") -> Solucao::AdicionaTarefa" << endl;
								return 1;
							}else{
								if( DisponibilidadeConstrucao == 2){
									cout << endl << endl << "  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      Possivel Alocação anterior    >>>>>>>>>>>>> " << endl << endl;
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

		//cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]   -> AdicionaTarefa &&&&&&&&&&&&& " << endl;

		return 0;

	}else{
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Construcao [" << c << "-" << d << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}

}

int Solucao::AdicionaTarefa( int Construcao, int Demanda ){
	int c;
	int d;

	int NumPlantaAnalisando;
	//int ParaPrograma;

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::AdicionaTarefa  c[" <<  Construcao << "-" << c ;
		cout << "]   d[" << Demanda << "-" << d << "]    >>>>>>>>>>>> " << endl;
	}

	if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
		PlantasInstancia.InicializaPlantasAnalizadas();




		do{
			EncontraPlantaMenorDistanciaConstrucao(c, NumPlantaAnalisando);
			if(NumPlantaAnalisando == -13){
				cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  -> AdicionaTarefa &&&&&&&&&&&&& " << endl << endl << endl;
			}



			PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();

			//cout << endl << endl << "    (((((+++ Situação carragamentos " << endl ;
			//PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Imprime(0);
			//cout << endl << endl;

			for( int v = 0; v < PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){
				if( (ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta) > PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento){
					HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
				}else{
					HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento;
				}
				//cout << "    Carreta usada [" << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << "-" << PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "]";
				//out << " Construcao e Demanda [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" <<  Demanda << "]" << endl;
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

								ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento + 1;
								PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].AlocaAtividade(HorarioInicioPlanta, HorarioRetornaPlanta, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , d);
								PlantasInstancia.Plantas[NumPlantaAnalisando].AlocaAtividade(HorarioInicioPlanta, HorarioSaiDaPlanta, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao , d,  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta);
								ConstrucoesInstancia.Construcoes[c].AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, d,  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta,0,0,0);
								ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
								//cout << "		PLanta (" <<  HorarioInicioPlanta << "-" << HorarioSaiDaPlanta << " trajeto " << HorarioChegaContrucao << " - " << HorarioSaiConstrucao << " trajeto " << HorarioRetornaPlanta << ") " << endl;

								ConstrucoesInstancia.OrdenaDescarregamentosConstrucoesOrdemCrescente();
								ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
								//cout << "      -> Adicionou construcao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]";
								//cout << " construcao ("<< HorarioChegaContrucao <<"-" << HorarioSaiConstrucao << ")";
								//cout << " planta [" << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << "] (" << HorarioInicioPlanta << "-" << HorarioSaiDaPlanta <<")";
								//cout << " caminhao  [" << PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta << "-"<< PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "]";
								//cout << " (" << HorarioInicioPlanta << "-" << HorarioRetornaPlanta << ") -> Solucao::AdicionaTarefa" << endl;
								return 1;
							}else{
								if( DisponibilidadeConstrucao == 2){
									cout << endl << endl << "  <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<      Possivel Alocação anterior    >>>>>>>>>>>>> " << endl << endl;
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

		//cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "]   -> AdicionaTarefa &&&&&&&&&&&&& " << endl;

		return 0;

	}else{
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Construcao [" << c << "-" << d << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}

}

int Solucao::ProcessoParaAlocarTarefa( int Construcao, int Demanda, int& NovatarefaAlocadaConstrucao , int& NovatarefaAlocadaDemanda ){
	int c;
	int d;

	int Alocou;
	Alocou = 0;

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::AdicionaTarefa  >>>>>>>>>> " << endl;
	}


	for( unsigned int contrucoes = 0; contrucoes < ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas; demandas++){
			if( contrucoes != c){
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					//cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "]  -> Solucao::ProcessoParaAlocarTarefa";
					Alocou = AdicionaTarefa(ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas);

					if( Alocou == 1){

						//cout << " => Alocou [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ProcessoParaAlocarTarefa" << endl;
						NovatarefaAlocadaConstrucao = ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao;
						NovatarefaAlocadaDemanda = demandas;

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

int Solucao::ReadicionaTarefasHoraInicioDescarregamento(int Construcao, int Demanda, double HoraInicioDescarregamento){
	int c;
	int d;

	int Alocou;
	int Ativa;

	vector < DadosTarefa > AuxiliarLixo;

	Ativa = 0;

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::ReadicionaTarefasHoraInicioDescarregamento  >>>>>>>>>> " << endl;
	}

	//cout << endl << " situacao alocacao [";
	for ( int demandas = d; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
		//cout << " ->[" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
		if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
			Alocou = AdicionaTarefaHorarioInicioDescarregamento(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, HoraInicioDescarregamento);
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

int Solucao::ReadicionaTarefas(int Construcao, int Demanda){
	int c;
	int d;

	int Alocou;
	int Ativa;

	double HorarioInicioDescarregamento;

	int TarefaDeletada;

	vector < DadosTarefa > AuxiliarLixo;

	Ativa = 0;

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::ReadicionaTarefas  >>>>>>>>>> " << endl;
	}


	for ( int demandas = d; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
		//cout << " ->[" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
		if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
			Alocou = AdicionaTarefa(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas);
			if( Alocou == -1 && demandas > d){

				//ConstrucoesInstancia.ImprimeContrucoes();

				ConstrucoesInstancia.Construcoes[c].RetornaHorarioInicioCarregamento(d, HorarioInicioDescarregamento);
				//cout << endl << endl << "    =======>>>>>>  Entrou  => demanda [" <<  ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << d << "] no horario " <<  HorarioInicioDescarregamento << endl;

				do{
					HorarioInicioDescarregamento = HorarioInicioDescarregamento + IntervaloDeTempo;
					TarefaDeletada = DeletaAlocacaoTarefasPosteriores(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao, d, AuxiliarLixo);
					Alocou = ReadicionaTarefasHoraInicioDescarregamento(ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao, d, HorarioInicioDescarregamento);
					//cout << "*" ;

				}while(  Alocou == -1);
			}

			if( Alocou == 1){
				//cout << "   +++ Realocou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
				Ativa = 1;
			}else{
				//cout << "   *** Nao Realocou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ReadicionaTarefas" << endl;
			}
		}
	}
	if( Ativa == 1){
		return 1;
	}else{
		return 0;
	}
}

int Solucao::ReadicionaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasDesalocadas){

	for(unsigned int t = 0; t < DadosTarefasDesalocadas.size(); t++){
		int c;
		int d;
		int p;
		int v;

		AlocaValoresIniciaisIndices(c,d);
		AlocaValoresIniciaisIndices(p,v);
		RetornaIndiceConstrucao(DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[0], c );
		VerificaIndiceDemandaAlemSituacaoAtendimentoDemanda(c, DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[1], d);
		RetornaIndicePlanta(DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[2], p);
		RetornaIndiceVeiculo(p, DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[3], v);

		if( VerificaInidices(c,d) == -1 ||  VerificaInidices2(p,v) == -1 ){
			cout << "  <<<<<<<<<<<<<<    Solucao::ReadicionaTarefasApartirDeDados  >>>>>>>>>> " << endl;
			 return 0;
		}


		ConstrucoesInstancia.Construcoes[c].AlocaAtividade( DadosTarefasDesalocadas[t].HorariosDasTarefasRetiradas[2],DadosTarefasDesalocadas[t].HorariosDasTarefasRetiradas[3], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[1], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[3], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[2], 0, 0, 0);
		ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento + 1;
		ConstrucoesInstancia.Construcoes[c].OrdenaDescarregamentosEmOrdemCrescente();
		ConstrucoesInstancia.Construcoes[c].MarcaInicioFimDescarregamentos();
		ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;

		PlantasInstancia.Plantas[p].AlocaAtividade(DadosTarefasDesalocadas[t].HorariosDasTarefasRetiradas[0], DadosTarefasDesalocadas[t].HorariosDasTarefasRetiradas[1], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[0], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[1], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[3] );

		PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].AlocaAtividade( DadosTarefasDesalocadas[t].HorariosDasTarefasRetiradas[0], DadosTarefasDesalocadas[t].HorariosDasTarefasRetiradas[4], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[0], DadosTarefasDesalocadas[t].DadosDasTarefasRetiradas[1]);

	}
	//ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	return 1;

}

void Solucao::MarcaTarefaNaoDeletadaNoVetor(int Construcao, int Demanda){
	int c;
	int d;

	AlocaValoresIniciaisIndices(c,d);
	RetornaIndiceConstrucao(Construcao, c );
	VerificaIndiceDemanda(c, Demanda, d);
	if( VerificaInidices(c,d) == -1){
		cout << "  <<<<    Solucao::ReadicionaTarefas  >>>>>>>>>> " << endl;
	}
	ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] = 0;
}

int Solucao::ConstrucaoTarefaRemover(int& Construcao, int& Demanda){

	//ConstrucoesInstancia.ImprimeContrucoes();

	double RankInicial;
	int Ativo;

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
		//cout << " Selecionou construcao " << Construcao << "-" << Demanda << " com janela de tempo ";
		//cout <<  ConstrucoesInstancia.Construcoes[Construcao].TempoMinimoDeFuncionamento << "-" << ConstrucoesInstancia.Construcoes[Construcao].TempoMaximoDeFuncionamento;
		//cout << " -> ConstrucaoTarefaRemover" << endl ;
		return 1;
	}else{
		return 0;
	}
}

void Solucao::ProcessoViabilizacao1(){

	int InviabilidadeSolucaoAnterior;
	bool ExisteTarefa;

	bool TarefaDeletada;

	int NovatarefaAlocadaConstrucao;
	int NovatarefaAlocadaDemanda;

	bool TarefaAlocada;

	int Readicionou;

	int ConstrucaoAnalisandoRetirada;
	int DemandaAnalisandoRetirada;

	//int PararPrograma;

	int NumeroCarreta;
	int NumeroPlanta;
	double HorarioInicioFabrica;
	double HorarioSaiFabrica;
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	double HorarioRetornaFabrica;

	vector < DadosTarefa > DadosTarefasDesalocadas;
	vector < DadosTarefa > AuxiliarLixo;

	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	ExisteTarefa = ConstrucaoTarefaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

	if( ExisteTarefa == 1){
		do{

			//cout << endl << "   Deleta tarefas [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl ;

			DadosTarefasDesalocadas.clear();


			TarefaDeletada = DeletaAlocacaoTarefasPosteriores(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, DadosTarefasDesalocadas);
			MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

			//cout  << endl << endl << " Imprime Vetor de dados " << endl << endl;
			//for (unsigned int i = 0; i < DadosTarefasDesalocadas.size(); i++ ){
			//	DadosTarefasDesalocadas[i].Imprimir();
			//}




			if ( TarefaDeletada == 1){
				AlocaValoresIniciaisIndices( NovatarefaAlocadaConstrucao, NovatarefaAlocadaDemanda);

				//cout << endl << "   Tenta adicionar " << endl ;
				TarefaAlocada = ProcessoParaAlocarTarefa( ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovatarefaAlocadaConstrucao , NovatarefaAlocadaDemanda);



				if( TarefaAlocada == 1){
					Readicionou = ReadicionaTarefas(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);



					if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
						//cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;
						MarcaTarefaNaoDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);
					}else{
						//cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;
						if( Readicionou == 1) {
							//cout <<  endl << "  Deleta tarefas antigas recolocadas [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" <<  endl;
							TarefaDeletada = DeletaAlocacaoTarefasPosteriores(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, AuxiliarLixo);
						}
						//cout <<  endl << "  Deleta tarefa adicionada [" << NovatarefaAlocadaConstrucao << "-" << NovatarefaAlocadaDemanda << "]" <<  endl;





						TarefaDeletada = DetetaAlocacaoTarefa(NovatarefaAlocadaConstrucao , NovatarefaAlocadaDemanda, NumeroCarreta, NumeroPlanta, HorarioInicioFabrica, HorarioSaiFabrica, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioRetornaFabrica);
						//cout <<  endl << "  Recoloca tarefas antigas para refazer solucao inicial [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" <<  endl;
						ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas );
					}
				}else{
					//cout << endl << endl << "   Nao consegui adicionar nova tarefa" << endl << endl;
					ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas );
				}
			}else{
				 cout << endl << endl << endl << "   #######################  Tarefa nao deletada ######################## " << endl << endl << endl;
			}

			InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
			ExisteTarefa = ConstrucaoTarefaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada);

			//if( ExisteTarefa == 1){
				//cout << " Selecionou a Analisar [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "] ";
				//cout << "( situacao demanda = " << ConstrucoesInstancia.Construcoes[ConstrucaoAnalisandoRetirada].SituacaoDemanda[DemandaAnalisandoRetirada] << " e ";
				//cout << "situacao remocao = " << ConstrucoesInstancia.Construcoes[ConstrucaoAnalisandoRetirada].SituacaoRemocao[DemandaAnalisandoRetirada]  << ")" << endl;
			//}

			//cout << endl << endl << "       $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
			//ConstrucoesInstancia.ImprimeContrucoes();
			//cin >> PararPrograma;

		}while( ExisteTarefa == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0);
	}
}

int  Solucao::ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida){
	int ConstrucaoTemporario;
	int IndiceConstrucaoTemporario;
	int DemandaTemporaria;
	ConstrucaoTemporario = -13;
	DemandaTemporaria = -13;
	double DistanciaPlantaTemporaria;
	DistanciaPlantaTemporaria = DBL_MAX;

	for ( int i = 0; i < NE; i++){
		for ( int d = 0; d < ConstrucoesInstancia.Construcoes[i].NumeroDemandas ; d++){
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

void Solucao::ProcessoViabilizacao2(){

	int InviabilidadeSolucaoAnterior;
	int ExisteTarefa;

	int	ConstrucaoNaoAtendida;
	int IndiceConstrucaoNaoAtendida;
	int DemandaNaoAtendida;

	vector < double > TempoSaiPlanta;

	int PlantaAux;

	double DistanciaAux;

	vector < DadosTarefa > DadosTarefasDesalocadas;
	int TarefaDeletada;
	int TarefaAdicionada;

	int PararPrograma;

	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	ExisteTarefa = ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);

	do{
		TempoSaiPlanta.resize(NP);
		cout << " ConstrucaoNaoAtendida = " << ConstrucaoNaoAtendida <<" DemandaNaoAtendida = " << DemandaNaoAtendida << endl;
		RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida);

		for( int p = 0; p < NP; p++){
			TempoSaiPlanta[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia;
		}
		if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento > 0){
			for( unsigned int d = 0; d < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos.size(); d++ ){
				for( int p = 0; p < NP; p++){
					if( TempoSaiPlanta[p] < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia){
						TempoSaiPlanta[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia;
					}
				}
			}
		}

		for( int p = 0; p < NP; p++){
			cout << " TempoSaiPlanta[" << p << "] = " << TempoSaiPlanta[p] << endl;
		}

		for( int c = 0; c < NE; c++){
			for(unsigned int d = 0; d < ConstrucoesInstancia.Construcoes[c].Descarregamentos.size() ; d++){
				PlantaAux = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;
				DistanciaAux = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[ PlantaAux ].Distancia;
				if( ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento - DistanciaAux > TempoSaiPlanta[PlantaAux]){
					cout << "	-> Planta = " << PlantaAux << "   Construcao = " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " (" << c << ")" << endl;
					ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].Imprime();
					TarefaDeletada = DeletaAlocacaoTarefasPosteriores( ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumeroDemandaSuprida, DadosTarefasDesalocadas);
					if( TarefaDeletada == 1){
						cout << "                  Tarefa deletada " << endl << endl;
					}

				}
			}
		}
		TarefaAdicionada = AdicionaTarefa( ConstrucaoNaoAtendida, DemandaNaoAtendida );
		if( TarefaAdicionada == 1){
			cout << "                  Tarefa adicionada " << endl << endl;
		}else{
			cout << "                  Tarefa NAO adicionada " << endl << endl;
			ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] = -1;
		}
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
		cin >> PararPrograma;



		ExisteTarefa = ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);
		cout << endl;
	}while( ExisteTarefa == 1);
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
