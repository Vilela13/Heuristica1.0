/*
 * Heuristica.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef HEURISTICA_HPP_
#define HEURISTICA_HPP_

#include "Bibliotecas.hpp"

class Heuristica{

public:

	ifstream arq;
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	Heuristica();
	int  LeDados(string, int );						// le os dados da instancia
	void ExecutaProcedimentoHeuristico1();			// executa o procedimento heuristico

	void LeNomeInstancia(int , string& );			// le o nome da instancia
	void LeNumeroPlantasEntregasVeiculos(int);		// le o numero de plantas, veiculos e cosntruções
	void LeVelocidade(int);							// le a velocidade

	void LeTempoDeVidaConcreto(int);				// Le o tempo de vida do concreto
	void LeVeiculosPorPlanta(int);					// le o numero de veículos por planta
	void LeNumeroDemandas(int);						// le o numero de demandas por construção

	void LeDistancias(int);							// le as distancias das plantas para as construções
	void LeTempoConstrucao(int);					// le os tempos que cada caminhão leva para atender cada demanda em cada cosntrução
	void LeTempoPlanta(int);						// le o tempo que acda planta leva para carregar um caminhão de concreto

	void LeTempoMaximoEntreDescargas(int);			// le o tempo maximo permitido entre o atendimento de duas demandas seguidas em cada construção
	void LeTempoMaximoMinimoConstrucoes(int);		// le o tempo minimo e maximo que um caminhão pode começar a descarregar em uma cosntrução
	void LeTempoMaximoMinimoPlantas(int);			// le o tempo minimo e máximo que um caminhão pode começar a carregar em uma planta

	void CalculoRankTempoDemanda(int);				// calcula o rank baseado na janela de tempo e no numero de demandas para cada cosntrução
    ~Heuristica();

};

Heuristica::Heuristica(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;

}

// le os dados da instancia
int Heuristica::LeDados(string Nome, int comentarios){

	string Instancia;
	string CaminhoArquivo1;


// Abre arquivo das instâncias
	// coloca a pasta que está o arquivo
	CaminhoArquivo1 = "./InstS/";
	// adiciona o nome do arquivo
	CaminhoArquivo1 += Nome;

	// escreve o arquivo que foi lido
	cout << " Arquivo a abrir : " << CaminhoArquivo1.c_str() << endl;

	// abre o arquivo da instancia
	arq.open(CaminhoArquivo1.c_str());
	// caso abrir o arquivo da instancia, entra no IF
	if (arq.is_open()){
		// le os dados da instancia
		LeNomeInstancia(comentarios, Instancia);
		LeNumeroPlantasEntregasVeiculos(comentarios);
		LeVelocidade(comentarios);
		LeTempoDeVidaConcreto(comentarios);
		LeVeiculosPorPlanta( comentarios);
		LeNumeroDemandas(comentarios);
		LeDistancias(comentarios);
		LeTempoConstrucao(comentarios);
		LeTempoPlanta(comentarios);
		LeTempoMaximoEntreDescargas(comentarios);
		LeTempoMaximoMinimoConstrucoes(comentarios);
		LeTempoMaximoMinimoPlantas(comentarios);
		// calcula o rank
		CalculoRankTempoDemanda(comentarios);

		// fecha o arquivo da instancia aberto
		arq.close();
		// retorna 1 pois o procedimento foi realizado com suceso
		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << CaminhoArquivo1 << endl << endl;
		return 0;
	}
}

// executa o procedimento heuristico
void Heuristica::ExecutaProcedimentoHeuristico1(){
	Procedimento1 Prod1;
	int Solucao;
	Solucao = 0;

	int TipoOrdenacaoVeiculos;
// ordena na ordem do menor número de tarefas para o maior se colocar o valor 1, ordena na ordem do maior número de tarefas para o menor se colocar o valor 2
	TipoOrdenacaoVeiculos = 1;

	ConjuntoSolucoes Solucoes;

	int VerificaViabilidade;
	VerificaViabilidade = 1;

	int Imprime;
	Imprime = 0;

	bool ImprimePlanta;
	bool ImprimeConstrucao;
	bool IntervalosRespeitadosConstrucaoes;

	ImprimePlanta = 1;
	ImprimeConstrucao = 1;
	IntervalosRespeitadosConstrucaoes = 0;

	Prod1.CarregaDados(NP, PlantasInstancia, NE, ConstrucoesInstancia, NV, Velocidade, TempoDeVidaConcreto);

	//Prod1.ConstrucoesInstancia.ImprimeContrucoes();

// Define a ordem de seleção da alocação inicial das atividades

	//sort ( Prod1.ConstrucoesInstancia.Construcoes.begin(), Prod1.ConstrucoesInstancia.Construcoes.end(), DecideQualContrucaoTemMaiorRank );
	sort ( Prod1.ConstrucoesInstancia.Construcoes.begin(), Prod1.ConstrucoesInstancia.Construcoes.end(), DecideQualContrucaoTemMenorInicioDepoisMaiorRank );

	Prod1.ConstrucoesInstancia.ImprimeContrucoes(Prod1.PlantasInstancia, VerificaViabilidade);

	cout << endl << endl << "############################### Procedimento Construcao Solucao por meio de Heuristica Construtiva #####################################" << endl << endl;

	Solucao = Prod1.Executa( TipoOrdenacaoVeiculos, Imprime );

	cout << endl << endl << "########################################################################################################################################" << endl << endl;

	if( Solucao == 1 ){
		cout << endl << endl << "  Solucao viavel!    " << endl << endl;
	}else{
		cout << endl << endl << "  Solucao inviavel!    " << endl << endl;
	}


	Solucoes.InsereSolucao(Prod1.NP, Prod1.PlantasInstancia, Prod1.NE, Prod1.ConstrucoesInstancia, Prod1.NV, Prod1.Velocidade, Prod1.TempoDeVidaConcreto);

	Solucoes.CalculaMakespanSolucoes();


	Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);

/*

	cout << endl << endl << "  coletando dados " << endl << endl;

	Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].ImprimeContrucao();

	cout << endl << endl << "  coletando tarefa " << endl << endl;

	Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].Imprime();

	double HoraInicio;
	double HoraFinal;
	int NumDemanda;
	int NumPlanta;
	int Carreta;

	HoraInicio = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioInicioDescarregamento;
	HoraFinal = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].HorarioFinalDescarregamento;
	NumDemanda = 1;
	NumPlanta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumPlantaFornecedor;
	Carreta = Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].Descarregamentos[1].NumCarretaUtilizada;



	Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].DeletaAtividadeLocomovendoAsOutrasTarefas(HoraInicio, HoraFinal, NumDemanda, NumPlanta, Carreta, Solucoes.Solucoes[0].PlantasInstancia);

	cout << endl << endl << "  Retira tarefa " << endl << endl;

	Solucoes.Imprime(1,1,0);

	cout << endl << endl << "  Readiciona tarefa " << endl << endl;

	Solucoes.Solucoes[0].ConstrucoesInstancia.Construcoes[1].AlocaAtividade(HoraInicio, HoraFinal, Carreta, NumPlanta,  0, 1, Solucoes.Solucoes[0].PlantasInstancia);

	Solucoes.Imprime(1,1,0);
*/


	cout << endl << endl << "############################### Procedimento Viabilidade 1 #####################################" << endl << endl;

	Solucoes.Solucoes[0].ProcessoViabilizacao1( TipoOrdenacaoVeiculos , Imprime);

	cout << endl << endl << "##############################################################################################" << endl << endl;

	Solucoes.CalculaMakespanSolucoes();
	Solucoes.Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);


	Solucoes.Solucoes.resize(Solucoes.Solucoes.size()+1);
	Solucoes.Solucoes[1] = Solucoes.Solucoes[0];


	cout << endl << endl << "############################### Procedimento Viabilidade 2 #####################################" << endl << endl;

	Solucoes.Solucoes[1].ProcessoViabilizacao2( TipoOrdenacaoVeiculos, Imprime);

	cout << endl << endl << "##############################################################################################" << endl << endl;

	Solucoes.CalculaMakespanSolucoes();
	Solucoes.Solucoes[1].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);

	cout << endl << endl << "############################### Busca Local 1 (caminhão) #####################################" << endl << endl;

	Solucoes.Solucoes[1].RealizarBuscaLocalCaminhao(0);

	cout << endl << endl << "##############################################################################################" << endl << endl;

	Solucoes.Solucoes[1].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);

	cout << endl << endl << "############################### Busca Local 2 (construcao) #####################################" << endl << endl;

	Solucoes.Solucoes[1].RealizarBuscaLocalConstrucao(0);

	cout << endl << endl << "##############################################################################################" << endl << endl;

	Solucoes.Solucoes[1].Imprime(ImprimePlanta, ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);



}


// le o nome da instancia
void Heuristica::LeNomeInstancia(int comentarios, string& Instancia){
	// le o nome da instancia
	arq >> Instancia;
	if( comentarios == 1){
		cout << " Nome instancia "<<  Instancia << endl;
	}
}

// le o numero de plantas, veiculos e cosntruções
void Heuristica::LeNumeroPlantasEntregasVeiculos(int comentarios){
	// le numero de plantas
	arq >> NP;
	// inicia os dados que guada os dados das plantas
	PlantasInstancia.IniciaConjuntoPlantas(NP);
	for( int p = 0; p < NP; p++){
		PlantasInstancia.Plantas[p].NumeroDaPlanta = p;
	}
	// le numero de construções
	arq >> NE;
	// inicia as estrutura que guardao os dados das construções
	ConstrucoesInstancia.IniciaConjuntoConstrucoes(NE);
	for( int c = 0; c < NE; c++){
		ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao = c;
	}
	// le numero de veiculos
	arq >> NV;

	if( comentarios == 1){
		cout << " Numero de plantas "<<  NP << endl;
		cout << " Numero de Entregas "<< NE << endl;
		cout << " Numero de Veiculos "<< NV << endl;
	}
}

// le a velocidade
void Heuristica::LeVelocidade(int comentarios){
	// le a velocidade dos caminhões
	arq >> Velocidade;
	if( comentarios == 1){
		cout << " Velocidade "<<  Velocidade << endl;
	}
}


// Le o tempo de vida do concreto
void Heuristica::LeTempoDeVidaConcreto(int comentarios){
	// le o tempo de vida do concreto
	arq >> TempoDeVidaConcreto;
	if( comentarios == 1){
		cout << " Tempo De Vida Concreto "<<  TempoDeVidaConcreto << endl;
	}
}

// le o numero de veículos por planta
void Heuristica::LeVeiculosPorPlanta(int comentarios){
	int aux;
	// percorre todas as planats
	for (int i = 0; i < NP ; i++){
		// le o numero d eveiculos que existe na planta corrente
		arq >> PlantasInstancia.Plantas[i].NumeroVeiculos;
		// inicia a estrutura que armazena os veiculos da planta corrente
		PlantasInstancia.Plantas[i].VeiculosDaPlanta.IniciaConjuntoCarretas( PlantasInstancia.Plantas[i].NumeroVeiculos, PlantasInstancia.Plantas[i].NumeroDaPlanta );
		if( comentarios == 1){
			cout << " Numero de veiculo na planta  " << i + 1 << " = " << PlantasInstancia.Plantas[i].NumeroVeiculos << "  ( ";
		}
		// le os numeros dos caminhões
		for ( int j = 0; j < PlantasInstancia.Plantas[i].NumeroVeiculos; j++){
			// le o numero do caminhão em questão, cada caminhão tem um número próprio
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}

}

// le o numero de demandas por construção
void Heuristica::LeNumeroDemandas(int comentarios){
	int aux;
	// percorre por todas as construções
	for (int i = 0; i < NE ; i++){
		// le o numero de demandas
		arq >> ConstrucoesInstancia.Construcoes[i].NumeroDemandas;
		// inicializa o numero de descarregamentos que cosntrução temq ue receber para satisfazer todas as suas demandas
		ConstrucoesInstancia.Construcoes[i].Descarregamentos.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		// inicia o status de atendiemntos como zero, nenhuma demanda foi atendida ainda
		ConstrucoesInstancia.Construcoes[i].StatusAtendimento = 0;
		// inicializa o vetor atendimento das demandas
		ConstrucoesInstancia.Construcoes[i].SituacaoDemanda.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		// inicializa o vetor remoção das demandas
		ConstrucoesInstancia.Construcoes[i].SituacaoRemocao.resize(ConstrucoesInstancia.Construcoes[i].NumeroDemandas);
		// percorre por todas as demandas da construção corrente
		for( int d = 0; d < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; d++){
			// faz o seu status atendimento ser zero
			ConstrucoesInstancia.Construcoes[i].SituacaoDemanda[d] = 0;
			// faz o seu status remoção ser zero
			ConstrucoesInstancia.Construcoes[i].SituacaoRemocao[d] = 0;
		}
		if( comentarios == 1){
			cout << " Numero de demandas na construção " << i + 1 << " = " << ConstrucoesInstancia.Construcoes[i].NumeroDemandas << "  ( ";
		}
		for ( int j = 0; j < ConstrucoesInstancia.Construcoes[i].NumeroDemandas; j++){
			// le o nuemro de cada demanda em separado, cada construção tem uma numeração propria.
			arq >> aux;
			if( comentarios == 1){
				cout << aux << " ";
			}

		}
		if( comentarios == 1){
			cout << ") " << endl;
		}
	}
}


// le as distancias das plantas para as construções
void Heuristica::LeDistancias(int comentarios){
	// Le a distancia das plantas para as construções
	if( comentarios == 1){
		cout << "     Distancia Planta para Construcoes"<< endl;
	}
	// percorre todas as plantas
	for (int p = 0; p < NP ; p++){
		// inicializa a estrutura de distancia da planta corrente para as cosntruções que existem
		PlantasInstancia.Plantas[p].DistanciaConstrucoes.resize(NE);
		// percorre por todas as construções que existem
		for ( int c = 0; c < NE; c++){
			// le a distancia da planta corresnte para a construção corrente e armazena esse valor
			arq >> PlantasInstancia.Plantas[p].DistanciaConstrucoes[c];
			if( comentarios == 1){
				cout << PlantasInstancia.Plantas[p].DistanciaConstrucoes[c] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}

	}

	// Le a distancia das construções para as plantas
	if( comentarios == 1){
		cout << "     Distancia Construcoes para Plantas"<< endl;
	}
	// percorre todas as cosntruções
	for (int c = 0; c < NE ; c++){
		// inicializa a estrutura de distancia da construção para as plantas
		ConstrucoesInstancia.Construcoes[c].DistanciaPlantas.resize(NP);
		// percorre todas as plantas
		for ( int p = 0; p < NP; p++){
			// le a distancia da construção corrente para a planta corresnte e armazena esse valor
			arq >> ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
			// armazena um ponteiro que leva a planta que a distancia acima que na construção corrente ela se refere
			ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].PlantaComparada = &PlantasInstancia.Plantas[p];
			if( comentarios == 1){
				cout <<  ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}

}

// le os tempos que cada caminhão leva para atender cada demanda em cada cosntrução
void Heuristica::LeTempoConstrucao(int comentarios){
	int aux;

	if( comentarios == 1){
		cout << "     Tempo de cada veiculo em cada cosntrucao "<< endl;
	}
	// percorre todas as plantas
	for (int p = 0; p < NP ; p++){
		// percorre todos os caminhões
		for (int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos ; v++){
			// le o numero do veiculo corrente
			arq >> aux;
			if( comentarios == 1){
				cout << " Veiculo  " << aux << endl;
			}
			// inicia o tamanho da estrutura que guarda os tempos dos veiculos para atender cada demanda com o número de construções que se tem
			PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao.resize( NE);
			// percorre todas as construções
			for ( int c = 0; c < NE; c++){
				// le o numero de demandas da construção
				arq >> aux;
				// verifica se os dados são inconsitentes caso o numero de demandas não seja o mesmo que o passado anteriormente
				if ( aux != ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
					cout << "        ############## Dados Incosistentes ############## " << endl << endl;
				}
				// inicializa a estrurura que guada os tempos dos veiculos para atender cada demanda com o numero das demandas
				PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c].resize( ConstrucoesInstancia.Construcoes[c].NumeroDemandas );
				// percorre todas as demandas
				for ( int d = 0; d < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; d++){
					// le o tempo que o veicuo corrente leva para atender a demanda corrente
					arq >> PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c][d];
					if( comentarios == 1){
						cout << PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[c][d] << "  ";
					}
				}
				if( comentarios == 1){
					cout << endl;
				}
			}
		}

	}
}

// le o tempo que acda planta leva para carregar um caminhão de concreto
void Heuristica::LeTempoPlanta(int comentarios){
	// percorre todas as plantas
	for (int p = 0; p < NP ; p++){
		// le e armazena o tempo que a planta leva para carregar um caminhão de concreto
		arq >> PlantasInstancia.Plantas[p].TempoPlanta;
		if( comentarios == 1){
			cout << " Tempo na Planta " << p +1 << " = " <<  PlantasInstancia.Plantas[p].TempoPlanta << endl;
		}
	}
}


// le o tempo maximo permitido entre o atendimento de duas demandas seguidas em cada construção
void Heuristica::LeTempoMaximoEntreDescargas(int comentarios){
	if( comentarios == 1){
		cout << "     Tempo maximo entre descargas " << endl;
	}
	// percorre por todas as construções
	for ( int c = 0; c < NE; c++){
		// le e armazena o tempo maximo entre dois carregamentos seguidos na mesma construção
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas;
		if( comentarios == 1){
			cout << " Construcao " << c + 1 << " = " <<  ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas << endl;
		}
	}
}

// le o tempo minimo e maximo que um caminhão pode começar a descarregar em uma cosntrução
void Heuristica::LeTempoMaximoMinimoConstrucoes(int comentarios){
	// percorre todas as construções
	for ( int c = 0; c < NE; c++){
		// le e armazena o tempo minimo que se pode receber um caminhão na construção
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento;
	}
	// percorre todas as construções
	for ( int c = 0; c < NE; c++){
		// le e armazena o tempo máximo que se pode receber um caminhão na construção
		arq >> ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento;
	}
	if( comentarios == 1){
		cout << "     Intervalo de Funcionamento Construcoes " << endl;
		for ( int c = 0; c < NE; c++){
			cout << c + 1 << " ( " << ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento << " - " << ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento << " ) " << endl;
		}
	}
}

// le o tempo minimo e máximo que um caminhão pode começar a carregar em uma planta
void Heuristica::LeTempoMaximoMinimoPlantas(int comentarios){
	// percorre todas as plantas
	for ( int p = 0; p < NP; p++){
		// le e armazena o tempo minimo que se pode começar a carregar um caminhão na planta corrente
		arq >> PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
	}
	// percorre todas as plantas
	for ( int p = 0; p < NP; p++){
		// le e armazena o tempo máximo que se pode começar a carregar um caminhão na planta corrente
		arq >> PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento;
	}
	if( comentarios == 1){
		cout << "     Intervalo de Funcionamento Plantas " << endl;
		for ( int p = 0; p < NP; p++){
			cout << p + 1 << " ( " << PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento << " - " << PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento << " ) " << endl;
		}
	}
}


// calcula o rank baseado na janela de tempo e no numero de demandas para cada cosntrução
void Heuristica::CalculoRankTempoDemanda(int comentarios){
	// percorre todas as construções
	for ( int c = 0; c < NE; c++){
		if( comentarios == 1){
			cout << " Construcao " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " com";
		}
		// calcula o rank para a cosntrução corrente
		ConstrucoesInstancia.Construcoes[c].CalculaRankTempoDemandas( comentarios );
	}
}

Heuristica::~Heuristica(){

}

#endif /* HEURISTICA_HPP_ */
