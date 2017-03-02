/*
 * DeclaraVariaceis.hpp
 *
 *  Created on: 1 de fev de 2017
 *      Author: mavus
 */

#ifndef DECLARAVARIACEIS_HPP_
#define DECLARAVARIACEIS_HPP_

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

	list<string>::iterator it;

	ofstream ArquivoExcelResposta;

	string 	Instancias;

	int 	EscreveDadosLidosNaTela;

	DadosSolomon *InstanciaSolomon;

	ifstream ArquivoInstanciaSolomon;

	ifstream ArquivoInstancia;

	Heuristica *Instancia;

	string TipoDeEntrada;

	unsigned int SementeAleatoria;

	// Exscrever a dadta
	 time_t timer;
	 char 	buffer[26];
	 struct tm* tm_info;




#endif /* DECLARAVARIACEIS_HPP_ */
