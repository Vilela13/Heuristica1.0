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

	void InicializaConstrucaosAnalizadas(vector < int >&);
	void InicializaPlantasAnalizadas(vector < int >&);

	int SelecionaConstrucao( Construcao**, vector < int >);
	int SelecionaPlanta( Planta** , Construcao*, vector < int > );
	int SelecionaCarreta(Planta& , Construcao& , int);

	int AnalizouTodasPLanats(vector < int > );

	void ConfereSeNaoEncontrouUmaPlanta( int);

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

void Procedimento1::InicializaConstrucaosAnalizadas(vector < int >& ConstrucaosAnalizadas){
	ConstrucaosAnalizadas.resize(NE);
	for( int c = 0; c < NE; c++){
		ConstrucaosAnalizadas[c] = 0;
	}
}

void Procedimento1::InicializaPlantasAnalizadas(vector < int >& PlantasAnalizadas){
	PlantasAnalizadas.resize(NP);
	for( int p = 0; p < NP; p++){
		PlantasAnalizadas[p] = 0;
	}
}

int Procedimento1::SelecionaConstrucao( Construcao** ConstrucaoVaiSerSuprida , vector < int > ConstrucaosAnalizadas){
	double RankInicial;
	int Ativo;

	Ativo = 0;
	RankInicial = DBL_MAX;

	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas &&  ConstrucaosAnalizadas[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] == 0){
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
	double DistanciaConstrucaoPlanta;
	int Ativo;

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


int Procedimento1::SelecionaCarreta(Planta& PlantaMaisPerto, Construcao& ConstrucaoVaiSerSuprida, int  NumeroDemanda ){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	PlantaMaisPerto.VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas();

	//PlantaMaisPerto.ImprimeDistancias();


	for( int c = 0; c < PlantaMaisPerto.NumeroVeiculos; c++){
		HorarioInicioPlanta = PlantaMaisPerto.TempoMinimoDeFuncionamento;
		cout << "             Carreta usada [" << PlantaMaisPerto.NumeroDaPlanta << "-" << PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].NumeroDaCarreta << "] Construcao e Demanda [" << ConstrucaoVaiSerSuprida.NumeroDaConstrucao << "-" <<  NumeroDemanda << "]" << endl;
		do{
			HorarioSaiDaPlanta = HorarioInicioPlanta + PlantaMaisPerto.TempoPlanta;
			HorarioChegaContrucao = HorarioSaiDaPlanta + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];
			HorarioSaiConstrucao = HorarioChegaContrucao +  PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].TempoParaDescarregarNaConstrucao[c][0];
			HorarioRetornaPlanta = HorarioSaiConstrucao + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];

			DisponibilidadePlanta = PlantaMaisPerto.VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
			//cout << " 		Disponibilidade Planta = " << DisponibilidadePlanta << endl ;

			DisponibilidadeConstrucao = ConstrucaoVaiSerSuprida.VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
			//cout << " 		Disponibilidade Construcao = " << DisponibilidadeConstrucao << endl ;

			DisponibilidadeCarreta = PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
			//cout << " 		Disponibilidade Caminhao = " << DisponibilidadeCarreta << endl ;

			if( DisponibilidadePlanta == 1){
				if( DisponibilidadeConstrucao == 1){
					if( DisponibilidadeCarreta == 1){
						ConstrucaoVaiSerSuprida.StatusAtendimento = ConstrucaoVaiSerSuprida.StatusAtendimento + 1;
						PlantaMaisPerto.AlocaAtividade(HorarioInicioPlanta, HorarioSaiDaPlanta, ConstrucaoVaiSerSuprida.NumeroDaConstrucao , NumeroDemanda,  PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].NumeroDaCarreta  );
						//PlantaMaisPerto.Imprime();
						ConstrucaoVaiSerSuprida.AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, NumeroDemanda,  PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].NumeroDaCarreta, PlantaMaisPerto.NumeroDaPlanta );
						//ConstrucaoVaiSerSuprida.ImprimeContrucao();
						PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].AlocaAtividade(HorarioInicioPlanta, HorarioRetornaPlanta, ConstrucaoVaiSerSuprida.NumeroDaConstrucao , NumeroDemanda);
						//PlantaMaisPerto.VeiculosDaPlanta.Carretas[c].Imprime();

						return 1;
					}
				}
			}
			HorarioInicioPlanta = HorarioInicioPlanta + 0.016666;
		}while( HorarioSaiDaPlanta <= PlantaMaisPerto.TempoMaximoDeFuncionamento ||  HorarioSaiConstrucao <= ConstrucaoVaiSerSuprida.TempoMaximoDeFuncionamento);
	}

	return 0;


}

int Procedimento1::AnalizouTodasPLanats(vector < int > PlantasAnalizadas){
	for ( int p = 0; p < NP; p++){
		if( PlantasAnalizadas[p] == 0){
			return 0;
		}
	}
	return 1;
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

int Procedimento1::Executa(){
	Planta* PlantaMaisPerto;
	Construcao* ConstrucaoVaiSerSuprida;

	int ConstrucaoSelecionada;
	int PlantaSelecionada;
	int Demanda;

	int Viabilidade;


	int PermiteAtendimentoDemanda;

	vector < int > PlantasAnalizadas;
	vector < int > ConstrucaosAnalizadas;

	Viabilidade = 1;

	InicializaConstrucaosAnalizadas(ConstrucaosAnalizadas);

	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		cout << "Construcao " << c << endl;

		ConstrucaoSelecionada = SelecionaConstrucao( &ConstrucaoVaiSerSuprida, ConstrucaosAnalizadas);

		if( ConstrucaoSelecionada == 1){

			ConstrucaosAnalizadas[ConstrucaoVaiSerSuprida->NumeroDaConstrucao] =  1;
			do{

				InicializaPlantasAnalizadas(PlantasAnalizadas);

				Demanda = ConstrucaoVaiSerSuprida->StatusAtendimento;

				PermiteAtendimentoDemanda = 0;

				do{
					PlantaSelecionada = SelecionaPlanta( &PlantaMaisPerto , ConstrucaoVaiSerSuprida, PlantasAnalizadas );

					ConfereSeNaoEncontrouUmaPlanta( PlantaSelecionada);

					//PlantaMaisPerto->ImprimeDistancias();

					if( PlantaSelecionada == 1){
						//cout << endl << "Construcao e planta selecionadas " << endl << endl;
						//ConstrucaoVaiSerSuprida->ImprimeContrucao();
						//PlantaMaisPerto->Imprime();

						PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 1;

						PermiteAtendimentoDemanda = SelecionaCarreta(*PlantaMaisPerto , *ConstrucaoVaiSerSuprida,  Demanda);
						cout << " atendeu " << PermiteAtendimentoDemanda << endl;
					}

				}while( PermiteAtendimentoDemanda == 0 && AnalizouTodasPLanats(PlantasAnalizadas) == 0);

			}while( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas && AnalizouTodasPLanats(PlantasAnalizadas) == 0);

			if( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas ){
				cout  << endl << endl << endl;
				cout << " ##############################################################" << endl;
				cout << "           Não consigo alocar demandas da contrucao " << ConstrucaoVaiSerSuprida->NumeroDaConstrucao << endl;
				cout << " ##############################################################" << endl;
				cout << endl << endl;
				Viabilidade = 0;
			}
		}else{
			cout << endl << endl << " &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& " << endl << endl;
		}
	}

	PlantasInstancia.Imprime();
	ConstrucoesInstancia.ImprimeContrucoes();

	if( Viabilidade == 1){
		return 1;
	}else{
		return 0;
	}
}

Procedimento1::~Procedimento1(){

}




#endif /* PROCEDIMENTO1_HPP_ */
