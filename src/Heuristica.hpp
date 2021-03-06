/*
 * Heuristica.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef HEURISTICA_HPP_
#define HEURISTICA_HPP_

#include "Bibliotecas.hpp"

void CriaPastaExec(int ImprimeSolucao){
	DIR* dp;

	dp = opendir ("Exec");

	//cria a pasta Exec para salvar os dados da execução
	if(!dp){
		if( ImprimeSolucao == 1){
			cout <<  "\n Nao tem diretorio \"Exec\"!!            FUDEU MUITO!! \n" << endl;
		}

		if(system("mkdir Exec;") == 0){
			if( ImprimeSolucao == 1){
				cout << " Criou pasta Exec" << endl;
			}
		}else{
			cout << " Problema ao criar pasta Exec" << endl;
		}

		/* Outra maneira de criar arquivos
		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/
		dp = opendir ("Exec");

		if(!dp){
			cout << "\n Nao tem diretorio \"Exec\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			if( ImprimeSolucao == 1){
				cout << " Tem diretorio \"Exec\" !!  " << endl;
			}
		}
	}else{
		if( ImprimeSolucao == 1){
			cout << " Tem diretorio \"Exec\" !!  " << endl;
		}
	}
	closedir( dp );
}


class Heuristica{

public:

	// armazena os dados do modelo
	DadosModelo DM;

	// variavel para ler arquivo
	ifstream arq;

	// variaveis do sistema
	int		NP;
	ConjuntoPlantas PlantasInstancia;
	int		NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int		NV;
	double	Velocidade;
	double	TempoDeVidaConcreto;

	Heuristica();
	int		LeDados(string, int );						// le os dados da instancia

	void	ExecutaCons(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas);
	void	ExecutaCons100(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas);

	void	ExecutaConsBuscVei(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);
	void	ExecutaConsBuscCons(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);
	void	ExecutaConsBuscPlan(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);

	void	ExecutaConsBuscasVeiConsPlan(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);


	void	ExecutaConsBuscas(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);			// executa o procedimento heuristico
	void	ExecutaConsBuscasCir(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas);

	void	ExecutaGrsp(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);
	void	ExecutaGrspCir(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);

	void	ExecutaGrspClass(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);
	void	ExecutaGrspClassCir(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas);

	void	LeNomeInstancia(int , string& );			// le o nome da instancia
	void	LeNumeroPlantasEntregasVeiculos(int);		// le o numero de plantas, veiculos e cosntruções
	void	LeVelocidade(int);							// le a velocidade

	void	LeTempoDeVidaConcreto(int);				// Le o tempo de vida do concreto
	void	LeVeiculosPorPlanta(int);					// le o numero de veículos por planta
	void	LeNumeroDemandas(int);						// le o numero de demandas por construção

	void	LeTemposContrucaoPlantaViceVersa(int);							// le as distancias das plantas para as construções
	void	LeTempoConstrucao(int);					// le os tempos que cada caminhão leva para atender cada demanda em cada cosntrução
	void	LeTempoPlanta(int);						// le o tempo que acda planta leva para carregar um caminhão de concreto

	void	LeTempoMaximoEntreDescargas(int);			// le o tempo maximo permitido entre o atendimento de duas demandas seguidas em cada construção
	void	LeTempoMaximoMinimoConstrucoes(int);		// le o tempo minimo e maximo que um caminhão pode começar a descarregar em uma cosntrução
	void	LeTempoMaximoMinimoPlantas(int);			// le o tempo minimo e máximo que um caminhão pode começar a carregar em uma planta

	void	CalculoRankTempoDemanda(int);				// calcula o rank baseado na janela de tempo e no numero de demandas para cada cosntrução

	void 	IniciaParametrosDoModelo();					// inicia parametros do modelo


	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;

	// caminho para o arquivo que se irá salvar os dados
	string Caminho;

	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int ImprimeArquivo;

	// variavel que controla se imprime na tela a solução e os procediemntos
	int ImprimeSolucao;

	time_t InicioExecucao, FinalExecucao;
	double TempoExecucao;

	bool ImprimePlanta;
	bool ImprimeConstrucao;
	bool IntervalosRespeitadosConstrucaoes;

	int ImprimeProcedimentoConstrutivo;
	int ImprimeViabilizacao;
	int ImprimeBusca;

	// Exscrever a dadta
	 time_t timer;
	 char buffer[26];
	 struct tm* tm_info;

	// variavel que faz o progrma parar
	int ParaPrograma;

	vector < vector < vector < double > > >TVvei;
	vector < vector < vector < double > > >TVPvei;


	vector < vector < vector < bool > > >ALFAvei;
	vector < vector < vector < vector < vector < bool > > > > > BETAveiei;
	vector < vector < vector < vector < vector < bool > > > > > BETAPpeiei;

	vector < double > Ze;

	void IniciaVariaveisDoModelo();

	void AlocaVariaveisDoModelo();




	~Heuristica();


};

Heuristica::Heuristica(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;

	Arquivo = NULL;



	ImprimeArquivo = 0;

	ImprimeSolucao = 0;

	InicioExecucao = 0;
	FinalExecucao = 0;
	TempoExecucao = 0;

	ImprimePlanta = 0;
	ImprimeConstrucao = 0;
	IntervalosRespeitadosConstrucaoes = 0;

	ImprimeProcedimentoConstrutivo = 0;
	ImprimeViabilizacao = 0;
	ImprimeBusca = 0;

	timer = 0;
	tm_info = NULL;
	ParaPrograma = 0;

}

// le os dados da instancia
int		Heuristica::LeDados(string Nome, int comentarios){

	string Instancia;
	string CaminhoArquivo1;


// Abre arquivo das instâncias
	// coloca a pasta que está o arquivo
	CaminhoArquivo1 = "./InstS/";
	// adiciona o nome do arquivo
	CaminhoArquivo1 += Nome;

	// escreve o arquivo que foi lido
	//cout << " Arquivo a abrir : " << CaminhoArquivo1.c_str() << endl;

	// abre o arquivo da instancia
	arq.open(CaminhoArquivo1.c_str());
	// caso abrir o arquivo da instancia, entra no IF
	if (arq.is_open()){
		// le os dados da instancia
		LeNomeInstancia(comentarios, Instancia);
		LeNumeroPlantasEntregasVeiculos(comentarios);
		LeVelocidade(comentarios);
		LeTempoDeVidaConcreto(comentarios);
		LeVeiculosPorPlanta( comentarios);
		LeNumeroDemandas(comentarios);
		LeTemposContrucaoPlantaViceVersa(comentarios);
		LeTempoConstrucao(comentarios);
		LeTempoPlanta(comentarios);
		LeTempoMaximoEntreDescargas(comentarios);
		LeTempoMaximoMinimoConstrucoes(comentarios);
		LeTempoMaximoMinimoPlantas(comentarios);
		// calcula o rank
		CalculoRankTempoDemanda(comentarios);

		// utilizado para verificr a coretude em relação ao modelo
		IniciaParametrosDoModelo();

		// fecha o arquivo da instancia aberto
		arq.close();
		Instancia.clear();
		CaminhoArquivo1.clear();
		// retorna 1 pois o procedimento foi realizado com suceso
		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << CaminhoArquivo1 << endl << endl;
		return 0;
	}
}




// executa o procedimento heuristico sem buscas locais

void	Heuristica::ExecutaCons(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas){

	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 1;
	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;

	ImprimePlanta = 1;
	ImprimeConstrucao = 1;
	IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;
	ImprimeViabilizacao = 0;
	ImprimeBusca = 1;

	// classe do procediemnto construtivo
	Procedimento1 Prod1;

	// variavel que armazena o estado da solução, inicializada com zero
	int EstadoSolucao;
	EstadoSolucao = 0;

	// classe que armazena todas as soluções do procediemnto
	ConjuntoSolucoes Solucoes;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;




	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	// coleta o horario inicial
	InicioExecucao = time(NULL);


	Prod1.CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

// Define a ordem de seleção da alocação inicial das atividades



	//Prod1.ConstrucoesInstancia.ImprimeContrucoes(Prod1.PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);

	if( ImprimeSolucao == 1){
		cout << endl << endl << "############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################" << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo,"\n\n############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################\n");
	}

	EstadoSolucao = Prod1.Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);


	if( ImprimeSolucao == 1){
		cout << endl << endl << "########################################################################################################################################" << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo,"\n########################################################################################################################################\n\n");
	}





	if( EstadoSolucao == 1 ){
		if( ImprimeSolucao == 1){
			cout << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n  Solucao inicial viavel!    \n\n");
		}
	}else{
		if( ImprimeSolucao == 1){
			cout << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n  Solucao inicial inviavel!    \n\n");
		}
	}


	Solucoes.InsereSolucao(Prod1.NP, Prod1.PlantasInstancia, Prod1.NE, Prod1.ConstrucoesInstancia, Prod1.NV, Prod1.Velocidade, Prod1.TempoDeVidaConcreto, Prod1.DM);

	Solucoes.CalculaMakespanSolucoes();

	//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

	//cout <<  endl << "  PC " ;
		//cin >> ParaPrograma;



	if(Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf("         %f \t", Solucoes.Solucoes[0].Makespan);
	}else{
		printf("            ------ \t");
	}


	//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao , ImprimeArquivo, Arquivo);

	if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade != 0){

	/*

		cout << endl << endl << "  coletando dados " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].ImprimeContrucao();

		cout << endl << endl << "  coletando tarefa " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].Imprime();

		double HoraInicio;
		double HoraFinal;
		int NumDemanda;
		int NumPlanta;
		int Carreta;

		HoraInicio = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioInicioDescarregamento;
		HoraFinal = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioFinalDescarregamento;
		NumDemanda = 1;
		NumPlanta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumPlantaFornecedor;
		Carreta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumCarretaUtilizada;



		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].DeletaAtividadeLocomovendoAsOutrasTarefas(HoraInicio, HoraFinal, NumDemanda, NumPlanta, Carreta, Solucoes.Solucoes[0].PlantasInstancia);

		cout << endl << endl << "  Retira tarefa " << endl << endl;

		Solucoes.Imprime(1,1,0);

		cout << endl << endl << "  Readiciona tarefa " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].AlocaAtividade(HoraInicio, HoraFinal, Carreta, NumPlanta,  0, 1, Solucoes.Solucoes[0].PlantasInstancia);

		Solucoes.Imprime(1,1,0);
	*/


		if( ImprimeSolucao == 1){
			cout << endl << endl << "############################### Procedimento Viabilidade 1 #####################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n############################### Procedimento Viabilidade 1 #####################################\n");
		}

		Solucoes.Solucoes[0].ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		if( ImprimeSolucao == 1){
			cout << endl << endl << "##############################################################################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n##############################################################################################\n\n");
		}

		//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

		//cout <<  endl << "   V1 = " ;
		//cin >> ParaPrograma;

		Solucoes.CalculaNiveisViabilidadeSolucoes();
		Solucoes.CalculaMakespanSolucoes();
		Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){

			printf(" %f \t ------ \t", Solucoes.Solucoes[0].Makespan);
		}else{
			printf("     ------   \t");
		}

		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade != 0){

			if( ImprimeSolucao == 1){
				cout << endl << endl << "############################### Procedimento Viabilidade 2 #####################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n############################### Procedimento Viabilidade 2 #####################################\n");
			}

			Solucoes.Solucoes[0].ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

			if( ImprimeSolucao == 1){
				cout << endl << endl << "##############################################################################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n##############################################################################################\n\n");
			}

			//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

			Solucoes.CalculaNiveisViabilidadeSolucoes();
			Solucoes.CalculaMakespanSolucoes();
			Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

			if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
				printf(" %f \t", Solucoes.Solucoes[0].Makespan);
			}else{
				printf(" ------ \t");
			}
		}
	}else{
		printf(" ------ \t ------ \t");
	}


// montei para escrever os dados do modelo em um arquivo separado, mudei a estrategia
	Solucoes.Solucoes[0].IniciaVariaveisModelo();
	Solucoes.Solucoes[0].AtribuiValoresVariaveisModelo();
	Solucoes.Solucoes[0].ImprimeVariaveisModeloSeparado();





	ConstrucoesInstancia.NivelDeInviabilidade = Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = Solucoes.Solucoes[0].ConstrucoesInstancia;
	PlantasInstancia = Solucoes.Solucoes[0].PlantasInstancia;


	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %f \n",  TempoExecucao);
	if( ImprimeArquivo == 1){
		fprintf( Arquivo," \n\n Tempo  %f \n\n",  TempoExecucao);
	}
	fclose (Arquivo);
	Caminho.clear();

}


// executa o procedimento heuristico 100 vezes sem realizar nenhuma busca
void	Heuristica::ExecutaCons100(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas){



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;


	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;





	// classe do procediemnto construtivo
	Procedimento1 *Prod1;



	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;



	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2    \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes <= 100  ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);


		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \t", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \t");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \t", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \t");
		}


		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){

	// para passara os parametros
		ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
		PlantasInstancia = SolucaoFinal.PlantasInstancia;

		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;


	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);
	if( ImprimeArquivo == 1){
		fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);
	}

	fclose (Arquivo);
	Caminho.clear();

}


// executa o procedimento heuristico um certo número de tempo e depois realiza uma busca veículo
void	Heuristica::ExecutaConsBuscVei(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){





	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0

	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos

	ImprimeSolucao = 0;



	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;



	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;

	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2   \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \n", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \n");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \n", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	fprintf(Arquivo,"\n    Busca Local  \t Tempo até aqui ( %.0f ) \n",  TempoExecucao);
	fprintf(Arquivo,"     Solução \t BuscaLocalVeiculo   \n");
	fprintf(Arquivo,"         %f \t ", SolucaoFinal.Makespan);

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		SolucaoFinal.RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();

		// para passara os parametros
		ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
		PlantasInstancia = SolucaoFinal.PlantasInstancia;

		fprintf(Arquivo,"  %f \t", SolucaoFinal.Makespan);
	}else{
		fprintf(Arquivo,"  ------ \n");
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;


	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);

	fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);


	fclose (Arquivo);
	Caminho.clear();

}

// executa o procedimento heuristico um certo número de tempo e depois realiza uma busca construção
void	Heuristica::ExecutaConsBuscCons(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){





	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;



	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;



	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;

	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2   \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \n", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \n");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \n", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	fprintf(Arquivo,"\n    Busca Local  \t Tempo até aqui ( %.0f ) \n",  TempoExecucao);
	fprintf(Arquivo,"     Solução  \t BuscaLocalConstrucao  \n");
	fprintf(Arquivo,"         %f \t ", SolucaoFinal.Makespan);

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){

		SolucaoFinal.RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();

		// para passara os parametros
		ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
		PlantasInstancia = SolucaoFinal.PlantasInstancia;

		fprintf(Arquivo,"  %f \t", SolucaoFinal.Makespan);

	}else{
		fprintf(Arquivo,"  ------ \n");
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;


	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);

	fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);


	fclose (Arquivo);
	Caminho.clear();

}

// executa o procedimento heuristico um certo número de tempo e depois realiza uma busca planta
void	Heuristica::ExecutaConsBuscPlan(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){





	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;



	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;



	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;

	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2   \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \n", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \n");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \n", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}





	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	fprintf(Arquivo,"\n    Busca Local  \t Tempo até aqui ( %.0f ) \n",  TempoExecucao);
	fprintf(Arquivo,"     Solução \t  BuscaLocalPlanta  \n");
	fprintf(Arquivo,"         %f \t ", SolucaoFinal.Makespan);

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		SolucaoFinal.RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();

		// para passara os parametros
		ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
		PlantasInstancia = SolucaoFinal.PlantasInstancia;

		fprintf(Arquivo,"  %f \n", SolucaoFinal.Makespan);
	}else{
		fprintf(Arquivo,"  ------ \n");
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;


	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);

	fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);


	fclose (Arquivo);
	Caminho.clear();

}



// executa o procedimento heuristico um certo número de tempo e depois realiza as buscas veículo, construção e planta em sequencia
void	Heuristica::ExecutaConsBuscasVeiConsPlan(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){





	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;



	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;



	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;

	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2   \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \n", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \n");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \n", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	fprintf(Arquivo,"\n    Busca Local  \t Tempo até aqui ( %.0f ) \n",  TempoExecucao);
	fprintf(Arquivo,"     Solução \t BuscaLocalVeiculoConstrucaoPlanta   \n");
	fprintf(Arquivo,"         %f \t ", SolucaoFinal.Makespan);

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		SolucaoFinal.RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();
		SolucaoFinal.RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();
		SolucaoFinal.RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();

		// para passara os parametros
		ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
		PlantasInstancia = SolucaoFinal.PlantasInstancia;

		fprintf(Arquivo,"  %f \t", SolucaoFinal.Makespan);
	}else{
		fprintf(Arquivo,"  ------ \n");
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;


	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);

	fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);


	fclose (Arquivo);
	Caminho.clear();


}



// executa o procedimento heuristico e buscas locais
void	Heuristica::ExecutaConsBuscas(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas){



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 1;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;





	ImprimePlanta = 1;
	ImprimeConstrucao = 1;
	IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 1;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 Prod1;

	// variavel que armazena o estado da solução, inicializada com zero
	int EstadoSolucao;
	EstadoSolucao = 0;

	// classe que armazena todas as soluções do procediemnto
	ConjuntoSolucoes Solucoes;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	// coleta o horario inicial
	InicioExecucao = time(NULL);


	Prod1.CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

// Define a ordem de seleção da alocação inicial das atividades



	//Prod1.ConstrucoesInstancia.ImprimeContrucoes(Prod1.PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);

	if( ImprimeSolucao == 1){
		cout << endl << endl << "############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################" << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo,"\n\n############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################\n");
	}

	EstadoSolucao = Prod1.Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);


	if( ImprimeSolucao == 1){
		cout << endl << endl << "########################################################################################################################################" << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo,"\n########################################################################################################################################\n\n");
	}





	if( EstadoSolucao == 1 ){
		if( ImprimeSolucao == 1){
			cout << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n  Solucao inicial viavel!    \n\n");
		}
	}else{
		if( ImprimeSolucao == 1){
			cout << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n  Solucao inicial inviavel!    \n\n");
		}
	}


	Solucoes.InsereSolucao(Prod1.NP, Prod1.PlantasInstancia, Prod1.NE, Prod1.ConstrucoesInstancia, Prod1.NV, Prod1.Velocidade, Prod1.TempoDeVidaConcreto, Prod1.DM);

	Solucoes.CalculaMakespanSolucoes();

	//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

	//cout <<  endl << "  PC " ;
		//cin >> ParaPrograma;



	if(Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf("         %f \t", Solucoes.Solucoes[0].Makespan);
	}else{
		printf("            ------ \t");
	}


	//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao , ImprimeArquivo, Arquivo);

	if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade != 0){

	/*

		cout << endl << endl << "  coletando dados " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].ImprimeContrucao();

		cout << endl << endl << "  coletando tarefa " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].Imprime();

		double HoraInicio;
		double HoraFinal;
		int NumDemanda;
		int NumPlanta;
		int Carreta;

		HoraInicio = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioInicioDescarregamento;
		HoraFinal = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioFinalDescarregamento;
		NumDemanda = 1;
		NumPlanta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumPlantaFornecedor;
		Carreta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumCarretaUtilizada;



		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].DeletaAtividadeLocomovendoAsOutrasTarefas(HoraInicio, HoraFinal, NumDemanda, NumPlanta, Carreta, Solucoes.Solucoes[0].PlantasInstancia);

		cout << endl << endl << "  Retira tarefa " << endl << endl;

		Solucoes.Imprime(1,1,0);

		cout << endl << endl << "  Readiciona tarefa " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].AlocaAtividade(HoraInicio, HoraFinal, Carreta, NumPlanta,  0, 1, Solucoes.Solucoes[0].PlantasInstancia);

		Solucoes.Imprime(1,1,0);
	*/


		if( ImprimeSolucao == 1){
			cout << endl << endl << "############################### Procedimento Viabilidade 1 #####################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n############################### Procedimento Viabilidade 1 #####################################\n");
		}

		Solucoes.Solucoes[0].ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		if( ImprimeSolucao == 1){
			cout << endl << endl << "##############################################################################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n##############################################################################################\n\n");
		}

		//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

		//cout <<  endl << "   V1 = " ;
		//cin >> ParaPrograma;

		Solucoes.CalculaNiveisViabilidadeSolucoes();
		Solucoes.CalculaMakespanSolucoes();
		Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){

			printf(" %f \t ------ \t", Solucoes.Solucoes[0].Makespan);
		}else{
			printf("     ------   \t");
		}

		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade != 0){

			if( ImprimeSolucao == 1){
				cout << endl << endl << "############################### Procedimento Viabilidade 2 #####################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n############################### Procedimento Viabilidade 2 #####################################\n");
			}

			Solucoes.Solucoes[0].ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

			if( ImprimeSolucao == 1){
				cout << endl << endl << "##############################################################################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n##############################################################################################\n\n");
			}

			//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

			Solucoes.CalculaNiveisViabilidadeSolucoes();
			Solucoes.CalculaMakespanSolucoes();
			Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

			if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
				printf(" %f \t", Solucoes.Solucoes[0].Makespan);
			}else{
				printf(" ------ \t");
			}
		}
	}else{
		printf(" ------ \t ------ \t");
	}

	if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){

		if( ImprimeSolucao == 1){
			cout << endl << endl << "############################### Busca Local 1 (caminhão) #####################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n############################### Busca Local 1 (caminhão) #####################################\n");
		}

		Solucoes.Solucoes[0].RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		if( ImprimeSolucao == 1){
			cout << endl << endl << "##############################################################################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n##############################################################################################\n\n");
		}

		//Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes,ImprimeSolucao, ImprimeArquivo, Arquivo);

		Solucoes.CalculaMakespanSolucoes();
		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
			printf(" %f \t", Solucoes.Solucoes[0].Makespan);
		}

		if( ImprimeSolucao == 1){
			cout << endl << endl << "############################### Busca Local 2 (construcao) ###################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n############################### Busca Local 2 (construcao) ###################################\n");
		}


		Solucoes.Solucoes[0].RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		if( ImprimeSolucao == 1){
			cout << endl << endl << "##############################################################################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n##############################################################################################\n\n");
		}

		//Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes,ImprimeSolucao, ImprimeArquivo, Arquivo);

		Solucoes.CalculaMakespanSolucoes();
		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
			printf(" %f \t", Solucoes.Solucoes[0].Makespan);
		}

		if( ImprimeSolucao == 1){
			cout << endl << endl << "############################### Busca Local 3 (planta) #######################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n############################### Busca Local 3 (planta) #######################################\n");
		}

		Solucoes.Solucoes[0].RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		if( ImprimeSolucao == 1){
			cout << endl << endl << "##############################################################################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n##############################################################################################\n\n");
		}

		Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

		Solucoes.CalculaMakespanSolucoes();
		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
			printf(" %f ", Solucoes.Solucoes[0].Makespan);
		}

	}else{
		printf(" ------ \t ------ \t ------ ");

		if( ImprimeSolucao == 1){
			cout << endl << endl << "				Solução Inviavel " << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n				Solução Inviavel \n\n");
		}
	}

	ConstrucoesInstancia.NivelDeInviabilidade = Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = Solucoes.Solucoes[0].ConstrucoesInstancia;
	PlantasInstancia = Solucoes.Solucoes[0].PlantasInstancia;

	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %f \n",  TempoExecucao);
	if( ImprimeArquivo == 1){
		fprintf( Arquivo," \n\n Tempo  %f \n\n",  TempoExecucao);
	}
	fclose (Arquivo);
	Caminho.clear();

}



// executa o procedimento heuristico
void	Heuristica::ExecutaConsBuscasCir(string NomeInstancia, int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas){

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0

	ImprimeArquivo = 1;

	// variavel que controla se imprime na tela a solução e os procediemntos

	ImprimeSolucao = 0;




	ImprimePlanta = 1;
	ImprimeConstrucao = 1;
	IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 1;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 Prod1;

	// variavel que armazena o estado da solução, inicializada com zero
	int EstadoSolucao;
	EstadoSolucao = 0;

	// classe que armazena todas as soluções do procediemnto
	ConjuntoSolucoes Solucoes;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	double MakespanAux1;
	int Buaca1;
	double MakespanAux2;
	int Buaca2;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	/*
	DIR* dp;

	dp = opendir ("Exec");
	 */

	opendir ("Exec");

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	// coleta o horario inicial
	InicioExecucao = time(NULL);


	Prod1.CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

// Define a ordem de seleção da alocação inicial das atividades



	//Prod1.ConstrucoesInstancia.ImprimeContrucoes(Prod1.PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);

	if( ImprimeSolucao == 1){
		cout << endl << endl << "############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################" << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo,"\n\n############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################\n");
	}

	EstadoSolucao = Prod1.Executa( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);


	if( ImprimeSolucao == 1){
		cout << endl << endl << "########################################################################################################################################" << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo,"\n########################################################################################################################################\n\n");
	}





	if( EstadoSolucao == 1 ){
		if( ImprimeSolucao == 1){
			cout << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n  Solucao inicial viavel!    \n\n");
		}
	}else{
		if( ImprimeSolucao == 1){
			cout << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n  Solucao inicial inviavel!    \n\n");
		}
	}


	Solucoes.InsereSolucao(Prod1.NP, Prod1.PlantasInstancia, Prod1.NE, Prod1.ConstrucoesInstancia, Prod1.NV, Prod1.Velocidade, Prod1.TempoDeVidaConcreto, Prod1.DM);

	Solucoes.CalculaMakespanSolucoes();

	//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

	//cout <<  endl << "  PC " ;
		//cin >> ParaPrograma;



	if(Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf("         %f \t", Solucoes.Solucoes[0].Makespan);
	}else{
		printf("            ------ \t");
	}


	//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao , ImprimeArquivo, Arquivo);

	if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade != 0){

	/*

		cout << endl << endl << "  coletando dados " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].ImprimeContrucao();

		cout << endl << endl << "  coletando tarefa " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].Imprime();

		double HoraInicio;
		double HoraFinal;
		int NumDemanda;
		int NumPlanta;
		int Carreta;

		HoraInicio = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioInicioDescarregamento;
		HoraFinal = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioFinalDescarregamento;
		NumDemanda = 1;
		NumPlanta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumPlantaFornecedor;
		Carreta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumCarretaUtilizada;



		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].DeletaAtividadeLocomovendoAsOutrasTarefas(HoraInicio, HoraFinal, NumDemanda, NumPlanta, Carreta, Solucoes.Solucoes[0].PlantasInstancia);

		cout << endl << endl << "  Retira tarefa " << endl << endl;

		Solucoes.Imprime(1,1,0);

		cout << endl << endl << "  Readiciona tarefa " << endl << endl;

		Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].AlocaAtividade(HoraInicio, HoraFinal, Carreta, NumPlanta,  0, 1, Solucoes.Solucoes[0].PlantasInstancia);

		Solucoes.Imprime(1,1,0);
	*/


		if( ImprimeSolucao == 1){
			cout << endl << endl << "############################### Procedimento Viabilidade 1 #####################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n############################### Procedimento Viabilidade 1 #####################################\n");
		}

		Solucoes.Solucoes[0].ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);



		if( ImprimeSolucao == 1){
			cout << endl << endl << "##############################################################################################" << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n##############################################################################################\n\n");
		}

		//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

		//cout <<  endl << "   V1 = " ;
		//cin >> ParaPrograma;

		Solucoes.CalculaNiveisViabilidadeSolucoes();
		Solucoes.CalculaMakespanSolucoes();
		Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){

			printf(" %f \t ------ \t", Solucoes.Solucoes[0].Makespan);
		}else{
			printf("     ------   \t");
		}

		if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade != 0){

			if( ImprimeSolucao == 1){
				cout << endl << endl << "############################### Procedimento Viabilidade 2 #####################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n############################### Procedimento Viabilidade 2 #####################################\n");
			}

			Solucoes.Solucoes[0].ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);



			if( ImprimeSolucao == 1){
				cout << endl << endl << "##############################################################################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n##############################################################################################\n\n");
			}

			//Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, 1 , 0, Arquivo);

			Solucoes.CalculaNiveisViabilidadeSolucoes();
			Solucoes.CalculaMakespanSolucoes();
			Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);

			if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){
				printf(" %f \t", Solucoes.Solucoes[0].Makespan);
			}else{
				printf(" ------ \t");
			}
		}
	}else{
		printf(" ------ \t ------ \t");
	}

	if( Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade == 0){

		do{

			if( ImprimeSolucao == 1){
				cout << endl << endl << "############################### Busca Local 1 (caminhão) #####################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n############################### Busca Local 1 (caminhão) #####################################\n");
			}

			Solucoes.Solucoes[0].RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

			if( ImprimeSolucao == 1){
				cout << endl << endl << "##############################################################################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n##############################################################################################\n\n");
			}

			//Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes,ImprimeSolucao, ImprimeArquivo, Arquivo);

			Solucoes.Solucoes[0].CalculaMakespan();

			MakespanAux1 = Solucoes.Solucoes[0].Makespan;
			Buaca1 = 0;

			if( ImprimeSolucao == 1){
				cout << endl << endl << "############################### Busca Local 2 (construcao) ###################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n############################### Busca Local 2 (construcao) ###################################\n");
			}

			Solucoes.Solucoes[0].RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

			if( ImprimeSolucao == 1){
				cout << endl << endl << "##############################################################################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n##############################################################################################\n\n");
			}

			//Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes,ImprimeSolucao, ImprimeArquivo, Arquivo);

			Solucoes.Solucoes[0].CalculaMakespan();
			if( MakespanAux1 > Solucoes.Solucoes[0].Makespan ){
				Buaca1 = 1;
			}

			MakespanAux2 = Solucoes.Solucoes[0].Makespan;
			Buaca2 = 0;

			if( ImprimeSolucao == 1){
				cout << endl << endl << "############################### Busca Local 3 (planta) #######################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n############################### Busca Local 3 (planta) #######################################\n");
			}

			Solucoes.Solucoes[0].RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

			if( ImprimeSolucao == 1){
				cout << endl << endl << "##############################################################################################" << endl << endl;
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n##############################################################################################\n\n");
			}

			Solucoes.Solucoes[0].CalculaMakespan();
			if( MakespanAux2 > Solucoes.Solucoes[0].Makespan ){
				Buaca2 = 1;
			}

		}while( Buaca1 == 1 || Buaca2 == 1);

		Solucoes.Solucoes[0].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes, ImprimeSolucao, ImprimeArquivo, Arquivo);
		printf( " %f \t ", Solucoes.Solucoes[0].Makespan);

	}else{
		printf(" ------ \t ");

		if( ImprimeSolucao == 1){
			cout << endl << endl << "				Solução Inviavel " << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n\n				Solução Inviavel \n\n");
		}
	}

	ConstrucoesInstancia.NivelDeInviabilidade = Solucoes.Solucoes[0].ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = Solucoes.Solucoes[0].ConstrucoesInstancia;
	PlantasInstancia = Solucoes.Solucoes[0].PlantasInstancia;

	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( "  %.0f \n",  TempoExecucao);
	if( ImprimeArquivo == 1){
		fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);
	}

	fclose (Arquivo);
	Caminho.clear();

}





void	Heuristica::ExecutaGrsp(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;



	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;

	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;

	// variaveis que sinalizam o meio de ordenação no procediemnto construtivo
	int 	EscolhaVeiculoProcediemnto 		= 4;	// ordenação aleatoria
	int 	EscolhaConstrucaoProcediemnto	= 4;	// ordenação aleatoria
	int 	EscolhaPlantaProcediemnto		= 4;	// ordenação aleatoria

	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;



	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	/*
	DIR* dp;

	dp = opendir ("Exec");
	*/

	opendir ("Exec");

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2  \t BuscaLocal1 \t BuscaLocal2 \t BuscaLocal3  \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculoProcediemnto, EscolhaConstrucaoProcediemnto, EscolhaPlantaProcediemnto, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \t", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \t");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \t", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \t");
		}

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			SolucaoCorrente->RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
			SolucaoCorrente->RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
			SolucaoCorrente->RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			fprintf(Arquivo,"         %f \n", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo," ------ \t ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
	PlantasInstancia = SolucaoFinal.PlantasInstancia;

	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);
	if( ImprimeArquivo == 1){
		fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);
	}

	fclose (Arquivo);
	Caminho.clear();

}



void	Heuristica::ExecutaGrspCir(string NomeInstancia, long int NumeroIteracoes,  long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;


	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;

	// variaveis que sinalizam o meio de ordenação no procediemnto construtivo
	int 	EscolhaVeiculoProcediemnto 		= 4;	// ordenação aleatoria
	int 	EscolhaConstrucaoProcediemnto	= 4;	// ordenação aleatoria
	int 	EscolhaPlantaProcediemnto		= 4;	// ordenação aleatoria

	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	double MakespanAux1;
	int Buaca1;
	double MakespanAux2;
	int Buaca2;

	int iteracoes;

	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2  \t BuscaLocal  \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculoProcediemnto, EscolhaConstrucaoProcediemnto, EscolhaPlantaProcediemnto, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \t", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \t");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \t", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \t");
		}

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){

			do{

				SolucaoCorrente->RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();

				MakespanAux1 = SolucaoCorrente->Makespan;
				Buaca1 = 0;
				SolucaoCorrente->RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				if( MakespanAux1 > SolucaoCorrente->Makespan ){
					Buaca1 = 1;
				}

				MakespanAux2 = SolucaoCorrente->Makespan;
				Buaca2 = 0;
				SolucaoCorrente->RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				if( MakespanAux2 > SolucaoCorrente->Makespan ){
					Buaca2 = 1;
				}

			}while( Buaca1 == 1 || Buaca2 == 1);

			fprintf(Arquivo," %f \n", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo," ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
	PlantasInstancia = SolucaoFinal.PlantasInstancia;

	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);
	if( ImprimeArquivo == 1){
		fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);
	}

	fclose (Arquivo);
	Caminho.clear();

}







void	Heuristica::ExecutaGrspClass(string NomeInstancia, long int NumeroIteracoes, long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;



	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;

	// variaveis que sinalizam o meio de ordenação no procediemnto construtivo
	int 	EscolhaVeiculoProcediemnto 		= 4;	// ordenação aleatoria
	int 	EscolhaConstrucaoProcediemnto	= 4;	// ordenação aleatoria
	int 	EscolhaPlantaProcediemnto		= 4;	// ordenação aleatoria

	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	int iteracoes;

	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2   \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculoProcediemnto, EscolhaConstrucaoProcediemnto, EscolhaPlantaProcediemnto, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \n", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \n");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \n", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}

	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	fprintf(Arquivo,"\n    Busca Local  \t Tempo até aqui ( %.0f ) \n",  TempoExecucao);
	fprintf(Arquivo,"     Solução \t BuscaLocal1 \t BuscaLocal2 \t BuscaLocal3  \n");
	fprintf(Arquivo,"         %f \t ", SolucaoFinal.Makespan);

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		SolucaoFinal.RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();
		fprintf(Arquivo,"  %f \t", SolucaoFinal.Makespan);
		SolucaoFinal.RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();
		fprintf(Arquivo,"  %f \t", SolucaoFinal.Makespan);
		SolucaoFinal.RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
		SolucaoFinal.CalculaMakespan();
		fprintf(Arquivo,"  %f \n", SolucaoFinal.Makespan);
	}else{
		fprintf(Arquivo," ------ \t ------ \t ------ \n");
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
	PlantasInstancia = SolucaoFinal.PlantasInstancia;

	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);

	fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);


	fclose (Arquivo);
	Caminho.clear();

}



void	Heuristica::ExecutaGrspClassCir(string NomeInstancia, long int NumeroIteracoes,  long int TempoExecucaoMaximo, int EscolhaVeiculo, int EscolhaConstrucao,  int EscolhaPlanta,  int RealizaProcessoDeAtrazarTarefas){



	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	ImprimeArquivo = 0;

	// variavel que controla se imprime na tela a solução e os procediemntos
	ImprimeSolucao = 0;


	//bool ImprimePlanta;
	//bool ImprimeConstrucao;
	//bool IntervalosRespeitadosConstrucaoes;

	//ImprimePlanta = 1;
	//ImprimeConstrucao = 1;
	//IntervalosRespeitadosConstrucaoes = 1;


	ImprimeProcedimentoConstrutivo = 0;


	ImprimeViabilizacao = 0;


	ImprimeBusca = 0;



	// variavel que faz o progrma parar


	// classe do procediemnto construtivo
	Procedimento1 *Prod1;

	// variaveis que sinalizam o meio de ordenação no procediemnto construtivo
	int 	EscolhaVeiculoProcediemnto 		= 4;	// ordenação aleatoria
	int 	EscolhaConstrucaoProcediemnto	= 4;	// ordenação aleatoria
	int 	EscolhaPlantaProcediemnto		= 4;	// ordenação aleatoria

	// classe que armazena solução corrente
	Solucao *SolucaoCorrente;

	// classe que armazena solução final
	Solucao SolucaoFinal;

	// variavel que informa se irá realizar a verificação da viabilidade ou não, inicializa com 1 que é que vai ter a verificação da viabilidade
	//int VerificaViabilidade;
	//VerificaViabilidade = 1;

	double MakespanAux1;
	int Buaca1;
	double MakespanAux2;
	int Buaca2;

	int iteracoes;



	// marca se já possui uma solução
	int Ativa;
	Ativa = 0;


	// fornece o caminnho onde será criado o arquivo
	Caminho =  "./Exec/";
	// acrescenta o nome do arquivo ao caminho
	Caminho +=  NomeInstancia;

	CriaPastaExec(ImprimeSolucao);

	// escreve o endereço do arquivo
	//cout << endl << endl << endl << Caminho << "   -  " <<  Caminho.c_str() <<  endl << endl << endl;

	cout << NomeInstancia << '\t';

	// abre o arquivo
	Arquivo = fopen (Caminho.c_str(), "a");

	// verifica se abriu o arquivo
	if(!Arquivo ){
		// caso não escreve está mensagem
		cout <<  endl << endl <<  endl << endl <<  "  Fudeu muito " <<  endl << endl <<  endl << endl;
		cin >> ParaPrograma;
	}

	// coleta a data e a hora
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

	if( ImprimeArquivo == 1){
		fprintf(Arquivo,"\n\n ----- Execução as %s ----- \n\n", buffer);
		// escreve o nome da instancia no arquivo de saida
		fprintf( Arquivo," %s \n ",  NomeInstancia.c_str());
	}
	if( ImprimeSolucao == 1){
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);
	}

	fprintf(Arquivo,"  Construtiva \t Viabilidade1 \t Viabilidade2   \n");

	// coleta o horario inicial
	InicioExecucao = time(NULL);
	FinalExecucao = time(NULL);

	iteracoes = 0;

	while( iteracoes < NumeroIteracoes && (int) difftime(FinalExecucao, InicioExecucao) < TempoExecucaoMaximo ){

		Prod1 = new Procedimento1;

		Prod1->CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto, DM);

		Prod1->Executa( EscolhaVeiculoProcediemnto, EscolhaConstrucaoProcediemnto, EscolhaPlantaProcediemnto, ImprimeProcedimentoConstrutivo, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);

		SolucaoCorrente = new Solucao;

		SolucaoCorrente->CarregaSolucao(Prod1->NP, Prod1->PlantasInstancia, Prod1->NE, Prod1->ConstrucoesInstancia, Prod1->NV, Prod1->Velocidade, Prod1->TempoDeVidaConcreto, Prod1->DM);

		delete(Prod1);

		SolucaoCorrente->CalculaMakespan();

		if(SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
			fprintf(Arquivo,"         %f \t", SolucaoCorrente->Makespan);
		}else{
			fprintf(Arquivo,"        ------ \t");
		}

		// ordena as construções
		SolucaoCorrente->ConstrucoesInstancia.OrdenaCosntrucoes(EscolhaConstrucao);

		if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
			SolucaoCorrente->ProcessoViabilizacao1( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoCorrente->CalculaMakespan();
			SolucaoCorrente->CalculaNiveisViabilidade();
			if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade != 0){
				SolucaoCorrente->ProcessoViabilizacao2( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeViabilizacao, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
				SolucaoCorrente->CalculaMakespan();
				SolucaoCorrente->CalculaNiveisViabilidade();
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0){
					fprintf(Arquivo," ------ \t %f \n", SolucaoCorrente->Makespan);
				}else{
					fprintf(Arquivo," ------ \t ------ \n");
				}
			}else{
				fprintf(Arquivo,"  %f \t ------ \n", SolucaoCorrente->Makespan);
			}
		}else{
			fprintf(Arquivo," ------ \t ------ \n");
		}

		if( Ativa == 0){
			SolucaoFinal = *SolucaoCorrente;
			 Ativa = 1;
		}else{
			if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
				if( SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade == 0 && SolucaoFinal.Makespan > SolucaoCorrente->Makespan){
					SolucaoFinal = *SolucaoCorrente;
				}
			}else{
				if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade > SolucaoCorrente->ConstrucoesInstancia.NivelDeInviabilidade){
					SolucaoFinal = *SolucaoCorrente;
				}
			}

		}
		FinalExecucao = time(NULL);
		delete( SolucaoCorrente);
		iteracoes++;
	}
	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	fprintf(Arquivo,"\n    Busca Local  \t Tempo até aqui ( %.0f ) \n",  TempoExecucao);
	fprintf(Arquivo,"     Solução \t BuscaLocal  \n");
	fprintf(Arquivo,"         %f \t ", SolucaoFinal.Makespan);

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		do{
			SolucaoFinal.RealizarBuscaLocalCaminhao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoFinal.CalculaMakespan();

			MakespanAux1 = SolucaoFinal.Makespan;
			Buaca1 = 0;
			SolucaoFinal.RealizarBuscaLocalConstrucao(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoFinal.CalculaMakespan();
			if( MakespanAux1 > SolucaoFinal.Makespan ){
				Buaca1 = 1;
			}

			MakespanAux2 = SolucaoFinal.Makespan;
			Buaca2 = 0;
			SolucaoFinal.RealizarBuscaLocalPlanta(EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,ImprimeBusca, ImprimeSolucao, ImprimeArquivo, Arquivo, RealizaProcessoDeAtrazarTarefas);
			SolucaoFinal.CalculaMakespan();
			if( MakespanAux2 > SolucaoFinal.Makespan ){
				Buaca2 = 1;
			}

		}while( Buaca1 == 1 || Buaca2 == 1);

		fprintf(Arquivo," %f \n", SolucaoFinal.Makespan);
	}else{
		fprintf(Arquivo," ------ \n");
	}

	if( SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade == 0){
		printf( " \t %f \t %d ",  SolucaoFinal.Makespan, SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}else{
		printf( " \t ------  \t %d ",  SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade);
	}
	SolucaoFinal.Imprime(1,1,1,0,1,Arquivo);

	ConstrucoesInstancia.NivelDeInviabilidade = SolucaoFinal.ConstrucoesInstancia.NivelDeInviabilidade;

	// para passara os parametros
	ConstrucoesInstancia = SolucaoFinal.ConstrucoesInstancia;
	PlantasInstancia = SolucaoFinal.PlantasInstancia;

	// coleta o horario final
	FinalExecucao = time(NULL);

	// calcula o tempo
	TempoExecucao = difftime(FinalExecucao, InicioExecucao);

	printf( " \t %.0f \n",  TempoExecucao);

	fprintf( Arquivo," \n\n Tempo  %.0f \n\n",  TempoExecucao);

	fclose (Arquivo);
	Caminho.clear();

}









// le o nome da instancia
void	Heuristica::LeNomeInstancia(int comentarios, string& Instancia){
	// le o nome da instancia
	arq >> Instancia;
	if( comentarios == 1){
		cout << " Nome instancia "<<  Instancia << endl;
	}
}

// le o numero de plantas, veiculos e cosntruções
void	Heuristica::LeNumeroPlantasEntregasVeiculos(int comentarios){
	// le numero de plantas
	arq >> NP;

	// inicia os dados que guada os dados das plantas
	PlantasInstancia.IniciaConjuntoPlantas(NP);
	for( int p = 0; p < NP; p++){
		PlantasInstancia.Plantas[p].NumeroDaPlanta = p;
	}
	// le numero de construções
	arq >> NE;



	// inicia as estrutura que guardao os dados das construções
	ConstrucoesInstancia.IniciaConjuntoConstrucoes(NE);
	for( int c = 0; c < NE; c++){
		ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao = c;
	}
	// le numero de veiculos
	arq >> NV;

	if( comentarios == 1){
		cout << " Numero de plantas "<<  NP << endl;
		cout << " Numero de Entregas "<< NE << endl;
		cout << " Numero de Veiculos "<< NV << endl;
	}

	DM.NP = NP;
	DM.NE = NE;
	DM.NV = NV;



	DM.Veiculos.resize(NP);
	DM.Demandas.resize(NE);

	DM.TEMpc.resize(NP);
	for( int p = 0; p < NP; p++){
		DM.TEMpc[p].resize(NE);
	}
	DM.TEMcp.resize(NE);
	for( int e = 0; e < NE; e++){
		DM.TEMcp[e].resize(NP);
	}
	DM.DESCvi.resize(NV);
	for( int v = 0; v < NV; v++){
		DM.DESCvi[v].resize(NE);
	}
	DM.CARRp.resize(NP);
	DM.TETAc.resize(NE);
	DM.S1vii.resize(NV);
	DM.S2vii.resize(NV);

	DM.TMINp.resize(NP);
	DM.TMAXp.resize(NP);
	DM.TMINc.resize(NE);
	DM.TMAXc.resize(NE);

	DM.M1vi.resize(NV);
	for( int v = 0; v < NV; v++){
		DM.M1vi[v].resize(NE);
	}
	DM.M2pc.resize(NP);
	for( int p = 0; p < NP; p++){
		DM.M2pc[p].resize(NE);
	}



	DM.M3c.resize(NE);
	DM.M4vi.resize(NV);
	for( int v = 0; v < NV; v++){
		DM.M4vi[v].resize(NE);
	}
	DM.M5vii.resize(NV);
	DM.M6vii.resize(NV);
	DM.M7c.resize(NE);
	DM.M8vi.resize(NV);
	for( int v = 0; v < NV; v++){
		DM.M8vi[v].resize(NE);
	}
	DM.M9p.resize(NP);
	DM.M10cp.resize(NE);
	for( int c = 0; c < NE; c++){
		DM.M10cp[c].resize(NP);
	}


}

// le a velocidade
void	Heuristica::LeVelocidade(int comentarios){
	// le a velocidade dos caminhões
	arq >> Velocidade;

	if( comentarios == 1){
		cout << " Velocidade "<<  Velocidade << endl;
	}
}


// Le o tempo de vida do concreto
void	Heuristica::LeTempoDeVidaConcreto(int comentarios){
	// le o tempo de vida do concreto
	arq >> TempoDeVidaConcreto;

	DM.TVC = TempoDeVidaConcreto;

	for( int c = 0; c < NE; c++){
			ConstrucoesInstancia.Construcoes[c].TempoDeVidaConcreto = TempoDeVidaConcreto;
	}

	if( comentarios == 1){
		cout << " Tempo De Vida Concreto "<<  TempoDeVidaConcreto << endl;
	}
}

// le o numero de veículos por planta
void	Heuristica::LeVeiculosPorPlanta(int comentarios){
	int aux;



	// percorre todas as planats
	for (int i = 0; i < NP ; i++){
		// le o numero d eveiculos que existe na planta corrente
		arq >> PlantasInstancia.Plantas[i].NumeroVeiculos;

		DM.Veiculos[i] = PlantasInstancia.Plantas[i].NumeroVeiculos;

		// inicia a estrutura que armazena os veiculos da planta corrente
		PlantasInstancia.Plantas[i].VeiculosDaPlanta.IniciaConjuntoCarretas( PlantasInstancia.Plantas[i].NumeroVeiculos, PlantasInstancia.Plantas[i].NumeroDaPlanta );
		if( comentarios == 1){
			cout << " Numero de veiculo na planta  " << i + 1 << " = " << PlantasInstancia.Plantas[i].NumeroVeiculos << "  ( ";
		}
		// le os numeros dos caminhões
		for ( int j = 0; j < PlantasInstancia.Plantas[i].NumeroVeiculos; j++){
			// le o numero do caminhão em questão, cada caminhão tem um número próprio
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

// le o numero de demandas por construção
void	Heuristica::LeNumeroDemandas(int comentarios){
	int aux;
	// percorre por todas as construções
	for (int i = 0; i < NE ; i++){
		// le o numero de demandas
		arq >> ConstrucoesInstancia.Construcoes[i].NumeroDemandas;

		DM.Demandas[i] = ConstrucoesInstancia.Construcoes[i].NumeroDemandas;
		for( int v = 0; v < NV; v++){
			DM.DESCvi[v][i].resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
			DM.M1vi[v][i].resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
			DM.M4vi[v][i].resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
			DM.M8vi[v][i].resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		}

		// inicializa o numero de descarregamentos que cosntrução temq ue receber para satisfazer todas as suas demandas
		ConstrucoesInstancia.Construcoes[i].Descarregamentos.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		// inicia o status de atendiemntos como zero, nenhuma demanda foi atendida ainda
		ConstrucoesInstancia.Construcoes[i].StatusAtendimento = 0;
		// inicializa o vetor atendimento das demandas
		ConstrucoesInstancia.Construcoes[i].SituacaoDemanda.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		// inicializa o vetor remoção das demandas
		ConstrucoesInstancia.Construcoes[i].SituacaoRemocao.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		// percorre por todas as demandas da construção corrente
		for( int d = 0; d < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; d++){
			// faz o seu status atendimento ser zero
			ConstrucoesInstancia.Construcoes[i].SituacaoDemanda[d] = 0;
			// faz o seu status remoção ser zero
			ConstrucoesInstancia.Construcoes[i].SituacaoRemocao[d] = 0;
		}
		if( comentarios == 1){
			cout << " Numero de demandas na construção " << i + 1 << " = " << ConstrucoesInstancia.Construcoes[i].NumeroDemandas << "  ( ";
		}
		for ( int j = 0; j < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; j++){
			// le o nuemro de cada demanda em separado, cada construção tem uma numeração propria.
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}




	for (int v = 0; v < NV ; v++){
		DM.S1vii[v].resize(NE);
		DM.S2vii[v].resize(NE);
		DM.M5vii[v].resize(NE);
		DM.M6vii[v].resize(NE);
		for (int e1 = 0; e1 < NE ; e1++){
			DM.S1vii[v][e1].resize( ConstrucoesInstancia.Construcoes[e1].NumeroDemandas );
			DM.S2vii[v][e1].resize( ConstrucoesInstancia.Construcoes[e1].NumeroDemandas );
			DM.M5vii[v][e1].resize( ConstrucoesInstancia.Construcoes[e1].NumeroDemandas );
			DM.M6vii[v][e1].resize( ConstrucoesInstancia.Construcoes[e1].NumeroDemandas );

			for (int d1 = 0; d1 < (int) DM.S1vii[v][e1].size() ; d1++){
				DM.S1vii[v][e1][d1].resize(NE);
				DM.S2vii[v][e1][d1].resize(NE);
				DM.M5vii[v][e1][d1].resize(NE);
				DM.M6vii[v][e1][d1].resize(NE);
				for (int e2 = 0; e2 < NE ; e2++){
					DM.S1vii[v][e1][d1][e2].resize( ConstrucoesInstancia.Construcoes[e2].NumeroDemandas );
					DM.S2vii[v][e1][d1][e2].resize( ConstrucoesInstancia.Construcoes[e2].NumeroDemandas );
					DM.M5vii[v][e1][d1][e2].resize( ConstrucoesInstancia.Construcoes[e2].NumeroDemandas );
					DM.M6vii[v][e1][d1][e2].resize( ConstrucoesInstancia.Construcoes[e2].NumeroDemandas );
				}
			}
		}
	}


}


// le as distancias das plantas para as construções
void	Heuristica::LeTemposContrucaoPlantaViceVersa(int comentarios){
	// Le a distancia das plantas para as construções
	if( comentarios == 1){
		cout << "    Tempo Planta para Construcoes"<< endl;
	}
	// percorre todas as plantas
	for (int p = 0; p < NP ; p++){
		// inicializa a estrutura de distancia da planta corrente para as cosntruções que existem
		PlantasInstancia.Plantas[p].TempoParaConstrucoes.resize(NE);
		// percorre por todas as construções que existem
		for ( int c = 0; c < NE; c++){
			// le a distancia da planta corresnte para a construção corrente e armazena esse valor
			arq >> PlantasInstancia.Plantas[p].TempoParaConstrucoes[c];

			// Dados modelo
			DM.TEMpc[p][c] = PlantasInstancia.Plantas[p].TempoParaConstrucoes[c];

			if( comentarios == 1){
				cout << PlantasInstancia.Plantas[p].TempoParaConstrucoes[c] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	}

	// Le a distancia das construções para as plantas
	if( comentarios == 1){
		cout << "     Tempo Construcoes para Plantas"<< endl;
	}
	// percorre todas as cosntruções
	for (int c = 0; c < NE ; c++){
		// inicializa a estrutura de distancia da construção para as plantas
		ConstrucoesInstancia.Construcoes[c].TempoParaPlantas.resize(NP);
		// percorre todas as plantas
		for ( int p = 0; p < NP; p++){
			// le a distancia da construção corrente para a planta corresnte e armazena esse valor
			arq >> ConstrucoesInstancia.Construcoes[c].TempoParaPlantas[p].Tempo;

			// Dados modelo
			DM.TEMcp[c][p] = ConstrucoesInstancia.Construcoes[c].TempoParaPlantas[p].Tempo;

			// armazena um ponteiro que leva a planta que a distancia acima que na construção corrente ela se refere
			ConstrucoesInstancia.Construcoes[c].TempoParaPlantas[p].PlantaComparada = &PlantasInstancia.Plantas[p];
			if( comentarios == 1){
				cout <<  ConstrucoesInstancia.Construcoes[c].TempoParaPlantas[p].Tempo << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}

}

// le os tempos que cada caminhão leva para atender cada demanda em cada cosntrução
void	Heuristica::LeTempoConstrucao(int comentarios){
	int aux;

	int VeiculoAux1;
	int VeiculoAux2;

	if( comentarios == 1){
		cout << "     Tempo de cada veiculo em cada cosntrucao "<< endl;
	}
	// percorre todas as plantas
	for (int p = 0; p < NP ; p++){
		// percorre todos os caminhões
		for (int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos ; v++){
			// le o numero do veiculo corrente
			arq >> aux;
			if( comentarios == 1){
				cout << " Veiculo  " << aux << endl;
			}
			// inicia o tamanho da estrutura que guarda os tempos dos veiculos para atender cada demanda com o número de construções que se tem
			PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao.resize( NE);
			// percorre todas as construções
			for ( int c = 0; c < NE; c++){
				// le o numero de demandas da construção
				arq >> aux;
				// verifica se os dados são inconsitentes caso o numero de demandas não seja o mesmo que o passado anteriormente
				if ( aux != ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
					cout << "        ############## Dados Incosistentes ############## " << endl << endl;
				}
				// inicializa a estrurura que guada os tempos dos veiculos para atender cada demanda com o numero das demandas
				PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c].resize( ConstrucoesInstancia.Construcoes[c].NumeroDemandas );
				// percorre todas as demandas
				for ( int d = 0; d < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; d++){
					// le o tempo que o veicuo corrente leva para atender a demanda corrente
					arq >> PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c][d];

					// encontra a númeração do veiculo referente a que se tem no modelo
					VeiculoAux1 = 0;
					VeiculoAux2 = 0;
					for( int p1 = 0; p1 < NP ; p1++){
						if( p1 == p){
							VeiculoAux2 = VeiculoAux1 + v;
						}
						VeiculoAux1 = VeiculoAux1 + PlantasInstancia.Plantas[p].NumeroVeiculos;
					}

					// Dados modelo
					DM.DESCvi[ VeiculoAux2 ][c][d] = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c][d];

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

// le o tempo que acda planta leva para carregar um caminhão de concreto
void	Heuristica::LeTempoPlanta(int comentarios){
	// percorre todas as plantas
	for (int p = 0; p < NP ; p++){
		// le e armazena o tempo que a planta leva para carregar um caminhão de concreto
		arq >> PlantasInstancia.Plantas[p].TempoPlanta;

		// Dados modelo
		DM.CARRp[p] = PlantasInstancia.Plantas[p].TempoPlanta;

		if( comentarios == 1){
			cout << " Tempo na Planta " << p +1 << " = " <<  PlantasInstancia.Plantas[p].TempoPlanta << endl;
		}
	}
}


// le o tempo maximo permitido entre o atendimento de duas demandas seguidas em cada construção
void	Heuristica::LeTempoMaximoEntreDescargas(int comentarios){
	if( comentarios == 1){
		cout << "     Tempo maximo entre descargas " << endl;
	}
	// percorre por todas as construções
	for ( int c = 0; c < NE; c++){
		// le e armazena o tempo maximo entre dois carregamentos seguidos na mesma construção
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas;

		// Dados modelo
		DM.TETAc[c] = ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas;

		if( comentarios == 1){
			cout << " Construcao " << c + 1 << " = " <<  ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas << endl;
		}
	}
}

// le o tempo minimo e maximo que um caminhão pode começar a descarregar em uma cosntrução
void	Heuristica::LeTempoMaximoMinimoConstrucoes(int comentarios){
	// percorre todas as construções
	for ( int c = 0; c < NE; c++){
		// le e armazena o tempo minimo que se pode receber um caminhão na construção
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento;

		// Dados modelo
		DM.TMINc[c] = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento;

	}
	// percorre todas as construções
	for ( int c = 0; c < NE; c++){
		// le e armazena o tempo máximo que se pode receber um caminhão na construção
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento;

		// Dados modelo
		DM.TMAXc[c] = ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento;

	}
	if( comentarios == 1){
		cout << "     Intervalo de Funcionamento Construcoes " << endl;
		for ( int c = 0; c < NE; c++){
			cout << c + 1 << " ( " << ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento << " - " << ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento << " ) " << endl;
		}
	}
}

// le o tempo minimo e máximo que um caminhão pode começar a carregar em uma planta
void	Heuristica::LeTempoMaximoMinimoPlantas(int comentarios){
	// percorre todas as plantas
	for ( int p = 0; p < NP; p++){
		// le e armazena o tempo minimo que se pode começar a carregar um caminhão na planta corrente
		arq >> PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;

		// Dados modelo
		DM.TMINp[p] = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
	}
	// percorre todas as plantas
	for ( int p = 0; p < NP; p++){
		// le e armazena o tempo máximo que se pode começar a carregar um caminhão na planta corrente
		arq >> PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento;

		// Dados modelo
		DM.TMAXp[p] = PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento;
	}
	if( comentarios == 1){
		cout << "     Intervalo de Funcionamento Plantas " << endl;
		for ( int p = 0; p < NP; p++){
			cout << p + 1 << " ( " << PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento << " - " << PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento << " ) " << endl;
		}
	}
}


// calcula o rank baseado na janela de tempo e no numero de demandas para cada cosntrução
void	Heuristica::CalculoRankTempoDemanda(int comentarios){
	// percorre todas as construções
	for ( int c = 0; c < NE; c++){
		if( comentarios == 1){
			cout << " Construcao " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " com";
		}
		// calcula o rank para a cosntrução corrente
		ConstrucoesInstancia.Construcoes[c].CalculaRankTempoDemandas( comentarios );
	}
}

void Heuristica::IniciaParametrosDoModelo(){




	int VeiculoAux;
	int imprime;

	VeiculoAux = 0;
	imprime = 0;

	// aloca valores nas variaveis S de tempo entre construções consecultivas
	for(int p = 0; p < NP; p++){
		for( int v = 0; v < DM.Veiculos[p]; v++){
			for( int c1 = 0; c1 < NE; c1++){
				for( int d1 = 0; d1 < DM.Demandas[c1]; d1++){
					for( int c2 = 0; c2 < NE; c2++){
						for( int d2 = 0; d2 < DM.Demandas[c2]; d2++){
							DM.S1vii[VeiculoAux][c1][d1][c2][d2] = DM.TEMcp[c1][p] + DM.CARRp[p] + DM.TEMpc[p][c2];
							DM.S2vii[VeiculoAux][c2][d2][c1][d1] = DM.TEMcp[c2][p] + DM.CARRp[p] + DM.TEMpc[p][c1];
						}
					}
				}
			}
			VeiculoAux++;
		}
	}

	// Aloca valor do M1
	for( int v = 0; v < NV; v++){
		for( int c1 = 0; c1 < NE; c1++){
			for( int d1 = 0; d1 < DM.Demandas[c1]; d1++){
				DM.M1vi[v][c1][d1] = DM.TMAXc[c1] + DM.DESCvi[v][c1][d1];
			}
		}
	}

	// Aloca valor do M2
	for( int p = 0; p < NP; p++){
		for( int c1 = 0; c1 < NE; c1++){
			DM.M2pc[p][c1] = DM.TMAXp[p] + DM.CARRp[p] + DM.TEMpc[p][c1];
		}
	}

	// Aloca valor do M3
	for( int c1 = 0; c1 < NE; c1++){
		DM.M3c[c1] = DM.TMAXc[c1];
	}

	// Aloca valor do M4
	VeiculoAux = 0;

	for(int p = 0; p < NP; p++){
		for( int v = 0; v < DM.Veiculos[p]; v++){
			for( int c1 = 0; c1 < NE; c1++){
				for( int d1 = 0; d1 < DM.Demandas[c1]; d1++){
					DM.M4vi[VeiculoAux][c1][d1] = DM.TMAXc[c1] + DM.DESCvi[VeiculoAux][c1][d1] + DM.TEMcp[c1][p];

					if( imprime == 1) {
						cout << " DM.M4vi[" << VeiculoAux << "][" << c1 << "][" << d1 << "] = DM.TMAXc[" << c1 << "] + DM.DESCvi[" << VeiculoAux << "][" << c1 << "][" << d1 << "] + DM.TEMcp[" << c1 << "][" << p << "]" << endl;
						cout << DM.M4vi[VeiculoAux][c1][d1] << " =  " << DM.TMAXc[c1] << " + " << DM.DESCvi[VeiculoAux][c1][d1] << " + " << DM.TEMcp[c1][p] << endl << endl;
					}
				}
			}
			VeiculoAux++;
		}
	}

	// Aloca valor M5 e M6
	for( int v = 0; v < NV; v++){
		for( int c1 = 0; c1 < NE; c1++){
			for( int d1 = 0; d1 < DM.Demandas[c1]; d1++){
				for( int c2 = 0; c2 < NE; c2++){
					for( int d2 = 0; d2 < DM.Demandas[c2]; d2++){
						DM.M5vii[v][c1][d1][c2][d2] = DM.TMAXc[c1] + DM.DESCvi[v][c1][d1] + DM.S1vii[v][c1][d1][c2][d2];
						DM.M6vii[v][c1][d1][c2][d2] = DM.TMAXc[c2] + DM.DESCvi[v][c2][d2] + DM.S2vii[v][c2][d2][c1][d1];
					}
				}
			}
		}
	}

	// Aloca valor do M7
	for( int c1 = 0; c1 < NE; c1++){
		DM.M7c[c1] = DM.TMAXc[c1];
	}

	// Aloca valor M8
	for( int v = 0; v < NV; v++){
		for( int c1 = 0; c1 < NE; c1++){
			for( int d1 = 0; d1 < DM.Demandas[c1]; d1++){
				DM.M8vi[v][c1][d1] = DM.TMAXc[c1] + DM.DESCvi[v][c1][d1];
			}
		}
	}

	// Aloca valor do M9
	for( int p = 0; p < NP; p++){
		DM.M9p[p] = DM.TMAXp[p] + DM.CARRp[p];
	}

	// Aloca valor do M10
	for( int p = 0; p < NP; p++){
		for( int c1 = 0; c1 < NE; c1++){
			DM.M10cp[c1][p] = DM.TMAXc[c1] - DM.TMINp[p];
		}
	}




}

void Heuristica::IniciaVariaveisDoModelo(){


	TVvei.resize(NV);
	for( int v = 0; v < NV; v++){
		TVvei[v].resize(NE);
		for( int e = 0; e < NE; e++){
			TVvei[v][e].resize(DM.Demandas[e]);
		}
	}

	//cout << endl << " TVvei " << endl;
	for( int v = 0; v < NV; v++){
		//cout << " v = " << v << endl;
		for( int e = 0; e < NE; e++){
			//cout << " e = " << e << endl;
			for( int i = 0; i < DM.Demandas[e]; i++){
				TVvei[v][e][i] = 0;
				//cout << "  0  ";
			}
			//cout << endl;
		}
		//cout << endl;
	}
//vector < vector < vector < double > > >TVPvei;

	TVPvei.resize(NV);
	for( int v = 0; v < NV; v++){
		TVPvei[v].resize(NE);
		for( int e = 0; e < NE; e++){
			TVPvei[v][e].resize(DM.Demandas[e]);
		}
	}

	for( int v = 0; v < NV; v++){
		//cout << " v = " << v << endl;
		for( int e = 0; e < NE; e++){
			//cout << " e = " << e << endl;
			for( int i = 0; i < DM.Demandas[e]; i++){
				TVPvei[v][e][i] = 0;
				//cout << "  0  ";
			}
			//cout << endl;
		}
		//cout << endl;
	}


//vector < vector < vector < bool > > >ALFAvei;

	ALFAvei.resize(NV);
	for( int v = 0; v < NV; v++){
		ALFAvei[v].resize(NE);
		for( int e = 0; e < NE; e++){
			ALFAvei[v][e].resize(DM.Demandas[e]);
		}
	}

	//cout << endl << " TVvei " << endl;
	for( int v = 0; v < NV; v++){
		//cout << " v = " << v << endl;
		for( int e = 0; e < NE; e++){
			//cout << " e = " << e << endl;
			for( int i = 0; i < DM.Demandas[e]; i++){
				ALFAvei[v][e][i] = 0;
				//cout << "  0  ";
			}
			//cout << endl;
		}
		//cout << endl;
	}


//vector < vector < vector < vector < vector < bool > > > > > BETAveiei;
	BETAveiei.resize(NV);
	for( int v = 0; v < NV; v++){
		BETAveiei[v].resize(NE);
		for( int e1 = 0; e1 < NE; e1++){
			BETAveiei[v][e1].resize(DM.Demandas[e1]);
			for( int i = 0; i < DM.Demandas[e1]; i++){
				BETAveiei[v][e1][i].resize(NE);
				for( int e2 = 0; e2 < NE; e2++){
					BETAveiei[v][e1][i][e2].resize(DM.Demandas[e2]);
				}
			}
		}
	}

	for( int v = 0; v < NV; v++){
		for( int e1 = 0; e1 < NE; e1++){
			for( int i1 = 0; i1 < DM.Demandas[e1]; i1++){
				for( int e2 = 0; e2 < NE; e2++){
					for( int i2 = 0; i2 < DM.Demandas[e2]; i2++){
						BETAveiei[v][e1][i1][e2][i2] = 0;
					}
				}
			}
		}
	}


//vector < vector < vector < vector < vector < bool > > > > > BETAPpeiei;

	BETAPpeiei.resize(NP);
	for( int p = 0; p < NP; p++){
		BETAPpeiei[p].resize(NE);
		for( int e1 = 0; e1 < NE; e1++){
			BETAPpeiei[p][e1].resize(DM.Demandas[e1]);
			for( int i = 0; i < DM.Demandas[e1]; i++){
				BETAPpeiei[p][e1][i].resize(NE);
				for( int e2 = 0; e2 < NE; e2++){
					BETAPpeiei[p][e1][i][e2].resize(DM.Demandas[e2]);
				}
			}
		}
	}

	for( int p = 0; p < NP; p++){
		for( int e1 = 0; e1 < NE; e1++){
			for( int i1 = 0; i1 < DM.Demandas[e1]; i1++){
				for( int e2 = 0; e2 < NE; e2++){
					for( int i2 = 0; i2 < DM.Demandas[e2]; i2++){
						BETAPpeiei[p][e1][i1][e2][i2] = 0;
					}
				}
			}
		}
	}

	Ze.resize(NE);

}

void Heuristica::AlocaVariaveisDoModelo(){

	int veiculo;

	//cout << "Inicia TVvei e ALFAvei " << endl;
	for( unsigned int c = 0; c < ConstrucoesInstancia.Construcoes.size(); c++){

		//cout << " const = " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << endl;

		for( unsigned int d = 0; d < ConstrucoesInstancia.Construcoes[c].Descarregamentos.size(); d++){

			//cout << "       dem = " << d;
			//cout << " plan = " <<   ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;

			veiculo = 0;
			for( int p1 = 0; p1 < ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor ; p1++){
				for( unsigned int p2 = 0; p2 < PlantasInstancia.Plantas.size(); p2++){
					if( p1 == PlantasInstancia.Plantas[p2].NumeroDaPlanta){
							veiculo = veiculo + PlantasInstancia.Plantas[p2].NumeroVeiculos;
					}
				}
			}

			veiculo = veiculo + ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada;


			//cout << " vei = " <<   veiculo;
			//cout << " Inicio = " << ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento ;
			//cout << " Final = " << ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento ;

			TVvei[ veiculo ][ ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao ][ d ] = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento;
			ALFAvei[ veiculo ][ ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao ][ d ] = 1;

			//cout << "  ** " << endl;
		}
	}



	//cout << "Inicia TVPvei " << endl;
	for( unsigned int p = 0; p < PlantasInstancia.Plantas.size(); p++){
		//cout << " Plan = " << PlantasInstancia.Plantas[p].NumeroDaPlanta << endl;
		for( unsigned int d = 0; d < PlantasInstancia.Plantas[p].Carregamentos.size(); d++){

			veiculo = 0;
			for( int p1 = 0; p1 < PlantasInstancia.Plantas[p].NumeroDaPlanta ; p1++){
				for( unsigned int p2 = 0; p2 < PlantasInstancia.Plantas.size(); p2++){
					if( p1 == PlantasInstancia.Plantas[p2].NumeroDaPlanta){
							veiculo = veiculo + PlantasInstancia.Plantas[p2].NumeroVeiculos;
					}
				}
			}

			veiculo = veiculo + PlantasInstancia.Plantas[p].Carregamentos[d].NumCarretaUtilizada;

			//cout << "  vei = " << veiculo;
			//cout << "  cons = " << PlantasInstancia.Plantas[p].Carregamentos[d].NumeroConstrucao;
			//cout << "  dem = " << PlantasInstancia.Plantas[p].Carregamentos[d].NumeroDemandaSuprida;
			//cout << " inicio = " << PlantasInstancia.Plantas[p].Carregamentos[d].HorarioInicioCarregamento << endl;

			TVPvei[ veiculo ][ PlantasInstancia.Plantas[p].Carregamentos[d].NumeroConstrucao ][ PlantasInstancia.Plantas[p].Carregamentos[d].NumeroDemandaSuprida ] = PlantasInstancia.Plantas[p].Carregamentos[d].HorarioInicioCarregamento;
		}
	}


	int veiculo1;
	int veiculo2;



	// problema
	//cout << " Inicia BETAveiei" <<endl;
	for( unsigned int c1 = 0; c1 < ConstrucoesInstancia.Construcoes.size(); c1++){
		for( unsigned int d1 = 0; d1 < ConstrucoesInstancia.Construcoes[c1].Descarregamentos.size(); d1++){
			for( unsigned int c2 = 0; c2 < ConstrucoesInstancia.Construcoes.size(); c2++){
				for( unsigned int d2 = 0; d2 < ConstrucoesInstancia.Construcoes[c2].Descarregamentos.size(); d2++){

					veiculo1 = 0;
					for( int p1 = 0; p1 < ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumPlantaFornecedor ; p1++){
						for( unsigned int p2 = 0; p2 < PlantasInstancia.Plantas.size(); p2++){
							if( p1 == PlantasInstancia.Plantas[p2].NumeroDaPlanta){
									veiculo1 = veiculo1 + PlantasInstancia.Plantas[p2].NumeroVeiculos;
							}
						}
					}

					veiculo1 = veiculo1 + ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumCarretaUtilizada;

					veiculo2 = 0;
					for( int p1 = 0; p1 < ConstrucoesInstancia.Construcoes[c2].Descarregamentos[d2].NumPlantaFornecedor ; p1++){
						for( unsigned int p2 = 0; p2 < PlantasInstancia.Plantas.size(); p2++){
							if( p1 == PlantasInstancia.Plantas[p2].NumeroDaPlanta){
									veiculo2 = veiculo2 + PlantasInstancia.Plantas[p2].NumeroVeiculos;
							}
						}
					}

					veiculo2 = veiculo2 + ConstrucoesInstancia.Construcoes[c2].Descarregamentos[d2].NumCarretaUtilizada;


					if( ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumPlantaFornecedor == ConstrucoesInstancia.Construcoes[c2].Descarregamentos[d2].NumPlantaFornecedor && veiculo1 == veiculo2 ){
						if( ALFAvei[veiculo1][ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao][d1] == 1 ){
							if( ALFAvei[veiculo2][ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao][d2] == 1){
								if( veiculo1 ==  veiculo2 &&  ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao == ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao && d1 == d2){
									// faz nada
								}else{
									if( TVvei[ veiculo1 ][ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao][d1] < TVvei[ veiculo2 ][ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao][d2]){


										//cout << " vei = " << veiculo1;
										//cout << "  cons1 = " << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << " dem1 = " << d1;
										//cout << "  cons2 = " << ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << " dem2 = " << d2 << endl;
										BETAveiei[ veiculo1 ][ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao][d1][ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao][d2] = 1;
									}
								}
							}
						}
					}
				}
			}
		}
	}


	// problema
	//cout << " Inicia BETAPpeiei" <<endl;
	for( unsigned int c1 = 0; c1 < ConstrucoesInstancia.Construcoes.size(); c1++){
		for( unsigned int d1 = 0; d1 < ConstrucoesInstancia.Construcoes[c1].Descarregamentos.size(); d1++){
			for( unsigned int c2 = 0; c2 < ConstrucoesInstancia.Construcoes.size(); c2++){
				for( unsigned int d2 = 0; d2 < ConstrucoesInstancia.Construcoes[c2].Descarregamentos.size(); d2++){

					veiculo1 = 0;
					for( int p1 = 0; p1 < ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumPlantaFornecedor ; p1++){
						for( unsigned int p2 = 0; p2 < PlantasInstancia.Plantas.size(); p2++){
							if( p1 == PlantasInstancia.Plantas[p2].NumeroDaPlanta){
									veiculo1 = veiculo1 + PlantasInstancia.Plantas[p2].NumeroVeiculos;
							}
						}
					}

					veiculo1 = veiculo1 + ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumCarretaUtilizada;

					veiculo2 = 0;
					for( int p1 = 0; p1 < ConstrucoesInstancia.Construcoes[c2].Descarregamentos[d2].NumPlantaFornecedor ; p1++){
						for( unsigned int p2 = 0; p2 < PlantasInstancia.Plantas.size(); p2++){
							if( p1 == PlantasInstancia.Plantas[p2].NumeroDaPlanta){
									veiculo2 = veiculo2 + PlantasInstancia.Plantas[p2].NumeroVeiculos;
							}
						}
					}

					veiculo2 = veiculo2 + ConstrucoesInstancia.Construcoes[c2].Descarregamentos[d2].NumCarretaUtilizada;

					if( ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumPlantaFornecedor == ConstrucoesInstancia.Construcoes[c2].Descarregamentos[d2].NumPlantaFornecedor ){
						if( ALFAvei[veiculo1][ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao][d1] == 1 ){
							if( ALFAvei[veiculo2][ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao][d2] == 1){
								if( veiculo1 ==  veiculo2 &&  ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao == ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao && d1 == d2){
									// faz nada
								}else{
									if( TVPvei[veiculo1][ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao][d1] <  TVPvei[veiculo2][ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao][d2]){
										//cout << " plan = " << ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumPlantaFornecedor;
										//cout << "  cons1 = " << ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao << " dem1 = " << d1;
										//cout << "  cons2 = " << ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao << " dem2 = " << d2 << endl;
										BETAPpeiei[ConstrucoesInstancia.Construcoes[c1].Descarregamentos[d1].NumPlantaFornecedor][ConstrucoesInstancia.Construcoes[c1].NumeroDaConstrucao][d1][ConstrucoesInstancia.Construcoes[c2].NumeroDaConstrucao][d2] = 1;
									}
								}
							}
						}
					}

				}
			}
		}
	}


	for( unsigned int c = 0; c < ConstrucoesInstancia.Construcoes.size(); c++){
		Ze[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] = 0;

		//cout << " const = " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << endl;

		for( unsigned int d = 0; d < ConstrucoesInstancia.Construcoes[c].Descarregamentos.size(); d++){

			//cout << "       dem = " << d << " vei = " <<   ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada << endl;
			//cout << " Inicio = " << ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento << endl;
			//cout << " Final = " << ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento << endl;

			if( Ze[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] <  ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento){
				Ze[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento;
			}

			//cout << "  ** " << endl;
		}

		//cout << "    				   Coloca Ze[" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "] = " << Ze[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] << endl;
	}



	//cout << "galo " ;


}

Heuristica::~Heuristica(){

}

#endif /* HEURISTICA_HPP_ */
