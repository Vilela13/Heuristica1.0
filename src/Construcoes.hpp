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

	void Imprime();

};

bool DecideQualDescarregamentoVemprimeiro ( Descarregamento d1, Descarregamento d2 ){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}

void Descarregamento::Imprime(){
	cout << " Demanda = " << NumeroDemandaSuprida;
	cout << " Planta = " << NumPlantaFornecedor;
	cout << " Carreta = " << NumCarretaUtilizada ;
	cout << " Inicio = " << InicioDescarregamentos << " Final = " << FinalDescarregamentos << endl;
	cout << " Tempo [" << HorarioInicioDescarregamento << " - " << HorarioFinalDescarregamento << "]" << endl;
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

	double Makespan;

	void CalculaRankTempoDemandas(int);

	vector < Descarregamento > Descarregamentos;

	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, int, int, int, int, bool, int);
	int DeletaAtividade(double, double, int, int, int);

	void OrdenaDescarregamentosEmOrdemCrescente();
	void MarcaInicioFimDescarregamentos();
	int VerificaDescarregamentosRespeitaIntervalo();

	void RetornaHorarioInicioCarregamento(  int, double&);

	void RetornaDadosDescarregamento( int, int&, int&, int&, int&, double&, double&);

	void CalculaMakespan();

	void ImprimeContrucao();

	vector < int > SituacaoRemocao;			// SE o valor for 1 ela ja foi removida, se é 0 ela ainda não foi

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
	Makespan = -13;
}

void Construcao::CalculaRankTempoDemandas(int comentarios){
	RankTempoDemandas = ( TempoMaximoDeFuncionamento - TempoMinimoDeFuncionamento) / NumeroDemandas ;
	if( comentarios == 1){
		cout << " Rank ( Tempo / Demandas ) = " << RankTempoDemandas << endl;
	}
}

int Construcao::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	int PossuiTarefaAnterior;
	int PossuiTarefaPosterior;

	PossuiTarefaAnterior = 0;
	PossuiTarefaPosterior = 0;

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
		// Verifica se possivel alocação está parcialmente dentro de um descarregamento alocado, no inicio do deslocamento já alocado
		if( InicioPossivelAlocacao <= Descarregamentos[d].HorarioInicioDescarregamento){
			if( Descarregamentos[d].HorarioInicioDescarregamento < FinalPossivelAlocacao ){
				return 0;
			}
		}
		// Verifica se possivel alocação está parcialmente detro de um descarregamento, no fim do deslocamento já alocado
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
				PossuiTarefaAnterior = 1;
			}
			if( FinalPossivelAlocacao <=  Descarregamentos[d].HorarioInicioDescarregamento &&  Descarregamentos[d].HorarioInicioDescarregamento   <= FinalPossivelAlocacao + TempoMaximoEntreDescargas ){
				PossuiTarefaPosterior = 1;
			}
		}

		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 0){
			// Entra no depois de todas as tarefas alocadas
			return 1;
		}
		if ( PossuiTarefaAnterior == 0 && PossuiTarefaPosterior == 1){
			// Entra antes de todas as tarefas alocadas
			return 2;
		}
		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 1){
			// Entra no meio de duas tarefas alocadas
			cout << endl << endl << " No meio das tarefas ->Construcao::VerificaDisponibilidade  " << endl << endl << endl;
			return 3;

		}

		// Não respeita o intervalo de tempo necessario entre um descarregamento e outro
		return -1;

	}
}

void Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int NumDemanda, int Carreta, int Planta, int inicio, int fim, bool StatusDesalocamento, int Situacao){
	Descarregamento DescarregamentoAux;

	DescarregamentoAux.HorarioInicioDescarregamento = HoraInicio;
	DescarregamentoAux.HorarioFinalDescarregamento = HoraFinal;
	DescarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	DescarregamentoAux.NumCarretaUtilizada = Carreta;
	DescarregamentoAux.NumPlantaFornecedor = Planta;
	DescarregamentoAux.InicioDescarregamentos = inicio;
	DescarregamentoAux.FinalDescarregamentos = fim;
	DescarregamentoAux.FoiDeslocado = StatusDesalocamento;
	SituacaoDemanda[NumDemanda] = Situacao;

	Descarregamentos.insert(Descarregamentos.begin(), DescarregamentoAux );
	StatusAtendimento = StatusAtendimento + 1;

	OrdenaDescarregamentosEmOrdemCrescente();
	MarcaInicioFimDescarregamentos();
}

int Construcao::DeletaAtividade(double HoraInicio, double HoraFinal, int NumDemanda,  int Planta, int Carreta){

	for( vector < Descarregamento >::iterator it = Descarregamentos.begin(); it != Descarregamentos.end(); it++){
			if( it->HorarioInicioDescarregamento == HoraInicio){
				if( it->HorarioFinalDescarregamento == HoraFinal){
					if( it->NumeroDemandaSuprida == NumDemanda){
						if( it->NumPlantaFornecedor == Planta){
							if( it->NumCarretaUtilizada == Carreta){
								SituacaoDemanda[NumDemanda] = 0;
								StatusAtendimento = StatusAtendimento - 1;
								SituacaoRemocao[NumDemanda] = 0;
								Descarregamentos.erase(it);
								//cout << endl << endl << " ************* deletou " << Deslocamentos.size() << endl << endl ;
								return 1;
							}
						}
					}
				}
			}
		}
		cout << endl << endl << " ###########################   Problema! Não encontrou elemento Descarregamento [" << NumeroDaConstrucao << "-" << NumDemanda << "] a deletar !  -> Construcao::DeletaAtividade ################## " << endl << endl;
		return 0;
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

		if( menor == -13 || maior == -13 ){
			if( Descarregamentos.size() > 1){
				cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema na ordenacao -> Construcao::MarcaInicioFimDescarregamentos &&&&&&&&&&&&& " << endl << endl << endl;
			}
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

void Construcao::RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio){
	for( unsigned int d = 0; d < Descarregamentos.size(); d ++){
		if( NumDemanda == Descarregamentos[d].NumeroDemandaSuprida){
			HoraInicio = Descarregamentos[d].HorarioInicioDescarregamento;
		}
	}
}

void Construcao::RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& 	CaminhaoEmAnalise, int& ConstrucaoEmAnalise, int& DemandaDesalocada, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar){
	PlantaEmAnalise 		=	Descarregamentos[d].NumPlantaFornecedor;
	CaminhaoEmAnalise 		=	Descarregamentos[d].NumCarretaUtilizada;
	ConstrucaoEmAnalise 	= 	NumeroDaConstrucao;
	DemandaDesalocada 		= 	Descarregamentos[d].NumeroDemandaSuprida;
	HorarioInicioAuxiliar 	= 	Descarregamentos[d].HorarioInicioDescarregamento;
	HorarioFinalAuxiliar 	= 	Descarregamentos[d].HorarioFinalDescarregamento;
}

void Construcao::CalculaMakespan(){
	Makespan = 0 ;

	//cout << endl << endl << "  Contrucao " << NumeroDaConstrucao << endl;

	for( unsigned int d = 0; d < Descarregamentos.size(); d++){
		if( Descarregamentos[d].HorarioFinalDescarregamento  > Makespan){
			Makespan = Descarregamentos[d].HorarioFinalDescarregamento;
			//cout << " =-=-=-=-=-";
		}
	}
	//cout << "  " << Makespan ;
	for ( int i = 0; i < NumeroDemandas; i++){
		if( SituacaoDemanda[ i ] == 0 || SituacaoDemanda[ i ] == -1){
			Makespan = Makespan + 5 * TempoMaximoDeFuncionamento;
			cout << endl << endl << "  " << Makespan << " -> Inviolado construcao " << NumeroDaConstrucao << endl << endl;
		}
	}
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
	cout << "   MAKESPAN = " << Makespan << "   Status = " <<  StatusAtendimento << endl;
}


Construcao::~Construcao(){

}


class ConjuntoConstrucoes{

public:
	ConjuntoConstrucoes();
	vector< Construcao > Construcoes;
	int NumeroConstrucoes;

	vector < int > ConstrucaosAnalizadas;

	double MakespanConstrucoes;

	void InicializaConstrucaosAnalizadas();

	int NivelDeInviabilidade;
	void CalcularNivelDeInviabilidade();

	void OrdenaDescarregamentosConstrucoesOrdemCrescente();
	void  MarcaInicioFimDescarregamentosConstrucoes();

	void IniciaConjuntoConstrucoes(int);

	int DeletaTarefa(int, double, double, int, int, int);

	void ImprimeContrucoes();

	void VerificaIntervaloContrucoes();

	void CalculaMakespansConstrucoes();



	~ConjuntoConstrucoes();
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){
	NumeroConstrucoes = -13;
	NivelDeInviabilidade = -13;
	MakespanConstrucoes = -13;
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

int ConjuntoConstrucoes::DeletaTarefa(int NumConstrucao, double HoraInicio, double HoraFinal, int NumDemanda,  int Planta, int Carreta){
	int Retirou;
	Retirou = 0;

	for( unsigned int c = 0; c < Construcoes.size(); c++){
		if( Construcoes[c].NumeroDaConstrucao == NumConstrucao){
			Retirou = Construcoes[c].DeletaAtividade( HoraInicio, HoraFinal, NumDemanda, Planta, Carreta);
			if( Retirou == 1){
				NivelDeInviabilidade = NivelDeInviabilidade + 1;
				return 1;
			}else{
				cout << endl << endl << " ###########################   Problema! Não encontrou elemento descarregamento [" << NumConstrucao << "-" << NumDemanda << "] a deletar !  -> ConjuntoConstrucoes::DeletaTarefa ################## " << endl << endl;
				return 0;
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou construcao [" << NumConstrucao << "] a deletar !  -> ConjuntoConstrucoes::DeletaTarefa ################## " << endl << endl;
	return 0;
}

void ConjuntoConstrucoes::ImprimeContrucoes(){
	cout << endl << endl << " [[[[[[  Imprime construcoes  ]]]]]]" << endl;
	for(int c = 0; c < NumeroConstrucoes; c++){
		Construcoes[c].ImprimeContrucao();
	}

	cout << endl << " Nivel de Inviabilidade = " << NivelDeInviabilidade << "  Makespan Geral das Construcoes = "<< MakespanConstrucoes << endl;

}

void ConjuntoConstrucoes::VerificaIntervaloContrucoes(){

	cout << endl << " Status de respeito a intervelos de construção" << endl;
	for(int c = 0; c < NumeroConstrucoes; c++){
		if( Construcoes[c].VerificaDescarregamentosRespeitaIntervalo() == 1){
			cout << endl << Construcoes[c].NumeroDaConstrucao << " OK!";
		}else{
			cout << endl << Construcoes[c].NumeroDaConstrucao << " inviavel!";
		}
	}
	cout << endl ;
}

void ConjuntoConstrucoes::CalculaMakespansConstrucoes(){
	MakespanConstrucoes = 0;
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		Construcoes[c].CalculaMakespan();
		MakespanConstrucoes = MakespanConstrucoes + Construcoes[c].Makespan;
	}
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
