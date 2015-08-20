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

		int EscreveDadosLidosNaTela;

		list<string>::iterator it;

		ofstream ArquivoExcelResposta;

		string Instancias;



		EscreveDadosLidosNaTela = 1;

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


	// Resolve o problema

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

		while( !ListaInstancias.empty()){
			it = ListaInstancias.begin();
			Nome = *it;
			ListaInstancias.pop_front();
			cout << " Modelo => " << Nome << endl << endl;
			Instancia = new Heuristica;

			if( Instancia->LeDados(Nome, EscreveDadosLidosNaTela) == 1){
				//cout << " Leu Dados" << endl;

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
