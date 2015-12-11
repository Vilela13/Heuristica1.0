/*
 * Construcoes.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CONSTRUCOES_HPP_
#define CONSTRUCOES_HPP_



#include "Bibliotecas.hpp"
#include "FuncoesSolucoes.hpp"

class Descarregamento{
public:
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	int NumCarretaUtilizada;
	int NumPlantaFornecedor;

	Descarregamento();	// construtora
	int verifica( int carreta, int planta, double HorarioInicio, double HorarioFinal);			// verifica se os dados passados se referem ao descarregamento
	void AnulaConteudo();			// anula o consteudo do descarregamento retornando ao estado original
	void Imprime();				// imprime o conteudo dos descarregamento
};

// construtora
Descarregamento::Descarregamento(){
	HorarioInicioDescarregamento = -13;
	HorarioFinalDescarregamento = -13;
	NumCarretaUtilizada = -13;
	NumPlantaFornecedor = -13;

}

// verifica se os dados passados se referem ao descarregamento
int Descarregamento::verifica( int carreta, int planta, double HorarioInicio, double HorarioFinal){
	// verifica se os dados passados são os memos que os do descarregamento
	if( NumCarretaUtilizada == carreta &&  NumPlantaFornecedor ==  planta && HorarioInicioDescarregamento == HorarioInicio && HorarioFinalDescarregamento == HorarioFinal){
		return 1;
	}
	return 0;
}

// anula o consteudo do descarregamento retornando ao estado original
void Descarregamento::AnulaConteudo(){
	HorarioInicioDescarregamento = -12;
	HorarioFinalDescarregamento = -12;
	NumCarretaUtilizada = -12;
	NumPlantaFornecedor = -12;
}

// imprime o conteudo dos descarregamento
void Descarregamento::Imprime(){
	printf ("  Planta = %d Carreta = %d Tempo[%.4f - %.4f]\n", NumPlantaFornecedor, NumCarretaUtilizada, HorarioInicioDescarregamento, HorarioFinalDescarregamento);
}

//
bool DecideQualDescarregamentoVemPrimeiro ( Descarregamento d1, Descarregamento d2 );

bool DecideQualDescarregamentoVemPrimeiro ( Descarregamento d1, Descarregamento d2 ){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}

// classe que foi criada para guardar a distancia da construção para a planta e manter um ponteiro para a estrutura dessa planta
class DistanciaPlanta{
public:
	double Distancia;
	Planta* PlantaComparada;
};


class Construcao{

public:
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
	vector < Descarregamento > Descarregamentos;
	double Makespan;

	Construcao();
	void CalculaRankTempoDemandas(int comentarios);					// Calcula o rank que decide qual construção será atendida inicialmente
	int VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao);				// Verifica se da para colocar a demanda na construção, ela sinaliza se caso atrazar as demandas sejá possivel alocar a demanda.
	int AlocaAtividade(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas);		// Aloca uma demanda na cosntrução apartir de dados

	void AlocaAtividadeSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int Carreta, int NumPlanta, int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidas);			// Aloca uma demanda na cosntrução apartir de dados, dalvando os dados da demanda alocada em estrutura DadosAdicionado
	int DeletaAtividadeLocomovendoAsOutrasTarefas(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas);				// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos
	int DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar);			// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos, salvando os dados da tarefa removida em uma estrutura

	int DeletaTodasAtividadesDaContrucaoSalvandoDados(int VerificaExistencia, double &HoraInicio, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosRetirandoAux);				// deleta todas as atividades de uma construção. Salvando atividades em estrutura

	int DeletaTarefas( int VerificaExistencia, int demanda, vector < DadosTarefa > &DadosRetirando, ConjuntoPlantas& Plantas);			// Deleta tarefas da demanda passada e as posteriores a esta demanda passada
	int DeletaTarefasAnteriormenteAdicionadasDados(   DadosTarefa DadosAdicionados, ConjuntoPlantas& Plantas);		// deleta tarefa apartir de dados
	int VerificaDescarregamentosRespeitaIntervalo();			// Verifica se os descrarregamentor na construção estão respeitando os intervalos entre elas

	void RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio);				// retorna o horario de inicio de um certo descarregamento na construção
	void RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& CaminhaoEmAnalise, int& ConstrucaoEmAnalise, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar);		// Retorna os dados de um certo descarregamento
	void CalculaMakespan();			// Calcula o Makespan da construção

	void ImprimeContrucao();		// Imprime os dados da construções

	int AtrazaDemandasParaAtenderMaster( int NumDemanda, double HoraInicioAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao, ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int TipoOrdenacao, int imprime, string frase);		// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe a demanda não alocada ainda

	int AtrazaDemandasParaAtenderRecursao( int NumDemanda, double HoraInicioAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int TipoOrdenacao,int imprime, string frase);
	void EncontraPlantaComMenorDistanciaParaConstrucao(  int& NumPlantaAnalisando, ConjuntoPlantas& Plantas, string frase);					// encontra a planta mais perto da construção e que não tenha sido analisada antes
	int AlocaAtividadeComHorarioInicio( int NumDemanda, double HoraFimAtendiemnto, double &NovaHoraFimAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao,ConjuntoPlantas& Plantas, int TipoOrdenacao , string frase);

	int VerificaIntegridadeDeDescrregamentos(int imprime);			// verifica a integridade entre os descarregamentos da construção

	~Construcao();

};

Construcao::Construcao(){
	NumeroDaConstrucao = -13;
	NumeroDemandas = -13;
	SituacaoDemanda.clear();
	SituacaoRemocao.clear();
	TempoMaximoEntreDescargas = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	RankTempoDemandas = -13;
	StatusAtendimento = 0;
	Descarregamentos.clear();
	Makespan = -13;
}

// Calcula o rank que decide qual construção será atendida inicialmente
void Construcao::CalculaRankTempoDemandas(int comentarios){
	RankTempoDemandas = ( TempoMaximoDeFuncionamento - TempoMinimoDeFuncionamento) / NumeroDemandas ;
	if( comentarios == 1){
		printf( " Rank ( Tempo / Demandas ) = %.4f\n",RankTempoDemandas);
	}
}

// Verifica se da para colocar a demanda na construção, ela sinaliza se caso atrazar as demandas sejá possivel alocar a demanda.
int Construcao::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	int PossuiTarefaAnterior;
	int PossuiTarefaPosterior;

	PossuiTarefaAnterior = 0;
	PossuiTarefaPosterior = 0;

	//int ParaPrograma;

	// verifica se respeita os intervalos de funcionamento da construção
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	// Verifica se a alocação da demanda irá violar a integridade do atendimento dos outros atendimentos
	for( int d = 0; d < StatusAtendimento; d ++){
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

	// se não tem nenhuma demanda atendida, se aloca a demanda
	if( StatusAtendimento == 0) {
		return 1;
	}else{
// verifica a situação dessa demanda com as outras demandas

		// percorre todas as demandas atendidas nesta construção
		for( int d = 0; d < StatusAtendimento; d ++){
			// Verifica se tem demanda alocada  antes dessa tarefa
			if( Descarregamentos[d].HorarioFinalDescarregamento <= InicioPossivelAlocacao && InicioPossivelAlocacao <= Descarregamentos[d].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
				PossuiTarefaAnterior = 1;
			}
			// Verifica se tem demanda alocada depois da alocação dessa tarefa
			if( FinalPossivelAlocacao <=  Descarregamentos[d].HorarioInicioDescarregamento &&  Descarregamentos[d].HorarioInicioDescarregamento   <= FinalPossivelAlocacao + TempoMaximoEntreDescargas ){
				PossuiTarefaPosterior = 1;
			}
		}

// Sinaliza a possição dessa tarefa

		// Entra depois de todas as tarefas alocadas
		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 0){
			return 1;
		}

		// Entra no meio de duas tarefas alocadas
		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 1){
			cout << endl << endl << " No meio das tarefas ->Construcao::VerificaDisponibilidade  " << endl << endl << endl;
			return 2;
		}

		// Entra antes de todas as tarefas alocadas
		if ( PossuiTarefaAnterior == 0 && PossuiTarefaPosterior == 1){
			return 3;
		}

		// Caso não respeita o intervalo de tempo necessario entre um descarregamento e outro semdo que ela seria colocada depois das outras demandas já alocadas.
		int TemTarefaAntes;
		TemTarefaAntes = 1;

		for( int d = 0; d < StatusAtendimento; d ++){
			if( Descarregamentos[d].HorarioFinalDescarregamento > InicioPossivelAlocacao ){
				TemTarefaAntes = 0;
			}
		}

		// Não se pode colocar a demanda pelo fato dela não respeitar o intervalo de atendimento, mas caso se atraze as demandas ela seria alocadac
		if( TemTarefaAntes == 1){
			return -2;
		}

		// Caso não seja possivel alocar a demanda e ela não está em nenhum dos casos acima.
		return -1;
	}
}

// Aloca uma demanda na cosntrução apartir de dados
int Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas){


// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! construcao [" << NumeroDaConstrucao << "] ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
		return 0;
	}

// Verifica se tem uma tarefa já alocada  e que atende a cosntrução em um horario depois desta
	int Encontrou;
	int NumDemanda;

	Encontrou = 0;
	NumDemanda = -13;

	// passa por todas as demanda já atendidas
	for( int d = 0; d < StatusAtendimento; d++){
		// caso se tenha uma demanda atendida após o horario passado
		if( Descarregamentos[d].HorarioInicioDescarregamento > HoraInicio && Encontrou == 0){
			// numero da demanda que se esta adicionando caso se tenha demandas atendidas apos o horario passado na função
			NumDemanda = d;
			// assinala que encontrou uma demanda que é atendida depois da que se quer atender
			Encontrou = 1;
		}
	}

	// Caso tenha tarefas que atendam a construção depois dessa, ele faz a atualização dos dados dessas tarefas
	if( Encontrou == 1 ){
		// passa por todas as demandas até a primeira demanda atendida após a que se quer colocar
		for( int d = StatusAtendimento - 1; d >= NumDemanda ; d--){
			// correige as referencias do atendimento da demanda corrente tanto na planta e no caminhão
			Plantas.CorrigeReferenciaCarregamentoDeslocamentoMaisUm( Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
			// atualiza os dados do descarregamento
			Descarregamentos[ d + 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
			Descarregamentos[ d + 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
			Descarregamentos[ d + 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
			Descarregamentos[ d + 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
			SituacaoDemanda[ d + 1 ] = SituacaoDemanda[ d ];
			SituacaoRemocao[ d + 1 ] = SituacaoRemocao[ d ];
		}
	}else{
		// caso não for, o numero da demanda é o numero da ultima demanda a se atender
		NumDemanda = StatusAtendimento;
	}

// Adiciona a tarefa
	Descarregamentos[NumDemanda].HorarioInicioDescarregamento = HoraInicio;
	Descarregamentos[NumDemanda].HorarioFinalDescarregamento = HoraFinal;
	Descarregamentos[NumDemanda].NumCarretaUtilizada = Carreta;
	Descarregamentos[NumDemanda].NumPlantaFornecedor = NumPlanta;
	SituacaoDemanda[NumDemanda] = Situacao;
	SituacaoRemocao[NumDemanda] = StatusRemocao;

// atualiza o status de atendimento
	StatusAtendimento = StatusAtendimento + 1;

// Adiciona a tarefa na Planta e no Caminhão
	int p;
	int v;

// aloca indices para planta e veiculo
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0 || 	Plantas.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(Carreta,v) == 0){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Alocar indice planta [" << NumPlanta << "] => " << p << " ou veiculo [" << Carreta << "] => " << v << " ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
		return 0;
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

	return 1;
}

// Aloca uma demanda na cosntrução apartir de dados, dalvando os dados da demanda alocada em estrutura DadosAdicionado
void Construcao::AlocaAtividadeSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int Carreta, int NumPlanta, int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidas){

// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! construcao [" << NumeroDaConstrucao << "] ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
	}

// Verifica se tem uma tarefa já alocada  e que atende a cosntrução em um horario depois desta
	int Encontrou;
	int NumDemanda;

	Encontrou = 0;
	NumDemanda = -13;

	// passa por todas as demanda já atendidas
	for( int d = 0; d < StatusAtendimento; d++){
		// caso se tenha uma demanda atendida após o horario passado
		if( Descarregamentos[d].HorarioInicioDescarregamento > HoraInicio && Encontrou == 0){
			// numero da demanda que se esta adicionando caso se tenha demandas atendidas apos o horario passado na função
			NumDemanda = d;
			// assinala que encontrou uma demanda que é atendida depois da que se quer atender
			Encontrou = 1;
		}
	}

// Caso tenha tarefas que atendam a construção depois dessa, ele faz a atualização dos dados dessas tarefas
	if( Encontrou == 1){
		// passa por todas as demandas até a primeira demanda atendida após a que se quer colocar
		for( int d = StatusAtendimento - 1; d >= NumDemanda ; d--){
			// correige as referencias do atendimento da demanda corrente tanto na planta e no caminhão
			Plantas.CorrigeReferenciaCarregamentoDeslocamentoMaisUm( Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
			// atualiza os dados do descarregamento
			Descarregamentos[ d + 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
			Descarregamentos[ d + 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
			Descarregamentos[ d + 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
			Descarregamentos[ d + 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
			SituacaoDemanda[ d + 1 ] = SituacaoDemanda[ d ];
			SituacaoRemocao[ d + 1 ] = SituacaoRemocao[ d ];
		}
	}else{
		// caso não for, o numero da demanda é o numero da ultima demanda a se atender
		NumDemanda = StatusAtendimento;
	}

// Adiciona a tarefa
	Descarregamentos[NumDemanda].HorarioInicioDescarregamento = HoraInicio;
	Descarregamentos[NumDemanda].HorarioFinalDescarregamento = HoraFinal;
	Descarregamentos[NumDemanda].NumCarretaUtilizada = Carreta;
	Descarregamentos[NumDemanda].NumPlantaFornecedor = NumPlanta;
	SituacaoDemanda[NumDemanda] = Situacao;
	SituacaoRemocao[NumDemanda] = StatusRemocao;

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

// salva os dados da demanda que está sendo adicionada em estrutura DadosAdiciona
	if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosTarefasMovidas,NumeroDaConstrucao, NumPlanta, Carreta,  Situacao, StatusRemocao, HorarioInicioPlanta, HorarioFimPlanta, HoraInicio, HoraFinal, HorarioFimCarreta, 'a')  == 0 ){
		cout << endl << endl << " Problema em adicionar tarefa a vetor de tarefas desalocadas -> Construcao::AlocaAtividadeSalvandoDados" << endl << endl;
	}
}

// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos
int Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas){

// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Demanda [" << NumDemanda << "] não existe ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas>>>>>>>>>> " << endl << endl;
		return 0;
	}

// Verifica se existe a tarefa a ser deletada com os dados passados
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

// Deleta tarefa
		int p;
		// encontra o inidice da planta
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas>>>>>>>>>> " << endl << endl;
			return 0;
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

		// se a demanda a ser deletada não é a ultima alocada na cosntrução
		if( NumDemanda != StatusAtendimento - 1){
			// caso não for, percorre todas as demandas após a que se quer deletar e corrige as suas referencias
			for( int d = NumDemanda + 1; d < StatusAtendimento; d++){
				// corrige as referencias da planta e dao caminhão
				Plantas.CorrigeReferenciaCarregamentoDeslocamentoMenosUm(Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
				// corrige as referencias do descarregamento
				Descarregamentos[ d - 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
				Descarregamentos[ d - 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
				Descarregamentos[ d - 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
				Descarregamentos[ d - 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
				SituacaoDemanda[ d - 1 ] = SituacaoDemanda[ d ];
				SituacaoRemocao[ d - 1 ] = SituacaoRemocao[ d ];
			}
		}

// atualiza dados da tarefa deletada
		Descarregamentos[ StatusAtendimento - 1].AnulaConteudo();
		SituacaoDemanda[StatusAtendimento - 1] = 0;
		SituacaoRemocao[StatusAtendimento - 1] = 0;

		// atualiza o numero de demandas atendidas
		StatusAtendimento = StatusAtendimento - 1;

	}else{
		//caso não encontrou o descarregamento, se escreve os dados dele e retorna 0
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Planta [" << NumPlanta << "], Carreta [" << Carreta << "]";
		cout << ", HoraInicio [" << HoraInicio << "],HoraFinal [" << HoraFinal << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas>>>>>>>>>> " << endl << endl;
		return 0;
	}
	return 1;

}

// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos, salvando os dados da tarefa removida em uma estrutura
int Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar){

// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Demanda [" << NumDemanda << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados>>>>>>>>>> " << endl << endl;
		return 0;
	}

	// Verifica se existe a tarefa a ser deletada com os dados passados
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

// Deleta tarefa
		int p;
		// encontra o inidice da planta
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados>>>>>>>>>> " << endl << endl;
			return 0;
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

// Armazena tarefa deletada
		if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosTarefasMovidasAuxiliar, NumeroDaConstrucao, NumPlanta, Carreta, SituacaoDemanda[NumDemanda], SituacaoRemocao[NumDemanda],  HorarioInicioPlanta, HorarioFimPlanta, HoraInicio, HoraFinal, HorarioFimCarreta, 'r') == 0 ){
			cout << endl << endl << " Erro! - Problema em adicionar tarefa a vetor de tarefas desalocadas -> Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados" << endl << endl;
			return 0;
		}

// Deleta tarefa na planta e no caminhão
		Plantas.DeletaTarefa( NumPlanta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, NumDemanda, Carreta, HorarioInicioCarreta, HorarioFimCarreta);

// Reorganiza Tarefas

		// se a demanda a ser deletada não é a ultima alocada na cosntrução
		if( NumDemanda != StatusAtendimento - 1){
			// caso não for, percorre todas as demandas após a que se quer deletar e corrige as suas referencias
			for( int d = NumDemanda + 1; d < StatusAtendimento; d++){
				// corrige as referencias da planta e dao caminhão
				Plantas.CorrigeReferenciaCarregamentoDeslocamentoMenosUm(Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
				// corrige as referencias do descarregamento
				Descarregamentos[ d - 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
				Descarregamentos[ d - 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
				Descarregamentos[ d - 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
				Descarregamentos[ d - 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
				SituacaoDemanda[ d - 1 ] = SituacaoDemanda[ d ];
				SituacaoRemocao[ d - 1 ] = SituacaoRemocao[ d ];
			}
		}

// atualiza dados da tarefa deletada
		Descarregamentos[ StatusAtendimento - 1].AnulaConteudo();
		SituacaoDemanda[StatusAtendimento - 1] = 0;
		SituacaoRemocao[StatusAtendimento - 1] = 0;

		// atualiza o numero de demandas atendidas
		StatusAtendimento = StatusAtendimento - 1;

	}else{
		//caso não encontrou o descarregamento, se escreve os dados dele e retorna 0
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Planta [" << NumPlanta << "], Carreta [" << Carreta << "]";
		cout << ", HoraInicio [" << HoraInicio << "],HoraFinal [" << HoraFinal << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados>>>>>>>>>> " << endl << endl;
		return 0;
	}
	return 1;
}


// deleta todas as atividades de uma construção. Salvando atividades em estrutura
int Construcao::DeletaTodasAtividadesDaContrucaoSalvandoDados(int VerificaExistencia, double &HoraInicio, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosRetirandoAux){

	int p;
	int Carreta;

	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	double HorarioInicioCarreta;
	double HorarioFimCarreta;

// verifica se construção tem alguma demanda atendida
	if( StatusAtendimento > 0){

		// pega o horario da primeira tarefa na construção
		HoraInicio = Descarregamentos[0].HorarioInicioDescarregamento;

		// percorre todas as descargas da cosntrução
		for( int d = 0; d < StatusAtendimento; d++){
			// encontra o indice da fabrica
			if( Plantas.AlocaInidiceFabrica( Descarregamentos[d].NumPlantaFornecedor, p) == 0) {
				cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << Descarregamentos[d].NumPlantaFornecedor << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
				return 0;
			}

			HorarioInicioPlanta = Descarregamentos[d].HorarioInicioDescarregamento - Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
			HorarioFimPlanta = HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

			HorarioInicioCarreta = HorarioInicioPlanta;
			HorarioFimCarreta = Descarregamentos[d].HorarioFinalDescarregamento + Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao];

			Carreta = Descarregamentos[d].NumCarretaUtilizada;

			// salva dados da tarefa a retirar
			if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosRetirandoAux, NumeroDaConstrucao, Descarregamentos[d].NumPlantaFornecedor, Carreta, SituacaoDemanda[d], SituacaoRemocao[d], HorarioInicioPlanta, HorarioFimPlanta, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento, HorarioFimCarreta, 'r') == 0 ){
				cout << endl << endl << " Problema em adicionar tarefa a vetor de tarefas desalocadas -> Construcao::DeletaTodasAtividadesDaContrucaoSalvandoDados" << endl << endl;
			}

			// deleta tarefa tanto na planta e nao caminhão
			Plantas.DeletaTarefa( Descarregamentos[d].NumPlantaFornecedor, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, d, Carreta, HorarioInicioCarreta, HorarioFimCarreta);
			// anula o conteudo do descarregamento corrente
			Descarregamentos[ d ].AnulaConteudo();
			SituacaoDemanda[ d ] = 0;
			SituacaoRemocao[ d ] = 0;

		}
		// faz o status artendimento ser 0, com nenhuma demanda atendida
		StatusAtendimento = 0;
		return 1;
	}
	cout << endl << endl << "    <<<<<<<<<<<<<<<< Não possui descarregaembtos -> Construcao::DeletaTodasAtividadesDaContrucaoSalvandoDados " << endl << endl;
	return 0;
}


// Deleta tarefas da demanda passada e as posteriores a esta demanda passada
int Construcao::DeletaTarefas(int VerificaExistencia, int demanda, vector < DadosTarefa > &DadosTarefasMovidas, ConjuntoPlantas& Plantas){
	double HorarioInicioConstrucao;
	double HorarioFinalConstrucao;

	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	int Planta;
	int Carreta;

	int p;
	int DemandasRetiradas;

	DemandasRetiradas = 0;		// inicializa o contador de tarefas retiradas com zero

// verifica se a demanda que se quer tirar está alocada na construção
	if( StatusAtendimento - 1 < demanda){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Demanda [" << demanda << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
		return 0;
	}

// se retira as tarefas da demanda que se quer e as posteriores a ela

	// se percorre todas as demandas apos a demanda passada, incluindo a demanda passada
	for( int d = demanda; d < StatusAtendimento; d++){
		Planta = Descarregamentos[d].NumPlantaFornecedor;
		// se pega o inidice da planta
		if( Plantas.AlocaInidiceFabrica( Planta, p) == 0) {
			cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << Planta << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
			return 0;
		}

		Carreta = Descarregamentos[d].NumCarretaUtilizada;

		HorarioInicioConstrucao = Descarregamentos[d].HorarioInicioDescarregamento;
		HorarioFinalConstrucao = Descarregamentos[d].HorarioFinalDescarregamento;

	// aloca horarios
		HorarioInicioPlanta = HorarioInicioConstrucao - Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
		HorarioFimPlanta = HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

		HorarioInicioCarreta = HorarioInicioPlanta;
		HorarioFimCarreta = HorarioFinalConstrucao + Plantas.Plantas[p].DistanciaConstrucoes[NumeroDaConstrucao];

		/*
		cout << endl << endl << "  Dados tarefa " << endl << endl;

		cout << "  contrucao [" << NumeroDaConstrucao << "-" << NumDemanda << "] as " <<  HoraInicio << " até " << HoraFinal << endl;
		cout << "  planta [" << NumPlanta << "] as " << HorarioInicioPlanta << " até " << HorarioFimPlanta << endl;
		cout << "  carreta [" << Carreta << "] as " << HorarioInicioCarreta  << " até " << HorarioFimCarreta << endl << endl;
		 */

		// Adiciona na estrutura a terefa retirada
		if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosTarefasMovidas,NumeroDaConstrucao, Planta, Carreta, SituacaoDemanda[d], SituacaoRemocao[d], HorarioInicioPlanta, HorarioFimPlanta,HorarioInicioConstrucao, HorarioFinalConstrucao, HorarioFimCarreta, 'r') == 0 ){
			cout << endl << endl << " Problema em adicionar tarefa a vetor de tarefas desalocadas -> Construcao::DeletaTarefas" << endl << endl;
			return 0;
		}

		// Deleta tarefa na planta e no caminhão
		Plantas.DeletaTarefa( Planta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, d, Carreta, HorarioInicioCarreta, HorarioFimCarreta);
		// Deleta tarefa na construção
		Descarregamentos[d].AnulaConteudo();
		SituacaoDemanda[d] = 0;
		SituacaoRemocao[d] = 0;

		// aumenta o contador das tarefas deletadas
		DemandasRetiradas++;
	}

	// atualiza o nivel de atendimento com o número de demandas atendidas na planta
	StatusAtendimento = StatusAtendimento - DemandasRetiradas;
	return 1;

}

// deleta tarefa apartir de dados
int Construcao::DeletaTarefasAnteriormenteAdicionadasDados(   DadosTarefa DadosAdicionados, ConjuntoPlantas& Plantas){
	int demanda;
	int ativo;
	ativo = 0;

// verifica se a tarefa existe na cosntrução

	// percorre todas as descargas existentes na construção
	for( int d = 0; d < StatusAtendimento; d++){
		// verifica se os dados da estrutura passada batem com algum descarregamento
		if( Descarregamentos[d].HorarioInicioDescarregamento == DadosAdicionados.HorariosDasTarefas[2] &&  Descarregamentos[d].HorarioFinalDescarregamento == DadosAdicionados.HorariosDasTarefas[3]){
			// verifica se os horarios da estrutura batem com algum descarregamento
			if( NumeroDaConstrucao == DadosAdicionados.DadosDasTarefas[0] && Descarregamentos[d].NumPlantaFornecedor == DadosAdicionados.DadosDasTarefas[1] &&  Descarregamentos[d].NumCarretaUtilizada == DadosAdicionados.DadosDasTarefas[2] ){
				// guarda a demanda
				demanda = d;
				// marca como encontrada a demanda atendida
				ativo = 1;
			}
		}
	}

	// caso não enconstrar a demanda, retorna 0 e escreve na tela
	if( ativo == 0 ){
		cout << endl << endl << "  				<<<<<<<< Probelma em deletar tarefa. Não encontrou tarefa -> Construcao::DeletaTarefasAnteriormenteAdicionadasDados" << endl;
		DadosAdicionados.Imprimir();
		cout << endl << endl;
		return 0;
	}

	// coleta dasdos da tarefa
	int NumPlanta;
	int Carreta;

	NumPlanta = DadosAdicionados.DadosDasTarefas[1];
	Carreta = DadosAdicionados.DadosDasTarefas[2];

	// Deleta tarefa
	int p;
	// pega o inidice da planta
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
		return 0;
	}

	// aloca horarios
	double HorarioInicioPlanta;
	double HorarioFimPlanta;
	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	HorarioInicioPlanta = DadosAdicionados.HorariosDasTarefas[0];
	HorarioFimPlanta = DadosAdicionados.HorariosDasTarefas[1];
	HorarioInicioCarreta = DadosAdicionados.HorariosDasTarefas[0];
	HorarioFimCarreta = DadosAdicionados.HorariosDasTarefas[4];


		/*
		cout << endl << endl << "  Dados tarefa " << endl << endl;

		cout << "  contrucao [" << NumeroDaConstrucao << "-" << NumDemanda << "] as " <<  HoraInicio << " até " << HoraFinal << endl;
		cout << "  planta [" << NumPlanta << "] as " << HorarioInicioPlanta << " até " << HorarioFimPlanta << endl;
		cout << "  carreta [" << Carreta << "] as " << HorarioInicioCarreta  << " até " << HorarioFimCarreta << endl << endl;
		 */


	// Deleta tarefa na planta e no caminhão
	Plantas.DeletaTarefa( NumPlanta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, demanda, Carreta, HorarioInicioCarreta, HorarioFimCarreta);


// Reorganiza Tarefas

	// se a demanda a ser deletada não é a ultima alocada na cosntrução
	if( demanda != StatusAtendimento - 1){
		// caso não for, percorre todas as demandas após a que se quer deletar e corrige as suas referencias
		for( int d = demanda + 1; d < StatusAtendimento; d++){
			// corrige as referencias da planta e dao caminhão
			Plantas.CorrigeReferenciaCarregamentoDeslocamentoMenosUm(Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
			// corrige as referencias do descarregamento
			Descarregamentos[ d - 1 ].HorarioInicioDescarregamento = Descarregamentos[ d ].HorarioInicioDescarregamento;
			Descarregamentos[ d - 1 ].HorarioFinalDescarregamento = Descarregamentos[ d ].HorarioFinalDescarregamento;
			Descarregamentos[ d - 1 ].NumCarretaUtilizada = Descarregamentos[ d ].NumCarretaUtilizada;
			Descarregamentos[ d - 1 ].NumPlantaFornecedor = Descarregamentos[ d ].NumPlantaFornecedor;
			SituacaoDemanda[ d - 1 ] = SituacaoDemanda[ d ];
			SituacaoRemocao[ d - 1 ] = SituacaoRemocao[ d ];
		}
	}

	// atualiza dados da tarefa deletada
	Descarregamentos[ StatusAtendimento - 1].AnulaConteudo();
	SituacaoDemanda[StatusAtendimento - 1] = 0;
	SituacaoRemocao[StatusAtendimento - 1] = 0;

	// atualiza o nivel de atendimento
	StatusAtendimento = StatusAtendimento - 1;


	return 1;

}

// Verifica se os descrarregamentor na construção estão respeitando os intervalos entre elas
int Construcao::VerificaDescarregamentosRespeitaIntervalo(){
	// caso existir mais de uma tarefa
	if( StatusAtendimento > 1){
		// percorre todas as tarefas apos a primeira
		for( int d = 1; d < StatusAtendimento; d++){
			// verifica se o intervalo é respeitado
			if( Descarregamentos[d].HorarioInicioDescarregamento - Descarregamentos[d -1].HorarioFinalDescarregamento > TempoMaximoEntreDescargas){
				return 0;
			}
		}
	}
	return 1;
}

// retorna o horario de inicio de um certo descarregamento na construção
void Construcao::RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio){
	int ativa;

	ativa = 0;

	// percorre todos os descarregamento
	for( unsigned int d = 0; d < Descarregamentos.size(); d++){
		// verifica se a demanda é a passada na função
		if( NumDemanda == d){
			// retorna o horario do descarregameto da demanda
			HoraInicio = Descarregamentos[d].HorarioInicioDescarregamento;
			// marca que encontrou a demanda procurada
			ativa = 1;
		}
	}

	// escreve na tela caso não se encontrou a demanda procurada
	if( ativa == 0){
		cout << endl << endl <<  " <<<<<<<<<<<<<<<< Erro! Não encontrou a demanda [" << NumDemanda << "] -> Construcao::RetornaHorarioInicioCarregamento >>>>>>>>>>>>>>>>>>>>>> " << endl << endl;
	}
}

// Retorna os dados de um certo descarregamento
void Construcao::RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& 	CaminhaoEmAnalise, int& ConstrucaoEmAnalise, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar){

	PlantaEmAnalise 		=	Descarregamentos[d].NumPlantaFornecedor;
	CaminhaoEmAnalise 		=	Descarregamentos[d].NumCarretaUtilizada;
	ConstrucaoEmAnalise 	= 	NumeroDaConstrucao;
	HorarioInicioAuxiliar 	= 	Descarregamentos[d].HorarioInicioDescarregamento;
	HorarioFinalAuxiliar 	= 	Descarregamentos[d].HorarioFinalDescarregamento;
}

// Calcula o Makespan da construção
void Construcao::CalculaMakespan(){
	Makespan = 0 ;

	//cout << endl << endl << "  Contrucao " << NumeroDaConstrucao << endl;

	// passa por todos os descarregamentos da construção
	for( unsigned int d = 0; d < Descarregamentos.size(); d++){
		// caso o tempo final do descarregamento for maior que o Makespan atual entra no if
		if(  Descarregamentos[d].HorarioFinalDescarregamento  > Makespan){
			// Atualiza o Makespan com o horario do descarregamento corrente
			Makespan = Descarregamentos[d].HorarioFinalDescarregamento;
			//cout << " =-=-=-=-=-";
		}
	}
	//cout << "  " << Makespan ;
	// passa por todas as demandas
	for ( int i = 0; i < NumeroDemandas; i++){
		// caso ela não tiver sido atendida
		if( SituacaoDemanda[ i ] == 0 || SituacaoDemanda[ i ] == -1){
			// acresecnta uma penalidade ao Makespan da construção
			Makespan = Makespan + PenalidadeNaoAtendimentoDemanda * TempoMaximoDeFuncionamento;
			//cout << endl << endl << "  " << Makespan << " -> Inviolado construcao " << NumeroDaConstrucao << endl << endl;
		}
	}
}

// Imprime os dados da construções
void Construcao::ImprimeContrucao(){

	// imprime descarregamentos
	printf( "# Contrucao %d com %d demandas, janela de tempo (%.4f - %.4f), com rank = %.4f \n",NumeroDaConstrucao, NumeroDemandas, TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento, RankTempoDemandas);
	if( StatusAtendimento != 0){
		for( unsigned int d = 0; d < Descarregamentos.size(); d++){
			printf( "     * Carreta [%d-%d] atende demanda %d-%d de ( %.4f as %.4f )\n", Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
		}
	}

	// imprime o vetor de atendimento
	cout << "   Vetor de atendimento demandas [ ";
	for ( int i = 0; i < NumeroDemandas; i++){
		cout << SituacaoDemanda[ i ] << " ";
	}
	cout << "]" << endl;

	// imprime o vetor remocao
	cout << "   Vetor de Situacao Remocao das demandas [ ";
	for ( int i = 0; i < NumeroDemandas; i++){
		cout << SituacaoRemocao[ i ] << " ";
	}
	cout << "]" << endl;

	// imprime makespan da cosntrução
	printf ("   MAKESPAN = %.4f   Status = %d\n", Makespan, StatusAtendimento);
}

// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe a demanda não alocada ainda
int Construcao::AtrazaDemandasParaAtenderMaster( int NumDemanda, double HoraFimAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int TipoOrdenacao,int imprime, string frase){
	// aramazena o valor auxiliar do horario final de atendiemnto na construção caso for adotado se possibilita o atendimento da demanda
	double NovaHoraFimAtendiemnto;

	if( imprime == 1){
		cout << endl << endl << "     ====================== Entra Master [" << NumeroDaConstrucao << "-" << NumDemanda << "] ====================== "  << endl << endl;

		ImprimeContrucao();
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
	}

	// aloca valor de situaçãAlocação como sendo que a tarefa que ainda naõ foi alocada pode ser alocada caso se atraze o atendimento das tarefas que são anteriores a ela
	SituacaoAlocacao = -2;

	// enquanto se puder atender a demanda coeernte se atrazar as outras, se continua no loop
	while(SituacaoAlocacao == -2 ){

		// tenta atrazar as demandas anteriores para possibilitar o atendimento da demand corrente
		AtrazaDemandasParaAtenderRecursao( NumDemanda, HoraFimAtendiemnto,  DadosTarefasMovidasAuxiliar,  Plantas, SituacaoAlocacao, TipoOrdenacao,imprime, frase);
		// verifica se pode atender a demanda corrente
		SituacaoAlocacao = AlocaAtividadeComHorarioInicio( NumDemanda, HoraFimAtendiemnto, NovaHoraFimAtendiemnto, DadosTarefasMovidasAuxiliar, SituacaoDemanda, StatusRemocao, Plantas, TipoOrdenacao,frase);
		// se atualiza a hora que se tem que atender a tarefa anterior a tarefa corrente que se quer alocar
		HoraFimAtendiemnto = NovaHoraFimAtendiemnto;
	}

	if( imprime == 1){
		ImprimeContrucao();
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
		cout << endl << endl << "     ====================== Sai Master [" << NumeroDaConstrucao << "-" << NumDemanda << "] ====================== "  << endl << endl;
	}

	if( SituacaoAlocacao == 1){
		// caso se consiga alocar a demanda, retorna 1
		return 1;
	}else{
		// caso não se consiga alocar a demanda, retorna 0
		return 0;
	}
}

// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe as demandas que serão atrasadas para que a demanda não atendida possa ser atendida
int Construcao::AtrazaDemandasParaAtenderRecursao( int NumDemanda, double HoraFimAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int TipoOrdenacao,int imprime, string frase){
	// aramazena o valor auxiliar do horario final de atendiemnto na construção caso for adotado se possibilita o atendimento da demanda
	double NovaHoraFimAtendiemnto;
	// aramzena os valores da situação da demanda e a situação remoção da demanda retirada, para que quando a demanda for readicionada ela tenha os mesmo valores para esses campos que era anteriorment
	int SituacaoDemandaAux;
	int SituacaoRemocaoAux;
	// variavel de input para parar o programa
	int ParaPrograma;

	if( imprime == 1){
		cout << endl << endl << "     ++++++++++++++++ Entra Sub Recursão [" << NumeroDaConstrucao << "-" << NumDemanda - 1 << "] +++++++++++++++ "  << endl << endl;

		ImprimeContrucao();
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

		cout << endl << endl << "        ->->->->->->->-> Atraza Demandas Para Atender  Demanda [" << NumeroDaConstrucao << "-" << NumDemanda << "] - A demanda [" << NumeroDaConstrucao << "-" << NumDemanda -1 << "] tem que terminar de ser atendida as " << HoraFimAtendiemnto << endl << endl;
	}

	// armazena a situação demanda e remoção antes de deletar a demanda
	SituacaoDemandaAux = SituacaoDemanda[NumDemanda-1];
	SituacaoRemocaoAux = SituacaoRemocao[NumDemanda-1];

//Deleta a demanda anterior (NumDemanda-1) a demanda que não se consegue alocar
	DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(0, Descarregamentos[NumDemanda-1].HorarioInicioDescarregamento, Descarregamentos[NumDemanda-1].HorarioFinalDescarregamento, NumDemanda - 1, Descarregamentos[NumDemanda-1].NumPlantaFornecedor  , Descarregamentos[NumDemanda-1].NumCarretaUtilizada , Plantas, DadosTarefasMovidasAuxiliar);

	if( imprime == 1){
		ImprimeContrucao();
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

		//cin >> ParaPrograma;

		cout << endl << endl << "  *****  Tenta adicionar demanda [" << NumeroDaConstrucao << "-" << NumDemanda -1 << "] respeitando o intervalo" << endl << endl;
	}
// Tenta alocar a demanda que foi retirada ( NumDemanda-1) em um horario que permite o atendiemnto da demanda atual (NumDemanda)
	SituacaoAlocacao = AlocaAtividadeComHorarioInicio( NumDemanda - 1, HoraFimAtendiemnto, NovaHoraFimAtendiemnto, DadosTarefasMovidasAuxiliar,SituacaoDemandaAux,SituacaoRemocaoAux,  Plantas, TipoOrdenacao, frase);

	if( imprime == 1){
		cout << endl << endl << "             A Demanda [" << NumDemanda - 1 << "] após processo tem o SituacaoAlocacao valor de [" << SituacaoAlocacao << "]"<< endl << endl;
		ImprimeContrucao();
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

		cin >> ParaPrograma;
	}

// Atualiza o horario de inicio que a nova demanda anterior temq eu ter
	HoraFimAtendiemnto = NovaHoraFimAtendiemnto;

// só entra para ver se vai no loop caso a demanda corrente no novo loop ( NumDemanda-1) for maior que 0, pois só se for maior que zero ela tera uma tarefa anterior para ser deslocada no procedimento AlocaAtendimentoComHorarioInicio
	if( NumDemanda - 1 > 0){
		// só entra no loop caso se puder atender a tarefa ( NumDemanda-1) caso se atrazar o atendiment de demandas anteriores
		while( SituacaoAlocacao == -2  ){
			// chama a função recursivamente para tentar atrazar a demanda que vem antes da demanda corrente. Isto é para possibilitar colocar a demanda corrente respeitando o tempo para atender a demanda após a demanda corrente
			AtrazaDemandasParaAtenderRecursao( NumDemanda - 1, HoraFimAtendiemnto,  DadosTarefasMovidasAuxiliar,Plantas, SituacaoAlocacao, TipoOrdenacao, imprime, frase);
			if( SituacaoAlocacao == 1){
				SituacaoAlocacao = AlocaAtividadeComHorarioInicio( NumDemanda, HoraFimAtendiemnto, NovaHoraFimAtendiemnto, DadosTarefasMovidasAuxiliar, SituacaoDemandaAux,SituacaoRemocaoAux, Plantas, TipoOrdenacao, frase);
				HoraFimAtendiemnto = NovaHoraFimAtendiemnto;
			}
		}
	}

	if( imprime == 1){
		ImprimeContrucao();

		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
		cout << endl << endl << "  ++++++++++++++++ Sai Sub Recursão [" << NumeroDaConstrucao << "-" << NumDemanda - 1 << "] ++++++++++++++++ " << endl << endl;

		cin >> ParaPrograma;
	}


}

// encontra a planta mais perto da construção e que não tenha sido analisada antes
void Construcao::EncontraPlantaComMenorDistanciaParaConstrucao(  int& NumPlantaAnalisando, ConjuntoPlantas& Plantas, string frase){
	// Armazena a distancia para a construção
	double DistanciaConstrucaoPlanta;
	// inicia valores das variaveis
	NumPlantaAnalisando = -13;
	DistanciaConstrucaoPlanta = DBL_MAX;

	// percorre todas as plantas
	for( unsigned int p = 0; p < Plantas.Plantas.size(); p++){
		// caso a planta corrente tiver uma distancia menor que a da distancia corrente, se entra no if
		if( DistanciaConstrucaoPlanta > DistanciaPlantas[p].Distancia){
			// se a planta que ainda não foi analisada, se entra no if
			if( Plantas.PlantasAnalizadas[p] == 0){
				// armazena os dados da planta mais perto no momento
				NumPlantaAnalisando = p;
				// armazena a distancia da planta mais perto da construção no momento
				DistanciaConstrucaoPlanta = DistanciaPlantas[p].Distancia;
			}
		}
	}
	// verifica se não encontrou uma planta mais perto não analisada ainda
	if(NumPlantaAnalisando == -13){
		cout << endl << endl << " >>>>>>>>>>>>>>>> Problema!  Planta não encontrada! " << frase << endl << endl << endl;
	}
}

int Construcao::AlocaAtividadeComHorarioInicio( int NumDemanda, double HoraFimAtendiemnto, double &NovaHoraFimAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar, int SituacaoDemanda, int StatusRemocao, ConjuntoPlantas& Plantas, int TipoOrdenacao, string frase){
	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	int NumPlantaAnalisando;

	// inicia o vetor que armazena os horariso que as plantas podem atender a demanda
	Plantas.InicializaVetorHorarioQuePlantaPodeAtender();

	//int ParaPrograma;

	//
	if ( NumeroDemandas > StatusAtendimento){
		Plantas.InicializaPlantasAnalizadas();
		do{
			EncontraPlantaComMenorDistanciaParaConstrucao( NumPlantaAnalisando, Plantas, "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  ->Construcao::AlocaAtividadeComHorarioInicio( &&&&&&&&&&&&& ");
			Plantas.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
			for( int v = 0; v < Plantas.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){
				HorarioInicioPlanta = HoraFimAtendiemnto - Plantas.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda] -  Plantas.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[NumPlantaAnalisando].TempoPlanta;
				do{
					HorarioSaiDaPlanta = HorarioInicioPlanta + Plantas.Plantas[NumPlantaAnalisando].TempoPlanta;
					HorarioChegaContrucao = HorarioSaiDaPlanta + Plantas.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[NumeroDaConstrucao];
					HorarioSaiConstrucao = HorarioChegaContrucao +  Plantas.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda];
					HorarioRetornaPlanta = HorarioSaiConstrucao + Plantas.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[NumeroDaConstrucao];

					DisponibilidadePlanta = Plantas.Plantas[NumPlantaAnalisando].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
					DisponibilidadeConstrucao = VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
					DisponibilidadeCarreta = Plantas.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
					if( DisponibilidadePlanta == 1){
						if( DisponibilidadeCarreta == 1){
							if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){

								AlocaAtividadeSalvandoDados(0,HorarioChegaContrucao, HorarioSaiConstrucao, Plantas.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, Plantas.Plantas[NumPlantaAnalisando].NumeroDaPlanta, SituacaoDemanda, StatusRemocao, Plantas, DadosTarefasMovidasAuxiliar);
								//ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
								return 1;
							}else{
								if( DisponibilidadeConstrucao == -2){
									//cout <<  "                     Caso atrazar da para alocar, demanda em analise [" << NumeroDaConstrucao << "-" << NumDemanda << "] no horario " << HorarioChegaContrucao << endl;
									if( Plantas.PlantasAnalizadas[NumPlantaAnalisando] == 0){
										Plantas.HorarioQuePlantaPodeAtender[NumPlantaAnalisando] = HorarioInicioPlanta;
										Plantas.HorarioQueConstrucaoPodeReceberDemanda[NumPlantaAnalisando] = HorarioChegaContrucao;
									}
									Plantas.PlantasAnalizadas[NumPlantaAnalisando] = -2;
									HorarioInicioPlanta = Plantas.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento;
								}
							}

						}
					}
					HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
				}while( HorarioInicioPlanta <= Plantas.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= TempoMaximoDeFuncionamento);
			}
			if (Plantas.PlantasAnalizadas[NumPlantaAnalisando] != -2){
				Plantas.PlantasAnalizadas[NumPlantaAnalisando] = 1;
			}
		}while( Plantas.AnalizouTodasPLanats() == 0);


		if( Plantas.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() == 1){
			NovaHoraFimAtendiemnto = Plantas.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() - TempoMaximoEntreDescargas + IntervaloDeTempo;
			return -2;
		}

		return 0;

	}else{
		cout << endl << endl << endl << "   >>>>>>>>>>>>>>>  Problema! -> Construcao [" << NumeroDaConstrucao << "-" << NumDemanda << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		return 0;
	}
	return 0;

}

// verifica a integridade entre os descarregamentos da construção
int Construcao::VerificaIntegridadeDeDescrregamentos(int imprime){
	// percorre todos os deslocamentos
	for( int d1 = 0; d1 < Descarregamentos.size(); d1++){
		// verifica se o descarregaento não possui tempo negativo
		if( Descarregamentos[d1].HorarioInicioDescarregamento > Descarregamentos[d1].HorarioFinalDescarregamento ){
			printf( " >>>>>>>>>>>>>> Problema! Descarregamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Descarregamentos[d1].HorarioFinalDescarregamento - Descarregamentos[d1].HorarioInicioDescarregamento  , Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
			return 0;
		}
		// percorre todos os deslocamentos
		for( int d2 = 0; d2 < Descarregamentos.size(); d2++){
			// o descarregamento não pode ser o memso que o analisado no primeiro loop
			if( Descarregamentos[d1].HorarioInicioDescarregamento != Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento != Descarregamentos[d2].HorarioFinalDescarregamento){
				// verifica se o descarregamento está contido dentro de outro descarregamento
				if( Descarregamentos[d1].HorarioInicioDescarregamento <= Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento >= Descarregamentos[d2].HorarioFinalDescarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento, Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
					return 0;
				}
				// verifica se o descarregamento  contem  outro descarregamento
				if( Descarregamentos[d1].HorarioInicioDescarregamento >= Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento <= Descarregamentos[d2].HorarioFinalDescarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento, Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
					return 0;
				}
				// verifica se o descarregamento  está parcialmente contido na parte inicial de  outro descarregamento
				if( Descarregamentos[d1].HorarioFinalDescarregamento > Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento <= Descarregamentos[d2].HorarioFinalDescarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento, Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento );
					return 0;
				}
				// verifica se o descarregamento  está parcialmente contido na parte final de  outro descarregamento
				if( Descarregamentos[d1].HorarioInicioDescarregamento >= Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioInicioDescarregamento < Descarregamentos[d2].HorarioFinalDescarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento, Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento );
					return 0;
				}

			}
		}
	}
	// os descarregamentos são integros entre se
	if( imprime == 1){
		cout << " Descarregamentos integros " << endl;
	}
	return 1;
}

Construcao::~Construcao(){		// destruidora da classe

}


class ConjuntoConstrucoes{

public:

	vector< Construcao > Construcoes;
	int NumeroConstrucoes;
	vector < int > ConstrucoesAnalizadas;

	vector < int > ConstrucaoPodeSerSuprida;

	double MakespanConstrucoes;
	int NivelDeInviabilidade;

	ConjuntoConstrucoes();

	void InicializaConstrucoesAnalizadas();				// Inicializa o status das cosntruções todos como 0
	void CalcularNivelDeInviabilidade();				// Calcula o Nivel de Inviabilidade
	void IniciaConjuntoConstrucoes(int Numero);			// Inicializa a classe com o número das construções que se quer

	void VerificaIntervaloContrucoes();					// Verifica se as construções respeitão os intervalos de atendimento entre suas demandas
	void CalculaMakespansConstrucoes();					// Calcula o Makespan das Construções
	int RetornaIndiceConstrucao(int Construcao, int& Indice, string frase);			// retorna o indice da construção passada

	void ImprimeContrucoes(ConjuntoPlantas& Plantas, int VerificaViabilidade);								// Imprime as construções e em seguida o nivel de inviabilidade
	int VerificacaoIntegridadeDeDescarregamentosConstrucoes(int imprime);			// faz a verificação dos descarregaemntos
	int VerificaIndividualmenteDemandas(ConjuntoPlantas& Plantas, int imprime);		// verifica se as tarefas são integras

	int VerificacaoConsistenciaTarefas(ConjuntoPlantas& Plantas, int imprime);		// verifica integridade das tarefas como um todo

// Funções com a SituaçãoRemover
	void ReiniciaTarefasRetiradas();			// Reinicia o status de remoção de todas as demandas de todas as construções
	void MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda, int Situacao);					// maraca a situação remoção da demanda no vetor que sinaliza a situação da demanda
	int ConstrucaoTemTarefaParaRemover(int& Construcao, int& Demanda, int Imprimir);			// Usado em ProcessoViabilizacao1. Verifica se possui uma construção que possui demandas que ainda não foram retiradas para se tentar a viabilização da solução. Caso possuir, retorna 1 a função e é retornado os dados da construção e da demanda por parametro.
	void MarcaTarefaNaoRemovidaNoVetor(int Construcao, int Demanda, string frase);				// marca a tarefa, demand, não removida


// Funções com a PodeAtender
	void AlocaValoresConstrucaoPodeAtender();		// Marca se precisa analisar a construção. Aloca 1 se a construção já teve todas as demandas atendidas, 0 as que não
	void AtualizaValoresConstrucaoPodeAtender();	// Atualiza com 1 se a construção já teve todas as demandas atendidas
	int VerificaConstrucaoPodeAtender();			// Verifica se existe uma demanda que ainda pode ser analisada pelo algoritmo

	void AlocaValoresConstrucoesAnalizadas( int IndiceConstrucaoNaoAtendida );			// 		Coloca o status 2 para as construções que já foram atendidas, e coloca 3 no status da construção passada como parametro
	int RetornaDadosDemandaAtendida( int Construcao, int Demanda,  int &NumPlanta, int &NumCarreta, double &HorarioInicioDescarregamento, double &HorarioFinalDescarregamento, double &HorarioInicioCarregamento, double &HorarioFinalCarregamento, double &HorarioInicioDeslocamento, double &HorarioFinalDeslocamento, ConjuntoPlantas& Plantas);		// retorna dados de uma tarefa que atende uma demanda passada na função
	int VerificaIntegridaDeDemandaAtendida( int Construcao, int Demanda, int NumPlanta, int NumCarreta, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento, double HorarioInicioCarregamento, double HorarioFinalCarregamento, double HorarioInicioDeslocamento, double HorarioFinalDeslocamento, int imprime);		// verifica a integridade da tarefa

	~ConjuntoConstrucoes();						// Destruidora da classe
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){
	NumeroConstrucoes = -13;
	NivelDeInviabilidade = -13;
	MakespanConstrucoes = -13;
}

// Inicializa o status das cosntruções todos como 0
void ConjuntoConstrucoes::InicializaConstrucoesAnalizadas(){
	// inicia o vetor de construções analisadas
	ConstrucoesAnalizadas.resize(Construcoes.size());
	// percorre por todas as construções
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		// inicia como não analisada, ou com o status 0
		ConstrucoesAnalizadas[c] = 0;
	}
}

// Calcula o Nivel de Inviabilidade
void ConjuntoConstrucoes::CalcularNivelDeInviabilidade(){
	// zera o nivel de inviabilidade
	NivelDeInviabilidade = 0;
	// percorre todas as contruçãoes
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		// atualiza com o nivel de inviabilidade da construção corrente
		NivelDeInviabilidade = NivelDeInviabilidade + Construcoes[c].NumeroDemandas - Construcoes[c].StatusAtendimento;
	}
}

// Inicializa a classe com o número das construções que se quer
void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	// inicia o vetor de cosntruções com o numero de construções
	Construcoes.resize(Numero);
	// aloca o numero de construções
	NumeroConstrucoes = Numero;

}


// Verifica se as construções respeitão os intervalos de atendimento entre suas demandas
void ConjuntoConstrucoes::VerificaIntervaloContrucoes(){

	cout << endl << " Status de respeito a intervelos de construção" << endl;
	// percorre por todas as construções
	for(int c = 0; c < NumeroConstrucoes; c++){
		// verifica se a cosntrução corrente respeita o intervalo entre descarregamentos
		if( Construcoes[c].VerificaDescarregamentosRespeitaIntervalo() == 1){
			// caso respeitar
			cout << endl << Construcoes[c].NumeroDaConstrucao << " OK!";
		}else{
			// caso não respeitar
			cout << endl << Construcoes[c].NumeroDaConstrucao << " inviavel!";
		}
	}
	cout << endl ;
}

// Calcula o Makespan das Construções
void ConjuntoConstrucoes::CalculaMakespansConstrucoes(){
	// inicia o makespan das cosntruções como zero
	MakespanConstrucoes = 0;
	// percorre por todas as construções
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		// calcula o makespan da construção corrente
		Construcoes[c].CalculaMakespan();
		// acrescenta o makespan da cosntruyução corrente ao  makespan de todas as cosntruções
		MakespanConstrucoes = MakespanConstrucoes + Construcoes[c].Makespan;
	}
}

// retorna o indice da construção passada
int ConjuntoConstrucoes::RetornaIndiceConstrucao(int Construcao, int& Indice, string frase){
	// percorre por todas as construções
	for ( int i = 0; i < NumeroConstrucoes; i++){
		// verifica se a construção corrente é a cosntrução que se quer
		if( Construcao == Construcoes[i].NumeroDaConstrucao){
			// aloca o indice da construção que se quer
			Indice = i;
			// retorna 1, encontrou a construção que se quer
			return 1;
		}
	}
	cout << endl << endl << "   Problema >> Não encontrou indice construção [" << Construcao << "]   -> ConjuntoConstrucoes::RetornaIndiceConstrucao" << endl << " ->";
	cout << frase << endl << endl;
	// retorna 0, não encontrou a construção que se quer
	return 0;
}


// Imprime as construções e em seguida o nivel de inviabilidade
void ConjuntoConstrucoes::ImprimeContrucoes(ConjuntoPlantas& Plantas, int VerificaViabilidade){
	cout << endl << endl << " [[[[[[  Imprime construcoes  ]]]]]]" << endl;
	// percorre todas as cosntruções
	for(int c = 0; c < NumeroConstrucoes; c++){
		// iomprime a construção corrente
		Construcoes[c].ImprimeContrucao();
	}
	printf( " Nivel de Inviabilidade = %d  Makespan Geral das Construcoes = %.4f\n", NivelDeInviabilidade, MakespanConstrucoes);

	if( VerificaViabilidade == 1){
		VerificacaoConsistenciaTarefas(Plantas, 1);
	}
}

// faz a verificação dos descarregaemntos
int ConjuntoConstrucoes::VerificacaoIntegridadeDeDescarregamentosConstrucoes(int imprime){
	int Integro;
	// inicia como integro o estado dos descarregamentos
	Integro = 1;

	if( imprime == 1) {
		cout << endl << "          Verifica integridade Descarregaemntos  " << endl << endl;
	}
	// percore todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		cout << " construcao [" << Construcoes[c].NumeroDaConstrucao << "] ";
		// verifica a integridade dos descarregamentos da construção
		if( Construcoes[c].VerificaIntegridadeDeDescrregamentos(imprime) == 0 ){
			cout << endl << endl << "      Problema! Descarremagentos não estão integros " << endl << endl;
			Integro = 0;
		}
	}

	// retorna se existe algum descarregamento que não esta integro ao retorna 0, ou 1 caso contrario
	return Integro;
}

// verifica se as tarefas são integras
int ConjuntoConstrucoes::VerificaIndividualmenteDemandas(ConjuntoPlantas& Plantas, int imprime){
	int NumPlanta;
	int NumCarreta;
	double HorarioInicioDescarregamento;
	double HorarioFinalDescarregamento;
	double HorarioInicioCarregamento;
	double HorarioFinalCarregamento;
	double HorarioInicioDeslocamento;
	double HorarioFinalDeslocamento;

	int integridade;
	// inicia como integro o estado dos descarregamentos
	integridade = 1;

	if( imprime == 1){
		cout << endl << "          Verifica tarefas individualmente  " << endl << endl;
	}

	// percorre por taodas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// percorre por todas as demandas da construção
		for( int d = 0; d < Construcoes[c].NumeroDemandas; d++){
			// verifica se a construção foi atendida
			if( Construcoes[c].SituacaoDemanda[d] == 1){
				// fornece os dados do atendimento da tarefa da demanda
				RetornaDadosDemandaAtendida( Construcoes[c].NumeroDaConstrucao, d, NumPlanta, NumCarreta, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioInicioCarregamento, HorarioFinalCarregamento, HorarioInicioDeslocamento, HorarioFinalDeslocamento, Plantas);
				if( imprime == 1){
					printf( "  - Demanda [%d-%d] => construcao [%d] no horario (%.4f-%.4f)",Construcoes[c].NumeroDaConstrucao,d,Construcoes[c].NumeroDaConstrucao,HorarioInicioDescarregamento, HorarioFinalDescarregamento);
					printf( "  planta [%d] no horario (%.4f-%.4f) ",NumPlanta, HorarioInicioCarregamento, HorarioFinalCarregamento);
					printf( "  carreta [%d] no horario (%.4f-%.4f) \n", NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento );
				}
				// verifica se a tarefa é integra
				if ( VerificaIntegridaDeDemandaAtendida(Construcoes[c].NumeroDaConstrucao, d, NumPlanta, NumCarreta, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioInicioCarregamento, HorarioFinalCarregamento, HorarioInicioDeslocamento, HorarioFinalDeslocamento, imprime) == 0){
					// caso não for ele assinala na variavel de controle que se tem uma tarefa não integra
					integridade = 0;
				}

			}
		}
	}
	// retorna o estado de integridade das tarefas, 1 se todas forem integras e 0 caso tiver alguma que não é integra
	return integridade;
}

// verifica integridade das tarefas como um todo
int ConjuntoConstrucoes::VerificacaoConsistenciaTarefas(ConjuntoPlantas& Plantas, int imprime){
	int integridade;
	// inicia como integro o estado das tarefas
	integridade = 1;

	cout << endl << endl << " ***********  Consistencia da solução ********************* " << endl << endl;

	//verifica as tarefas individualmente
	if( VerificaIndividualmenteDemandas( Plantas,imprime) == 0){
		cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de demandas individuais" << endl << endl;
		integridade = 0;
	}
	//verifica os descarregamentos
	if( VerificacaoIntegridadeDeDescarregamentosConstrucoes(imprime) == 0){
		cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de Descarregaemntos" << endl << endl;
		integridade = 0;
	}
	//verifica os carregamentos
	if(Plantas.VerificaIntegridadeDeCarregamentosDasPlantas(imprime) == 0){
		cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de Carregaemntos" << endl << endl;
		integridade = 0;
	}
	//verifica os deslocamentos
	if(Plantas.VerificaIntegridadeDeDeslocaemntosDosVeiculosDasPlantas(imprime) == 0){
		cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de Deslocamentos" << endl << endl;
		integridade = 0;
	}

	cout << endl << endl << " *********************************************************** " << endl << endl;

	return integridade;
}

// ***************** Funções com a SituaçãoRemover ***************** //

// Reinicia o status de remoção de todas as demandas de todas as construções
void ConjuntoConstrucoes::ReiniciaTarefasRetiradas(){
	// percorre todas as cosntruções
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		// percorre todas as demandas da cosntrução corrente
		for( int d = 0; d < Construcoes[c].NumeroDemandas; d++){
			// coloca o status da demanda corrente como não removida
			Construcoes[c].SituacaoRemocao[d] = 0;
		}
	}
}

// maraca a situação remoção da demanda no vetor que sinaliza a situação da demanda
void ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda, int Situacao){
	int c;
	// caso se encontrar a construção passada na função, entrar no if
	if( RetornaIndiceConstrucao(Construcao, c, "ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor")== 1 ){
		if( Construcoes[c].NumeroDemandas > Demanda ) {
		    //marca a demanda com o valor passado
			Construcoes[c].SituacaoRemocao[Demanda] = Situacao;
			//cout << endl << endl << "  marquei " << endl << endl;
		}else{
			cout << endl << endl << "    <<<<<<<<<<<<<<<  Problema!   Demanda  [" << Construcao << "-" << Demanda << "] não existe -> ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor >>>>>>>>>>>> " << endl << endl;
		}
	}else{
		cout << endl << endl << "    <<<<<<<<<<<<<<<  Problema!   Não encontrei a construção [" << Construcao << "] -> ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor >>>>>>>>>>>> " << endl << endl;
	}

}

// Usado em ProcessoViabilizacao1. Verifica se possui uma construção que possui demandas que ainda não foram retiradas para se tentar a viabilização da solução. Caso possuir, retorna 1 a função e é retornado os dados da construção e da demanda por parametro.
int ConjuntoConstrucoes::ConstrucaoTemTarefaParaRemover(int& Construcao, int& Demanda, int Imprimir){

	//ConstrucoesInstancia.ImprimeContrucoes();
	int Ativo;
	double RankInicial;

	Construcao = -13;
	Demanda = -13;

	Ativo = 0;
	RankInicial = DBL_MAX;

	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// caso o rank da cosntrução corrente for menor que o rank atual entra no if, isso faz que a função pegue a construção com o menor rank
		if ( RankInicial > Construcoes[c].RankTempoDemandas){
			// percorre as demandas da construção em ordem decerscente
			for( int d = (Construcoes[c].NumeroDemandas - 1); d >= 0 ; d--){
				// so entra caso a demanda tenha sido atendida
				if(Construcoes[c].SituacaoDemanda[d] == 1){
					// so entrra caso ela não tenha sido removida anteriormente
					if( Construcoes[c].SituacaoRemocao[d] == 0){
						// aloc a construção corrente, a demanda e o rank da construção
						Construcao = Construcoes[c].NumeroDaConstrucao;
						Demanda = d;
						RankInicial = Construcoes[c].RankTempoDemandas;
						// marca que encontrou uma demanda
						Ativo = 1;
					}
				}
			}
		}
	}
	if( Ativo == 1){
		if( Imprimir == 1){
			cout << " Selecionou construcao " << Construcao << "-" << Demanda << " com janela de tempo ";
			cout <<  Construcoes[Construcao].TempoMinimoDeFuncionamento << "-" << Construcoes[Construcao].TempoMaximoDeFuncionamento;
			cout << " -> ConstrucaoTarefaRemover" << endl ;
		}
		// encontrou uma demanda a remover
		return 1;
	}else{
		// não encontrou uma demanda a remover
		return 0;
	}
}

// marca a tarefa, demand, não removida
void ConjuntoConstrucoes::MarcaTarefaNaoRemovidaNoVetor(int Construcao, int Demanda, string frase){
	int c;

	// aloca o indice da construção
	if( RetornaIndiceConstrucao( Construcao, c, " ConjuntoConstrucoes::MarcaTarefaNaoDeletadaNoVetor") == 1 ){
		if( Construcoes[c].NumeroDemandas > Demanda ) {
			// marca a demanda como não removida
			Construcoes[c].SituacaoRemocao[Demanda] = 0;
		}else{
			cout << endl << endl << "    <<<<<<<<<<<<<<<  Problema!   Demanda  [" << Construcao << "-" << Demanda << "] não existe -> ConjuntoConstrucoes::MarcaTarefaNaoRemovidaNoVetor " << frase << endl << endl;
		}
	}else{
		cout << " <<<<<<<<<<<< problema! não encontrou a construção [" <<  Construcao << "] ->  ConjuntoConstrucoes::MarcaTarefaNaoRemovidaNoVetor " << frase << endl << endl;
	}
}

// ***************** Funções com a PodeAtender ***************** //

// Marca se precisa analisar a construção. Aloca 1 se a construção já teve todas as demandas atendidas, 0 as que não
void ConjuntoConstrucoes::AlocaValoresConstrucaoPodeAtender(){
	// inicia a estrutura de pode avaliar com o numero de construções
	ConstrucaoPodeSerSuprida.resize(NumeroConstrucoes);
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// entra caso a cosntrução já tenha todas as suas demandas atendidas
		if ( Construcoes[c].NumeroDemandas == Construcoes[c].StatusAtendimento){
			// marca que não precisa avaliar a cosntrução corrente
			ConstrucaoPodeSerSuprida[c] = 1;
		}else{
			// marca que precisa avaliar a cosntrução corrente
			ConstrucaoPodeSerSuprida[c] = 0;
		}
	}

}

// Atualiza com 1 se a construção já teve todas as demandas atendidas
void ConjuntoConstrucoes::AtualizaValoresConstrucaoPodeAtender(){
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// caso todas as demandas da construção tenha suas demandas já atendidas entra
		if ( Construcoes[c].NumeroDemandas == Construcoes[c].StatusAtendimento){
			// marca que não precisa analisar a construção corrente
			ConstrucaoPodeSerSuprida[c] = 1;
		}
	}

}

// Verifica se existe uma demanda que ainda pode ser analisada pelo algoritmo
int ConjuntoConstrucoes::VerificaConstrucaoPodeAtender(){
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// caso a construção corrente ainda possa ser analisada
		if( ConstrucaoPodeSerSuprida[c] == 0){
			// caso ela possa ser analisada retorna 1
			return 1;
		}
	}
	// não se possui mais construções a analisar, retorna 0
	return 0;

}

// 		Coloca o status 2 para as construções que já foram atendidas, e coloca 3 no status da construção passada como parametro
void ConjuntoConstrucoes::AlocaValoresConstrucoesAnalizadas( int IndiceConstrucaoNaoAtendida){
	// percorre todas as construções
	for ( int c = 0; c < NumeroConstrucoes; c++){
		// caso a cosntruçaõ já tenha tido todas as suas demandas atendidas
		if( Construcoes[c].StatusAtendimento == Construcoes[c].NumeroDemandas ){
			// coloca o valor 2
			ConstrucoesAnalizadas[c] = 2;
		}
	}
	// coloca o valor 3 na construção que foi passada na função
	ConstrucoesAnalizadas[IndiceConstrucaoNaoAtendida] = 3;

}

// retorna dados de uma tarefa que atende uma demanda passada na função
int ConjuntoConstrucoes::RetornaDadosDemandaAtendida( int Construcao, int Demanda, int &NumPlanta, int &NumCarreta, double &HorarioInicioDescarregamento, double &HorarioFinalDescarregamento, double &HorarioInicioCarregamento, double &HorarioFinalCarregamento, double &HorarioInicioDeslocamento, double &HorarioFinalDeslocamento, ConjuntoPlantas& Plantas){
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		//verifica se a cosntrução corrente é a que se quer
		if( Construcoes[c].NumeroDaConstrucao == Construcao ){
			// verifica se a demanda que se quer já foi atendida
			if( Construcoes[c].SituacaoDemanda[Demanda] == 1 ){
				// coleta dados da planta e da carreta que se deseja
				if( Plantas.RetornaDadosDemandaAtendida(Construcao, Demanda, HorarioInicioCarregamento, HorarioFinalCarregamento, NumPlanta, NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento) == 0){
					cout << endl << endl << "  <<<<<<<<<<<< Problema! não consegui pegar dados da planta e da carreta da demanda [" << Construcao << "-" << Demanda << "] ! -> ConjuntoConstrucoes::RetornaDadosDemandaAtendida " << endl << endl;
					// problema em se coleta dados da planta e da carreta que se deseja
					return 0;
				}else{
					// caso o descarregamento que se quer tenha a mesma planta e carreta que se verificaou pela planta e carreta que atendem a demanda, caso sim entra
					 if( Construcoes[c].Descarregamentos[Demanda].NumPlantaFornecedor == NumPlanta && Construcoes[c].Descarregamentos[Demanda].NumCarretaUtilizada == NumCarreta){
						 // aloca os dados
						 HorarioInicioDescarregamento = Construcoes[c].Descarregamentos[Demanda].HorarioInicioDescarregamento;
						 HorarioFinalDescarregamento = Construcoes[c].Descarregamentos[Demanda].HorarioFinalDescarregamento;
						 // retorna 1, encontrou os dados procurados e não se verificou inconsistencia entre a planta, construção e a carreta
						 return 1;
					 }else{
						 cout << endl << endl << "  <<<<<<<<<<<< Problema! não consegui pegar dados do descarregamento da demanda [" << Construcao << "-" << Demanda << "] ! -> ConjuntoConstrucoes::RetornaDadosDemandaAtendida " << endl << endl;
						 // inconsistencia entre o atendimento na construção com o realizado pela planta e pala carreta, retorna 0
						return 0;
					 }
				}
			}else{
				cout << endl << endl << "  <<<<<<<<<<<< Problema! Demanda [" << Construcao << "-" << Demanda << "] não atendida! -> ConjuntoConstrucoes::RetornaDadosDemandaAtendida " << endl << endl;
				// demanda não atedida, retorna 0
				return 0;
			}
		}
	}
	cout << endl << endl << "  <<<<<<<<<<<< Problema! Construção [" << Construcao << "] não encontrada! -> ConjuntoConstrucoes::RetornaDadosDemandaAtendida " << endl << endl;
	// não encontrou a consrução que se quer, retorna 0
	return 0;
}

// verifica a integridade da tarefa
int ConjuntoConstrucoes::VerificaIntegridaDeDemandaAtendida( int Construcao, int Demanda, int NumPlanta, int NumCarreta, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento, double HorarioInicioCarregamento, double HorarioFinalCarregamento, double HorarioInicioDeslocamento, double HorarioFinalDeslocamento, int imprime){
	int c;

	// inicia o inidce da construção
	c = -13;

	// verifica se o delocamento se inicia no mesmo horario que o carregaemnto na planta
	if( HorarioInicioDeslocamento == HorarioInicioCarregamento){
		// verifica se o carregamento se inicia antes do seu final
		if( HorarioInicioCarregamento <= HorarioFinalCarregamento){
			// verifica se tempo de deslocamento da planta até construção não seja negativo
			if( HorarioFinalCarregamento <= HorarioInicioDescarregamento){
				// verifica que o tempo de descarregamento na planta não seja negativo
				if( HorarioInicioDescarregamento <= HorarioFinalDescarregamento){
					// verifica se tempo de deslocamento da até a planta não seja negativo
					if( HorarioFinalDescarregamento <= HorarioFinalDeslocamento){
						if( imprime == 1){
							cout << "     Integro " << endl;
						}
						return 1;
					}else{
						printf("       -------- Problema! HorarioFinalDescarregamento maior que HorarioFinalDeslocamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
					}
				}else{
					printf("       -------- Problema! HorarioInicioDescarregamento maior que HorarioFinalDescarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
				}
			}else{
				printf("       -------- Problema! HorarioFinalCarregamento maior que HorarioInicioDescarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
			}
		}else{
			printf("       -------- Problema! HorarioInicioCarregamento maior que HorarioFinalCarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
		}

	}else{
		printf("       -------- Problema! O horario de inicio do deslocamento e de inicio do carregamento não conicidem para a demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
	}
	// caso tiver algum problem, imprime os dados da tarefa e retorna 0
	RetornaIndiceConstrucao(Construcao, c, " ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida" );
	printf( "  - Demanda [%d-%d] => construcao [%d] no horario (%.4f-%.4f)",Construcoes[c].NumeroDaConstrucao, Demanda,Construcoes[c].NumeroDaConstrucao,HorarioInicioDescarregamento, HorarioFinalDescarregamento);
	printf( "  planta [%d] no horario (%.4f-%.4f) ",NumPlanta, HorarioInicioCarregamento, HorarioFinalCarregamento);
	printf( "  carreta [%d] no horario (%.4f-%.4f) \n", NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento );
	return 0;

}

// Destruidora da classe
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
