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


	int SelecionaConstrucao( Construcao**, vector < int >);
	int SelecionaPlanta( Planta** , Construcao*, vector < int > );

	void RearrumaTarefasParaAdicionalas(Construcao, int, int, int, double, double, double, double, double );

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

void Procedimento1::RearrumaTarefasParaAdicionalas(Construcao ConstrucaoVaiSerSuprida, int NumDemanda, int NumPlanta, int NumCarreta, double HorarioInicioPlanta, double HorarioSaiDaPlanta, double HorarioChegaContrucao, double HorarioSaiConstrucao, double HorarioRetornaPlanta){

	vector < vector < int > > DadosDasTarefasRetiradas; 		// 0 -> NumConstrução , 1 -> NumDemanda , 2 -> NumPlanta , 3 -> NumCarreta
	vector < vector < double > > HorariosDasTarefasRetiradas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta

	int  ParaPrograma;

	Planta PlantaAuxiliarRemocao;

	//ConstrucoesInstancia.ImprimeContrucoes();
	PlantasInstancia.Imprime();

	DadosDasTarefasRetiradas.resize(ConstrucaoVaiSerSuprida.StatusAtendimento+1);
	HorariosDasTarefasRetiradas.resize(ConstrucaoVaiSerSuprida.StatusAtendimento+1);

	for( int t = 0; t < DadosDasTarefasRetiradas.size(); t++){
		DadosDasTarefasRetiradas[t].resize(4);
		HorariosDasTarefasRetiradas[t].resize(5);
	}

	for( unsigned int d = 0; d < ConstrucaoVaiSerSuprida.Descarregamentos.size(); d++){
		DadosDasTarefasRetiradas[d][0] = ConstrucaoVaiSerSuprida.NumeroDaConstrucao;
		DadosDasTarefasRetiradas[d][1] = ConstrucaoVaiSerSuprida.Descarregamentos[d].NumeroDemandaSuprida;
		DadosDasTarefasRetiradas[d][2] = ConstrucaoVaiSerSuprida.Descarregamentos[d].NumPlantaFornecedor;
		DadosDasTarefasRetiradas[d][3] = ConstrucaoVaiSerSuprida.Descarregamentos[d].NumCarretaUtilizada;

		HorariosDasTarefasRetiradas[d][2] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioInicioDescarregamento;
		HorariosDasTarefasRetiradas[d][3] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioFinalDescarregamento;

		for( unsigned int p = 0; p < PlantasInstancia.Plantas.size(); p++){
			if( PlantasInstancia.Plantas[p].NumeroDaPlanta == DadosDasTarefasRetiradas[d][2] ){
				PlantaAuxiliarRemocao = PlantasInstancia.Plantas[p];
			}
		}

		HorariosDasTarefasRetiradas[d][0] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioInicioDescarregamento - PlantaAuxiliarRemocao.DistanciaConstrucoes[DadosDasTarefasRetiradas[d][0]] - PlantaAuxiliarRemocao.TempoPlanta;
		HorariosDasTarefasRetiradas[d][1] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioInicioDescarregamento - PlantaAuxiliarRemocao.DistanciaConstrucoes[DadosDasTarefasRetiradas[d][0]];
		HorariosDasTarefasRetiradas[d][4] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioFinalDescarregamento + PlantaAuxiliarRemocao.DistanciaConstrucoes[DadosDasTarefasRetiradas[d][0]];

	}

	cout << endl << endl << "  Dados Gravados " << endl << endl;

	for( unsigned int d = 0; d < ConstrucaoVaiSerSuprida.Descarregamentos.size(); d++){
		cout << " Construcao [" << DadosDasTarefasRetiradas[d][0] << "-" << DadosDasTarefasRetiradas[d][1] << "] tempo (" << HorariosDasTarefasRetiradas[d][2] << "-" << HorariosDasTarefasRetiradas[d][3] << ") ";
		cout << " Planta [" << DadosDasTarefasRetiradas[d][2] << "] tempo (" << HorariosDasTarefasRetiradas[d][0] << "-" << HorariosDasTarefasRetiradas[d][1] << ") ";
		cout << " Caminhao [" << DadosDasTarefasRetiradas[d][2] << "-" << DadosDasTarefasRetiradas[d][3] << "] tempo (" << HorariosDasTarefasRetiradas[d][0] << "-" << HorariosDasTarefasRetiradas[d][4] << ") " << endl;
	}
	int d;
	d = 0;

	PlantasInstancia.DeletaTarefa( DadosDasTarefasRetiradas[d][2], HorariosDasTarefasRetiradas[d][0], HorariosDasTarefasRetiradas[d][1], DadosDasTarefasRetiradas[d][0], DadosDasTarefasRetiradas[d][1], DadosDasTarefasRetiradas[d][3],HorariosDasTarefasRetiradas[d][0],  HorariosDasTarefasRetiradas[d][4]);
	ConstrucoesInstancia.DeletaTarefa(DadosDasTarefasRetiradas[d][0], HorariosDasTarefasRetiradas[d][2], HorariosDasTarefasRetiradas[d][3], DadosDasTarefasRetiradas[d][1],  DadosDasTarefasRetiradas[d][2], DadosDasTarefasRetiradas[d][3]);

	//ConstrucoesInstancia.ImprimeContrucoes();
	PlantasInstancia.Imprime();


	DadosDasTarefasRetiradas[DadosDasTarefasRetiradas.size()-1][0] = ConstrucaoVaiSerSuprida.NumeroDaConstrucao;
	DadosDasTarefasRetiradas[DadosDasTarefasRetiradas.size()-1][1] = NumDemanda;
	DadosDasTarefasRetiradas[DadosDasTarefasRetiradas.size()-1][2] = NumPlanta;
	DadosDasTarefasRetiradas[DadosDasTarefasRetiradas.size()-1][3] = NumCarreta;

	HorariosDasTarefasRetiradas[HorariosDasTarefasRetiradas.size()-1][0] = HorarioInicioPlanta;
	HorariosDasTarefasRetiradas[HorariosDasTarefasRetiradas.size()-1][1] = HorarioSaiDaPlanta;
	HorariosDasTarefasRetiradas[HorariosDasTarefasRetiradas.size()-1][2] = HorarioChegaContrucao;
	HorariosDasTarefasRetiradas[HorariosDasTarefasRetiradas.size()-1][3] = HorarioSaiConstrucao;
	HorariosDasTarefasRetiradas[HorariosDasTarefasRetiradas.size()-1][4] = HorarioRetornaPlanta;

	for( unsigned int d = 0; d < HorariosDasTarefasRetiradas.size(); d++){
		cout << " Construcao [" << DadosDasTarefasRetiradas[d][0] << "-" << DadosDasTarefasRetiradas[d][1] << "] tempo (" << HorariosDasTarefasRetiradas[d][2] << "-" << HorariosDasTarefasRetiradas[d][3] << ") ";
		cout << " Planta [" << DadosDasTarefasRetiradas[d][2] << "] tempo (" << HorariosDasTarefasRetiradas[d][0] << "-" << HorariosDasTarefasRetiradas[d][1] << ") ";
		cout << " Caminhao [" << DadosDasTarefasRetiradas[d][2] << "-" << DadosDasTarefasRetiradas[d][3] << "] tempo (" << HorariosDasTarefasRetiradas[d][0] << "-" << HorariosDasTarefasRetiradas[d][4] << ") " << endl;
	}

	cin >> ParaPrograma;

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
			if( DisponibilidadePlanta == 1){
				if( DisponibilidadeCarreta == 1){
					if( DisponibilidadeConstrucao == 1){
						ConstrucaoVaiSerSuprida.StatusAtendimento = ConstrucaoVaiSerSuprida.StatusAtendimento + 1;
						PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].AlocaAtividade(HorarioInicioPlanta, HorarioRetornaPlanta, ConstrucaoVaiSerSuprida.NumeroDaConstrucao , NumeroDemanda);
						PlantaMaisPerto.AlocaAtividade(HorarioInicioPlanta, HorarioSaiDaPlanta, ConstrucaoVaiSerSuprida.NumeroDaConstrucao , NumeroDemanda,  PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta);
						ConstrucaoVaiSerSuprida.AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, NumeroDemanda,  PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantaMaisPerto.NumeroDaPlanta,0,0,0);
						//cout << "		PLanta (" <<  HorarioInicioPlanta << "-" << HorarioSaiDaPlanta << " trajeto " << HorarioChegaContrucao << " - " << HorarioSaiConstrucao << " trajeto " << HorarioRetornaPlanta << ") " << endl;
						return 1;
					}else{
						if( DisponibilidadeConstrucao == 2){
							RearrumaTarefasParaAdicionalas(ConstrucaoVaiSerSuprida, NumeroDemanda, PlantaMaisPerto.NumeroDaPlanta, PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta , HorarioInicioPlanta, HorarioSaiDaPlanta, HorarioChegaContrucao, HorarioSaiConstrucao, HorarioRetornaPlanta);

						}
					}
				}
			}
			HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
		}while( HorarioInicioPlanta <= PlantaMaisPerto.TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucaoVaiSerSuprida.TempoMaximoDeFuncionamento);
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

int Procedimento1::Executa(){
	Planta* PlantaMaisPerto;
	Construcao* ConstrucaoVaiSerSuprida;

	int ConstrucaoSelecionada;
	int PlantaSelecionada;
	int Demanda;
	int Viabilidade;
	int PermiteAtendimentoDemanda;

	Viabilidade = 1;

	ConstrucoesInstancia.InicializaConstrucaosAnalizadas();
	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		//cout << "Construcao " << c << endl;
		ConstrucaoSelecionada = SelecionaConstrucao( &ConstrucaoVaiSerSuprida, ConstrucoesInstancia.ConstrucaosAnalizadas);
		if( ConstrucaoSelecionada == 1){
			ConstrucoesInstancia.ConstrucaosAnalizadas[ConstrucaoVaiSerSuprida->NumeroDaConstrucao] =  1;
			do{
				PlantasInstancia.InicializaPlantasAnalizadas();
				Demanda = ConstrucaoVaiSerSuprida->StatusAtendimento;
				PermiteAtendimentoDemanda = 0;
				do{
					PlantaSelecionada = SelecionaPlanta( &PlantaMaisPerto , ConstrucaoVaiSerSuprida, PlantasInstancia.PlantasAnalizadas );
					ConfereSeNaoEncontrouUmaPlanta( PlantaSelecionada);
					//PlantaMaisPerto->ImprimeDistancias();
					if( PlantaSelecionada == 1){
						//cout << endl << "Construcao e planta selecionadas " << endl << endl;
						//ConstrucaoVaiSerSuprida->ImprimeContrucao();
						//PlantaMaisPerto->Imprime();
						PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 1;
						PermiteAtendimentoDemanda = SelecionaCarreta(*PlantaMaisPerto , *ConstrucaoVaiSerSuprida,  Demanda);
						//cout << " 			Atendeu " << PermiteAtendimentoDemanda << endl;
					}
				}while( PermiteAtendimentoDemanda == 0 && PlantasInstancia.AnalizouTodasPLanats() == 0);
				if( PermiteAtendimentoDemanda == 1){
					PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 0;
				}
			}while( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas && PlantasInstancia.AnalizouTodasPLanats() == 0);

			if( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas ){
				cout << endl;
				cout << " ##############################################################" << endl;
				cout << "           Não consigo alocar demandas da contrucao " << ConstrucaoVaiSerSuprida->NumeroDaConstrucao << endl;
				cout << " ##############################################################" << endl;
				Viabilidade = 0;
			}
		}else{
			cout << endl << endl << " &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& " << endl << endl;
		}
	}
	ConstrucoesInstancia.OrdenaDescarregamentosConstrucoesOrdemCrescente();
	ConstrucoesInstancia.MarcaInicioFimDescarregamentosConstrucoes();
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	//ConstrucoesInstancia.ImprimeContrucoes();
	if( Viabilidade == 1){
		return 1;
	}else{
		return 0;
	}
}

Procedimento1::~Procedimento1(){

}




#endif /* PROCEDIMENTO1_HPP_ */
