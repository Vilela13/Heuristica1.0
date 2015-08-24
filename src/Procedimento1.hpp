/*
 * Procedimento1.hpp
 *
 *  Created on: Aug 20, 2015
 *      Author: mateus.vilela
 */

#ifndef PROCEDIMENTO1_HPP_
#define PROCEDIMENTO1_HPP_

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

	int SelecionaCarreta(Planta& , Construcao& , int);

	int Executa();

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

int Procedimento1::SelecionaCarreta(Planta& PlantaMaisPerto, Construcao& ConstrucaoVaiSerSuprida, int  NumeroDemanda ){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	PlantaMaisPerto.VeiculosDaPlanta.OrdenaCarretasPorNUmeroDeTarefasRealizadas();


	int c = 0;
	HorarioInicioPlanta = PlantaMaisPerto.TempoMinimoDeFuncionamento;
	HorarioSaiDaPlanta = HorarioInicioPlanta + PlantaMaisPerto.TempoPlanta;
	HorarioChegaContrucao = HorarioSaiDaPlanta + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];
	HorarioSaiConstrucao = HorarioChegaContrucao +  PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].TempoParaDescarregarNaConstrucao[c][0];
	HorarioRetornaPlanta = HorarioSaiConstrucao + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];

	cout << endl << endl;
	cout << " Horario inicio planta = " << HorarioInicioPlanta << endl;
	cout << " Horario que sai da planta = " << HorarioSaiDaPlanta << endl;
	cout << " Horario que chega na construcao = " << HorarioChegaContrucao << endl;
	cout << " Horario que sai da construcao = " << HorarioSaiConstrucao << endl;
	cout << " Horario que retorna a planta = " << HorarioRetornaPlanta << endl << endl;

	DisponibilidadePlanta = PlantaMaisPerto.VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
	cout << " Disponibilidade Planta = " << DisponibilidadePlanta << endl ;

	DisponibilidadeConstrucao = ConstrucaoVaiSerSuprida.VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
	cout << " Disponibilidade Construcao = " << DisponibilidadeConstrucao << endl ;

	DisponibilidadeCarreta = PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
	cout << " Disponibilidade Caminhao = " << DisponibilidadeCarreta << endl ;

	if( DisponibilidadePlanta == 1){
		if( DisponibilidadeConstrucao == 1){
			if( DisponibilidadeCarreta == 1){
				ConstrucaoVaiSerSuprida.StatusAtendimento = ConstrucaoVaiSerSuprida.StatusAtendimento + 1;
				PlantaMaisPerto.AlocaAtividade(HorarioInicioPlanta, HorarioSaiDaPlanta, ConstrucaoVaiSerSuprida.NumeroDaConstrucao, NumeroDemanda, &( PlantaMaisPerto.VeiculosDaPlanta.Carretas[c] ) );
				PlantaMaisPerto.Imprime();
				ConstrucaoVaiSerSuprida.AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, NumeroDemanda,  &( PlantaMaisPerto.VeiculosDaPlanta.Carretas[c] ) );
				ConstrucaoVaiSerSuprida.ImprimeContrucao();
				PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].AlocaAtividade(HorarioInicioPlanta, HorarioRetornaPlanta, ConstrucaoVaiSerSuprida.NumeroDaConstrucao, NumeroDemanda);
				PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].Imprime();
			}
		}
	}

	return 1;


}

int Procedimento1::Executa(){
	Planta* PlantaMaisPerto;
	Construcao* ConstrucaoVaiSerSuprida;
	double RankInicial;
	double DistanciaConstrucaoPlanta;
	int PermiteAtendimentoDemanda;

	int Demanda;

	vector < int > PLantasAnalizadas;
	PLantasAnalizadas.resize(NP);

	for( int p = 0; p < NP; p++){
		PLantasAnalizadas[p] = 0;
	}


	RankInicial = DBL_MAX;

	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas && ConstrucoesInstancia.Construcoes[c].StatusAtendimento == 0){
			ConstrucaoVaiSerSuprida = &ConstrucoesInstancia.Construcoes[c];
			RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
		}
	}

	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucaoVaiSerSuprida->DistanciaPlantas[p].Distancia ){
			PlantaMaisPerto = &PlantasInstancia.Plantas[p];
			DistanciaConstrucaoPlanta = ConstrucaoVaiSerSuprida->DistanciaPlantas[p].Distancia;
		}
	}

	cout << endl << "Construcao e planta selecionadas " << endl << endl;
	ConstrucaoVaiSerSuprida->ImprimeContrucao();
	PlantaMaisPerto->Imprime();

	PLantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 1;

	Demanda = 0;

	PermiteAtendimentoDemanda = SelecionaCarreta(*PlantaMaisPerto , *ConstrucaoVaiSerSuprida,  Demanda);


	Demanda = 1;


	for( int d = Demanda; d < ConstrucaoVaiSerSuprida->NumeroDemandas; d++){
		cout << " Demanda a ser atendida ainda = " << d << endl;
	}
	return 1;
}

Procedimento1::~Procedimento1(){

}




#endif /* PROCEDIMENTO1_HPP_ */
