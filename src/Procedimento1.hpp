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

// Seleciona uma construção baseada em um rank que elas possuem
	int SelecionaConstrucao( Construcao**, vector < int >);
// Seleciona a planta mais perto
	int SelecionaPlanta( Planta** , Construcao*, vector < int > );
// Seleciona carreta menos utilizada
	int SelecionaCarreta(Planta& , Construcao& , int, int, int);

// funções de verificação
	int AnalizouTodasPLanats(vector < int > );
	void ConfereSeNaoEncontrouUmaPlanta( int);
	void VerificaAlocacaoDemandaConstrucao(Construcao*, int&);

// executa o procedimento de realizar o sequenciamento da produção e despache de concreto
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

// Seleciona uma construção baseada em um rank = Janela de tempo / numero de demandas
int Procedimento1::SelecionaConstrucao( Construcao** ConstrucaoVaiSerSuprida , vector < int > ConstrucoesAnalizadas){
	int Ativo;
	double RankInicial;

	Ativo = 0;
	RankInicial = DBL_MAX;

	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			// Seleciona a construção que não possui todas as suas demandas já atendidas e que ainda não foi analisada
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

// seleciona a planta mais perto
int Procedimento1::SelecionaPlanta( Planta** PlantaMaisPerto,Construcao* ConstrucaoVaiSerSuprida, vector < int > PlantasAnalizadas ){
	int Ativo;
	double DistanciaConstrucaoPlanta;

	Ativo = 0;
	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucaoVaiSerSuprida->DistanciaPlantas[p].Distancia){
			// seleciona a planta que ainda não foi analisada
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

// seleciona a betoneira analisando primeiro a betoenira que tem mais tarefas alocadas ou a que tem emnos, depende da maneira como as betoneiras foram ordenadas antes de analisar elas para realizar o atendimento
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

	// entra caso a demanda em questão não tiver sido atendida
	if( ConstrucaoVaiSerSuprida.SituacaoDemanda[NumeroDemanda] == 0){
		// Ordena as betoneiras que seraõa analisadas para atender a demanda
		PlantaMaisPerto.VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
		//PlantaMaisPerto.VeiculosDaPlanta.Imprime(0);
		//cin >> Para;
		// realiza para todos o veiculos ou até a demanda for atendida
		for( int v = 0; v < PlantaMaisPerto.NumeroVeiculos; v++){
			// Estipula o tempo inicial que a planta ira começar a carregar a betoneira de concreto e que será possivel atender a demanda na construção.
			if( (ConstrucaoVaiSerSuprida.TempoMinimoDeFuncionamento - PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao] - PlantaMaisPerto.TempoPlanta) > PlantaMaisPerto.TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = ConstrucaoVaiSerSuprida.TempoMinimoDeFuncionamento - PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao] - PlantaMaisPerto.TempoPlanta;
			}else{
				HorarioInicioPlanta = PlantaMaisPerto.TempoMinimoDeFuncionamento;
			}
			//cout << "    Carreta usada [" << PlantaMaisPerto.NumeroDaPlanta << "-" << PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta << "] Construcao e Demanda [" << ConstrucaoVaiSerSuprida.NumeroDaConstrucao << "-" <<  NumeroDemanda << "]" << endl;

			// Ira continuar no loop aumentando o tempo de inicio para se começar a carregar a betoneira de concreto até a demandar ser atendida ou até o tempo maximo que a cosntrução pode receber uma betoneira sejá alcançado
			do{
				HorarioSaiDaPlanta = HorarioInicioPlanta + PlantaMaisPerto.TempoPlanta;
				HorarioChegaContrucao = HorarioSaiDaPlanta + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];
				HorarioSaiConstrucao = HorarioChegaContrucao +  PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucaoVaiSerSuprida.NumeroDaConstrucao][NumeroDemanda];
				HorarioRetornaPlanta = HorarioSaiConstrucao + PlantaMaisPerto.DistanciaConstrucoes[ConstrucaoVaiSerSuprida.NumeroDaConstrucao];

				// Verifica se é possivel atender a demanda utilizando a planta, a construção e o veículo corrente.
				DisponibilidadePlanta = PlantaMaisPerto.VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeCarreta = PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
				DisponibilidadeConstrucao = ConstrucaoVaiSerSuprida.VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);

				// Caso for possivel atender a demanda se ira alocar essa tarefa na planta, na construção e na betoneira e a função retorna o valor 1.
				if( DisponibilidadePlanta == 1 && DisponibilidadeCarreta == 1){
					if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
						ConstrucaoVaiSerSuprida.AlocaAtividade(HorarioChegaContrucao, HorarioSaiConstrucao, PlantaMaisPerto.VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantaMaisPerto.NumeroDaPlanta,  0, 1, PlantasInstancia);
						return 1;
					}
				}

				//caso não for possivel atender a demnada iniciando o carregamento de concreto na planta neste horario, se irá aumentar o horario para começar o carregamento na planta
				HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
			}while( HorarioInicioPlanta <= PlantaMaisPerto.TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucaoVaiSerSuprida.TempoMaximoDeFuncionamento);
		}
	}
	// Retorna 0 caso não for possivel atender a demanda com essa planta em questao
	return 0;
}

void Procedimento1::ConfereSeNaoEncontrouUmaPlanta( int  PlantaSelecionada){
	if( PlantaSelecionada == 0){
		cout  << endl << endl << endl;
		cout << " ################################################################################" << endl;
		cout << "           Não encontrou Planta para se alocar <<<<<<< Problema >>>>>>>>>>>" << endl;
		cout << " ################################################################################" << endl;
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

	// faz com que nenhuma construção tenha sido avaliada para o atendimento de suas demandas
	ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		// Seleciona a construção caso ela já não tiver sido analisada
		ConstrucaoSelecionada = SelecionaConstrucao( &ConstrucaoVaiSerSuprida, ConstrucoesInstancia.ConstrucoesAnalizadas);
		if( ConstrucaoSelecionada == 1){
			// marca a construção escolhida como já analisada
			ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucaoVaiSerSuprida->NumeroDaConstrucao] =  1;
			// Entrar no loop enqaunto tiver demandas a serem atendidas e planatas que ainda puderem atender a demanda
			do{
				// marca todas as plantas como não analisadas
				PlantasInstancia.InicializaPlantasAnalizadas();
				// atualiza a demanda que será analisada para ser atendida
				Demanda = ConstrucaoVaiSerSuprida->StatusAtendimento;
				PermiteAtendimentoDemanda = 0;
				// Enquanto não tiver atendida a demanda corrente ou não existir mais plantas para se analisar
				do{
					// Seleciona a planta que ira tentar atender a demanda
					PlantaSelecionada = SelecionaPlanta( &PlantaMaisPerto , ConstrucaoVaiSerSuprida, PlantasInstancia.PlantasAnalizadas );
					ConfereSeNaoEncontrouUmaPlanta( PlantaSelecionada);
					if( PlantaSelecionada == 1){
						// Marca a planta atual como analisada
						PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 1;
						// Seleciona uma carreta para atender a demanda e aloca a carreta, construção e planta para atender a demanda caso possivel.
						PermiteAtendimentoDemanda = SelecionaCarreta(*PlantaMaisPerto , *ConstrucaoVaiSerSuprida,  Demanda, 1, TipoOrdenacao);
					}
				}while( PermiteAtendimentoDemanda == 0 && PlantasInstancia.AnalizouTodasPLanats() == 0);
				// caso se conseguir atender a demnada corrente com a planta, se marca a planta como não analisada. Isto é para evitar que ela saia do proximo loop caso chegar em um caso que a ultima planta analisada é a que fez o atendimento da demanda dando o false entendimento que se viu todas as plantas
				if( PermiteAtendimentoDemanda == 1){
					PlantasInstancia.PlantasAnalizadas[ PlantaMaisPerto->NumeroDaPlanta ] = 0;
				}
			}while( ConstrucaoVaiSerSuprida->StatusAtendimento < ConstrucaoVaiSerSuprida->NumeroDemandas && PlantasInstancia.AnalizouTodasPLanats() == 0);
			// verifica se todas as demandas da construção corrente foi atendida
			VerificaAlocacaoDemandaConstrucao(ConstrucaoVaiSerSuprida, Viabilidade);
		}else{
			cout << endl << endl << " &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& " << endl << endl;
		}
	}
	// Calcula o nivel de viabilidade
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
