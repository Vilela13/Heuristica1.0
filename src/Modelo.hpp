/*
 * Modelo.hpp
 *
 *  Created on: 16/04/2015
 *      Author: mateus
 */

#ifndef MODELO_HPP_
#define MODELO_HPP_

#include "Bibliotecas.hpp"

//#define TipoLocalizacao vector < vector < float > >			// coordenadas geograficas, X e Y

#define TipoTCVP vector < int >								//Tamanho do Conjunto de Veiculos por Planta
#define TipoCVP vector < vector < int > >					//Conjunto dos Veiculos da Planta

#define TipoTCDE vector < int >								// Tamanho do conjunto de demandas por entregas
#define TipoCDE vector < vector < int > >					// Conjunto de demanas por entrega

#define TipoTempoEntrePontos vector < vector < float > >			// tipo de tempo entre dois conjuntos de pontos

#define TipoDESCvi vector < vector < vector < double > > >
#define TipoCARRp vector < double >
#define TipoTeta vector <  double  >
#define TipoSvii vector < vector < vector < double  > > >

#define TipoTminE vector <  double  >
#define TipoTmaxE vector <  double  >
#define TipoTminP vector <  double  >
#define TipoTmaxP vector <  double  >

#define TipoAlfa IloArray<IloArray<IloBoolVarArray> >
#define TipoBeta IloArray< IloArray< IloArray< IloArray< IloBoolVarArray > > > >

#define TipoTvei IloArray < IloArray < IloFloatVarArray > >
#define TipoTPvei IloArray < IloArray < IloFloatVarArray > >

#define TipoZe IloFloatVarArray




class ClasseModelo{

public:
    ClasseModelo();                                       // construtora da classe
/*
 // Escreve arquivo TXT

    int NumPlantas;						// Número de plantas
    int NumEntregas;					// Número de entregas
    int NumVeiculos;					// Número de veículos

    double Velocidade;
    double TempoDeVidaConcreto;

    TipoTCVP TamanhoConjuntoVeiculoPlanta;
    TipoCVP ConjuntoVeiculoPlanta;

    TipoTCDE TamanhoConjuntoDemandasEntrada;
    TipoCDE ConjuntoDemandasEntrada;

    TipoLocalizacao Localizacao;
    TipoDistancia DistanciaPlantaEntrega;
    TipoDistancia DistanciaEntregaPlanta;

    TipoDESCvi TempoParaDescarregamento;
    TipoCARRp  TempoNaPlanta;

    TipoTeta TempoEntreChegadas;

    TipoTminE TempoInicioEntrada;
    TipoTmaxE TempoFinalEntrada;

    TipoTminP TempoInicioPlanta;
    TipoTmaxP TempoFinalPlanta;

// Funções

    void PreencheEstrutura();
    void CriaTXT();
*/
//	Funções de leitura do arquivo
    void LeNomeInstancia(int, string&);
    void LeNumeroPlantasEntregasVeiculos(int);
    void LeVelocidadeTempoVidaConcreto(int);
    void LeVeiculoPorPlanta(int);
    void LeDemandasPorEntrada(int);
    void LeDistanciaPlantaEntrada(int);
    void LeDistanciaEntregaPlanta(int);
    void LeTempoProcessamentoEntrega(int);
    void LeTempoCarregamentoPlanta(int);
    void LeTempoMaximoEntreEntregasConsecultivas(int);
    void CalculaTempoMinimoDeAtendimentoEntreDuasEntregas(int);
    void LeIntervalosNasEntregas(int);
    void LeIntervalosNasPlantas(int);

    int  LeDados(string, int );

// Le arquivo para resolver o CPLEX, parametros
    ifstream arq;

    int 		NP;			// Número de plantas
	int 		NE;			// Número de entregas
	int 		NV;			// Número de veículos

	double 		Vel;			// Velocidade dos caminhões
	double 		TVC;		// Tempo de vida do concreto

	TipoTCVP 	TCVP;		// Tamanho do conjunto de veículos (caminhões) por planta
	TipoCVP 	CVP;		// Conjunto de veículos (caminhões) por planta

	TipoTCDE 	TCDE;		// Tamanho do conjunto de demandas por entregas
	TipoCDE 	CDE;		// Conjunto de demanas por entrega

	//TipoLocalizacao Loc;		// coordenada dos pontos
	TipoTempoEntrePontos TEMpe;		// Tempo entre uma planta e um entrega
	TipoTempoEntrePontos TEMep;		// Tempo entre uma entrega e uma planta

	TipoDESCvi		DESCvi;		// Tempo para se descarregar o veiculo para a demanda i
	TipoCARRp		CARRp;		// Tempo para se carregar na planta

	TipoTeta	Teta;		// Tempo entre carregamentos máximo

	TipoSvii	Svii;		// Tempo minimo para se atender duas demandas

	TipoTminE	TminE;		// Tempo mínimo na construção
	TipoTmaxE	TmaxE;		// Tempo máximo na construção

	TipoTminP	TminP;		// Tempo mínimo na planta
	TipoTmaxP	TmaxP;		// Tempo máximo na planta



// ********************** Se possui isto aqui para se facilitar o calculo dos Big Ms ******************
	vector< double >	TempoPodeAdiantarEmpresa;
	vector< double >	TempoPodePostergarEmpresa;



// Calcula tempos que podem adiantar ou protergar o funcionamento das construções ou plantas

	void CalculaTempoPodeAdiantarOuPostergarEmpresa(int);

// ***************************************************************************************************


// Variaveis do CPLEX
	IloEnv env;

// Funções que inicializam as variaveis do modleo
	void CriaAlfa(TipoAlfa& , int);
	void CriaBeta(TipoBeta&, int);
	void CriaBetaProducao(TipoBeta&, int);
	void CriaTvei( TipoTvei& ,int);
	void CriaTPvei( TipoTPvei&,int);
	void CriaZe(TipoZe&, int);




// Funções Objetivo
	void FuncaoObjetivo(TipoZe,  IloModel&, int);
//Restrições
	void Restricao_AtendimentoDasDemandas(TipoAlfa, IloModel&, int );
	void Restricao_LowerBoundZe(TipoZe, TipoTvei, TipoAlfa , IloModel&, int );
	void Restricao_VinculoTveiTPvei(TipoAlfa, TipoTPvei, TipoTvei,IloModel&, int);


	void Restricao_PrecedenciaTvei( TipoAlfa ,TipoBeta, TipoTvei, IloModel&, int , int );
	void Restricao_TempoMaximoEntreDescarregamentosSeguidosNaMesmaEntrega( TipoAlfa ,TipoTvei, IloModel&, int);
	void Restricao_TempoMinimoEntreDescarregamentosSeguidosNaMesmaEntrega(TipoAlfa, TipoTvei, IloModel&, int);
	void Restricao_PrecedenciaTPvei( TipoAlfa,TipoBeta,TipoTPvei, IloModel&, int, int);
	void Restricao_TempoDeVidaDoConcreto( TipoAlfa,TipoTvei, TipoTPvei, IloModel&, int);

	void Restricao_LimiteDeTempoNaEntrega( TipoTvei,TipoAlfa, IloModel&, int );
	void Restricao_LimiteDeTempoNaPlanta( TipoTvei, TipoAlfa, IloModel&, int);


	void VerificaOuCriaPastaOut(int);
	void VerificaOuCriaPastaSol(int);

	void EscreveVariaveisAlfaDoModeloAposResolucao(int , int ,ofstream& , IloCplex , TipoAlfa );
	void EscreveVariaveisBetaDoModeloAposResolucao(int, int, ofstream&, IloCplex,  TipoBeta);
	void EscreveVariaveisBetaProducaoDoModeloAposResolucao(int, int, ofstream&, IloCplex, TipoBeta);
	void EscreveVariaveisTveiDoModeloAposResolucao(int, int, ofstream&, IloCplex, TipoTvei);
	void EscreveVariaveisTPveiDoModeloAposResolucao(int, int, ofstream&, IloCplex, TipoTPvei);
	void EscreveVariaveisZeDoModeloAposResolucao(int, int, ofstream&, IloCplex, TipoZe);


	void CalculaFuncaoObjetivo( IloCplex, IloFloatVarArray,  double&);


	void EscreveItinerarioVeiculos(int, int, ofstream&, IloCplex, TipoAlfa, TipoTvei, TipoTPvei);
	void EscreveEntregasNosClientes(int, int, ofstream&, IloCplex, TipoAlfa, TipoTvei);
	void EscreveUtilizacaoVeiculos(int, int, ofstream&, IloCplex, TipoAlfa, TipoTvei);


// Funções que chama o Cplex

    int Cplex(string, int, int&, double&, double&, double&, double&, double&,  vector < string > , vector < double >);

// Escrever em diretorio a saída

    char *c1;
    char *c2;
    string Nome1;
    string Nome2;

 // Pegar o tempo

    double Tempo1;
    double Tempo2;

    ~ClasseModelo();       // Destruidora
};

ClasseModelo::ClasseModelo(){
	NP  = 0;
	NE  = 0;
	NV  = 0;
	Vel = 0;
	TVC = 0;
	c1 = NULL;
	c2 = NULL;
	Tempo1 = -13;
	Tempo2 = -13;
}

/*
void ClasseModelo::PreencheEstrutura(){
// Coloca o numero de plantas, entregas, veiculos e velocidade
	NumPlantas 	= NumeroDePlantasVariaveisFixas;
	NumEntregas = NumeroDeEntregasVariaveisFixas;
	NumVeiculos = NumeroDeVeiculosVariaveisFixas;
	Velocidade 	= VelocidadeVariaveisFixas;
	TempoDeVidaConcreto = TempoDeVidaConcretoVariaveisFixas;
// Preenche o numero veiculos por planta
	TamanhoConjuntoVeiculoPlanta.resize( NumPlantas );
	TamanhoConjuntoVeiculoPlanta[0]	=	3;
	TamanhoConjuntoVeiculoPlanta[1]	=	2;
	ConjuntoVeiculoPlanta.resize( NumPlantas );
	ConjuntoVeiculoPlanta[0].resize( TamanhoConjuntoVeiculoPlanta[0] );
	ConjuntoVeiculoPlanta[1].resize( TamanhoConjuntoVeiculoPlanta[1] );
	int aux1;
	int aux2;
	aux1 = 0;
	aux2 = 0;
	for (int i = 0; i < NumVeiculos ; i ++){
		if( aux1 == TamanhoConjuntoVeiculoPlanta[aux2]){
			aux2 = aux2 + 1 ;
			aux1 = 0;
		}
		ConjuntoVeiculoPlanta[aux2][aux1] = i+1;
		aux1 = aux1 + 1;
	}
// Preenche o numero de demandas por entrada
	TamanhoConjuntoDemandasEntrada.resize(NumEntregas);
	TamanhoConjuntoDemandasEntrada[0] = 2;
	TamanhoConjuntoDemandasEntrada[1] = 1;
	TamanhoConjuntoDemandasEntrada[2] = 3;
	TamanhoConjuntoDemandasEntrada[3] = 2;
	ConjuntoDemandasEntrada.resize(NumEntregas);
	for( int i = 0; i < NumEntregas ; i++){
		ConjuntoDemandasEntrada[i].resize( TamanhoConjuntoDemandasEntrada[i] );
		for( int j = 0; j < TamanhoConjuntoDemandasEntrada[i] ; j++){
			ConjuntoDemandasEntrada[i][j] = j + 1;
		}
	}
// Preenche as localizações das plantas e entradas
	Localizacao.resize( NumPlantas + NumEntregas);
	for( int i = 0 ; i < NumPlantas + NumEntregas ; i++){
		Localizacao[i].resize( 2);
	}
	// Localização plantas (x,Y)
	Localizacao[0][0]= -7;	Localizacao[0][1]= 1; // planta 1
	Localizacao[1][0]= -2;	Localizacao[1][1]= 1; // planta 2
	// Localização entradas (x,Y)
	Localizacao[2][0]= -9;	Localizacao[2][1]= 9; //Entrada 1
	Localizacao[3][0]= -9;	Localizacao[3][1]= -5;//Entrada 2
	Localizacao[4][0]= -4;	Localizacao[4][1]= 6; //Entrada 3
	Localizacao[5][0]= 0;	Localizacao[5][1]= -5;//Entrada 4
// Distâncias das Plantas para as Entradas /
	DistanciaPlantaEntrega.resize( NumPlantas);
	for( int i = 0; i <  NumPlantas; i++){
		DistanciaPlantaEntrega[i].resize( NumEntregas);
	}
	for( int i = 0; i <  NumPlantas; i++){
	    for( int j = NumPlantas; j <  (NumPlantas + NumEntregas); j++){
	    	DistanciaPlantaEntrega[i][j-NumPlantas] = sqrt( pow( Localizacao[i][0] - Localizacao[j][0],2) + pow( Localizacao[i][1] - Localizacao[j][1],2) ) / Velocidade;
	   	}
	}
// Distâncias das Entradas para as Plantas
	DistanciaEntregaPlanta.resize( NumEntregas);
		for( int i = 0; i <  NumEntregas; i++){
			DistanciaEntregaPlanta[i].resize( NumPlantas);
		}
	for( int i = NumPlantas; i <  (NumPlantas + NumEntregas); i++){
		for( int j = 0; j <  NumPlantas; j++){
			DistanciaEntregaPlanta[i-NumPlantas][j] = sqrt( pow( Localizacao[i][0] - Localizacao[j][0],2) + pow( Localizacao[i][1] - Localizacao[j][1],2) ) / Velocidade;
		}
	}
// Tempo para descarregamento de cada veiculo
	TempoParaDescarregamento.resize( NumVeiculos);
	for( int i = 0; i <  NumVeiculos; i++){
		TempoParaDescarregamento[i].resize( NumEntregas);
		for( int j = 0; j <  NumEntregas; j++){
			TempoParaDescarregamento[i][j].resize(TamanhoConjuntoDemandasEntrada[j]);
			for( int z = 0; z <  TamanhoConjuntoDemandasEntrada[j]; z++){
			TempoParaDescarregamento[i][j][z] = 0.2;
			}
		}
	}
// Tempo na planta para carregamento
	TempoNaPlanta.resize( NumPlantas);
	for( int p = 0; p < NumPlantas; p++){
		TempoNaPlanta[p] = 0.083333333; // equivalente a 5 minutos(4 min = 0.066667 ; 3min = 0.05 e 2min = 0.0333333)
	}
// Tempo entre chegadas
	TempoEntreChegadas.resize(NumEntregas);
	for( int j = 0; j <  NumEntregas; j++){
		TempoEntreChegadas[j] = 0.3;
	}
//  Tempo inicio e termino Entrada
	 TempoInicioEntrada.resize(NumEntregas);
	 for( int i = 0; i <  NumEntregas; i++){
		 TempoInicioEntrada[i] = 8;
	 }
	 TempoFinalEntrada.resize(NumEntregas);
	 for( int i = 0; i <  NumEntregas; i++){
		TempoFinalEntrada[i] = 16;
	 }
 //  Tempo inicio e termino Planta
	 TempoInicioPlanta.resize(NumPlantas);
	 for( int i = 0; i <  NumPlantas; i++){
		 TempoInicioPlanta[i] = 8;
	 }
	 TempoFinalPlanta.resize(NumPlantas);
	 for( int i = 0; i <  NumPlantas; i++){
		TempoFinalPlanta[i] = 16;
	 }
}
void ClasseModelo::CriaTXT(){
	ofstream Instancia;
	Instancia.open("./InstS/T-M-V1.txt");
cout << "T-M-V1" << endl;
	Instancia <<"T-M-V1" << endl;
cout << " Numero de Plantas " << endl << '\t';
    cout << NumPlantas << endl;
    Instancia << NumPlantas << endl;
cout << " Numero de Entregas " << endl << '\t';
    cout << NumEntregas << endl;
    Instancia << NumEntregas << endl;
cout << " Numero de Veículos " << endl << '\t';
    cout << NumVeiculos <<  endl;
    Instancia << NumVeiculos  << endl;
cout << " Velocidade " << endl << '\t';
	cout << Velocidade <<  endl;
    Instancia << Velocidade  << endl;
cout << " Tempo de Vida do Concreto " << endl << '\t';
	cout << TempoDeVidaConcreto <<  endl;
	Instancia << TempoDeVidaConcreto  << endl;
cout << "Conjunto de Veiculos por Planta " << endl;
    for( int i = 0; i <  NumPlantas; i++){
    	cout << '\t' << "Planta " << i + 1 <<  " ( " << TamanhoConjuntoVeiculoPlanta[i] << " ) -> ";
    	Instancia << TamanhoConjuntoVeiculoPlanta[i] << " ";
    	for( int j = 0; j <  TamanhoConjuntoVeiculoPlanta[i]; j++){
    		cout << ConjuntoVeiculoPlanta[i][j] << " ";
    		Instancia << ConjuntoVeiculoPlanta[i][j] << " ";
    	}
    	cout << endl;
    	Instancia << endl;
	}
cout << "Conjunto de Demandas por Entrega " << endl;
	for( int i = 0; i <  NumEntregas; i++){
		cout << '\t' << "Entrega " << i + 1 <<  " ( " << TamanhoConjuntoDemandasEntrada[i] << " ) -> ";
		Instancia << TamanhoConjuntoDemandasEntrada[i] << " ";
		for( int j = 0; j <  TamanhoConjuntoDemandasEntrada[i]; j++){
			cout << ConjuntoDemandasEntrada[i][j] << " ";
			Instancia << ConjuntoDemandasEntrada[i][j] << " ";
		}
		cout << endl;
		Instancia << endl;
	}
cout << "Distancia Planta - Entrega " << endl;
	cout << ' ';
	for( int j = 0; j <  NumEntregas; j++){
		cout << '\t' << j+1 ;
	}
	cout << endl;
	for( int i = 0; i <  NumPlantas; i++){
		cout << i+1 << '\t';
		for( int j = 0; j <  NumEntregas; j++){
			cout << DistanciaPlantaEntrega[i][j] << '\t';
			Instancia << DistanciaPlantaEntrega[i][j] << " ";
		}
		cout << endl;
		Instancia << endl;
	}
cout << "Distancia Entrega - Planta " << endl;
	cout << ' ';
	for( int j = 0; j <  NumPlantas; j++){
		cout << '\t' << j+1 ;
	}
	cout << endl;
	for( int i = 0; i <  NumEntregas; i++){
		cout << i+1 << '\t';
		for( int j = 0; j <  NumPlantas; j++){
			cout << DistanciaEntregaPlanta[i][j] << '\t';
			Instancia << DistanciaEntregaPlanta[i][j] << " ";
		}
		cout << endl;
		Instancia << endl;
	}
cout << "Tempo Para Descarregamento " << endl;
	for( int i = 0; i <  NumVeiculos; i++){
	cout << '\t' << '\t' << "Veiculo " << i+1 << endl;
	Instancia << i+1 << endl;
		for( int j = 0; j <  NumEntregas; j++){
			cout << "Entrega " << j+1 << " (" << TamanhoConjuntoDemandasEntrada[j] << ") " <<  '\t';
			Instancia << TamanhoConjuntoDemandasEntrada[j] << '\t';
			for( int z = 0; z <  TamanhoConjuntoDemandasEntrada[j]; z++){
			cout << TempoParaDescarregamento[i][j][z] << '\t';
			Instancia << TempoParaDescarregamento[i][j][z] << '\t';
			}
			cout << endl;
			Instancia << endl;
		}
	}
cout << "Tempo Para Carregamento " << endl;
	for( int p = 0; p < NumPlantas; p++){
		Instancia <<  TempoNaPlanta[p] << '\t';
		cout  << TempoNaPlanta[p] << '\t';
	}
	cout << endl;
	Instancia << endl;
cout << " Tempo entre chagadas " << endl;
	for( int j = 0; j <  NumEntregas; j++){
		cout << TempoEntreChegadas[j] << '\t';
		Instancia << TempoEntreChegadas[j] << '\t';
	}
	cout << endl;
	Instancia << endl;
cout << " Tempo Inicio Entrada " << endl;
	 for( int i = 0; i <  NumEntregas; i++){
		cout << i << ' ' << TempoInicioEntrada[i]<< endl;
		Instancia << TempoInicioEntrada[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;
cout << " Tempo Final Entrada " << endl;
	 for( int i = 0; i <  NumEntregas; i++){
		cout << i << ' ' << TempoFinalEntrada[i]<< endl;
		Instancia << TempoFinalEntrada[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;
cout << " Tempo Inicio Planta " << endl;
	 for( int i = 0; i <  NumPlantas; i++){
		 cout << i << ' ' << TempoInicioPlanta[i] << endl;
		 Instancia << TempoInicioPlanta[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;
cout << " Tempo Final Planta " << endl;
	 for( int i = 0; i <  NumPlantas; i++){
		 cout << i << ' ' << TempoFinalPlanta[i] << endl;
		 Instancia << TempoFinalPlanta[i] << ' ';
	 }
	 cout << endl;
	 Instancia << endl;
	 Instancia.close();
}
*/

// Le dadso da Intância
void ClasseModelo::LeNomeInstancia(int comentarios, string& Instancia){
	arq >> Instancia;
	if( comentarios == 1){
		cout << " Nome instancia "<<  Instancia << endl;
	}
}

void ClasseModelo::LeNumeroPlantasEntregasVeiculos(int comentarios){
	arq >> NP;
	arq >> NE;
	arq >> NV;
	if( comentarios == 1){
		cout << " Numero de plantas "<<  NP << endl;
		cout << " Numero de Entregas "<< NE << endl;
		cout << " Numero de Veiculos "<< NV << endl;
	}
}

void ClasseModelo::LeVelocidadeTempoVidaConcreto(int comentarios){
	arq >> Vel;
	arq >> TVC;
	if( comentarios == 1){
		cout << " V (velocidade)  "<< Vel << endl;
		cout << " TVC (tempo de vida do concreto) "<< TVC << endl;
	}
}

void ClasseModelo::LeVeiculoPorPlanta(int comentarios){
	if( comentarios == 1){
		cout << "Conjunto de Veiculos por Planta " << endl;
	}
	TCVP.resize(NP);
	CVP.resize(NP);
	for( int i = 0; i < NP ; i++){
		arq >> TCVP[i];
		if( comentarios == 1){
			cout << '\t' << "Planta " << i + 1 <<  " ( " << TCVP[i] << " ) -> ";
		}
		CVP[i].resize(TCVP[i]);
		for( int j = 0; j < TCVP[i] ; j++){
			arq >>  CVP[i][j];
			if( comentarios == 1){
				cout << CVP[i][j] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}
	if( comentarios == 1){
		cout << endl;
	}
}

void ClasseModelo::LeDemandasPorEntrada(int comentarios){
	if( comentarios == 1){
		cout << "Conjunto de Demandas por Entrega " << endl;
	}
	TCDE.resize(NE);
	CDE.resize(NE);
	for( int i = 0; i < NE ; i++){
		arq >> TCDE[i];
		if( comentarios == 1){
			cout << '\t' << "Entrega " << i + 1 <<  " ( " << TCDE[i] << " ) -> ";
		}
		CDE[i].resize(TCDE[i]);
		for( int j = 0; j < TCDE[i] ; j++){
			arq >>  CDE[i][j];
			if( comentarios == 1){
				cout << CDE[i][j] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}
	if( comentarios == 1){
		cout << endl;
	}
}

void ClasseModelo::LeDistanciaPlantaEntrada(int comentarios){
	TEMpe.resize(NP);
	for(int p = 0; p < NP; p++){
		TEMpe[p].resize(NE);
	}

	if( comentarios == 1){
		cout << "Distancia Planta - Entrega " << endl;
		cout << ' ';
		for( int e = 0; e <  NE; e++){
			cout << '\t' << e+1 ;
		}
		cout << endl;
	}
	for( int p = 0; p <  NP; p++){
		if( comentarios == 1){
			cout << p+1 << '\t';
		}
		for( int e = 0; e <  NE; e++){
			arq >> TEMpe[p][e];
			if( comentarios == 1){
				cout << TEMpe[p][e] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}
}

void ClasseModelo::LeDistanciaEntregaPlanta(int comentarios){
	TEMep.resize(NE);
	for(int e = 0; e < NE; e++){
		TEMep[e].resize(NP);
	}

	if( comentarios == 1){
		cout << "Distancia Entrega - Planta " << endl;
		cout << ' ';
		for( int p = 0; p <  NP; p++){
			cout << '\t' << p+1 ;
		}
		cout << endl;
	}
	for( int e = 0; e <  NE; e++){
		if( comentarios == 1){
			cout << e+1 << '\t';
		}
		for( int p = 0; p <  NP; p++){
			arq >> TEMep[e][p];
			if( comentarios == 1){
				cout << TEMep[e][p] << " ";
			}
		}
		if( comentarios == 1){
			cout << endl;
		}
	}
}

void ClasseModelo::LeTempoProcessamentoEntrega(int comentarios){
	int Aux1;

	DESCvi.resize( NV);
	for( int i = 0; i <  NV; i++){
		DESCvi[i].resize( NE);
		for( int j = 0; j <  NE; j++){
			DESCvi[i][j].resize(TCDE[j]);
		}
	}

	if( comentarios == 1){
		cout << "Tempo Para Descarregamento " << endl;
	}

	for( int i = 0; i <  NV; i++){
		arq >> Aux1;
		if( comentarios == 1){
			cout << '\t' << '\t' << "Veiculo " << Aux1 << endl;
		}
		for( int j = 0; j <  NE; j++){
			arq >> Aux1;
			if( comentarios == 1){
				cout << "Entrega " << j+1 << " (" << Aux1 << ") " <<  '\t';
			}
			for( int z = 0; z <  Aux1; z++){
				arq >> DESCvi[i][j][z];
				if( comentarios == 1){
					cout << DESCvi[i][j][z] << '\t';
				}
			}
			if( comentarios == 1){
				cout << endl;
			}
		}
	}
}

void ClasseModelo::LeTempoCarregamentoPlanta(int comentarios){
	CARRp.resize(NP );
	if( comentarios == 1){
		cout << "Tempo Para Carregamento nas Plantas " << endl;
	}
	for( int p = 0; p < NP; p++){
		arq >> CARRp[p];
		if( comentarios == 1){
			cout << CARRp[p] << '\t';
		}
	}
	if( comentarios == 1){
		cout << endl;
	}
}

void ClasseModelo::LeTempoMaximoEntreEntregasConsecultivas(int comentarios){
	Teta.resize(NE);
	if( comentarios == 1){
		cout << " Tempo entre chagadas " << endl;
	}
	for( int e = 0; e <  NE; e++){
		arq >>Teta[e];
		if( comentarios == 1){
			cout <<Teta[e] << '\t';
		}
	}
	if( comentarios == 1){
		cout << endl;
	}
}

void ClasseModelo::CalculaTempoMinimoDeAtendimentoEntreDuasEntregas(int comentarios){
	int Aux2;

	Svii.resize(NV);
	for( int v = 0; v <  NV; v++){
		 Svii[v].resize(NE);
		 for( int e1 = 0; e1 <  NE; e1++){
			 Svii[v][e1].resize(NE);;
		 }
	}
	if( comentarios == 1){
		cout << " Tempo para ir de uma entrada a outra " << endl;
	}
	Aux2 = 0;
	for( int p = 0; p <  NP; p++){
		for( int v = 0; v < TCVP[p]; v++ ){
			if( comentarios == 1){
				cout << '\t' << '\t' << "Veiculo " << Aux2 + 1 << endl ;
			}
			for( int e1 = 0; e1 <  NE; e1++){
				for( int e2 = 0; e2 <  NE; e2++){
					if( comentarios == 1){
						cout << " Entrega [" << e1 + 1 << "] para a Entrega [" << e2+ 1 << "] = ";
					}
					for( int j = 0; j < TCDE[e2]; j++){
						Svii[Aux2][e1][e2] = TEMep[e1][p] + CARRp[p] + TEMpe[p][e2];
						if( comentarios == 1){
							cout << Svii[Aux2][e1][e2] << '\t';
						}
					}
					if( comentarios == 1){
						cout << endl;
					}
				}
				if( comentarios == 1){
					cout << endl;
				}
			 }
			Aux2 = Aux2 + 1;
		}
	}
}

// le  tempo inicio e final entrada e planta
void ClasseModelo::LeIntervalosNasEntregas(int comentarios){
	TminE.resize(NE);
	if( comentarios == 1){
		cout << " Tempo Inicio Entrada " << endl;
	}
	 for( int i = 0; i <  NE; i++){
		 arq >> TminE[i];
		 if( comentarios == 1){
			 cout << i + 1 << ' ' << TminE[i]<< endl;
		 }
	 }
	 if( comentarios == 1){
		 cout << endl;
	 }
	TmaxE.resize(NE);
	if( comentarios == 1){
		cout << " Tempo Final Entrada " << endl;
	}
	for( int i = 0; i <  NE; i++){
		arq >> TmaxE[i];
		if( comentarios == 1){
			cout << i + 1 << ' ' << TmaxE[i]<< endl;
		}
	 }
	if( comentarios == 1){
		cout << endl;
	}
}
void ClasseModelo::LeIntervalosNasPlantas(int comentarios){
	 TminP.resize(NP);
	 if( comentarios == 1){
		 cout << " Tempo Inicio Planta " << endl;
	 }
	 for( int i = 0; i <  NP; i++){
		 arq >> TminP[i];
		 if( comentarios == 1){
			 cout << i + 1 << ' ' << TminP[i] << endl;
		 }
	 }
	 if( comentarios == 1){
		 cout << endl;
	 }
	TmaxP.resize(NP);
	if( comentarios == 1){
		cout << " Tempo Final Planta " << endl;
	}
	for( int i = 0; i <  NP; i++){
		arq >> TmaxP[i];
		if( comentarios == 1){
			cout << i + 1 << ' ' << TmaxP[i] << endl;
		}
	}
	if( comentarios == 1){
		cout << endl;
	}
}

// Le dados
int ClasseModelo::LeDados(string Nome, int comentarios){

	string Instancia;
	string CaminhoArquivo1;

// Abre arquivo das instâncias

	CaminhoArquivo1 = "./InstS/";
	CaminhoArquivo1 += Nome;



	arq.open(CaminhoArquivo1.c_str());
	if (arq.is_open()){
		LeNomeInstancia(comentarios, Instancia);
		LeNumeroPlantasEntregasVeiculos(comentarios);
		LeVelocidadeTempoVidaConcreto(comentarios);
		LeVeiculoPorPlanta(comentarios);
		LeDemandasPorEntrada(comentarios);
		LeDistanciaPlantaEntrada(comentarios);
		LeDistanciaEntregaPlanta(comentarios);
		LeTempoProcessamentoEntrega(comentarios);
		LeTempoCarregamentoPlanta(comentarios);
		LeTempoMaximoEntreEntregasConsecultivas(comentarios);
		CalculaTempoMinimoDeAtendimentoEntreDuasEntregas(comentarios);
		LeIntervalosNasEntregas(comentarios);
		LeIntervalosNasPlantas(comentarios);
		arq.close();
		Instancia.clear();
		CaminhoArquivo1.clear();
		return 1;
	}else{
		cout << "         Fudeu Muito! Não abriu o arquivo " << Nome << endl << endl;
		CaminhoArquivo1.clear();
		return 0;
	}
}

// Calcula tempos que podem adiantar ou protergar o funcionamento das construções ou plantas, nesse caso coloca zero nos tempos de adiantamento e atraso nas empresas, no outro caso coloca tempo, na outra construtora
void ClasseModelo::CalculaTempoPodeAdiantarOuPostergarEmpresa(int Escreve){
	TempoPodeAdiantarEmpresa.resize(NE);
	TempoPodePostergarEmpresa.resize(NE);
	for(int e = 0; e < NE; e++ ){
		TempoPodeAdiantarEmpresa[e] = 0;
		TempoPodePostergarEmpresa[e] = 0;
		if(Escreve == 1){
			cout << " Construcao[" << e << "] tempo que pode adiantar => " << TempoPodeAdiantarEmpresa[e] ;
			cout << " tempo que pode postergar => " << TempoPodePostergarEmpresa[e] << endl;
		}
	}
}


// Cria Variáveis
void ClasseModelo::CriaAlfa(TipoAlfa& Alfa, int Escreve){
	char varName[24];
	for (int v = 0; v < NV; v++) {
		Alfa[v] = IloArray< IloBoolVarArray>(env, NE);
		for (int e = 0; e < NE; e++) {
			Alfa[v][e] =  IloBoolVarArray(env, TCDE[e]);
			for (int i = 0; i < TCDE[e]; i++) {
				sprintf(varName, "Alfa_%d_%d_%d", v, e, i);
				Alfa[v][e][i] = IloBoolVar(env,varName);
				if ( Escreve == 1){
					cout << " Alfa["<< v << "][" << e << "][" << i << "] "<< endl;
				}
			}
			if ( Escreve == 1){
				cout << endl;
			}
		}
	}
}

void ClasseModelo::CriaBeta(TipoBeta& Beta, int Escreve ){
	char varName[24];
	for (int v = 0; v < NV; v++) {
		Beta[v] = IloArray< IloArray< IloArray< IloBoolVarArray> > >(env, NE);
		for (int e1 = 0; e1 < NE; e1++) {
			Beta[v][e1] =  IloArray< IloArray< IloBoolVarArray > > (env, TCDE[e1]);
			for (int i = 0; i < TCDE[e1]; i++) {
				Beta[v][e1][i] =   IloArray< IloBoolVarArray >  (env, NE);
				for (int e2 = 0; e2 < NE; e2++) {
					Beta[v][e1][i][e2] =  IloBoolVarArray (env, TCDE[e2]);
					for (int j = 0; j < TCDE[e2]; j++) {
						if( e1 == e2 and i == j){

						}else{
							sprintf(varName, "Beta_%d_%d_%d_%d_%d", v, e1, i, e2,  j);
							Beta[v][e1][i][e2][j] = IloBoolVar(env,varName);
							if ( Escreve == 1){
								cout << " Beta["<< v << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "] "<< endl;
							}
						}
					}
					if ( Escreve == 1){
						cout << endl;
					}
				}
			}
		}
		if ( Escreve == 1){
			cout << endl;
			cout << endl;
		}
	}
}

void ClasseModelo::CriaBetaProducao(TipoBeta& BetaProducao, int Escreve ){
	char varName[24];
	for (int p = 0; p < NP; p++) {
		BetaProducao[p] = IloArray< IloArray< IloArray< IloBoolVarArray> > >(env, NE);
		for (int e1 = 0; e1 < NE; e1++) {
			BetaProducao[p][e1] =  IloArray< IloArray< IloBoolVarArray > > (env, TCDE[e1]);
			for (int i = 0; i < TCDE[e1]; i++) {
				BetaProducao[p][e1][i] =   IloArray< IloBoolVarArray >  (env, NE);
				for (int e2 = 0; e2 < NE; e2++) {
					BetaProducao[p][e1][i][e2] =  IloBoolVarArray (env, TCDE[e2]);
					for (int j = 0; j < TCDE[e2]; j++) {
						if( e1 == e2 and i == j){

						}else{
							sprintf(varName, "BetaProd_%d_%d_%d_%d_%d", p, e1, i, e2,  j);
							BetaProducao[p][e1][i][e2][j] = IloBoolVar(env,varName);
							if ( Escreve == 1){
								cout << " BetaProducao["<< p << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "] "<< endl;
							}
						}
					}
					if ( Escreve == 1){
						cout << endl;
					}
				}
			}
		}
		if ( Escreve == 1){
			cout << endl;
			cout << endl;
		}
	}
}

void ClasseModelo::CriaTvei( TipoTvei& Tvei,int Escreve){
	char varName[24];
	for (int v = 0; v < NV; v++) {
		Tvei[v] = IloArray < IloFloatVarArray >(env,NE);
		for (int e = 0; e < NE; e++) {
			Tvei[v][e] = IloFloatVarArray(env,TCDE[e]);
			for (int i = 0; i < TCDE[e]; i++) {
				sprintf(varName, "Tvei_%d_%d_%d", v, e, i);
				Tvei[v][e][i] = IloFloatVar(env,varName);
				if ( Escreve == 1){
					cout << " Tvei["<< v << "]["<< e << "]["<< i << "] "<< endl;
				}
			}
			if ( Escreve == 1){
				cout << endl;
			}
		}
	}
	if ( Escreve == 1){
		cout << endl;
	}
}

void ClasseModelo::CriaTPvei( TipoTPvei& TPvei,int Escreve){
	char varName[24];
	for (int v = 0; v < NV; v++) {
		TPvei[v] = IloArray < IloFloatVarArray > (env,NV);
		for (int e = 0; e < NE; e++) {
			TPvei[v][e] = IloFloatVarArray(env,TCDE[e]);
			for (int i = 0; i < TCDE[e]; i++) {
				sprintf(varName, "TPvei_%d_%d_%d", v, e, i);
				TPvei[v][e][i] = IloFloatVar(env,varName);
				if ( Escreve == 1){
					cout << " TPvei["<< v << "]["<< e << "]["<< i << "] "<< endl;
					cout << endl;
				}
			}
		}
	}
	if ( Escreve == 1){
		cout << endl;
	}
}

void ClasseModelo::CriaZe(TipoZe& Ze , int Escreve){
	char varName[24];
	for (int e = 0; e < NE; e++) {
		sprintf(varName, "Ze_%d", e);
		Ze[e] = IloFloatVar(env,varName);
		if ( Escreve == 1){
			cout << " Z_Entrada[" << e << "] "<< endl;
		}
	}
	if ( Escreve == 1){
		cout << endl;
	}
}



// Função Objetivo
void ClasseModelo::FuncaoObjetivo(TipoZe Ze,   IloModel& model, int Imprime){
	int Ativo;
	Ativo = 0;
	if ( Imprime == 1){
		cout << " MIN  ";
	}
	IloExpr funcao_objetivo(env);
	for (int e = 0; e < NE; e++) {
		funcao_objetivo += Ze[e];
		if ( Imprime == 1){
			if( Ativo == 1){
				cout << "+";
			}
			cout << " Ze[" << e << "] ";
			Ativo = 1;
		}
	}
	if ( Imprime == 1){
		cout << endl;
	}
	IloObjective obj = IloMinimize(env, funcao_objetivo);
	model.add(obj);
	funcao_objetivo.end();
}

// Restrições
	// restrição 1
void ClasseModelo::Restricao_AtendimentoDasDemandas(TipoAlfa Alfa, IloModel& model, int Escreve){
	IloRangeArray Restricao1Demandas;
	char varName[20];

	int NumAux;
	NumAux = 0;

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			NumAux++;
		}
	}

	Restricao1Demandas = IloRangeArray(env, NumAux);

	NumAux = 0;

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			IloExpr expr(env);
			for (int v = 0; v < NV; v++) {
				// monta o lado esquerdo
				expr += Alfa[v][e][i];
				if ( Escreve == 1){
					if( v < ( NV - 1 ) ) {
						cout << " ALFAvei[" << v << "][" << e << "][" << i << "] +";
					}else{
						cout << " ALFAvei[" << v << "][" << e << "][" << i << "] = 1" << endl;
					}
				}
			}
			//monta o lado direito
			Restricao1Demandas[NumAux] = expr == 1 ;

			sprintf(varName,"Rest1_SuprirD_e%di%d", e, i);
			Restricao1Demandas[NumAux].setName(varName);


			model.add(Restricao1Demandas[NumAux]);
			expr.end();
			NumAux++;
		}
	}
}
	// restrição 2
void ClasseModelo::Restricao_LowerBoundZe(TipoZe Ze, TipoTvei Tvei, TipoAlfa Alfa, IloModel& model, int Escreve){
	float BigMauternativo;
	IloRangeArray Restricao2;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			for (int v = 0; v < NV; v++) {
				NumAux++;
			}
		}
	}

	Restricao2 = IloRangeArray(env, NumAux);

	NumAux = 0;

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			for (int v = 0; v < NV; v++) {
				// declara expressão
				IloExpr expr(env);

				BigMauternativo = TmaxE[e] + TempoPodePostergarEmpresa[e] + DESCvi[v][e][i];   // M1

				// monta lado esquerdo
				expr +=  Tvei[v][e][i] + DESCvi[v][e][i] - BigMauternativo  * ( 1 - Alfa[v][e][i] ) - Ze[e] ;

				// coloca o lado direito da expressão, no meu caso é o 0, pois coloquei as outras coisas no lado esquerdo
				Restricao2[NumAux] = expr <=  0;

				if( Escreve == 1){
					cout << " Ze[" << e << "] >= Tvei[" << v << "][" << e << "][" << i << "] + DESCvei[" << v << "][" << e << "][" << i << "] - BigM1  * ( 1 - Alfa[" << v << "][" << e << "][" << i << "])" << endl;
				}



				sprintf(varName,"Rest2_ZeLimInf_v%de%di%d", v, e, i);
				Restricao2[NumAux].setName(varName);

				model.add(Restricao2[NumAux]);

				expr.end();
				NumAux++;
			}
		}
	}
}
	// restrição 3 e 4
void ClasseModelo::Restricao_VinculoTveiTPvei(TipoAlfa Alfa, TipoTPvei TPvei, TipoTvei Tvei,IloModel& model, int EscreveRestricao ){
	int vAux;
	float BigMauternativo;
	IloRangeArray Restricao3;
	IloRangeArray Restricao4;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			vAux = 0;
			for (int p = 0; p < NP; p++) {
				for (int v = 0; v < TCVP[p]; v++) {
					NumAux++;
				}
			}
		}
	}

	Restricao3 = IloRangeArray(env, NumAux);
	Restricao4 = IloRangeArray(env, NumAux);
	NumAux = 0;

	for (int e = 0; e < NE; e++) {
		for (int i = 0; i < TCDE[e]; i++) {
			vAux = 0;
			for (int p = 0; p < NP; p++) {
				for (int v = 0; v < TCVP[p]; v++) {
					// declara expressão
					IloExpr expr1(env);
					IloExpr expr2(env);

					if ( EscreveRestricao == 1){
						cout << " - BigM2 * ( 1 - ALFAvei[" << vAux << "][" << e << "][" << i << "] )";
						cout << " + TDESCvi[" << vAux << "][" << e << "][" << i << "] + CARRp[" << p << "]";
						cout << "+ TEMpe[" << p << "][" << e << "] <= ";
						cout << " Tvei[" << vAux << "][" << e << "][" << i << "] " << endl;
					}
					BigMauternativo = TmaxP[p]  + CARRp[p] + TEMpe[p][e]; // M2

					expr1 += - BigMauternativo  * ( 1 - Alfa[vAux][e][i] ) + TPvei[vAux][e][i] + CARRp[p] + TEMpe[p][e] - Tvei[vAux][e][i];

					Restricao3[NumAux] = expr1 <= 0;

					sprintf(varName, "Rest3_VincTsSup_p%dv%de%di%d", p, vAux, e, i);
					Restricao3[NumAux].setName(varName);

					model.add(Restricao3[NumAux]);

					//model.add( - BigMauternativo  * ( 1 - Alfa[vAux][e][i] ) + TPvei[vAux][e][i] + CARRp[p] + TEMpe[p][e] <= Tvei[vAux][e][i] );

					if ( EscreveRestricao == 1){
						cout << " BigM2 * ( 1 - ALFAvei[" << vAux << "][" << e << "][" << i << "] )";
						cout << " + TDESCvi[" << vAux << "][" << e << "][" << i << "] + CARRp[" << p << "]";
						cout << "+ TEMpe[" << p << "][" << e << "] >= ";
						cout << " Tvei[" << vAux << "][" << e << "][" << i << "] " << endl;
					}
					BigMauternativo = TmaxE[e] + TempoPodePostergarEmpresa[e];	// M3



					expr2 += BigMauternativo  * ( 1 - Alfa[vAux][e][i] ) + TPvei[vAux][e][i] + CARRp[p] + TEMpe[p][e] - Tvei[vAux][e][i];

					Restricao4[NumAux] = expr2 >= 0;

					sprintf(varName,"Rest4_VincTsInf_p%dv%de%di%d", p, vAux, e, i);
					Restricao4[NumAux].setName(varName);

					model.add(Restricao4[NumAux]);

					//model.add( BigMauternativo  * ( 1 - Alfa[vAux][e][i] ) + TPvei[vAux][e][i] + CARRp[p] + TEMpe[p][e] >= Tvei[vAux][e][i] );

					vAux = vAux + 1;

					expr1.end();
					expr2.end();
					NumAux++;
				}
			}
		}
	}
}



	// restrição 6 e 7
void ClasseModelo::Restricao_PrecedenciaTvei( TipoAlfa Alfa,TipoBeta Beta,TipoTvei Tvei, IloModel& model, int EscrveRestricao1, int EscreveRestricao2){
	float BigMauternativo;
	IloRangeArray Restricao7;
	IloRangeArray Restricao8;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int v = 0; v < NV; v++) {
		for (int e1 = 0; e1 < NE; e1++) {
			for (int i = 0; i < TCDE[e1]; i++) {
				for (int e2 = 0; e2 < NE; e2++) {
					for (int j = 0; j < TCDE[e2]; j++) {
						if ( i == j and e1 == e2){

						}else{
							NumAux++;
						}
					}
				}
			}
		}
	}

	Restricao7 = IloRangeArray(env, NumAux);
	Restricao8 = IloRangeArray(env, NumAux);
	NumAux = 0;


	for (int v = 0; v < NV; v++) {
		for (int e1 = 0; e1 < NE; e1++) {
			for (int i = 0; i < TCDE[e1]; i++) {
				for (int e2 = 0; e2 < NE; e2++) {
					for (int j = 0; j < TCDE[e2]; j++) {
						if ( i == j and e1 == e2){

						}else{

							// declara expressão
							IloExpr expr1(env);
							IloExpr expr2(env);

							if ( EscrveRestricao1 == 1){
								cout << " BigM3 * ( 1 - ALFAvei[" << v << "][" << e1 << "][" << i << "]) +";
								cout << " BigM3 * ( 1 - ALFAve'i'[" << v << "][" << e2 << "][" << j << "]) +";
								cout << " BigM3 * ( 1 - BETAveie'i'[" << v << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "])";
								cout << " + Tve'i'[" << v << "][" << e2 << "][" << j << "] >= Tvei[" << v << "][" << e1 << "][" << i << "]";
								cout << " + Pvei[" << v << "][" << e1 << "][" << i << "]";
								cout << " + Svee'[" << v << "][" << e1 << "][" << e2 << "]" << endl;
							}
							BigMauternativo = TmaxE[e1] + TempoPodePostergarEmpresa[e1] + DESCvi[v][e1][i] + Svii[v][e1][e2];		// M5

							expr1 += BigMauternativo * ( 1 - Alfa[v][e1][i] ) + BigMauternativo * ( 1 - Alfa[v][e2][j] ) + BigMauternativo * ( 1 - Beta[v][e1][i][e2][j] ) + Tvei[v][e2][j] - Tvei[v][e1][i] - DESCvi[v][e1][i] - Svii[v][e1][e2] ;
							Restricao7[NumAux] = expr1 >= 0;

							sprintf(varName,"Rest6_PrecTvi_v%de%di%de'%di'%d", v, e1, i, e2, j);
							Restricao7[NumAux].setName(varName);

							model.add(Restricao7[NumAux]);
							expr1.end();


							//model.add( BigMauternativo * ( 1 - Alfa[v][e1][i] ) + BigMauternativo * ( 1 - Alfa[v][e2][j] ) + BigMauternativo * ( 1 - Beta[v][e1][i][e2][j] ) + Tvei[v][e2][j] >= Tvei[v][e1][i] + DESCvi[v][e1][i] + Svii[v][e1][e2] );
							if ( EscreveRestricao2 == 1){
								cout << " BigM4 * ( 1 - ALFAvei[" << v << "][" << e1 << "][" << i << "]) +";
								cout << " BigM4 * ( 1 - ALFAve'i'[" << v << "][" << e2 << "][" << j << "]) +";
								cout << " BigM4 * BETAveie'i'[" << v << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "]";
								cout << " + Tvei[" << v << "][" << e1 << "][" << i << "] >= Tvei'[" << v << "][" << e2 << "][" << j << "]";
								cout << " + DESCvi'[" << v << "][" << e2 << "][" << j << "]";
								cout << " + Svi'i[" << v << "][" << e2 << "][" << e1 << "]" << endl << endl;
							}
							BigMauternativo = TmaxE[e2] + TempoPodePostergarEmpresa[e2] + DESCvi[v][e2][j] + Svii[v][e2][e1];		// M6

							expr2 += BigMauternativo * ( 1 - Alfa[v][e1][i] ) + BigMauternativo * ( 1 - Alfa[v][e2][j] ) + BigMauternativo * Beta[v][e1][i][e2][j] + Tvei[v][e1][i] - Tvei[v][e2][j] - DESCvi[v][e2][j] - Svii[v][e2][e1];
							Restricao8[NumAux] = expr2 >= 0;

							sprintf(varName,"Rest7_PrecTvi_v%de%di%de'%di'%d", v, e1, i, e2, j);
							Restricao8[NumAux].setName(varName);

							model.add(Restricao8[NumAux]);
							expr2.end();

							//model.add( BigMauternativo * ( 1 - Alfa[v][e1][i] ) + BigMauternativo * ( 1 - Alfa[v][e2][j] ) + BigMauternativo * Beta[v][e1][i][e2][j] + Tvei[v][e1][i] >= Tvei[v][e2][j] + DESCvi[v][e2][j] + Svii[v][e2][e1] );

							NumAux++;
						}
					}
				}
			}
		}
	}
}
	// restrição 8
void ClasseModelo::Restricao_TempoMaximoEntreDescarregamentosSeguidosNaMesmaEntrega( TipoAlfa Alfa,TipoTvei Tvei, IloModel& model, int EscreveRestricao ){
	float BigMauternativo;
	IloRangeArray Restricao9;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int v1 = 0; v1 < NV; v1++) {
		for (int v2 = 0; v2 < NV; v2++) {
			for (int e1 = 0; e1 < NE; e1++) {
				if( TCDE[e1] > 1){
					for (int i = 0; i < ( TCDE[e1] - 1 ); i++) {
						NumAux++;
					}
				}
			}
		}
	}

	Restricao9 = IloRangeArray(env, NumAux);
	NumAux = 0;


	for (int v1 = 0; v1 < NV; v1++) {
		for (int v2 = 0; v2 < NV; v2++) {
			for (int e1 = 0; e1 < NE; e1++) {
				if( TCDE[e1] > 1){
					for (int i = 0; i < ( TCDE[e1] - 1 ); i++) {
						if ( EscreveRestricao == 1){
							cout << " - BigM5 * ( 1 - ALFAvei+1[" << v1 << "][" << e1 << "][" << i + 1 << "] )";
							cout << " + Tvei+1[" << v1 << "][" << e1 << "][" << i + 1 << "] <=";
							cout << " BigM5 * ( 1 - ALFAv'ei[" <<v2<< "][" <<e1<< "][" <<i<< "] )";
							cout << " + Tv'ei[" << v2 << "][" << e1 << "][" << i << "] + Teta[" << e1 << "]" << endl;
						}
						BigMauternativo = TmaxE[e1] + TempoPodePostergarEmpresa[e1];		// M5

						// declara expressão
						IloExpr expr1(env);

						expr1 += - BigMauternativo * ( 1 - Alfa[v1][e1][i+1] ) +  Tvei[v1][e1][i+1]   - BigMauternativo * ( 1 - Alfa[v2][e1][i] ) - Tvei[v2][e1][i] - DESCvi[v2][e1][i] - Teta[e1];
						Restricao9[NumAux] = expr1 <= 0;

						sprintf(varName,"Rest8_SeqMax_v%dv'%de%di%di'%d",v1,v2,e1,i,i+1);
						Restricao9[NumAux].setName(varName);

						model.add(Restricao9[NumAux]);
						expr1.end();

						//model.add( - BigMauternativo * ( 1 - Alfa[v1][e1][i+1] ) +  Tvei[v1][e1][i+1] <=  BigMauternativo * ( 1 - Alfa[v2][e1][i] ) + Tvei[v2][e1][i] + DESCvi[v2][e1][i] + Teta[e1]);

						NumAux++;

						/* if( v1 == 2 && e1 == 2 && (i + 1) == 2 && v2 == 2 && e1 == 2 && i == 1){
							cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<< endl;
							cout << " - BigM * ( 1 - Alfa[" <<v1<< "][" <<e1<< "][" <<i + 1<< "]) +  Tvei[" <<v1<< "][" <<e1<< "][" <<i + 1<< "] <=  BigM * ( 1 - Alfa[" <<v2<< "][" <<e1<< "][" <<i<< "]) Tvei[" <<v2<< "][" <<e1<< "][" <<i<< "] + Teta["<<e1<<"]" << endl;
							cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ "<< endl;
						} */
					}
				}
			}
		}
	}
}
	// restrição 10
void ClasseModelo::Restricao_TempoMinimoEntreDescarregamentosSeguidosNaMesmaEntrega(TipoAlfa Alfa, TipoTvei Tvei, IloModel& model, int EscreveRestricao ){
	 float BigMauternativo;
	IloRangeArray Restricao10;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int v1 = 0; v1 < NV; v1++) {
		for (int v2 = 0; v2 < NV; v2++) {
			for (int e1 = 0; e1 < NE; e1++) {
				if( TCDE[e1] > 1){
					for (int i = 0; i < (TCDE[e1] - 1); i++) {
						NumAux++;
					}
				}
			}
		}
	}

	Restricao10 = IloRangeArray(env, NumAux);
	NumAux = 0;

	for (int v1 = 0; v1 < NV; v1++) {
		for (int v2 = 0; v2 < NV; v2++) {
			for (int e1 = 0; e1 < NE; e1++) {
				if( TCDE[e1] > 1){
					for (int i = 0; i < (TCDE[e1] - 1); i++) {
						if ( EscreveRestricao == 1){
							cout << " BigM6 * ( 1 - ALFAvei+1[" << v1 << "][" << e1 << "][" << i +1 << "]) +";
							cout << " Tvei[" << v1 << "][" << e1 << "][" << i + 1 << "] >= ";
							cout << " Tvei[" << v2 << "][" << e1 << "][" << i << "] +  DESCvi[" << v2 << "][" << e1 << "][" << i << "] ";
							cout << "- BigM6 * ( 1 - ALFAv'ei[" << v2 << "][" << e1 << "][" << i << "] )" << endl;
						}
						BigMauternativo = TmaxE[e1] + TempoPodePostergarEmpresa[e1] + DESCvi[v2][e1][i];		// M8

						// declara expressão
						IloExpr expr1(env);

						expr1 += BigMauternativo  * ( 1 - Alfa[v1][e1][i+1]) + Tvei[v1][e1][i+1] -   Tvei[v2][e1][i] -   DESCvi[v2][e1][i] + BigMauternativo  * ( 1 - Alfa[v2][e1][i]);
						Restricao10[NumAux] = expr1 >= 0;

						//model.add( BigMauternativo  * ( 1 - Alfa[v1][e1][i+1]) + Tvei[v1][e1][i+1] >=   Tvei[v2][e1][i] +   DESCvi[v2][e1][i] - BigMauternativo  * ( 1 - Alfa[v2][e1][i]) );

						sprintf(varName,"Rest10_SeqMin_v%dv'%de%di%di'%d",v1,v2,e1,i,i+1);
						Restricao10[NumAux].setName(varName);

						model.add(Restricao10[NumAux]);
						expr1.end();

						NumAux++;

						/*if( v1 == 2 && e1 == 2 && (i + 1) == 2 && v2 == 2 && e1 == 2 && i == 1){
						cout << " ################################################################ "<< endl;
						cout << " BigM * ( 1 - Alfa[" << v1 + 1 << "][" <<e1 + 1 << "][" << i + 2 << "]) +  Tvei[" << v1 + 1 << "][" << e1 + 1 << "][" << i + 2 << "] >=  Tvei[" << v2 + 1 << "][" << e1 + 1 << "][" << i + 1 << "] +  DESCvi[" << v2 + 1 << "][" << e1 + 1 << "][" << i + 1 << "]  - BigM * ( 1 - Alfa[" <<v2 + 1 << "][" <<e1 + 1 << "][" << i + 1 << "])" << endl;
						cout << " ################################################################ "<< endl;
					}*/
					}
				}
			}
		}
	}
}
	// restrição 11 e 12
void ClasseModelo::Restricao_PrecedenciaTPvei( TipoAlfa Alfa,TipoBeta BetaProducao,TipoTPvei TPvei, IloModel& model, int EscreveRestricao1, int EscreveRestricao2){
	float BigMauternativo;
	int v1Aux;
	int v2Aux;
	int vArmazena;
	IloRangeArray Restricao11;
	IloRangeArray Restricao12;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int e1 = 0; e1 < NE; e1++) {
		for (int i = 0; i < TCDE[e1]; i++) {
			for (int e2 = 0; e2 < NE; e2++) {
				for (int j = 0; j < TCDE[e2]; j++) {
					v1Aux = 0;
					for (int p = 0; p < NP; p++) {
						for (int v1 = 0; v1 < TCVP[p]; v1++) {
							if( v1 == 0 ){
								vArmazena = v1Aux;
							}
							for (int v2 = 0; v2 < TCVP[p]; v2++) {
								if( v2 == 0 ){
									v2Aux = vArmazena;
								}
								if ( i == j and e1 == e2){

								}else{
									NumAux++;
								}
							}
						}
					}
				}
			}
		}
	}

	Restricao11 = IloRangeArray(env, NumAux);
	Restricao12 = IloRangeArray(env, NumAux);
	NumAux = 0;

	for (int e1 = 0; e1 < NE; e1++) {
		for (int i = 0; i < TCDE[e1]; i++) {
			for (int e2 = 0; e2 < NE; e2++) {
				for (int j = 0; j < TCDE[e2]; j++) {
					v1Aux = 0;
					for (int p = 0; p < NP; p++) {
						for (int v1 = 0; v1 < TCVP[p]; v1++) {
							if( v1 == 0 ){
								vArmazena = v1Aux;
							}
							for (int v2 = 0; v2 < TCVP[p]; v2++) {
								if( v2 == 0 ){
									v2Aux = vArmazena;
								}
								if ( i == j and e1 == e2){

								}else{
									// declara expressão
									IloExpr expr1(env);
									IloExpr expr2(env);

									if ( EscreveRestricao1 == 1){
										cout << " BigM7 * ( 1 - ALFAvei[" << v1Aux << "][" << e1 << "][" << i << "] ) ";
										cout << " + BigM7 * ( 1 - ALFAve'i'[" << v2Aux << "][" << e2 << "][" << j << "] ) ";
										cout << " + BigM7 * ( 1- BETAProd-veii'[" << p << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "] )";
										cout << " + TPvei'[" << v2Aux << "][" << e2 << "][" << j << "] >=";
										cout << " TPvei[" << v1Aux << "][" << e1 << "][" << i << "] +  CARRp[" << p << "] " << endl;
									}
									BigMauternativo = TmaxP[p]  + CARRp[p];			// M9

									expr1 += BigMauternativo  * ( 1 - Alfa[v1Aux][e1][i] ) + BigMauternativo  * ( 1 - Alfa[v2Aux][e2][j] ) + BigMauternativo * ( 1 - BetaProducao[p][e1][i][e2][j] )  + TPvei[v2Aux][e2][j] - TPvei[v1Aux][e1][i] -  CARRp[p];
									Restricao11[NumAux] = expr1 >= 0;

									sprintf(varName,"Rest11_PrecTPvi_p%dv%dv'%de%di%de'%di'%d", p, v1Aux, v2Aux, e1, i, e2, j);
									Restricao11[NumAux].setName(varName);

									model.add(Restricao11[NumAux]);

									//model.add( BigMauternativo  * ( 1 - Alfa[v1Aux][e1][i] ) + BigMauternativo  * ( 1 - Alfa[v2Aux][e2][j] ) + BigMauternativo * ( 1 - BetaProducao[p][e1][i][e2][j] )  + TPvei[v2Aux][e2][j] >= TPvei[v1Aux][e1][i] +  CARRp[p] );

									if ( EscreveRestricao2 == 1){
										cout << " BigM7 * ( 1 - ALFAvei[" << v1Aux << "][" << e1 << "][" << i << "] )";
										cout << " + BigM7 * ( 1 - ALFAve'i'[" << v2Aux << "][" << e2 << "][" << j << "])";
										cout << " + BigM7 * BETAProd-veii'[" << p << "][" << e1 << "][" << i << "][" << e2 << "][" << j << "]";
										cout << " + TPvei[" << v1Aux << "][" << e1 << "][" << i << "] >=";
										cout << " TPvei'[" << v2Aux << "][" << e2 << "][" << j << "] + CARRp[" << p << "]" << endl;
									}
									BigMauternativo = TmaxP[p]  + CARRp[p];			// M9

									expr2 += BigMauternativo  * ( 1 - Alfa[v1Aux][e1][i]) + BigMauternativo  * ( 1 - Alfa[v2Aux][e2][j]) + BigMauternativo  * BetaProducao[p][e1][i][e2][j]  + TPvei[v1Aux][e1][i] - TPvei[v2Aux][e2][j] - CARRp[p];
									Restricao12[NumAux] = expr2 >= 0;

									sprintf(varName,"Rest12_PrecTPvi_p%dv%dv'%de%di%de'%di'%d", p, v1Aux, v2Aux, e1, i, e2, j);
									Restricao12[NumAux].setName(varName);

									model.add(Restricao12[NumAux]);

									//model.add( BigMauternativo  * ( 1 - Alfa[v1Aux][e1][i]) + BigMauternativo  * ( 1 - Alfa[v2Aux][e2][j]) + BigMauternativo  * BetaProducao[p][e1][i][e2][j]  + TPvei[v1Aux][e1][i] >= TPvei[v2Aux][e2][j] +  CARRp[p]);

									expr1.end();
									expr2.end();
									NumAux++;
								}
								v2Aux = v2Aux + 1;
							}
							v1Aux = v1Aux + 1;
						}
					}
				}
			}
		}
	}
}
	// restrição 13
void ClasseModelo::Restricao_TempoDeVidaDoConcreto( TipoAlfa Alfa, TipoTvei Tvei, TipoTPvei TPvei, IloModel& model, int EscreveRestricao){
	float BigMauternativo;
	int vAux;
	IloRangeArray Restricao13;
	char varName[40];

	int NumAux;
	NumAux = 0;

	for (int p = 0; p < NP; p++) {
		for (int v = 0; v < TCVP[p]; v++) {
			for (int e = 0; e < NE; e++) {
				for (int i = 0; i < TCDE[e]; i++) {
					NumAux++;
				}
			}
		}
	}

	Restricao13 = IloRangeArray(env, NumAux);
	NumAux = 0;

	vAux = 0;
	for (int p = 0; p < NP; p++) {
		for (int v = 0; v < TCVP[p]; v++) {
			for (int e = 0; e < NE; e++) {
				for (int i = 0; i < TCDE[e]; i++) {
					if ( EscreveRestricao == 1){
						cout << " Tvi[" << vAux << "][" << e << "][" << i << "] - TDESCvi[" << vAux << "][" << e << "][" << i << "] ";
						cout << " -  BigM8 * ( 1 - ALFAvei[" << vAux << "][" << e << "][" << i << "] ) <= " << TVC << endl;
					}
					BigMauternativo = TmaxE[e]-  TminP[p] ;				// M10
					// declara expressão
					IloExpr expr1(env);

					expr1 += Tvei[vAux][e][i] - TPvei[vAux][e][i] - BigMauternativo  * ( 1 - Alfa[vAux][e][i]) - TVC;
					Restricao13[NumAux] = expr1 <= 0;

					sprintf(varName,"Rest13_TVC_v%de%di%d", vAux, e, i);
					Restricao13[NumAux].setName(varName);

					model.add(Restricao13[NumAux]);

					//model.add( Tvei[vAux][e][i] - TPvei[vAux][e][i] - BigMauternativo  * ( 1 - Alfa[vAux][e][i]) <= TVC );
					expr1.end();
					NumAux++;
				}
			}
			vAux = vAux + 1;
		}
	}

}


	// restrição 14 e 15
void ClasseModelo::Restricao_LimiteDeTempoNaEntrega( TipoTvei Tvei, TipoAlfa Alfa, IloModel& model, int EscreveRestricao){
	IloRangeArray Restricao14;
	IloRangeArray Restricao15;
	char varName[40];

	int NumAux;
	NumAux = 0;
	for (int v = 0; v < NV; v++) {
		for (int e1 = 0; e1 < NE; e1++) {
			for (int i = 0; i < TCDE[e1]; i++) {
				NumAux++;
			}
		}
	}

	Restricao14 = IloRangeArray(env, NumAux);
	Restricao15 = IloRangeArray(env, NumAux);

	NumAux = 0;

	for (int v = 0; v < NV; v++) {
		for (int e1 = 0; e1 < NE; e1++) {
			for (int i = 0; i < TCDE[e1]; i++) {
				// declara expressão
				IloExpr expr1(env);
				IloExpr expr2(env);

				if ( EscreveRestricao == 1){
					cout << "  Tvei[" << v << "][" << e1 << "][" << i << "] >= TminE[" << e1 <<"] *Alfa[" << v << "][" << e1 << "][" << i << "]" << endl;
				}
				expr1 += Tvei[v][e1][i] - TminE[e1]*Alfa[v][e1][i] ;
				Restricao14[NumAux] = expr1 >= 0;

				sprintf(varName,"Rest14_TveiMin_v%de%di%d", v, e1, i);
				Restricao14[NumAux].setName(varName);

				model.add(Restricao14[NumAux]);
				//model.add( Tvei[v][e1][i] >= TminE[e1] - AEe[e1] );

				if ( EscreveRestricao == 1){
					cout << "  Tvei[" << v << "][" << e1 << "][" << i << "] <= TmaxE[" << e1 <<"] *Alfa[" << v << "][" << e1 << "][" << i << "]" << endl;
				}
				expr2 += Tvei[v][e1][i] - TmaxE[e1]*Alfa[v][e1][i] ;
				Restricao15[NumAux] = expr2 <= 0;

				sprintf(varName,"Rest15_TveiMax_v%de%di%d", v, e1, i);
				Restricao15[NumAux].setName(varName);

				model.add(Restricao15[NumAux]);

				//model.add(  Tvei[v][e1][i] <= TmaxE[e1] + PEe[e1] );

				expr1.end();
				expr2.end();
				NumAux++;
			}
		}
	}
}

	// restrição 16 e 17
void ClasseModelo::Restricao_LimiteDeTempoNaPlanta( TipoTvei TPvei, TipoAlfa Alfa, IloModel& model, int EscreveRestricao ){
	int vAux;
	IloRangeArray Restricao16;
	IloRangeArray Restricao17;
	char varName[40];

	int NumAux;
	NumAux = 0;
	for (int p = 0; p < NP; p++) {
		for (int v = 0; v < TCVP[p]; v++) {
			for (int e1 = 0; e1 < NE; e1++) {
				for (int i = 0; i < TCDE[e1]; i++) {
					NumAux++;
				}
			}
		}
	}

	Restricao16 = IloRangeArray(env, NumAux);
	Restricao17 = IloRangeArray(env, NumAux);

	NumAux = 0;

	vAux = 0;
	for (int p = 0; p < NP; p++) {
		for (int v = 0; v < TCVP[p]; v++) {
			for (int e1 = 0; e1 < NE; e1++) {
				for (int i = 0; i < TCDE[e1]; i++) {
					// declara expressão
					IloExpr expr1(env);
					IloExpr expr2(env);

					if ( EscreveRestricao == 1){
						cout << "  TPvei[" << vAux << "][" << e1 << "][" << i << "] >= TminP[" << p <<"] *Alfa[" << vAux << "][" << e1 << "][" << i << "]" << endl;
					}
					expr1 += TPvei[vAux][e1][i] - TminP[p] *Alfa[vAux][e1][i] ;
					Restricao16[NumAux] = expr1 >= 0;

					sprintf(varName,"Rest16_TPviMin_p%dv%de%di%d", p, vAux, e1, i);
					Restricao16[NumAux].setName(varName);

					model.add(Restricao16[NumAux]);

					//model.add(  TPvei[vAux][e1][i] >= TminP[p] - APp[p]);
					if ( EscreveRestricao == 1){
						cout << "  TPvei[" << vAux << "][" << e1 << "][" << i << "] <= TmaxP[" << p <<"] *Alfa[" << vAux << "][" << e1 << "][" << i << "]" << endl;
					}
					expr2 += TPvei[vAux][e1][i] - TmaxP[p] *Alfa[vAux][e1][i] ;
					Restricao17[NumAux] = expr2 <= 0;

					sprintf(varName,"Rest17_TPviMax_p%dv%de%di%d", p, vAux, e1, i);
					Restricao17[NumAux].setName(varName);

					model.add(Restricao17[NumAux]);
					//model.add(  TPvei[vAux][e1][i] <= TmaxP[p] + PPp[p]);

					expr1.end();
					expr2.end();
					NumAux++;
				}
			}
			vAux = vAux + 1;
		}
	}
}


// Cria pastas
void ClasseModelo::VerificaOuCriaPastaOut(int EscreveNaTelaResultados){
	DIR* dp1;

	dp1 = opendir ("Out");

	if(!dp1){
		cout <<  "\n\n Nao tem diretorio \"Out\" !!        FUDEU MUITO!! \n" << endl;

		if(system("mkdir Out;") == 0){
			cout << " Criou pasta Out" << endl;
		}else{
			cout << " Problema ao criar pasta Out" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		dp1 = opendir ("Out");
		if(!dp1){
			cout << "\n Nao tem diretorio  \"InstS\" !!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Out\" !!  " << endl;
		}
	}else{
		if( EscreveNaTelaResultados == 1){
			cout << " Tem diretorio \"Out\" !!  " << endl;
		}
	}
	closedir( dp1 );
}
void ClasseModelo::VerificaOuCriaPastaSol(int EscreveNaTelaResultados){
	DIR* dp1;

	dp1 = opendir ("Sol");

	if(!dp1){
		cout <<  "\n\n Nao tem diretorio \"Sol\" !!        FUDEU MUITO!! \n" << endl;

		if(system("mkdir Sol;") == 0){
			cout << " Criou pasta Sol" << endl;
		}else{
			cout << " Problema ao criar pasta Sol" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		dp1 = opendir ("Sol");
		if(!dp1){
			cout << "\n Nao tem diretorio  \"Sol\" !!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Sol\" !!  " << endl;
		}
	}else{
		if( EscreveNaTelaResultados == 1){
			cout << " Tem diretorio \"Sol\" !!  " << endl;
		}
	}
	closedir( dp1 );
}

// Escreve variáveis
void ClasseModelo::EscreveVariaveisAlfaDoModeloAposResolucao(int EscreveArquivoComRespostas, int EscreveNaTelaResultados,ofstream& logfile2, IloCplex cplex, TipoAlfa Alfa){
	for (int v = 0; v< NV; v++) {
		if( EscreveArquivoComRespostas == 1){
			logfile2 << " Veiculo " << v << endl;
		}
		if( EscreveNaTelaResultados == 1){
			cout << " Veiculo " << v << endl;
		}
		for (int e = 0; e < NE; e++) {
			for( int i = 0; i < TCDE[e]; i++){
				if( EscreveNaTelaResultados == 1){
					cout << Alfa[v][e][i].getName() << " [" << cplex.getValue(Alfa[v][e][i]) << "]  ";
				}
				if( EscreveArquivoComRespostas == 1){
					logfile2 << Alfa[v][e][i].getName() << " [" << cplex.getValue(Alfa[v][e][i]) << "]  ";
				}
			}
			if( EscreveNaTelaResultados == 1){
				cout << endl;
			}
			if( EscreveArquivoComRespostas == 1){
				logfile2 << endl;
			}
		}
	}
}

void ClasseModelo::EscreveVariaveisBetaDoModeloAposResolucao(int EscreveArquivoComRespostas, int EscreveNaTelaResultados,ofstream& logfile2, IloCplex cplex,  TipoBeta Beta ){
	for (int v = 0; v< NV; v++) {
		if( EscreveNaTelaResultados == 1){
			cout << " Veiculo " << v << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << " Veiculo " << v << endl;
		}
		for (int e1 = 0; e1 < NE; e1++) {
			for( int i = 0; i < TCDE[e1]; i++){
				for (int e2 = 0; e2 < NE; e2++) {
					for( int j = 0; j < TCDE[e2]; j++){
						if( e1 == e2 and i == j){

						}else{
							if( EscreveNaTelaResultados == 1){
								cout << Beta[v][e1][i][e2][j].getName();
								cout << " [" << cplex.getValue(Beta[v][e1][i][e2][j]) << "]  ";
								cout << endl;
							}
							if( EscreveArquivoComRespostas == 1){
								logfile2 << Beta[v][e1][i][e2][j].getName();
								logfile2 << " [" << cplex.getValue(Beta[v][e1][i][e2][j]);
								logfile2 << "]  " << endl;
							}
						}
					}
				}
			}
		}
		if( EscreveNaTelaResultados == 1 ){
			cout << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << endl;
		}
	}
}

void ClasseModelo::EscreveVariaveisBetaProducaoDoModeloAposResolucao(int EscreveArquivoComRespostas, int EscreveNaTelaResultados,ofstream& logfile2, IloCplex cplex,  TipoBeta BetaProducao ){
	for (int p = 0; p < NP; p++) {
		if( EscreveNaTelaResultados == 1){
			cout << " Planta " << p << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << " Planta " << p << endl;
		}
		for (int e1 = 0; e1 < NE; e1++) {
			for( int i = 0; i < TCDE[e1]; i++){
				for (int e2 = 0; e2 < NE; e2++) {
					for( int j = 0; j < TCDE[e2]; j++){
						if( e1 == e2 and i == j){

						}else{
							if( EscreveNaTelaResultados == 1){
								cout << BetaProducao[p][e1][i][e2][j].getName();
								cout << " [" << cplex.getValue(BetaProducao[p][e1][i][e2][j]) << "]  ";
								cout << endl;
							}
							if( EscreveArquivoComRespostas == 1){
								logfile2 << BetaProducao[p][e1][i][e2][j].getName();
								logfile2 << " [" << cplex.getValue(BetaProducao[p][e1][i][e2][j]) << "]  ";
								logfile2 << endl;
							}
						}
					}
				}
			}
		}
		if( EscreveNaTelaResultados == 1 ){
			cout << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << endl;
		}
	}
}

void ClasseModelo::EscreveVariaveisTveiDoModeloAposResolucao(int EscreveArquivoComRespostas, int EscreveNaTelaResultados,ofstream& logfile2, IloCplex cplex, TipoTvei Tvei){
	for (int v = 0; v < NV; v++) {
		if( EscreveArquivoComRespostas == 1){
			logfile2 << " Veiculo " << v << endl;
		}
		if( EscreveNaTelaResultados == 1){
			cout << " Veiculo " << v << endl;
		}
		for (int e = 0; e < NE; e++) {
			for( int i = 0; i < TCDE[e]; i++){
				if( EscreveNaTelaResultados == 1){
					cout << Tvei[v][e][i].getName() << " [" << cplex.getValue(Tvei[v][e][i]) << "]  " << endl;
				}
				if( EscreveArquivoComRespostas == 1){
					logfile2 << Tvei[v][e][i].getName() << " [" << cplex.getValue(Tvei[v][e][i]) << "]  " << endl;
				}
			}
		}
		if( EscreveNaTelaResultados == 1){
			cout << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << endl;
		}
	}
}

void ClasseModelo::EscreveVariaveisTPveiDoModeloAposResolucao(int EscreveArquivoComRespostas, int EscreveNaTelaResultados,ofstream& logfile2, IloCplex cplex, TipoTPvei TPvei ){
	int vAux;
	vAux = 0;
	for (int p = 0; p < NP; p++) {
		if( EscreveNaTelaResultados == 1){
			cout << "  Planta " << p << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << "  Planta " << p << endl;
		}
		for (int v = 0; v < TCVP[p]; v++) {
			for (int e = 0; e < NE; e++) {
				for( int i = 0; i < TCDE[e]; i++){
					if( EscreveNaTelaResultados == 1){
						cout << TPvei[vAux][e][i].getName() << " [" << cplex.getValue(TPvei[vAux][e][i])  << "]  "<< endl;
					}
					if( EscreveArquivoComRespostas == 1){
						logfile2 << TPvei[vAux][e][i].getName() << " [" << cplex.getValue(TPvei[vAux][e][i]) << "]  "<< endl;
					}
				}
			}
			vAux = vAux + 1;
		}
		if( EscreveNaTelaResultados == 1){
			cout << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << endl;
		}
	}
}

void ClasseModelo::EscreveVariaveisZeDoModeloAposResolucao(int EscreveArquivoComRespostas, int EscreveNaTelaResultados,ofstream& logfile2, IloCplex cplex, IloFloatVarArray Ze ){
	for (int e = 0; e < NE; e++) {
		for( int i = 0; i < TCDE[e]; i++){
			if( EscreveNaTelaResultados == 1){
				cout << Ze[e].getName() << " [" << cplex.getValue(Ze[e]) << "]  "<< endl;
			}
			if( EscreveArquivoComRespostas == 1){
				logfile2 << Ze[e].getName() << " [" << cplex.getValue(Ze[e]) << "]  "<< endl;
			}
		}
	}

	if( EscreveNaTelaResultados == 1){
		cout << endl;
	}
	if( EscreveArquivoComRespostas == 1){
		logfile2 << endl;
	}

}

// Calcula Função Objetivo Real
void ClasseModelo::CalculaFuncaoObjetivo(  IloCplex cplex, IloFloatVarArray Ze,   double& ValorRealFuncaoObjetivo){
	ValorRealFuncaoObjetivo = 0;
	for( int e = 0; e < NE; e++){
		ValorRealFuncaoObjetivo = ValorRealFuncaoObjetivo + cplex.getValue(Ze[e]);
	}

}



// Escreve a Solução
void ClasseModelo::EscreveItinerarioVeiculos( int EscreveNaTelaResultados,int EscreveArquivoComRespostas, ofstream& logfile2, IloCplex cplex, TipoAlfa Alfa, TipoTvei Tvei, TipoTPvei TPvei){
	int vAux;

	vAux = 0;
	for (int p = 0; p < NP; p++) {
		if( EscreveNaTelaResultados == 1){
			cout << "     Planta " << p + 1 << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << "     Planta " << p + 1 << endl;
		}
		for (int v = 0; v < TCVP[p]; v++) {
			if( EscreveNaTelaResultados == 1){
				cout << " Veiculo " << vAux + 1 << endl;
			}
			if( EscreveArquivoComRespostas == 1){
				logfile2 << " Veiculo " << vAux + 1 << " : "<< endl;
			}
			for (int e = 0; e < NE; e++) {
				for( int i = 0; i < TCDE[e]; i++){
					if( 0.9 < cplex.getValue(Alfa[vAux][e][i]) && cplex.getValue(Alfa[vAux][e][i]) < 1.1){
						if( EscreveNaTelaResultados == 1){
							cout << '\t' << " Entrega[Construcao->" << e+1 << "][Job->" << i+1<< "] carrega as ";
							printf("%.2f", cplex.getValue(TPvei[vAux][e][i]) );
							cout << ", sai da planta as ";
							printf("%.2f", ( cplex.getValue(TPvei[vAux][e][i]) + CARRp[p] ) );
							cout << ", chega a entrega" << e + 1 << " as " ;
							printf("%.2f", cplex.getValue(Tvei[vAux][e][i]) );
							cout << " e sai as  ";
							printf("%.2f", ( cplex.getValue(Tvei[vAux][e][i]) + DESCvi[vAux][e][i]) );
							cout << ", retorna a planta as ";
							printf("%.2f", ( cplex.getValue(Tvei[vAux][e][i]) + DESCvi[vAux][e][i] + TEMep[e][p] ) );
							cout << endl;
						}
						if( EscreveArquivoComRespostas == 1){
							logfile2 << '\t' << " Entrega[Construcao->" << e+1 << "][Job->" << i+1<< "] carrega as ";
							logfile2 <<  cplex.getValue(TPvei[vAux][e][i]) ;
							logfile2  << ", sai da planta as " << cplex.getValue(TPvei[vAux][e][i]) + CARRp[p] ;
							logfile2 << ", chega a entrega" << e + 1 << " as " << cplex.getValue(Tvei[vAux][e][i]);
							logfile2 << " e sai as  " << cplex.getValue(Tvei[vAux][e][i]) + DESCvi[vAux][e][i] ;
							logfile2 << ", retorna a planta as " << cplex.getValue(Tvei[vAux][e][i]) + DESCvi[vAux][e][i] + TEMep[e][p];
							logfile2 << endl;
						}
					}
				}
			}
			vAux = vAux + 1;
		}
	}
}

void ClasseModelo::EscreveEntregasNosClientes(int EscreveNaTelaResultados,int EscreveArquivoComRespostas, ofstream& logfile2, IloCplex cplex, TipoAlfa Alfa, TipoTvei Tvei){
	int vAux;
	if( EscreveNaTelaResultados == 1){
		cout << endl << endl;
		cout << "           Tempo de entrega em cada cliente         " << endl;
	}

	if( EscreveArquivoComRespostas == 1){
		logfile2 << endl << endl;
		logfile2 <<  "           Tempo de entrega em cada cliente         " << endl;
	}
	for (int e = 0; e < NE; e++) {
		if( EscreveNaTelaResultados == 1){
			cout << " Cliente " << e +1 << "\t[ ";
			printf("%.2f", TminE[e]);
			cout << "\t<=\t";
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << " Cliente " << e +1 << "\t[ ";
			logfile2 << TminE[e];
			logfile2 << "\t<=\t";
		}
		for( int i = 0; i < TCDE[e]; i++){
			vAux = 0;
			for (int p = 0; p < NP; p++) {
				for (int v = 0; v < TCVP[p]; v++) {
					if( 0.9 < cplex.getValue(Alfa[vAux][e][i]) && cplex.getValue(Alfa[vAux][e][i]) < 1.1 ){
						//cout << "   Tvei[" << vAux << "][" << e << "][" << i <<"] " << TveiImprime[vAux][e][i];
						if( EscreveNaTelaResultados == 1){
							cout << "\t";
							printf("%.2f", cplex.getValue(Tvei[vAux][e][i]) );
							cout << "[v" << vAux + 1<< "]";
						}
						if( EscreveArquivoComRespostas == 1){
							logfile2 << "\t";
							logfile2 << cplex.getValue(Tvei[vAux][e][i]);
							logfile2 << "(v[" << vAux + 1<< "] e[" << e + 1 << "] i[" << i + 1 << "] )";
						}
					}
					vAux++;
				}

			}
		}
		if( EscreveNaTelaResultados == 1){
			cout << "\t<=\t";
			printf("%.2f", TmaxE[e]);
			cout << "]" << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << "\t<=\t";
			logfile2 << TmaxE[e];
			logfile2 << "]" << endl;
		}
	}
}

void ClasseModelo::EscreveUtilizacaoVeiculos(int EscreveNaTelaResultados,int EscreveArquivoComRespostas, ofstream& logfile2, IloCplex cplex, TipoAlfa Alfa, TipoTvei Tvei){
	int vAux;
	int UsouCaminhao;
	int AtendeCliente;
	int AtendendoCliente;


	if( EscreveNaTelaResultados == 1){
		cout << endl << endl;
		cout << "           Veiculos usados         " << endl;
	}
	if( EscreveArquivoComRespostas == 1){
		logfile2 << endl << endl;
		logfile2 << "           Veiculos usados         " << endl;
	}
	vAux = 0;
	for (int p = 0; p < NP; p++) {
		if( EscreveNaTelaResultados == 1){
			cout << "Planta " << p + 1 << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << "Planta " << p + 1 << endl;
		}
		for (int v = 0; v < TCVP[p]; v++) {
			UsouCaminhao = 0;
			for (int e = 0; e < NE; e++) {
				for( int i = 0; i < TCDE[e]; i++){
					if( 0.9 < cplex.getValue(Alfa[vAux][e][i]) && cplex.getValue(Alfa[vAux][e][i]) < 1.1 ){
						UsouCaminhao = 1;
					}
				}
			}
			if( UsouCaminhao == 1){
				if( EscreveNaTelaResultados == 1){
					cout << "  Veiculo " << vAux + 1 << " \t[clientes ->\t";
				}
				if( EscreveArquivoComRespostas == 1){
					logfile2  << "  Veiculo " << vAux + 1 << " \t[clientes ->\t";
				}
				for (int e = 0; e < NE; e++) {
					AtendeCliente = 0;
					AtendendoCliente = 0;
					for( int i = 0; i < TCDE[e]; i++){
						if( 0.9 < cplex.getValue(Alfa[vAux][e][i]) && cplex.getValue(Alfa[vAux][e][i]) < 1.1  ){
							AtendeCliente = AtendeCliente + 1;
							AtendendoCliente = 1;
						}
						if( AtendeCliente == 1 && AtendendoCliente == 1){
							if( EscreveNaTelaResultados == 1){
								cout << "   " << e + 1 ;
							}
							if( EscreveArquivoComRespostas == 1){
								logfile2 << "   " <<  e + 1 << " ";
							}
						}
						if(AtendendoCliente == 1){
							if( EscreveNaTelaResultados == 1){
								cout << "(" << cplex.getValue(Tvei[vAux][e][i]) << ") ";
							}
							if( EscreveArquivoComRespostas == 1){
								logfile2 << "(" << cplex.getValue(Tvei[vAux][e][i]) << ") ";
							}
							AtendendoCliente = 0;
						}

					}
				}
				if( EscreveNaTelaResultados == 1){
					cout << "]" << endl;
				}
				if( EscreveArquivoComRespostas == 1){
					logfile2  << "]" << endl;
				}
			}
			vAux++;
		}
		if( EscreveNaTelaResultados == 1){
			cout << endl;
		}
		if( EscreveArquivoComRespostas == 1){
			logfile2 << endl;
		}
	}
}

// Resolve modelo
int ClasseModelo::Cplex(string Nome, int  TempoExecucao, int &status, double &primal, double &dual, double& SolucaoReal,   double &gap, double &tempo,  vector < string > NomeInstanciaLimiteUpper, vector < double > ValorLimiteUpper){

	int Escreve;				// Escreve variaveis criadas

	int EscreveVariaveis;
	int OutPut1;
	int OutPut2;
	int SaidaPastaSeparada;
	int EscreveArquivoComRespostas;
	int EscreveNaTelaResultados;
	vector < int > EscreveRestricao;
	EscreveRestricao.resize(20+1);
	for( int i = 0; i <= 20; i++){
		EscreveRestricao[i] = 0;
	}

	vector < int > TamanhoPenalidade;
	TamanhoPenalidade.resize(2+1);
	for( int i = 0; i <= 2; i++){
		TamanhoPenalidade[i] = 2;
	}

	Escreve = 0;				// Escreve as variaveis criadas
	EscreveVariaveis = 1;
	OutPut1 = 1;
	OutPut2 = 1;
	SaidaPastaSeparada = 1;
	EscreveArquivoComRespostas = 1;
	EscreveNaTelaResultados = 0;

// Começa a escrever modelo do Cplex
	IloModel 	model(env);

/* Declara variaveis */

// Variavel ALFA
	TipoAlfa 	Alfa(env, NV);
	CriaAlfa(Alfa,Escreve);

// Variavel BETA
	TipoBeta 	Beta(env, NV);
	CriaBeta(Beta,Escreve);

// Variavel BETAProducao
	TipoBeta 	BetaProducao(env, NV);
	CriaBetaProducao(BetaProducao,Escreve);


// Variavel Ze
	TipoZe 		Ze(env,NE);
	CriaZe(Ze ,Escreve);



// Variavel Tvei
	TipoTvei 	Tvei(env,NV);
	CriaTvei( Tvei, Escreve);

// Variavel TPvei
	TipoTPvei 	TPvei(env,NV);
	CriaTPvei( TPvei, Escreve);




// Calcula variaveis de adiantamento e postergamento dos limites de tempo
	CalculaTempoPodeAdiantarOuPostergarEmpresa(Escreve);



// Funcao Objetivo
	FuncaoObjetivo(Ze, model, EscreveRestricao[0]);

// Restrição 1 : Antendimento das Demandas
	Restricao_AtendimentoDasDemandas(Alfa, model, EscreveRestricao[1]);
// Restrição  2 : Lower bound Ze
	Restricao_LowerBoundZe(Ze, Tvei, Alfa, model, EscreveRestricao[2]);
// Restrição  3 : Vinculo Tvei e TPvei
	Restricao_VinculoTveiTPvei( Alfa, TPvei, Tvei,model, EscreveRestricao[3] );
// Restrição  5 e 6 : de precedencia Tvei
	Restricao_PrecedenciaTvei(  Alfa, Beta, Tvei, model,  EscreveRestricao[5], EscreveRestricao[6]);
// Restrição  7:
	Restricao_TempoMaximoEntreDescarregamentosSeguidosNaMesmaEntrega( Alfa, Tvei, model, EscreveRestricao[7] );
// Restrição 8
    Restricao_TempoMinimoEntreDescarregamentosSeguidosNaMesmaEntrega( Alfa, Tvei, model, EscreveRestricao[10] );
// Restrição 9
    Restricao_PrecedenciaTPvei( Alfa, BetaProducao, TPvei, model, EscreveRestricao[11],EscreveRestricao[12]);
// Restrição 10
    Restricao_TempoDeVidaDoConcreto( Alfa,Tvei,TPvei, model,EscreveRestricao[13]);
// Restrição  11
	Restricao_LimiteDeTempoNaEntrega( Tvei,  Alfa, model, EscreveRestricao[14] );
// Restrição  12
	Restricao_LimiteDeTempoNaPlanta(  TPvei,  Alfa, model, EscreveRestricao[15] );




// Modelo
	IloCplex *cplex;

	cplex = new IloCplex(model);
	//cplex->exportModel("model.lp");

// Cria pasta OUT
	VerificaOuCriaPastaOut(EscreveNaTelaResultados);

	Nome1 = "./Out/";
	Nome1 += Nome;

	//cout << endl << endl << " arquivo a gravar a saida " << c1 << endl << endl;

	ofstream logfile1(Nome1.c_str());

	if(SaidaPastaSeparada == 1){
		cplex->setOut(logfile1);
	}
	cplex->setParam(IloCplex::TiLim,  TempoExecucao);
	cplex->setParam(IloCplex::Threads, 12);

	for( int i = 0; i < (int) NomeInstanciaLimiteUpper.size(); i++){

		if( Nome.compare(NomeInstanciaLimiteUpper[i].c_str()) == 0){
			//cout << endl << endl << "		Usou o Limite superior em " << NomeInstanciaLimiteUpper[i] << " no valor de " << ValorLimiteUpper[i] << endl << endl;
			cplex->setParam(IloCplex::Param::MIP::Tolerances::UpperCutoff, ValorLimiteUpper[i]);
		}
	}

	Tempo1 = cplex->getCplexTime();

	//cout << endl << " setou tempo" << endl << endl;
	primal = -1;
	dual = -1;
	SolucaoReal = -1;
	gap = -1;

// Resolve o modelo.
	if (!cplex->solve()) {
		cerr << "Failed to optimize LP." << endl;
		status = cplex->getStatus();
		cout << " status = (" << status << ")" << endl;
		tempo = cplex->getCplexTime() - Tempo1;
		logfile1.close();
		//throw(-1);                                                   // Olhar!!!!!!!!!!!!!!!!!!

		//model.end();				// problema, trava o programa. olhar! falam que demora muito. que é melhor deletar o objeto IloClpex

		delete(cplex);

		Alfa.clear();
		Beta.clear();
		BetaProducao.clear();
		Ze.clear();
		Tvei.clear();
		TPvei.clear();
		TPvei.clear();
		EscreveRestricao.clear();

		return (0);
	}else{

		//cout << endl << " rodou " << endl << endl;

		Tempo2 = cplex->getCplexTime();

		VerificaOuCriaPastaSol(EscreveNaTelaResultados);

		Nome2 = "./Sol/";
		Nome2 += Nome;

		//cout << endl << endl << " arquivo a gravar a solucao " << Nome2 << endl << endl;

		ofstream logfile2(Nome2.c_str());

		status = cplex->getStatus();
		primal = cplex->getObjValue();
		dual = cplex->getBestObjValue();
		if( cplex->getStatus() == 1 || cplex->getStatus() == 2 || cplex->getStatus() == 4 ){
			CalculaFuncaoObjetivo(		*cplex, Ze, 	SolucaoReal);
		}
		gap =  100 * ( cplex->getObjValue() - cplex->getBestObjValue() ) / cplex->getObjValue();
		tempo = Tempo2 - Tempo1;

		if( EscreveNaTelaResultados == 1){
			cout << "Solution status = " << status << " [" << cplex->getStatus() << "] "<< endl;
			cout << "Solution primal cost = " << primal << endl;
			cout << "Solution dual cost = " << dual << endl ;
			cout << "Soution with delay = " << SolucaoReal << endl;
			cout << "Gap = " << gap << "%" << endl ;
			cout << "Tempo = " << tempo << " segundos. " << endl<< endl;
		}

		if( EscreveArquivoComRespostas == 1){
			logfile2 <<  "Solution status = " << " [" << cplex->getStatus() << "] "<< endl;
			logfile2 << "Solution primal cost = " << primal << endl;
			logfile2 << "Solution dual cost = " << dual << endl ;
			logfile2 << "Soution with delay = " << SolucaoReal << endl;
			logfile2 << "Gap = " << gap  << "%" << endl ;
			logfile2 << "Tempo = " << tempo << " segundos. " << endl << endl;
		}

		if( EscreveVariaveis == 1){
	// Imprimi Variaveis
			EscreveVariaveisAlfaDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Alfa);
			EscreveVariaveisBetaDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Beta);
			EscreveVariaveisBetaProducaoDoModeloAposResolucao(		EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, BetaProducao);
			EscreveVariaveisTveiDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Tvei);
			EscreveVariaveisTPveiDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, TPvei);
			EscreveVariaveisZeDoModeloAposResolucao(				EscreveArquivoComRespostas, EscreveNaTelaResultados, logfile2, *cplex, Ze);

		}

		if( OutPut1 == 1){
	// Itinerario dos veiculos
			EscreveItinerarioVeiculos( EscreveNaTelaResultados, EscreveArquivoComRespostas, logfile2,	*cplex, Alfa,  Tvei, TPvei);
		}

		if( OutPut2 == 1){
	// Tempo de cada entrega em cada cliente
			EscreveEntregasNosClientes(EscreveNaTelaResultados,EscreveArquivoComRespostas, logfile2,	*cplex, Alfa,  Tvei);
	// Veiculos usados
			EscreveUtilizacaoVeiculos( EscreveNaTelaResultados,EscreveArquivoComRespostas, logfile2,	*cplex, Alfa,  Tvei);
		}

		logfile1.close();
		logfile2.close();

		//model.end();				// problema, trava o programa. olhar! falam que demora muito. que é melhor deletar o objeto IloClpex

		delete(cplex);

		Alfa.clear();
		Beta.clear();
		BetaProducao.clear();
		Ze.clear();
		Tvei.clear();
		TPvei.clear();
		TPvei.clear();
		EscreveRestricao.clear();



		return (1);
	}
}

ClasseModelo::~ClasseModelo(){



	TCVP.clear();
	CVP.clear();
	TCDE.clear();
	CDE.clear();
	TEMpe.clear();
	TEMep.clear();
	DESCvi.clear();
	CARRp.clear();
	Teta.clear();
	Svii.clear();
	TminE.clear();
	TmaxE.clear();
	TminP.clear();
	TmaxP.clear();
	Nome1.clear();
	Nome2.clear();
	TempoPodeAdiantarEmpresa.clear();
	TempoPodePostergarEmpresa.clear();


	env.end();


}

#endif /* MODELO_HPP_ */
