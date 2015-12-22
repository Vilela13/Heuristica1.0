/*
 * Plantas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef PLANTAS_HPP_
#define PLANTAS_HPP_

#include "Bibliotecas.hpp"

class Carregamento{
public:
	double HorarioInicioCarregamento;
	double HorarioFinalCarregamento;
	int NumeroConstrucao;
	int NumeroDemandaSuprida;
	int NumCarretaUtilizada;

	int verifica(int NumCarreta, int construcao, int Demanda, double HorarioInicioPlanta, double HorarioFimPlanta);					// Verifica se estes dados representão o carregamento em questão
};

// Verifica se estes dados representão o carregamento em questão
int Carregamento::verifica( int NumCarreta, int construcao, int Demanda, double HorarioInicioPlanta, double HorarioFimPlanta){
	// verifica se dados passados são os mesmos constidos na estrutura carregamento
	if( NumCarreta == NumCarretaUtilizada &&  construcao == NumeroConstrucao && Demanda == NumeroDemandaSuprida && HorarioInicioPlanta == HorarioInicioCarregamento && HorarioFimPlanta == HorarioFinalCarregamento){
		// são os mesmos e retorna 1
		return 1;
	}
	// não são os mesmo e retorna 0
	return 0;
}

bool DecideQualMenorInicioTempoCarregamento ( Carregamento c1, Carregamento c2 ){
	return ( c1.HorarioInicioCarregamento < c2.HorarioInicioCarregamento );
}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class Planta{

public:
	int NumeroDaPlanta;
	int NumeroVeiculos;
	ConjuntoCarretas VeiculosDaPlanta;
	vector < double > DistanciaConstrucoes;
	double TempoPlanta;
	double TempoMinimoDeFuncionamento;
	double TempoMaximoDeFuncionamento;

	vector < Carregamento > Carregamentos;

	double Makespan;

	Planta();			// conmstrutora

	int VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao);					// Verifica a possibilidade de alocação da demanda
	void AlocaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta);	// Aloca tarefa na planta
	int DeletaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta);	// Deleta tarefa na planta

	void CalculaMakespan();										// calcula o Makes pan da Planta
	void Imprime(int OrdenaPlantas, int OrdenaCarretas);		// Imprime dados da planta
	void ImprimeDistancias();									// Imprime as distancias da planta as construções

	int VerificaIntegridadeDeCarregamentos(int imprime); 					// verifica a integridade entre os Carregamentos da planta

	~Planta();			// destruidora

};

// conmstrutora
Planta::Planta(){
	NumeroDaPlanta = -13;
	NumeroVeiculos = -13;
	TempoPlanta = -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	Carregamentos.clear();
	Makespan = -13;
}
// Verifica a possibilidade de alocação da demanda
int Planta::VerificaDisponibilidade( double InicioPossivelAlocacao, double FinalPossivelAlocacao){
	//verifica se respeita os intervalos de atendimento da planta
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	// verifica se não viola outros acrregamentos que são realizados pela planta
	for( unsigned int c = 0; c < Carregamentos.size(); c++){
		// carregamento a alocar está dentro de outro carregamento
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		// carregamento a alocar contem outro carregamento
		if( InicioPossivelAlocacao >= Carregamentos[c].HorarioInicioCarregamento){
			if ( FinalPossivelAlocacao <= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
		// Carregamento possui sua parte final conflitando com a parte fronteira de outro carregamento
		if( InicioPossivelAlocacao <= Carregamentos[c].HorarioInicioCarregamento){
			if( FinalPossivelAlocacao > Carregamentos[c].HorarioInicioCarregamento){
				return 0;
			}
		}
		// Carregamento possui sua parte inicial conflitando com a parte posterior de outro carregamento
		if( InicioPossivelAlocacao < Carregamentos[c].HorarioFinalCarregamento){
			if ( FinalPossivelAlocacao >= Carregamentos[c].HorarioFinalCarregamento){
				return 0;
			}
		}
	}
	// é possivel, retorna 1
	return 1;
}

// Aloca tarefa na planta
void Planta::AlocaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
	Carregamento CarregamentoAux;

	// aloca os dados do carregamento
	CarregamentoAux.HorarioInicioCarregamento = HoraInicio;
	CarregamentoAux.HorarioFinalCarregamento = HoraFinal;
	CarregamentoAux.NumeroConstrucao = NumConstrucao;
	CarregamentoAux.NumeroDemandaSuprida = NumDemanda;
	CarregamentoAux.NumCarretaUtilizada = Carreta;

	// insere carregamento
	Carregamentos.insert(Carregamentos.begin(), CarregamentoAux );

}

// Deleta tarefa na planta
int Planta::DeletaAtividade(double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
	// percorre por todos os carregamentos
	for( vector < Carregamento >::iterator it = Carregamentos.begin(); it != Carregamentos.end(); it++){
		//verifica se o horario inicio e final passados correspondem com o do carregamento corrente
		if( it->HorarioInicioCarregamento == HoraInicio && it->HorarioFinalCarregamento == HoraFinal){
			//verifica se a cosntrução e demanda passados correspondem com o do carregamento corrente
			if( it->NumeroConstrucao == NumConstrucao && it->NumeroDemandaSuprida == NumDemanda){
				//verifica se a carreta passada correspondem com o do carregamento corrente
				if( it->NumCarretaUtilizada == Carreta){
					// deleta carregamento
					Carregamentos.erase(it);
					// retorna 1, foi encontrado carregam,ento e ele foi deletado
					return 1;
				}
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou elemento carregamento [" << NumConstrucao << "-" << NumDemanda << "] a deletar !  -> Planta::DeletaAtividade ################## " << endl << endl;
	// não se conseguiu encontrar o carregamento
	return 0;
}

// calcula o MakesPan da Planta
void Planta::CalculaMakespan(){
	Makespan = 0;

	// inicia o makespan da planta com o menor tempo que a planta pode iniciar um carregamento
	if( Makespan > TempoMinimoDeFuncionamento){
		Makespan = TempoMinimoDeFuncionamento;
	}
	// percorre por todos os caminhões das plantas
	for( unsigned int v = 0; v < VeiculosDaPlanta.Carretas.size(); v++){
		// percorre por todos os delocamentos do caminhão corrente
		for( unsigned int d = 0; d < VeiculosDaPlanta.Carretas[v].Deslocamentos.size(); d++){
			// se o tempo de retorno do deslocamento for maior que o mekespan da planta no momento, entra no if
			if( Makespan < VeiculosDaPlanta.Carretas[v].Deslocamentos[d].HorarioFinalDeslocamento){
				// atualiza o makespan da planta com o horario final do deslocamento corrente
				Makespan = VeiculosDaPlanta.Carretas[v].Deslocamentos[d].HorarioFinalDeslocamento;
			}
		}
	}
}

// Imprime dados da planta
void Planta::Imprime(int OrdenaPlantas, int OrdenaCarretas){
	printf ("\n# Planta %d com %d veiculos, funciona de (%.4f - %.4f)\n", NumeroDaPlanta,NumeroVeiculos,TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento);

	// entra acso se tiver que ordenar os carregamentos em ordem crescente
	if(OrdenaPlantas == 1){
		// oderna os carregamentos da planta em ordem cresecnte
		sort (Carregamentos.begin(), Carregamentos.end(), DecideQualMenorInicioTempoCarregamento);
	}
	// caso existir carregamento, entrar
	if ( Carregamentos.size() != 0 ){
		cout << "   Carregamentos " << endl;
		// percorrer todos os carregamentos
		for( unsigned int c = 0; c < Carregamentos.size(); c++){
			// imprimir o carregamento
			printf ("    * Caminhao [%d - %d] para suprir construcao [%d - %d] das ( %.4f as %.4f)\n", NumeroDaPlanta, Carregamentos[c].NumCarretaUtilizada, Carregamentos[c].NumeroConstrucao, Carregamentos[c].NumeroDemandaSuprida, Carregamentos[c].HorarioInicioCarregamento, Carregamentos[c].HorarioFinalCarregamento);
		}
	}
// Imprime os veículos da planta
	cout <<  "    =>  Veiculos da Planta " << NumeroDaPlanta << " <= " << endl;
	// imprimir os veiculos da planta
	VeiculosDaPlanta.Imprime(OrdenaCarretas);
	// imprimir o makespan da planta
	cout << "   Makespan = " << Makespan << endl;

}

// Imprime as distancias da planta as construções
void Planta::ImprimeDistancias(){
	cout << " +++ Distancias ++++ " << endl;
	cout << "Numero de conatricoes " << DistanciaConstrucoes.size() << endl;
	// percorre por todas as construções
	for ( unsigned int c = 0; c < DistanciaConstrucoes.size(); c++){
		// imprime a distancia da planta a construção corrente
		printf("   Contrucao %d = %.4f", c, DistanciaConstrucoes[c]);
	}
}

// verifica a integridade entre os Carregamentos da planta
int Planta::VerificaIntegridadeDeCarregamentos(int imprime){
	// percorre todos os carregamentos
	for( int c1 = 0; c1 < (int) Carregamentos.size(); c1++){
		// verifica se o carregamento não possui tempo negativo
		if( Carregamentos[c1].HorarioInicioCarregamento > Carregamentos[c1].HorarioFinalCarregamento ){
			printf( " >>>>>>>>>>>>>> Problema! Carregamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Carregamentos[c1].HorarioFinalCarregamento - Carregamentos[c1].HorarioInicioCarregamento  , Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
			return 0;
		}
		// percorre todos os carregamentos
		for( int c2 = 0; c2 < (int)  Carregamentos.size(); c2++){
			// o Carregamento não pode ser o memso que o analisado no primeiro loop
			if( Carregamentos[c1].HorarioInicioCarregamento != Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento != Carregamentos[c2].HorarioFinalCarregamento){
				// verifica se o Carregamento está contido dentro de outro Carregamento
				if( Carregamentos[c1].HorarioInicioCarregamento <= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento >= Carregamentos[c2].HorarioFinalCarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento, Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
					return 0;
				}
				// verifica se o Carregamento  contem  outro Carregamento
				if( Carregamentos[c1].HorarioInicioCarregamento >= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento <= Carregamentos[c2].HorarioFinalCarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento, Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
					return 0;
				}
				// verifica se o Carregamento  está parcialmente contido na parte inicial de  outro Carregamento
				if( Carregamentos[c1].HorarioFinalCarregamento >= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento <= Carregamentos[c2].HorarioFinalCarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento, Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento );
					return 0;
				}
				// verifica se o Carregamento  está parcialmente contido na parte final de  outro Carregamento
				if( Carregamentos[c1].HorarioInicioCarregamento >= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioInicioCarregamento <= Carregamentos[c2].HorarioFinalCarregamento ){
					printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento, Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento );
					return 0;
				}

			}
		}
	}
	// os Carregamentos são integros entre se
	if( imprime == 1){
		cout << " Carregamentos integros " << endl;
	}
	return 1;
}

// destruidora
Planta::~Planta(){

}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class ConjuntoPlantas{

public:

	vector< Planta > Plantas;
	vector < int > PlantasAnalizadas;

	vector < double > HorarioQuePlantaPodeAtender; 		// Vetor que guarda o primeiro horario que a planta pode passar a atender essa demanda caso as demandas porteriores forem atrazadas
	vector < double > HorarioQueConstrucaoPodeReceberDemanda;

	double MakespanPLantas;

	ConjuntoPlantas();			// Cosntrutora da classe

	void InicializaPlantasAnalizadas();			// Faz que nenhuma planta tenha sido analisada pelos algoritmos
	int AnalizouTodasPLanats();					// Verifica se já analisou todas as plantas
	void IniciaConjuntoPlantas(int Numero);		// Inicia o vetor de plantas da classe com o número de palnats que se quer

	int DeletaTarefa( int NumPlanta, double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, double HoraInicioCarreta, double HoraFinalCarreta);			// deleta tarefa tanto na planta e no veiculo que executa a tarefa
	void CalculaMakespanPlantas();			// Calcula o Makespan de todas as Plantas
	int AlocaInidiceFabrica( int Planta, int &IndicePlanta);			// Aloca o inice da planta que corresponde a planat que se passa como parametro

	int CorrigeReferenciaCarregamentoDeslocamentoMaisUm(int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, double HorarioInicioDescarregamento,  double HorarioFinalDescarregamento);		// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em mais um
	int CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento);					// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em menos um
	void Imprime(int OrdenaPlantas,int OrdenaCarrtas);		// Imprime os dados das plantas

	int VerificaPlantasAnalizadasPodemAtenderSeAtrazar();			// verifica se uma das plantas em questão pode atender a demanda em questão caso de atrazar o atendimento das outras demandas da construção que se quer atender
	void InicializaVetorHorarioQuePlantaPodeAtender();				// inicializa os horarios que as plantas podem atender certa demanda e a cosntrução pode ser atendida, caso das outras demandas anteriores a esta forem atrazadas, com o valor DBL_MAX
	double RetornaMenorHorarioQueConstrucaoPodeReceberDemanda();	// retorna o menor horario que a construção pode recerber a demanda que não é atendida no momento

	int RetornaDadosDemandaAtendida( int Construcao, int Demanda, double &HorarioInicio, double &HorarioFinal, int &planta, int &Carreta, double &HorarioInicioCarreta, double &HorarioFinalCarreta);				// Retorna os dados do carregaemnto de uma certa demanda passada na função
	int VerificaIntegridadeDeCarregamentosDasPlantas(int imprime);					// verifica a integridade dos carregamentos realizados pelas plantas
	int VerificaIntegridadeDeDeslocaemntosDosVeiculosDasPlantas(int imprime);		// verifica a integridade dos deslocamentos realizados pelos veiculos das plantas

	~ConjuntoPlantas();		// destruidora
};

// Cosntrutora da classe
ConjuntoPlantas::ConjuntoPlantas(){
	MakespanPLantas = -13;
}

// Faz que nenhuma planta tenha sido analisada pelos algoritmos
void ConjuntoPlantas::InicializaPlantasAnalizadas(){
	// inicia estrutura de plantas
	PlantasAnalizadas.resize(Plantas.size());
	// percorre todas as plantas
	for( unsigned  int p = 0; p < Plantas.size(); p++){
		// faz a planta corrente não ter sido analizada
		PlantasAnalizadas[p] = 0;
	}
}

// Verifica se já analisou todas as plantas
int ConjuntoPlantas::AnalizouTodasPLanats(){
	// percorre todas as plantas
	for ( unsigned  int p = 0; p < Plantas.size(); p++){
		// verifica se a planta corrente não foi analizada
		if( PlantasAnalizadas[p] == 0){
			// retorna 0, pois ainda tem planta a analizar
			return 0;
		}
	}
	// retorna 1, não se tem mais plantas a analisar
	return 1;
}

// Inicia o vetor de plantas da classe com o número de palnats que se quer
void ConjuntoPlantas::IniciaConjuntoPlantas(int Numero){
	// inicia estrutura de plantas
	Plantas.resize(Numero);

}


// deleta tarefa tanto na planta e no veiculo que executa a tarefa
int ConjuntoPlantas::DeletaTarefa( int NumPlanta, double HoraInicio, double HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, double HoraInicioCarreta, double HoraFinalCarreta){
	// variaveis de controle
	int RetirouCarregamento;
	RetirouCarregamento = 0;

	int RetirouDeslocamento;
	RetirouDeslocamento = 0;

	// percorre todas as plantas
	for( unsigned int p = 0; p < Plantas.size(); p++){
		// caso a planta passada for a mesma que a planta corrente
		if( Plantas[p].NumeroDaPlanta == NumPlanta){
			// retira tarefa da planta
			RetirouCarregamento = Plantas[p].DeletaAtividade( HoraInicio, HoraFinal, NumConstrucao, NumDemanda, Carreta);
			// retira tarefa do caminhão
			RetirouDeslocamento = Plantas[p].VeiculosDaPlanta.DeletaTarefa(Carreta, HoraInicioCarreta, HoraFinalCarreta, NumConstrucao, NumDemanda);
			if( RetirouCarregamento == 1 && RetirouDeslocamento == 1){
				// conseguiu retirar tanto da planta e do veiculo que realiza o transporte
				return 1;
			}else{
				if( RetirouCarregamento != 1){
					// não conseguiu retirar tanto da planta
					cout << endl << endl << " ###########################   Problema! Não encontrou elemento carregamento [" << NumConstrucao << "-" << NumDemanda << "] a deletar na planta [" << NumPlanta << "] !  -> ConjuntoPlantas::DeletaTarefa ################## " << endl << endl;
				}
				if( RetirouDeslocamento != 1){
					// não conseguiu retirar do veiculo que realiza o transporte
					cout << endl << endl << " ###########################   Problema! Não encontrou elemento delocamento [" << NumConstrucao << "-" << NumDemanda << "] da carreta [" << Carreta << "] a deletar !  -> ConjuntoPlantas::DeletaTarefa ################## " << endl << endl;
				}
				// problema em retirar a tarefa do veiculo ou da planta, ou os dois
				return 0;
			}
		}
	}
	cout << endl << endl << " ###########################   Problema! Não encontrou planta [" << NumPlanta << "] a deletar !  -> ConjuntoPlantas::DeletaTarefa ################## " << endl << endl;
	// problema em encontrar a planta passada
	return 0;

}

// Calcula o Makespan de todas as Plantas
void ConjuntoPlantas::CalculaMakespanPlantas(){
	MakespanPLantas = 0;
	// percorre todas as plantas
	for( unsigned int p = 0; p < Plantas.size(); p++){
		// calcula o makespan da planta corrente
		Plantas[p].CalculaMakespan();
		// soma o makespan da planta corrente ao makespan total de todas as plantas
		MakespanPLantas = MakespanPLantas + Plantas[p].Makespan;
	}
}

// Aloca o inice da planta que corresponde a planat que se passa como parametro
int ConjuntoPlantas::AlocaInidiceFabrica(int Planta, int &IndicePlanta){
	// percorre todas as plantas
	for ( unsigned int i  = 0; i < Plantas.size(); i ++){
		// caso a planta crrente for a procuraada
		if( Plantas[i].NumeroDaPlanta == Planta){
			// aloca o indice da planta corrente
			IndicePlanta = i;
			// encontrou a planta procurada
			return 1;
		}
	}
	cout << endl << endl << " <<<<<<<<<<<< Problema! Não encontrou a planta [" << Planta << "] -> ConjuntoPlantas::AlocaInidiceFabrica " << endl << endl ;
	// não conseguiu encnontrar a planta procurada
	return 0;
}


// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em mais um
int ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm( int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, double HorarioInicioDescarregamento,  double HorarioFinalDescarregamento ){
// Emcontra o indice da planta
	int p;
	if( AlocaInidiceFabrica(NumPlantaFornecedor,p) == 0){
		cout << endl << endl << " <<<<<<<< probelam com indice planta [" << NumPlantaFornecedor << "] => " << p << " -> ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa na planta
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].DistanciaConstrucoes[construcao] -  Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta + Plantas[p].TempoPlanta;

// Modifica o número da demanda suprida pela planta em questão em mais um
	int ModificouCarregamento;
	ModificouCarregamento = 0;

	for( unsigned int c = 0; c < Plantas[p].Carregamentos.size() ; c++){
		if( Plantas[p].Carregamentos[c].verifica( NumCarretaUtilizada, construcao, NumeroDemandaSuprida, HorarioInicioPlanta, HorarioFimPlanta) == 1 && ModificouCarregamento == 0){
			Plantas[p].Carregamentos[c].NumeroDemandaSuprida = Plantas[p].Carregamentos[c].NumeroDemandaSuprida + 1;
			ModificouCarregamento = 1;
		}
	}

// Emcontra o indice do veículo
	int v;
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarretaUtilizada, v) == 0 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarretaUtilizada << "] => " << v << " ->CorrigeReferenciaCarregamentoDeslocamentoMaisUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa no caminhão (veículo)
	double HorarioInicioVeiculo;
	double HorarioFimVeiculo;

	HorarioInicioVeiculo = HorarioInicioPlanta;
	HorarioFimVeiculo = HorarioFinalDescarregamento + Plantas[p].DistanciaConstrucoes[construcao];

// Modifica o número da demanda suprida pelo caminhão (veículo) em questão em mais um
	int ModificouDeslocamento;
	ModificouDeslocamento = 0;

	for( unsigned int d = 0; d < Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.size() ; d++){
		if( Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].verifica( construcao, NumeroDemandaSuprida, HorarioInicioVeiculo, HorarioFimVeiculo) == 1 && ModificouDeslocamento == 0){
			Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida = Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida + 1;
			ModificouDeslocamento = 1;
		}
	}

// verifica se realizou as mudanças desejadas
	if( ModificouCarregamento == 1 && ModificouDeslocamento == 1){
		return 1;
	}else{
		if( ModificouCarregamento == 0 ){
			cout << endl << endl << " <<<<<<<< probelam em corrigir carregamento [" << construcao << "-" << NumeroDemandaSuprida << "] ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		if( ModificouDeslocamento == 0){
			cout << endl << endl << " <<<<<<<< probelam em corrigir deslocamento [" << construcao << "-" << NumeroDemandaSuprida << "]  ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		return 0;
	}

}

// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em menos um
int ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, double HorarioInicioDescarregamento, double HorarioFinalDescarregamento){

// Emcontra o indice da planta
	int p;
	if( AlocaInidiceFabrica(NumPlanta,p) == 0){
		cout << endl << endl << " <<<<<<<< problema com indice planta [" << NumPlanta << "] => " << p << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa na planta
	double HorarioInicioPlanta;
	double HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].DistanciaConstrucoes[Construcao] -  Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  Plantas[p].TempoPlanta;

// Modifica o número da demanda suprida pela planta em questão em mais um
	int ModificouCarregamento;
	ModificouCarregamento = 0;

	for( unsigned int c = 0; c < Plantas[p].Carregamentos.size() ; c++){
		if( Plantas[p].Carregamentos[c].verifica(NumCarreta, Construcao, Demanda, HorarioInicioPlanta, HorarioFimPlanta) == 1 && ModificouCarregamento == 0){
			Plantas[p].Carregamentos[c].NumeroDemandaSuprida = Plantas[p].Carregamentos[c].NumeroDemandaSuprida - 1;
			ModificouCarregamento = 1;
		}
	}

// Emcontra o indice do veículo
	int v;
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarreta, v) == 0 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarreta << "] => " << v << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa no caminhão (veículo)
	double HorarioInicioVeiculo;
	double HorarioFimVeiculo;

	HorarioInicioVeiculo = HorarioInicioPlanta;
	HorarioFimVeiculo = HorarioFinalDescarregamento + Plantas[p].DistanciaConstrucoes[Construcao];

// Modifica o número da demanda suprida pelo caminhão (veículo) em questão em mais um
	int ModificouDeslocamento;
	ModificouDeslocamento = 0;

	for( unsigned int d = 0; d < Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.size() ; d++){
		if( Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].verifica( Construcao, Demanda, HorarioInicioVeiculo, HorarioFimVeiculo) == 1 && ModificouDeslocamento == 0){
			Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida = Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos[d].NumeroDemandaSuprida - 1;
			ModificouDeslocamento = 1;
		}
	}

// verifica se realizou as mudanças desejadas
	if( ModificouCarregamento == 1 && ModificouDeslocamento == 1){
		return 1;
	}else{
		if( ModificouCarregamento == 0 ){
			cout << endl << endl << " <<<<<<<< probelam em corrigir carregamento [" << Construcao << "-" << Demanda << "] ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		if( ModificouDeslocamento == 0){
			cout << endl << endl << " <<<<<<<< probelam em corrigir deslocamento [" << Construcao << "-" << Demanda << "]  ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
		}
		return 0;
	}
}

// Imprime os dados das plantas
void ConjuntoPlantas::Imprime(int OrdenaPlantas,int OrdenaCarrtas){
	cout << endl << endl << " [[[[[[  Imprime plantas  ]]]]]]" << endl;
	// percorre todas as plantas
	for( unsigned int p = 0; p < Plantas.size(); p++){
		// imprime a planta corrente
		Plantas[p].Imprime(OrdenaPlantas, OrdenaCarrtas);
	}
	// escreve o makespan das plantas
	printf ("\n  Makespan Geral das Plantas = %.4f\n", MakespanPLantas);
}

// verifica se uma das plantas em questão pode atender a demanda em questão caso de atrazar o atendimento das outras demandas da construção que se quer atender
int ConjuntoPlantas::VerificaPlantasAnalizadasPodemAtenderSeAtrazar(){
	// percorre todas as plantas
	for ( unsigned  int p = 0; p < Plantas.size(); p++){
		// verifica se a planta corrente pode atender a demanda em questão caso se atrazar o atendiemnto das demandas posteriores a demanda em questão
		if( PlantasAnalizadas[p] == -2){
			// retorna 1 caso isso for possivel
			return 1;
		}
	}
	// naõ se consegue atender a demanda mesmo se atrazar as demandas anteriores a demanda em questão
	return 0;

}

// inicializa os horarios que as plantas podem atender certa demanda e a cosntrução pode ser atendida, caso das outras demandas anteriores a esta forem atrazadas, com o valor DBL_MAX
void ConjuntoPlantas::InicializaVetorHorarioQuePlantaPodeAtender(){
	// inicia os vetores com o numero de plantas
	HorarioQuePlantaPodeAtender.resize(Plantas.size());
	HorarioQueConstrucaoPodeReceberDemanda.resize(Plantas.size());
	// faz para toda planta
	for( unsigned int p = 0; p < HorarioQuePlantaPodeAtender.size(); p++){
		// inicia com o valor maximo de double o horario que a planta pode atender e a construção pode ser atendida
		HorarioQuePlantaPodeAtender[p] = DBL_MAX;
		HorarioQueConstrucaoPodeReceberDemanda[p] = DBL_MAX;
	}
}

// retorna o menor horario que a construção pode recerber a demanda que não é atendida no momento
double ConjuntoPlantas::RetornaMenorHorarioQueConstrucaoPodeReceberDemanda(){
	double HoraAux;
	HoraAux = DBL_MAX;

	// faz para toda planta
	for( int p = 0; p < (int) HorarioQuePlantaPodeAtender.size(); p++){
		// caso o horario que a cosntrução pode receber a demanda corrente for maior que o que a planta pode atender a demanda, entra no if
		if( HorarioQueConstrucaoPodeReceberDemanda[p] < HoraAux){
			// atualiza o menor horario que a cosntrução pode receber a demanda
			HoraAux = HorarioQueConstrucaoPodeReceberDemanda[p];
		}
	}
	// retorna o menor horario que a demanda pode ser atendida
	return HoraAux;
}

// Retorna os dados do carregaemnto de uma certa demanda passada na função
int ConjuntoPlantas::RetornaDadosDemandaAtendida(int Construcao, int Demanda, double &HorarioInicio, double &HorarioFinal, int &planta, int &Carreta, double &HorarioInicioCarreta, double &HorarioFinalCarreta){
	// percorre todas as plantas
	for( unsigned int p = 0; p < Plantas.size(); p++){
		// percorre todos os carregamentotos da planta
		for( unsigned int c = 0; c < Plantas[p].Carregamentos.size(); c++){
			// casso o carregamento corrente atender a demanda da construução passada na função, entra
			if( Plantas[p].Carregamentos[c].NumeroConstrucao == Construcao && Plantas[p].Carregamentos[c].NumeroDemandaSuprida == Demanda){
				// armazena os valores do carregamento
				HorarioInicio = Plantas[p].Carregamentos[c].HorarioInicioCarregamento ;
				HorarioFinal  = Plantas[p].Carregamentos[c].HorarioFinalCarregamento;
				planta = Plantas[p].NumeroDaPlanta;
				Carreta = Plantas[p].Carregamentos[c].NumCarretaUtilizada;
				// pega os dados do deslocamento
				if( Plantas[p].VeiculosDaPlanta.RetornaDadosDeslocamento(Construcao, Demanda, HorarioInicioCarreta, HorarioFinalCarreta) == 0 ){
					cout << endl << endl << " <<<<<<<<<<<  Problema!  Não encontrou deslocamento demanda [" << Construcao << "-" << Demanda << "] -> ConjuntoPlantas::RetornaDadosDemandaAtendida" << endl << endl;
				}
				// retorna 1, encontrou o descarregamento
				return 1;
			}
		}
	}
	cout << endl << endl << " <<<<<<<<<<<  Problema!  Não encontrou carregamento demanda [" << Construcao << "-" << Demanda << "] -> ConjuntoPlantas::RetornaDadosDemandaAtendida" << endl << endl;
	// retorna 0, não encontrou o descarregamento
	return 0;

}

// verifica a integridade dos carregamentos realizados pelas plantas
int ConjuntoPlantas::VerificaIntegridadeDeCarregamentosDasPlantas(int imprime){
	int integro;
	// inicia com integro o estado dos carregamentos
	integro = 1;

	if( imprime == 1){
		cout << endl << endl << "  Verifica integridade carregamentos " << endl << endl;
	}
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		if( imprime == 1){
			cout << " planta [" << Plantas[p].NumeroDaPlanta << "] ";
		}
		// verica a integridade dos carregamentos da planta corrente
		if ( Plantas[p].VerificaIntegridadeDeCarregamentos(imprime) == 0){
			// caso não for integro, atualiza a variavel de saida
			integro = 0;
		}
	}
	// retorna se as plantas em geral tem integridade em seus carregamentos
	return integro;
}

// verifica a integridade dos deslocamentos realizados pelos veiculos das plantas
int ConjuntoPlantas::VerificaIntegridadeDeDeslocaemntosDosVeiculosDasPlantas(int imprime){
	int integro;
	// inicia como integro o estado dos deslocamentos
	integro = 1;

	if( imprime == 1){
		cout << endl << "          Verifica integridade Deslocamentos  " << endl << endl;
	}
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		if( imprime == 1){
			cout << "   Planta [" << Plantas[p].NumeroDaPlanta << "]" << endl ;
		}
		// verifica a integridade dos deslocaentos dos veiculos da planta
		if( Plantas[p].VeiculosDaPlanta.VerificaIntegridadeDeDeslocamentosDasCarretas(imprime) == 0){
			// caso não for integro, atualiza a variavel de saida
			integro = 0;
		}
	}
	// retorna se existe algum deslocamento que não esta integro ao retorna 0, ou 1 caso contrario
	return integro;
}

// destruidora
ConjuntoPlantas::~ConjuntoPlantas(){

}

#endif /* PLANTAS_HPP_ */
