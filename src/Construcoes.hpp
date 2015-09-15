/*
 * Construcoes.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CONSTRUCOES_HPP_
#define CONSTRUCOES_HPP_

#include "Bibliotecas.hpp"

class Descarregamento{
public:
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	int NumeroDemandaSuprida;
	int NumCarretaUtilizada;
	int NumPlantaFornecedor;
	int InicioDescarregamentos;
	int FinalDescarregamentos;

	bool FoiDeslocado;

};

bool DecideQualDescarregamentoVemprimeiro ( Descarregamento d1, Descarregamento d2 ){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}

class DistanciaPlanta{
public:
	double Distancia;
	Planta* PlantaComparada;
};


class Construcao{

public:
	Construcao();
	int NumeroDaConstrucao;
	int NumeroDemandas;
	vector < int > SituacaoDemanda;
	vector < DistanciaPlanta > DistanciaPlantas;
	double TempoMaximoEntreDescargas;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;
	double RankTempoDemandas;
	int StatusAtendimento;

	void CalculaRankTempoDemandas(int);

	vector < Descarregamento > Descarregamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, int, int, int, int, bool);

	void OrdenaDescarregamentosEmOrdemCrescente();
	void MarcaInicioFimDescarregamentos();
	int VerificaDescarregamentosRespeitaIntervalo();

	void ImprimeContrucao();

	vector < bool > SituacaoRemocao;			// SE o valor for 1 ela ja foi removida, se é 0 ela ainda não foi

	~Construcao();

};

Construcao::Construcao(){
	NumeroDaConstrucao = -13;
	NumeroDemandas = -13;
	TempoMaximoEntreDescargas = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	RankTempoDemandas = -13;
	StatusAtendimento = 0;
}

void Construcao::CalculaRankTempoDemandas(int comentarios){
	RankTempoDemandas = ( TempoMaximoDeFuncionamento - TempoMinimoDeFuncionamento) / NumeroDemandas ;
	if( comentarios == 1){
		cout << " Rank ( Tempo / Demandas ) = " << RankTempoDemandas << endl;
	}
}

int Construcao::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){

	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	for( unsigned int d = 0; d < Descarregamentos.size(); d ++){
		// Verifica se possivel alocação possui um descarregamento alocado dentro dela
		if( InicioPossivelAlocacao <= Descarregamentos[d].HorarioInicioDescarregamento){
			if ( Descarregamentos[d].HorarioFinalDescarregamento <= FinalPossivelAlocacao){
				return 0;
			}
		}
		// Verifica se possivel alocação está dentro de um descarregamento alocado
		if( Descarregamentos[d].HorarioInicioDescarregamento <= InicioPossivelAlocacao){
			if ( FinalPossivelAlocacao <= Descarregamentos[d].HorarioFinalDescarregamento){
				return 0;
			}
		}
		// Verifica se possivel alocação está parcialmente dentro de um descarregamento alocado, no seu final
		if( InicioPossivelAlocacao <= Descarregamentos[d].HorarioInicioDescarregamento){
			if( Descarregamentos[d].HorarioInicioDescarregamento < FinalPossivelAlocacao ){
				return 0;
			}
		}
		if( InicioPossivelAlocacao < Descarregamentos[d].HorarioFinalDescarregamento){
			if (  Descarregamentos[d].HorarioFinalDescarregamento <= FinalPossivelAlocacao ){
				return 0;
			}
		}
	}

	if( StatusAtendimento == 0) {
		return 1;
	}else{
		for( unsigned int d = 0; d < Descarregamentos.size(); d ++){
			if( Descarregamentos[d].HorarioFinalDescarregamento <= InicioPossivelAlocacao && InicioPossivelAlocacao <= Descarregamentos[d].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
				return 1;
			}
		}
		return 0;
	}
}

void Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int NumDemanda, int Carreta, int Planta, int inicio, int fim, bool StatusDesalocamento){
	Descarregamento DescarregamentoAux;

	DescarregamentoAux.HorarioInicioDescarregamento = HoraInicio;
	DescarregamentoAux.HorarioFinalDescarregamento = HoraFinal;
	DescarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	DescarregamentoAux.NumCarretaUtilizada = Carreta;
	DescarregamentoAux.NumPlantaFornecedor = Planta;
	DescarregamentoAux.InicioDescarregamentos = inicio;
	DescarregamentoAux.FinalDescarregamentos = fim;
	DescarregamentoAux.FoiDeslocado = StatusDesalocamento;
	SituacaoDemanda[NumDemanda] = 1;

	Descarregamentos.insert(Descarregamentos.begin(), DescarregamentoAux );
}

void Construcao::OrdenaDescarregamentosEmOrdemCrescente(){
	sort (Descarregamentos.begin(), Descarregamentos.end(), DecideQualDescarregamentoVemprimeiro);
}

void Construcao::MarcaInicioFimDescarregamentos(){
	int menor;
	int maior;
	double ValorMenor;
	double ValorMaior;
	ValorMenor = TempoMaximoDeFuncionamento + 1;
	ValorMaior =  0;
	menor = -13;
	maior = -13;

	if( StatusAtendimento > 0){

		for( unsigned int d = 0; d < Descarregamentos.size(); d++){
			Descarregamentos[d].InicioDescarregamentos = 0;
			Descarregamentos[d].FinalDescarregamentos = 0;
			if( Descarregamentos[d].HorarioInicioDescarregamento < ValorMenor){
				ValorMenor = Descarregamentos[d].HorarioInicioDescarregamento;
				menor = d;
			}
			if( Descarregamentos[d].HorarioInicioDescarregamento > ValorMaior){
				ValorMaior = Descarregamentos[d].HorarioInicioDescarregamento;
				maior = d;
			}
		}
		Descarregamentos[menor].InicioDescarregamentos = 1;
		Descarregamentos[maior].FinalDescarregamentos = 1;
	}
	if( menor == -13 || maior == -13 ){
		if( Descarregamentos.size() > 1){
			cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema na ordenacao &&&&&&&&&&&&& " << endl << endl << endl;
		}
	}
}

int Construcao::VerificaDescarregamentosRespeitaIntervalo(){
	bool DescarregamentoEsquerda;
	bool DescarregamentoDireita;
	for( unsigned int d1 = 0; d1 < Descarregamentos.size(); d1++){
		DescarregamentoEsquerda = 0;
		DescarregamentoDireita = 0;
		if( Descarregamentos[d1].InicioDescarregamentos == 1 ){
			DescarregamentoEsquerda = 1;
			for( unsigned int d2 = 0; d2 < Descarregamentos.size(); d2++){
				if( Descarregamentos[d1].HorarioFinalDescarregamento < Descarregamentos[d2].HorarioInicioDescarregamento &&  Descarregamentos[d1].HorarioFinalDescarregamento + TempoMaximoEntreDescargas > Descarregamentos[d2].HorarioInicioDescarregamento ){
					DescarregamentoDireita = 1;
				}
			}
		}

		if( Descarregamentos[d1].FinalDescarregamentos == 1 ){
			DescarregamentoDireita = 1;
			for( unsigned int d2 = 0; d2 < Descarregamentos.size(); d2++){
				if( Descarregamentos[d1].HorarioInicioDescarregamento > Descarregamentos[d2].HorarioFinalDescarregamento && Descarregamentos[d1].HorarioInicioDescarregamento < Descarregamentos[d2].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
					DescarregamentoEsquerda = 1;
				}
			}
		}
		if( Descarregamentos[d1].InicioDescarregamentos == 0 && Descarregamentos[d1].FinalDescarregamentos == 0 ){
			for( unsigned int d2 = 0; d2 < Descarregamentos.size(); d2++){
				if( Descarregamentos[d1].HorarioFinalDescarregamento < Descarregamentos[d2].HorarioInicioDescarregamento &&  Descarregamentos[d1].HorarioFinalDescarregamento + TempoMaximoEntreDescargas > Descarregamentos[d2].HorarioInicioDescarregamento ){
					DescarregamentoDireita = 1;
				}
				if( Descarregamentos[d1].HorarioInicioDescarregamento > Descarregamentos[d2].HorarioFinalDescarregamento && Descarregamentos[d1].HorarioInicioDescarregamento < Descarregamentos[d2].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
					DescarregamentoEsquerda = 1;
				}
			}
		}
		if( Descarregamentos[d1].InicioDescarregamentos == 1 && Descarregamentos[d1].FinalDescarregamentos == 1 ){
			DescarregamentoEsquerda = 1;
			DescarregamentoDireita = 1;
		}
		if ( DescarregamentoDireita == 0 || DescarregamentoEsquerda == 0){
			return 0;
		}
	}
	return 1;
}

void Construcao::ImprimeContrucao(){
	cout << "# Contrucao " << NumeroDaConstrucao << " com " << NumeroDemandas << " demandas, janela de tempo (" <<  TempoMinimoDeFuncionamento;
	cout << "," << TempoMaximoDeFuncionamento << "), com rank = " << RankTempoDemandas << endl;
	if( StatusAtendimento != 0){
		for( unsigned int d = 0; d < Descarregamentos.size(); d++){
			cout << "     * Carreta [" << Descarregamentos[d].NumPlantaFornecedor << "-" << Descarregamentos[d].NumCarretaUtilizada;
			cout << "] atende demanda " << NumeroDaConstrucao << "-" << Descarregamentos[d].NumeroDemandaSuprida;
			cout << " de ( " << Descarregamentos[d].HorarioInicioDescarregamento;
			cout << " as " << Descarregamentos[d].HorarioFinalDescarregamento  << " ) inicio = " << Descarregamentos[d].InicioDescarregamentos;
			cout << " final = " << Descarregamentos[d].FinalDescarregamentos <<  endl;
		}
	}
	cout << "   Vetor de atendimento demandas [ ";
	for ( int i = 0; i < NumeroDemandas; i++){
		cout << SituacaoDemanda[ i ] << " ";
	}
	cout << "]" << endl;
	cout << "   Vetor de Situacao Remocao das demandas [ ";
	for ( int i = 0; i < NumeroDemandas; i++){
		cout << SituacaoRemocao[ i ] << " ";
	}
	cout << "]" << endl;
}


Construcao::~Construcao(){

}


class ConjuntoConstrucoes{

public:
	ConjuntoConstrucoes();
	vector< Construcao > Construcoes;
	int NumeroConstrucoes;

	vector < int > ConstrucaosAnalizadas;
	void InicializaConstrucaosAnalizadas();

	int NivelDeInviabilidade;
	void CalcularNivelDeInviabilidade();

	void OrdenaDescarregamentosConstrucoesOrdemCrescente();
	void  MarcaInicioFimDescarregamentosConstrucoes();

	void IniciaConjuntoConstrucoes(int);
	void ImprimeContrucoes();

	void VerificaIntervaloContrucoes();



	~ConjuntoConstrucoes();
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){
	NumeroConstrucoes = -13;
	NivelDeInviabilidade = -13;
}

void ConjuntoConstrucoes::InicializaConstrucaosAnalizadas(){
	ConstrucaosAnalizadas.resize(Construcoes.size());
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		ConstrucaosAnalizadas[c] = 0;
	}
}

void ConjuntoConstrucoes::CalcularNivelDeInviabilidade(){
	NivelDeInviabilidade = 0;
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		NivelDeInviabilidade = NivelDeInviabilidade + Construcoes[c].NumeroDemandas - Construcoes[c].StatusAtendimento;
	}
}

void  ConjuntoConstrucoes::OrdenaDescarregamentosConstrucoesOrdemCrescente(){
	for( unsigned int c = 0; c < Construcoes.size(); c++){
			Construcoes[c].OrdenaDescarregamentosEmOrdemCrescente();
	}
}

void  ConjuntoConstrucoes::MarcaInicioFimDescarregamentosConstrucoes(){
	for( unsigned int c = 0; c < Construcoes.size(); c++){
			Construcoes[c].MarcaInicioFimDescarregamentos();
	}
}

void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	Construcoes.resize(Numero);
	NumeroConstrucoes = Numero;

}

void ConjuntoConstrucoes::ImprimeContrucoes(){
	cout << endl << endl << " [[[[[[  Imprime construcoes  ]]]]]]" << endl;
	for(int c = 0; c < NumeroConstrucoes; c++){
		Construcoes[c].ImprimeContrucao();
	}

	cout << endl << " Nivel de Inviabilidade = " << NivelDeInviabilidade << endl;

}

void ConjuntoConstrucoes::VerificaIntervaloContrucoes(){

	cout << endl << " Status de respeito aintervelos de construção" << endl;
	for(int c = 0; c < NumeroConstrucoes; c++){
		if( Construcoes[c].VerificaDescarregamentosRespeitaIntervalo() == 1){
			cout << endl << Construcoes[c].NumeroDaConstrucao << " OK!";
		}else{
			cout << endl << Construcoes[c].NumeroDaConstrucao << " inviavel!";
		}
	}
	cout << endl ;
}
ConjuntoConstrucoes::~ConjuntoConstrucoes(){

}


bool DecideQualContrucaoTemMaiorRank (Construcao c1,Construcao c2) {
	return ( c1.RankTempoDemandas < c2.RankTempoDemandas );
}

bool DecideQualContrucaoTemMenorInicioDepoisMaiorRank (Construcao c1,Construcao c2) {
	if( c1.TempoMinimoDeFuncionamento == c2.TempoMinimoDeFuncionamento ){
			return ( c1.RankTempoDemandas < c2.RankTempoDemandas );
	}
	return ( c1.TempoMinimoDeFuncionamento < c2.TempoMinimoDeFuncionamento );
}

bool DecideQualMenorInicioTempoDescarregamento ( Descarregamento d1, Descarregamento d2){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}


#endif /* CONSTRUCOES_HPP_ */
