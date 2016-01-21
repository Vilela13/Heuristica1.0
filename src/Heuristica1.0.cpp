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


	//if( argc == 2){

		list<string> ListaInstancias;
		string Nome;

		string Saida;
		char *cstr;

		list<string>::iterator it;

		ofstream ArquivoExcelResposta;

		string Instancias;

		int EscreveDadosLidosNaTela;

		EscreveDadosLidosNaTela = 0;

	// -------------------------- Le arquivo com as instancias de Solomon e as guarda em uma lista ----------------------- //

		ifstream ArquivoInstanciaSolomon( "ArquivosSolomon.txt" );
		if(!ArquivoInstanciaSolomon){
			cout << " Arquivo nao Existe! \n FUDEU MUITO! \n";
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

		DadosSolomon *InstanciaSolomon = new DadosSolomon;

		while( ListaInstancias.size() > 0){
			it = ListaInstancias.begin();
			Nome = *it;
			ListaInstancias.pop_front();
			//cout <<  " ai 1" << endl;

			cout << Nome << endl;
			//cout <<  " ai 2" << endl;

			cout << " entrei 0 - carrega dados" << endl;
			InstanciaSolomon->CarregarNumeroNosCoordenadas( Nome );
			//InstanciaSolomon->EscreverDadosLidosInstanciaSolomon();
			cout << " sai 0 - carrega dados" << endl;

			cout << " entrei 1 - escreve Instancia Salomon" << endl;
			InstanciaSolomon->CriarInstanciaSolomon( Nome );
			cout << " sai 1 - escreve Instancia Salomon" << endl;

			cout << " entrei 2 - escreve comandos R" << endl;
			InstanciaSolomon->EscreverComandosR( Nome ,'4');
			// 1 => .ps	  2 =>.png   3 =>.jpeg    4 =>.pdf
			cout << " sai 2 - escreve comandos R" << endl;

			cout << " entrei 3 - escreve comandos excel" << endl;
			InstanciaSolomon->EscreverComandosExcel( Nome );					// Não implementado ainda
			cout << " sai 3 - escreve comandos excel" << endl;
		}
		free(InstanciaSolomon);


		// -------------------------- Resolve as instancais atraevez dos procediemntos implementados ----------------------- //

		//Instancias = argv[1];
		Instancias = "Instancias.txt";

		ifstream ArquivoInstancia;

		cstr = new char[Instancias.length() + 1];
		strcpy(cstr, Instancias.c_str());

		ArquivoInstancia.open(cstr);

		delete [] cstr;

		if ( ArquivoInstancia.is_open() ){
			ArquivoInstancia >> Nome;
			cout << " instancia lida = " << Nome << endl;
			while( Nome != "EOF"){
				ListaInstancias.push_back(Nome);
				ArquivoInstancia >> Nome;
			}
			ArquivoInstancia.close();


		}else{
			cout << "\n \n Arquivo inexistente! \n \n";
			return 0;
		}

		Heuristica *Instancia;

		// Exscrever a dadta
		 time_t timer;
		 char buffer[26];
		 struct tm* tm_info;

		 // tipo de escolha de veiculo, construção e planta
		 int EscolhaVeiculo;
		 int EscolhaConstrucao;
		 int EscolhaPlanta;

		 // ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
		 EscolhaVeiculo = 1;
		 // modo de escolha da construção, 1 escolhe a construção por meio do RankTempoDemandas, 2 escolhe a construção com mais demandas,
		 EscolhaConstrucao = 1;
		 // modo de escolha da planta, 1 é a planta mais proxima, 1 é a planta com menos tarefas, 3 é a planta com mais tarefas
		 EscolhaPlanta = 1;

		 // coleta a data e a hora
		time(&timer);
		tm_info = localtime(&timer);
		strftime(buffer, 26, " * %H:%M:%S de %d:%m:%Y", tm_info);

		// escreve a hora da execucao e a parte inicial da tabela
		printf("\n\n ----- Execução as %s ----- \n\n", buffer);

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

		printf("\n ******************************************************************** \n\n\n");



		// escreve cabeçario
		printf(" Nome_Instancia \t Situacao_Inicial \t Makespan \t Viabilidade1 \t Viabilidade2  \t BuscaLocal1 \t BuscaLocal2 \t BuscaLocal3 \t Tempo \n");

		while( !ListaInstancias.empty()){
			it = ListaInstancias.begin();
			Nome = *it;
			ListaInstancias.pop_front();

			//cout << " Modelo => " << Nome << endl << endl;

			Instancia = new Heuristica;

			if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
				//cout << " Leu Dados" << endl;

				Instancia->ExecutaProcedimentoHeuristico1(Nome, EscolhaVeiculo, EscolhaConstrucao, EscolhaPlanta);

			}
			free(Instancia);
		}

		ArquivoExcelResposta.close();

		cout << "\n \n Galo Doido! \n \n";
		return 1;


/*
	}else{
		cout << "\n \n Passagem de parametros errada \n \n";
		return 0;
	}
	*/

}
