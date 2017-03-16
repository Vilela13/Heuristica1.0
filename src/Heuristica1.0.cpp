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

#include "DeclaraVariaceis.hpp"

bool EscreveTipoDeExecucao( int EscolhaVeiculo, int EscolhaConstrucao, int EscolhaPlanta, int RealizaProcessoDeAtrazarTarefas){
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
		case 4:
			printf("  -> Veículo em ordem aleatoria  \n");
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
		case 4:
			printf("  -> Construção em ordem aleatoria  \n");
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
		case 4:
			printf("  -> Planta com ordem aleatoria \n");
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
	return 1;


}



int main(int argc, char **argv) {

	EscreveDadosLidosNaTela  = 0;

	// apenas o modelo ************************************************************************
	if( argc == 6 && strcmp ( argv[4], "modelo") == 0 ){		// strcmp for 0 é porque o conteudo é igual

		#include "DeclaracaoVariaveisMain.hpp"

		EscreveDadosLidosNaTela = 0;
		if(strcmp ( argv[5], "Violando") == 0){
			ComViolacao = 1;
		}else{
			if(strcmp ( argv[5], "NaoViolando") == 0){
				ComViolacao = 0;
			}else{
				cout << "    Problema na passagem de parametros do modelo." << endl << endl;
			}

		}

	//Cria instancia manual
		//No PreInstancia;

//Cria instância que criei na mão
		//PreInstancia.PreencheEstrutura();
		//PreInstancia.CriaTXT();


// *************** Pega valores de um arquivo dos Upperbound das intâncias ***************
		TemLimites = 0;
		UpperBounds.open("ValoresLimitesUpper.txt");
		if ( UpperBounds.is_open() ){
			TemLimites = 1;

			UpperBounds >> NomeInstanciaUpper;
			while( NomeInstanciaUpper != "EOF"){
				//cout << " coloca lista = " << Nome  << endl ;
				UpperBounds >> ValorUpper;
				//cout << "   " << NomeInstanciaUpper << " : " << ValorUpper << endl;

				if(ValorUpper.compare("------") == 0 ){
					//cout << "  Sem resposta" << endl;
				}else{
					NomeInstanciaLimiteUpper.push_back(NomeInstanciaUpper);
					ValorDoubleUpper = atof(ValorUpper.c_str());
					//cout << "            " << NomeInstanciaUpper << " valor double : " << ValorDoubleUpper << endl;
					ValorLimiteUpper.push_back(ValorDoubleUpper);
				}
				UpperBounds >> NomeInstanciaUpper;
			}
		}

		//cout << endl<< endl<< " Passou limites :" << TemLimites << endl<< endl;
		if( TemLimites == 1){
			for( int i = 0; i < (int) NomeInstanciaLimiteUpper.size(); i++){
				//cout << NomeInstanciaLimiteUpper[i] << " => " << ValorLimiteUpper[i] << endl;
			}
		}

// *****************************************************************************************
	// Resolve o problema


		TipoDeEntrada = argv[1];
		Instancias = argv[2];
		if( strcmp(argv[3],"-") == 0 ){
			TempoExecucao = INT_MAX;
		}else{
			TempoExecucao = atoi( argv[3] ) ;
		}

		if( TipoDeEntrada.compare(0,3,"arq") == 0 ){
			ArquivoInstancia.open(Instancias.c_str());
			if ( ArquivoInstancia.is_open() ){
				ArquivoInstancia >> Nome;
				while( Nome != "EOF"){
					//cout << " coloca lista = " << Nome  << endl ;
					ListaInstancias.push_back(Nome);
					ArquivoInstancia >> Nome;

				}
				ArquivoInstancia.close();
			}
		}else{
			if( TipoDeEntrada.compare(0,4,"inst") == 0 ){
				ListaInstancias.push_back(Instancias);
			}else{
				cout << "(" << TipoDeEntrada << ")";
				printf( " TipoDeEntrada  -> Problema na definição da entrada das instancias. \n\n\n");
				ListaInstancias.clear();
				Nome.clear();
				Instancias.clear();
				Saida.clear();
				return 0;
			}
		}



		// ----------- Le um arquivo com as instancias a serem resolvidas pelo modelo, abre o arquivo com a instancia e o resolve -------------------------- //

			//cout << endl << endl << " Lendo arquivo " << endl << endl << endl;


		Saida = "R-";				// coloca Res- no char*
		if( TipoDeEntrada.compare(0,3,"arq") == 0 ){
			Saida += Instancias;
		}else{
			Saida += "Instancias.txt";
		}

		//Saida += ".txt";

		//cout << " Saida = > "<< Saida << "   Tamanho entrada = " << TamanhoEntrda << endl;

		//ArquivoExcelResposta.open(Saida.c_str());
		ArquivoExcelResposta = fopen(Saida.c_str(), "a");

		//ArquivoExcelResposta << " Instância" << '\t';
		//ArquivoExcelResposta << " Status" << '\t';
		//ArquivoExcelResposta << " Solução Primal" << '\t';
		//ArquivoExcelResposta << " Solução Dual" << '\t';
		//ArquivoExcelResposta << " Gap" << '\t';
		//ArquivoExcelResposta << " Tempo" << '\n';

		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);


		if( TipoDeEntrada.compare("arq") == 0 ){
			fprintf(ArquivoExcelResposta,"%s \n", buffer);
			if( ComViolacao == 0){
				fprintf(ArquivoExcelResposta, "Instância \t Status \t Solução_Primal \t Solução_Dual \t Solução_Real \t Gap \t Tempo \n");
			}else{
				fprintf(ArquivoExcelResposta, "Instância \t Status \t Solução_Primal \t Solução_Dual \t Solução_Real \t Construcoes_Com_Atrazo \t Demandas_Afetadas  \t Gap \t Tempo \n");
			}
		}
		fclose(ArquivoExcelResposta);



		while( !ListaInstancias.empty()){

			if( ComViolacao == 0){
				InstanciaSemViolacao = new ClasseModelo;
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();
				cout << " Modelo <= " << Nome << endl ;

				if( InstanciaSemViolacao->LeDados(Nome, EscreveDadosLidosNaTela) == 1){

					resolveu = InstanciaSemViolacao->Cplex(Nome,  TempoExecucao, Status, SolucaoPrimal, SolucaoDual, SolucaoReal,   Gap, Tempo, NomeInstanciaLimiteUpper, ValorLimiteUpper);
					cout  << " Resolveu = " << resolveu << endl << endl ;

					ArquivoExcelResposta = fopen(Saida.c_str(), "a");
					fprintf(ArquivoExcelResposta, " %s \t", Nome.c_str());
					//ArquivoExcelResposta << Nome  << '\t' ;

					DescobreStatus( Status, ArquivoExcelResposta);

					//ArquivoExcelResposta << " " <<   SolucaoPrimal << '\t' <<  " " << SolucaoDual << '\t' << " " <<   Gap << '\t' <<  " " << Tempo << '\n';
					fprintf(ArquivoExcelResposta, "%.3f \t %.3f \t %.3f \t %.3f \t %.3f \t \n", SolucaoPrimal, SolucaoDual, SolucaoReal, Gap, Tempo);
					fclose(ArquivoExcelResposta);

				}
				//cout << endl << " Antes do free " << Nome <<  endl;

				delete(InstanciaSemViolacao);
				//cout << endl << " Depois do free "  << Nome << endl;

			}else{

				InstanciaComViolacao = new ClasseModeloJanelaViolada ;
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();
				cout << " Modelo <= " << Nome << endl ;

				if( InstanciaComViolacao->LeDados(Nome, EscreveDadosLidosNaTela) == 1){

					resolveu = InstanciaComViolacao->Cplex(Nome,  TempoExecucao, Status, SolucaoPrimal, SolucaoDual, SolucaoReal, ConstrucoesComAtrazo, DemandasAfetadas,   Gap, Tempo, NomeInstanciaLimiteUpper, ValorLimiteUpper);
					cout  << " Resolveu = " << resolveu << endl << endl ;

					ArquivoExcelResposta = fopen(Saida.c_str(), "a");
					fprintf(ArquivoExcelResposta, " %s \t", Nome.c_str());
					//ArquivoExcelResposta << Nome  << '\t' ;

					DescobreStatus( Status, ArquivoExcelResposta);

					//ArquivoExcelResposta << " " <<   SolucaoPrimal << '\t' <<  " " << SolucaoDual << '\t' << " " <<   Gap << '\t' <<  " " << Tempo << '\n';
					fprintf(ArquivoExcelResposta, "%.3f \t %.3f \t %.3f \t %d \t %d \t %.3f \t %d \t %.3f \t %.3f \t %.3f \t \n", SolucaoPrimal, SolucaoDual, SolucaoReal,ConstrucoesComAtrazo, DemandasAfetadas, ValorAtrazoConstrucoes, PlantasComAtrazo, ValorAtrazoPlantas, Gap, Tempo);
					fclose(ArquivoExcelResposta);

				}
				//cout << endl << " Antes do free " << Nome <<  endl;

				delete(InstanciaComViolacao);
				//cout << endl << " Depois do free "  << Nome << endl;
			}

		}

		//ArquivoExcelResposta.close();

		if( TipoDeEntrada.compare("arq") == 0 ){
			cout << " \n Acabou!   Galo Doido! \n";
		}



		ListaInstancias.clear();
		Nome.clear();
		Instancias.clear();
		Saida.clear();
		return 1;

	}



	// apenas huristicas **************************************************************************
	if( (argc == 9 || argc == 11) && strcmp( argv[1], "ModeloComInicio") != 0){

		if( argc == 9) {
			if( strcmp( argv[8], "heuristica") != 0 ){
				cout << "   Passagem errada de parametros " << endl << endl;
				return 0;
			}
		}

		if( argc == 11) {
			if( strcmp( argv[10], "heuristica") != 0 ){
				cout << "   Passagem errada de parametros " << endl << endl;
				return 0;
			}
		}


		#include "CriaInstancias.hpp"

		// -------------------------- Resolve as instancais atraevez dos procediemntos implementados ----------------------- //

		TipoDeEntrada = argv[1];
		Instancias = argv[2];
		//Instancias = "Instancias.txt";

		Recursao = argv[3];

		if( Recursao != "ComRec" && Recursao != "SemRec"){
			cout << endl << endl << endl <<  argv[3] << "   Problema a se definir se o programa irá atrasar as tarefas anteriores para atender uma demanda ou não " << endl << endl << endl;
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

		TipoProcedimento = argv[4];

		if( TipoProcedimento != "Cons" && TipoProcedimento != "Cons100" && TipoProcedimento != "ConsBuscVei" && TipoProcedimento != "ConsBuscCons" && TipoProcedimento != "ConsBuscPlan" && TipoProcedimento != "ConsBuscasVeiConsPlan" && TipoProcedimento != "ConsBuscas" && TipoProcedimento != "ConsBuscasCir" && TipoProcedimento != "Grsp" && TipoProcedimento != "GrspCir" && TipoProcedimento != "GrspClass" && TipoProcedimento != "GrspClassCir"){
			cout << endl << endl << endl <<  argv[4] << "   Problema em se identificar o tipo de procediemnto a se realizar " << endl << endl << endl;
			return 0;
		}


		// caso for passado o parametro arq, que quer dizer que um conjunto de instancias será testado se entra nesse loop. compare retorna 0 se o string for igual ao texto (arq) que se quer comparar.
		if( TipoDeEntrada.compare(0,3,"arq") == 0 ){
			ArquivoInstancia.open(Instancias.c_str());
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
		}else{

		// caso for apenas uma intância, se coloca na lista de instancia apena a instancia que se quer comprar
			if( TipoDeEntrada.compare(0,4,"inst") == 0 ){
				ListaInstancias.push_back(Instancias);
			}else{
				cout << "(" << TipoDeEntrada << ")";
				printf( " TipoDeEntrada  Problema na definição da entrada das instancias. \n\n\n");
				ListaInstancias.clear();
				Nome.clear();
				Instancias.clear();
				Saida.clear();
				return 0;
			}
		}

		if( TipoProcedimento == "Cons"){

			if( argc != 9){
				if( TipoProcedimento == "Cons"){
					cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o cons" << endl << endl << endl;
				}
				return 0;
			}

			srand ( time(NULL) + clock()  );

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			EscolhaVeiculo = atoi( argv[5]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			EscolhaPlanta = atoi( argv[7]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				if( TipoProcedimento == "Cons" ){
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução Cons as %s ----- \n\n", buffer);
				}

				// escreve o tipo de execução

				if( EscreveTipoDeExecucao( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas) == 0){
					return 0;
				}

				if( TipoProcedimento == "Cons" ){
					// escreve cabeçario
					printf(" Nome_Instancia  \t Construtiva \t Viabilidade1 \t Viabilidade2  \t  Tempo (segundos) \n");
				}
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;

					if( TipoProcedimento == "Cons" ){
						Instancia->ExecutaCons(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
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

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << "\n \n Galo Doido! \n \n";
			}
			return 1;
		 }


		if( TipoProcedimento == "Cons100"){

			if( argc != 9){
				if( TipoProcedimento == "Cons100"){
					cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o cons" << endl << endl << endl;
				}
				return 0;
			}

			srand ( time(NULL) + clock()  );

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			EscolhaVeiculo = atoi( argv[5]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			EscolhaPlanta = atoi( argv[7]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				if( TipoProcedimento == "Cons400" ){
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução Cons400 as %s ----- \n\n", buffer);
				}

				// escreve o tipo de execução

				if( EscreveTipoDeExecucao( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas) == 0){
					return 0;
				}

				if( TipoProcedimento == "Cons100" ){
					// escreve cabeçario
					printf(" Nome_Instancia  \t Construtiva \t NivelDeInviabilidade  \t  Tempo(segundos) \n");
				}
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;

					if( TipoProcedimento == "Cons100" ){
						Instancia->ExecutaCons100(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
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

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << "\n \n Galo Doido! \n \n";
			}
			return 1;
		 }



		if( TipoProcedimento == "ConsBuscVei" || TipoProcedimento == "ConsBuscCons" || TipoProcedimento == "ConsBuscPlan" || TipoProcedimento == "ConsBuscasVeiConsPlan"){

			 if( argc != 11){
				 cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o " << TipoProcedimento << endl << endl << endl;
				 return 0;
			 }


			 // numero maximo de iterações
			 NumeroIteracoesString = argv[5];
			 if( NumeroIteracoesString == "-"){
				 NumeroIteracoes = LONG_MAX;
			 }else{
				 if( atoi( argv[5]) > 0){
					 NumeroIteracoes = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Numero de iterações negativo " << Nome << endl << endl;
					 return 0;
				 }
			 }

			 // pega o tempo de execução
			 TempoExecucaoMaximoString = argv[6];
			 if( TempoExecucaoMaximoString == "-"){
				 TempoExecucaoMaximo = LONG_MAX;
			 }else{
				 if( atoi( argv[6]) > 0){
					 TempoExecucaoMaximo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Tempo de execução negativo " << Nome << endl << endl;
					 return 0;
				 }
				 // tempo maximo de execução do problema
				 TempoExecucaoMaximo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 }

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			 EscolhaVeiculo = atoi( argv[7]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			 EscolhaConstrucao = atoi( argv[8]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			 EscolhaPlanta = atoi( argv[9]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)



			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				if( TipoProcedimento == "ConsBuscVei"){
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução ConsBuscVei as %s ----- \n\n", buffer);
				}else{
					if(TipoProcedimento == "ConsBuscCons"){
						// escreve a hora da execucao e a parte inicial da tabela
						printf("\n\n ----- Execução ConsBuscCons as %s ----- \n\n", buffer);
					}else{
						if( TipoProcedimento == "ConsBuscPlan" ){
							printf("\n\n ----- Execução ConsBuscPlan as %s ----- \n\n", buffer);
						}else{
							printf("\n\n ----- Execução ConsBuscVeiconsPlan as %s ----- \n\n", buffer);
						}
					}

				}

				SementeAleatoria = (unsigned int)  ( clock() + time(NULL) );

				srand( SementeAleatoria);

				printf(" Semente Aleatoria : %u \n\n",SementeAleatoria);



				// escreve o tipo de execução

				if( EscreveTipoDeExecucao( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas) == 0){
					return 0;
				}



				// escreve cabeçario
				printf(" Nome_Instancia  \t Solução \t Nivel_Viabilidade \t Tempo (segundos) \n");
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;



					if( TipoProcedimento == "ConsBuscVei"){
						Instancia->ExecutaConsBuscVei(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						if( TipoProcedimento == "ConsBuscCons"){
							Instancia->ExecutaConsBuscCons(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
						}else{
							if( TipoProcedimento == "ConsBuscPlan" ){
								Instancia->ExecutaConsBuscPlan(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
							}else{
								Instancia->ExecutaConsBuscasVeiConsPlan(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
							}
						}

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

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << "\n \n Galo Doido! \n \n";
			}
			return 1;
		 }







		if( TipoProcedimento == "ConsBuscas" || TipoProcedimento == "ConsBuscasCir"){

			if( argc != 9){
				if( TipoProcedimento == "ConsBuscas"){
					cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o cons" << endl << endl << endl;
				}else{
					cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o cons Circular" << endl << endl << endl;
				}
				return 0;
			}

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			EscolhaVeiculo = atoi( argv[5]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			EscolhaPlanta = atoi( argv[7]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				if( TipoProcedimento == "ConsBuscas" ){
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução ConsBuscas as %s ----- \n\n", buffer);
				}else{
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução ConsBuscas Circular as %s ----- \n\n", buffer);
				}


				// escreve o tipo de execução

				if( EscreveTipoDeExecucao( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas) == 0){
					return 0;
				}

				if( TipoProcedimento == "cons" ){
					// escreve cabeçario
					printf(" Nome_Instancia  \t Construtiva \t Viabilidade1 \t Viabilidade2  \t BuscaLocal1 \t BuscaLocal2 \t BuscaLocal3 \t Tempo (segundos) \n");
				}else{
					printf(" Nome_Instancia  \t Construtiva \t Viabilidade1 \t Viabilidade2  \t BuscaLocal \t Tempo (segundos) \n");
				}
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;

					if( TipoProcedimento == "ConsBuscas" ){
						Instancia->ExecutaConsBuscas(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						Instancia->ExecutaConsBuscasCir(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
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

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << "\n \n Galo Doido! \n \n";
			}
			return 1;
		 }

		 if( TipoProcedimento == "Grsp" || TipoProcedimento == "GrspCir"){

			 if( argc != 11){
				 cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o Grsp" << endl << endl << endl;
				 return 0;
			 }

			 // numero maximo de iterações
			 NumeroIteracoesString = argv[5];
			 if( NumeroIteracoesString == "-"){
				 NumeroIteracoes = LONG_MAX;
			 }else{
				 if( atoi( argv[5]) > 0){
					 NumeroIteracoes = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Numero de iterações negativo " << Nome << endl << endl;
					 return 0;
				 }
			 }
			 TempoExecucaoMaximoString = argv[6];
			 if( TempoExecucaoMaximoString == "-"){
				 TempoExecucaoMaximo = LONG_MAX;
			 }else{
				 if( atoi( argv[6]) > 0){
					 TempoExecucaoMaximo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Tempo de execução negativo " << Nome << endl << endl;
					 return 0;
				 }
				 // tempo maximo de execução do problema
				 TempoExecucaoMaximo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 }

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			EscolhaVeiculo = atoi( argv[7]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[8]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			EscolhaPlanta = atoi( argv[9]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				if( TipoProcedimento == "Grsp"){
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução GRASP as %s ----- \n\n", buffer);
				}else{
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução GRASP Circular as %s ----- \n\n", buffer);
				}

				SementeAleatoria = (unsigned int)  ( clock() + time(NULL) );

				srand( SementeAleatoria);

				printf(" Semente Aleatoria : %u \n\n",SementeAleatoria);

				// escreve o tipo de execução

				if( EscreveTipoDeExecucao( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas) == 0){
					return 0;
				}

				// escreve cabeçario
				printf(" Nome_Instancia  \t Solução \t Nivel_Viabilidade \t Tempo (segundos) \n");
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;


					if( TipoProcedimento == "Grsp"){
						Instancia->ExecutaGrsp(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						Instancia->ExecutaGrspCir(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
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

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << "\n \n Finalizou!  Galo Doido! \n \n";
			}
			return 1;
		 }





		 if( TipoProcedimento == "GrspClass" || TipoProcedimento == "GrspClassCir"){

			 if( argc != 11){
				 cout << endl << endl << endl << "    Probelma na entrada de parametros para se executar o Grsp Classico" << endl << endl << endl;
				 return 0;
			 }


			 // numero maximo de iterações
			 NumeroIteracoesString = argv[5];
			 if( NumeroIteracoesString == "-"){
				 NumeroIteracoes = LONG_MAX;
			 }else{
				 if( atoi( argv[5]) > 0){
					 NumeroIteracoes = atoi( argv[5]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Numero de iterações negativo " << Nome << endl << endl;
					 return 0;
				 }
			 }

			 TempoExecucaoMaximoString = argv[6];
			 if( TempoExecucaoMaximoString == "-"){
				 TempoExecucaoMaximo = LONG_MAX;
			 }else{
				 if( atoi( argv[6]) > 0){
					 TempoExecucaoMaximo = atoi( argv[6]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
				 }else{
					 cout << endl << endl << " Tempo de execução negativo " << Nome << endl << endl;
					 return 0;
				 }
			 }

			 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
			 EscolhaVeiculo = atoi( argv[7]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
			EscolhaConstrucao = atoi( argv[8]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
			 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
			 EscolhaPlanta = atoi( argv[9]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)



			 // coleta a data e a hora
			time(&timer);
			tm_info = localtime(&timer);
			strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				if( TipoProcedimento == "Grsp"){
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução GRASP Classico as %s ----- \n\n", buffer);
				}else{
					// escreve a hora da execucao e a parte inicial da tabela
					printf("\n\n ----- Execução GRASP Classico Circular as %s ----- \n\n", buffer);
				}

				SementeAleatoria = (unsigned int)  ( clock() + time(NULL) );

				srand( SementeAleatoria);

				printf(" Semente Aleatoria : %u \n\n",SementeAleatoria);



				// escreve o tipo de execução

				if( EscreveTipoDeExecucao( EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta, RealizaProcessoDeAtrazarTarefas) == 0){
					return 0;
				}



				// escreve cabeçario
				printf(" Nome_Instancia  \t Solução \t Nivel_Viabilidade \t Tempo (segundos) \n");
			}

			while( !ListaInstancias.empty()){
				it = ListaInstancias.begin();
				Nome = *it;
				ListaInstancias.pop_front();

				//cout << " Modelo => " << Nome << endl << endl;

				Instancia = new Heuristica;

				if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
					//cout << " Leu Dados" << endl;



					if( TipoProcedimento == "GrspClass"){
						Instancia->ExecutaGrspClass(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
					}else{
						Instancia->ExecutaGrspClassCir(Nome, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo,  EscolhaConstrucao,  EscolhaPlanta, RealizaProcessoDeAtrazarTarefas);
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

			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << "\n \n Galo Doido! \n \n";
			}
			return 1;
		 }



	}



	// modelo com inicio na heuristica
	if( argc = 10 && strcmp ( argv[1], "ModeloComInicio") == 0 ){

		int StatusInicio;
		double PrimalInicio;
		double DualInicio;
		double SolucaoRealInicio;
		double GapInicio;
		double TempoInicio;

		ClasseModeloInicioHeuristica *InstanciaInicioHeuristica;

		//cout << endl << " entrou " << endl;

		Instancias = argv[2];

		Recursao = argv[3];

		if( Recursao != "ComRec" && Recursao != "SemRec"){
			cout << endl << endl << endl <<  argv[4] << "   Problema a se definir se o programa irá atrasar as tarefas anteriores para atender uma demanda ou não " << endl << endl << endl;
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
		 }

		srand ( time(NULL) + clock()  );

		 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
		EscolhaVeiculo = atoi( argv[6]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
		 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
		EscolhaConstrucao = atoi( argv[7]);		// função atoi tranforma char em inteiro ( biblioteca stdlib.h)
		 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
		EscolhaPlanta = atoi( argv[8]);			// função atoi tranforma char em inteiro ( biblioteca stdlib.h)

		// modelo **************************************************************************************


		double TempoExecucao;
		if( strcmp(argv[9],"-") == 0 ){
			TempoExecucao = INT_MAX;
		}else{
			TempoExecucao = atoi( argv[9] ) ;
		}

		InstanciaInicioHeuristica = new ClasseModeloInicioHeuristica;
		if( InstanciaInicioHeuristica->LeDados(Instancias, EscreveDadosLidosNaTela) == 1){
			//cout << "   Leu dados " << endl << endl;

			//cout << endl <<  "TempoExecucaoMaximo  " << TempoExecucaoMaximo << endl << endl;

			InstanciaInicioHeuristica->CplexInicia(Instancias, RealizaProcessoDeAtrazarTarefas, NumeroIteracoes, TempoExecucaoMaximo, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta,  TempoExecucao, StatusInicio, PrimalInicio, DualInicio, SolucaoRealInicio, GapInicio, TempoInicio);
		}

		return 1;


	}




	cout << "\n \n Passagem de parametros errada fim\n \n";
	return 0;


}
