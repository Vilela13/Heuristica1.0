/*
 * Carretas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef CARRETAS_HPP_
#define CARRETAS_HPP_

#include "Bibliotecas.hpp"

class Deslocamento{
public:
	double HorarioInicioDeslocamento;
	double HorarioFinalDeslocamento;
	int NumeroConstrucao;
	int NumeroDemandaSuprida;

	int verifica(int construcao,int NumeroDemandaSuprida, double HorarioInicioVeiculo,double HorarioFimVeiculo);			// verifica se o deslocamento é o mesmo que o que os dados passados representão

};

// verifica se o deslocamento é o mesmo que o que os dados passados representão
int Deslocamento::verifica(int construcao,int Demanda, double HorarioInicioVeiculo,double HorarioFimVeiculo){
	if( construcao == NumeroConstrucao && Demanda == NumeroDemandaSuprida && HorarioInicioVeiculo == HorarioInicioDeslocamento && HorarioFimVeiculo == HorarioFinalDeslocamento){
		return 1;
	}
	return 0;
}

// decide qual deslocamento tem menor tempo de inicio
bool DecideQualMenorInicioTempoDeslocamento ( Deslocamento c1, Deslocamento c2 ){
	return ( c1.HorarioInicioDeslocamento < c2.HorarioInicioDeslocamento );
}

class Carreta{

public:
	Carreta();
	int NumeroDaCarreta;
	int NumeroDeDemandasAntendidas;
	int NumeroPlanta;
	vector < vector < double > > TempoParaDescarregarNaConstrucao;
	vector < Deslocamento > Deslocamentos;

	int VerificaDisponibilidade(double InicioPossivelAlocacao, double FinalPossivelAlocacao);		// verifica a disponibilidade do veículo para atender a demanda
	void AlocaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda);		// Aloca veículo para atender a demanda
	int DeletaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda);		// Deleta alocação de demanda alocada ao veículo

	void Imprime(int Ordena);														// Imprime as atividades realizadas pelo veículo, pode ordena-las
	int VerificaIntegridadeDeDeslocamentos(int Imprime);							// verifica a integridade entre os Deslocamentos da Carreta


	~Carreta();
};

// Construtora
Carreta::Carreta(){
	NumeroDaCarreta = -13;
	NumeroDeDemandasAntendidas = -13;
	NumeroPlanta = -13;

}

// verifica a disponibilidade do veículo para atender a demanda
int Carreta::VerificaDisponibilidade(double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	// percorre todos os delocamentos
	for( unsigned int d = 0; d < Deslocamentos.size(); d ++){
		// verifica se o deslocamento que se quer colocar possui dentro de se um deslocamento já alocado
		if( InicioPossivelAlocacao <= Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao >= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		// verifica se o deslocamento que se quer colocar está dentro de se um deslocamento já alocado
		if( InicioPossivelAlocacao >= Deslocamentos[d].HorarioInicioDeslocamento){
			if ( FinalPossivelAlocacao <= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
		// verifica se o deslocamento que se quer colocar possui a parte posterior dentro de um deslocamento alocado
		if( InicioPossivelAlocacao <= Deslocamentos[d].HorarioInicioDeslocamento){
			if( FinalPossivelAlocacao > Deslocamentos[d].HorarioInicioDeslocamento){
				return 0;
			}
		}
		// verifica se o deslocamento que se quer colocar possui a parte anterior dentro de um deslocamento alocado
		if( InicioPossivelAlocacao < Deslocamentos[d].HorarioFinalDeslocamento){
			if ( FinalPossivelAlocacao >= Deslocamentos[d].HorarioFinalDeslocamento){
				return 0;
			}
		}
	}

	// retorna 1, é viavel se adicionar um carregamento no intervalo passado
	return 1;

}

// Aloca veículo para atender a demanda
void Carreta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){

	// incrementa em 1 o numero de demandas atendidas pela carreta
	NumeroDeDemandasAntendidas = NumeroDeDemandasAntendidas + 1;

	Deslocamento DeslocamentoAux;

	DeslocamentoAux.HorarioInicioDeslocamento = HoraInicio;
	DeslocamentoAux.HorarioFinalDeslocamento = HoraFinal;
	DeslocamentoAux.NumeroConstrucao = NumContrucao;
	DeslocamentoAux.NumeroDemandaSuprida = NumDemanda;

	//cout << endl << endl << "     ******** aloca  caminhao ********* " << endl;
	//cout << " inicio " << HoraInicio << " final " << HoraFinal <<endl;

	// acrescenta o deslocamento
	Deslocamentos.insert(Deslocamentos.begin(), DeslocamentoAux );

}

// Deleta alocação de demanda alocada ao veículo
int Carreta::DeletaAtividade(double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){
	// percorre todos os delocamentos
	for( vector < Deslocamento >::iterator it = Deslocamentos.begin(); it != Deslocamentos.end(); it++){
		//verifica se a hora inicial e final sãoa as mesmas que a passada na função
		if( it->HorarioInicioDeslocamento == HoraInicio && it->HorarioFinalDeslocamento == HoraFinal){
			// verifica se a construção é a mesma passada na função
			if( it->NumeroConstrucao == NumContrucao){
				// verifica se a demanda é a mesma passada na função
				if( it->NumeroDemandaSuprida == NumDemanda){
					// diminui o numero de demandas atendidas pela carreta
					NumeroDeDemandasAntendidas = NumeroDeDemandasAntendidas - 1;
					// deleta o deslocamento
					Deslocamentos.erase(it);
					//cout << endl << endl << " ************* deletou " << Deslocamentos.size() << endl << endl ;

					// retorna 1 para sinalizar que a atividade foi realizada com sucesso
					return 1;
				}
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou elemento deslocamento [" << NumContrucao << "-" << NumDemanda << "] a deletar !  -> Carreta::DeletaAtividade ################## " << endl << endl;
	// retorna 0 para sinalizar que a atividade não foi realizada com sucesso
	return 0;
}

// Imprime as atividades realizadas pelo veículo, pode ordena-las
void Carreta::Imprime(int Ordena){
	// caso se tiver que ordena-las
	if( Ordena == 1){
		sort (Deslocamentos.begin(), Deslocamentos.end(), DecideQualMenorInicioTempoDeslocamento);
	}

	cout << "# Carreta [" << NumeroPlanta << "-" << NumeroDaCarreta << "] que atendeu " << NumeroDeDemandasAntendidas << " demandas" << endl;
	// percorre todos os delocamentos
	for( int d = 0; d < NumeroDeDemandasAntendidas; d++){
		// imprime o deslocamento corrente
		printf( "    *  Atender a [%d-%d] de (%.4f - %.4f)\n", Deslocamentos[d].NumeroConstrucao, Deslocamentos[d].NumeroDemandaSuprida, Deslocamentos[d].HorarioInicioDeslocamento, Deslocamentos[d].HorarioFinalDeslocamento);
	}
}

// verifica a integridade entre os Deslocamentos da Carreta
int Carreta::VerificaIntegridadeDeDeslocamentos(int Imprime){
	// percorre todos os Deslocamentos
	for( unsigned int d1 = 0; d1 < Deslocamentos.size(); d1++){
		// verifica se o Deslocamento não possui tempo negativo
		if( Deslocamentos[d1].HorarioInicioDeslocamento > Deslocamentos[d1].HorarioFinalDeslocamento ){
			printf( " >>>>>>>>>>>>>> Problema! Deslocamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Deslocamentos[d1].HorarioFinalDeslocamento - Deslocamentos[d1].HorarioInicioDeslocamento  , Deslocamentos[d1].HorarioInicioDeslocamento, Deslocamentos[d1].HorarioFinalDeslocamento );
			return 0;
		}
		// percorre todos os Deslocamentos
		for( unsigned int d2 = 0; d2 < Deslocamentos.size(); d2++){
			// o Deslocamento não pode ser o memso que o analisado no primeiro loop
			if( Deslocamentos[d1].HorarioInicioDeslocamento != Deslocamentos[d2].HorarioInicioDeslocamento && Deslocamentos[d1].HorarioFinalDeslocamento != Deslocamentos[d2].HorarioFinalDeslocamento){
				// verifica se o Deslocamento está contido dentro de outro Deslocamento
				if( Deslocamentos[d1].HorarioInicioDeslocamento <= Deslocamentos[d2].HorarioInicioDeslocamento && Deslocamentos[d1].HorarioFinalDeslocamento >= Deslocamentos[d2].HorarioFinalDeslocamento ){
					printf( " >>>>>>>>>>>>>> Problema! Deslocamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Deslocamentos[d2].HorarioInicioDeslocamento  , Deslocamentos[d2].HorarioFinalDeslocamento, Deslocamentos[d1].HorarioInicioDeslocamento, Deslocamentos[d1].HorarioFinalDeslocamento );
					return 0;
				}
				// verifica se o Deslocamento  contem  outro Deslocamento
				if( Deslocamentos[d1].HorarioInicioDeslocamento >= Deslocamentos[d2].HorarioInicioDeslocamento && Deslocamentos[d1].HorarioFinalDeslocamento <= Deslocamentos[d2].HorarioFinalDeslocamento ){
					printf( " >>>>>>>>>>>>>> Problema! Deslocamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Deslocamentos[d2].HorarioInicioDeslocamento  , Deslocamentos[d2].HorarioFinalDeslocamento, Deslocamentos[d1].HorarioInicioDeslocamento, Deslocamentos[d1].HorarioFinalDeslocamento );
					return 0;
				}
				// verifica se o Deslocamento  está parcialmente contido na parte inicial de  outro Deslocamento
				if( Deslocamentos[d1].HorarioFinalDeslocamento >= Deslocamentos[d2].HorarioInicioDeslocamento && Deslocamentos[d1].HorarioFinalDeslocamento <= Deslocamentos[d2].HorarioFinalDeslocamento ){
					printf( " >>>>>>>>>>>>>> Problema! Deslocamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Deslocamentos[d1].HorarioInicioDeslocamento, Deslocamentos[d1].HorarioFinalDeslocamento, Deslocamentos[d2].HorarioInicioDeslocamento  , Deslocamentos[d2].HorarioFinalDeslocamento );
					return 0;
				}
				// verifica se o Deslocamento  está parcialmente contido na parte final de  outro Deslocamento
				if( Deslocamentos[d1].HorarioInicioDeslocamento >= Deslocamentos[d2].HorarioInicioDeslocamento && Deslocamentos[d1].HorarioInicioDeslocamento <= Deslocamentos[d2].HorarioFinalDeslocamento ){
					printf( " >>>>>>>>>>>>>> Problema! Deslocamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Deslocamentos[d1].HorarioInicioDeslocamento, Deslocamentos[d1].HorarioFinalDeslocamento, Deslocamentos[d2].HorarioInicioDeslocamento  , Deslocamentos[d2].HorarioFinalDeslocamento );
					return 0;
				}

			}
		}
	}
	// os Deslocamentos são integros entre se
	if( Imprime == 1){
		cout << " Deslocamentos integros " << endl;
	}
	return 1;
}

Carreta::~Carreta(){						// Destruidora

}

// decide qaul carreta tem menos tarefas realizadas
bool DecideQualCarretaTemMenosTarefasRealizadas ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDeDemandasAntendidas < c2.NumeroDeDemandasAntendidas );
}

// decide qaul carreta tem mais tarefas realizadas
bool DecideQualCarretaTemMaisTarefasRealizadas ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDeDemandasAntendidas > c2.NumeroDeDemandasAntendidas );
}

// decide a carreta que tem menor indice
bool DecideCarretaAnterior ( Carreta c1, Carreta c2 ){
	return ( c1.NumeroDaCarreta < c2.NumeroDaCarreta );
}


class ConjuntoCarretas{

public:
	ConjuntoCarretas();
	vector< Carreta > Carretas;

	void IniciaConjuntoCarretas(int NumeroCaminhoes, int NumeroDaPlanta);				// inicia os dados e as estruturas dos veículos
	void OrdenaCarretasPorNumeroDeTarefasRealizadas(int TipoOrdenacao);					// ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
	int DeletaTarefa(  int NumeroCaminhao, double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda);		// deleta tarefa realizada por um veiculo

	int AlocaInidiceVeiculo( int NumCarretaUtilizada, int &v);		// aloca o inidice do veiculo crrespondente ao numero do caminhão
	void Imprime(int Ordena);										// Imprime os dados dos veiculos

	int RetornaDadosDeslocamento(int Construcao, int Demanda, double &HorarioInicio, double &HorarioFinal);			// retorna dados de deslocamento da deamnda de uma construção passados
	int VerificaIntegridadeDeDeslocamentosDasCarretas(int Imprime);													// verifica a integridade entre os Deslocamentos da Carreta


	~ConjuntoCarretas();
};


ConjuntoCarretas::ConjuntoCarretas(){

}

// inicia os dados e as estruturas dos veículos
void ConjuntoCarretas::IniciaConjuntoCarretas(int NumeroCaminhoes, int NumeroDaPlanta){
	// inicia a estrutura
	Carretas.resize(NumeroCaminhoes);
	// percorre todos os cainhões
	for(int v = 0; v < NumeroCaminhoes; v++){
		//assinala o numero de cada caminhão
		Carretas[v].NumeroDaCarreta = v;
		// inicia os valores iniciais de todos os caminhõpes
		Carretas[v].NumeroDeDemandasAntendidas = 0;
		Carretas[v].Deslocamentos.clear();
		Carretas[v].NumeroPlanta = NumeroDaPlanta;
	}

}

// ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
void ConjuntoCarretas::OrdenaCarretasPorNumeroDeTarefasRealizadas(int TipoOrdenacao){
	if( TipoOrdenacao == 1){
		sort (Carretas.begin(), Carretas.end(), DecideQualCarretaTemMenosTarefasRealizadas);
	}
	if( TipoOrdenacao == 2){
			sort (Carretas.begin(), Carretas.end(),DecideQualCarretaTemMaisTarefasRealizadas);
	}
}

// deleta tarefa realizada por um veiculo
int ConjuntoCarretas::DeletaTarefa( int NumeroCaminhao, double HoraInicio, double HoraFinal, int NumContrucao, int NumDemanda){
	int Retirou;
	Retirou = 0;

	// percorre por todas as carretas
	for( unsigned int c = 0; c < Carretas.size(); c++){
		// verifica se a carreta corrente tem o mesmo numero que o numero da carreta passada na função
		if( Carretas[c].NumeroDaCarreta == NumeroCaminhao){
			// deleta a tarefa na carreta
			Retirou = Carretas[c].DeletaAtividade(HoraInicio, HoraFinal, NumContrucao, NumDemanda);
			if( Retirou == 1){
				// caso conseguiu retirar, retorna 1
				return 1;
			}else{
				cout << endl << endl << " ###########################   Problema! Não encontrou elemento deslocamento [" << NumContrucao << "-" << NumDemanda << "] a deletar !  -> ConjuntoCarretas::DeletaTarefa ################## " << endl << endl;
				// caso não conseguiu retirar, retorna 0
				return 0;
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou caminhao [" << NumeroCaminhao << "] a deletar !  -> ConjuntoCarretas::DeletaTarefa ################## " << endl << endl;
	// caso não encontrou a carreta, retorna 0
	return 0;
}

// aloca o inidice do veiculo crrespondente ao numero do caminhão
int ConjuntoCarretas::AlocaInidiceVeiculo( int NumCarretaUtilizada, int &v){
	// percorre todos os caminhões
	for( unsigned int i = 0; i < Carretas.size(); i++){
		// caso encontrar o caminhão procurado
		if ( Carretas[i].NumeroDaCarreta == NumCarretaUtilizada ){
			// aloca o inice do caminhão
			v = i;
			// retorna 1 caso achar o caminhão
			return 1;
		}
	}
	// retorna 0 caso não achar o caminhão
	return 0;
}

// Imprime os dados dos veiculos
void ConjuntoCarretas::Imprime(int Ordena){
	// caso se queira ordenar as carretas
	if(Ordena == 1){
		sort (Carretas.begin(), Carretas.end(), DecideCarretaAnterior);
	}

	cout  << " [[[[[[  Imprime carretas  ]]]]]]" << endl;
	// percorre todas as carretas
	for( unsigned int c = 0; c < Carretas.size(); c++){
		// imprime os dados da carreta
		Carretas[c].Imprime(Ordena);
	}
}

// retorna dados de deslocamento da deamnda de uma construção passados
int ConjuntoCarretas::RetornaDadosDeslocamento(int Construcao, int Demanda, double &HorarioInicio, double &HorarioFinal){
	// percorre todas as carretas
	for( unsigned int c = 0; c < Carretas.size(); c++){
		// percorre todos os deslocamentos
		for( unsigned int d = 0; d < Carretas[c].Deslocamentos.size(); d++){
			// verifica se o deslocamento atual atende a demanda passada na função
			if( Carretas[c].Deslocamentos[d].NumeroConstrucao == Construcao && Carretas[c].Deslocamentos[d].NumeroDemandaSuprida == Demanda ){
				// armazena os valores
				HorarioInicio = Carretas[c].Deslocamentos[d].HorarioInicioDeslocamento;
				HorarioFinal = Carretas[c].Deslocamentos[d].HorarioFinalDeslocamento;
				// retorna 1 caso se encontre o deslocamento
				return 1;
			}
		}
	}
	// retorna 0 caso não se encontre o deslocamento
	cout << endl << endl << "   <<<<<<<<<<< Problema! não se encontrou o deslocamento da demanda [" << Construcao << "-" << Demanda << "] -> ConjuntoCarretas::RetornaDadosDeslocamento " << endl << endl;
	return 0;
}

// verifica a integridade entre os Deslocamentos da Carreta
int ConjuntoCarretas::VerificaIntegridadeDeDeslocamentosDasCarretas(int Imprime){
	int integro;

	integro = 1;

	// percorre todas as carretas
	for( unsigned int c = 0; c < Carretas.size(); c++){
		if( Imprime == 1){
			cout << "     Carreta [" << Carretas[c].NumeroDaCarreta << "] ";
		}
		if( Carretas[c].VerificaIntegridadeDeDeslocamentos(Imprime) == 0){
			integro = 0;
		}
	}

	// retorna se as plantas em geral tem integridade em seus carregamentos
	return integro;
}



ConjuntoCarretas::~ConjuntoCarretas(){

}


#endif /* CARRETAS_HPP_ */
