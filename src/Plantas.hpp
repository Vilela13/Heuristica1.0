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
	float 	HorarioInicioCarregamento;
	float 	HorarioFinalCarregamento;
	int 	NumeroConstrucao;
	int 	NumeroDemandaSuprida;
	int 	NumCarretaUtilizada;

	int 	verifica(int NumCarreta, int construcao, int Demanda, float HorarioInicioPlanta, float HorarioFimPlanta);					// Verifica se estes dados representão o carregamento em questão
};

// Verifica se estes dados representão o carregamento em questão
int 	Carregamento::verifica( int NumCarreta, int construcao, int Demanda, float HorarioInicioPlanta, float HorarioFimPlanta){
	// verifica se dados passados são os mesmos constidos na estrutura carregamento
	if( NumCarreta == NumCarretaUtilizada &&  construcao == NumeroConstrucao && Demanda == NumeroDemandaSuprida && HorarioInicioPlanta == HorarioInicioCarregamento && HorarioFimPlanta == HorarioFinalCarregamento){
		// são os mesmos e retorna 1
		return 1;
	}
	// não são os mesmo e retorna 0
	return 0;
}

bool 	DecideQualMenorInicioTempoCarregamento ( Carregamento c1, Carregamento c2 ){
	return ( c1.HorarioInicioCarregamento < c2.HorarioInicioCarregamento );
}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class Planta{

public:
	int 	NumeroDaPlanta;
	int 	NumeroVeiculos;
	ConjuntoCarretas VeiculosDaPlanta;
	vector < float > TempoParaConstrucoes;
	float 	TempoPlanta;
	float 	TempoMinimoDeFuncionamento;
	float 	TempoMaximoDeFuncionamento;

	vector < Carregamento > Carregamentos;

	float 	Makespan;

	int		PlantasAnalizadas;
	float	HorarioQuePlantaPodeAtender; 		// guarda o primeiro horario que a planta pode passar a atender essa demanda caso as demandas porteriores forem atrazadas
	float 	HorarioQueConstrucaoPodeReceberDemanda;


	// Funções

	Planta();			// conmstrutora

	int 	VerificaDisponibilidade( float InicioPossivelAlocacao, float FinalPossivelAlocacao);					// Verifica a possibilidade de alocação da demanda
	void 	AlocaAtividade(float HoraInicio, float HoraFinal, int NumConstrucao, int NumDemanda, int Carreta);	// Aloca tarefa na planta
	int 	DeletaAtividade(float HoraInicio, float HoraFinal, int NumConstrucao, int NumDemanda, int Carreta);	// Deleta tarefa na planta

	void 	CalculaMakespan();										// calcula o Makes pan da Planta
	void 	Imprime(int OrdenaPlantas, int OrdenaCarretas, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// Imprime dados da planta
	void 	ImprimeTempos();									// Imprime as distancias da planta as construções

	int 	VerificaIntegridadeDeCarregamentos(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo); 					// verifica a integridade entre os Carregamentos da planta

	~Planta();			// destruidora

};

// conmstrutora
Planta::Planta(){
	NumeroDaPlanta 	= -13;
	NumeroVeiculos 	= -13;
	TempoPlanta 	= -13;
	TempoMinimoDeFuncionamento = -13;
	TempoMaximoDeFuncionamento = -13;
	Carregamentos.clear();
	Makespan 		= -13;
	PlantasAnalizadas 			= -13;
	HorarioQuePlantaPodeAtender = -13;
	HorarioQueConstrucaoPodeReceberDemanda = -13;
}
// Verifica a possibilidade de alocação da demanda
int 	Planta::VerificaDisponibilidade( float InicioPossivelAlocacao, float FinalPossivelAlocacao){
	//verifica se respeita os intervalos de atendimento da planta
	if( InicioPossivelAlocacao < TempoMinimoDeFuncionamento){
		return 0;
	}
	if( InicioPossivelAlocacao > TempoMaximoDeFuncionamento){
		return 0;
	}

	// verifica se não viola outros acrregamentos que são realizados pela planta
	for(  int c = 0; c < (int) Carregamentos.size(); c++){
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
void 	Planta::AlocaAtividade(float HoraInicio, float HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
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
int 	Planta::DeletaAtividade(float HoraInicio, float HoraFinal, int NumConstrucao, int NumDemanda, int Carreta){
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
void 	Planta::CalculaMakespan(){
	Makespan = 0;

	// inicia o makespan da planta com o menor tempo que a planta pode iniciar um carregamento
	if( Makespan > TempoMinimoDeFuncionamento){
		Makespan = TempoMinimoDeFuncionamento;
	}
	// percorre por todos os caminhões das plantas
	for( int v = 0; v < (int) VeiculosDaPlanta.Carretas.size(); v++){
		// percorre por todos os delocamentos do caminhão corrente
		for( int d = 0; d < (int) VeiculosDaPlanta.Carretas[v].Deslocamentos.size(); d++){
			// se o tempo de retorno do deslocamento for maior que o mekespan da planta no momento, entra no if
			if( Makespan < VeiculosDaPlanta.Carretas[v].Deslocamentos[d].HorarioFinalDeslocamento){
				// atualiza o makespan da planta com o horario final do deslocamento corrente
				Makespan = VeiculosDaPlanta.Carretas[v].Deslocamentos[d].HorarioFinalDeslocamento;
			}
		}
	}
}

// Imprime dados da planta
void 	Planta::Imprime(int OrdenaPlantas, int OrdenaCarretas, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	if( ImprimeSolucao == 1){
		printf ("\n# Planta %d com %d veiculos, funciona de (%.4f - %.4f)\n", NumeroDaPlanta,NumeroVeiculos,TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento);
	}
	// imprime no arquivo
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "\n# Planta %d com %d veiculos, funciona de (%.4f - %.4f)\n", NumeroDaPlanta,NumeroVeiculos,TempoMinimoDeFuncionamento, TempoMaximoDeFuncionamento);
	}

	// entra acso se tiver que ordenar os carregamentos em ordem crescente
	if(OrdenaPlantas == 1){
		// oderna os carregamentos da planta em ordem cresecnte
		sort (Carregamentos.begin(), Carregamentos.end(), DecideQualMenorInicioTempoCarregamento);
	}
	// caso existir carregamento, entrar
	if ( Carregamentos.size() != 0 ){
		if( ImprimeSolucao == 1){
			cout << "   Carregamentos " << endl;
		}
		// imprime no arquivo
		if( ImprimeArquivo == 1){
			fprintf( Arquivo, "   Carregamentos \n");
		}
		// percorrer todos os carregamentos
		for( int c = 0; c < (int) Carregamentos.size(); c++){
			if( ImprimeSolucao == 1){
				// imprimir o carregamento
				printf ("    * Caminhao [%d - %d] para suprir construcao [%d - %d] das ( %.4f as %.4f)\n", NumeroDaPlanta, Carregamentos[c].NumCarretaUtilizada, Carregamentos[c].NumeroConstrucao, Carregamentos[c].NumeroDemandaSuprida, Carregamentos[c].HorarioInicioCarregamento, Carregamentos[c].HorarioFinalCarregamento);
			}
			// imprime no arquivo
			if( ImprimeArquivo == 1){
				fprintf( Arquivo, "    * Caminhao [%d - %d] para suprir construcao [%d - %d] das ( %.4f as %.4f)\n", NumeroDaPlanta, Carregamentos[c].NumCarretaUtilizada, Carregamentos[c].NumeroConstrucao, Carregamentos[c].NumeroDemandaSuprida, Carregamentos[c].HorarioInicioCarregamento, Carregamentos[c].HorarioFinalCarregamento);
			}
		}
	}
// Imprime os veículos da planta
	if( ImprimeSolucao == 1){
		cout <<  "    =>  Veiculos da Planta " << NumeroDaPlanta << " <= " << endl;
	}
	// imprime no arquivo
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "    =>  Veiculos da Planta %d <= \n", NumeroDaPlanta);
	}
	// imprimir os veiculos da planta
	VeiculosDaPlanta.Imprime(OrdenaCarretas, ImprimeSolucao, ImprimeArquivo, Arquivo);
	// imprimir o makespan da planta
	if( ImprimeSolucao == 1){
		cout << "   Makespan = " << Makespan << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, 	"   Makespan = %f \n", Makespan);
	}

}

// Imprime as distancias da planta as construções
void 	Planta::ImprimeTempos(){
	cout << " +++ Tempos ++++ " << endl;
	cout << "Numero de conatricoes " << TempoParaConstrucoes.size() << endl;
	// percorre por todas as construções
	for ( int c = 0; c < (int) TempoParaConstrucoes.size(); c++){
		// imprime a distancia da planta a construção corrente
		printf("   Contrucao %d = %.4f", c, TempoParaConstrucoes[c]);
	}
}

// verifica a integridade entre os Carregamentos da planta
int 	Planta::VerificaIntegridadeDeCarregamentos(int imprime,int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	// percorre todos os carregamentos
	for( int c1 = 0; c1 < (int) Carregamentos.size(); c1++){
		// verifica se o carregamento não possui tempo negativo
		if( Carregamentos[c1].HorarioInicioCarregamento > Carregamentos[c1].HorarioFinalCarregamento ){
			if( ImprimeSolucao == 1){
				printf( " >>>>>>>>>>>>>> Problema! Carregamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Carregamentos[c1].HorarioFinalCarregamento - Carregamentos[c1].HorarioInicioCarregamento  , Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
			}
			if(ImprimeArquivo ==1 ){
				fprintf(Arquivo, " >>>>>>>>>>>>>> Problema! Carregamento possui tempo negativo %.4f (%.4f-%.4f)\n",  Carregamentos[c1].HorarioFinalCarregamento - Carregamentos[c1].HorarioInicioCarregamento  , Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
			}
			return 0;
		}
		// percorre todos os carregamentos
		for( int c2 = 0; c2 < (int)  Carregamentos.size(); c2++){
			// o Carregamento não pode ser o memso que o analisado no primeiro loop
			if( Carregamentos[c1].HorarioInicioCarregamento != Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento != Carregamentos[c2].HorarioFinalCarregamento){
				// verifica se o Carregamento está contido dentro de outro Carregamento
				if( Carregamentos[c1].HorarioInicioCarregamento <= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento >= Carregamentos[c2].HorarioFinalCarregamento ){
					if( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento, Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
					}
					if(ImprimeArquivo ==1 ){
						fprintf(Arquivo," >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está contido em (%.4f-%.4f) \n", Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento, Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
					}
					return 0;
				}
				// verifica se o Carregamento  contem  outro Carregamento
				if( Carregamentos[c1].HorarioInicioCarregamento >= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento <= Carregamentos[c2].HorarioFinalCarregamento ){
					if( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento, Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
					}
					if(ImprimeArquivo ==1 ){
						fprintf(Arquivo," >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) contem (%.4f-%.4f) \n", Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento, Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento );
					}
					return 0;
				}
				// verifica se o Carregamento  está parcialmente contido na parte inicial de  outro Carregamento
				if( Carregamentos[c1].HorarioFinalCarregamento >= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioFinalCarregamento <= Carregamentos[c2].HorarioFinalCarregamento ){
					if( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento, Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento );
					}
					if(ImprimeArquivo ==1 ){
						fprintf(Arquivo, " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está parcialmente contido na parte inicial de (%.4f-%.4f) \n", Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento, Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento );
					}
					return 0;
				}
				// verifica se o Carregamento  está parcialmente contido na parte final de  outro Carregamento
				if( Carregamentos[c1].HorarioInicioCarregamento >= Carregamentos[c2].HorarioInicioCarregamento && Carregamentos[c1].HorarioInicioCarregamento <= Carregamentos[c2].HorarioFinalCarregamento ){
					if( ImprimeSolucao == 1){
						printf( " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento, Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento );
					}
					if(ImprimeArquivo ==1 ){
						fprintf(Arquivo, " >>>>>>>>>>>>>> Problema! Carregamento (%.4f-%.4f) está parcialmente contido na parte final de (%.4f-%.4f) \n", Carregamentos[c1].HorarioInicioCarregamento, Carregamentos[c1].HorarioFinalCarregamento, Carregamentos[c2].HorarioInicioCarregamento  , Carregamentos[c2].HorarioFinalCarregamento );
					}
					return 0;
				}

			}
		}
	}
	// os Carregamentos são integros entre se
	if( imprime == 1){
		if( ImprimeSolucao == 1){
			cout << " Carregamentos integros " << endl;
		}
		if(ImprimeArquivo ==1 ){
			fprintf(Arquivo, " Carregamentos integros \n");
		}
	}
	return 1;
}

// destruidora
Planta::~Planta(){
	TempoParaConstrucoes.clear();
	Carregamentos.clear();
}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

// função que retorna se p1 tem menos tarefas que que p2
bool 	DecideQualPlantaMenosTarefa(Planta p1,Planta p2) {
	if( (int) p1.Carregamentos.size() != (int) p2.Carregamentos.size() ){
		return ( (int) p1.Carregamentos.size() < (int) p2.Carregamentos.size() );
	}else{
		if( p1.TempoMaximoDeFuncionamento - p1.TempoMinimoDeFuncionamento !=  p2.TempoMaximoDeFuncionamento - p2.TempoMinimoDeFuncionamento){
			return ( p1.TempoMaximoDeFuncionamento - p1.TempoMinimoDeFuncionamento >  p2.TempoMaximoDeFuncionamento - p2.TempoMinimoDeFuncionamento);
		}else{
			if ( p1.TempoMinimoDeFuncionamento !=  p1.TempoMinimoDeFuncionamento ){
				return ( p1.TempoMinimoDeFuncionamento <  p1.TempoMinimoDeFuncionamento );
			}else{
				return ( p1.NumeroVeiculos > p2.NumeroVeiculos);
			}
		}
	}
}

// função que retorna se p1 tem mais tarefas que que p2
bool 	DecideQualPlantaMaisTarefa(Planta p1,Planta p2) {
	if( (int) p1.Carregamentos.size() != (int) p2.Carregamentos.size() ){
		return ( (int) p1.Carregamentos.size() > (int) p2.Carregamentos.size() );
	}else{
		if( p1.TempoMaximoDeFuncionamento - p1.TempoMinimoDeFuncionamento !=  p2.TempoMaximoDeFuncionamento - p2.TempoMinimoDeFuncionamento){
			return ( p1.TempoMaximoDeFuncionamento - p1.TempoMinimoDeFuncionamento >  p2.TempoMaximoDeFuncionamento - p2.TempoMinimoDeFuncionamento);
		}else{
			if ( p1.TempoMinimoDeFuncionamento !=  p1.TempoMinimoDeFuncionamento ){
				return ( p1.TempoMinimoDeFuncionamento <  p1.TempoMinimoDeFuncionamento );
			}else{
				return ( p1.NumeroVeiculos > p2.NumeroVeiculos);
			}
		}
	}
}

// Gerador Aleatorico Planta
int 	GeradorAleatoricoPlanta (int i) {
	return rand()%i;
}

// #################################################################
// #################################################################
// #################################################################
// #################################################################
// #################################################################

class ConjuntoPlantas{

public:

	vector< Planta > 	Plantas;

	float 	MakespanPLantas;

	ConjuntoPlantas();			// Cosntrutora da classe

	void 	InicializaPlantasAnalizadas();			// Faz que nenhuma planta tenha sido analisada pelos algoritmos
	int 	AnalizouTodasPLanats();					// Verifica se já analisou todas as plantas
	void 	IniciaConjuntoPlantas(int Numero);		// Inicia o vetor de plantas da classe com o número de palnats que se quer

	int 	DeletaTarefa( int NumPlanta, float HoraInicio, float HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, float HoraInicioCarreta, float HoraFinalCarreta);			// deleta tarefa tanto na planta e no veiculo que executa a tarefa
	void 	CalculaMakespanPlantas();			// Calcula o Makespan de todas as Plantas
	int 	AlocaInidiceFabrica( int Planta, int &IndicePlanta);			// Aloca o inice da planta que corresponde a planat que se passa como parametro

	int 	CorrigeReferenciaCarregamentoDeslocamentoMaisUm(int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, float HorarioInicioDescarregamento,  float HorarioFinalDescarregamento);		// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em mais um
	int 	CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, float HorarioInicioDescarregamento, float HorarioFinalDescarregamento);					// corrige as referencias da tarefa aumentando o numerod a demanda que é suprida em menos um


	int 	VerificaPlantasAnalizadasPodemAtenderSeAtrasar();			// verifica se uma das plantas em questão pode atender a demanda em questão caso de atrazar o atendimento das outras demandas da construção que se quer atender
	void 	InicializaVetorHorarioQuePlantaPodeAtender();				// inicializa os horarios que as plantas podem atender certa demanda e a cosntrução pode ser atendida, caso das outras demandas anteriores a esta forem atrazadas, com o valor DBL_MAX
	float 	RetornaMenorHorarioQueConstrucaoPodeReceberDemanda();	// retorna o menor horario que a construção pode recerber a demanda que não é atendida no momento

	int 	RetornaDadosDemandaAtendida( int Construcao, int Demanda, float &HorarioInicio, float &HorarioFinal, int &planta, int &Carreta, float &HorarioInicioCarreta, float &HorarioFinalCarreta);				// Retorna os dados do carregaemnto de uma certa demanda passada na função
	int 	VerificaIntegridadeDeCarregamentosDasPlantas(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);					// verifica a integridade dos carregamentos realizados pelas plantas
	int 	VerificaIntegridadeDeDeslocaemntosDosVeiculosDasPlantas(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// verifica a integridade dos deslocamentos realizados pelos veiculos das plantas

	void 	OrdenaPlantas( int EscolhaPlanta);
	void 	ArmazenaVetorIntComOrdem( vector < int > &VetorOrdem);

	void 	Imprime(int OrdenaPlantas,int OrdenaCarrtas,int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo);		// Imprime os dados das plantas
	void 	ImprimeHorariosPlantasPodemAtender();

	~ConjuntoPlantas();		// destruidora
};

// Cosntrutora da classe
ConjuntoPlantas::ConjuntoPlantas(){
	MakespanPLantas = -13;
}

// Faz que nenhuma planta tenha sido analisada pelos algoritmos
void 	ConjuntoPlantas::InicializaPlantasAnalizadas(){

	// percorre todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		// faz a planta corrente não ter sido analizada
		Plantas[p].PlantasAnalizadas = 0;
	}
}

// Verifica se já analisou todas as plantas
int 	ConjuntoPlantas::AnalizouTodasPLanats(){
	// percorre todas as plantas
	for ( int p = 0; p < (int) Plantas.size(); p++){
		// verifica se a planta corrente não foi analizada
		if( Plantas[p].PlantasAnalizadas == 0){
			// retorna 0, pois ainda tem planta a analizar
			return 0;
		}
	}
	// retorna 1, não se tem mais plantas a analisar
	return 1;
}

// Inicia o vetor de plantas da classe com o número de palnats que se quer
void 	ConjuntoPlantas::IniciaConjuntoPlantas(int Numero){
	// inicia estrutura de plantas
	Plantas.resize(Numero);


	// inicia os valores das estruturas da planta, as plantas analisadas como 0 e os horarios como o maximo float
	for( int p = 0; p < Numero; p++){
		Plantas[p].PlantasAnalizadas = 0;
		Plantas[p].HorarioQuePlantaPodeAtender = DBL_MAX;
		Plantas[p].HorarioQueConstrucaoPodeReceberDemanda = DBL_MAX;
	}

}


// deleta tarefa tanto na planta e no veiculo que executa a tarefa
int 	ConjuntoPlantas::DeletaTarefa( int NumPlanta, float HoraInicio, float HoraFinal, int NumConstrucao, int NumDemanda, int Carreta, float HoraInicioCarreta, float HoraFinalCarreta){
	// variaveis de controle
	int 	RetirouCarregamento;
	RetirouCarregamento = 0;

	int 	RetirouDeslocamento;
	RetirouDeslocamento = 0;

	// percorre todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
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
void 	ConjuntoPlantas::CalculaMakespanPlantas(){
	MakespanPLantas = 0;
	// percorre todas as plantas
	for(  int p = 0; p < (int) Plantas.size(); p++){
		// calcula o makespan da planta corrente
		Plantas[p].CalculaMakespan();
		// soma o makespan da planta corrente ao makespan total de todas as plantas
		MakespanPLantas = MakespanPLantas + Plantas[p].Makespan;
	}
}

// Aloca o inice da planta que corresponde a planat que se passa como parametro
int 	ConjuntoPlantas::AlocaInidiceFabrica(int Planta, int &IndicePlanta){
	// percorre todas as plantas
	for ( int i  = 0; i < (int) Plantas.size(); i ++){
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
int 	ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm( int NumPlantaFornecedor,int NumCarretaUtilizada,int construcao, int NumeroDemandaSuprida, float HorarioInicioDescarregamento,  float HorarioFinalDescarregamento ){
// Emcontra o indice da planta
	int 	p;
	if( AlocaInidiceFabrica(NumPlantaFornecedor,p) == 0){
		cout << endl << endl << " <<<<<<<< probelam com indice planta [" << NumPlantaFornecedor << "] => " << p << " -> ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMaisUm  >>>>>>>>>>>>> " << endl << endl ;
		return 0;
	}

// Encontra os tempos relativos da tarefa na planta
	float 	HorarioInicioPlanta;
	float 	HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].TempoParaConstrucoes[construcao] -  Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta + Plantas[p].TempoPlanta;

// Modifica o número da demanda suprida pela planta em questão em mais um
	int 	ModificouCarregamento;
	ModificouCarregamento = 0;

	for( int c = 0; c < (int) Plantas[p].Carregamentos.size() ; c++){
		if( Plantas[p].Carregamentos[c].verifica( NumCarretaUtilizada, construcao, NumeroDemandaSuprida, HorarioInicioPlanta, HorarioFimPlanta) == 1 && ModificouCarregamento == 0){
			Plantas[p].Carregamentos[c].NumeroDemandaSuprida = Plantas[p].Carregamentos[c].NumeroDemandaSuprida + 1;
			ModificouCarregamento = 1;
		}
	}

// Emcontra o indice do veículo
	int 	v;
	if( Plantas[p].VeiculosDaPlanta.AlocaInidiceVeiculo( NumCarretaUtilizada, v) == 0 ){
		cout << endl << endl << " <<<<<<<< probelam com indice veiculo [" << NumCarretaUtilizada << "] => " << v << " ->CorrigeReferenciaCarregamentoDeslocamentoMaisUm  >>>>>>>>>>>>> " << endl << endl ;
		return 0;
	}

// Encontra os tempos relativos da tarefa no caminhão (veículo)
	float 	HorarioInicioVeiculo;
	float 	HorarioFimVeiculo;

	HorarioInicioVeiculo = HorarioInicioPlanta;
	HorarioFimVeiculo = HorarioFinalDescarregamento + Plantas[p].TempoParaConstrucoes[construcao];

// Modifica o número da demanda suprida pelo caminhão (veículo) em questão em mais um
	int 	ModificouDeslocamento;
	ModificouDeslocamento = 0;

	for(  int d = 0; d < (int) Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.size() ; d++){
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
int 	ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm(int NumPlanta, int NumCarreta,int Construcao, int Demanda, float HorarioInicioDescarregamento, float HorarioFinalDescarregamento){

// Emcontra o indice da planta
	int		p;
	if( AlocaInidiceFabrica(NumPlanta,p) == 0){
		cout << endl << endl << " <<<<<<<< problema com indice planta [" << NumPlanta << "] => " << p << " ->ConjuntoPlantas::CorrigeReferenciaCarregamentoDeslocamentoMenosUm  >>>>>>>>>>>>> " << endl << endl ;
	}

// Encontra os tempos relativos da tarefa na planta
	float 	HorarioInicioPlanta;
	float 	HorarioFimPlanta;

	HorarioInicioPlanta = HorarioInicioDescarregamento - Plantas[p].TempoParaConstrucoes[Construcao] -  Plantas[p].TempoPlanta;
	HorarioFimPlanta = HorarioInicioPlanta +  Plantas[p].TempoPlanta;

// Modifica o número da demanda suprida pela planta em questão em mais um
	int ModificouCarregamento;
	ModificouCarregamento = 0;

	for( int c = 0; c < (int) Plantas[p].Carregamentos.size() ; c++){
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
	float HorarioInicioVeiculo;
	float HorarioFimVeiculo;

	HorarioInicioVeiculo = HorarioInicioPlanta;
	HorarioFimVeiculo = HorarioFinalDescarregamento + Plantas[p].TempoParaConstrucoes[Construcao];

// Modifica o número da demanda suprida pelo caminhão (veículo) em questão em mais um
	int ModificouDeslocamento;
	ModificouDeslocamento = 0;

	for( int d = 0; d < (int) Plantas[p].VeiculosDaPlanta.Carretas[v].Deslocamentos.size() ; d++){
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


// verifica se uma das plantas em questão pode atender a demanda em questão caso de atrazar o atendimento das outras demandas da construção que se quer atender
int 	ConjuntoPlantas::VerificaPlantasAnalizadasPodemAtenderSeAtrasar(){
	// percorre todas as plantas
	for ( int p = 0; p < (int) Plantas.size(); p++){
		// verifica se a planta corrente pode atender a demanda em questão caso se atrazar o atendiemnto das demandas posteriores a demanda em questão
		if( Plantas[p].PlantasAnalizadas == -2){
			// retorna 1 caso isso for possivel
			return 1;
		}
	}
	// naõ se consegue atender a demanda mesmo se atrazar as demandas anteriores a demanda em questão
	return 0;

}

// inicializa os horarios que as plantas podem atender certa demanda e a cosntrução pode ser atendida, caso das outras demandas anteriores a esta forem atrazadas, com o valor DBL_MAX
void 	ConjuntoPlantas::InicializaVetorHorarioQuePlantaPodeAtender(){

	// faz para toda planta
	for(  int p = 0; p < (int) Plantas.size(); p++){
		// inicia com o valor maximo de float o horario que a planta pode atender e a construção pode ser atendida
		Plantas[p].HorarioQuePlantaPodeAtender 				= DBL_MAX;
		Plantas[p].HorarioQueConstrucaoPodeReceberDemanda	= DBL_MAX;
	}
}

// retorna o menor horario que a construção pode recerber a demanda que não é atendida no momento
float 	ConjuntoPlantas::RetornaMenorHorarioQueConstrucaoPodeReceberDemanda(){
	float 	HoraAux;
	HoraAux = DBL_MAX;

	// faz para toda planta
	for( int p = 0; p < (int) Plantas.size(); p++){
		// caso o horario que a cosntrução pode receber a demanda corrente for maior que o que a planta pode atender a demanda, entra no if
		if( Plantas[p].HorarioQueConstrucaoPodeReceberDemanda < HoraAux){
			// atualiza o menor horario que a cosntrução pode receber a demanda
			HoraAux = Plantas[p].HorarioQueConstrucaoPodeReceberDemanda;
		}
	}
	// retorna o menor horario que a demanda pode ser atendida
	return HoraAux;
}

// Retorna os dados do carregaemnto de uma certa demanda passada na função
int 	ConjuntoPlantas::RetornaDadosDemandaAtendida(int Construcao, int Demanda, float &HorarioInicio, float &HorarioFinal, int &planta, int &Carreta, float &HorarioInicioCarreta, float &HorarioFinalCarreta){
	// percorre todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		// percorre todos os carregamentotos da planta
		for(  int c = 0; c < (int) Plantas[p].Carregamentos.size(); c++){
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
int 	ConjuntoPlantas::VerificaIntegridadeDeCarregamentosDasPlantas(int imprime,int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	int 	integro;
	// inicia com integro o estado dos carregamentos
	integro = 1;

	if( imprime == 1){
		if( ImprimeSolucao == 1){
			cout << endl << endl << "  Verifica integridade carregamentos " << endl << endl;
		}
		if(  ImprimeArquivo == 1){
			fprintf( Arquivo, "\n\n  Verifica integridade carregamentos \n\n");
		}
	}
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		if( imprime == 1){
			if( ImprimeSolucao == 1){
				cout << " planta [" << Plantas[p].NumeroDaPlanta << "] ";
			}
			if(  ImprimeArquivo == 1){
				fprintf( Arquivo, " planta [%d] ",  Plantas[p].NumeroDaPlanta);
			}
		}
		// verica a integridade dos carregamentos da planta corrente
		if ( Plantas[p].VerificaIntegridadeDeCarregamentos(imprime, ImprimeSolucao, ImprimeArquivo,Arquivo) == 0){
			// caso não for integro, atualiza a variavel de saida
			integro = 0;
		}
	}
	// retorna se as plantas em geral tem integridade em seus carregamentos
	return integro;
}

// verifica a integridade dos deslocamentos realizados pelos veiculos das plantas
int 	ConjuntoPlantas::VerificaIntegridadeDeDeslocaemntosDosVeiculosDasPlantas(int imprime, int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	int 	integro;
	// inicia como integro o estado dos deslocamentos
	integro = 1;

	if( imprime == 1){
		if( ImprimeSolucao == 1){
			cout << endl << "          Verifica integridade Deslocamentos  " << endl << endl;
		}
		if(  ImprimeArquivo == 1){
			fprintf( Arquivo, "\n          Verifica integridade Deslocamentos  \n\n" );
		}
	}
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		if( imprime == 1){
			if( ImprimeSolucao == 1){
				cout << "   Planta [" << Plantas[p].NumeroDaPlanta << "]" << endl ;
			}
			if(  ImprimeArquivo == 1){
				fprintf( Arquivo,"   Planta [%d]\n",  Plantas[p].NumeroDaPlanta);
			}
		}
		// verifica a integridade dos deslocaentos dos veiculos da planta
		if( Plantas[p].VeiculosDaPlanta.VerificaIntegridadeDeDeslocamentosDasCarretas(imprime, ImprimeSolucao, ImprimeArquivo, Arquivo) == 0){
			// caso não for integro, atualiza a variavel de saida
			integro = 0;
		}
	}
	// retorna se existe algum deslocamento que não esta integro ao retorna 0, ou 1 caso contrario
	return integro;
}

void 	ConjuntoPlantas::OrdenaPlantas( int EscolhaPlanta){
	// variavel para parar o programa
	int 	Para;

	// variavel para imprimir a ordenação
	int 	Imprime;
	// 0 se não for imprimir, 1 se for imprimir
	Imprime = 0;

	if( EscolhaPlanta == 2){
		// ordena baseado no menor rank
		sort(Plantas.begin(), Plantas.end(), DecideQualPlantaMenosTarefa);
	}

	if( EscolhaPlanta == 3){
		// ordena baseado no menor rank
		sort(Plantas.begin(), Plantas.end(), DecideQualPlantaMaisTarefa);
	}

	if( EscolhaPlanta == 4){

		random_shuffle (Plantas.begin(), Plantas.end(),  GeradorAleatoricoPlanta);
	}

	if(Imprime == 1){
		cout << "    Planta ordenadas" << endl ;
		for( int p = 0; p < (int) Plantas.size(); p++){
			cout << " planta [" << Plantas[p].NumeroDaPlanta << "]" << endl;

		}
		cin >> Para;
	}



}

void 	ConjuntoPlantas::ArmazenaVetorIntComOrdem( vector < int > &VetorOrdem){
	// faz o vetor de int ter o memso tamanho que o número de plantas
	VetorOrdem.resize( (int) Plantas.size() );
	// percorre todas as planats
	for( int p = 0; p < (int) Plantas.size(); p++){
		// armazena o numero da planta na posição em que a planta está
		VetorOrdem[p] = Plantas[p].NumeroDaPlanta;
	}
}

// Imprime os dados das plantas
void 	ConjuntoPlantas::Imprime(int OrdenaPlantas,int OrdenaCarrtas , int ImprimeSolucao, int ImprimeArquivo, PonteiroArquivo  &Arquivo){
	if( ImprimeSolucao == 1){
		cout << endl << endl << " [[[[[[  Imprime plantas  ]]]]]]" << endl;
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "\n\n  [[[[[[  Imprime plantas  ]]]]]]\n");
	}
	// percorre todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		// imprime a planta corrente
		Plantas[p].Imprime(OrdenaPlantas, OrdenaCarrtas, ImprimeSolucao, ImprimeArquivo, Arquivo);
	}
	if( ImprimeSolucao == 1){
		// escreve o makespan das plantas
		printf ("\n  Makespan Geral das Plantas = %.4f\n", MakespanPLantas);
	}
	if( ImprimeArquivo == 1){
		fprintf( Arquivo, "\n  Makespan Geral das Plantas = %.4f\n", MakespanPLantas);
	}
}


void 	ConjuntoPlantas::ImprimeHorariosPlantasPodemAtender(){

	cout << endl << endl <<  " SituacaoPlantaAtenderCasoAtrasar" << endl;
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		cout << p << " [" << Plantas[p].PlantasAnalizadas << "] ";
	}
	cout << endl;

	cout <<   " HorarioQuePlantaPodeAtender" << endl;
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		cout << p << " [" << Plantas[p].HorarioQuePlantaPodeAtender << "] ";
	}
	cout << endl;

	cout <<   " HorarioQueConstrucaoPodeReceberDemanda" << endl;
	// passa por todas as plantas
	for( int p = 0; p < (int) Plantas.size(); p++){
		cout << p << " [" << Plantas[p].HorarioQueConstrucaoPodeReceberDemanda << "] ";
	}
	cout << endl;
}

// destruidora
ConjuntoPlantas::~ConjuntoPlantas(){
	Plantas.clear();
}

#endif /* PLANTAS_HPP_ */
