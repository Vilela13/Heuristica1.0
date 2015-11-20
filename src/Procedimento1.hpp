/*
 * Procedimento1.hpp
 *
 *  Created on: Aug 20, 2015
 *      Author: mateus.vilela
 */

#ifndef PROCEDIMENTO1_HPP_
#define PROCEDIMENTO1_HPP_

#include "DadosParaReordenar.hpp"

class Procedimento1{

public:
	Procedimento1();

	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	void CarregaDados(int , ConjuntoPlantas, int, ConjuntoConstrucoes, int, double, double );

// Seleciona uma construção baseada em um rank que elas possuem
	int SelecionaConstrucao( Construcao**, vector < int >);
// Seleciona a planta mais perto
	int SelecionaPlanta( Planta** , Construcao*, vector < int > );
// Seleciona carreta menos utilizada
	int SelecionaCarreta(Planta& , Construcao& , int, int, int);

	int AnalizouTodasPLanats(vector < int > );
	void ConfereSeNaoEncontrouUmaPlanta( int);
	void VerificaAlocacaoDemandaConstrucao(Construcao*, int&);

	int Executa(int);


    ~Procedimento1();

};

Procedimento1::Procedimento1(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
}

void Procedimento1::CarregaDados(int InstNP, ConjuntoPlantas InstPlantasInstancia, int InstNE, ConjuntoConstrucoes InstConstrucoesInstancia, int InstNV, double InstVelocidade, double InstTempoDeVidaConcreto){
	NP = InstNP;
	PlantasInstancia = InstPlantasInstancia;
	NE = InstNE;
	ConstrucoesInstancia  = InstConstrucoesInstancia;
	NV = InstNV;
	Velocidade = InstVelocidade;
	TempoDeVidaConcreto = InstTempoDeVidaConcreto;
}

int Procedimento1::SelecionaConstrucao( Construcao** ConstrucaoVaiSerSuprida , vector < int > ConstrucoesAnalizadas){
	int Ativo;
	double RankInicial;

	Ativo = 0;
	RankInicial = DBL_MAX;

	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas &&  ConstrucoesAnalizadas[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] == 0){
				*ConstrucaoVaiSerSuprida = &ConstrucoesInstancia.Construcoes[c];
				RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
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

int Procedimento1::SelecionaPlanta( Planta** PlantaMaisPerto,Construcao* ConstrucaoVaiSerSuprida, vector < int > PlantasAnalizadas ){
	int Ativo;
	double DistanciaConstrucaoPlanta;

	Ativo = 0;
	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucaoVaiSerSuprida->DistanciaPlantas[p].Distancia){
			if( PlantasAnalizadas[p] == 0){
				*PlantaMaisPerto = &PlantasInstancia.Plantas[p];
				DistanciaConstrucaoPlanta = ConstrucaoVaiSerSuprida->DistanciaPlantas[p].Distancia;
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

int Procedimento1::SelecionaCarreta(Planta& PlantaMaisPerto, Construcao& ConstrucaoVaiSerSuprida, int  NumeroDemanda, int SituacaoDemanda, int TipoOrdenacao ){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	//int Para;

	if( ConstrucaoVaiSerSuprida.SituacaoDemanda[NumeroDemanda] == 0){
		PlantaMaisPerto.VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
		//PlantaMaisPerto.VeiculosDaPlanta.Imprime(0);
		//cin >> Para;

		for( int v = 0; v < PlantaMaisPerto.NumeroVeiculos; v++){
			if( (ConstrucaoVaiSerSuprida.TempoMinimoDeFuncionamento - PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao] - PlantaMaisPerto.TempoPlanta) > PlantaMaisPerto.TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = ConstrucaoVaiSerSuprida.TempoMinimoDeFuncionamento - PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao] - PlantaMaisPerto.TempoPlanta;
			}else{
				HorarioInicioPlanta = PlantaMaisPerto.TempoMinimoDeFuncionamento;
			}
			//cout << "    Carreta usada [" << PlantaMaisPerto.NumeroDaPlanta << "-" << PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "] Construcao e Demanda [" << ConstrucaoVaiSerSuprida.NumeroDaConstrucao << "-" <<  NumeroDemanda << "]" << endl;
			do{
				HorarioSaiDaPlanta = HorarioInicioPlanta + PlantaMaisPerto.TempoPlanta;
				HorarioChegaContrucao = HorarioSaiDaPlanta + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];
				HorarioSaiConstrucao = HorarioChegaContrucao +  PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucaoVaiSerSuprida.NumeroDaConstrucao][NumeroDemanda];
				HorarioRetornaPlanta = HorarioSaiConstrucao + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];

				DisponibilidadePlanta = PlantaMaisPerto.VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeCarreta = PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
				DisponibilidadeConstrucao = ConstrucaoVaiSerSuprida.VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);

				if( DisponibilidadePlanta == 1 && DisponibilidadeCarreta == 1){
					if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
						ConstrucaoVaiSerSuprida.AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantaMaisPerto.NumeroDaPlanta,  0, 1, PlantasInstancia);
						return 1;
					}
				}
				HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
			}while( HorarioInicioPlanta <= PlantaMaisPerto.TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucaoVaiSerSuprida.TempoMaximoDeFuncionamento);
		}
	}
	return 0;
}

void Procedimento1::ConfereSeNaoEncontrouUmaPlanta( int  PlantaSelecionada){
	if( PlantaSelecionada == 0){
		cout  << endl << endl << endl;
		cout << " ##############################################################" << endl;
		cout << "           Não encontrou Planta para se alocar " << endl;
		cout << " ##############################################################" << endl;
		cout << endl << endl;
	}
}
void Procedimento1::VerificaAlocacaoDemandaConstrucao(Construcao *ConstrucaoVaiSerSuprida, int &Viabilidade){
	if( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas ){
		cout << endl;
		cout << " ##############################################################" << endl;
		cout << "           Não consigo alocar demandas da contrucao " << ConstrucaoVaiSerSuprida->NumeroDaConstrucao << endl;
		cout << " ##############################################################" << endl;
		Viabilidade = 0;
	}
}

int Procedimento1::Executa( int TipoOrdenacao){
	Planta* PlantaMaisPerto;
	Construcao* ConstrucaoVaiSerSuprida;

	int ConstrucaoSelecionada;
	int PlantaSelecionada;
	int Demanda;
	int Viabilidade;
	int PermiteAtendimentoDemanda;

	int paraPrograma;

	Viabilidade = 1;

	ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		ConstrucaoSelecionada = SelecionaConstrucao( &ConstrucaoVaiSerSuprida, ConstrucoesInstancia.ConstrucoesAnalizadas);
		if( ConstrucaoSelecionada == 1){
			ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucaoVaiSerSuprida->NumeroDaConstrucao] =  1;
			do{
				PlantasInstancia.InicializaPlantasAnalizadas();
				Demanda = ConstrucaoVaiSerSuprida->StatusAtendimento;
				PermiteAtendimentoDemanda = 0;
				do{
					PlantaSelecionada = SelecionaPlanta( &PlantaMaisPerto , ConstrucaoVaiSerSuprida, PlantasInstancia.PlantasAnalizadas );
					ConfereSeNaoEncontrouUmaPlanta( PlantaSelecionada);
					if( PlantaSelecionada == 1){
						PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 1;
						PermiteAtendimentoDemanda = SelecionaCarreta(*PlantaMaisPerto , *ConstrucaoVaiSerSuprida,  Demanda, 1, TipoOrdenacao);
					}
				}while( PermiteAtendimentoDemanda == 0 && PlantasInstancia.AnalizouTodasPLanats() == 0);
				if( PermiteAtendimentoDemanda == 1){
					PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 0;
				}
			}while( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas && PlantasInstancia.AnalizouTodasPLanats() == 0);
			VerificaAlocacaoDemandaConstrucao(ConstrucaoVaiSerSuprida, Viabilidade);
		}else{
			cout << endl << endl << " &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& " << endl << endl;
		}
	}
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	if( Viabilidade == 1){
		return 1;
	}else{
		return 0;
	}
}

Procedimento1::~Procedimento1(){

}

#endif /* PROCEDIMENTO1_HPP_ */
