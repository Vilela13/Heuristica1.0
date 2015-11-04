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
	Descarregamento();
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	int NumCarretaUtilizada;
	int NumPlantaFornecedor;

	bool FoiDeslocado;

	int verifica( int, int, double, double);
	void AnulaConteudo();
	void Imprime();
};

Descarregamento::Descarregamento(){
	HorarioInicioDescarregamento = -13;
	HorarioFinalDescarregamento = -13;
	NumCarretaUtilizada = -13;
	NumPlantaFornecedor = -13;

	FoiDeslocado = 0;
}

int Descarregamento::verifica( int carreta, int planta, double HorarioInicio, double HorarioFinal){
	if( NumCarretaUtilizada == carreta &&  NumPlantaFornecedor ==  planta && HorarioInicioDescarregamento == HorarioInicio && HorarioFinalDescarregamento == HorarioFinal){
		return 1;
	}
	return 0;
}
void Descarregamento::AnulaConteudo(){
	HorarioInicioDescarregamento = -12;
	HorarioFinalDescarregamento = -12;
	NumCarretaUtilizada = -12;
	NumPlantaFornecedor = -12;

	FoiDeslocado = 0;
}

bool DecideQualDescarregamentoVemprimeiro ( Descarregamento d1, Descarregamento d2 ){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}

void Descarregamento::Imprime(){
	cout << " Planta = " << NumPlantaFornecedor;
	cout << " Carreta = " << NumCarretaUtilizada ;
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
	vector < int > SituacaoRemocao;			// SE o valor for 1 ela ja foi removida, se é 0 ela ainda não foi
	vector < DistanciaPlanta > DistanciaPlantas;
	double TempoMaximoEntreDescargas;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;
	double RankTempoDemandas;
	int StatusAtendimento;
	double Makespan;
	vector < Descarregamento > Descarregamentos;

	void CalculaRankTempoDemandas(int);
	int VerificaDisponibilidade( double, double);
	void AlocaAtividade(double, double, int, int, bool, int, ConjuntoPlantas&);
	int VerificaIterador( vector < Descarregamento >::iterator, double, double, int, int);
	int DeletaAtividadeLocomovendoAsOutrasTarefas(double, double, int, int, int, ConjuntoPlantas&);
	int VerificaDescarregamentosRespeitaIntervalo();
	void RetornaHorarioInicioCarregamento(  int, double&);
	void RetornaDadosDescarregamento( int, int&, int&, int&, double&, double&);
	void CalculaMakespan();
	void ImprimeContrucao();

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

	for( unsigned int d = 0; d < StatusAtendimento; d ++){
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
		for( unsigned int d = 0; d < StatusAtendimento; d ++){
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

void Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  bool StatusDesalocamento, int Situacao, ConjuntoPlantas& Plantas){


	// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! construcao [" << NumeroDaConstrucao << "] ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
	}

	// Verifica se tem uma tarefa já alocada atende a cosntrução depois desta
	int Encontrou;
	int NumDemanda;

	Encontrou = 0;
	NumDemanda = -13;

	for( int d = 0; d < StatusAtendimento; d++){
		if( Descarregamentos[d].HorarioInicioDescarregamento > HoraInicio && Encontrou == 0){
			NumDemanda = d;
			Encontrou = 1;
		}
	}


	// Caso tenha uma tarefa que atenda a construção depois dessa, ele faz a atualização das tarefas que atendem a construção após ela
	if( Encontrou == 1){

		for( int d = StatusAtendimento - 1; d >= NumDemanda ; d--){
			Plantas.CorrigeReferenciaCarregamentoDeslocamentoMaisUm( Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);

			Descarregamentos[ d + 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
			Descarregamentos[ d + 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
			Descarregamentos[ d + 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
			Descarregamentos[ d + 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
			Descarregamentos[ d + 1 ].FoiDeslocado = Descarregamentos[ d ].FoiDeslocado;
			SituacaoDemanda[ d + 1 ] = SituacaoDemanda[ d ];
			SituacaoRemocao[ d + 1 ] = SituacaoRemocao[ d ];
		}
	}else{
		NumDemanda = StatusAtendimento;
	}

	// Adiciona a tarefa
	Descarregamentos[NumDemanda].HorarioInicioDescarregamento = HoraInicio;
	Descarregamentos[NumDemanda].HorarioFinalDescarregamento = HoraFinal;
	Descarregamentos[NumDemanda].NumCarretaUtilizada = Carreta;
	Descarregamentos[NumDemanda].NumPlantaFornecedor = NumPlanta;
	Descarregamentos[NumDemanda].FoiDeslocado = StatusDesalocamento;
	SituacaoDemanda[NumDemanda] = Situacao;
	SituacaoRemocao[NumDemanda] = 0;

	// atualiza o status de atendimento
	StatusAtendimento = StatusAtendimento + 1;

// Adiciona a tarefa na Planta e no Caminhão
	int p;
	int v;

	// aloca indices para planta e veiculo
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0 || 	Plantas.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(Carreta,v) == 0){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Alocar indice planta [" << NumPlanta << "] => " << p << " ou veiculo [" << Carreta << "] => " << v << " ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
	}

	// aloca horarios
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HoraInicio - Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	HorarioInicioCarreta = HorarioInicioPlanta;
	HorarioFimCarreta = HoraFinal + Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao];

	// Aloca atividades no veiculo e depois na planta
	Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].AlocaAtividade( HorarioInicioCarreta, HorarioFimCarreta, NumeroDaConstrucao , NumDemanda);
	Plantas.Plantas[p].AlocaAtividade(HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao , NumDemanda,  Carreta);


}

int Construcao::VerificaIterador( vector < Descarregamento >::iterator it, double HoraInicio, double HoraFinal,   int NumPlanta, int Carreta){
	if( it->HorarioInicioDescarregamento == HoraInicio &&  it->HorarioFinalDescarregamento == HoraFinal && it->NumPlantaFornecedor == NumPlanta && it->NumCarretaUtilizada == Carreta){
		return 1;
	}else{
		return 0;
	}
}

int Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas){

	// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Demanda [" << NumDemanda << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
	}

	// Verifica se tem uma tarefa já alocada atende a cosntrução depois desta
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

		// Deleta tarefa
		int p;
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
		}

		// aloca horarios
		double HorarioInicioPlanta;
		double HorarioFimPlanta;

		HorarioInicioPlanta = HoraInicio - Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
		HorarioFimPlanta = HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

		double HorarioInicioCarreta;
		double HorarioFimCarreta;

		HorarioInicioCarreta = HorarioInicioPlanta;
		HorarioFimCarreta = HoraFinal + Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao];

		/*
		cout << endl << endl << "  Dados tarefa " << endl << endl;

		cout << "  contrucao [" << NumeroDaConstrucao << "-" << NumDemanda << "] as " <<  HoraInicio << " até " << HoraFinal << endl;
		cout << "  planta [" << NumPlanta << "] as " << HorarioInicioPlanta << " até " << HorarioFimPlanta << endl;
		cout << "  carreta [" << Carreta << "] as " << HorarioInicioCarreta  << " até " << HorarioFimCarreta << endl << endl;
		 */


// Deleta tarefa na planta e no caminhão
		Plantas.DeletaTarefa( NumPlanta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, NumDemanda, Carreta, HorarioInicioCarreta, HorarioFimCarreta);


		// Reorganiza Tarefas
		for( int d = NumDemanda + 1; d < StatusAtendimento; d++){
			Plantas.CorrigeReferenciaCarregamentoDeslocamentoMenosUm(Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
			Descarregamentos[ d - 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
			Descarregamentos[ d - 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
			Descarregamentos[ d - 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
			Descarregamentos[ d - 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
			Descarregamentos[ d - 1 ].FoiDeslocado = Descarregamentos[ d ].FoiDeslocado;
			SituacaoDemanda[ d - 1 ] = SituacaoDemanda[ d ];
			SituacaoRemocao[ d - 1 ] = SituacaoRemocao[ d ];
		}

		// atualiza dados da tarefa deletada
		Descarregamentos[ StatusAtendimento - 1].AnulaConteudo();
		SituacaoDemanda[StatusAtendimento - 1] = 0;
		SituacaoRemocao[StatusAtendimento - 1] = 0;

		StatusAtendimento = StatusAtendimento - 1;

	}else{
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Planta [" << NumPlanta << "], Carreta [" << Carreta << "]";
		cout << ", HoraInicio [" << HoraInicio << "],HoraFinal [" << HoraFinal << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
	}



}
/*
void Construcao::OrdenaDescarregamentosEmOrdemCrescente(){
	sort (Descarregamentos.begin(), Descarregamentos.end(), DecideQualDescarregamentoVemprimeiro);
}
*/


int Construcao::VerificaDescarregamentosRespeitaIntervalo(){
	cout << endl << endl << "  Reimplementar -> Construcao::VerificaDescarregamentosRespeitaIntervalo()" << endl << endl;
}

void Construcao::RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio){
	for( unsigned int d = 0; d < Descarregamentos.size(); d ++){
		if( NumDemanda == d){
			HoraInicio = Descarregamentos[d].HorarioInicioDescarregamento;
		}
	}
}

void Construcao::RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& 	CaminhaoEmAnalise, int& ConstrucaoEmAnalise, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar){

	PlantaEmAnalise 		=	Descarregamentos[d].NumPlantaFornecedor;
	CaminhaoEmAnalise 		=	Descarregamentos[d].NumCarretaUtilizada;
	ConstrucaoEmAnalise 	= 	NumeroDaConstrucao;
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
			cout << "] atende demanda " << NumeroDaConstrucao << "-" << d;
			cout << " de ( " << Descarregamentos[d].HorarioInicioDescarregamento;
			cout << " as " << Descarregamentos[d].HorarioFinalDescarregamento  << " ) " << endl;
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
	int NivelDeInviabilidade;

	void InicializaConstrucaosAnalizadas();
	void CalcularNivelDeInviabilidade();
	void IniciaConjuntoConstrucoes(int);
	int DeletaTarefa(int, double, double, int, int, int, ConjuntoPlantas&);
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

void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	Construcoes.resize(Numero);
	NumeroConstrucoes = Numero;

}

int ConjuntoConstrucoes::DeletaTarefa(int NumConstrucao, double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas){
	cout << endl << endl << " >>>>>>>>>  reimplementar -> ConjuntoConstrucoes::DeletaTarefa " << endl << endl;

	/*
	int Retirou;
	Retirou = 0;

	for( unsigned int c = 0; c < Construcoes.size(); c++){
		if( Construcoes[c].NumeroDaConstrucao == NumConstrucao){
			Retirou = Construcoes[c].DeletaAtividadeLocomovendoAsOutrasTarefas( HoraInicio, HoraFinal, NumDemanda, NumPlanta, Carreta, Plantas);
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

	*/
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
