//============================================================================
// Name        : 0.cpp
// Author      : Mateus Vilela Souza
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Bibliotecas.hpp"
#include "Plantas.hpp"

using namespace std;

int main(int argc, char **argv) {


	if( argc > 5){

		// tipo de escolha de veiculo, construção e planta
		int 	EscolhaVeiculo;
		int 	EscolhaConstrucao;
		int 	EscolhaPlanta;

		// variavel que armazena o numero de iterações que serão realizadas no GRASP
		string 	NumeroIteracoesString;
		long int 	NumeroIteracoes;
		// tempo maximo de execução em segundos
		string 	TempoExecucaoMaximoString;
		long int 	TempoExecucaoMaximo;

		// variavel que sinaliza se realizará o processo recursivo para se tentar atender a demanda se atrasando as demandas anteriores
		int 	RealizaProcessoDeAtrazarTarefas;


		string Recursao;
		string 	TipoProcedimento;
		list<string> ListaInstancias;
		string 	Nome;

		string 	Saida;
		char *cstr;

		list<string>::iterator it;

		ofstream ArquivoExcelResposta;

		string 	Instancias;

		int 	EscreveDadosLidosNaTela;

		EscreveDadosLidosNaTela = 0;

		DadosSolomon *InstanciaSolomon;

		ifstream ArquivoInstanciaSolomon;

		ifstream ArquivoInstancia;

		Heuristica *Instancia;

		// Exscrever a dadta
		 time_t timer;
		 char 	buffer[26];
		 struct tm* tm_info;

		Recursao = argv[2];

		if( Recursao != "ComRec" && Recursao != "SemRec"){
			cout << endl << endl << endl <<  argv[2] << "   Problema a se definir se o programa irá atrasar as tarefas anteriores para atender uma demanda ou não " << endl << endl << endl;
			return 0;
		}else{
			if( Recursao == "SemRec"){
				// 1 se realizará o processo recursivo para se tentar atender a demanda se atrasando as demandas anteriores, 0 caso contrário
				 RealizaProcessoDeAtrazarTarefas = 0;
			}
			if( Recursao == "ComRec"){
				// 1 se realizará o processo recursivo para se tentar atender a demanda se atrasando as demandas anteriores, 0 caso contrário
				 RealizaProcessoDeAtrazarTarefas = 1;
			}
		}

		TipoProcedimento = argv[3];

		if( TipoProcedimento != "cons" && TipoProcedimento != "consCir" && TipoProcedimento != "grasp" && TipoProcedimento != "graspCir" && TipoProcedimento != "graspClass" && TipoProcedimento != "graspClassCir"){
			cout << endl << endl << endl <<  argv[2] << "   Problema em se identificar o tipo de procediemnto a se realizar " << endl << endl << endl;
			return 0;
		}

	// -------------------------- Le arquivo com as instancias de Solomon e as guarda em uma lista ----------------------- //

		ArquivoInstanciaSolomon.open( "ArquivosSolomon.txt" );
		if(!ArquivoInstanciaSolomon){
			cout << " Arquivo ArquivosSolomon.txt não Existe! \n FUDEU MUITO! \n";
		}else{
			ArquivoInstanciaSolomon >> Nome;
			cout << " \n   Armazena nome de instancias Solomon\n " << endl;
			while( Nome != "EOF"){
				ListaInstancias.push_back(Nome);
				ArquivoInstanciaSolomon >> Nome;
			}

			//cout << " Tamanho = " << ListaInstancias.size() << endl << endl;
		 }

		ArquivoInstanciaSolomon.close();



	// -------------------------- Le nome dos arquivos Solomon, carrega os dados, cria arquivo do R, Excel e cria arquivo que pode ser lido pelo Modelo ----------------------- //
for( int v = 1; v <= 3; v++){
	for(int m = 2; m <= 4; m++){

		//while( ListaInstancias.size() > 0){

			it = ListaInstancias.begin();
			Nome = *it;

			InstanciaSolomon = new DadosSolomon;


			//			ListaInstancias.pop_front();

			cout <<  " entra v = " << v << " m = " << m << endl;

			cout << Nome << endl;
			//cout <<  " ai 2" << endl;

			//cout << " entrei 0 - carrega dados" << endl;
			InstanciaSolomon->CarregarNumeroNosCoordenadas( Nome );
			//InstanciaSolomon->EscreverDadosLidosInstanciaSolomon();
			//cout << " sai 0 - carrega dados" << endl;


			//cout << " entrei 1 - escreve Instancia Salomon" << endl;
			InstanciaSolomon->CriarInstanciaSolomon( Nome , v, m );
			//cout << " sai 1 - escreve Instancia Salomon" << endl;

			//cout << " entrei 2 - escreve comandos R" << endl;
			InstanciaSolomon->EscreverComandosR( Nome ,'4');
			// 1 => .ps	  2 =>.png   3 =>.jpeg    4 =>.pdf
			//cout << " sai 2 - escreve comandos R" << endl;

			//cout << " entrei 3 - escreve comandos excel" << endl;
			//InstanciaSolomon->EscreverComandosExcel( Nome );					// Não implementado ainda
			//cout << " sai 3 - escreve comandos excel" << endl;

			delete(InstanciaSolomon);

		//}
	}
}

ListaInstancias.clear();


		// -------------------------- Resolve as instancais atraevez dos procediemntos implementados ----------------------- //

		Instancias = argv[1];
		//Instancias = "Instancias.txt";

		cstr = new char[Instancias.length() + 1];
		strcpy(cstr, Instancias.c_str());

		ArquivoInstancia.open(cstr);

		delete [] cstr;

		if ( ArquivoInstancia.is_open() ){
			ArquivoInstancia >> Nome;
			//cout << " instancia lida = " << Nome << endl;
			while( Nome != "EOF"){
				ListaInstancias.push_back(Nome);
				ArquivoInstancia >> Nome;
			}
			ArquivoInstancia.close();
		}else{
			cout << "\n \n Arquivo inexistente! \n \n";
			return 0;
		}

			if( TipoProcedimento == "cons" || TipoProcedimento == "consCir"){

			if( argc != 7){
				if( TipoProcedimento == "cons"){
					cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o cons" << endl << endl << endl;
				}else{
					cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o cons Circular" << endl << endl << endl;
				}
				return 0;
			}

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			EscolhaVeiculo = atoi( argv[4]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			EscolhaPlanta = atoi( argv[6]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoProcedimento == "cons" ){
				// escreve a hora da execucao e a parte inicial da tabela
				printf("\n\n ----- Execução CONS as %s ----- \n\n", buffer);
			}else{
				// escreve a hora da execucao e a parte inicial da tabela
				printf("\n\n ----- Execução CONS Circular as %s ----- \n\n", buffer);
			}

			// escreve o tipo de execução

			printf("\n ******************** Tipo Execução **************************** \n\n");

			// escreve o tipo de escolha do veículo
			switch (EscolhaVeiculo) {
				case 1:
					printf("  -> Veículo com menor número de tarefas  \n");
					break;
				case 2:
					printf("  -> Veículo com maior número de tarefas  \n");
					break;
				case 3:
					printf("  -> Veículo em ordem de sua numeração  \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação do veículo \n\n");
					return 0;
					break;
			}

			// escreve o tipo de escolha do cosntrução
			switch (EscolhaConstrucao) {
				case 1:
					printf("  -> Construção com menor Rank (Janela de tempo / Deamanda )   \n");
					break;
				case 2:
					printf("  -> Construção com menor Janela de tempo   \n");
					break;
				case 3:
					printf("  -> Construção com menor Tempo inicio   \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação da cosntrução \n\n");
					return 0;
					break;
			}

			// escreve o tipo de escolha do planta
			switch (EscolhaPlanta) {
				case 1:
					printf("  -> Planta mais proxima da construção \n");
					break;
				case 2:
					printf("  -> Planta com menor número de tarefas \n");
					break;
				case 3:
					printf("  -> Planta com maior número de tarefas \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação da planta \n\n");
					return 0;
					break;
			}

			if( RealizaProcessoDeAtrazarTarefas == 1){
				printf("\n    -> Realzia processo recursivo para se atender uma demanda atrasando as demandas anteriores \n\n");
			}else{
				printf("\n    -> NÃO realzia processo recursivo para se atender uma demanda atrasando as demandas anteriores \n\n");
			}

			printf("\n ******************************************************************** \n\n\n");


			if( TipoProcedimento == "cons" ){
				// escreve cabeçario
				printf(" Nome_Instancia  \t Construtiva \t Viabilidade1 \t Viabilidade2  \t BuscaLocal1 \t BuscaLocal2 \t BuscaLocal3 \t Tempo (segundos) \n");
			}else{
				printf(" Nome_Instancia  \t Construtiva \t Viabilidade1 \t Viabilidade2  \t BuscaLocal \t Tempo (segundos) \n");
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;

					if( TipoProcedimento == "cons" ){
						Instancia->ExecutaCONS(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						Instancia->ExecutaCONScir(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}
				}

				delete(Instancia);
			}

			NumeroIteracoesString.clear();
			TempoExecucaoMaximoString.clear();
			Recursao.clear();
			TipoProcedimento.clear();
			ListaInstancias.clear();
			Nome.clear();
			Saida.clear();
			Instancias.clear();

			ArquivoExcelResposta.close();
			ListaInstancias.clear();

			cout << "\n \n Galo Doido! \n \n";
			return 1;
		 }

		 if( TipoProcedimento == "grasp" || TipoProcedimento == "graspCir"){

			 if( argc != 9){
				 cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o grasp" << endl << endl << endl;
				 return 0;
			 }

			 // numero maximo de iterações
			 NumeroIteracoesString = argv[4];
			 if( NumeroIteracoesString == "-"){
				 NumeroIteracoes = LONG_MAX;
			 }else{
				 if( atoi( argv[4]) > 0){
					 NumeroIteracoes = atoi( argv[4]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Numero de iterações negativo " << Nome << endl << endl;
					 return 0;
				 }
			 }
			 TempoExecucaoMaximoString = argv[5];
			 if( TempoExecucaoMaximoString == "-"){
				 TempoExecucaoMaximo = LONG_MAX;
			 }else{
				 if( atoi( argv[5]) > 0){
					 TempoExecucaoMaximo = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Tempo de execução negativo " << Nome << endl << endl;
					 return 0;
				 }
				 // tempo maximo de execução do problema
				 TempoExecucaoMaximo = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 }

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			EscolhaVeiculo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[7]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			EscolhaPlanta = atoi( argv[8]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoProcedimento == "grasp"){
				// escreve a hora da execucao e a parte inicial da tabela
				printf("\n\n ----- Execução GRASP as %s ----- \n\n", buffer);
			}else{
				// escreve a hora da execucao e a parte inicial da tabela
				printf("\n\n ----- Execução GRASP Circular as %s ----- \n\n", buffer);
			}

			// escreve o tipo de execução

			printf("\n ******************** Tipo Execução **************************** \n\n");

			if( NumeroIteracoesString == "-" ){
				printf("  -> Número irrestrito de iterações  \n");
			}else{
				printf("  -> %ld número de iterações  \n", NumeroIteracoes);
			}

			if( TempoExecucaoMaximoString == "-"){
				printf("  -> Tempo de execução irrestrito  \n");
			}else{
				printf("  -> Tempo maximo para a execução : %ld segundos  \n", TempoExecucaoMaximo );
			}

			// escreve o tipo de escolha do veículo
			switch (EscolhaVeiculo) {
				case 1:
					printf("  -> Veículo com menor número de tarefas  \n");
					break;
				case 2:
					printf("  -> Veículo com maior número de tarefas  \n");
					break;
				case 3:
					printf("  -> Veículo em ordem de sua numeração  \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação do veículo \n\n");
					return 0;
					break;
			}

			// escreve o tipo de escolha do cosntrução
			switch (EscolhaConstrucao) {
				case 0:
					printf("  -> Mantem ordenação aleatória  realizada no processo construtivo  \n");
					break;
				case 1:
					printf("  -> Construção com menor Rank (Janela de tempo / Deamanda )   \n");
					break;
				case 2:
					printf("  -> Construção com menor Janela de tempo   \n");
					break;
				case 3:
					printf("  -> Construção com menor Tempo inicio   \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação da cosntrução \n\n");
					return 0;
					break;
			}

			// escreve o tipo de escolha do planta
			switch (EscolhaPlanta) {
				case 1:
					printf("  -> Planta mais proxima da cosntrução \n");
					break;
				case 2:
					printf("  -> Planta com menor número de tarefas \n");
					break;
				case 3:
					printf("  -> Planta com maior número de tarefas \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação da planta \n\n");
					return 0;
					break;
			}

			if( RealizaProcessoDeAtrazarTarefas == 1){
				printf("\n    -> Realzia processo recursivo para se atender uma demanda atrasando as demandas anteriores \n\n");
			}else{
				printf("\n    -> NÃO realzia processo recursivo para se atender uma demanda atrasando as demandas anteriores \n\n");
			}

			printf("\n ******************************************************************** \n\n\n");

			// escreve cabeçario
			printf(" Nome_Instancia  \t Solução \t Nivel_Viabilidade \t Tempo (segundos) \n");

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;

					srand( clock() + time(NULL));

					if( TipoProcedimento == "grasp"){
						Instancia->ExecutaGrasp(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						Instancia->ExecutaGraspCir(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}

				}
				delete(Instancia);
			}

			NumeroIteracoesString.clear();
			TempoExecucaoMaximoString.clear();
			Recursao.clear();
			TipoProcedimento.clear();
			ListaInstancias.clear();
			Nome.clear();
			Saida.clear();
			Instancias.clear();

			ArquivoExcelResposta.close();
			ListaInstancias.clear();

			cout << "\n \n Galo Doido! \n \n";
			return 1;
		 }





		 if( TipoProcedimento == "graspClass" || TipoProcedimento == "graspClassCir"){

			 if( argc != 9){
				 cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o grasp Classico" << endl << endl << endl;
				 return 0;
			 }


			 // numero maximo de iterações
			 NumeroIteracoesString = argv[4];
			 if( NumeroIteracoesString == "-"){
				 NumeroIteracoes = LONG_MAX;
			 }else{
				 if( atoi( argv[4]) > 0){
					 NumeroIteracoes = atoi( argv[4]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Numero de iterações negativo " << Nome << endl << endl;
					 return 0;
				 }
			 }

			 TempoExecucaoMaximoString = argv[5];
			 if( TempoExecucaoMaximoString == "-"){
				 TempoExecucaoMaximo = LONG_MAX;
			 }else{
				 if( atoi( argv[5]) > 0){
					 TempoExecucaoMaximo = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Tempo de execução negativo " << Nome << endl << endl;
					 return 0;
				 }
				 // tempo maximo de execução do problema
				 TempoExecucaoMaximo = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 }

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			 EscolhaVeiculo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[7]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			 EscolhaPlanta = atoi( argv[8]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)



			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoProcedimento == "grasp"){
				// escreve a hora da execucao e a parte inicial da tabela
				printf("\n\n ----- Execução GRASP Classico as %s ----- \n\n", buffer);
			}else{
				// escreve a hora da execucao e a parte inicial da tabela
				printf("\n\n ----- Execução GRASP Classico Circular as %s ----- \n\n", buffer);
			}


			// escreve o tipo de execução

			printf("\n ******************** Tipo Execução **************************** \n\n");


			if( NumeroIteracoesString == "-" ){
				printf("  -> Número irrestrito de iterações  \n");
			}else{
				printf("  -> %ld número de iterações  \n", NumeroIteracoes);
			}

			if( TempoExecucaoMaximoString == "-"){
				printf("  -> Tempo de execução irrestrito  \n");
			}else{
				printf("  -> Tempo maximo para a execução : %ld segundos  \n", TempoExecucaoMaximo );
			}


			// escreve o tipo de escolha do veículo
			switch (EscolhaVeiculo) {
				case 1:
					printf("  -> Veículo com menor número de tarefas  \n");
					break;
				case 2:
					printf("  -> Veículo com maior número de tarefas  \n");
					break;
				case 3:
					printf("  -> Veículo em ordem de sua numeração  \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação do veículo \n\n");
					return 0;
					break;
			}

			// escreve o tipo de escolha do cosntrução
			switch (EscolhaConstrucao) {
				case 0:
					printf("  -> Mantem ordenação aleatória  realizada no processo construtivo  \n");
					break;
				case 1:
					printf("  -> Construção com menor Rank (Janela de tempo / Deamanda )   \n");
					break;
				case 2:
					printf("  -> Construção com menor Janela de tempo   \n");
					break;
				case 3:
					printf("  -> Construção com menor Tempo inicio   \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação da cosntrução \n\n");
					return 0;
					break;
			}

			// escreve o tipo de escolha do planta
			switch (EscolhaPlanta) {
				case 1:
					printf("  -> Planta mais proxima da cosntrução \n");
					break;
				case 2:
					printf("  -> Planta com menor número de tarefas \n");
					break;
				case 3:
					printf("  -> Planta com maior número de tarefas \n");
					break;
				default:
					printf("\n\n Probelam ao selecionar a ordenação da planta \n\n");
					return 0;
					break;
			}

			if( RealizaProcessoDeAtrazarTarefas == 1){
				printf("\n    -> Realzia processo recursivo para se atender uma demanda atrasando as demandas anteriores \n\n");
			}else{
				printf("\n    -> NÃO realzia processo recursivo para se atender uma demanda atrasando as demandas anteriores \n\n");
			}

			printf("\n ******************************************************************** \n\n\n");



			// escreve cabeçario
			printf(" Nome_Instancia  \t Solução \t Nivel_Viabilidade \t Tempo (segundos) \n");

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;

					srand(clock()+time(NULL));

					if( TipoProcedimento == "graspClass"){
						Instancia->ExecutaGraspClass(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						Instancia->ExecutaGraspClassCir(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}

				}
				delete(Instancia);
			}

			NumeroIteracoesString.clear();
			TempoExecucaoMaximoString.clear();
			Recursao.clear();
			TipoProcedimento.clear();
			ListaInstancias.clear();
			Nome.clear();
			Saida.clear();
			Instancias.clear();

			ListaInstancias.clear();
			ArquivoExcelResposta.close();

			cout << "\n \n Galo Doido! \n \n";
			return 1;
		 }



	}else{
		cout << "\n \n Passagem de parametros errada \n \n";
		return 0;
	}


}
