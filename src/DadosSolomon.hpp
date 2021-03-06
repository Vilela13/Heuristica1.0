/*
 * DadosSolomon.hpp
 *
 *  Created on: 19/05/2015
 *      Author: mvus
 */

#ifndef DADOSSOLOMON_HPP_
#define DADOSSOLOMON_HPP_

#include "Bibliotecas.hpp"

class CoordenadaNo{
public:
	int NumeroNo;
	double CoordenadaX;
	double CoordenadaY;
};

class DadosSolomon{

public:
    DadosSolomon();

// Variaveis de leitura do arquivo
	string 	NomeInstancia;
	string 	Auxiliar;
	int 	NumeroVeiculos;
	int 	Capacidade;

	int 	NumeroNosDadosSolomon;

	vector< CoordenadaNo > NosCoord;


	vector< int > Demanda;
	vector< vector< int > > JanelaDeTempo;
	vector< int > TempoDeServico;
	int 	x;
	int 	y;
	int 	AuxiliarInt;

// Variaveis de escrita dos arquivos de saida

	int 	NumeroPlantas;
	vector < CoordenadaNo > NoPlanta;
	int 	NumeroClientes;
	vector < CoordenadaNo > NoCliente;
	int 	NumeroCaminhoes;
	double Velocidade;

// Declara variaveis

	char 	*b;
	char 	*aux1;

	int 	CaminhaoAux;

	vector < int > CaminhoesPlanta;
	vector < int > NumeroCarretas;		// guarda o numero de clientes

	long int  	TempoDeDescarga;
	long int  	TemproEntreEntregas;
	long int  	TempoPlanta;
	long int  	TempoDeVidaConcreto;
	long int  	TempoEntreEntregas;

	vector < long int  > HoraInicioPlanta;
	vector < long int  > HoraFinalPlanta;

	vector < long int  > HoraInicioCliente;
	vector < long int  > HoraFinalCliente;

	ifstream Instancia;
	ofstream ComandosR;
	ofstream ComandosExcel;
	ofstream InstanciaSolomon;
	ofstream DadosInstanciaSalomonCriada;

	string 	NomeAux;

// Funções

	void CarregarNumeroNosCoordenadas( string Nome);

	void EscreverDadosLidosInstanciaSolomon();

	void CriaPastaInstS();
	void CriaPastaDat();

	void CriarInstanciaSolomon(string Nome); //, int NumeroVERSAO, int MultiplicadorTempoDescarga );

	void EscreverComandosR(string,char );

	void EscreverComandosExcel(string);


    ~DadosSolomon();

};

DadosSolomon::DadosSolomon(){
	AuxiliarInt = 0;
	Capacidade = 0;
	NumeroNosDadosSolomon = 0;
	NumeroVeiculos = 0;
	x = 0;
	y = 0;
	AuxiliarInt = 0;
	CaminhaoAux = 0;

	b = NULL;
	aux1  = NULL;

	NumeroPlantas = 0;
	NumeroClientes = 0;
	NumeroCaminhoes = 0;
	Velocidade = 0;

	TempoDeDescarga = 0;
	TemproEntreEntregas = 0;
	TempoPlanta = 0;
	TempoDeVidaConcreto = 0;
	TempoEntreEntregas = 0;

}

void 	DadosSolomon::CarregarNumeroNosCoordenadas( string Nome){

	int 	EscreveDadosLidos = 0;

	Instancia.open(Nome.c_str());

	Instancia >> NomeInstancia;

	if( EscreveDadosLidos == 1){
		cout << " Nome Instancia no carrega dados = " << NomeInstancia << endl;
	}

	for( int i = 0; i<3; i++){
        Instancia >>Auxiliar;
        if( EscreveDadosLidos == 1){
        	cout << Auxiliar << "  ";
        }
    }
	if( EscreveDadosLidos == 1){
		cout << endl;
	}

	Instancia >> NumeroVeiculos;
	if( EscreveDadosLidos == 1){
		cout << NumeroVeiculos << "\t\t\t";
	}

	Instancia >> Capacidade;
	if( EscreveDadosLidos == 1){
		cout << Capacidade << endl;
	}

	// Guarda os dados a serem lidos

	for( int i = 0; i<12; i++){
		Instancia >> Auxiliar;
		if( EscreveDadosLidos == 1){
			cout << Auxiliar << "\t";
		}
	}
	if( EscreveDadosLidos == 1){
		cout << endl;
	}

	string name;
	istringstream linha2Aux;

	NumeroNosDadosSolomon = 0;

	while ( getline (Instancia,name) ){
		if( name.size() > 5 ){
			if( EscreveDadosLidos == 1){
				cout << "linha " << name ;
			}
			linha2Aux.str(name);

			NosCoord.resize(NosCoord.size() + 1);
			linha2Aux >> NosCoord[ NumeroNosDadosSolomon ].NumeroNo;
			linha2Aux >> NosCoord[ NumeroNosDadosSolomon ].CoordenadaX;
			linha2Aux >> NosCoord[ NumeroNosDadosSolomon ].CoordenadaY;

			Demanda.resize( Demanda.size() + 1);
			linha2Aux >>Demanda[ NumeroNosDadosSolomon ];

			JanelaDeTempo.resize( JanelaDeTempo.size() + 1);
			JanelaDeTempo[JanelaDeTempo.size() - 1].resize(2);

			linha2Aux >> JanelaDeTempo[ NumeroNosDadosSolomon ][0];
			linha2Aux >> JanelaDeTempo[ NumeroNosDadosSolomon ][1];

			TempoDeServico.resize( TempoDeServico.size() + 1);
			linha2Aux >>TempoDeServico[ NumeroNosDadosSolomon ];
			NumeroNosDadosSolomon++;
		}
	}

    //cout << endl << endl << " DadosSolomon " << endl << endl;
    Instancia.close();
}

void 	DadosSolomon::EscreverDadosLidosInstanciaSolomon(){
	cout << endl << endl;

	cout << "Nome: " << NomeInstancia << endl;
	cout << "Numero de Veiculos: " << NumeroVeiculos<< endl;
	cout << "Capacidade: " << Capacidade << endl;
	cout << "Numero de Nos: " << NumeroNosDadosSolomon << endl << endl;

	cout << " Numero No \t Coordenada X \t Coordenada Y \t Demanda \t InicioJanela \t FimJanela \t TempoServico"<< endl;
    for( int i = 0; i < NumeroNosDadosSolomon; i++){
        cout << "\t " << NosCoord[i].NumeroNo << "\t\t" << NosCoord[i].CoordenadaX  << "\t\t" << NosCoord[i].CoordenadaY << "\t\t" << Demanda[i] << "\t\t";
        cout << JanelaDeTempo[i][0]  << "\t\t" << JanelaDeTempo[i][1]  << "\t\t" << TempoDeServico[i] << endl;
    }
    cout << endl << endl;

}

void 	DadosSolomon::CriaPastaInstS(){
	DIR* dp1;

	dp1 = opendir ("InstS");

	if(!dp1){
		cout <<  "\n Nao tem diretorio \"InstS\"!!            FUDEU MUITO!! \n" << endl;

		if(system("mkdir InstS;") == 0){
			cout << " Criou pasta InstS" << endl;
		}else{
			cout << " Problema ao criar pasta InstS" << endl;
		}

		// Outra maneira de criar arquivos
		//SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		dp1 = opendir ("InstS");

		if(!dp1){
			cout << "\n Nao tem diretorio \"InstS\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"InstS\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"InstS\" !!  " << endl;
	}

	closedir( dp1 );
}

void 	DadosSolomon::CriaPastaDat(){
	DIR* dp1;

	dp1 = opendir ("Dat");

	if(!dp1){
		cout <<  "\n Nao tem diretorio \"Dat\"!!            FUDEU MUITO!! \n" << endl;

		if(system("mkdir Dat;") == 0){
			cout << " Criou pasta Dat" << endl;
		}else{
			cout << " Problema ao criar pasta Dat" << endl;
		}

		// Outra maneira de criar arquivos
		//SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		dp1 = opendir ("Dat");

		if(!dp1){
			cout << "\n Nao tem diretorio \"Dat\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Dat\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"Dat\" !!  " << endl;
	}

	closedir( dp1 );

}

void 	DadosSolomon::CriarInstanciaSolomon(string Nome) { //,  int NumeroVERSAO, int MultiplicadorTempoDescarga ){

	string 	CaminhoArquivo1;
	string 	CaminhoArquivo2;

	string 	Versao;
	string 	Dados;
	string 	TXT;

	long int HorarioInicioPlanta;
	long int HorarioFinalPlanta;

	long int TempoCarreta;
	int NumeroMaxCarretas;
	long int InicioMinAtendimento;
	long int HorarioMinimoConstrucao;
	long int HorarioMaximoConstrucao;

	int NoPlantaAux;
	int NoConstrucaoAux;

	int NumeroCaminhoesPorPlanta;

	double DistanciaMaxima;
	double DistanciaAuxiliar;

	CoordenadaNo No1;
	CoordenadaNo No2;

	double VelocidadeAux;

	long int InicioAlmoco;
	long int FinalAlmoco;

	stringstream ConverterIntEmString;

	double MultiplicadorTempoDescarga;
	int 	NumeroVERSAO;

	//double AuxiliarNumero;
	//double Lixo;

	int EscreveVelocidadeMinima;

	double MinutosEmUmaHora;
	MinutosEmUmaHora = 60;

	EscreveVelocidadeMinima = 1;

	// Isso vale só para iniciar e escrever os dados da instancia passada
	//MultiplicadorTempoDescarga = 2;
	//NumeroVERSAO = 13;

	NumeroPlantas 	= 1;
	NumeroClientes 	= 5;

	TempoDeDescarga 	= 10; // equivaelente a 10 minutos
	TemproEntreEntregas = 10; // equivaelente a 10 minutos
	TempoPlanta 		= 5; // equivalente a 5 minutos(4 min = 0.066667 ; 3min = 0.05 e 2min = 0.0333333)
	TempoDeVidaConcreto = 90;			// 1,5 horas

	HorarioInicioPlanta = 420;		// (7:00)
	HorarioFinalPlanta = 1080;		// (18:00)

	TempoCarreta = (long int) (MultiplicadorTempoDescarga * TempoDeDescarga); 			// tempo que se tem na janela de atendiemnto para atender a uma demanda

	cout << " TempoCarreta = " << TempoCarreta << endl;

	NumeroMaxCarretas = 5;			// numero maximo de demandas em uma construção
	InicioMinAtendimento = 30;		// valor minimo que duas janelas de atendiemto podem ter no minimo caso os horarios inicio de atendiemnto iniciais forem difrentes
	HorarioMinimoConstrucao = 480;	// horario minimo que uma janela de tempo pode ter (8:00)
	HorarioMaximoConstrucao = 1020;	// horario maximo que uma janela de tempo pode ter (17:00)

	NumeroCaminhoesPorPlanta = 10;

	InicioAlmoco = 720;		// 12:00
	FinalAlmoco = 810;		// 13:30

	DistanciaMaxima = 0;

	for( int i = 1; i < NumeroNosDadosSolomon; i++){
		//cout <<   "      no [" << i << "]" << endl;
		DistanciaAuxiliar = sqrt( pow( NosCoord[0].CoordenadaX - NosCoord[i].CoordenadaX ,2) + pow( NosCoord[0].CoordenadaY - NosCoord[i].CoordenadaY ,2) );
		if( DistanciaMaxima < DistanciaAuxiliar ){
			DistanciaMaxima = DistanciaAuxiliar;
			No1 = NosCoord[i];
			No2 = NosCoord[0];
		}
	}

	//cout << " numero normal = " << 120.934 << " numero com (int) = " << (int) 120.934 << endl; // sempre arredonda para baixo

	if( EscreveVelocidadeMinima == 1){
		cout << endl << endl << "      Maior distancia entre nos = " << DistanciaMaxima << endl;
		cout << " No " << No1.NumeroNo << " [ " << No1.CoordenadaX << "," << No1.CoordenadaY << "] ao No "  << No2.NumeroNo << " [ " << No2.CoordenadaX << "," << No2.CoordenadaY << "]" << endl;
		cout << "  tempo entre nos a 20 km/h = " <<  (int) ( (DistanciaMaxima/20) * 60 ) << endl;
		cout << "  tempo entre nos a 30 km/h = " <<  (int) ( (DistanciaMaxima/30) * 60 ) << endl;
		cout << "  tempo entre nos a 40 km/h = " <<  (int) ( (DistanciaMaxima/40) * 60 ) << endl;
		cout << "  tempo entre nos a 50 km/h = " <<  (int) ( (DistanciaMaxima/50) * 60 ) << endl;

		VelocidadeAux = DistanciaMaxima/TempoDeVidaConcreto;

		cout << " Velocidade minima para que os nos mais distantes entre se não possuam um tempo de deslocamento entre eles superior ao tempo de vida do concreto. " << endl;
		cout << " Velocidade Minima = " << VelocidadeAux;
		cout << endl<< endl<< endl;
	}

	Velocidade 	= 30/MinutosEmUmaHora ;		// velocidade em hora dividido por minutos (60), da a velocidade por minuto

	//cout << endl << endl << " Velocidade = " << Velocidade << endl << endl;

	//binomial_distribution<int> distribution(5,0.5); 		// gera numeros segundo a distribuição binomial

// Cria diretorio caso não exista
	CriaPastaInstS();

// Cria o nome da instancia para o modelo

	cout << endl << endl << " NomeInstancia = " << NomeInstancia << endl << endl;

	if( Nome.size() > 3){
		if( NomeInstancia[0] == 'R' || NomeInstancia[0] == 'C'){
			Versao = "-V";
		}else{
			cout << endl << endl <<  " Arquivo inconforme com as possiveis entradas" << endl << endl;
		}

		//srand(NumeroVERSAO);		// O gerador é o numero da versão
		srand(clock()+time(NULL));			// gera numeros aleatorios

		//cout << "  rand =" << rand() << endl << endl;

		//AuxiliarNumero = rand()%10000;

		//cout << endl << endl << " Numero de vezes no rand => " << AuxiliarNumero << "  rand = " << rand() << endl << endl << endl;

		//for( int i = 0; i < AuxiliarNumero; i++){
			//Lixo = rand();
		//}

		NomeAux = Nome;

		NomeAux.resize(NomeAux.size()-4);
		NomeAux += "-P";
		ConverterIntEmString << NumeroPlantas;
		NomeAux += ConverterIntEmString.str();
		ConverterIntEmString.str("");
		NomeAux += "C";
		ConverterIntEmString << NumeroClientes;
		NomeAux += ConverterIntEmString.str();
		ConverterIntEmString.str("");
		NomeAux += "-I";
		ConverterIntEmString << MultiplicadorTempoDescarga ;
		NomeAux += ConverterIntEmString.str();
		ConverterIntEmString.str("");
		NomeAux += "-V";
		ConverterIntEmString << NumeroVERSAO;
		NomeAux += ConverterIntEmString.str();
		ConverterIntEmString.str("");
		TXT 	= ".txt";
		NomeAux += TXT;

		cout << "      Nome da Instancia Solomon = " << NomeAux << endl << endl;

	}else{
		cout << "Arquivo passado com tamanho invaldo " <<  Nome << endl ;
	}

	//cout <<  "  Nome = " << Nome << endl;

	//CaminhoArquivo1 	= "./";
	CaminhoArquivo1 	= "./InstS/";
	CaminhoArquivo1 	+= NomeAux;

	cout << endl << "  Arquivo = " << NomeAux << "  Caminho = " << CaminhoArquivo1 << endl;

// Cria arquivo para guardar os dados da instancia criada

	if( NomeInstancia[0] == 'R' || NomeInstancia[0] == 'C' ){

		InstanciaSolomon.open(CaminhoArquivo1.c_str());

		CriaPastaDat();

		CaminhoArquivo2 = "./Dat/";
		CaminhoArquivo2 += NomeAux;

		DadosInstanciaSalomonCriada.open(CaminhoArquivo2.c_str());

		//cout << endl << "  Caminho salvar em pasta Dat = " << CaminhoArquivo2 << endl;

		DadosInstanciaSalomonCriada << CaminhoArquivo2 << endl;
		InstanciaSolomon << NomeAux << endl;

		//Inicializa Parametros

		NoPlanta.resize(NumeroPlantas + 1);
		HoraInicioPlanta.resize(NumeroPlantas + 1);
		HoraFinalPlanta.resize(NumeroPlantas + 1);

		NoPlanta[1].NumeroNo = NosCoord[0].NumeroNo;
		NoPlanta[1].CoordenadaX = NosCoord[0].CoordenadaX;
		NoPlanta[1].CoordenadaY = NosCoord[0].CoordenadaY;
		HoraInicioPlanta[1] = HorarioInicioPlanta;
		HoraFinalPlanta[1]  = HorarioFinalPlanta;
		NosCoord.erase(NosCoord.begin());

		for(int p = 2; p <= NumeroPlantas; p++){
			cout << "    planta " << p << " tamanho = " << NosCoord.size() << endl;
			NoPlantaAux = rand() % NosCoord.size() ;
			NoPlanta[p].NumeroNo = NosCoord[NoPlantaAux].NumeroNo;
			NoPlanta[p].CoordenadaX = NosCoord[NoPlantaAux].CoordenadaX;
			NoPlanta[p].CoordenadaY = NosCoord[NoPlantaAux].CoordenadaY;
			NosCoord.erase(NosCoord.begin() + NoPlantaAux);
			HoraInicioPlanta[p] = HorarioInicioPlanta;
			HoraFinalPlanta[p]  = HorarioFinalPlanta;
		}

		NoCliente.resize(	NumeroClientes	+	1);
		HoraInicioCliente.resize(	NumeroClientes	+	1);
		HoraFinalCliente.resize( 	NumeroClientes	+	1);


		NumeroCarretas.resize( NumeroClientes + 1 ); // vetor que guarda o numero de carretas por cliente

		cout << " +++++++++++ [ C ]  Plantas (" << NumeroPlantas << ")    Construcoes (" << NumeroClientes << ") ++++++++++++++++++" << endl;


		// define o no que ira representar a construção, o númeor de carretas e o intervalo de atendiemnto
		for( int i = 1; i <= NumeroClientes; i++){
			//cout << "    construção " << i << " tamanho = " << NosCoord.size() << endl;

			NoConstrucaoAux = rand() % NosCoord.size();
			NoCliente[i].NumeroNo = NosCoord[NoConstrucaoAux].NumeroNo;
			NoCliente[i].CoordenadaX = NosCoord[NoConstrucaoAux].CoordenadaX;
			NoCliente[i].CoordenadaY = NosCoord[NoConstrucaoAux].CoordenadaY;
			NosCoord.erase(NosCoord.begin() + NoConstrucaoAux);


			NumeroCarretas[i] = rand()%(NumeroMaxCarretas) + 1;	// fornece o numero de demandas da conrução

			if(rand()%2 == 1){
				HoraInicioCliente[i] = HorarioMinimoConstrucao + ( rand() % (int)( (HorarioMinimoConstrucao-InicioAlmoco)/ InicioMinAtendimento )  ) *InicioMinAtendimento;
				HoraFinalCliente[i] = HoraInicioCliente[i] + NumeroCarretas[i]*TempoCarreta -  TempoDeDescarga;

				while( HoraFinalCliente[i] + TempoDeDescarga > InicioAlmoco ){
					HoraInicioCliente[i] = HorarioMinimoConstrucao + ( rand() % (int)( (HorarioMinimoConstrucao-InicioAlmoco)/ InicioMinAtendimento) ) *InicioMinAtendimento;
					HoraFinalCliente[i] = HoraInicioCliente[i] + NumeroCarretas[i]*TempoCarreta -  TempoDeDescarga;
				}
			}else{
				HoraInicioCliente[i] = FinalAlmoco + ( rand() % (int)( (FinalAlmoco-HorarioMaximoConstrucao)/ InicioMinAtendimento) ) *InicioMinAtendimento;
				HoraFinalCliente[i] = HoraInicioCliente[i] + NumeroCarretas[i]*TempoCarreta  -  TempoDeDescarga;

				while( HoraFinalCliente[i] + TempoDeDescarga > HorarioMaximoConstrucao ){
					HoraInicioCliente[i] = HorarioMinimoConstrucao + ( rand() % (int)( (FinalAlmoco-HorarioMaximoConstrucao)/ InicioMinAtendimento) ) *InicioMinAtendimento;
					HoraFinalCliente[i] = HoraInicioCliente[i] + NumeroCarretas[i]*TempoCarreta -  TempoDeDescarga;
				}
			}
		}

		NumeroCaminhoes = 0;
		for( int p = 0; p < NumeroPlantas; p++){
			NumeroCaminhoes = NumeroCaminhoes + NumeroCaminhoesPorPlanta;
		}

		CaminhoesPlanta.resize(NumeroPlantas + 1);
		for( int p = 1; p <= NumeroPlantas; p++){
			CaminhoesPlanta[p] = NumeroCaminhoesPorPlanta;
		}

		InstanciaSolomon << NumeroPlantas 		<< endl; 	// NUmero de plantas que serão nos Nós N4 ,N15 e o N22
		InstanciaSolomon << NumeroClientes 		<< endl;	// Numero de construções (clientes) , tirei o no N0 e dos 25 restantes eu tirei os 3 das plantas
		InstanciaSolomon << NumeroCaminhoes 	<< endl;	// Coloquei 20 caminhões paracada planta (pode mudar depois.
		InstanciaSolomon << Velocidade 			<< endl;	// Velocidade dos caminhões
		InstanciaSolomon << TempoDeVidaConcreto << endl;	// Tempo de vida do concreto

		// Preenche o numero veiculos por planta

		CaminhaoAux = 1;
		for( int p = 1; p <= NumeroPlantas; p++){
			InstanciaSolomon << CaminhoesPlanta[p];
			for( int i = 1; i <= CaminhoesPlanta[p]; i++){
				InstanciaSolomon << " " << CaminhaoAux;
				CaminhaoAux++;
			}
			InstanciaSolomon << endl;
		}
		// InstanciaSolomon << " Veiculo planta " << endl;

		// Preenche o numero de demandas por entrada

		for(int c =1; c <= NumeroClientes; c++){
			//InstanciaSolomon << " No" << i << " ";
			InstanciaSolomon << NumeroCarretas[c] ;
			for( int i= 1; i <= NumeroCarretas[c] ; i++){
				InstanciaSolomon << " " << i;
			}
			InstanciaSolomon << endl;
		}

		// Preenche as os tempos entre  plantas e entradas

		for(int p =1; p <= NumeroPlantas; p++){
			for(int i =1; i <= NumeroClientes; i++){
				InstanciaSolomon << (long int) ( sqrt( pow( NoPlanta[p].CoordenadaX - NoCliente[i].CoordenadaX,2) + pow( NoPlanta[p].CoordenadaY - NoCliente[i].CoordenadaY,2) ) / Velocidade ) << " ";
			}
			InstanciaSolomon << endl;
		}

		//InstanciaSolomon << " localidade plantas "<< endl;

		// Preenche as os tempos entre entradas e plantas
		for(int i =1; i <= NumeroClientes; i++){
			for(int p =1; p <= NumeroPlantas; p++){
				InstanciaSolomon << (long int) ( sqrt( pow( NoPlanta[p].CoordenadaX - NoCliente[i].CoordenadaX ,2) + pow( NoPlanta[p].CoordenadaY - NoCliente[i].CoordenadaY ,2) ) / Velocidade ) << " ";
			}
			InstanciaSolomon << endl;
		}

		// Tempo descarga
		for( int v = 1; v <= NumeroCaminhoes; v++){
			InstanciaSolomon << v << endl;
			for( int c = 1; c <= NumeroClientes; c++){
				InstanciaSolomon << NumeroCarretas[c];
				for( int i = 1; i <= NumeroCarretas[c]; i++){
					InstanciaSolomon << " " << TempoDeDescarga;
				}
				InstanciaSolomon << endl;

			}
		}

		// Tempo Carregamento

		for( int p = 1; p <= NumeroPlantas; p++){
			InstanciaSolomon << TempoPlanta << " ";
		}
		InstanciaSolomon << endl;

		// Tempo entre entregas
		for( int c = 1; c <= NumeroClientes; c++){
			InstanciaSolomon << TemproEntreEntregas << " ";
		}
		InstanciaSolomon << endl;

		// Declara o intervalo estipulado pelos clientes
		for( int c = 1; c <= NumeroClientes; c++){
			InstanciaSolomon << HoraInicioCliente[c] << " ";
		}
		InstanciaSolomon << endl;

		for( int c = 1; c <= NumeroClientes; c++){
			InstanciaSolomon << HoraFinalCliente[c] << " ";
		}
		InstanciaSolomon << endl;

		// Declara o intervalo estipulado pelos plantas
		for( int p = 1; p <= NumeroPlantas; p++){
			InstanciaSolomon <<  HoraInicioPlanta[p] << " ";
		}
		InstanciaSolomon << endl;

		for( int p = 1; p <= NumeroPlantas; p++){
			InstanciaSolomon <<  HoraFinalPlanta[p]  << " ";
		}
		InstanciaSolomon << endl;

		// Armazena dados da instancia gerada
		DadosInstanciaSalomonCriada << " Gerador dos numeros aleatorios das demandas ( " << NumeroVERSAO << " ) " << endl;
		DadosInstanciaSalomonCriada << "Dados das plantas " << endl;
		for (int p = 1; p <= NumeroPlantas; p++){
			DadosInstanciaSalomonCriada <<  "   NoPlanta = " <<  p;
			DadosInstanciaSalomonCriada << " Horario [ "	<< HoraInicioPlanta[p] << " - "	<< HoraFinalPlanta[p] << " ]" << endl;
		}
		DadosInstanciaSalomonCriada << "Dados dos Clientes " << endl;
		for( int c = 1; c <= NumeroClientes; c++){
			DadosInstanciaSalomonCriada << "  NoCliente = " << c;
			DadosInstanciaSalomonCriada << " \tDemanda em carretas ( " << NumeroCarretas[c] << " ) ";
			DadosInstanciaSalomonCriada << "Horario [ "	<< HoraInicioCliente[c] << " - " << HoraFinalCliente[c] << " ]" << endl;
		}

		DadosInstanciaSalomonCriada << endl << endl<< "Tempo das plantas para construcoes  em minutos" << endl << endl;
		for (int p = 1; p <= NumeroPlantas; p++){
			DadosInstanciaSalomonCriada <<  "   Planta = " <<  p << endl;
			DadosInstanciaSalomonCriada << "Construcao   Tempo de Ida    Tempo de Ida e Volta" << endl;
			for( int c = 1; c <= NumeroClientes; c++){
				DadosInstanciaSalomonCriada << c << "\t\t" <<  (long int)  (sqrt( pow( NoPlanta[p].CoordenadaX - NoCliente[c].CoordenadaX ,2) + pow( NoPlanta[p].CoordenadaY - NoCliente[c].CoordenadaY,2) ) / Velocidade )  << "\t\t";
				DadosInstanciaSalomonCriada <<  (long int) ( sqrt( pow( NoPlanta[p].CoordenadaX - NoCliente[c].CoordenadaX ,2) + pow( NoPlanta[p].CoordenadaY - NoCliente[c].CoordenadaY,2) )  / Velocidade ) + TempoPlanta  +  (long int) (sqrt( pow( NoPlanta[p].CoordenadaX - NoCliente[c].CoordenadaX,2) + pow( NoPlanta[p].CoordenadaY - NoCliente[c].CoordenadaY,2) ) / Velocidade) << endl;
			}
		}
	}else{
		InstanciaSolomon << " Nao se enquadra! " << endl;
	}

	DadosInstanciaSalomonCriada.close();
	InstanciaSolomon.close();
}

void 	DadosSolomon::EscreverComandosR(string Nome, char TipoArquivoSaida){

	//int LimiteplotarX;
	//int LimiteplotarY;

	//LimiteplotarX = 45;
	//LimiteplotarY = 90;

	double 	PosicaoTextoX;
	double 	PosicaoTextoY;
	int 	TamanhoLetraLegenda;

	PosicaoTextoX = 0.5;
	PosicaoTextoY = 2;
	TamanhoLetraLegenda = 2;

	string TipoComando;
	string NomeArquivoComandoR;
	TipoComando = "./ComR/CmdR-";
	TipoComando += NomeAux;

	DIR* dp1;
	DIR* dp2;

	dp1 = opendir ("ComR");

	if(!dp1){
		cout <<  "\n Nao tem diretorio \"ComR\"!!            FUDEU MUITO!! \n" << endl;

		if(system("mkdir ComR;") == 0){
			cout << " Criou pasta ComR" << endl;
		}else{
			cout << " Problema ao criar pasta ComR" << endl;
		}

		// Outra maneira de criar arquivos
		// SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		dp1 = opendir ("ComR");

		if(!dp1){
			cout << "\n Nao tem diretorio \"ComR\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"ComR\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"ComR\" !!  " << endl;
	}

	closedir( dp1 );

	cout << endl <<  " Arquivo do comando R = " <<   TipoComando << endl << endl;

	ComandosR.open(TipoComando.c_str());

	ComandosR << "require(ggplot2) "<< endl;

	ComandosR << "Dados <- data.frame(nomes = c(" ;

	for( int c = 1; c <= NumeroClientes; c++){
		if( c != 1){
			ComandosR << ",";
		}
		ComandosR << "\"C" <<  c << "(" <<  NumeroCarretas[c] << ")"<<  "\"";
	}

	for( int p = 1; p <= NumeroPlantas; p++){
		ComandosR << ","<< "\"P" <<  p <<  "\"";
	}
	ComandosR << ")" << endl;

	//cout << " Aqui 1 " << endl;

	ComandosR << ", x <- c(" ;
	for( int c = 1; c <= NumeroClientes; c++){
		if( c != 1) {
			ComandosR << ",";
		}
		ComandosR <<  NoCliente[c].CoordenadaX ;
	}
	for( int p = 1; p <= NumeroPlantas; p++){
		ComandosR << ","<<  NoPlanta[p].CoordenadaX;
	}
	ComandosR << ")" << endl;

	ComandosR << ", y <- c(" ;
	for( int c = 1; c <= NumeroClientes; c++){
		if( c != 1) {
			ComandosR << ",";
		}
		ComandosR <<  NoCliente[c].CoordenadaY ;
	}
	for( int p = 1; p <= NumeroPlantas; p++){
		ComandosR << ","<<  NoPlanta[p].CoordenadaY ;
	}
	ComandosR << ")" << endl;

	ComandosR << ", tipo <- c(" ;
	for( int c = 1; c <= NumeroClientes; c++){
		if(c != 1 ){
			ComandosR << ",";
		}
		ComandosR << "3";
	}
	for( int p = 1; p <= NumeroPlantas; p++){
			ComandosR << ",4" ;
	}
	ComandosR << ")" << endl;

	ComandosR << ", tamanho <- c(" ;
	for( int c = 1; c <= NumeroClientes; c++){
		if(c != 1 ){
			ComandosR << ",";
		}
			ComandosR << "1" ;
	}
	for( int p = 1; p <= NumeroPlantas; p++){
		ComandosR << ",2" ;
	}
	ComandosR << ")" << endl << ")"<< endl;

	dp2 = opendir ("Imagens");

	if(!dp2){
		cout <<  "\n Nao tem diretorio Imagens!!          FUDEU MUITO!! \n" << endl;

		if(system("mkdir Imagens;") == 0){
			cout << " Criou pasta Imagens" << endl;
		}else{
			cout << " Problema ao criar pasta Imagens" << endl;
		}

		// Outra maneira de criar arquivos
		//SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		dp2 = opendir ("Imagens");

		if(!dp2){
			cout << "\n Nao tem diretorio \"Imagens\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Imagens\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"Imagens\" !!  " << endl;
	}

	closedir( dp2 );

	//NomeArquivoComandoR = "./Imagens/";
	NomeArquivoComandoR += NomeAux;

	NomeArquivoComandoR.resize( NomeArquivoComandoR.size() - 4 );

// Cria Post Script
	if (TipoArquivoSaida == '1'){
		NomeArquivoComandoR += ".ps";

		ComandosR << "postscript('" << NomeArquivoComandoR << "')" << endl;
	}

// Criar PNG
	if (TipoArquivoSaida == '2'){

		NomeArquivoComandoR += ".png";
		ComandosR << "png('" << NomeArquivoComandoR << "')" << endl;
	}

// Criar Jpeg
	if (TipoArquivoSaida == '3'){

		NomeArquivoComandoR += ".jpg";
		ComandosR << "jpeg('" << NomeArquivoComandoR << "')" << endl;
	}

 // Criar PDF
	if (TipoArquivoSaida == '4'){

		NomeArquivoComandoR += ".pdf";
		ComandosR << "pdf('" << NomeArquivoComandoR << "')" << endl;
	}

	ComandosR << "ggplot(Dados, aes(x,y)) + geom_point(aes(shape = factor(tipo),size =tamanho) ) + scale_size_continuous(range = c(3,4))";
	ComandosR << "+ scale_shape(solid = FALSE)+  geom_text(aes(label=nomes),";
	ComandosR << " hjust= " << PosicaoTextoX << ",vjust=" << PosicaoTextoY  ;
	ComandosR << " ,size = " << TamanhoLetraLegenda << ")";
	ComandosR << "+ xlim( min(x)- 10, max(x)+10 ) + ylim( min(y)-10,max(y)+10 )" << endl; //ComandosR << "+ xlim(0," << LimiteplotarX << ") + ylim(0," << LimiteplotarY << ")" << endl;
	ComandosR << "dev.off() ;" << endl;

	ComandosR.close();

	TipoComando.clear();
	NomeArquivoComandoR.clear();

	//cout << " Aqui 3" << endl;

}

void 	DadosSolomon::EscreverComandosExcel(string Nome){


	//char *b;
	//string TipoComando;
	//TipoComando = "CmdE-";

	//b = new char[TipoComando.size()+1];
	//b[TipoComando.size()]=0;
	//memcpy(b,TipoComando.c_str(),TipoComando.size());
	//strcat(b,a);

	//FILE *fp;
	//fp = fopen (b, "w");
	//if (fp == NULL) {
		//for( int i = 0; i <= NumeroNosDadosSolomon; i++){
			//printf ("N %d \t %f \t %f \n",i,Coordenadas[i][0],Coordenadas[i][1]);
			//fprintf (fp, "N %d \t %f \t %f \n",i,Coordenadas[i][0],Coordenadas[i][1]);
		//}
	//}
	//fclose (fp);

	string 	TipoComando;
	TipoComando = "./ComE/CmdE-";
	TipoComando += Nome;

	DIR* dp1;

	dp1 = opendir ("ComE");

	if(!dp1){
		cout <<  "\n Nao tem diretorio \"ComE\"!!            FUDEU MUITO!! \n" << endl;

		if(system("mkdir ComE") == 0){
			cout << " Criou pasta ComE" << endl;
		}else{
			cout << " Problema ao criar pasta ComE" << endl;
		}

		// Outra maneira de criar arquivos
		//SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

		dp1 = opendir ("ComE");

		if(!dp1){
			cout << "\n Nao tem diretorio \"ComE\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"ComE\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"ComE\" !!  " << endl;
	}

	closedir( dp1 );

	//cout << " galo => " << b << endl << endl;

	ComandosExcel.open(TipoComando.c_str());

	//cout << " Doido " << endl << endl;

	for(int p = 1; p <= NumeroPlantas; p++){
        ComandosExcel << "P" <<  NoPlanta[p].NumeroNo  << "\t" << NoPlanta[p].CoordenadaX << "\t" << NoPlanta[p].CoordenadaY << endl ;
    }

	for( int i = 1; i <= NumeroClientes; i++){
		ComandosExcel << "C" <<	NoCliente[i].NumeroNo   << "\t" <<  NoCliente[i].CoordenadaX   << "\t" << NoCliente[i].CoordenadaY << endl;
	}

    ComandosExcel.close();
}

DadosSolomon::~DadosSolomon(){

    NomeInstancia.clear();
    Auxiliar.clear();
    NosCoord.clear();
    Demanda.clear();
    JanelaDeTempo.clear();
    TempoDeServico.clear();
    NoPlanta.clear();
    NoCliente.clear();
    CaminhoesPlanta.clear();
    NumeroCarretas.clear();		// guarda o numero de clientes
    HoraInicioPlanta.clear();
    HoraFinalPlanta.clear();
    HoraInicioCliente.clear();
    HoraFinalCliente.clear();
}

#endif /* DADOSSOLOMON_HPP_ */

