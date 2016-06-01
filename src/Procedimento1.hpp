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

	int 	NP;
	ConjuntoPlantas 	PlantasInstancia;
	int 	NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int 	NV;
	float 	Velocidade;
	float 	TempoDeVidaConcreto;

	DadosModelo DM;

	Procedimento1();

	void 	CarregaDados(int InstNP, ConjuntoPlantas InstPlantasInstancia, int InstNE, ConjuntoConstrucoes InstConstrucoesInstancia, int InstNV, float InstVelocidade, float InstTempoDeVidaConcreto, DadosModelo dm);		// carrega os dados da solução
	int 	SelecionaConstrucao(  int &ConstrucaoVaiSerSuprida, int &IndiceConstrucaoVaiSerSuprida);											// Seleciona uma construção baseada em um rank que elas possuem
	void 	ConfereSeNaoEncontrouUmaPlanta( int  PlantaSelecionada);											// Verifica se não encontrou uma planta

	void 	VerificaAlocacaoDemandaConstrucao(int IndiceConstrucaoVaiSerSuprida, int &Viabilidade, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);			// Verifica se consegue atender as demandas da construção
	int 	Executa( int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas);		// executa o procedimento de realizar o sequenciamento da produção e despache de concreto

    ~Procedimento1();
};

Procedimento1::Procedimento1(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
}

// carrega os dados da solução
void 	Procedimento1::CarregaDados(int InstNP, ConjuntoPlantas InstPlantasInstancia, int InstNE, ConjuntoConstrucoes InstConstrucoesInstancia, int InstNV, float InstVelocidade, float InstTempoDeVidaConcreto, DadosModelo dm){
	NP 	= InstNP;
	PlantasInstancia 		= InstPlantasInstancia;
	NE 	= InstNE;
	ConstrucoesInstancia 	= InstConstrucoesInstancia;
	NV 	= InstNV;
	Velocidade 				= InstVelocidade;
	TempoDeVidaConcreto 	= InstTempoDeVidaConcreto;

	DM = dm;
}



// Seleciona uma construção baseada em um rank = Janela de tempo / numero de demandas
int 	Procedimento1::SelecionaConstrucao(  int &ConstrucaoVaiSerSuprida, int &IndiceConstrucaoVaiSerSuprida ){

	// percorre todas as cosntruções
	for( int c = 0; c < NE; c++){
		// Seleciona a construção que não possui todas as suas demandas já atendidas e que ainda não foi analisada
		if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas &&  ConstrucoesInstancia.Construcoes[c].ConstrucaoAnalizada == 0){
			// armazena os dados da cosntrução selecionada
			ConstrucaoVaiSerSuprida = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
			IndiceConstrucaoVaiSerSuprida = c;
			// retorna 1, encontrou uma construção
			return 1;
		}
	}
	// retorna 0, não encontrou uma cosntrução
	return 0;
}

// Verifica se não encontrou uma planta
void 	Procedimento1::ConfereSeNaoEncontrouUmaPlanta( int  PlantaSelecionada){
	if( PlantaSelecionada == 0){
		cout  << endl << endl << endl;
		cout << " ################################################################################" << endl;
		cout << "           Não encontrou Planta para se alocar <<<<<<< Problema >>>>>>>>>>>" << endl;
		cout << " ################################################################################" << endl;
		cout << endl << endl;
	}
}


// Verifica se consegue atender as demandas da construção
void 	Procedimento1::VerificaAlocacaoDemandaConstrucao( int IndiceConstrucaoVaiSerSuprida, int &Viabilidade, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].StatusAtendimento < ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDemandas ){
		if( ImprimeSolucao == 1){
			cout << endl;
			cout << " ##############################################################" << endl;
			cout << "           Não consigo alocar demandas da contrucao " << ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao <<  endl;
			cout << " ##############################################################" << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n ##############################################################\n");
			fprintf( Arquivo,"           Não consigo alocar demandas da contrucao %d   \n",ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao);
			fprintf( Arquivo," ##############################################################\n");
		}

		Viabilidade = 0;
	}
}

// executa o procedimento de construção da solução
int 	Procedimento1::Executa(  int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,  int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo, int RealizaProcessoDeAtrazarTarefas){

	int 	ConstrucaoVaiSerSuprida;
	int 	IndiceConstrucaoVaiSerSuprida;

	int 	Demanda;

	int 	ConstrucaoSelecionada;

	int 	Viabilidade;
	int 	PermiteAtendimentoDemanda;

	//int paraPrograma;

	Viabilidade = 1;
	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;  // contem a movimentação das tarefas no procedimento



	// ordena as cosntruções na ordem em que elas devem ser escolhidas com prioridade
	ConstrucoesInstancia.OrdenaCosntrucoes( EscolhaConstrucao);

	// faz com que nenhuma construção tenha sido avaliada para o atendimento de suas demandas
	ConstrucoesInstancia.InicializaConstrucoesAnalizadas();
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();

	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		// Seleciona a construção caso ela já não tiver sido analisada
		ConstrucaoSelecionada = SelecionaConstrucao(  ConstrucaoVaiSerSuprida, IndiceConstrucaoVaiSerSuprida);

		//cout << " ConstrucaoVaiSerSuprida [" << ConstrucaoVaiSerSuprida << "] IndiceConstrucaoVaiSerSuprida [" << IndiceConstrucaoVaiSerSuprida  << "] ConstrucaoSelecionada [" << ConstrucaoSelecionada << "] " << endl;

		if( ConstrucaoSelecionada == 1){
			// marca a construção escolhida como já analisada
			ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].ConstrucaoAnalizada =  1;

			// Entrar no loop enqaunto tiver demandas a serem atendidas e planatas que ainda puderem atender a demanda
			do{
				// atualiza a demanda que será analisada para ser atendida
				Demanda = ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].StatusAtendimento;
				PermiteAtendimentoDemanda = 0;

				PermiteAtendimentoDemanda = ConstrucoesInstancia.AdicionaTarefa( 0, ConstrucaoVaiSerSuprida, Demanda , DadosTarefasMovidasAuxiliar, 1, 0, RealizaProcessoDeAtrazarTarefas, EscolhaVeiculo , EscolhaPlanta, PlantasInstancia, imprime, " -> Procedimento1::Executa ");

				if ( imprime == 1){
					//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, 0, ImprimeSolucao,ImprimeArquivo,Arquivo);
					if( PermiteAtendimentoDemanda == 0){
						if( ImprimeSolucao == 1){
							cout << endl << endl << "  Não consegue colocar mais demandas da construção [" << ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao << "]" << endl << endl;
						}
						if( ImprimeArquivo == 1){
							fprintf( Arquivo, "\n\n  Não consegue colocar mais demandas da construção [%d] \n\n", ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao);
						}
					}
				}

			}while( ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].StatusAtendimento < ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDemandas && PermiteAtendimentoDemanda != 0);
			// verifica se todas as demandas da construção corrente foi atendida
			VerificaAlocacaoDemandaConstrucao(IndiceConstrucaoVaiSerSuprida, Viabilidade, ImprimeSolucao, ImprimeArquivo, Arquivo);
		}else{
			if( ImprimeSolucao == 1){
				cout << endl << endl << " &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& " << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& \n\n");
			}
		}
	}
	// Calcula o nivel de viabilidade
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();

	//ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia,0,1,0,Arquivo);

	if( Viabilidade == 1){
		return 1;
	}else{
		return 0;
	}
}

Procedimento1::~Procedimento1(){

}

#endif /* PROCEDIMENTO1_HPP_ */
