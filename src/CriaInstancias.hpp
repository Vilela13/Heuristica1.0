/*
 * CriaInstancias.hpp
 *
 *  Created on: 1 de fev de 2017
 *      Author: mavus
 */

#ifndef CRIAINSTANCIAS_HPP_
#define CRIAINSTANCIAS_HPP_

// -------------------------- Le arquivo com as instancias de Solomon e as guarda em uma lista ----------------------- //

		ArquivoInstanciaSolomon.open( "ArquivosSolomon.txt" );
		if(!ArquivoInstanciaSolomon){
			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << " Arquivo ArquivosSolomon.txt não Existe! \n FUDEU MUITO! \n";
			}
		}else{
			ArquivoInstanciaSolomon >> Nome;
			if( TipoDeEntrada.compare(0,3,"arq") == 0){
				cout << " \n   Armazena nome de instancias Solomon\n " << endl;
			}
			while( Nome != "EOF"){
				ListaInstancias.push_back(Nome);
				ArquivoInstanciaSolomon >> Nome;
			}

			//cout << " Tamanho = " << ListaInstancias.size() << endl << endl;
		 }

		ArquivoInstanciaSolomon.close();



	// -------------------------- Le nome dos arquivos Solomon, carrega os dados, cria arquivo do R, Excel e cria arquivo que pode ser lido pelo Modelo ----------------------- //
//for( int v = 1; v <= 3; v++){
	//for(int m = 2; m <= 4; m++){

		while( ListaInstancias.size() > 0){

			it = ListaInstancias.begin();
			Nome = *it;

			InstanciaSolomon = new DadosSolomon;


			ListaInstancias.pop_front();

			//cout <<  " entra v = " << v << " m = " << m << endl;

			cout << Nome << endl;
			//cout <<  " ai 2" << endl;

			//cout << " entrei 0 - carrega dados" << endl;
			InstanciaSolomon->CarregarNumeroNosCoordenadas( Nome );
			//InstanciaSolomon->EscreverDadosLidosInstanciaSolomon();
			//cout << " sai 0 - carrega dados" << endl;


			//cout << " entrei 1 - escreve Instancia Salomon" << endl;
			InstanciaSolomon->CriarInstanciaSolomon( Nome); //, v, m );
			//cout << " sai 1 - escreve Instancia Salomon" << endl;

			//cout << " entrei 2 - escreve comandos R" << endl;
			InstanciaSolomon->EscreverComandosR( Nome ,'4');
			// 1 => .ps	  2 =>.png   3 =>.jpeg    4 =>.pdf
			//cout << " sai 2 - escreve comandos R" << endl;

			//cout << " entrei 3 - escreve comandos excel" << endl;
			//InstanciaSolomon->EscreverComandosExcel( Nome );					// Não implementado ainda
			//cout << " sai 3 - escreve comandos excel" << endl;

			delete(InstanciaSolomon);

		}
	//}
//}

//ListaInstancias.clear();



#endif /* CRIAINSTANCIAS_HPP_ */
