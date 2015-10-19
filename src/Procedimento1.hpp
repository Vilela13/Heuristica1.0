/*
 * Procedimento1.hpp
 *
 *  Created on: Aug 20, 2015
 *      Author: mateus.vilela
 */

#ifndef PROCEDIMENTO1_HPP_
#define PROCEDIMENTO1_HPP_



class DadosParaReordenar{
public:
	DadosParaReordenar();
	 vector < int >  DadosDasTarefasRetiradas; 		// 0 -> NumConstrução , 1 -> NumDemanda , 2 -> NumPlanta , 3 -> NumCarreta
	 vector < double > HorariosDasTarefasRetiradas;		// 0 -> HoraChegaPlanta , 1 -> HoraSaiPlanta , 2 -> HoraChegaConstrução , 3 -> HoraSaiConstrução , 4 -> HoraRetornaPlanta
	void IniciaConteudo();
	void InserirConteudo(int, int, int, int, double, double, double, double, double);
	void Imprimir();
	~DadosParaReordenar();
};

DadosParaReordenar::DadosParaReordenar(){

}

void DadosParaReordenar::IniciaConteudo(){
	DadosDasTarefasRetiradas.resize(4);
	HorariosDasTarefasRetiradas.resize(5);
}

void DadosParaReordenar::InserirConteudo(int NumConstucao, int NumDemanda, int NumPlanta, int NumCarreta, double HoraInicioPlanta, double HoraSaiPlanta, double HoraInicioConstrucao, double HoraSaiConstrucao, double HoraRetornaPlanta ){
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

void DadosParaReordenar::Imprimir(){
	cout << " Construcao [" << DadosDasTarefasRetiradas[0] << "-" << DadosDasTarefasRetiradas[1] << "]";
	cout << "tempo (" << HorariosDasTarefasRetiradas[2] << "-" << HorariosDasTarefasRetiradas[3] << ") ";
	cout << " Planta [" << DadosDasTarefasRetiradas[2] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[1] << ") ";
	cout << " Caminhao [" << DadosDasTarefasRetiradas[2] << "-" << DadosDasTarefasRetiradas[3] << "]";
	cout << " tempo (" << HorariosDasTarefasRetiradas[0] << "-" << HorariosDasTarefasRetiradas[4] << ") " << endl;
}

DadosParaReordenar::~DadosParaReordenar(){

}

bool DecideQualTarefaVemAntes ( DadosParaReordenar d1, DadosParaReordenar d2 ){
	return ( d1.HorariosDasTarefasRetiradas[2] < d2.HorariosDasTarefasRetiradas[2] );
}


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

	void AlocaIndicesDadosParaReorganizar(int, int&, int&,  int&, vector < DadosParaReordenar >);
	void InserirDadosEmEstruturaInstanciasDadosTarefasRetirar( vector < DadosParaReordenar > &, Construcao, int);
	void RearrumaTarefasParaAdicionalas(Construcao, int, int, int, double, double, double, double, double , int);

	int SelecionaCarreta(Planta& , Construcao& , int, int);

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

void Procedimento1::AlocaIndicesDadosParaReorganizar(int t, int &ConstrucaoIndice, int &PlantaIndice,  int &CaminhaoIndice, vector < DadosParaReordenar > Instancia){
	for( unsigned int c = 0; c < ConstrucoesInstancia.Construcoes.size(); c++){
		if( ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao == Instancia[t].DadosDasTarefasRetiradas[0] ){
			ConstrucaoIndice = c;
		}
	}

	for( unsigned int p = 0; p < PlantasInstancia.Plantas.size(); p++){
		if( PlantasInstancia.Plantas[p].NumeroDaPlanta ==  Instancia[t].DadosDasTarefasRetiradas[2] ){
			PlantaIndice = p;
		}
	}

	for( unsigned int v = 0; v < PlantasInstancia.Plantas[PlantaIndice].VeiculosDaPlanta.Carretas.size(); v++){
		if(  PlantasInstancia.Plantas[PlantaIndice].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta ==  Instancia[t].DadosDasTarefasRetiradas[3] ){
			CaminhaoIndice = v;
		}
	}

	if( ConstrucaoIndice == -13 || PlantaIndice == -13 || CaminhaoIndice == -13){
		cout << endl << endl << "  ########################## Problema em alocar os valores de ConstrucaoIndice, PlantaIndice e CaminhaoIndice  -> Procedimento1::RearrumaTarefasParaAdicionalas:: AlocaIndicesDadosParaReorganizar ########################## " << endl << endl ;
	}
}

void Procedimento1::InserirDadosEmEstruturaInstanciasDadosTarefasRetirar( vector < DadosParaReordenar > &Instancia, Construcao ConstrucaoVaiSerSuprida, int Imprime){

	Planta PlantaAuxiliarRemocao;

	for( unsigned int d = 0; d < ConstrucaoVaiSerSuprida.Descarregamentos.size(); d++){
		Instancia[d].DadosDasTarefasRetiradas[0] = ConstrucaoVaiSerSuprida.NumeroDaConstrucao;
		Instancia[d].DadosDasTarefasRetiradas[1] = ConstrucaoVaiSerSuprida.Descarregamentos[d].NumeroDemandaSuprida;
		Instancia[d].DadosDasTarefasRetiradas[2] = ConstrucaoVaiSerSuprida.Descarregamentos[d].NumPlantaFornecedor;
		Instancia[d].DadosDasTarefasRetiradas[3] = ConstrucaoVaiSerSuprida.Descarregamentos[d].NumCarretaUtilizada;

		Instancia[d].HorariosDasTarefasRetiradas[2] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioInicioDescarregamento;
		Instancia[d].HorariosDasTarefasRetiradas[3] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioFinalDescarregamento;

		for( unsigned int p = 0; p < PlantasInstancia.Plantas.size(); p++){
			if( PlantasInstancia.Plantas[p].NumeroDaPlanta == Instancia[d].DadosDasTarefasRetiradas[2] ){
				PlantaAuxiliarRemocao = PlantasInstancia.Plantas[p];
			}
		}

		Instancia[d].HorariosDasTarefasRetiradas[0] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioInicioDescarregamento - PlantaAuxiliarRemocao.DistanciaConstrucoes[ Instancia[d].DadosDasTarefasRetiradas[0] ] - PlantaAuxiliarRemocao.TempoPlanta;
		Instancia[d].HorariosDasTarefasRetiradas[1] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioInicioDescarregamento - PlantaAuxiliarRemocao.DistanciaConstrucoes[ Instancia[d].DadosDasTarefasRetiradas[0] ];
		Instancia[d].HorariosDasTarefasRetiradas[4] = ConstrucaoVaiSerSuprida.Descarregamentos[d].HorarioFinalDescarregamento + PlantaAuxiliarRemocao.DistanciaConstrucoes[ Instancia[d].DadosDasTarefasRetiradas[0] ];

	}

	if( Imprime == 1){
		cout << endl << endl << "  Dados Gravados " << endl << endl;
		for( unsigned int d = 0; d < ConstrucaoVaiSerSuprida.Descarregamentos.size(); d++){
			Instancia[d].Imprimir();
		}
	}
}

void Procedimento1::RearrumaTarefasParaAdicionalas(Construcao ConstrucaoVaiSerSuprida, int NumDemanda, int NumPlanta, int NumCarreta, double HorarioInicioPlanta, double HorarioSaiDaPlanta, double HorarioChegaContrucao, double HorarioSaiConstrucao, double HorarioRetornaPlanta, int SituacaoDemanda){


	int  ParaPrograma;
	int	Imprime;
	Imprime = 0;

	if( Imprime == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
	}

	vector < DadosParaReordenar > Instancia;

// Armazena Tarefas em estrutura

	Instancia.resize( ConstrucaoVaiSerSuprida.StatusAtendimento + 1 );

	for( unsigned int t = 0; t < Instancia.size(); t++){
		Instancia[t].IniciaConteudo();
	}

	InserirDadosEmEstruturaInstanciasDadosTarefasRetirar( Instancia, ConstrucaoVaiSerSuprida, Imprime);

// Deleta tarefas

	for( int d = 0; d < ( Instancia.size() - 1 ); d++){
		PlantasInstancia.DeletaTarefa( Instancia[d].DadosDasTarefasRetiradas[2], Instancia[d].HorariosDasTarefasRetiradas[0], Instancia[d].HorariosDasTarefasRetiradas[1], Instancia[d].DadosDasTarefasRetiradas[0], Instancia[d].DadosDasTarefasRetiradas[1], Instancia[d].DadosDasTarefasRetiradas[3],Instancia[d].HorariosDasTarefasRetiradas[0],  Instancia[d].HorariosDasTarefasRetiradas[4]);
		ConstrucoesInstancia.DeletaTarefa(Instancia[d].DadosDasTarefasRetiradas[0], Instancia[d].HorariosDasTarefasRetiradas[2], Instancia[d].HorariosDasTarefasRetiradas[3], Instancia[d].DadosDasTarefasRetiradas[1],  Instancia[d].DadosDasTarefasRetiradas[2], Instancia[d].DadosDasTarefasRetiradas[3]);
	}

	if( Imprime == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
	}

// Insere Tarfea que está fora da ordem em estrutura
	Instancia[ (Instancia.size()-1) ].InserirConteudo( ConstrucaoVaiSerSuprida.NumeroDaConstrucao, NumDemanda, NumPlanta, NumCarreta, HorarioInicioPlanta, HorarioSaiDaPlanta, HorarioChegaContrucao, HorarioSaiConstrucao, HorarioRetornaPlanta);

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

	int ConstrucaoIndice;
	int PlantaIndice;
	int CaminhaoIndice;

	ConstrucaoIndice = -13;
	PlantaIndice = -13;
	CaminhaoIndice = -13;

// Reinsere Tarefas que foram retiradas, só que agora em ordem
	for( unsigned int t = 0; t < Instancia.size(); t++){

		AlocaIndicesDadosParaReorganizar(t, ConstrucaoIndice, PlantaIndice, CaminhaoIndice, Instancia);

		ConstrucoesInstancia.Construcoes[ConstrucaoIndice].StatusAtendimento = ConstrucoesInstancia.Construcoes[ConstrucaoIndice].StatusAtendimento + 1;
		PlantasInstancia.Plantas[PlantaIndice].VeiculosDaPlanta.Carretas[CaminhaoIndice].AlocaAtividade(Instancia[t].HorariosDasTarefasRetiradas[0], Instancia[t].HorariosDasTarefasRetiradas[4],Instancia[t].DadosDasTarefasRetiradas[0], t);
		PlantasInstancia.Plantas[PlantaIndice].AlocaAtividade( Instancia[t].HorariosDasTarefasRetiradas[0], Instancia[t].HorariosDasTarefasRetiradas[1], Instancia[t].DadosDasTarefasRetiradas[0], t, Instancia[t].DadosDasTarefasRetiradas[3]);
		ConstrucoesInstancia.Construcoes[ConstrucaoIndice].AlocaAtividade( Instancia[t].HorariosDasTarefasRetiradas[2], Instancia[t].HorariosDasTarefasRetiradas[3] , t, Instancia[t].DadosDasTarefasRetiradas[3], Instancia[t].DadosDasTarefasRetiradas[2],0,0,0, SituacaoDemanda);
	}

	if( Imprime == 1){
		ConstrucoesInstancia.ImprimeContrucoes();
		PlantasInstancia.Imprime(1,1);
		cout << "                 Ta indo " << endl;
		cin >> ParaPrograma;
	}

}

int Procedimento1::SelecionaCarreta(Planta& PlantaMaisPerto, Construcao& ConstrucaoVaiSerSuprida, int  NumeroDemanda, int SituacaoDemanda ){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	if( ConstrucaoVaiSerSuprida.SituacaoDemanda[NumeroDemanda] == 0){
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
							ConstrucaoVaiSerSuprida.AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, NumeroDemanda,  PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantaMaisPerto.NumeroDaPlanta,0,0,0,SituacaoDemanda);
							//cout << "		PLanta (" <<  HorarioInicioPlanta << "-" << HorarioSaiDaPlanta << " trajeto " << HorarioChegaContrucao << " - " << HorarioSaiConstrucao << " trajeto " << HorarioRetornaPlanta << ") " << endl;
							return 1;
						}else{
							if( DisponibilidadeConstrucao == 2){
								RearrumaTarefasParaAdicionalas(ConstrucaoVaiSerSuprida, NumeroDemanda, PlantaMaisPerto.NumeroDaPlanta, PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta , HorarioInicioPlanta, HorarioSaiDaPlanta, HorarioChegaContrucao, HorarioSaiConstrucao, HorarioRetornaPlanta, SituacaoDemanda);
								return 1;
							}else{
								if( DisponibilidadeConstrucao == 3){
									RearrumaTarefasParaAdicionalas(ConstrucaoVaiSerSuprida, NumeroDemanda, PlantaMaisPerto.NumeroDaPlanta, PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta , HorarioInicioPlanta, HorarioSaiDaPlanta, HorarioChegaContrucao, HorarioSaiConstrucao, HorarioRetornaPlanta, SituacaoDemanda);
									cout << endl << endl << endl << "            Verificar corretude do procedimento -> Procedimento1::SelecionaCarreta " << endl << endl << endl;
								}
							}
						}
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

int Procedimento1::Executa(){
	Planta* PlantaMaisPerto;
	Construcao* ConstrucaoVaiSerSuprida;

	int ConstrucaoSelecionada;
	int PlantaSelecionada;
	int Demanda;
	int Viabilidade;
	int PermiteAtendimentoDemanda;

	int ParaPrograma;

	Viabilidade = 1;

	ConstrucoesInstancia.InicializaConstrucaosAnalizadas();
	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		//cout << "Construcao " << c << endl;
		ConstrucaoSelecionada = SelecionaConstrucao( &ConstrucaoVaiSerSuprida, ConstrucoesInstancia.ConstrucaosAnalizadas);
		/*
		if( ConstrucaoVaiSerSuprida->NumeroDaConstrucao == 2 ){
			cin >> ParaPrograma;
		}
		*/
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
						PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 1;
						PermiteAtendimentoDemanda = SelecionaCarreta(*PlantaMaisPerto , *ConstrucaoVaiSerSuprida,  Demanda, 1);
						//cout << " 			Atendeu " << PermiteAtendimentoDemanda << endl;
					}
				}while( PermiteAtendimentoDemanda == 0 && PlantasInstancia.AnalizouTodasPLanats() == 0);
				if( PermiteAtendimentoDemanda == 1){
					PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 0;
				}
			}while( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas && PlantasInstancia.AnalizouTodasPLanats() == 0);
			/*
			if( ConstrucaoVaiSerSuprida->NumeroDaConstrucao == 2 ){
				cout << "fora  Demanda  = " << Demanda << "(" << ConstrucaoVaiSerSuprida->StatusAtendimento << ") / " << ConstrucaoVaiSerSuprida->NumeroDemandas << endl;
				cin >> ParaPrograma;
			}
			*/
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
