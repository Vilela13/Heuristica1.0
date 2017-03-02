/*
 * DeclaracaoVariaveisMain.hpp
 *
 *  Created on: 11 de out de 2016
 *      Author: mavus
 */

#ifndef DECLARACAOVARIAVEISMAIN_HPP_
#define DECLARACAOVARIAVEISMAIN_HPP_

	list<string> ListaInstancias;
	string Nome;

	int EscreveDadosLidosNaTela;

	list<string>::iterator it;

	//ofstream ArquivoExcelResposta;
	FILE *ArquivoExcelResposta;

// Exscrever a dadta
	time_t timer;
	char buffer[26];
	struct tm* tm_info;

// Variavel que indica se resolveu
	int resolveu;

// Status da solução
	int Status;
	double SolucaoPrimal;
	double SolucaoDual;
	double SolucaoReal;
	int ConstrucoesComAtrazo;
	int DemandasAfetadas;
	double ValorAtrazoConstrucoes;
	int PlantasComAtrazo;
	double ValorAtrazoPlantas;
	double Gap;
	double Tempo;

	int ComViolacao;

	ifstream ArquivoInstancia;

	ClasseModelo *InstanciaSemViolacao;

	ClasseModeloJanelaViolada *InstanciaComViolacao;

	string Instancias;
	string Saida;

	string TipoDeEntrada;
	int TempoExecucao;


	// Limite superior
	ifstream UpperBounds;
	bool TemLimites;
	vector < string > NomeInstanciaLimiteUpper;
	string NomeInstanciaUpper;
	string ValorUpper;
	vector < double > ValorLimiteUpper;
	double ValorDoubleUpper;



#endif /* DECLARACAOVARIAVEISMAIN_HPP_ */
