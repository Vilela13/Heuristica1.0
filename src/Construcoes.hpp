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

	void AlocaAtividadeSalvandoDados(double, double, int, int,  bool, int, ConjuntoPlantas&, vector < DadosTarefa >&);

	int DeletaAtividadeLocomovendoAsOutrasTarefas(double, double, int, int, int, ConjuntoPlantas&);

	int DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(double, double, int, int, int, ConjuntoPlantas&, vector < DadosTarefa >&);

	int DeletaTodasAtividadesDaContrucaoSalvandoDados(double&, ConjuntoPlantas&, vector < DadosTarefa >&);

	int DeletaTarefas(  int, vector < DadosTarefa >&, ConjuntoPlantas& Plantas);
	int DeletaTarefasAnteriormenteAdicionadasDados(   DadosTarefa, ConjuntoPlantas&);
	int VerificaDescarregamentosRespeitaIntervalo();

	void RetornaHorarioInicioCarregamento(  int, double&);
	void RetornaDadosDescarregamento( int, int&, int&, int&, double&, double&);
	void CalculaMakespan();

	void ReiniciaTarefasRetiradas();

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

void Construcao::CalculaRankTempoDemandas(int comentarios){			// Calcula o rank que decide qual construção será atendida inicialmente
	RankTempoDemandas = ( TempoMaximoDeFuncionamento - TempoMinimoDeFuncionamento) / NumeroDemandas ;
	if( comentarios == 1){
		cout << " Rank ( Tempo / Demandas ) = " << RankTempoDemandas << endl;
	}
}

int Construcao::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){			// Verifica se da para colocar a demanda na construção, ela sinaliza se caso atrazar as demandas sejá possivel alocar a demanda.
	int PossuiTarefaAnterior;
	int PossuiTarefaPosterior;

	PossuiTarefaAnterior = 0;
	PossuiTarefaPosterior = 0;

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


	if( StatusAtendimento == 0) {		// se não tem nenhuma demanda atendida, se aloca a demanda
		return 1;
	}else{								// verifica a situação dessa demanda com as outras demandas
		for( int d = 0; d < StatusAtendimento; d ++){		// Verifica se tem demanda alocada  antes e depois da alocação dessa tarefa
			if( Descarregamentos[d].HorarioFinalDescarregamento <= InicioPossivelAlocacao && InicioPossivelAlocacao <= Descarregamentos[d].HorarioFinalDescarregamento + TempoMaximoEntreDescargas){
				PossuiTarefaAnterior = 1;
			}
			if( FinalPossivelAlocacao <=  Descarregamentos[d].HorarioInicioDescarregamento &&  Descarregamentos[d].HorarioInicioDescarregamento   <= FinalPossivelAlocacao + TempoMaximoEntreDescargas ){
				PossuiTarefaPosterior = 1;
			}
		}

		// Sinaliza a possição dessa tarefa
		if ( PossuiTarefaAnterior == 1 && PossuiTarefaPosterior == 0){
			// Entra depois de todas as tarefas alocadas
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

		// Caso não respeita o intervalo de tempo necessario entre um descarregamento e outro semdo que ela seria colocada depois das outras demandas já alocadas.
		int TemTarefaAntes;
		TemTarefaAntes = 0;

		for( int d = 0; d < StatusAtendimento; d ++){
			if( Descarregamentos[d].HorarioFinalDescarregamento > InicioPossivelAlocacao ){
				TemTarefaAntes = 1;
			}
		}

		if( TemTarefaAntes == 0){		// Não se pode colocar a demanda pelo fato dela não respeitar o intervalo de atendimento, mas caso se atraze as demandas ela seria alocadac
			return -2;
		}

		// Caso não seja possivel alocar a demanda e ela não está em nenhum dos casos acima.
		return -1;

	}
}

void Construcao::AlocaAtividade(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  bool StatusDesalocamento, int Situacao, ConjuntoPlantas& Plantas){		// Aloca uma demanda na cosntrução apartir de dados


	// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! construcao [" << NumeroDaConstrucao << "] ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
	}

	// Verifica se tem uma tarefa já alocada  e que atende a cosntrução em um horario depois desta
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


	// Caso tenha tarefas que atendam a construção depois dessa, ele faz a atualização dos dados dessas tarefas
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

void Construcao::AlocaAtividadeSalvandoDados(double HoraInicio, double HoraFinal, int Carreta, int NumPlanta,  bool StatusDesalocamento, int Situacao, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosAdicionado){		// Aloca uma demanda na cosntrução apartir de dados, dalvando os dados da demanda alocada em estrutura DadosAdicionado


	// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento == NumeroDemandas){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! construcao [" << NumeroDaConstrucao << "] ->Construcao::AlocaAtividade >>>>>>>>>> " << endl << endl;
	}

	// Verifica se tem uma tarefa já alocada  e que atende a cosntrução em um horario depois desta
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


	// Caso tenha tarefas que atendam a construção depois dessa, ele faz a atualização dos dados dessas tarefas
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

	// salva os dados da demanda que está sendo adicionada em estrutura DadosAdiciona
	AdicionaElementoVetorDadosTarefa(DadosAdicionado,NumeroDaConstrucao, NumPlanta, Carreta,  Situacao, HorarioInicioPlanta, HorarioFimPlanta, HoraInicio, HoraFinal, HorarioFimCarreta);


}



int Construcao::DeletaAtividadeLocomovendoAsOutrasTarefas(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas){		// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos

	// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Demanda [" << NumDemanda << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
		return 0;
	}

	// Verifica se tem uma tarefa já alocada atende a cosntrução depois desta
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

		// Deleta tarefa
		int p;
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
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
		return 0;
	}
	return 1;

}


int Construcao::DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados(double HoraInicio, double HoraFinal, int NumDemanda,  int NumPlanta, int Carreta, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosRetirando){		// Deleta alocação de tarefa e reordenadno as alocações para que os dados se mantenham corretos, salvando os dados da tarefa removida em uma estrutura

	// Verifica se é possivel colocar uma tarefa nesta construção
	if( StatusAtendimento - 1 < NumDemanda){
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! Demanda [" << NumDemanda << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
		return 0;
	}

	// Verifica se tem uma tarefa já alocada atende a cosntrução depois desta
	if( Descarregamentos[NumDemanda].verifica( Carreta, NumPlanta, HoraInicio,HoraFinal) == 1){

		// Deleta tarefa
		int p;
		if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
			cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
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

		AdicionaElementoVetorDadosTarefa(DadosRetirando, NumeroDaConstrucao, NumPlanta, Carreta, 0, HorarioInicioPlanta, HorarioFimPlanta, HoraInicio, HoraFinal, HorarioFimCarreta);


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
		return 0;
	}
	return 1;

}


int Construcao::DeletaTodasAtividadesDaContrucaoSalvandoDados(double &HoraInicio, ConjuntoPlantas& Plantas, vector < DadosTarefa > &DadosRetirandoAux){						// deleta todas as atividades de uma construção. Salvando atividades em estrutura

	// Verifica se tem uma tarefa já alocada atende a cosntrução depois desta
	int p;
	int Carreta;

	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	// verifica se construção tem alguma demanda atendida
	if( StatusAtendimento > 0){

		HoraInicio = Descarregamentos[0].HorarioInicioDescarregamento;			// pega o horario da primeira tarefa na construção

		for( int d = 0; d < StatusAtendimento; d++){
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
			AdicionaElementoVetorDadosTarefa(DadosRetirandoAux, NumeroDaConstrucao, Descarregamentos[d].NumPlantaFornecedor, Carreta, 0, HorarioInicioPlanta, HorarioFimPlanta, Descarregamentos[d].HorarioInicioDescarregamento, Descarregamentos[d].HorarioFinalDescarregamento, HorarioFimCarreta);
// deleta tarefa
			Plantas.DeletaTarefa( Descarregamentos[d].NumPlantaFornecedor, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, d, Carreta, HorarioInicioCarreta, HorarioFimCarreta);
			Descarregamentos[ d ].AnulaConteudo();
			SituacaoDemanda[d ] = 0;
			SituacaoRemocao[ d ] = 0;

		}
		StatusAtendimento = 0;
		return 1;
	}
	return 0;
}

int Construcao::DeletaTarefas(  int demanda, vector < DadosTarefa > &DadosRetirando, ConjuntoPlantas& Plantas){			// Deleta tarefas da demanda passada e as posteriores a esta demanda passada
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
	for( int d = demanda; d < StatusAtendimento; d++){
		Planta = Descarregamentos[d].NumPlantaFornecedor;
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


// Deleta tarefa na planta e no caminhão
		Plantas.DeletaTarefa( Planta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, d, Carreta, HorarioInicioCarreta, HorarioFimCarreta);


		Descarregamentos[d].AnulaConteudo();
		SituacaoDemanda[d] = 0;
		SituacaoRemocao[d] = 0;

// Adiciona na estrutura a terefa retirada
		if( AdicionaElementoVetorDadosTarefa(DadosRetirando,NumeroDaConstrucao, Planta, Carreta, 0, HorarioInicioPlanta, HorarioFimPlanta,HorarioInicioConstrucao, HorarioFinalConstrucao, HorarioFimCarreta) == 0 ){
			cout << endl << endl << " Problema em adicionar tarefa a vetor de tarefas desalocadas " << endl << endl;
			return 0;
		}

		DemandasRetiradas++;	// aumenta o contador das tarefas deletadas
	}

	// atualiza o nivel de atendimento com o número de demandas atendidas na planta
	StatusAtendimento = StatusAtendimento - DemandasRetiradas;
	return 1;

}


int Construcao::DeletaTarefasAnteriormenteAdicionadasDados(   DadosTarefa DadoRetirando, ConjuntoPlantas& Plantas){
	int demanda;
	int ativo;
	ativo = 0;

	// verifica se a tarefa existe na cosntrução
	for( int d = 0; d < StatusAtendimento; d++){
		if( Descarregamentos[d].HorarioInicioDescarregamento == DadoRetirando.HorariosDasTarefas[2] &&  Descarregamentos[d].HorarioFinalDescarregamento == DadoRetirando.HorariosDasTarefas[3]){
			if( Descarregamentos[d].NumPlantaFornecedor == DadoRetirando.DadosDasTarefas[1] &&  Descarregamentos[d].NumCarretaUtilizada == DadoRetirando.DadosDasTarefas[2] ){
				demanda = d;
				ativo = 1;
			}
		}
	}

	if( ativo == 0 ){
		return 0;
	}

	// coleta dasdos da tarefa
	int NumPlanta;
	int Carreta;

	NumPlanta = DadoRetirando.DadosDasTarefas[1];
	Carreta = DadoRetirando.DadosDasTarefas[2];

	// Deleta tarefa
	int p;
	if( Plantas.AlocaInidiceFabrica( NumPlanta, p) == 0) {
		cout << endl << endl << "  <<<<<<<<<<<<<  Erro! planta [" << NumPlanta << "] ->Construcao::DeletaAtividade>>>>>>>>>> " << endl << endl;
		return 0;
	}

	// aloca horarios
	double HorarioInicioPlanta;
	double HorarioFimPlanta;
	double HorarioInicioCarreta;
	double HorarioFimCarreta;

	HorarioInicioPlanta = DadoRetirando.HorariosDasTarefas[0];
	HorarioFimPlanta = DadoRetirando.HorariosDasTarefas[1];
	HorarioInicioCarreta = DadoRetirando.HorariosDasTarefas[0];
	HorarioFimCarreta = DadoRetirando.HorariosDasTarefas[4];


		/*
		cout << endl << endl << "  Dados tarefa " << endl << endl;

		cout << "  contrucao [" << NumeroDaConstrucao << "-" << NumDemanda << "] as " <<  HoraInicio << " até " << HoraFinal << endl;
		cout << "  planta [" << NumPlanta << "] as " << HorarioInicioPlanta << " até " << HorarioFimPlanta << endl;
		cout << "  carreta [" << Carreta << "] as " << HorarioInicioCarreta  << " até " << HorarioFimCarreta << endl << endl;
		 */


// Deleta tarefa na planta e no caminhão
	Plantas.DeletaTarefa( NumPlanta, HorarioInicioPlanta, HorarioFimPlanta, NumeroDaConstrucao, demanda, Carreta, HorarioInicioCarreta, HorarioFimCarreta);


	// Reorganiza Tarefas
	for( int d = demanda + 1; d < StatusAtendimento; d++){
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

	// atualiza o nivel de atendimento
	StatusAtendimento = StatusAtendimento - 1;


	return 1;

}

int Construcao::VerificaDescarregamentosRespeitaIntervalo(){			// Verifica se os descrarregamentor na construção estão respeitando os intervalos entre elas
	if( StatusAtendimento > 1){
		for( int d = 2; d < StatusAtendimento; d++){
			if( Descarregamentos[d].HorarioInicioDescarregamento - Descarregamentos[d -1].HorarioFinalDescarregamento > TempoMaximoEntreDescargas){
				return 0;
			}
		}
	}
	return 1;
}

void Construcao::RetornaHorarioInicioCarregamento( int NumDemanda, double& HoraInicio){		// retorna o horario de inicio de um certo descarregamento na construção
	for( unsigned int d = 0; d < Descarregamentos.size(); d++){
		if( NumDemanda == d){
			HoraInicio = Descarregamentos[d].HorarioInicioDescarregamento;
		}
	}
}

void Construcao::RetornaDadosDescarregamento( int d, int& PlantaEmAnalise, int& 	CaminhaoEmAnalise, int& ConstrucaoEmAnalise, double& HorarioInicioAuxiliar,double& HorarioFinalAuxiliar){	// Retorna os dados de um certo descarregamento

	PlantaEmAnalise 		=	Descarregamentos[d].NumPlantaFornecedor;
	CaminhaoEmAnalise 		=	Descarregamentos[d].NumCarretaUtilizada;
	ConstrucaoEmAnalise 	= 	NumeroDaConstrucao;
	HorarioInicioAuxiliar 	= 	Descarregamentos[d].HorarioInicioDescarregamento;
	HorarioFinalAuxiliar 	= 	Descarregamentos[d].HorarioFinalDescarregamento;
}

void Construcao::CalculaMakespan(){			// Calcula o Makespan da construção
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
			Makespan = Makespan + 50 * TempoMaximoDeFuncionamento;
			cout << endl << endl << "  " << Makespan << " -> Inviolado construcao " << NumeroDaConstrucao << endl << endl;
		}
	}
}

void Construcao::ReiniciaTarefasRetiradas(){		// faz tarefas serem mascadas como não retiradas ainda
	for( unsigned int d = 0; d < Descarregamentos.size(); d++){
		Descarregamentos[d].FoiDeslocado = 0;
	}
}



void Construcao::ImprimeContrucao(){		// Imprime os dados da construções
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


Construcao::~Construcao(){		// destruidora da classe

}


class ConjuntoConstrucoes{

public:
	ConjuntoConstrucoes();

	vector< Construcao > Construcoes;
	int NumeroConstrucoes;
	vector < int > ConstrucaosAnalizadas;

	vector < int > ConstrucaoPodeAvaliar;

	double MakespanConstrucoes;
	int NivelDeInviabilidade;

	void InicializaConstrucaosAnalizadas();
	void AlocaValoresConstrucaosAnalizadas( int );
	void CalcularNivelDeInviabilidade();

	void IniciaConjuntoConstrucoes(int);

	void ImprimeContrucoes();

	void VerificaIntervaloContrucoes();
	void CalculaMakespansConstrucoes();
	void ReiniciaTarefasRetiradas();

	void AlocaValoresConstrucaoPodeAtender();
	void AtualizaValoresConstrucaoPodeAtender();
	int VerificaConstrucaoPodeAtender();

	~ConjuntoConstrucoes();
};

ConjuntoConstrucoes::ConjuntoConstrucoes(){
	NumeroConstrucoes = -13;
	NivelDeInviabilidade = -13;
	MakespanConstrucoes = -13;
}

void ConjuntoConstrucoes::InicializaConstrucaosAnalizadas(){			// Inicializa o status das cosntruções todos como 0
	ConstrucaosAnalizadas.resize(Construcoes.size());
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		ConstrucaosAnalizadas[c] = 0;
	}
}

void ConjuntoConstrucoes::AlocaValoresConstrucaosAnalizadas( int IndiceConstrucaoNaoAtendida){		// 		Coloca o status 2 para as construções que já foram atendidas, e coloca 3 no status da construção passada como parametro
	for ( int c = 0; c < NumeroConstrucoes; c++){
		if( Construcoes[c].StatusAtendimento == Construcoes[c].NumeroDemandas ){
			ConstrucaosAnalizadas[c] = 2;
		}
	}
	ConstrucaosAnalizadas[IndiceConstrucaoNaoAtendida] = 3;

}

void ConjuntoConstrucoes::CalcularNivelDeInviabilidade(){			// Calcula o Nivel de Inviabilidade
	NivelDeInviabilidade = 0;
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		NivelDeInviabilidade = NivelDeInviabilidade + Construcoes[c].NumeroDemandas - Construcoes[c].StatusAtendimento;
	}
}

void ConjuntoConstrucoes::IniciaConjuntoConstrucoes(int Numero){		// Inicializa a classe com o número das construções que se quer
	Construcoes.resize(Numero);
	NumeroConstrucoes = Numero;

}



void ConjuntoConstrucoes::ImprimeContrucoes(){							// Imprime as construções e em seguida o nivel de inviabilidade
	cout << endl << endl << " [[[[[[  Imprime construcoes  ]]]]]]" << endl;
	for(int c = 0; c < NumeroConstrucoes; c++){
		Construcoes[c].ImprimeContrucao();
	}

	cout << endl << " Nivel de Inviabilidade = " << NivelDeInviabilidade << "  Makespan Geral das Construcoes = "<< MakespanConstrucoes << endl;

}

void ConjuntoConstrucoes::VerificaIntervaloContrucoes(){				// Verifica se as construções respeitão os intervalos de atendimento entre suas demandas

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

void ConjuntoConstrucoes::CalculaMakespansConstrucoes(){			// Calcula o Makespan das Construções
	MakespanConstrucoes = 0;
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		Construcoes[c].CalculaMakespan();
		MakespanConstrucoes = MakespanConstrucoes + Construcoes[c].Makespan;
	}
}

void ConjuntoConstrucoes::ReiniciaTarefasRetiradas(){				// Reinicia o status de remoção de todas as demandas de todas as construções
	for( unsigned int c = 0; c < Construcoes.size(); c++){
		Construcoes[c].ReiniciaTarefasRetiradas();
		for( int d = 0; d < Construcoes[c].NumeroDemandas; d++){
			Construcoes[c].SituacaoRemocao[d] = 0;
		}
	}
}

void ConjuntoConstrucoes::AlocaValoresConstrucaoPodeAtender(){		// aloca 1 se a construção já teve todas as demandas atendidas, 0 as que não
	ConstrucaoPodeAvaliar.resize(NumeroConstrucoes);
	for( int c = 0; c < NumeroConstrucoes; c++){
		if ( Construcoes[c].NumeroDemandas == Construcoes[c].StatusAtendimento){
			ConstrucaoPodeAvaliar[c] = 1;
		}else{
			ConstrucaoPodeAvaliar[c] = 0;
		}
	}

}

void ConjuntoConstrucoes::AtualizaValoresConstrucaoPodeAtender(){		// atualiza com 1 se a construção já teve todas as demandas atendidas
	for( int c = 0; c < NumeroConstrucoes; c++){
		if ( Construcoes[c].NumeroDemandas == Construcoes[c].StatusAtendimento){
			ConstrucaoPodeAvaliar[c] = 1;
		}
	}

}

int ConjuntoConstrucoes::VerificaConstrucaoPodeAtender(){			// Verifica se existe uma demanda que ainda pode ser analisada pelo algoritmo
	for( int c = 0; c < NumeroConstrucoes; c++){
		if( ConstrucaoPodeAvaliar[c] == 0){
			return 1;
		}
	}
	return 0;

}

ConjuntoConstrucoes::~ConjuntoConstrucoes(){						// Destruidora da classe

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
