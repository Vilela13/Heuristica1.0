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
	double	HorarioInicioDescarregamento;
	double	HorarioFinalDescarregamento;
	int		NumCarretaUtilizada;			// número da carreta utilizada para realizar o descarregamento
	int		NumPlantaFornecedor;			// númerod a planta que fornece o concreto

	Descarregamento();	// construtora

	int		verifica( int carreta, int planta, double HorarioInicio, double HorarioFinal);			// verifica se os dados passados se referem ao descarregamento
	void	AnulaConteudo();			// anula o consteudo do descarregamento retornando ao estado original
	void	Imprime();				// imprime o conteudo dos descarregamento

	~Descarregamento();	// destruidora
};

// construtora
Descarregamento::Descarregamento(){
	HorarioInicioDescarregamento 	= -13;
	HorarioFinalDescarregamento 	= -13;
	NumCarretaUtilizada = -13;
	NumPlantaFornecedor = -13;

}

// verifica se os dados passados se referem ao descarregamento
int		Descarregamento::verifica( int carreta, int planta, double HorarioInicio, double HorarioFinal){
	// verifica se os dados passados são os memos que os do descarregamento
	if( NumCarretaUtilizada == carreta &&  NumPlantaFornecedor ==  planta && HorarioInicioDescarregamento == HorarioInicio && HorarioFinalDescarregamento == HorarioFinal){
		// dados conferem, retorna 1
		return 1;
	}
	// dados não conferem, retorna 0
	return 0;
}

// anula o consteudo do descarregamento retornando ao estado original
void 	Descarregamento::AnulaConteudo(){
	HorarioInicioDescarregamento 	= -12;
	HorarioFinalDescarregamento 	= -12;
	NumCarretaUtilizada = -12;
	NumPlantaFornecedor = -12;
}

// imprime o conteudo dos descarregamento
void 	Descarregamento::Imprime(){
	printf ("  Planta = %d Carreta = %d Tempo[%.4f - %.4f]\n", NumPlantaFornecedor, NumCarretaUtilizada, HorarioInicioDescarregamento, HorarioFinalDescarregamento);
}

Descarregamento::~Descarregamento(){
}


// retorna 1 se d1 vem anntes de d2
bool 	DecideQualDescarregamentoVemPrimeiro ( Descarregamento d1, Descarregamento d2 );

bool 	DecideQualDescarregamentoVemPrimeiro ( Descarregamento d1, Descarregamento d2 ){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}

// classe que foi criada para guardar a distancia da construção para a planta e manter um ponteiro para a estrutura dessa planta
class TempoParaPlanta{
public:
	double	Tempo;
	Planta* PlantaComparada;
};

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class Construcao{

public:
	int		NumeroDaConstrucao;						// número da construção
	int		NumeroDemandas;							// número de demadas que se tem que suprir na construções
	vector < int > SituacaoDemanda;					// vetor que se armazena a situação das demandas que se temq ue suprir na construção
	vector < int > SituacaoRemocao;					// vetor que armazena a situação de remoção da demanda. Se o valor for 1 ela ja foi removida, se é 0 ela ainda não foi
	vector < TempoParaPlanta > TempoParaPlantas;	// distância da construção até as plantas
	double	TempoMaximoEntreDescargas;				// tempo máximo permitido entre dois descarregamentos
	double	TempoMinimoDeFuncionamento;				// tempo mínimo de funcionamento da construção, primeiro horario que se pode receber um carregamento em uma construção
	double	TempoMaximoDeFuncionamento;				// tempo máximo de funcionamento da construção, ultimo horario que se pode receber um carregamento em uma construção
	double	RankTempoDemandas;						// rank entre a janela de tempo de se receber descarregamentos e o número de demandas
	int		StatusAtendimento;						// o número de demandas atendidas na construção
	vector < Descarregamento > Descarregamentos;	// descarregamentos já realziados na construção
	double	Makespan;								// makespan da construção
	double TempoDeVidaConcreto;

	// variaveis auxiliares nos procedimentos

	int ConstrucaoAnalizada;					// construção já foi analisada
	int ConstrucaoPodeSerSuprida;				// construção pode ser suprida
	int ConstrucaoComDemandasNaoAtendidas;		// construção com demandas que ainda temq ue ser atendidas

	Construcao();
	void	CalculaRankTempoDemandas(int comentarios);					// Calcula o rank que decide qual construção será atendida inicialmente
	int		VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao);				// Verifica se da para colocar a demanda na construção, ela sinaliza se caso atrazar as demandas sejá possivel alocar a demanda.
	int 	VerificaTempoDeVidaConcreto ( double HorarioChegaContrucao, double HorarioInicioPlanta);
	int		AlocaAtividade(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas);		// Aloca uma demanda na cosntrução apartir de dados

	int		AlocaAtividadeSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int Carreta, int NumPlanta, int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidas);			// Aloca uma demanda na cosntrução apartir de dados, dalvando os dados da demanda alocada em estrutura DadosAdicionado
	int		DeletaAtividadeLocomovendoAsOutrasTarefas(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas);				// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos
	int		DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar);			// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos, salvando os dados da tarefa removida em uma estrutura

	int		DeletaTarefas( int VerificaExistencia, int demanda, vector < DadosTarefa > &DadosRetirando, ConjuntoPlantas& Plantas);			// Deleta tarefas da demanda passada e as posteriores a esta demanda passada
	int		DeletaTarefasAnteriormenteAdicionadasDados(   DadosTarefa DadosAdicionados, ConjuntoPlantas& Plantas);		// deleta tarefa apartir de dados
	int		VerificaDescarregamentosRespeitaIntervalo();			// Verifica se os descrarregamentor na construção estão respeitando os intervalos entre elas

	void	RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio);				// retorna o horario de inicio de um certo descarregamento na construção
	void	RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& CaminhaoEmAnalise, int& ConstrucaoEmAnalise, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar);		// Retorna os dados de um certo descarregamento
	void	CalculaMakespan();			// Calcula o Makespan da construção

	int		AtrasaDemandasParaAtenderMaster( int NumDemanda, double HoraInicioAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao, ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int EscolhaVeiculo, int EscolhaPlanta, int imprime, string frase);		// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe a demanda não alocada ainda

	void	RecolocaTarefaDeletada( vector < DadosTarefa > &DadosTarefasMovidasAuxiliar, ConjuntoPlantas& Plantas, int imprime);
	void	AtrasaDemandasParaAtenderRecursao( int NumDemanda, double HoraInicioAtendiemnto, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int EscolhaVeiculo, int EscolhaPlanta,int imprime, string frase);			// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe as demandas que serão atrasadas para que a demanda não atendida possa ser atendida
	void	EncontraPlanta(  int& NumPlantaAnalisando, int EscolhaPlanta, ConjuntoPlantas& Plantas, string frase);					// encontra a planta mais perto da construção e que não tenha sido analisada antes
	int		AlocaAtividadeComHorarioFinalAtendimento( int NumDemanda, double HoraFimAtendimento, double &NovaHoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao,ConjuntoPlantas& Plantas, int EscolhaVeiculo,  int EscolhaPlanta, int imprime, string frase);			// aloca atividade sabedno que ela tem que começar em um certo hoario, este horaio é determinado pelo horaio que ela tem que terminar.

	int		VerificaIntegridadeDeDescrregamentos(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);			// verifica a integridade entre os descarregamentos da construção

	int		AlocaAtividadeComHorarioFinalAtendimentoComVeiculoFixo( int NumDemanda, int NumPlanta, int NumCarreta, double HoraFimAtendimento, double &NovaHoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar, int SituacaoDemanda, int StatusRemocao, ConjuntoPlantas& Plantas, int EscolhaVeiculo, int EscolhaPlanta, string frase);		// aloca atividade sabedno que ela tem que começar em um certo hoario, este horaio é determinado pelo horaio que ela tem que terminar. Nesse caso se tem que realizar o atendimeto com o veículo passado na função
	int		AtrasaDemandasParaAtenderMasterComVeiculoFixo( int NumDemanda, int NumPlanta, int NumCarreta, double HoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int EscolhaVeiculo, int EscolhaPlanta,int imprime, string frase);

	int		DemandaNaoAtendida( int &DemandaNaoAtendida);			// retorna a demanda não atendida na construção por parametro, retorna 1 se tive demanda não atendida e zero se a construção já tiver sido completamente atendida
	void	ImprimeContrucao(int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// Imprime os dados da construções

	bool HabilitaCinDeErro;

	~Construcao();

};

Construcao::Construcao(){
	NumeroDaConstrucao 	= -13;
	NumeroDemandas 		= -13;
	SituacaoDemanda.clear();
	SituacaoRemocao.clear();
	TempoMaximoEntreDescargas 	= -13;
	TempoMinimoDeFuncionamento 	= -13;
	TempoMaximoDeFuncionamento 	= -13;
	RankTempoDemandas 	= -13;
	StatusAtendimento 	= 0;
	Descarregamentos.clear();
	Makespan = -13;
	ConstrucaoAnalizada = -13;
	ConstrucaoPodeSerSuprida = -13;
	ConstrucaoComDemandasNaoAtendidas = -13;
	TempoDeVidaConcreto = -13;

	HabilitaCinDeErro = 1;
}

// Calcula o rank que decide qual construção será atendida inicialmente
void	Construcao::CalculaRankTempoDemandas(int comentarios){
	// calcula o rank de tempo por demadna
	RankTempoDemandas = ( TempoMaximoDeFuncionamento - TempoMinimoDeFuncionamento) / NumeroDemandas ;
	// escreve os ranks calculados
	if( comentarios == 1){
		printf( " Rank ( Tempo / Demandas ) = %.4f \n",RankTempoDemandas);
	}
}

// Verifica se da para colocar a demanda na construção, ela sinaliza se caso atrazar as demandas sejá possivel alocar a demanda.
int		Construcao::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	// variaveis que sinalizam se tem tarefa anterior ou posterior
	int 	PossuiTarefaAnterior;
	int 	PossuiTarefaPosterior;

	// inicializa como não tendo tarefa anterior ou posterior
	PossuiTarefaAnterior = 0;
	PossuiTarefaPosterior = 0;

	//int ParaPrograma;

	// verifica se respeita os intervalos de funcionamento da construção
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		// retorna zero, não respeita o tempo de funcionamento da construção
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		// retorna zero, não respeita o tempo de funcionamento da construção
		return 0;
	}

	// Verifica se a alocação da demanda irá violar a integridade do atendimento dos outros atendimentos
	for( int d = 0; d < StatusAtendimento; d ++){
		// Verifica se possivel alocação possui um descarregamento alocado dentro dela
		if( InicioPossivelAlocacao <= Descarregamentos[d].HorarioInicioDescarregamento){
			if ( Descarregamentos[d].HorarioFinalDescarregamento <= FinalPossivelAlocacao){
				// retorna zero, possui um descarregamento alocado dentro dela
				return 0;
			}
		}
		// Verifica se possivel alocação está dentro de um descarregamento alocado
		if( Descarregamentos[d].HorarioInicioDescarregamento <= InicioPossivelAlocacao){
			if ( FinalPossivelAlocacao <= Descarregamentos[d].HorarioFinalDescarregamento){
				// retorna zero, um descarregamento está alocado dentro dela
				return 0;
			}
		}
		// Verifica se possivel alocação está parcialmente dentro de um descarregamento alocado, no inicio do deslocamento já alocado
		if( InicioPossivelAlocacao <= Descarregamentos[d].HorarioInicioDescarregamento){
			if( Descarregamentos[d].HorarioInicioDescarregamento < FinalPossivelAlocacao ){
				// retorna zero, descarregamento está parcialmente alocado dentro de um outro descarregamento
				return 0;
			}
		}
		// Verifica se possivel alocação está parcialmente detro de um descarregamento, no fim do deslocamento já alocado
		if( InicioPossivelAlocacao < Descarregamentos[d].HorarioFinalDescarregamento){
			if (  Descarregamentos[d].HorarioFinalDescarregamento <= FinalPossivelAlocacao ){
				// retorna zero, descarregamento está parcialmente alocado dentro de um outro descarregamento
				return 0;
			}
		}
	}

	// se não tem nenhuma demanda atendida, se aloca a demanda
	if( StatusAtendimento == 0) {
		// retorna 1, é o primeiro descarregamento
		return 1;
	}else{
// verifica a situação dessa demanda com as outras demandas

		// percorre todas as demandas atendidas nesta construção
		for( int d = 0; d < StatusAtendimento; d++){
			// Verifica se tem demanda alocada  antes dessa tarefa e que respeita o intervalo entre descarregamentos
			if( Descarregamentos[d].HorarioFinalDescarregamento <= InicioPossivelAlocacao && InicioPossivelAlocacao <= Descarregamentos[d].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
				// possui descarremaneto antes dele
				PossuiTarefaAnterior = 1;
			}
			// Verifica se tem demanda alocada depois da alocação dessa tarefa e que respeita o intervalo entre descarregamentos
			if( FinalPossivelAlocacao <=  Descarregamentos[d].HorarioInicioDescarregamento &&  Descarregamentos[d].HorarioInicioDescarregamento   <= FinalPossivelAlocacao + TempoMaximoEntreDescargas ){
				// possui descarremaneto depois dele
				PossuiTarefaPosterior = 1;
			}
		}

// Sinaliza a possição dessa tarefa

		// Entra depois de todas as tarefas alocadas e que respeita o intervalo entre descarregamentos
		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 0){
			// retorna 1 se só tem descarregamento antes ele
			return 1;
		}

		// Entra no meio de duas tarefas alocadas e que respeita o intervalo entre descarregamentos
		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 1){
			//cout << endl << endl << " No meio das tarefas ->Construcao::VerificaDisponibilidade  " << endl << endl << endl;
			// retorna 2 se tem descarregamento após e antes dele
			return 2;
		}

		// Entra antes de todas as tarefas alocadas e que respeita o intervalo entre descarregamentos
		if ( PossuiTarefaAnterior == 0 && PossuiTarefaPosterior == 1){
			//cout << endl << endl << " Antes das tarefas ->Construcao::VerificaDisponibilidade  " << endl << endl << endl;
			// retorna 3 se só tem descarregamento depois dele
			return 3;
		}

		// Caso não respeita o intervalo de tempo necessario entre um descarregamento e outro sendo que ela seria colocada depois das outras demandas já alocadas.
		int 	TemTarefaAntes;
		// marca que só tem demanda após este
		TemTarefaAntes = 1;

		// percorre todos os descarregamentos
		for( int d = 0; d < StatusAtendimento; d ++){
			// verifica se tem descarregamento após ele
			if( Descarregamentos[d].HorarioFinalDescarregamento > InicioPossivelAlocacao ){
				// marca que não tem descarregamento só após este descarregamento
				TemTarefaAntes = 0;
			}
		}

		// Não se pode colocar a demanda pelo fato dela não respeitar o intervalo de atendimento, mas caso se atraze as demandas ela seria alocada
		if( TemTarefaAntes == 1){
			// sinaliza que se pode colocar a demanda caso se atrase as outras demandas
			return -2;
		}

		// Caso não seja possivel alocar a demanda e ela não está em nenhum dos casos acima.
		return -1;
	}
}

int 	Construcao::VerificaTempoDeVidaConcreto ( double HorarioChegaContrucao, double HorarioInicioPlanta){
	// verifica se o tempo entre a produção e o consumo do concreto respeita o tempo de vida do concreto
	if( ( HorarioChegaContrucao - HorarioInicioPlanta ) <= TempoDeVidaConcreto){
		// retorna 1 se sim
		return 1;
	}
	// retorna 0 se não
	return 0;

}

// Aloca uma demanda na cosntrução apartir de dados
int 	Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas){

// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <-<-<-<-<-<-<-  Erro! construcao [" << NumeroDaConstrucao << "] já suprida! StatusAtendimento " << StatusAtendimento << " = NumeroDemandas [" << NumeroDemandas << "] ->Construcao::AlocaAtividade ->->->->->->-> " << endl << endl;
		// retorna 0 caso a construção já tenha todas as suas demandas atendidas
		return 0;
	}

// Verifica se tem uma tarefa já alocada  e que atende a cosntrução em um horario depois desta
	int 	Encontrou;
	int 	NumDemanda;

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
	Descarregamentos[NumDemanda].HorarioInicioDescarregamento 	= HoraInicio;
	Descarregamentos[NumDemanda].HorarioFinalDescarregamento 	= HoraFinal;
	Descarregamentos[NumDemanda].NumCarretaUtilizada = Carreta;
	Descarregamentos[NumDemanda].NumPlantaFornecedor = NumPlanta;
	SituacaoDemanda[NumDemanda] = Situacao;
	SituacaoRemocao[NumDemanda] = StatusRemocao;

// atualiza o status de atendimento
	StatusAtendimento = StatusAtendimento + 1;

// Adiciona a tarefa na Planta e no Caminhão
	int 	p;
	int 	v;

// aloca indices para planta e veiculo
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0 || 	Plantas.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(Carreta,v) == 0){
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! Alocar indice planta [" << NumPlanta << "] => " << p << " ou veiculo [" << Carreta << "] => " << v << " ->Construcao::AlocaAtividade ->->->->->->->->->-> " << endl << endl;
		// retorna 0, pois não encontrou o indice da planta
		return 0;
	}

// aloca horarios
	double 	HorarioInicioPlanta;
	double 	HorarioFimPlanta;

	HorarioInicioPlanta = HoraInicio - Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

	double 	HorarioInicioCarreta;
	double 	HorarioFimCarreta;

	HorarioInicioCarreta = HorarioInicioPlanta;
	HorarioFimCarreta = HoraFinal + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];

// Aloca atividades no veiculo e depois na planta
	Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].AlocaAtividade( HorarioInicioCarreta, HorarioFimCarreta, NumeroDaConstrucao , NumDemanda);
	Plantas.Plantas[p].AlocaAtividade(HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao , NumDemanda,  Carreta);

	// alocou tarefa
	return 1;
}

// Aloca uma demanda na cosntrução apartir de dados, dalvando os dados da demanda alocada em estrutura DadosAdicionado
int		Construcao::AlocaAtividadeSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int Carreta, int NumPlanta, int Situacao, int StatusRemocao, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidas){

// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <-<-<-<-<-<-<-  Erro! construcao [" << NumeroDaConstrucao << "] já suprida! StatusAtendimento " << StatusAtendimento << " = NumeroDemandas [" << NumeroDemandas << "] ->Construcao::AlocaAtividadeSalvandoDados ->->->->->->-> " << endl << endl;
		// retorna 0 caso a construção já tenha todas as suas demandas atendidas
		return 0;
	}

// Verifica se tem uma tarefa já alocada  e que atende a cosntrução em um horario depois desta
	int 	Encontrou;
	int 	NumDemanda;

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
	Descarregamentos[NumDemanda].HorarioInicioDescarregamento 	= HoraInicio;
	Descarregamentos[NumDemanda].HorarioFinalDescarregamento 	= HoraFinal;
	Descarregamentos[NumDemanda].NumCarretaUtilizada = Carreta;
	Descarregamentos[NumDemanda].NumPlantaFornecedor = NumPlanta;
	SituacaoDemanda	[NumDemanda] = Situacao;
	SituacaoRemocao	[NumDemanda] = StatusRemocao;

// atualiza o status de atendimento
	StatusAtendimento = StatusAtendimento + 1;

// Adiciona a tarefa na Planta e no Caminhão
	int 	p;
	int 	v;

// aloca indices para planta e veiculo
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0 || 	Plantas.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(Carreta,v) == 0){
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! Alocar indice planta [" << NumPlanta << "] => " << p << " ou veiculo [" << Carreta << "] => " << v << " ->Construcao::AlocaAtividadeSalvandoDados ->->->->->->->->->-> " << endl << endl;
		// retorna 0, pois não encontrou o indice da planta
		return 0;
	}

// aloca horarios
	double 	HorarioInicioPlanta;
	double 	HorarioFimPlanta;

	HorarioInicioPlanta = HoraInicio - Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

	double	HorarioInicioCarreta;
	double 	HorarioFimCarreta;

	HorarioInicioCarreta = HorarioInicioPlanta;
	HorarioFimCarreta = HoraFinal + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];

// Aloca atividades no veiculo e depois na planta
	Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].AlocaAtividade( HorarioInicioCarreta, HorarioFimCarreta, NumeroDaConstrucao , NumDemanda);
	Plantas.Plantas[p].AlocaAtividade(HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao , NumDemanda,  Carreta);

// salva os dados da demanda que está sendo adicionada em estrutura DadosAdiciona
	if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosTarefasMovidas,NumeroDaConstrucao, NumPlanta, Carreta,  Situacao, StatusRemocao, HorarioInicioPlanta, HorarioFimPlanta, HoraInicio, HoraFinal, HorarioFimCarreta, 'a')  == 0 ){
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-   Problema em adicionar tarefa ao vetor de tarefas desalocadas -> Construcao::AlocaAtividadeSalvandoDados   ->->->->->->->->->-> " << endl << endl;// retorna 0 caso a construção já tenha todas as suas demandas atendidas
		// retorna 0, caso a tarefa já tenha sido salvada na estrutura de dados e ela não possa ser salva mais de uma vez nela
		return 0;
	}

	// alocou tarefa
	return 1;
}

// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos
int		Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas){

// Verifica se existe a demanda que se quer deletar
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! Demanda [" << NumDemanda << "] não existe ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas ->->->->->->->->->-> " << endl << endl;
		// retorna 0, pois a demanda que se quer deletar não existe
		return 0;
	}

// Verifica se existe a tarefa a ser deletada com os dados passados
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

// Deleta tarefa
		int 	p;
		// encontra o inidice da planta
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! planta [" << NumPlanta << "] não encontrada ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas ->->->->->->->->->-> " << endl << endl;
			// retorna 0 pois não se encontrou o indice da planta
			return 0;
		}

// aloca horarios
		double	HorarioInicioPlanta;
		double 	HorarioFimPlanta;

		HorarioInicioPlanta = HoraInicio - Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
		HorarioFimPlanta 	= HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

		double 	HorarioInicioCarreta;
		double 	HorarioFimCarreta;

		HorarioInicioCarreta 	= HorarioInicioPlanta;
		HorarioFimCarreta 		= HoraFinal + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];

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
		SituacaoDemanda	[ StatusAtendimento - 1] = 0;
		SituacaoRemocao	[ StatusAtendimento - 1] = 0;

		// atualiza o numero de demandas atendidas
		StatusAtendimento = StatusAtendimento - 1;

	}else{
		//caso não encontrou o descarregamento, se escreve os dados dele e retorna 0
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! Não se encontrou o descarreamento com os dados: Planta [" << NumPlanta << "], Carreta [" << Carreta << "]";
		cout << ", HoraInicio [" << HoraInicio << "],HoraFinal [" << HoraFinal << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas  ->->->->->->->->->-> " << endl << endl;
		// retorna 0, pois não se encontrou o descarregamento
		return 0;
	}
	// retorna 1, se conseguiu deletar o descarregamento
	return 1;

}

// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos, salvando os dados da tarefa removida em uma estrutura
int		Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(int VerificaExistencia, double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar){

	// variavel para parar o programa
	//int 	ParaPrograma;

// Verifica se a demanda que se quer deletar existe
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl;
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! Demanda [" << NumeroDaConstrucao << "-" << NumDemanda << "] não existe. StatusAtendimento ("<< StatusAtendimento << ") ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados ->->->->->->->->->-> " << endl << endl;
		cout << endl << endl;
		//if( HabilitaCinDeErro == 1){
			//cout << " Entre com um número para continuar : ";
			//cin >> ParaPrograma;
		//}
		// retorna 0, não se tem a demanda que se quer deletar
		return 0;
	}

	// Verifica se existe a tarefa a ser deletada com os dados passados
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

// Deleta tarefa
		int		p;
		// encontra o inidice da planta
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! planta [" << NumPlanta << "] não encontrada ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados ->->->->->->->->->-> " << endl << endl;
			// problema em encontrar o indice da planta
			return 0;
		}

// aloca horarios
		double 	HorarioInicioPlanta;
		double 	HorarioFimPlanta;

		HorarioInicioPlanta = HoraInicio - Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
		HorarioFimPlanta 	= HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;

		double 	HorarioInicioCarreta;
		double 	HorarioFimCarreta;

		HorarioInicioCarreta 	= HorarioInicioPlanta;
		HorarioFimCarreta 		= HoraFinal + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];

		/*
		cout << endl << endl << "  Dados tarefa " << endl << endl;

		cout << "  contrucao [" << NumeroDaConstrucao << "-" << NumDemanda << "] as " <<  HoraInicio << " até " << HoraFinal << endl;
		cout << "  planta [" << NumPlanta << "] as " << HorarioInicioPlanta << " até " << HorarioFimPlanta << endl;
		cout << "  carreta [" << Carreta << "] as " << HorarioInicioCarreta  << " até " << HorarioFimCarreta << endl << endl;
		 */

// Armazena tarefa deletada
		if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosTarefasMovidasAuxiliar, NumeroDaConstrucao, NumPlanta, Carreta, SituacaoDemanda[NumDemanda], SituacaoRemocao[NumDemanda],  HorarioInicioPlanta, HorarioFimPlanta, HoraInicio, HoraFinal, HorarioFimCarreta, 'r') == 0 ){
			cout << endl << endl << "   <-<-<-<-<-<-<-<-<-<-<-  Erro! - Problema em adicionar tarefa no vetor de tarefas desalocadas -> Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados ->->->->->->->->->-> " << endl << endl;
			// retorna 0, não se conseguiu alocar a tarefa na estrutura de dads passado
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
		SituacaoDemanda	[ StatusAtendimento - 1] = 0;
		SituacaoRemocao	[ StatusAtendimento - 1] = 0;

		// atualiza o numero de demandas atendidas
		StatusAtendimento = StatusAtendimento - 1;

	}else{
		//caso não encontrou o descarregamento, se escreve os dados dele e retorna 0
		cout << endl << endl << "    <-<-<-<-<-<-<-<-<-<-<-   Erro! Descarregamento não existe. Dados: Planta [" << NumPlanta << "], Carreta [" << Carreta << "]";
		cout << ", HoraInicio [" << HoraInicio << "],HoraFinal [" << HoraFinal << "] ->Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados ->->->->->->->->->-> " << endl << endl;
		//  retorna 0, não se tem a demanda que se quer retirar
		return 0;
	}
	// retorna 1, demanda deletada com sucesso
	return 1;
}


// Deleta tarefas da demanda passada e as posteriores a esta demanda passada, ela salva as tarefas deletadas em estrutura
int		Construcao::DeletaTarefas(int VerificaExistencia, int demanda, vector < DadosTarefa > &DadosTarefasMovidas, ConjuntoPlantas& Plantas){
	// variaveis que armazenam a planta e a carreta da demanda deletada
	int 	Planta;
	int 	Carreta;

	// variavel que armazena indice da planta
	int		p;
	// variavel que armazena o numero de demandas retiradas
	int 	DemandasRetiradas;

	// variaveis que armazenam os horarios da cosntrução
	double 	HorarioInicioConstrucao;
	double 	HorarioFinalConstrucao;

	// variaveis que armazenam os horarios da planta
	double 	HorarioInicioPlanta;
	double 	HorarioFimPlanta;

	// variaveis que armazenam os horarios da carreta
	double 	HorarioInicioCarreta;
	double 	HorarioFimCarreta;

	// inicializa o contador de tarefas retiradas com zero
	DemandasRetiradas = 0;

// verifica se a demanda que se quer tirar está alocada na construção
	if( StatusAtendimento - 1 < demanda){
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! Demanda [" << demanda << "] não está alocada ->Construcao::DeletaTarefas ->->->->->->->->->-> " << endl << endl;
		// retorna 0, demanda que se quer começar a deletar não existe na cosntrução
		return 0;
	}

// se retira as tarefas da demanda que se quer e as posteriores a ela

	// se percorre todas as demandas apos a demanda passada, incluindo a demanda passada
	for( int d = demanda; d < StatusAtendimento; d++){
		// guarda a planta da tarefa
		Planta = Descarregamentos[d].NumPlantaFornecedor;
		// se pega o inidice da planta
		if( Plantas.AlocaInidiceFabrica( Planta, p) == 0) {
			cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<- Erro! planta [" << Planta << "] não encontrada ->Construcao::DeletaTarefas ->->->->->->->->->-> " << endl << endl;
			// retorna 0, não encontrou o indice da planta
			return 0;
		}
		// armazena a carreta da terafa
		Carreta = Descarregamentos[d].NumCarretaUtilizada;
		// armazena os horarios da construção referente a tarefa
		HorarioInicioConstrucao = Descarregamentos[d].HorarioInicioDescarregamento;
		HorarioFinalConstrucao  = Descarregamentos[d].HorarioFinalDescarregamento;
		// armazena os horarios da plana referente a tarefa
		HorarioInicioPlanta 	= HorarioInicioConstrucao - Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
		HorarioFimPlanta 		= HorarioInicioPlanta +  Plantas.Plantas[p].TempoPlanta;
		// armazena os horarios da carreta referente a tarefa
		HorarioInicioCarreta 	= HorarioInicioPlanta;
		HorarioFimCarreta 		= HorarioFinalConstrucao + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];

		/*
		cout << endl << endl << "  Dados tarefa " << endl << endl;

		cout << "  contrucao [" << NumeroDaConstrucao << "-" << NumDemanda << "] as " <<  HoraInicio << " até " << HoraFinal << endl;
		cout << "  planta [" << NumPlanta << "] as " << HorarioInicioPlanta << " até " << HorarioFimPlanta << endl;
		cout << "  carreta [" << Carreta << "] as " << HorarioInicioCarreta  << " até " << HorarioFimCarreta << endl << endl;
		 */

		// Adiciona na estrutura a terefa retirada
		if( AdicionaElementoVetorDadosTarefa(VerificaExistencia, DadosTarefasMovidas,NumeroDaConstrucao, Planta, Carreta, SituacaoDemanda[d], SituacaoRemocao[d], HorarioInicioPlanta, HorarioFimPlanta,HorarioInicioConstrucao, HorarioFinalConstrucao, HorarioFimCarreta, 'r') == 0 ){
			cout << endl << endl << " <-<-<-<-<-<-<-<-<-<-<- Problema em adicionar tarefa a vetor de tarefas desalocadas -> Construcao::DeletaTarefas ->->->->->->->->->->" << endl << endl;
			// retorna 0, não se conseguiu adicionar a tarefa na estrutura passada
			return 0;
		}

		// Deleta tarefa na planta e no caminhão
		Plantas.DeletaTarefa( Planta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, d, Carreta, HorarioInicioCarreta, HorarioFimCarreta);
		// Deleta tarefa na construção
		Descarregamentos[d].AnulaConteudo();
		SituacaoDemanda	[d] = 0;
		SituacaoRemocao	[d] = 0;

		// aumenta o contador das tarefas deletadas
		DemandasRetiradas++;
	}

	// atualiza o nivel de atendimento com o número de demandas atendidas na planta
	StatusAtendimento = StatusAtendimento - DemandasRetiradas;
	// retorna 1, se conseguiu deletar as tarefas
	return 1;

}

// deleta tarefa apartir de dados
int		Construcao::DeletaTarefasAnteriormenteAdicionadasDados(   DadosTarefa DadosAdicionados, ConjuntoPlantas& Plantas){
	// demanda a deletar
	int 	demanda;
	// variavel que controla se encontrou a demanda
	int 	ativo;
	// inicia como se não tivesse encontrado a demanda
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
		cout << endl << endl << "  	  <-<-<-<-<-<-<-<-<-<-<- Probelma em deletar tarefa. Não encontrou tarefa a se deletar ->Construcao::DeletaTarefasAnteriormenteAdicionadasDados ->->->->->->->->->-> " << endl;
		DadosAdicionados.Imprimir();
		cout << endl << endl;
		// probelma em encontrar a demanda a deletar, retorna 0
		return 0;
	}

	// coleta dasdos da tarefa
	int NumPlanta;
	int Carreta;

	NumPlanta 	= DadosAdicionados.DadosDasTarefas[1];
	Carreta 	= DadosAdicionados.DadosDasTarefas[2];

	// Deleta tarefa
	int p;
	// pega o inidice da planta
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
		cout << endl << endl << "  <-<-<-<-<-<-<-<-<-<-<-  Erro! planta [" << NumPlanta << "] não encontrada ->Construcao::DeletaTarefasAnteriormenteAdicionadasDados  ->->->->->->->->->-> " << endl << endl;
		// probelma em encontrar o indice da planta, retorna 0
		return 0;
	}

	// aloca horarios
	double HorarioInicioPlanta;
	double HorarioFimPlanta;
	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	HorarioInicioPlanta  = DadosAdicionados.HorariosDasTarefas[0];
	HorarioFimPlanta 	 = DadosAdicionados.HorariosDasTarefas[1];
	HorarioInicioCarreta = DadosAdicionados.HorariosDasTarefas[0];
	HorarioFimCarreta    = DadosAdicionados.HorariosDasTarefas[4];


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
	SituacaoDemanda	[ StatusAtendimento - 1] = 0;
	SituacaoRemocao	[ StatusAtendimento - 1] = 0;

	// atualiza o nivel de atendimento
	StatusAtendimento = StatusAtendimento - 1;

	// tarefas deletadas corretamente
	return 1;

}

// Verifica se os descrarregamentor na construção estão respeitando os intervalos entre elas
int		Construcao::VerificaDescarregamentosRespeitaIntervalo(){
	// caso existir mais de uma tarefa
	if( StatusAtendimento > 1){
		// percorre todas as tarefas apos a primeira
		for( int d = 1; d < StatusAtendimento; d++){
			// verifica se o intervalo é respeitado
			if( Descarregamentos[d].HorarioInicioDescarregamento - Descarregamentos[d -1].HorarioFinalDescarregamento > TempoMaximoEntreDescargas){
				// não respeita intervalo
				return 0;
			}
		}
	}
	// respeita intervalo
	return 1;
}

// retorna o horario de inicio de um certo descarregamento na construção
void	Construcao::RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio){
	// sinaliza se encontrou o descarregamento
	int 	ativa;
	// inicia como se não tivesse encontrado o descarregamento
	ativa = 0;

	// percorre todos os descarregamento
	for(  int d = 0; d < (int) Descarregamentos.size(); d++){
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
		cout << endl << endl <<  " <-<-<-<-<-<-<-<-<-<-<- Erro! Não encontrou a demanda [" << NumDemanda << "] -> Construcao::RetornaHorarioInicioCarregamento ->->->->->->->->->-> " << endl << endl;
	}
}

// Retorna os dados de um certo descarregamento
void	Construcao::RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& 	CaminhaoEmAnalise, int& ConstrucaoEmAnalise, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar){

	PlantaEmAnalise 		=	Descarregamentos[d].NumPlantaFornecedor;
	CaminhaoEmAnalise 		=	Descarregamentos[d].NumCarretaUtilizada;
	ConstrucaoEmAnalise 	= 	NumeroDaConstrucao;
	HorarioInicioAuxiliar 	= 	Descarregamentos[d].HorarioInicioDescarregamento;
	HorarioFinalAuxiliar 	= 	Descarregamentos[d].HorarioFinalDescarregamento;
}

// Calcula o Makespan da construção
void	Construcao::CalculaMakespan(){
	// inicia o makespan como zero
	Makespan = 0 ;

	//cout << endl << endl << "  Contrucao " << NumeroDaConstrucao << endl;



	// passa por todos os descarregamentos da construção
	for( int d = 0; d < (int) Descarregamentos.size(); d++){
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


// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe a demanda não alocada ainda
int		Construcao::AtrasaDemandasParaAtenderMaster( int NumDemanda, double HoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int EscolhaVeiculo, int EscolhaPlanta, int imprime, string frase){

	// ****************** Variaveis que precisão ser removidas, pois não tem utilidade na função ***************************//

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int 	ImprimeArquivo;
	ImprimeArquivo = 0;
	// variavel que imprime se ira escrever os dados da solução na tela
	int 	ImprimeSolucao;
	ImprimeSolucao = 1;

	// ********************************************************************************************************************//


	// aramazena o valor auxiliar do horario final de atendiemnto na construção caso for adotado se possibilita o atendimento da demanda
	double 	NovaHoraFimAtendimento;

	if( imprime == 1){
		cout  << endl << "     ====================== Entra Master [" << NumeroDaConstrucao << "-" << NumDemanda << "] ====================== "  << endl << endl;

		ImprimeContrucao( ImprimeSolucao,ImprimeArquivo,Arquivo);
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
	}

	// aloca valor de situaçãAlocação como sendo que a tarefa que ainda naõ foi alocada pode ser alocada caso se atraze o atendimento das tarefas que são anteriores a ela
	SituacaoAlocacao = -2;

	// enquanto se puder atender a demanda coeernte se atrazar as outras, se continua no loop
	while(SituacaoAlocacao == -2 ){

		if( imprime == 1){
			cout << endl << " ===>>>>>>>>>>> while do Master  <<<<<<<<<<<<<<=== " << endl << endl;
		}

		// tenta atrazar as demandas anteriores para possibilitar o atendimento da demand corrente
		AtrasaDemandasParaAtenderRecursao( NumDemanda, HoraFimAtendimento,  DadosTarefasMovidasAuxiliar,  Plantas, SituacaoAlocacao, EscolhaVeiculo,  EscolhaPlanta,imprime, frase);

		if( SituacaoAlocacao == 1){

			if( imprime == 1){
				cout << endl << endl << " while -> Tenta adicionar a demanda  [" << NumeroDaConstrucao << "-" << NumDemanda << "] com horario final (" << HoraFimAtendimento << ")" << endl << endl;
			}

			// verifica se pode atender a demanda corrente
			SituacaoAlocacao = AlocaAtividadeComHorarioFinalAtendimento( NumDemanda, HoraFimAtendimento, NovaHoraFimAtendimento, DadosTarefasMovidasAuxiliar, SituacaoDemanda, StatusRemocao, Plantas,EscolhaVeiculo,EscolhaPlanta,imprime, frase);
			// caso ainda de para atender a demanda se atrasar as demandas anteriores entra no if
			if(SituacaoAlocacao == -2 ){
				// se atualiza a hora que se tem que atender a tarefa anterior a tarefa corrente que se quer alocar
				HoraFimAtendimento = NovaHoraFimAtendimento;
			}
		}
	}

	if( imprime == 1){
		ImprimeContrucao(ImprimeSolucao,ImprimeArquivo,Arquivo);
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

void	Construcao::RecolocaTarefaDeletada( vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,ConjuntoPlantas& Plantas, int imprime){
	int 	Posicao;
	//PonteiroArquivo  Arquivo;

	double 	HoraInicio;
	double 	HoraFinal;
	int 	Carreta;
	int 	NumPlanta;
	int 	Situacao;
	int 	StatusRemocao;

	Posicao = DadosTarefasMovidasAuxiliar.size() - 1;

	if( imprime == 1){
		printf ("            Reinsere \n");
		printf (" < %c >  ", DadosTarefasMovidasAuxiliar[Posicao].Status);
		printf (" Planta [%d]",DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[1] );
		printf (" tempo (%.4f-%.4f)", DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[0], DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[1]);
		printf (" Construcao [%d]",DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[0]);
		printf (" tempo (%.4f-%.4f) ", DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[2], DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[3]);
		printf (" Caminhao [%d-%d]",DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[1], DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[2]);
		printf (" tempo (%.4f-%.4f)", DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[0], DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[4]);
		printf (" Situação [%d], Status Remocao [%d]\n\n", DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[3], DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[4]);
	}

	HoraInicio 		= DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[2];
	HoraFinal 		= DadosTarefasMovidasAuxiliar[Posicao].HorariosDasTarefas[3];
	Carreta 		= DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[2];
	NumPlanta 		= DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[1];
	Situacao 		= DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[3];
	StatusRemocao 	= DadosTarefasMovidasAuxiliar[Posicao].DadosDasTarefas[4];

	AlocaAtividade(HoraInicio, HoraFinal, Carreta, NumPlanta,  Situacao, StatusRemocao, Plantas);
	//ImprimeContrucao(1, 0, Arquivo);


	DadosTarefasMovidasAuxiliar.pop_back();
}

// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe as demandas que serão atrasadas para que a demanda não atendida possa ser atendida
void	Construcao::AtrasaDemandasParaAtenderRecursao( int NumDemanda, double HoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int EscolhaVeiculo, int EscolhaPlanta, int imprime, string frase){

	// ****************** Variaveis que precisão ser removidas, pois não tem utilidade na função *************************** //

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int 	ImprimeArquivo;
	ImprimeArquivo = 0;
	// variavel que imprime se ira escrever os dados da solução na tela
	int 	ImprimeSolucao;
	ImprimeSolucao = 1;

	// ******************************************************************************************************************** //


	// aramazena o valor auxiliar do horario final de atendiemnto na construção caso for adotado se possibilita o atendimento da demanda
	double 	NovaHoraFimAtendimento;
	// aramzena os valores da situação da demanda e a situação remoção da demanda retirada, para que quando a demanda for readicionada ela tenha os mesmo valores para esses campos que era anteriorment
	int 	SituacaoDemandaAux;
	int 	SituacaoRemocaoAux;

	int 	DeletouDemanda;

	// variavel de input para parar o programa
	int 	ParaPrograma;

	if( imprime == 1){
		cout << endl << endl << "     ++++++++++++++++ Entra Sub Recursão [" << NumeroDaConstrucao << "-" << NumDemanda - 1 << "] +++++++++++++++ "  << endl << endl;

		ImprimeContrucao(ImprimeSolucao,ImprimeArquivo,Arquivo);
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

		cout << endl << endl << "        ->->->->->->->-> Atrasa Demandas Para Atender  Demanda [" << NumeroDaConstrucao << "-" << NumDemanda << "] - Deleta a demanda [" << NumeroDaConstrucao << "-" << NumDemanda -1 << "] tem que terminar de ser atendida as " << HoraFimAtendimento << endl << endl;
	}
	// armazena a situação demanda e remoção antes de deletar a demanda
	SituacaoDemandaAux = SituacaoDemanda[NumDemanda-1];
	SituacaoRemocaoAux = SituacaoRemocao[NumDemanda-1];

	// confere se tem mais demanda que se deveria ter
	if( StatusAtendimento > NumDemanda){
		cout << endl << endl << "            >>>>>>>>>>>>>>###### Problema! Tem mais descarregamentos do que deveria! StatusAtendimento [" << StatusAtendimento << "] NumDemanda [" << NumDemanda << "] -> Construcao::AtrasaDemandasParaAtenderRecursao " << endl << endl;
		ImprimeContrucao(1,0,Arquivo);
		cout << endl << endl;
		if( HabilitaCinDeErro == 1){
			cout << " Entre com um número para continuar : ";
			cin >> ParaPrograma;
		}
	}

	//Deleta a demanda anterior (NumDemanda-1) a demanda que não se consegue alocar
	DeletouDemanda = DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(0, Descarregamentos[NumDemanda-1].HorarioInicioDescarregamento, Descarregamentos[NumDemanda-1].HorarioFinalDescarregamento, NumDemanda - 1, Descarregamentos[NumDemanda-1].NumPlantaFornecedor  , Descarregamentos[NumDemanda-1].NumCarretaUtilizada , Plantas, DadosTarefasMovidasAuxiliar);

	if( DeletouDemanda == 1){

		if( imprime == 1){
			ImprimeContrucao(ImprimeSolucao,ImprimeArquivo,Arquivo);
			cout << "DadosTarefasMovidasAuxiliar" << endl;
			ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

			//cin >> ParaPrograma;

			cout << endl << endl << "  *****  Tenta adicionar demanda [" << NumeroDaConstrucao << "-" << NumDemanda -1 << "] respeitando o intervalo e terminando depois de (" << HoraFimAtendimento << ")" << endl << endl;
		}
	// Tenta alocar a demanda que foi retirada ( NumDemanda-1) em um horario que permite o atendiemnto da demanda atual (NumDemanda)
		SituacaoAlocacao = AlocaAtividadeComHorarioFinalAtendimento( NumDemanda - 1, HoraFimAtendimento, NovaHoraFimAtendimento, DadosTarefasMovidasAuxiliar,SituacaoDemandaAux,SituacaoRemocaoAux,  Plantas,  EscolhaVeiculo,  EscolhaPlanta, imprime, frase);
		if( imprime == 1){
			cout << endl << endl << "             A Demanda [" << NumDemanda - 1 << "] após processo tem o SituacaoAlocacao valor de [" << SituacaoAlocacao << "] com o novo horario de fim de (" << NovaHoraFimAtendimento << ")" << endl << endl;
			ImprimeContrucao(ImprimeSolucao,ImprimeArquivo,Arquivo);
			cout << "DadosTarefasMovidasAuxiliar" << endl;
			ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
			if( HabilitaCinDeErro == 1){
				cout << " Entre com um número para continuar : ";
				cin >> ParaPrograma;
			}
		}

		if( SituacaoAlocacao == -2){

	// Atualiza o horario de inicio que a nova demanda anterior temq eu ter
			HoraFimAtendimento = NovaHoraFimAtendimento;
	// só entra para ver se vai no loop caso a demanda corrente no novo loop ( NumDemanda-1) for maior que 0, pois só se for maior que zero ela tera uma tarefa anterior para ser deslocada no procedimento AlocaAtendimentoComHorarioInicio
			//if( NumDemanda - 1 > 0){
				// só entra no loop caso se puder atender a tarefa ( NumDemanda-1) caso se atrazar o atendiment de demandas anteriores
				if( imprime == 1){
					cout << endl << endl << "             While Entra recursão da demanda [" << NumDemanda - 1 << "]" << endl << endl;
				}

				while( SituacaoAlocacao == -2  ){
					// chama a função recursivamente para tentar atrazar a demanda que vem antes da demanda corrente. Isto é para possibilitar colocar a demanda corrente respeitando o tempo para atender a demanda após a demanda corrente
					AtrasaDemandasParaAtenderRecursao( NumDemanda - 1, HoraFimAtendimento,  DadosTarefasMovidasAuxiliar,Plantas, SituacaoAlocacao,  EscolhaVeiculo,  EscolhaPlanta, imprime, frase);
					// caso conseguiu alocar a demanda antes da demanda corrente na função recursiva acima, entra no if
					if( SituacaoAlocacao == 1){
						// tenta alocar a demanda corrente
						SituacaoAlocacao = AlocaAtividadeComHorarioFinalAtendimento( NumDemanda, HoraFimAtendimento, NovaHoraFimAtendimento, DadosTarefasMovidasAuxiliar, SituacaoDemandaAux,SituacaoRemocaoAux, Plantas,  EscolhaVeiculo, EscolhaPlanta, imprime, frase);
						// caso ainda de para atender a demanda se atrasar as demandas anteriores entra no if
						if(SituacaoAlocacao == -2 ){
							// armazena a hora que se tem que atender a demanda anterior para ser possivel atender a demanda corrente
							HoraFimAtendimento = NovaHoraFimAtendimento;
						}
					}
				}

				if( imprime == 1){
					cout << endl << endl << "             While sai recursão da demanda [" << NumDemanda - 1 << "] SituacaoAlocacao [" << SituacaoAlocacao << "]" << endl << endl;
				}

			//}

			if( imprime == 1){
				ImprimeContrucao(ImprimeSolucao,ImprimeArquivo,Arquivo);
				cout << "DadosTarefasMovidasAuxiliar" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
				cout << endl << endl << "  ++++++++++++++++ Sai Sub Recursão dentro [" << NumeroDaConstrucao << "-" << NumDemanda - 1 << "] SituacaoAlocacao (" << SituacaoAlocacao << ") ++++++++++++++++ " << endl << endl;
				cin >> ParaPrograma;
			}
		}

	}else{
		cout << endl << endl << endl << "         >>>>>>>>>>>>>>######  Probelma em deletar tarefa [" << NumeroDaConstrucao << "-" << NumDemanda - 1 << "]" << endl << endl << endl;
		if( HabilitaCinDeErro == 1){
			cout << " Entre com um número para continuar : ";
			cin >> ParaPrograma;
		}
	}
}

// encontra a planta mais perto da construção e que não tenha sido analisada antes
void	Construcao::EncontraPlanta(  int& NumPlantaAnalisando, int EscolhaPlanta, ConjuntoPlantas& Plantas, string frase){

	if( EscolhaPlanta == 1){
		// variavel que armazena a distancia da construção a planta usada para se encontra a planta mais proxima
		double 	TempoConstrucaoPlanta;

		// inicializa as variaveis
		NumPlantaAnalisando 		= -13;
		TempoConstrucaoPlanta 	= DBL_MAX;

		// percorre todas as plantas
		for( int p = 0; p < (int) Plantas.Plantas.size(); p++){
			if( TempoConstrucaoPlanta > TempoParaPlantas[p].Tempo){
				// planta que ainda não foi analisada
				if( Plantas.Plantas[p].PlantasAnalizadas == 0){
					// passa o numero da planta escolhida
					NumPlantaAnalisando = p;
					// atualiza a distancia da planta mais proxima a construção
					TempoConstrucaoPlanta = TempoParaPlantas[p].Tempo;
				}
			}
		}

		// caso não encontre nenhuma planta
		if(NumPlantaAnalisando == -13){
			cout << endl << endl << endl << "      ++++++++++++++++ Probelma encontrar planta : " << frase << endl << endl << endl;
		}
		return;
	}

	if( EscolhaPlanta == 2){
		Plantas.OrdenaPlantas( EscolhaPlanta);
		// percorre todas as plantas
		for( int p = 0; p < (int) Plantas.Plantas.size(); p++){
			if( Plantas.Plantas[p].PlantasAnalizadas == 0){
				// passa o numero da planta escolhida
				NumPlantaAnalisando = p;
				return;
			}
		}
	}

	if( EscolhaPlanta == 3){
		Plantas.OrdenaPlantas( EscolhaPlanta);
		// percorre todas as plantas
		for( int p = 0; p < (int) Plantas.Plantas.size(); p++){
			if( Plantas.Plantas[p].PlantasAnalizadas == 0){
				// passa o numero da planta escolhida
				NumPlantaAnalisando = p;
				return;
			}
		}
	}

	if( EscolhaPlanta == 4){
		Plantas.OrdenaPlantas( EscolhaPlanta);
		// percorre todas as plantas
		for( int p = 0; p < (int) Plantas.Plantas.size(); p++){
			if( Plantas.Plantas[p].PlantasAnalizadas == 0){
				// passa o numero da planta escolhida
				NumPlantaAnalisando = p;
				return;
			}
		}
	}

	cout << endl << endl << endl << "  ************* Probelma em encontrar planta *************" << endl << endl << endl;

}


// aloca atividade sabedno que ela tem que começar em um certo horario, este horaio é determinado pelo horaio que ela tem que terminar.
int		Construcao::AlocaAtividadeComHorarioFinalAtendimento( int NumDemanda, double HoraFimAtendimento, double &NovaHoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar, int SituacaoDemanda, int StatusRemocao, ConjuntoPlantas& Plantas,  int EscolhaVeiculo,  int EscolhaPlanta, int imprime, string frase){
	// armazena os horarios de uma tarefa
	double 	HorarioInicioPlanta;
	double 	HorarioSaiDaPlanta;
	double 	HorarioRetornaPlanta;
	double 	HorarioChegaContrucao;
	double 	HorarioSaiConstrucao;
	// arqmazena os estados de disponibilidade da tarefa na planta, na coonstrução e no caminhão
	int 	DisponibilidadePlanta;
	int 	DisponibilidadeConstrucao;
	int 	DisponibilidadeCarreta;
	int 	DisponibilidadeVidaConcreto;
	// numero da planta que é analisada no momento
	int 	IndPlantaAnalisando;

	//int ParaPrograma;

	//PonteiroArquivo  Arquivo;

	// inicia o vetor que armazena os horariso que as plantas podem atender a demanda
	Plantas.InicializaVetorHorarioQuePlantaPodeAtender();

	if( imprime == 1){
		cout << endl << endl<< "      -++++ Aloca a demanda [" << NumeroDaConstrucao << "-" << NumDemanda << "] com final as (" << HoraFimAtendimento << ") no maximo de (" << TempoMaximoDeFuncionamento << ")" << endl;
	}

	//int ParaPrograma;

	// verifica se a cosntrução já não teve todas as suas demandas atendidas
	if ( NumeroDemandas > StatusAtendimento){
		// faz que nenhuma planta tenha sido analisada
		Plantas.InicializaPlantasAnalizadas();
		// repetir o procedimento enquanto tiver plantas a analisar
		while( Plantas.AnalizouTodasPLanats() == 0){
			// encontra a planta mais proxma da cosntrução e que ainda não foi atendida
			EncontraPlanta( IndPlantaAnalisando, EscolhaPlanta, Plantas, "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  ->Construcao::AlocaAtividadeComHorarioFinalAtendimento( &&&&&&&&&&&&& ");

			// ordena as carretas da planta de acordo com as tarefas realizadas
			Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretas(EscolhaVeiculo);
			// percorre por todos os veiculos da planta
			for( int v = 0; v < Plantas.Plantas[IndPlantaAnalisando].NumeroVeiculos; v++){

				/*
				 * versão 1
				// atualiza o horario inicial que a planta pode atender a demanda
				HorarioInicioPlanta 	= HoraFimAtendimento - Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda] -  Plantas.Plantas[IndPlantaAnalisando].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[IndPlantaAnalisando].TempoPlanta;
				HorarioChegaContrucao 	= HoraFimAtendimento - Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda];
				 */

				HorarioChegaContrucao 	= HoraFimAtendimento - Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda];
				HorarioInicioPlanta 	= HorarioChegaContrucao -  Plantas.Plantas[IndPlantaAnalisando].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[IndPlantaAnalisando].TempoPlanta;

				// realizar até o horario inicio da planta ou da construção não ultrapassar o limite de atendidmento da planta ou da construção respectivamente
				while( HorarioInicioPlanta <= Plantas.Plantas[IndPlantaAnalisando].TempoMaximoDeFuncionamento &&  HorarioChegaContrucao <= TempoMaximoDeFuncionamento){
					// atualiza os horarios na construção e planta
					HorarioSaiDaPlanta 			= HorarioInicioPlanta 	+ Plantas.Plantas[IndPlantaAnalisando].TempoPlanta;
					HorarioChegaContrucao 		= HorarioSaiDaPlanta 	+ Plantas.Plantas[IndPlantaAnalisando].TempoParaConstrucoes[NumeroDaConstrucao];
					HorarioSaiConstrucao 		= HorarioChegaContrucao +  Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda];
					HorarioRetornaPlanta 		= HorarioSaiConstrucao 	+ Plantas.Plantas[IndPlantaAnalisando].TempoParaConstrucoes[NumeroDaConstrucao];
					// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta, verifica tempo de vida concreto
					DisponibilidadePlanta 		= Plantas.Plantas[IndPlantaAnalisando].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
					DisponibilidadeConstrucao 	= VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
					DisponibilidadeCarreta 		= Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
					DisponibilidadeVidaConcreto = VerificaTempoDeVidaConcreto ( HorarioChegaContrucao, HorarioInicioPlanta);
					// caso se puder realizar a terefa se entra nos If

					if( DisponibilidadeVidaConcreto == 1){
						if( DisponibilidadePlanta == 1){
							if( DisponibilidadeCarreta == 1){
								if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
									// se consegue atender a demanda com essa planta, carreta e nessa construção
									AlocaAtividadeSalvandoDados(0, HorarioChegaContrucao, HorarioSaiConstrucao, Plantas.Plantas[IndPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, Plantas.Plantas[IndPlantaAnalisando].NumeroDaPlanta, SituacaoDemanda, StatusRemocao, Plantas, DadosTarefasMovidasAuxiliar);
									//ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1; ( não se aplica isso, pois se entra na equação d erecorrencia
									// se conseguiu atender a demanda, se retorna 1
									return 1;
								}else{
									// caso se consiga atender a demanda caso se atrase as demandas atendidas anteriormente na construção, se entra no if
									if( DisponibilidadeConstrucao == -2){

										//cout <<  "                     Caso atrazar da para alocar, demanda em analise [" << NumeroDaConstrucao << "-" << NumDemanda << "] no horario " << HorarioChegaContrucao << endl;

										// caso a planta ainda não foi analisada, entra no if
										if( Plantas.Plantas[IndPlantaAnalisando].HorarioQueConstrucaoPodeReceberDemanda > HorarioChegaContrucao){
											// atualiza a hora de inicio que a planta pode atender a demanda e a construção pode ser atendida
											Plantas.Plantas[IndPlantaAnalisando].HorarioQuePlantaPodeAtender 			= HorarioInicioPlanta;
											Plantas.Plantas[IndPlantaAnalisando].HorarioQueConstrucaoPodeReceberDemanda = HorarioChegaContrucao;
										}
										// marca no vetor de estado da planta para o atendiemnto  que a planta corrente pode atender a demanda caso se atrase as demandas atendidas anteriormente a demanda corrente na construção
										Plantas.Plantas[IndPlantaAnalisando].PlantasAnalizadas = -2;
										// se coloca o limite de tempo que a planta pode atender a demanda na variavel para se sair do loop
										HorarioInicioPlanta = Plantas.Plantas[IndPlantaAnalisando].TempoMaximoDeFuncionamento + IntervaloDeTempo;
									}
								}
							}
						}
					}
					// acrescenta o horario inicio que ira começar o carregamento na planta
					HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
				}
			}
			if (Plantas.Plantas[IndPlantaAnalisando].PlantasAnalizadas 	!= -2){
				Plantas.Plantas[IndPlantaAnalisando].PlantasAnalizadas 	= 1;
			}
		}

		if( imprime == 1){
			Plantas.ImprimeHorariosPlantasPodemAtender();
		}

		// caso se dê para atender caso atrazar os otros atendiemntos se enra na função
		if( Plantas.VerificaPlantasAnalizadasPodemAtenderSeAtrasar() == 1){
			// se fornece o horario que a demanda anterior a está tem que terminar pelo menos
			NovaHoraFimAtendimento = Plantas.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() - TempoMaximoEntreDescargas + IntervaloDeTempo;
			// retorna -2 para indicar que se pode atender a demada caso se atrasa-la
			return -2;
		}
		// não da para atender a demanda
		return 0;

	}else{
		cout << endl << endl << endl << "   >>>>>>>>>>>>>>>  Problema! -> Construcao [" << NumeroDaConstrucao << "-" << NumDemanda << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		// retorna 0 caso a demanda a se adicionar já tenha sido atendida
		return 0;
	}
	// não se consegue atender a demanda, retorna zero
	return 0;

}

// verifica a integridade entre os descarregamentos da construção
int 	Construcao::VerificaIntegridadeDeDescrregamentos(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// percorre todos os deslocamentos
	for( int d1 = 0; d1 < (int)  Descarregamentos.size(); d1++){
		// verifica se o descarregaento não possui tempo negativo
		if( Descarregamentos[d1].HorarioInicioDescarregamento > Descarregamentos[d1].HorarioFinalDescarregamento ){
			//if ( ImprimeSolucao == 1){
				printf( " >>>>>>>>>>>>>> Problema! Descarregamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Descarregamentos[d1].HorarioFinalDescarregamento - Descarregamentos[d1].HorarioInicioDescarregamento  , Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
			//}
			if ( ImprimeArquivo == 1){
				fprintf( Arquivo, " >>>>>>>>>>>>>> Problema! Descarregamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Descarregamentos[d1].HorarioFinalDescarregamento - Descarregamentos[d1].HorarioInicioDescarregamento  , Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
			}
			// probelma com o tempo do descarregamento, retorna 0
			return 0;
		}
		// percorre todos os deslocamentos
		for( int d2 = 0; d2 < (int) Descarregamentos.size(); d2++){
			// o descarregamento não pode ser o memso que o analisado no primeiro loop
			if( Descarregamentos[d1].HorarioInicioDescarregamento != Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento != Descarregamentos[d2].HorarioFinalDescarregamento){
				// verifica se o descarregamento está contido dentro de outro descarregamento
				if( Descarregamentos[d1].HorarioInicioDescarregamento <= Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento >= Descarregamentos[d2].HorarioFinalDescarregamento ){
					//if ( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento, Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
					//}
					if ( ImprimeArquivo == 1){
						fprintf( Arquivo," >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento, Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
					}
					// probelma com descarregamento que viala outro descarregamento, o descarregamento contem outro descarregamenbto. retorna 0
					return 0;
				}
				// verifica se o descarregamento  contem  outro descarregamento
				if( Descarregamentos[d1].HorarioInicioDescarregamento >= Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento <= Descarregamentos[d2].HorarioFinalDescarregamento ){
					//if ( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento, Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
					//}
					if ( ImprimeArquivo == 1){
						fprintf( Arquivo, " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento, Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento );
					}
					// probelma com descarregamento que viala outro descarregamento, o descarregamento está contido outro descarregamenbto. retorna 0
					return 0;
				}
				// verifica se o descarregamento  está parcialmente contido na parte inicial de  outro descarregamento
				if( Descarregamentos[d1].HorarioFinalDescarregamento > Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioFinalDescarregamento <= Descarregamentos[d2].HorarioFinalDescarregamento ){
					//if ( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento, Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento );
					//}
					if ( ImprimeArquivo == 1){
						fprintf( Arquivo," >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento, Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento );
					}
					// probelma com descarregamento que viala outro descarregamento, o descarregamento está parcialmente contido em outro descarregamenbto. retorna 0
					return 0;
				}
				// verifica se o descarregamento  está parcialmente contido na parte final de  outro descarregamento
				if( Descarregamentos[d1].HorarioInicioDescarregamento >= Descarregamentos[d2].HorarioInicioDescarregamento && Descarregamentos[d1].HorarioInicioDescarregamento < Descarregamentos[d2].HorarioFinalDescarregamento ){
					//if ( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento, Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento );
					//}
					if( ImprimeArquivo == 1){
						fprintf( Arquivo, " >>>>>>>>>>>>>> Problema! Descarregamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Descarregamentos[d1].HorarioInicioDescarregamento, Descarregamentos[d1].HorarioFinalDescarregamento, Descarregamentos[d2].HorarioInicioDescarregamento  , Descarregamentos[d2].HorarioFinalDescarregamento );
					}
					// probelma com descarregamento que viala outro descarregamento, o descarregamento contem parcialmente  outro descarregamenbto. retorna 0
					return 0;
				}

			}
		}
	}
	// os descarregamentos são integros entre se
	if( imprime == 1){
		if ( ImprimeSolucao == 1){
			cout << " Descarregamentos integros " << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo, " Descarregamentos integros \n");
		}
	}
	// descarregamneto é integro, retorna 1
	return 1;
}


// aloca atividade sabedno que ela tem que começar em um certo hoario, este horaio é determinado pelo horaio que ela tem que terminar. Nesse caso se tem que realizar o atendimeto com o veículo passado na função
int 	Construcao::AlocaAtividadeComHorarioFinalAtendimentoComVeiculoFixo( int NumDemanda, int NumPlanta, int NumCarreta, double HoraFimAtendimento, double &NovaHoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar, int SituacaoDemanda, int StatusRemocao, ConjuntoPlantas& Plantas, int EscolhaVeiculo, int EscolhaPlanta, string frase){
	// armazena os horarios de uma tarefa
	double 	HorarioInicioPlanta;
	double 	HorarioSaiDaPlanta;
	double 	HorarioRetornaPlanta;
	double 	HorarioChegaContrucao;
	double 	HorarioSaiConstrucao;
	// arqmazena os estados de disponibilidade da tarefa na planta, na coonstrução e no caminhão
	int 	DisponibilidadePlanta;
	int 	DisponibilidadeConstrucao;
	int 	DisponibilidadeCarreta;
	int 	DisponibilidadeVidaConcreto;

	// situação se a planta pode atender a demanda caso atrasar (-2) ou ela não pode atender a demanda (0)
	int 	SituacaoPlanta;
	// hoaraior que a planta pode atender a demanda caso as demandas ateriores forem atrasadas, e o horario que a construção iria ser atendida
	//double 	HorarioQuePlantaPodeAtender;
	double 	HorarioQueConstrucaoPodeReceberDemanda;

	// inidices da planta e do veículo (caminhão)
	int 	p;
	int 	v;

	// aloca os inidces da planta e do veiculo
	Plantas.AlocaInidiceFabrica(NumPlanta,p);
	Plantas.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(NumCarreta, v);

	// inicializa a situação da planta e os horarios que a planta pode atender a demanda e a construção pode ser atendida
	SituacaoPlanta = 0;
	//HorarioQuePlantaPodeAtender = DBL_MAX;
	HorarioQueConstrucaoPodeReceberDemanda = DBL_MAX;

	//int ParaPrograma;

	// verifica se a cosntrução já não teve todas as suas demandas atendidas
	if ( NumeroDemandas > StatusAtendimento){
		/*
		 * versão 1
		 * // atualiza o horario inicial que a planta pode atender a demanda
		HorarioInicioPlanta 	= HoraFimAtendimento 	- Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda] -  Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;
		HorarioChegaContrucao 	= HorarioInicioPlanta 	+ Plantas.Plantas[p].TempoPlanta + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];
		*/

		HorarioChegaContrucao 	= HoraFimAtendimento 	- Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda];
		HorarioInicioPlanta 	= HorarioChegaContrucao - Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao] -  Plantas.Plantas[p].TempoPlanta;

		// realizar até o horario inicio da planta ou da construção não ultrapassar o limite de atendidmento da planta ou da construção respectivamente
		while( HorarioInicioPlanta <= Plantas.Plantas[p].TempoMaximoDeFuncionamento &&  HorarioChegaContrucao <= TempoMaximoDeFuncionamento){
			// atualiza os horarios na construção e planta
			HorarioSaiDaPlanta 		= HorarioInicioPlanta + Plantas.Plantas[p].TempoPlanta;
			HorarioChegaContrucao 	= HorarioSaiDaPlanta + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];
			HorarioSaiConstrucao 	= HorarioChegaContrucao +  Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[NumeroDaConstrucao][NumDemanda];
			HorarioRetornaPlanta 	= HorarioSaiConstrucao + Plantas.Plantas[p].TempoParaConstrucoes[NumeroDaConstrucao];
			// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta, verifica tempo de vida concreto
			DisponibilidadePlanta 		= Plantas.Plantas[p].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
			DisponibilidadeConstrucao 	= VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
			DisponibilidadeCarreta 		= Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
			DisponibilidadeVidaConcreto = VerificaTempoDeVidaConcreto ( HorarioChegaContrucao, HorarioInicioPlanta);
			// caso se puder realizar a terefa se entra nos If
			if( DisponibilidadeVidaConcreto == 1){
				if( DisponibilidadePlanta == 1){
					if( DisponibilidadeCarreta == 1){
						if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
							// se consegue atender a demanda com essa planta, carreta e nessa construção
							AlocaAtividadeSalvandoDados(0, HorarioChegaContrucao, HorarioSaiConstrucao, Plantas.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, Plantas.Plantas[p].NumeroDaPlanta, SituacaoDemanda, StatusRemocao, Plantas, DadosTarefasMovidasAuxiliar);
							//ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1; ( não se aplica isso, pois se entra na equação d erecorrencia
							// se conseguiu atender a demanda, se retorna 1
							return 1;
						}else{
							// caso se consiga atender a demanda caso se atrase as demandas atendidas anteriormente na construção, se entra no if
							if( DisponibilidadeConstrucao == -2){
								//cout <<  "                     Caso atrazar da para alocar, demanda em analise [" << NumeroDaConstrucao << "-" << NumDemanda << "] no horario " << HorarioChegaContrucao << endl;

								// caso a planta ainda não foi analisada, entra no if
								if( HorarioQueConstrucaoPodeReceberDemanda 	> HorarioChegaContrucao){
									// atualiza a hora de inicio que a planta pode atender a demanda e a construção pode ser atendida
									//HorarioQuePlantaPodeAtender  			= HorarioInicioPlanta;
									HorarioQueConstrucaoPodeReceberDemanda 	= HorarioChegaContrucao;
								}
								// marca no vetor de estado da planta para o atendiemnto  que a planta corrente pode atender a demanda caso se atrase as demandas atendidas anteriormente a demanda corrente na construção
								SituacaoPlanta = -2;
								// se coloca o limite de tempo que a planta pode atender a demanda na variavel para se sair do loop
								HorarioInicioPlanta = Plantas.Plantas[p].TempoMaximoDeFuncionamento;
							}
						}
					}
				}
			}
			// acrescenta o horario inicio que ira começar o carregamento na planta
			HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
		}
		// caso se dê para atender caso atrazar os otros atendiemntos se enra na função
		if( SituacaoPlanta == -2){
			// se fornece o horario que a demanda anterior a está tem que terminar pelo menos
			NovaHoraFimAtendimento = HorarioQueConstrucaoPodeReceberDemanda - TempoMaximoEntreDescargas + IntervaloDeTempo;
			// retorna -2 para indicar que se pode atender a demada caso se atrasa-la
			return -2;
		}
		// não da para atender a demanda
		return 0;

	}else{
		cout << endl << endl << endl << "   >>>>>>>>>>>>>>>  Problema! -> Construcao [" << NumeroDaConstrucao << "-" << NumDemanda << "] com demanda ja atendida -> Construcao::AlocaAtividadeComHorarioFinalAtendimentoComVeiculoFixo &&&&&&&&&&&&& " << endl << endl << endl;
		// demanda já atendida
		return 0;
	}
}


// função de atrazar as demandas para atender a ultima demanda, está é a função que recebe a demanda não alocada ainda
int 	Construcao::AtrasaDemandasParaAtenderMasterComVeiculoFixo( int NumDemanda, int NumPlanta, int NumCarreta, double HoraFimAtendimento, vector < DadosTarefa > &DadosTarefasMovidasAuxiliar,int SituacaoDemanda, int StatusRemocao,ConjuntoPlantas& Plantas, int &SituacaoAlocacao, int EscolhaVeiculo, int EscolhaPlanta,int imprime, string frase){


	// ****************** Variaveis que precisão ser removidas, pois não tem utilidade na função ***************************//

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int 	ImprimeArquivo;
	ImprimeArquivo = 0;
	// variavel que imprime se ira escrever os dados da solução na tela
	int 	ImprimeSolucao;
	ImprimeSolucao = 1;

	// ********************************************************************************************************************//


	// aramazena o valor auxiliar do horario final de atendiemnto na construção caso for adotado se possibilita o atendimento da demanda
	double 	NovaHoraFimAtendimento;

	if( imprime == 1){
		cout << endl << endl << "     ====================== Entra Master [" << NumeroDaConstrucao << "-" << NumDemanda << "] -> Construcao::AtrasaDemandasParaAtenderMasterComVeiculoFixo ====================== "  << endl << endl;

		ImprimeContrucao(ImprimeSolucao,ImprimeArquivo,Arquivo);
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
	}

	// aloca valor de situaçãAlocação como sendo que a tarefa que ainda naõ foi alocada pode ser alocada caso se atraze o atendimento das tarefas que são anteriores a ela
	SituacaoAlocacao = -2;

	// enquanto se puder atender a demanda coeernte se atrazar as outras, se continua no loop
	while(SituacaoAlocacao == -2 ){

		// tenta atrazar as demandas anteriores para possibilitar o atendimento da demand corrente
		AtrasaDemandasParaAtenderRecursao( NumDemanda, HoraFimAtendimento,  DadosTarefasMovidasAuxiliar,  Plantas, SituacaoAlocacao,EscolhaVeiculo, EscolhaPlanta,imprime, frase);

		if( SituacaoAlocacao == 1){

			// verifica se pode atender a demanda corrente
			SituacaoAlocacao = AlocaAtividadeComHorarioFinalAtendimentoComVeiculoFixo( NumDemanda, NumPlanta, NumCarreta, HoraFimAtendimento, NovaHoraFimAtendimento, DadosTarefasMovidasAuxiliar, SituacaoDemanda, StatusRemocao, Plantas, EscolhaVeiculo,  EscolhaPlanta,frase);
			// caso ainda de para atender a demanda se atrasar as demandas anteriores entra no if
			if(SituacaoAlocacao == -2 ){
				// se atualiza a hora que se tem que atender a tarefa anterior a tarefa corrente que se quer alocar
				HoraFimAtendimento = NovaHoraFimAtendimento;
			}

		}
	}

	if( imprime == 1){
		ImprimeContrucao( ImprimeSolucao,ImprimeArquivo,Arquivo);
		cout << "DadosTarefasMovidasAuxiliar" << endl;
		ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
		cout << endl << endl << "     ====================== Sai Master [" << NumeroDaConstrucao << "-" << NumDemanda << "] -> Construcao::AtrasaDemandasParaAtenderMasterComVeiculoFixo ====================== "  << endl << endl;
	}

	if( SituacaoAlocacao == 1){
		// caso se consiga alocar a demanda, retorna 1
		return 1;
	}else{
		// caso não se consiga alocar a demanda, retorna 0
		return 0;
	}
}


// retorna a demanda não atendida na construção por parametro, retorna 1 se tive demanda não atendida e zero se a construção já tiver sido completamente atendida
int 	Construcao::DemandaNaoAtendida( int &DemandaNaoAtendida){
	// inicia o valor da demanda não atendida
	DemandaNaoAtendida = -13;

	// percorre todas as demandas da construção
	for( int d = 0; d < NumeroDemandas; d++){
		// caso a demanda não tenha sido atendida se entra no if
		if( SituacaoDemanda[d] == 0 ){
			// se retorna a demanda não atendida
			DemandaNaoAtendida = d;
			// retorna 1 mostrando que tem uma demanda não atendida
			return 1;
		}
	}
	// retorna 0 mostrando que não tem demanda não atendida
	return 0;
}

// Imprime os dados da construções
void	Construcao::ImprimeContrucao(int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){

	// calcular o makespan da construção
	CalculaMakespan();
	// imprime descarregamentos
	if( ImprimeSolucao == 1 ){
		printf( "# Contrucao %d com %d demandas, janela de tempo (%.4f - %.4f), com rank = %.4f \n",NumeroDaConstrucao, NumeroDemandas, TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento, RankTempoDemandas);
	}
	if( ImprimeArquivo == 1 ){
		fprintf( Arquivo, "# Contrucao %d com %d demandas, janela de tempo (%.4f - %.4f), com rank = %.4f \n",NumeroDaConstrucao, NumeroDemandas, TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento, RankTempoDemandas);
	}
	if( StatusAtendimento != 0){
		for( int d = 0; d < (int) Descarregamentos.size(); d++){
			if( ImprimeSolucao == 1){
				printf( "     * Carreta [%d-%d] atende demanda %d-%d de ( %.4f as %.4f )\n", Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
			}
			if( ImprimeArquivo ==1 ){
				fprintf( Arquivo, "     * Carreta [%d-%d] atende demanda %d-%d de ( %.4f as %.4f )\n", Descarregamentos[d].NumPlantaFornecedor, Descarregamentos[d].NumCarretaUtilizada, NumeroDaConstrucao, d, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento);
			}
		}
	}

	if( ImprimeSolucao == 1){
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

	if( ImprimeArquivo ==1 ){
		fprintf( Arquivo,"   Vetor de atendimento demandas [ ");
		for ( int i = 0; i < NumeroDemandas; i++){
			fprintf( Arquivo," %d ", SituacaoDemanda[ i ]);
		}
		fprintf( Arquivo,"]\n");

		// imprime o vetor remocao
		fprintf( Arquivo,"    Vetor de Situacao Remocao das demandas [ ");
		for ( int i = 0; i < NumeroDemandas; i++){
			fprintf( Arquivo," %d ", SituacaoRemocao[ i ]);
		}
		fprintf( Arquivo,"]\n");

		// imprime makespan da cosntrução
		fprintf( Arquivo,"   MAKESPAN = %.4f   Status = %d\n", Makespan, StatusAtendimento);
	}

}

// destruidora da classe
Construcao::~Construcao(){
	NumeroDaConstrucao = -13;
	NumeroDemandas = -13;
	SituacaoDemanda.clear();
	SituacaoRemocao.clear();
	TempoParaPlantas.clear();
	TempoMaximoEntreDescargas = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	RankTempoDemandas = -13;
	StatusAtendimento = -13;
	Descarregamentos.clear();
	Makespan = -13;
}


// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

// função que retorna se c1 tem menor rank que c2
bool 	DecideQualContrucaoTemMenorRank (Construcao c1,Construcao c2) {
	if( c1.RankTempoDemandas != c2.RankTempoDemandas){
		return ( c1.RankTempoDemandas < c2.RankTempoDemandas );
	}else{
		if( c1.TempoMinimoDeFuncionamento != c2.TempoMinimoDeFuncionamento){
			// retorna a cosntrução com o menor tempo inicio
			return ( c1.TempoMinimoDeFuncionamento < c2.TempoMinimoDeFuncionamento );
		}else{
			return ( c1.TempoMaximoDeFuncionamento < c2.TempoMaximoDeFuncionamento );
		}
	}
}

// função que retorna se c1 tem menor janela de tempo de funcionamento que c2. Caso de empate nesse quesito, ela verifica se c1 mais demandas que c2
bool 	DecideQualContrucaoTemMenorJanela (Construcao c1,Construcao c2) {
	if( c1.TempoMaximoDeFuncionamento - c1.TempoMinimoDeFuncionamento != c2.TempoMaximoDeFuncionamento - c2.TempoMinimoDeFuncionamento ){
		return ( c1.TempoMaximoDeFuncionamento - c1.TempoMinimoDeFuncionamento < c2.TempoMaximoDeFuncionamento - c2.TempoMinimoDeFuncionamento );
	}else{
		return ( c1.NumeroDemandas > c2.NumeroDemandas);
	}
}

// função que retorna se c1 tem menor inicio de funcionamento que c2. Caso de empate nesse quesito, ela verifica se c1 tem menor fim de funcionamento que c2. Caso de empate, verifica se c1
bool 	DecideQualContrucaoTemMenorInicio (Construcao c1,Construcao c2) {
	if( c1.TempoMinimoDeFuncionamento != c2.TempoMinimoDeFuncionamento ){
			return ( c1.TempoMinimoDeFuncionamento < c2.TempoMinimoDeFuncionamento );
	}else{
		if( c1.TempoMaximoDeFuncionamento != c2.TempoMaximoDeFuncionamento){
			return ( c1.TempoMaximoDeFuncionamento < c2.TempoMaximoDeFuncionamento);
		}else{
			return ( c1.NumeroDemandas > c2.NumeroDemandas);
		}
	}
}

// Gerador Aleatorico Construcao
int 	GeradorAleatoricoConstrucao (int i) {


	return rand()%i;
}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class ConjuntoConstrucoes{

public:

	vector< Construcao > Construcoes;
	int 	NumeroConstrucoes;

	double	MakespanConstrucoes;
	int 	NivelDeInviabilidade;

	ConjuntoConstrucoes();

	void 	InicializaConstrucoesAnalizadas();				// Inicializa o status das cosntruções todos como 0
	void 	CalcularNivelDeInviabilidade();				// Calcula o Nivel de Inviabilidade
	void 	IniciaConjuntoConstrucoes(int Numero);			// Inicializa a classe com o número das construções que se quer


	void 	CalculaMakespansConstrucoes();											// Calcula o Makespan das Construções
	int 	RetornaIndiceConstrucao(int Construcao, int& Indice, string frase);		// retorna o indice da construção passada

	int 	VerificacaoIntegridadeDeDescarregamentosConstrucoes(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// faz a verificação dos descarregaemntos
	int 	VerificaIndividualmenteDemandas(ConjuntoPlantas& Plantas, int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);	// verifica se as tarefas são integras
	int 	VerificaIntervaloContrucoes(int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);											// Verifica se as construções respeitão os intervalos de atendimento entre suas demandas

	int 	VerificacaoConsistenciaTarefas(ConjuntoPlantas& Plantas, int imprime,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);	// verifica integridade das tarefas como um todo

// Funções com a SituaçãoRemover
	void 	ReiniciaTarefasRetiradas();													// Reinicia o status de remoção de todas as demandas de todas as construções
	void 	MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda, int Situacao);			// maraca a situação remoção da demanda no vetor que sinaliza a situação da demanda
	void 	MarcaTarefaNaoRemovidaNoVetor(int Construcao, int Demanda, string frase);		// marca a tarefa, demand, não removida


// Funções com a PodeAtender
	void 	AlocaValoresConstrucaoPodeSerSuprida();		// Marca se precisa analisar a construção. Aloca 1 se a construção já teve todas as demandas atendidas, 0 as que não
	void 	AtualizaValoresConstrucaoPodeAtender();	// Atualiza com 1 se a construção já teve todas as demandas atendidas
	int 	VerificaConstrucaoPodeSerSuprida();			// Verifica se existe uma demanda que ainda pode ser analisada pelo algoritmo
	int 	VerificaSeTodasConstrucaoPodeSerSupridaForamAnalisadas();

	void 	AlocaValoresConstrucoesAnalizadas( int IndiceConstrucaoNaoAtendida );		// 		Coloca o status 2 para as construções que já foram atendidas, e coloca 3 no status da construção passada como parametro
	int 	VerificaTemConstrucaoParaAnalisar();									// verifica se tem construção para analisar

	int 	RetornaDadosDemandaAtendida( int Construcao, int Demanda,  int &NumPlanta, int &NumCarreta, double &HorarioInicioDescarregamento, double &HorarioFinalDescarregamento, double &HorarioInicioCarregamento, double &HorarioFinalCarregamento, double &HorarioInicioDeslocamento, double &HorarioFinalDeslocamento, ConjuntoPlantas& Plantas);		// retorna dados de uma tarefa que atende uma demanda passada na função
	int 	VerificaIntegridaDeDemandaAtendida( int Construcao, int Demanda, int NumPlanta, int NumCarreta, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento, double HorarioInicioCarregamento, double HorarioFinalCarregamento, double HorarioInicioDeslocamento, double HorarioFinalDeslocamento, int imprime,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// verifica a integridade da tarefa

// 	Função auxiliar a retornar a solução inicial
	int 	ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas, ConjuntoPlantas &PlantasInstancia);

	void 	EncontraPlanta( int c, int& NumPlantaAnalisando, int EscolhaPlanta, ConjuntoPlantas &PlantasInstancia, string frase);		// encontra a planta mais perto da construção que ainda não foi analisada
	int 	AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrasarTarefas, int EscolhaVeiculo ,int EscolhaPlanta, ConjuntoPlantas &PlantasInstancia, int imprime, string frase);		// função que tenta alocar uma demanda
	int 	AdicionaTarefaComVeiculoFixo( int VerificaExistencia, int Construcao, int Demanda , int Planta, int Carreta, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrasarTarefas, int EscolhaVeiculo, int EscolhaPlanta, ConjuntoPlantas &PlantasInstancia, int imprime, string frase);

	void 	OrdenaCosntrucoes( int EscolhaConstrucao);			// realiza o ordenamento das construções

	void 	InicializaConstrucoesComDemandasNaoAtendidas( int Construcao, int Imprime);				// marca as construções com demandas não atendidas que pode ser atendidas
	int 	ExisteConstrucaoComDemandaNaoAtendida( int &Construcao, int &Demanda, int Imprime);			// escolhe a construção que possui demandas não atendidas e que será atendida

	void 	ImprimeContrucoes(ConjuntoPlantas& Plantas, int VerificaViabilidade ,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);	// Imprime as construções e em seguida o nivel de inviabilidade
	void	ImprimeConstrucoesComDemandasNaoAtendidas();			// imprime os valores que indicam se a construção tem demandas não atendidas

	~ConjuntoConstrucoes();						// Destruidora da classe
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){
	NumeroConstrucoes = -13;
	NivelDeInviabilidade = -13;
	MakespanConstrucoes = -13;
}

// Inicializa o status das cosntruções todos como 0
void 	ConjuntoConstrucoes::InicializaConstrucoesAnalizadas(){

	// percorre por todas as construções
	for( int c = 0; c < (int) Construcoes.size(); c++){
		// inicia como não analisada, ou com o status 0
		Construcoes[c].ConstrucaoAnalizada = 0;
	}
}

// Calcula o Nivel de Inviabilidade
void 	ConjuntoConstrucoes::CalcularNivelDeInviabilidade(){
	// zera o nivel de inviabilidade
	NivelDeInviabilidade = 0;
	// percorre todas as contruçãoes
	for( int c = 0; c < (int) Construcoes.size(); c++){
		// atualiza com o nivel de inviabilidade da construção corrente
		NivelDeInviabilidade = NivelDeInviabilidade + Construcoes[c].NumeroDemandas - Construcoes[c].StatusAtendimento;
	}
}

// Inicializa a classe com o número das construções que se quer
void 	ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){
	// inicia o vetor de cosntruções com o numero de construções
	Construcoes.resize(Numero);
	// aloca o numero de construções
	NumeroConstrucoes = Numero;

	for( int i = 0; i < Numero; i++){
		Construcoes[i].ConstrucaoAnalizada = 0;
	}

	// inicia o vetor de construções pode ser suprida como 0
	for( int i = 0; i < Numero; i++){
		Construcoes[i].ConstrucaoPodeSerSuprida = 0;
	}

	// inicia o vetor de construções com demandas não atendidas como 0
	for( int i = 0; i < Numero; i++){
		Construcoes[i].ConstrucaoComDemandasNaoAtendidas = 0;
	}

}


// Calcula o Makespan das Construções
void 	ConjuntoConstrucoes::CalculaMakespansConstrucoes(){
	// inicia o makespan das cosntruções como zero
	MakespanConstrucoes = 0;
	// percorre por todas as construções
	for( int c = 0; c < (int) Construcoes.size(); c++){
		// calcula o makespan da construção corrente
		Construcoes[c].CalculaMakespan();
		// acrescenta o makespan da cosntruyução corrente ao  makespan de todas as cosntruções
		MakespanConstrucoes = MakespanConstrucoes + Construcoes[c].Makespan;
	}
}

// retorna o indice da construção passada
int 	ConjuntoConstrucoes::RetornaIndiceConstrucao(int Construcao, int& Indice, string frase){
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


// faz a verificação dos descarregaemntos
int 	ConjuntoConstrucoes::VerificacaoIntegridadeDeDescarregamentosConstrucoes(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// variavel que representa a integridade dos descarregamentos
	int 	Integro;
	// inicia como integro o estado dos descarregamentos
	Integro = 1;

	if( imprime == 1) {
		if( ImprimeSolucao == 1){
			cout << endl << "          Verifica integridade Descarregaemntos  " << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"\n          Verifica integridade Descarregaemntos  \n\n" );
		}
	}
	// percore todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		if( ImprimeSolucao == 1){
			cout << " construcao [" << Construcoes[c].NumeroDaConstrucao << "] ";
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo," construcao [ %d ] ", Construcoes[c].NumeroDaConstrucao );
		}
		// verifica a integridade dos descarregamentos da construção
		if( Construcoes[c].VerificaIntegridadeDeDescrregamentos(imprime, ImprimeSolucao,ImprimeArquivo, Arquivo) == 0 ){
			//if( ImprimeSolucao == 1){
				cout << endl << endl << "      Problema! Descarremagentos não estão integros " << endl << endl;
			//}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"\n\n      Problema! Descarremagentos não estão integros \n\n");
			}
			// sinaliza que o descarrregamento não é integro
			Integro = 0;
		}
	}

	// retorna se existe algum descarregamento que não esta integro ao retorna 0, ou 1 caso contrario
	return Integro;
}

// verifica se as tarefas são integras
int 	ConjuntoConstrucoes::VerificaIndividualmenteDemandas(ConjuntoPlantas& Plantas, int imprime,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// variaveis que armazenam os dados da tarefa
	int 	NumPlanta;
	int 	NumCarreta;
	double 	HorarioInicioDescarregamento;
	double 	HorarioFinalDescarregamento;
	double 	HorarioInicioCarregamento;
	double 	HorarioFinalCarregamento;
	double 	HorarioInicioDeslocamento;
	double 	HorarioFinalDeslocamento;

	// variavel que sinaliza se a tarefa é integra ou não
	int 	integridade;
	// inicia como integro o estado da tarefa
	integridade = 1;

	if( imprime == 1){
		if( ImprimeSolucao == 1){
			cout << endl << "          Verifica tarefas individualmente  " << endl << endl;
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo, "\n           Verifica tarefas individualmente \n\n");
		}
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
					if( ImprimeSolucao == 1){
						printf( "  - Demanda [%d-%d] => construcao [%d] no horario (%.4f-%.4f)",Construcoes[c].NumeroDaConstrucao,d,Construcoes[c].NumeroDaConstrucao,HorarioInicioDescarregamento, HorarioFinalDescarregamento);
						printf( "  planta [%d] no horario (%.4f-%.4f) ",NumPlanta, HorarioInicioCarregamento, HorarioFinalCarregamento);
						printf( "  carreta [%d] no horario (%.4f-%.4f) \n", NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento );
					}
					if( ImprimeArquivo == 1){
						fprintf( Arquivo, "  - Demanda [%d-%d] => construcao [%d] no horario (%.4f-%.4f)",Construcoes[c].NumeroDaConstrucao,d,Construcoes[c].NumeroDaConstrucao,HorarioInicioDescarregamento, HorarioFinalDescarregamento);
						fprintf( Arquivo,  "  planta [%d] no horario (%.4f-%.4f) ",NumPlanta, HorarioInicioCarregamento, HorarioFinalCarregamento);
						fprintf( Arquivo, "  carreta [%d] no horario (%.4f-%.4f) \n", NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento );
					}
				}
				// verifica se a tarefa é integra
				if ( VerificaIntegridaDeDemandaAtendida(Construcoes[c].NumeroDaConstrucao, d, NumPlanta, NumCarreta, HorarioInicioDescarregamento, HorarioFinalDescarregamento, HorarioInicioCarregamento, HorarioFinalCarregamento, HorarioInicioDeslocamento, HorarioFinalDeslocamento, imprime, ImprimeSolucao,ImprimeArquivo, Arquivo) == 0){
					// caso não for ele assinala na variavel de controle que se tem uma tarefa não integra
					integridade = 0;
				}
				// verifica o tempo de vida do concreto na tarefa
				if( HorarioInicioDescarregamento - HorarioInicioCarregamento > Construcoes[c].TempoDeVidaConcreto){
					if( imprime == 1){
						if( ImprimeSolucao == 1){
							printf( " NÃO RESPEITA TEMPO DE VIDA DO CONCRETO\n\n\n");
						}
						if( ImprimeArquivo == 1){
							fprintf( Arquivo, " NÃO RESPEITA TEMPO DE VIDA DO CONCRETO\n\n\n");
						}
					}
				}else{
					if( imprime == 1){
						if( ImprimeSolucao == 1){
							printf( " Respeita Tempo De Vida Concreto\n");
						}
						if( ImprimeArquivo == 1){
							fprintf( Arquivo, " Respeita Tempo De Vida Concreto\n");
						}
					}
				}

			}
		}
	}
	// retorna o estado de integridade das tarefas, 1 se todas forem integras e 0 caso tiver alguma que não é integra
	return integridade;
}


// Verifica se as construções respeitão os intervalos de atendimento entre suas demandas
int 	ConjuntoConstrucoes::VerificaIntervaloContrucoes(int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// status da viabilidade
	int 	viavel;

	// começa com solução viavel
	viavel = 1;

	if(	ImprimeSolucao == 1){
		cout << endl << " Status de respeito a intervelos de construção" << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, " \n  Status de respeito a intervelos de construção \n");
	}
	// percorre por todas as construções
	for(int c = 0; c < NumeroConstrucoes; c++){
		// verifica se a cosntrução corrente respeita o intervalo entre descarregamentos
		if( Construcoes[c].VerificaDescarregamentosRespeitaIntervalo() == 1){
			// caso respeitar
			if( ImprimeSolucao == 1){
				cout << endl << Construcoes[c].NumeroDaConstrucao << " Respeita Intervalo!";
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo," \n %d  Respeita Intervalo!", Construcoes[c].NumeroDaConstrucao);
			}
		}else{
			// caso não respeitar
			//if( ImprimeSolucao == 1){
				cout << endl << Construcoes[c].NumeroDaConstrucao << " Não Respeita Intervalo! INVIÁVEL!!!";
			//}
			if(  ImprimeArquivo == 1){
				fprintf( Arquivo, "\n %d Não Respeita Intervalo! INVIÁVEL!!!",Construcoes[c].NumeroDaConstrucao);
			}
			// marca como não viavel as demandas atendidadas na construção
			viavel = 0;
		}
	}
	if( ImprimeSolucao == 1){
		cout << endl ;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "\n");
	}
	// retorna se é respeitado ou não o intervalo entre tarefas nas construções
	return viavel;
}


// verifica integridade das tarefas
int 	ConjuntoConstrucoes::VerificacaoConsistenciaTarefas(ConjuntoPlantas& Plantas, int imprime,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// variavel que sinaliza a integridade das tarefas
	int 	integridade;
	// inicia como integro o estado das tarefas
	integridade = 1;

	if( ImprimeSolucao == 1){
		cout << endl << endl << " ***********  Consistencia da solução ********************* " << endl << endl;
	}

	if( ImprimeArquivo == 1){
		fprintf (Arquivo, " \n\n ***********  Consistencia da solução ********************* \n\n");
	}

	//verifica as tarefas individualmente
	if( VerificaIndividualmenteDemandas( Plantas,imprime, ImprimeSolucao,ImprimeArquivo, Arquivo) == 0){
		//if( ImprimeSolucao == 1){
			cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de demandas individuais" << endl << endl;
		//}
		if( ImprimeArquivo == 1){
			fprintf (Arquivo, " \n\n    >>>>>>>>>>>>> Probelma com integridade de demandas individuais \n\n");
		}
		// sinaliza que as tarefas não são integras
		integridade = 0;
	}
	//verifica os descarregamentos
	if( VerificacaoIntegridadeDeDescarregamentosConstrucoes(imprime, ImprimeSolucao,ImprimeArquivo, Arquivo) == 0){
		//if( ImprimeSolucao == 1){
			cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de Descarregaemntos" << endl << endl;
		//}
		if( ImprimeArquivo == 1){
			fprintf (Arquivo, " \n\n    >>>>>>>>>>>>> Probelma com integridade de Descarregaemntos \n\n");
		}
		// sinaliza que as tarefas não são integras
		integridade = 0;
	}
	//verifica intervalo entre descarregamentos descarregamentos
	if( VerificaIntervaloContrucoes(ImprimeSolucao,ImprimeArquivo, Arquivo) == 0){
		//if( ImprimeSolucao == 1){
			cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade com o tempo entre os Descarregaemntos" << endl << endl;
		//}
		if( ImprimeArquivo == 1){
			fprintf (Arquivo, " \n\n   >>>>>>>>>>>>> Probelma com integridade com o tempo entre os Descarregaemntos \n\n");
		}
		// sinaliza que as tarefas não são integras
		integridade = 0;
	}
	//verifica os carregamentos
	if(Plantas.VerificaIntegridadeDeCarregamentosDasPlantas(imprime, ImprimeSolucao,ImprimeArquivo, Arquivo) == 0){
		//if( ImprimeSolucao == 1){
			cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de Carregaemntos" << endl << endl;
		//}
		if( ImprimeArquivo == 1){
			fprintf (Arquivo, " \n\n   >>>>>>>>>>>>> Probelma com integridade de Carregaemntos \n\n");
		}
		// sinaliza que as tarefas não são integras
		integridade = 0;
	}
	//verifica os deslocamentos
	if(Plantas.VerificaIntegridadeDeDeslocaemntosDosVeiculosDasPlantas(imprime, ImprimeSolucao,ImprimeArquivo, Arquivo) == 0){
		//if( ImprimeSolucao == 1){
			cout << endl << endl << "   >>>>>>>>>>>>> Probelma com integridade de Deslocamentos" << endl << endl;
		//}
		if( ImprimeArquivo == 1){
			fprintf (Arquivo, " \n\n   >>>>>>>>>>>>> Probelma com integridade de Deslocamentos \n\n");
		}
		// sinaliza que as tarefas não são integras
		integridade = 0;
	}

	if( ImprimeSolucao == 1){
		cout << endl << endl << " *********************************************************** " << endl << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf (Arquivo, "\n\n *********************************************************** \n\n");
	}
	// retorna se as tarefas são integras ou não
	return integridade;
}

// ***************** Funções com a SituaçãoRemover ***************** //

// Reinicia o status de remoção de todas as demandas de todas as construções
void 	ConjuntoConstrucoes::ReiniciaTarefasRetiradas(){
	// percorre todas as cosntruções
	for( int c = 0; c < (int) Construcoes.size(); c++){
		// percorre todas as demandas da cosntrução corrente
		for( int d = 0; d < Construcoes[c].NumeroDemandas; d++){
			// coloca o status da demanda corrente como não removida
			Construcoes[c].SituacaoRemocao[d] = 0;
		}
	}
}

// maraca a situação remoção da demanda no vetor que sinaliza a situação da demanda
void 	ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor(int Construcao, int Demanda, int Situacao){
	// variavel qiue guarda o indice da cosntrução passada
	int 	c;
	// caso se encontrar a construção passada na função, entrar no if
	if( RetornaIndiceConstrucao(Construcao, c, "ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor")== 1 ){
		if( Construcoes[c].NumeroDemandas > Demanda ) {
		    //marca a demanda com o valor passado
			Construcoes[c].SituacaoRemocao[Demanda] = Situacao;
			//cout << endl << endl << "  marquei " << endl << endl;
		}else{
			cout << endl << endl << "    <<<<<<<<<<<<+<+<+<+  Problema!   Demanda  [" << Construcao << "-" << Demanda << "] não existe -> ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor +>+>+>+>>>>>>>>> " << endl << endl;
		}
	}else{
		cout << endl << endl << "    <<<<<<<<<<<<<<<  Problema!   Não encontrei a construção [" << Construcao << "] -> ConjuntoConstrucoes::MarcaTarefaDeletadaNoVetor >>>>>>>>>>>> " << endl << endl;
	}

}

// marca a tarefa, demand, não removida
void 	ConjuntoConstrucoes::MarcaTarefaNaoRemovidaNoVetor(int Construcao, int Demanda, string frase){
	// variavel qiue guarda o indice da cosntrução passada
	int 	c;

	// aloca o indice da construção
	if( RetornaIndiceConstrucao( Construcao, c, " ConjuntoConstrucoes::MarcaTarefaNaoDeletadaNoVetor") == 1 ){
		// verifica se a demanda passada existe na cosntrução
		if( Construcoes[c].NumeroDemandas > Demanda ) {
			// marca a demanda como não removida
			Construcoes[c].SituacaoRemocao[Demanda] = 0;
		}else{
			cout << endl << endl << "    <<<<<<<<<<<<+<+<+<+  Problema!   Demanda  [" << Construcao << "-" << Demanda << "] não existe -> ConjuntoConstrucoes::MarcaTarefaNaoRemovidaNoVetor " << frase << endl << endl;
		}
	}else{
		cout << " <<<<<<<<<<<< problema! não encontrou a construção [" <<  Construcao << "] ->  ConjuntoConstrucoes::MarcaTarefaNaoRemovidaNoVetor " << frase << endl << endl;
	}
}

// ***************** Funções com a PodeAtender ***************** //

// Marca se precisa analisar a construção. Aloca 1 se a construção já teve todas as demandas atendidas, 0 as que não
void 	ConjuntoConstrucoes::AlocaValoresConstrucaoPodeSerSuprida(){

	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// entra caso a cosntrução já tenha todas as suas demandas atendidas
		if ( Construcoes[c].NumeroDemandas == Construcoes[c].StatusAtendimento){
			// marca que não precisa avaliar a cosntrução corrente
			Construcoes[c].ConstrucaoPodeSerSuprida = 1;
		}else{
			// marca que precisa avaliar a cosntrução corrente
			Construcoes[c].ConstrucaoPodeSerSuprida = 0;
		}
	}

}

// Atualiza com 1 se a construção já teve todas as demandas atendidas

void 	ConjuntoConstrucoes::AtualizaValoresConstrucaoPodeAtender(){
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// caso todas as demandas da construção tenha suas demandas já atendidas entra
		if ( Construcoes[c].NumeroDemandas == Construcoes[c].StatusAtendimento){
			// marca que não precisa analisar a construção corrente
			Construcoes[c].ConstrucaoPodeSerSuprida = 1;
		}
	}

}

// Verifica se existe uma demanda que ainda pode ser analisada pelo algoritmo

int 	ConjuntoConstrucoes::VerificaConstrucaoPodeSerSuprida(){
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// caso a construção corrente ainda possa ser analisada
		if( Construcoes[c].ConstrucaoPodeSerSuprida == 0){
			// caso ela possa ser analisada retorna 1
			return 1;
		}
	}
	// não se possui mais construções a analisar, retorna 0
	return 0;

}

int 	ConjuntoConstrucoes::VerificaSeTodasConstrucaoPodeSerSupridaForamAnalisadas(){
	// percorre todas as construções
	for( int c = 0; c < NumeroConstrucoes; c++){
		// caso a construção corrente ainda possa ser analisada
		if( Construcoes[c].ConstrucaoPodeSerSuprida != 1){
			return 0;
		}
	}
	return 1;

}


// 		Coloca o status 2 para as construções que já foram atendidas, e coloca 3 no status da construção passada como parametro

void 	ConjuntoConstrucoes::AlocaValoresConstrucoesAnalizadas( int IndiceConstrucaoNaoAtendida){
	// percorre todas as construções
	for ( int c = 0; c < NumeroConstrucoes; c++){
		// caso a cosntruçaõ já tenha tido todas as suas demandas atendidas
		if( Construcoes[c].StatusAtendimento == Construcoes[c].NumeroDemandas ){
			// coloca o valor 2
			Construcoes[c].ConstrucaoAnalizada = 2;
		}
	}
	// coloca o valor 3 na construção que foi passada na função
	Construcoes[IndiceConstrucaoNaoAtendida].ConstrucaoAnalizada = 3;

}

// verifica se tem construção para analisar
int 	ConjuntoConstrucoes::VerificaTemConstrucaoParaAnalisar(){
	// percorre todas as construções
	for ( int c = 0; c < NumeroConstrucoes; c++){
		// verifica se a construção corrente não foi analisada
		if( Construcoes[c].ConstrucaoAnalizada == 0){
			return 1;
		}
	}
	return 0;
}


// retorna dados de uma tarefa que atende uma demanda passada na função

int 	ConjuntoConstrucoes::RetornaDadosDemandaAtendida( int Construcao, int Demanda, int &NumPlanta, int &NumCarreta, double &HorarioInicioDescarregamento, double &HorarioFinalDescarregamento, double &HorarioInicioCarregamento, double &HorarioFinalCarregamento, double &HorarioInicioDeslocamento, double &HorarioFinalDeslocamento, ConjuntoPlantas& Plantas){
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
	cout << endl << endl << "  <<<<<<<<<+<+<+<+ Problema! Construção [" << Construcao << "] não encontrada! -> ConjuntoConstrucoes::RetornaDadosDemandaAtendida +>+>+>+>>>>>>>>>>>>>>>>>>>> " << endl << endl;
	// não encontrou a consrução que se quer, retorna 0
	return 0;
}

// verifica a integridade da tarefa

int 	ConjuntoConstrucoes::VerificaIntegridaDeDemandaAtendida( int Construcao, int Demanda, int NumPlanta, int NumCarreta, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento, double HorarioInicioCarregamento, double HorarioFinalCarregamento, double HorarioInicioDeslocamento, double HorarioFinalDeslocamento, int imprime,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// variavel qiue guarda o indice da cosntrução passada
	int 	c;

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
							if( ImprimeSolucao == 1){
								cout << "     Integro " << endl;
							}
							if( ImprimeArquivo == 1){
								fprintf( Arquivo, "     Integro \n");
							}
						}
						// retorna 1, sinalizando que a demanda é integra
						return 1;
					}else{
						if( ImprimeSolucao == 1){
							printf("       -------- Problema! HorarioFinalDescarregamento maior que HorarioFinalDeslocamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
						}
						if( ImprimeArquivo == 1){
							fprintf( Arquivo,"       -------- Problema! HorarioFinalDescarregamento maior que HorarioFinalDeslocamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
						}
					}
				}else{
					if( ImprimeSolucao == 1){
						printf("       -------- Problema! HorarioInicioDescarregamento maior que HorarioFinalDescarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
					}
					if( ImprimeArquivo == 1){
						fprintf( Arquivo,"       -------- Problema! HorarioInicioDescarregamento maior que HorarioFinalDescarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
					}
				}
			}else{
				if( ImprimeSolucao == 1){
					printf("       -------- Problema! HorarioFinalCarregamento maior que HorarioInicioDescarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
				}
				if( ImprimeArquivo == 1){
					fprintf( Arquivo,"       -------- Problema! HorarioFinalCarregamento maior que HorarioInicioDescarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
				}
			}
		}else{
			if( ImprimeSolucao == 1){
				printf("       -------- Problema! HorarioInicioCarregamento maior que HorarioFinalCarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
			}
			if( ImprimeArquivo == 1){
				fprintf( Arquivo,"       -------- Problema! HorarioInicioCarregamento maior que HorarioFinalCarregamento da demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
			}
		}

	}else{
		if( ImprimeSolucao == 1){
			printf("       -------- Problema! O horario de inicio do deslocamento e de inicio do carregamento não conicidem para a demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
		}
		if( ImprimeArquivo == 1){
			fprintf( Arquivo,"       -------- Problema! O horario de inicio do deslocamento e de inicio do carregamento não conicidem para a demanda [%d-%d] -> ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida", Construcao, Demanda);
		}
	}
	// caso tiver algum problem, imprime os dados da tarefa
	RetornaIndiceConstrucao(Construcao, c, " ConjuntoConstrucoes::VerificaIntegridadeDemandaAtendida" );
	if( ImprimeSolucao == 1){
		printf( "  - Demanda [%d-%d] => construcao [%d] no horario (%.4f-%.4f)",Construcoes[c].NumeroDaConstrucao, Demanda,Construcoes[c].NumeroDaConstrucao,HorarioInicioDescarregamento, HorarioFinalDescarregamento);
		printf( "  planta [%d] no horario (%.4f-%.4f) ",NumPlanta, HorarioInicioCarregamento, HorarioFinalCarregamento);
		printf( "  carreta [%d] no horario (%.4f-%.4f) \n", NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento );
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "  - Demanda [%d-%d] => construcao [%d] no horario (%.4f-%.4f)",Construcoes[c].NumeroDaConstrucao, Demanda,Construcoes[c].NumeroDaConstrucao,HorarioInicioDescarregamento, HorarioFinalDescarregamento);
		fprintf( Arquivo, "  planta [%d] no horario (%.4f-%.4f) ",NumPlanta, HorarioInicioCarregamento, HorarioFinalCarregamento);
		fprintf( Arquivo, "  carreta [%d] no horario (%.4f-%.4f) \n", NumCarreta, HorarioInicioDeslocamento, HorarioFinalDeslocamento );
	}
	// retorna 0, sinalizando que a demanda não é integra
	return 0;

}

// ***************** Função auxiliar a retornar a solução inicial ***************** //

// readiciona tarefas deletadas e deleta tarefas adicionadas visando restaurar a configuração inicial da solução

int 	ConjuntoConstrucoes::ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas, ConjuntoPlantas &PlantasInstancia){
	// retorna 1, sinalizando que a demanda é integra
	int 	c;

	// percorre trodos os elementos das tarefas que foram removidas e adicionadas no vetor
	for( int i = (int) DadosTarefasMovidas.size() - 1 ; i >= 0; i--){

		// caso a tarefa tenha sido retirada da solução, ela é adicionada novamente
		if( DadosTarefasMovidas[i].Status == 'r'){
			// coleta o inidice da construção
			if(RetornaIndiceConstrucao( DadosTarefasMovidas[i].DadosDasTarefas[0]  , c, " ConjuntoConstrucoes::ReadicionaDeletaTarefasApartirDeDados") == 0 ){
				// retorna 0. problema ao encontrar construção
				return 0;
			}
			// Aloca a tarefa caso possivel
			if( Construcoes[c].AlocaAtividade( DadosTarefasMovidas[i].HorariosDasTarefas[2],DadosTarefasMovidas[i].HorariosDasTarefas[3], DadosTarefasMovidas[i].DadosDasTarefas[2], DadosTarefasMovidas[i].DadosDasTarefas[1], DadosTarefasMovidas[i].DadosDasTarefas[3], DadosTarefasMovidas[i].DadosDasTarefas[4], PlantasInstancia) == 0 ){
				cout << endl << endl << "       <<<<<<<+<+<+<+<+ Problema em adicionar -> ConjuntoConstrucoes::ReadicionaDeletaTarefasApartirDeDados +>+>+>+>>>>>>>>>>> " << endl;
				DadosTarefasMovidas[i].Imprimir();
				cout << endl;
				// retorna 0. problema ao readicionar tarefa
				return 0;
			}
			//Atualiza o Indice de Inviabilidade da solução
			NivelDeInviabilidade = NivelDeInviabilidade - 1;
		}

		// caso a tarefa tenha sido adicionada a solução, ela é retirada da solução
		if( DadosTarefasMovidas[i].Status == 'a'){
			// coleta o inidice da construção
			if(RetornaIndiceConstrucao( DadosTarefasMovidas[i].DadosDasTarefas[0]  , c, " ConjuntoConstrucoes::ReadicionaDeletaTarefasApartirDeDados") == 0 ){
				// retorna 0. problema ao encontrar construção
				return 0;
			}
			// deleta a tarefa caso possivel
			if( Construcoes[c].DeletaTarefasAnteriormenteAdicionadasDados( DadosTarefasMovidas[i], PlantasInstancia) == 0){
				cout << endl << endl << "       <<<<<<<+<+<+<+<+ Problema em remover -> ConjuntoConstrucoes::ReadicionaDeletaTarefasApartirDeDados +>+>+>+>>>>>>>>>>> " << endl;
				DadosTarefasMovidas[i].Imprimir();
				cout << endl;
				// retorna 0. problema ao deletar tarefa
				return 0;
			}
			//Atualiza o Indice de Inviabilidade da solução
			NivelDeInviabilidade = NivelDeInviabilidade + 1;
		}
	}
	// processo realizado com sucesso, sem problemas. retorna 1
	return 1;
}

// encontra a planta mais perto da construção que ainda não foi analisada

void 	ConjuntoConstrucoes::EncontraPlanta( int c, int& NumPlantaAnalisando,int EscolhaPlanta, ConjuntoPlantas &PlantasInstancia, string frase){
	if( EscolhaPlanta == 1){
		// variavel que armazena a distancia da construção a planta usada para se encontra a planta mais proxima
		double 	TempoConstrucaoPlanta;

		// inicializa as variaveis
		NumPlantaAnalisando 		= -13;
		TempoConstrucaoPlanta 	= DBL_MAX;

		// percorre todas as plantas
		for( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
			if( TempoConstrucaoPlanta > Construcoes[c].TempoParaPlantas[p].Tempo){
				// planta que ainda não foi analisada
				if( PlantasInstancia.Plantas[p].PlantasAnalizadas == 0){
					// passa o numero da planta escolhida
					NumPlantaAnalisando = p;
					// atualiza a distancia da planta mais proxima a construção
					TempoConstrucaoPlanta = Construcoes[c].TempoParaPlantas[p].Tempo;
				}
			}
		}

		// caso não encontre nenhuma planta
		if(NumPlantaAnalisando == -13){
			cout << endl << endl << endl << "      ++++++++++++++++ Probelma" << frase << endl << endl << endl;
		}
		return;
	}

	if( EscolhaPlanta == 2){
		PlantasInstancia.OrdenaPlantas( EscolhaPlanta);
		// percorre todas as plantas
		for( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
			if( PlantasInstancia.Plantas[p].PlantasAnalizadas == 0){
				// passa o numero da planta escolhida
				NumPlantaAnalisando = p;
				return;
			}
		}
	}

	if( EscolhaPlanta == 3){
		PlantasInstancia.OrdenaPlantas( EscolhaPlanta);
		// percorre todas as plantas
		for( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
			if( PlantasInstancia.Plantas[p].PlantasAnalizadas == 0){
				// passa o numero da planta escolhida
				NumPlantaAnalisando = p;
				return;
			}
		}
	}

	if( EscolhaPlanta == 4){
		PlantasInstancia.OrdenaPlantas( EscolhaPlanta);
		// percorre todas as plantas
		for( int p = 0; p < (int) PlantasInstancia.Plantas.size(); p++){
			if( PlantasInstancia.Plantas[p].PlantasAnalizadas == 0){
				// passa o numero da planta escolhida
				NumPlantaAnalisando = p;
				return;
			}
		}
	}

	cout << endl << endl << endl << "  ************* Probelma em encontrar planta *************" << endl << endl << endl;

}

// função que tenta alocar uma demanda

int 	ConjuntoConstrucoes::AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrasarTarefas, int EscolhaVeiculo , int EscolhaPlanta, ConjuntoPlantas &PlantasInstancia, int imprime, string frase){

	// ****************** Variaveis que precisão ser removidas, pois não tem utilidade na função ***************************//

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int 	ImprimeArquivo;
	ImprimeArquivo = 0;
	// variavel que imprime se ira escrever os dados da solução na tela
	int 	ImprimeSolucao;
	ImprimeSolucao = 1;

	// ********************************************************************************************************************//

	// armazena os horarios de uma tarefa
	double 	HorarioInicioPlanta;
	double 	HorarioSaiDaPlanta;
	double 	HorarioRetornaPlanta;
	double 	HorarioChegaContrucao;
	double 	HorarioSaiConstrucao;
	// arqmazena os estados de disponibilidade da tarefa na planta, na coonstrução e no caminhão
	int 	DisponibilidadePlanta;
	int 	DisponibilidadeConstrucao;
	int 	DisponibilidadeCarreta;
	int 	DisponibilidadeVidaConcreto;
	// indice da construção e planta
	int 	c;
	int 	p ;

	// Guarda as tarefas movidada no processo de mudar o horario de atendimento de uma demanda anterior visando atender uma posterior
	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;

	// variaveis de controle
	int SituacaoAlocacao;

	// variavel que indica se ira realizar a verificação da solução
	int 	VerificaViabilidade;
	VerificaViabilidade = 0;

	// variavel para se parar o programa
	int 	ParaPrograma;

	// inicializa os vetores que armazenam os horarios que as plantas podem atender a demanda da construção caso se caia no caso de -2 na Analise da planta. Se é inicializado com os valores maximos de Double
	PlantasInstancia.InicializaVetorHorarioQuePlantaPodeAtender();
	// aloca o indice da construção
	if( RetornaIndiceConstrucao(Construcao, c, " <<<<<<<<<<<<<<<<< ConjuntoConstrucoes::AdicionaTarefa  >>>>>>>>>>>>>>>>>>>>>>>>>>") == 1 ){
		// verifica se a construção já foi atendida em sua totatlidade, cao não entra no if
		if ( Construcoes[c].NumeroDemandas > Construcoes[c].StatusAtendimento){
			// faz com que nenhuma planta tenha sido analisada até o momento
			PlantasInstancia.InicializaPlantasAnalizadas();

			// só entra no loop enquanto se tem uma planta para analisar
			while( PlantasInstancia.AnalizouTodasPLanats() == 0){
				// encontra a planta mais perto d aconstrução
				EncontraPlanta(c,  p , EscolhaPlanta, PlantasInstancia, "   &&&&&&&&&&&&& Problema em fornecer valor de   p  em adiciona tarefa  -> ConjuntoConstrucoes::AdicionaTarefa &&&&&&&&&&&&& ");
				// ordena as britadeiras
				PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.OrdenaCarretas(EscolhaVeiculo);
				// percorre todos os veículos da planta
				for( int v = 0; v < PlantasInstancia.Plantas[ p ].NumeroVeiculos; v++){
					// inicializa o tempo inicio que a planta corrente ira começar a analise se pode atender a demanda corrente, caso
					if( ( Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ] - PlantasInstancia.Plantas[ p ].TempoPlanta ) > PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento ){
						//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela construção.
						HorarioInicioPlanta 	= Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ] - PlantasInstancia.Plantas[ p ].TempoPlanta;
						// atualiza os horarios na construção e planta
						HorarioSaiDaPlanta 		= HorarioInicioPlanta 	+ PlantasInstancia.Plantas[ p ].TempoPlanta;
						HorarioChegaContrucao 	= HorarioSaiDaPlanta 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao];
						HorarioSaiConstrucao 	= HorarioChegaContrucao + PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ Construcoes[c].NumeroDaConstrucao ][ Demanda ];
						HorarioRetornaPlanta 	= HorarioSaiConstrucao 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ];

					}else{
						//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela planta.
						HorarioInicioPlanta 	= PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento;
						// atualiza os horarios na construção e planta
						HorarioSaiDaPlanta 		= HorarioInicioPlanta + PlantasInstancia.Plantas[ p ].TempoPlanta;
						HorarioChegaContrucao 	= HorarioSaiDaPlanta + PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao];
						HorarioSaiConstrucao 	= HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ Construcoes[c].NumeroDaConstrucao ][ Demanda ];
						HorarioRetornaPlanta 	= HorarioSaiConstrucao + PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ];
					}
					// enquanto estiver na janela de tempo possivel para atendimeto se realiza o loop abaixo.
					while( HorarioInicioPlanta <= PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento &&  HorarioChegaContrucao <= Construcoes[c].TempoMaximoDeFuncionamento){
						// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta, verifica tempo de vida concreto
						DisponibilidadePlanta 		= PlantasInstancia.Plantas[ p ].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
						DisponibilidadeConstrucao 	= Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao );
						DisponibilidadeCarreta 		= PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade( HorarioInicioPlanta, HorarioRetornaPlanta );
						DisponibilidadeVidaConcreto = Construcoes[c].VerificaTempoDeVidaConcreto ( HorarioChegaContrucao, HorarioInicioPlanta);

						// caso se puder realizar a terefa se entra nos If
						if( DisponibilidadeVidaConcreto == 1){
							if( DisponibilidadePlanta == 1){
								if( DisponibilidadeCarreta == 1){
									if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){

										// se consegue atender a demanda com essa planta, carreta e nessa construção
										Construcoes[c].AlocaAtividadeSalvandoDados(VerificaExistencia, HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[ p ].NumeroDaPlanta, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, DadosTarefasMovidas);

										// se dieminui o nível de iniviabilidade da solução
										NivelDeInviabilidade = NivelDeInviabilidade - 1;
										// retorna 1 indicando que se foi possivel alocar a demanda corrente
										return 1;
									}else{

										// Caso for atrasar demandas anteriores para se atender a demanda
										if( RealizaProcessoDeAtrasarTarefas == 1){

											// caso se possa atender a demanda se atender as demandas anterior em um horario diferente
											if( DisponibilidadeConstrucao == -2){

												// caso for  aprimeira vez que se verifique a valor -2 para a DisponibilidadeConstrução, se atualiza os hoarios iniciais tanto na planta e na construção que a planta corrente pode vir a atender a construção
												if(  PlantasInstancia.Plantas[ p ].HorarioQueConstrucaoPodeReceberDemanda > HorarioChegaContrucao){
													PlantasInstancia.Plantas[ p ].HorarioQuePlantaPodeAtender = HorarioInicioPlanta;
													PlantasInstancia.Plantas[ p ].HorarioQueConstrucaoPodeReceberDemanda = HorarioChegaContrucao;
												}

												// se atualiza a situação da planta corrente com -2 e coloca o tempo de inicio da planta como o tempo maximo de funcionamento da planta para se forçar sair do loop do while
												PlantasInstancia.Plantas[ p ].PlantasAnalizadas = -2;
												// se coloca o limite de tempo que a planta pode atender a demanda na variavel para se sair do loop
												HorarioInicioPlanta = PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento + IntervaloDeTempo;

												if( imprime == 1){
													cout <<  "           (-) Caso atrazar da para alocar, demanda em analise [" << Construcao << "-" << Demanda<< "] no horario " << HorarioChegaContrucao << " na planta [" << PlantasInstancia.Plantas[ p ].NumeroDaPlanta << "] no veiculo [" << v << "]" << endl;
												}
											}

										}

									}
								}
							}
						}
						// acrescenta o horario do inicio da planta para se percorrer todos os possiveis horarios de alocação da demanda por essa planta corrente
						HorarioInicioPlanta 	= HorarioInicioPlanta 	+ IntervaloDeTempo;
						// atualiza os horarios na construção e planta
						HorarioSaiDaPlanta 		= HorarioInicioPlanta 	+ PlantasInstancia.Plantas[ p ].TempoPlanta;
						HorarioChegaContrucao 	= HorarioSaiDaPlanta 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao];
						HorarioSaiConstrucao 	= HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ Construcoes[c].NumeroDaConstrucao ][ Demanda ];
						HorarioRetornaPlanta 	= HorarioSaiConstrucao 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ];
					// realiza o loop até que os intervalos de de funcionamento da planta e da construção ainda sejam respeitados
					}
				}

				// caso a planta não tenha sido assinalada com -2, que ela pode atender a demanda caso atraze as outras demandas anteriores, se marca a planta com 1 para sinalizar que ela não consegue atender a está demanda.
				if (PlantasInstancia.Plantas[ p ].PlantasAnalizadas != -2){
					PlantasInstancia.Plantas[ p ].PlantasAnalizadas = 1;
				}
			}
			if( imprime == 1){
				PlantasInstancia.ImprimeHorariosPlantasPodemAtender();
			}

			// Caso for atrasar demandas anteriores para se atender a demanda
			if( RealizaProcessoDeAtrasarTarefas == 1){

				// caso não se tenha conseguido atender a demanda corrente, se verifica se tem alguma planta que pode atender a demanda caso se mude o horario de atendiemnto das outras demandas posteriores a está. Caso se possa, se entra no if e tenta mudar o horario das demandas anteriores para se tentar atender a demanda corrente
				if( PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrasar() == 1){

					if( imprime == 1){
							cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   sem atrazar as outra demandas -> ConjuntoConstrucoes::AdicionaTarefa &&&&&&&&&&&&& " << endl;
					}

					// limpa o vetor que aramzena as tarefas adicionadas e removidas no processo de atraso
					DadosTarefasMovidasAuxiliar.clear();
					if( imprime == 1){
						cout << endl << endl << "      Função que atraza demandas - horario que pode atender construção = << " << PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() << ">> " << endl << endl;
					}

					// função que realiza o atraso das tarefas para atender uma demanda anterior, caso cosnseguir alocar entra no if
					if ( Construcoes[c].AtrasaDemandasParaAtenderMaster( Demanda, PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() - Construcoes[c].TempoMaximoEntreDescargas  + IntervaloDeTempo,DadosTarefasMovidasAuxiliar, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, SituacaoAlocacao, EscolhaVeiculo, EscolhaPlanta, imprime, frase) == 1 ){
						if( imprime == 1){
							cout << endl << endl << "       ******* adicionei demanda [" << Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "] com o processo de atraso " << endl << endl;
							cout << "DadosTarefasMovidasAuxiliar" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
							cin >> ParaPrograma;
						}
						// funde as tarefas adicionadas e retiradas no processo de atraso e as do procedimento corrente
						if( MergeDadosTarefa( DadosTarefasMovidas, DadosTarefasMovidasAuxiliar) == 0 ){
							cout << endl << endl << " <<<<<<<<<+<+<+<+ Problema em adicionar DadosTarefasMovidasAuxiliar em DadosTarefasMovidas, DadosTarefasMovidasAuxiliar -> ConjuntoConstrucoes::AdicionaTarefa  [[[" << frase << "]]] +>+>+>+>>>>>>>>>> " << endl << endl;
						}
						if( imprime == 1){
							cout << endl << endl << "Merge DadosTarefasMovidasAuxiliar com DadosTarefasMovidas" << endl << endl;

							cout << "DadosTarefasMovidasAuxiliar" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
							cout << "DadosTarefasMovidas" << endl;
							ImprimeVetorDadosTarefa( DadosTarefasMovidas);

							cin >> ParaPrograma;
						}
						// limpa as demandas adicionadas e retiradas no processo de atraso de demandas para atender a ultima demanda
						DadosTarefasMovidasAuxiliar.clear();
						// retorna 1, conseguiu alocar a demanda em questão
						return 1;
					// caso não se consiga alocar a demanda
					}else{
						// retorna a solução até o ponto que ela estava antes do processo de atraso das demandas para atender a ultima demanda
						if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasAuxiliar, PlantasInstancia ) == 0){
							cout << endl << endl << "   <<<<<<<<<+<+<+<+  Problema em adicionar e deletar tarefas para se retornar a solução inicial -> ConjuntoConstrucoes::AdicionaTarefa +>+>+>+>>>>>>>>>> " << endl << endl;
						}
					}
					// limpa as demandas adicionadas e retiradas no processo de atraso de demandas para atender a ultima demanda
					DadosTarefasMovidasAuxiliar.clear();
					if( imprime == 1){
						cout << endl << endl <<  " Fim do atraza tarefas" << endl;
						cout << "DadosTarefasMovidasAuxiliar" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

						ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);

						cin >> ParaPrograma;
					}
				}

			}

			if( imprime == 1){
				cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   MESMO SE atrazar as outra demandas -> ConjuntoConstrucoes::AdicionaTarefa &&&&&&&&&&&&& " << endl;
			}
			// retorna 0 caso não conseguir atender a demansa em qeustão
			return 0;
		}else{
			cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema -> Construcao [" << c << "-" << Demanda << "] com demanda ja atendida -> ConjuntoConstrucoes::AdicionaTarefa &&&&&&&&&&&&& " << endl << endl << endl;
			// retorna 0 pois a demanda que se quer atender já estiver sido atendida
			return 0;
		}
	}
	cout << endl << endl << endl << "      <<<<<<<<<+<+<+<+ Passou por toda a função e não entrou em nada!!! OLHAR ISSO!  -> ConjuntoConstrucoes::AdicionaTarefa +>+>+>+>>>>>>>>>>>>>>> " << endl << endl << endl;
	// retorna 0 pois não encontrou a cosntrução passada
	return 0;

}

// função que tenta alocar uma demanda

int 	ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo( int VerificaExistencia, int Construcao, int Demanda , int Planta, int Carreta, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrasarTarefas, int EscolhaVeiculo, int EscolhaPlanta, ConjuntoPlantas &PlantasInstancia, int imprime, string frase){

	// ****************** Variaveis que precisão ser removidas, pois não tem utilidade na função ***************************//

	// ponteiro para o arquivo que se irá salvar os dados
	PonteiroArquivo  Arquivo;
	// variavel que controla se irá escrever os dados em um aruivo, é inicializada com 0
	int 	ImprimeArquivo;
	ImprimeArquivo = 0;
	// variavel que imprime se ira escrever os dados da solução na tela
	int 	ImprimeSolucao;
	ImprimeSolucao = 1;

	// ********************************************************************************************************************//


	// armazena os horarios de uma tarefa
	double 	HorarioInicioPlanta;
	double 	HorarioSaiDaPlanta;
	double 	HorarioRetornaPlanta;
	double 	HorarioChegaContrucao;
	double 	HorarioSaiConstrucao;
	// arqmazena os estados de disponibilidade da tarefa na planta, na coonstrução e no caminhão
	int 	DisponibilidadePlanta;
	int 	DisponibilidadeConstrucao;
	int 	DisponibilidadeCarreta;
	int 	DisponibilidadeVidaConcreto;
	// indice da construção, planta e veículo
	int 	c;
	int 	p;
	int 	v;

	// Guarda as tarefas movidada no processo de mudar o horario de atendimento de uma demanda anterior visando atender uma posterior
	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;

	// variavel que indica se ira realizar a verificação da solução
	int 	VerificaViabilidade;
	VerificaViabilidade = 0;

	// situação se a planta pode atender a demanda caso atrasar (-2) ou ela não pode atender a demanda (0)
	int 	SituacaoPlanta;
	// hoaraior que a planta pode atender a demanda caso as demandas ateriores forem atrasadas, e o horario que a construção iria ser atendida
	double 	HorarioQuePlantaPodeAtender;
	double 	HorarioQueConstrucaoPodeReceberDemanda;

	// variaveis de controle
	int 	SituacaoAlocacao;

	// variavel para parar o programa
	int 	ParaPrograma;

	// aloca os inidces da planta e do veiculo
	PlantasInstancia.AlocaInidiceFabrica(Planta,p);
	PlantasInstancia.Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo(Carreta, v);

	// inicializa a situação da planta e os horarios que a planta pode atender a demanda e a construção pode ser atendida
	SituacaoPlanta = 0;
	HorarioQuePlantaPodeAtender = DBL_MAX;
	HorarioQueConstrucaoPodeReceberDemanda = DBL_MAX;

	// aloca o indice da construção
	if( RetornaIndiceConstrucao(Construcao, c, " <<<< ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo  >>>>") == 1 ){
		// verifica se a construção já foi atendida em sua totatlidade, cao não entra no if
		if ( Construcoes[c].NumeroDemandas > Construcoes[c].StatusAtendimento){
			// inicializa o tempo inicio que a planta corrente ira começar a analise se pode atender a demanda corrente, caso
			if( ( Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ] - PlantasInstancia.Plantas[ p ].TempoPlanta ) > PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento ){
				//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela construção.
				HorarioInicioPlanta = Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ] - PlantasInstancia.Plantas[ p ].TempoPlanta;
				// atualiza os horarios na construção e planta
				HorarioSaiDaPlanta 		= HorarioInicioPlanta 	+ PlantasInstancia.Plantas[ p ].TempoPlanta;
				HorarioChegaContrucao 	= HorarioSaiDaPlanta 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao 	= HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ Construcoes[c].NumeroDaConstrucao ][ Demanda ];
				HorarioRetornaPlanta 	= HorarioSaiConstrucao 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ];
			}else{
				//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela planta.
				HorarioInicioPlanta = PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento;
				// atualiza os horarios na construção e planta
				HorarioSaiDaPlanta 		= HorarioInicioPlanta 	+ PlantasInstancia.Plantas[ p ].TempoPlanta;
				HorarioChegaContrucao 	= HorarioSaiDaPlanta 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao 	= HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ Construcoes[c].NumeroDaConstrucao ][ Demanda ];
				HorarioRetornaPlanta 	= HorarioSaiConstrucao 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ];
			}
			// enquanto estiver na janela de tempo possivel para atendimeto se realiza o loop abaixo.
			while( HorarioInicioPlanta <= PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento &&  HorarioChegaContrucao <= Construcoes[c].TempoMaximoDeFuncionamento){

				// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta, verifica tempo de vida concreto
				DisponibilidadePlanta 		= PlantasInstancia.Plantas[ p ].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeConstrucao 	= Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao );
				DisponibilidadeCarreta 		= PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade( HorarioInicioPlanta, HorarioRetornaPlanta );
				DisponibilidadeVidaConcreto = Construcoes[c].VerificaTempoDeVidaConcreto ( HorarioChegaContrucao, HorarioInicioPlanta);

				if( DisponibilidadeVidaConcreto == 1){
					// caso se puder realizar a terefa se entra nos If
					if( DisponibilidadePlanta == 1){
						if( DisponibilidadeCarreta == 1){
							if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
								// se consegue atender a demanda com essa planta, carreta e nessa construção
								Construcoes[c].AlocaAtividadeSalvandoDados(VerificaExistencia, HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[ v ].NumeroDaCarreta, PlantasInstancia.Plantas[ p ].NumeroDaPlanta, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, DadosTarefasMovidas);
								// se dieminui o nível de iniviabilidade da solução
								NivelDeInviabilidade = NivelDeInviabilidade - 1;
								// retorna 1 indicando que se foi possivel alocar a demanda corrente
								return 1;
							}else{

								// Caso for atrasar demandas anteriores para se atender a demanda
								if( RealizaProcessoDeAtrasarTarefas == 1){
									// caso se possa atender a demanda se atender as demandas anterior em um horario diferente
									if( DisponibilidadeConstrucao == -2){

										// caso for a primeira vez que se verifique o valor -2 para a DisponibilidadeConstrução, se atualiza os hoarios iniciais tanto na planta e na construção que a planta pode vir a atender a construção
										if(  HorarioQueConstrucaoPodeReceberDemanda > HorarioChegaContrucao){
											HorarioQuePlantaPodeAtender = HorarioInicioPlanta;
											HorarioQueConstrucaoPodeReceberDemanda = HorarioChegaContrucao;
										}

										// se atualiza a situação da planta com -2
										SituacaoPlanta = -2;
										// coloca o tempo de inicio da planta como o tempo maximo de funcionamento da planta para se forçar sair do loop do while
										HorarioInicioPlanta = PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento + IntervaloDeTempo;

										if( imprime == 1){
											cout <<  "           (-) Caso atrazar da para alocar, demanda em analise [" << Construcao << "-" << Demanda<< "] no horario " << HorarioChegaContrucao << " na planta [" << PlantasInstancia.Plantas[ p ].NumeroDaPlanta << "] no veiculo [" << v << "]" << endl;
										}
									}
								}
							}
						}
					}
				}
				// acrescenta o horario do inicio da planta para se percorrer todos os possiveis horarios de alocação da demanda por essa planta corrente
				HorarioInicioPlanta 	= HorarioInicioPlanta + IntervaloDeTempo;
				// atualiza os horarios na construção e planta
				HorarioSaiDaPlanta 		= HorarioInicioPlanta 	+ PlantasInstancia.Plantas[ p ].TempoPlanta;
				HorarioChegaContrucao 	= HorarioSaiDaPlanta 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao 	= HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ Construcoes[c].NumeroDaConstrucao ][ Demanda ];
				HorarioRetornaPlanta 	= HorarioSaiConstrucao 	+ PlantasInstancia.Plantas[ p ].TempoParaConstrucoes[ Construcoes[c].NumeroDaConstrucao ];
			// realiza o loop até que os intervalos de de funcionamento da planta e da construção ainda sejam respeitados
			}
		}

		if( imprime == 1){
			cout << endl << endl <<  " SituacaoPlantaAtenderCasoAtrasar [" << SituacaoPlanta << "]" << endl;
			cout <<   " HorarioQuePlantaPodeAtender [" << HorarioQuePlantaPodeAtender << "]" << endl;
			cout <<   " HorarioQueConstrucaoPodeReceberDemanda [" << HorarioQueConstrucaoPodeReceberDemanda << "]" <<endl;
			cin >> ParaPrograma;
		}

		// Caso for atrasar demandas anteriores para se atender a demanda
		if( RealizaProcessoDeAtrasarTarefas == 1){
			// caso não se tenha conseguido atender a demanda corrente, se verifica se tem alguma planta que pode atender a demanda caso se mude o horario de atendiemnto das outras demandas posteriores a está. Caso se possa, se entra no if e tenta mudar o horario das demandas anteriores para se tentar atender a demanda corrente
			if(  SituacaoPlanta == -2){
				if( imprime == 1){
					cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   sem atrazar as outra demandas -> ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo &&&&&&&&&&&&& " << endl;
				}

				// limpa o vetor que aramzena as tarefas adicionadas e removidas no processo de atraso
				DadosTarefasMovidasAuxiliar.clear();
				if( imprime == 1){
					cout << endl << endl << "      Função que atraza demandas - horario que pode atender construção = " << HorarioQueConstrucaoPodeReceberDemanda << endl << endl;
				}
				// função que realiza o atraso das tarefas para atender uma demanda anterior, caso cosnseguir alocar entra no if
				if ( Construcoes[c].AtrasaDemandasParaAtenderMasterComVeiculoFixo( Demanda, Planta, Carreta, HorarioQueConstrucaoPodeReceberDemanda - Construcoes[c].TempoMaximoEntreDescargas  + IntervaloDeTempo,DadosTarefasMovidasAuxiliar, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, SituacaoAlocacao,  EscolhaVeiculo,  EscolhaPlanta, imprime, frase) == 1 ){
					if( imprime == 1){
						cout << endl << endl << "       ******* adicionei demanda [" << Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "] com o processo de atraso " << endl << endl;
						cout << "DadosTarefasMovidasAuxiliar" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
						cin >> ParaPrograma;
					}
					// funde as tarefas adicionadas e retiradas no processo de atraso e as do procedimento corrente
					if( MergeDadosTarefa( DadosTarefasMovidas, DadosTarefasMovidasAuxiliar) == 0 ){
						cout << endl << endl << " <<<<<<<<<+<+<+<+ Problema em adicionar DadosTarefasMovidasAuxiliar em DadosTarefasMovidas, DadosTarefasMovidasAuxiliar -> ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo  [[[" << frase << "]]] +>+>+>+>>>>>>>>>> " << endl << endl;
					}
					if( imprime == 1){
						cout << endl << endl << "Merge DadosTarefasMovidasAuxiliar com DadosTarefasMovidas" << endl << endl;

						cout << "DadosTarefasMovidasAuxiliar" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);

						cin >> ParaPrograma;
					}
					// limpa as demandas adicionadas e retiradas no processo de atraso de demandas para atender a ultima demanda
					DadosTarefasMovidasAuxiliar.clear();
					// retorna 1, conseguiu alocar a demanda em questão
					return 1;
				// caso não se consiga alocar a demanda
				}else{
					// retorna a solução até o ponto que ela estava antes do processo de atraso das demandas para atender a ultima demanda
					if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasAuxiliar, PlantasInstancia ) == 0){
						cout << endl << endl << "   Problema em adicionar e deletar tarefas para se retornar a solução inicial -> ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo" << endl << endl;
					}
				}
				// limpa as demandas adicionadas e retiradas no processo de atraso de demandas para atender a ultima demanda
				DadosTarefasMovidasAuxiliar.clear();
				if( imprime == 1){
					cout << endl << endl <<  " Fim do atraza tarefas" << endl;
					cout << "DadosTarefasMovidasAuxiliar" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

					ImprimeContrucoes(PlantasInstancia, VerificaViabilidade, ImprimeSolucao,ImprimeArquivo,Arquivo);

					cin >> ParaPrograma;
				}
			}

		}

		if( imprime == 1){
			cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   MESMO SE atrazar as outra demandas -> ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo &&&&&&&&&&&&& " << endl;
		}
		// retorna 0 caso não conseguir atender a demansa em qeustão
		return 0;
	}else{
		cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema -> Construcao [" << c << "-" << Demanda << "] com demanda ja atendida -> ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo &&&&&&&&&&&&& " << endl << endl << endl;
		// retorna 0 pois a demanda que se quer atender já estiver sido atendida
		return 0;
	}
	cout << endl << endl << endl << "      <<<<<<<<<+<+<+<+ Passou por toda a função e não entrou em nada!!! OLHAR ISSO!  -> ConjuntoConstrucoes::AdicionaTarefaComVeiculoFixo " << endl << endl << endl;
	// retorna 0 pois não encontrou a cosntrução passada
	return 0;

}


// realiza o ordenamento das construções
void 	ConjuntoConstrucoes::OrdenaCosntrucoes( int EscolhaConstrucao){
	// variavel para parar o programa
	int 	Para;

	// variavel para imprimir a ordenação
	int 	Imprime;
	// 0 se não for imprimir, 1 se for imprimir
	Imprime = 0;

	// mantem a ordenação das construções como esta se for 0
	if( EscolhaConstrucao != 0 ){


		if( EscolhaConstrucao == 1){
			// ordena baseado no menor rank
			sort(Construcoes.begin(), Construcoes.end(), DecideQualContrucaoTemMenorRank);
		}

		if( EscolhaConstrucao == 2){
			// ordena baseado na menor janela
			sort(Construcoes.begin(), Construcoes.end(), DecideQualContrucaoTemMenorJanela);
		}

		if( EscolhaConstrucao == 3){
			// ordena baseado no menor tempo inicio
			sort(Construcoes.begin(), Construcoes.end(), DecideQualContrucaoTemMenorInicio);
		}

		if( EscolhaConstrucao == 4){
			// Desordena o vetor de construções
			random_shuffle ( Construcoes.begin(), Construcoes.end(),GeradorAleatoricoConstrucao);
		}
	}

	if(Imprime == 1){
		cout << "    construções ordenadas" << endl ;
		for( int c = 0; c < NumeroConstrucoes; c++){
			cout << " construcao [" << Construcoes[c].NumeroDaConstrucao << "] rank [" << Construcoes[c].RankTempoDemandas << "]  tempo minimo [" << Construcoes[c].TempoMinimoDeFuncionamento << "]tempo maximo [" << Construcoes[c].TempoMaximoDeFuncionamento << "]"<< endl;

		}
		cin >> Para;
	}
}

// marca as construções com demandas não atendidas que pode ser atendidas
void 	ConjuntoConstrucoes::InicializaConstrucoesComDemandasNaoAtendidas( int Construcao, int Imprime){

	int 	ParaPrograma;

	// variavel qiue guarda o indice da cosntrução passada
	int 	IndConstrucaoEscolhida;
	// caso se encontrar a construção passada na função, entrar no if
	if( RetornaIndiceConstrucao(Construcao, IndConstrucaoEscolhida, "ConjuntoConstrucoes::ExisteConstrucoesComDemandasNaoAtendidas")== 1 ){
		// marca a cosntrução passada com o valor 5
		Construcoes[IndConstrucaoEscolhida].ConstrucaoComDemandasNaoAtendidas = 5;
		// faz para todas as construções
		for( int c = 0; c < (int) Construcoes.size(); c++){
			// não realiza isso para a cosntrução passada
			if( c != IndConstrucaoEscolhida){
				// caso a construção não tenha sido completamente atendida entra no if
				if( Construcoes[c].StatusAtendimento < Construcoes[c].NumeroDemandas){
					// marca a construção não completamente atendida com 0
					Construcoes[c].ConstrucaoComDemandasNaoAtendidas = 0;
				}else{
					// marc a cosntrução atendida compleatmente com 3
					Construcoes[c].ConstrucaoComDemandasNaoAtendidas = 3;
				}
			}

		}
		// imprime o conteudo do vetor de controle das plantas
		if( Imprime == 1){
			cout << endl << endl << "      Vetor de cosntrucoes com demandas não atendidas" << endl ;
			ImprimeConstrucoesComDemandasNaoAtendidas();
			cin >> ParaPrograma;
		}

	}

}

// escolhe a construção que possui demandas não atendidas e que será atendida
int 	ConjuntoConstrucoes::ExisteConstrucaoComDemandaNaoAtendida( int &Construcao, int &Demanda, int Imprime){

	// percorre todas as construções
	for(  int c = 0; c < (int) Construcoes.size(); c++){
		// não tenta aloca demandas da construçãoq ue teve uma demanda retirada anteriormente
		if( Construcoes[c].ConstrucaoComDemandasNaoAtendidas == 0){
			if( Construcoes[c].StatusAtendimento < Construcoes[c].NumeroDemandas){
				// retorna a cosntrução e a demanda que deve ser alocada
				Construcao 	= Construcoes[c].NumeroDaConstrucao;
				Demanda 	= Construcoes[c].StatusAtendimento;
				// imprime a cosntrução escolhida
				if( Imprime == 1){
					cout << endl << endl << "     >>> Conatrução-demanda[" << Construcao << "-" << Demanda << "] não atendeida que se tentara atender " << endl << endl;
				}
				// atualiza a situação da contrução como analisada
				Construcoes[c].ConstrucaoComDemandasNaoAtendidas = 1;
				// retorna 1 sinalizando que se tem construçãoa  ser analisada
				return 1;
			}else{
				cout << endl << endl << "   Problema ! Construção já atendida, mas marcada como não atendida    -> ConjuntoConstrucoes::ExisteConstrucaoComDemandaNaoAtendida" << endl << endl;
			}
		}
	}
	// não conseguir alocar a demanda da função, retorna 0
	return 0;
}

// Imprime as construções e em seguida o nivel de inviabilidade
void 	ConjuntoConstrucoes::ImprimeContrucoes(ConjuntoPlantas& Plantas, int VerificaViabilidade ,  int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// calcular o makespan das construções
	CalculaMakespansConstrucoes();
	// calcular o nivel de viabilidade das construções
	CalcularNivelDeInviabilidade();

	if( ImprimeSolucao == 1){
		cout << endl << endl << " [[[[[[  Imprime construcoes  ]]]]]]" << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "\n\n [[[[[[  Imprime construcoes  ]]]]]] \n ");
	}
	// percorre todas as cosntruções
	for(int c = 0; c < NumeroConstrucoes; c++){
		// iomprime a construção corrente
		Construcoes[c].ImprimeContrucao( ImprimeSolucao,ImprimeArquivo, Arquivo);
	}
	if( ImprimeSolucao == 1){
		printf( " Nivel de Inviabilidade = %d  \n \n Makespan Geral das Construcoes = %f\n", NivelDeInviabilidade, MakespanConstrucoes);
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, " Nivel de Inviabilidade = %d  \n \n Makespan Geral das Construcoes = %f\n", NivelDeInviabilidade, MakespanConstrucoes);
	}
	// imprime a verificação de viabilidade caso for pedida na função
	if( VerificaViabilidade == 1){
		VerificacaoConsistenciaTarefas(Plantas, 1, ImprimeSolucao,ImprimeArquivo, Arquivo);
	}
}

// imprime os valores que indicam se a construção tem demandas não atendida
void	ConjuntoConstrucoes::ImprimeConstrucoesComDemandasNaoAtendidas(){
	cout << " Construcoes Com Demandas Nao Atendidasfor ( 1 se tiver, 0 se não) " << endl;
	for( int c = 0;  c < (int) Construcoes.size(); c++){
		cout << c << " [" << Construcoes[c].ConstrucaoComDemandasNaoAtendidas << "] ";
	}
	cout << endl;
}

// Destruidora da classe
ConjuntoConstrucoes::~ConjuntoConstrucoes(){
	Construcoes.clear();
}


bool 	DecideQualMenorInicioTempoDescarregamento ( Descarregamento d1, Descarregamento d2){
	return ( d1.HorarioInicioDescarregamento < d2.HorarioInicioDescarregamento );
}


#endif /* CONSTRUCOES_HPP_ */
