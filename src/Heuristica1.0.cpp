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

		char *a;
		list<char*> ListaInstancias;
		string Nome;

		char Saida[200];

		int EscreveDadosLidosNaTela;

		list<char*>::iterator it;

		ofstream ArquivoExcelResposta;



		EscreveDadosLidosNaTela = 1;

	// -------------------------- Le arquivo com as instancias de Solomon e as guarda em uma lista ----------------------- //

		ifstream ArquivoInstanciaSolomon( "ArquivosSolomon.txt" );
		if(!ArquivoInstanciaSolomon){
			cout << " Arquivo nao Existe! \n FUDEU MUITO! \n";
		}else{

			ArquivoInstanciaSolomon >> Nome;
			cout << " \n   Arqmazena nome de instancias \n " << endl;
			while( Nome != "EOF"){
				a = new char[Nome.size()+1];
				a[Nome.size()]=0;
				memcpy(a,Nome.c_str(),Nome.size());
				cout << "  " << a  << endl ;
				ListaInstancias.push_back(a);
				ArquivoInstanciaSolomon >> Nome;
			}

			//cout << " Tamanho = " << ListaInstancias.size() << endl << endl;
		 }

		ArquivoInstanciaSolomon.close();

	// -------------------------- Le nome dos arquivos Solomon, carrega os dados, cria arquivo do R, Excel e cria arquivo que pode ser lido pelo Modelo ----------------------- //

		DadosSolomon *InstanciaSolomon = new DadosSolomon;

		while( ListaInstancias.size() > 0){
			it = ListaInstancias.begin();
			a = *it;
			ListaInstancias.pop_front();
			//cout <<  " ai 1" << endl;

			cout << a << endl;
			//cout <<  " ai 2" << endl;

			InstanciaSolomon->CarregarNumeroNosCoordenadas(a);
			//InstanciaSolomon->EscreverDadosLidosInstanciaSolomon();
			cout << " entrei 0 - carrega dados" << endl;

			InstanciaSolomon->CriarInstanciaSolomon(a);
			cout << " entrei 1 - escreve Instancia Salomon" << endl;

			InstanciaSolomon->EscreverComandosR(a,'4');
			// 1 => .ps	  2 =>.png   3 =>.jpeg    4 =>.pdf
			cout << " entrei 2 - escreve comandos R" << endl;

			InstanciaSolomon->EscreverComandosExcel(a);					// Não implementado ainda
			cout << " entrei 3 - escreve comandos excel" << endl;
		}
		free(InstanciaSolomon);




	// Resolve o problema

		char* Instancias;
		Instancias = argv[1];
		Instancias = "Instancias.txt";

		ifstream ArquivoInstancia;
		ArquivoInstancia.open(Instancias);
		if ( ArquivoInstancia.is_open() ){
			ArquivoInstancia >> Nome;
			while( Nome != "EOF"){
				a = new char[Nome.size()+1];
				a[Nome.size()]=0;
				memcpy(a,Nome.c_str(),Nome.size());
				cout << a  << endl ;
				ListaInstancias.push_back(a);
				ArquivoInstancia >> Nome;
			}
			ArquivoInstancia.close();


		// ----------- Le um arquivo com as instancias a serem resolvidas pelo modelo, abre o arquivo com a instancia e o resolve -------------------------- //

			//cout << endl << endl << " Lendo arquivo " << endl << endl << endl;

			char Saida[200];
			int TamanhoEntrda;
			strcpy (Saida,"Res-");				// coloca Res- no char*
			TamanhoEntrda = strcspn (Instancias,".");	// Ve o tamanho do char* passado na entrada
			if(TamanhoEntrda > 12){				// Fixa o tamanho minimo da string
				TamanhoEntrda = 12;
			}
			strncat (Saida, Instancias, TamanhoEntrda);	// Cria o nome do arquivo de saida
			strcat (Saida,".txt");
		}else{
			cout << "\n \n Arquivo inexistente! \n \n";
			return 0;
		}


		ArquivoExcelResposta.open(Saida);


		Heuristica *Instancia;

		while( !ListaInstancias.empty()){
			it = ListaInstancias.begin();
			a = *it;
			ListaInstancias.pop_front();
			cout << " Modelo <= " << a << endl << endl;
			Instancia = new Heuristica;

			if( Instancia->LeDados(a, EscreveDadosLidosNaTela) == 1){
				cout << " Leu Dados" << endl;

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
