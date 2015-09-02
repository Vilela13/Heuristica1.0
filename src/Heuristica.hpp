/*
 * Heuristica.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef HEURISTICA_HPP_
#define HEURISTICA_HPP_

#include "Bibliotecas.hpp"

#define ItCarregamento vector< Carregamento >::iterator
#define ItDeslocamento vector< Deslocamento >::iterator

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
	int StatusSolucao;

	void CarregaSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double, int);
	void Imprime();

	int Viabilidade1();

	~Solucao();
};

Solucao::Solucao(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
	StatusSolucao = -13;

}

void Solucao::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC, int status){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
	StatusSolucao = status;
}

void Solucao::Imprime(){
	PlantasInstancia.Imprime();
	ConstrucoesInstancia.ImprimeContrucoes();

}

int Solucao::Viabilidade1(){
/*	cout << " 		Entregas  " << endl;
	for(  int c = 0; c < NE; c++ ){
		cout << " Contrucao " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << endl;
		for ( int w = 0; w < ConstrucoesInstancia.Construcoes[c].StatusAtendimento; w++){
			cout << endl << " W = " << w << endl;

		}
	}
*/

	int PlantaEmAnalise;
	int CaminhaoEmAnalise;
	int ConstrucaoEmAnalise;
	int DemandaDesalocada;
	double HorarioInicioAuxiliar;
	double HorarioFinalAuxiliar;

	int c;
	c = 0;
	int d;
	d = 0;

	ItCarregamento it1Aux;
	ItDeslocamento it2Aux;

	if( 0 < ConstrucoesInstancia.Construcoes[c].StatusAtendimento ){
		cout << endl << endl;
		cout << " contrucao " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
		PlantaEmAnalise =  ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;
		ConstrucaoEmAnalise = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
		DemandaDesalocada = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumeroDemandaSuprida;
		CaminhaoEmAnalise = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada;
		HorarioInicioAuxiliar = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento;
		HorarioFinalAuxiliar = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento;
		cout << " planta " << PlantaEmAnalise << " construcao " << ConstrucaoEmAnalise << " demanda " << DemandaDesalocada << " caminhao " << CaminhaoEmAnalise << endl;

		if ( ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin()->HorarioInicioDescarregamento == HorarioInicioAuxiliar && ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin()->HorarioFinalDescarregamento == HorarioFinalAuxiliar && ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin()->NumCarretaUtilizada == CaminhaoEmAnalise && ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin()->NumPlantaFornecedor == PlantaEmAnalise && ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin()->NumCarretaUtilizada ==  CaminhaoEmAnalise ){
			cout << endl << "  Deleta construcao" << endl;
			ConstrucoesInstancia.Construcoes[c].Descarregamentos.erase( ConstrucoesInstancia.Construcoes[c].Descarregamentos.begin() );
			ConstrucoesInstancia.Construcoes[c].StatusAtendimento = ConstrucoesInstancia.Construcoes[c].StatusAtendimento - 1;
			ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade + 1;
		}else{
			cout << endl << endl << endl << "   FUDEU " << endl << endl << endl;
		}

		for( int p = 0; p < NP; p++){
			if( PlantasInstancia.Plantas[p].NumeroDaPlanta == PlantaEmAnalise ){
				for (ItCarregamento it1 = PlantasInstancia.Plantas[p].Carregamentos.begin() ; it1 != PlantasInstancia.Plantas[p].Carregamentos.end(); it1++){
					if( it1->NumCarretaUtilizada == CaminhaoEmAnalise && it1->NumeroConstrucao ==  ConstrucaoEmAnalise && it1->NumeroDemandaSuprida == DemandaDesalocada){
						cout <<  "        Deletou na planta " << endl;
						it1Aux = it1;
					}
				}
				PlantasInstancia.Plantas[p].Carregamentos.erase(it1Aux);
				for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){
					if( v == CaminhaoEmAnalise ){
						for (ItDeslocamento it2 = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.begin(); it2 != PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.end(); it2++){
							if( it2->NumeroConstrucao == ConstrucaoEmAnalise && it2->NumeroDemandaSuprida == DemandaDesalocada){
								cout << "        Deletou na carreta " << endl;
								it2Aux = it2;
							}
						}
						PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.erase(it2Aux);
						PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDeDemandasAntendidas = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDeDemandasAntendidas - 1;
					}
				}
			}
		}
	}

	return 1;
}

Solucao::~Solucao(){

}

class ConjuntoSolucoes{
public:
	ConjuntoSolucoes();
	vector < Solucao > Solucoes;
	void InsereSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double, int);
	void Imprime();
	~ConjuntoSolucoes();

};

ConjuntoSolucoes::ConjuntoSolucoes(){
}

void ConjuntoSolucoes::InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC, int status){
	Solucao S1;
	S1.CarregaSolucao( np, Plantas, ne, Construcoes, nv, v, TDVC, status);
	Solucoes.push_back(S1);
}

void ConjuntoSolucoes::Imprime(){
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		cout << endl << endl << "   Solucao " << s << endl << endl;
		 Solucoes[s].Imprime();
	}
}

ConjuntoSolucoes::~ConjuntoSolucoes(){

}
void InsereSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double, int);


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

	ConjuntoSolucoes Solucoes;


	Prod1.CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

	//sort ( Prod1.ConstrucoesInstancia.Construcoes.begin(), Prod1.ConstrucoesInstancia.Construcoes.end(), DecideQualContrucaoTemMaiorRank );
	sort ( Prod1.ConstrucoesInstancia.Construcoes.begin(), Prod1.ConstrucoesInstancia.Construcoes.end(), DecideQualContrucaoTemMenorInicioDepoisMaiorRank );

	Prod1.ConstrucoesInstancia.ImprimeContrucoes();

	Solucao = Prod1.Executa();

	if( Solucao == 1 ){
		cout << endl << endl << "  Solucao viavel!    " << endl << endl;
	}else{
		cout << endl << endl << "  Solucao inviavel!    " << endl << endl;
	}

	Solucoes.InsereSolucao(Prod1.NP, Prod1.PlantasInstancia, Prod1.NE, Prod1.ConstrucoesInstancia, Prod1.NV, Prod1.Velocidade, Prod1.TempoDeVidaConcreto, Solucao);
	Solucoes.Imprime();

	Solucoes.Solucoes[0].Viabilidade1();

	Solucoes.Imprime();

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
