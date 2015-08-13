/*
 * DadosSolomon.hpp
 *
 *  Created on: 19/05/2015
 *      Author: mvus
 */

#ifndef DADOSSOLOMON_HPP_
#define DADOSSOLOMON_HPP_

#include "Bibliotecas.hpp"



class DadosSolomon{

public:
    DadosSolomon();

// Variaveis de leitura do arquivo

    //int X;					// Não sei para que serve mais
	string NomeInstancia;
	string Auxiliar;
	int NumeroVeiculos;
	int Capacidade;

	int NumeroNosDadosSolomon;

	vector< int > NumeroDoNo;
	vector< vector< int > > Coordenadas;
	vector< int > Demanda;
	vector< vector< int > > JanelaDeTempo;
	vector< int > TempoDeServico;
	int x;
	int y;
	int AuxiliarInt;

// Variaveis de escrita dos arquivos de saida

	int NumeroPlantas;
	vector < int > NoPlanta;
	int NumeroClientes;
	vector < int > NoCliente;
	int NumeroCaminhoes;
	int Velocidade;

// Declara variaveis

	char *b;
	char *aux1;
	string CaminhoArquivo1;
	string CaminhoArquivo2;
	string Nome;
	string NomeAux;
	string Versao;
	string Dados;
	string TXT;
	int NumeroVERSAO;

	int CaminhaoAux;

	vector < int > CaminhoesPlanta;
	vector < int > NumeroCarretas;		// guarda o numero de clientes

	double TempoDeDescarga;
	double TemproEntreEntregas;
	double TempoPlanta;
	double TempoDeVidaConcreto;
	double TempoEntreEntregas;

	vector < double > HoraInicioPlanta;
	vector < double > HoraFinalPlanta;

	vector < double > HoraInicioCliente;
	vector < double > HoraFinalCliente;


// Funções

	void CarregarNumeroNosCoordenadas( char*);

	void EscreverDadosLidosInstanciaSolomon();

	ifstream Instancia;

	void EscreverComandosR(char*,char );

	ofstream ComandosR;

	void EscreverComandosExcel(char*);

	ofstream ComandosExcel;

	void CriaPastaInstS();
	void CriaPastaDat();

	void CriarInstanciaSolomon(char*);

	ofstream InstanciaSolomon;
	ofstream DadosInstanciaSalomonCriada;

    ~DadosSolomon();

};

DadosSolomon::DadosSolomon(){
	AuxiliarInt = 13131313;
	Capacidade  = 13131313;
	NumeroNosDadosSolomon = 13131313;
	NumeroVeiculos = 13131313;
	x = 13131313;
	y = 13131313;

}

void DadosSolomon::CarregarNumeroNosCoordenadas( char* a){

	int EscreveDadosLidos = 0;

	Instancia.open(a);

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
		cout << NumeroVeiculos ;
	}
	NumeroNosDadosSolomon = NumeroVeiculos;
	if( EscreveDadosLidos == 1){
		cout << "    (" << NumeroNosDadosSolomon << ")   ";
	}

	Instancia >> Capacidade;
	if( EscreveDadosLidos == 1){
		cout << Capacidade << endl;
	}

// Inicializa estrutura ds dados

	NumeroDoNo.resize( NumeroNosDadosSolomon + 1 );

	Coordenadas.resize( NumeroNosDadosSolomon + 1 );
    for( int i = 0; i <= NumeroNosDadosSolomon + 1; i++){
            Coordenadas[i].resize(2);

    }
    Demanda.resize( NumeroNosDadosSolomon + 1 );

    JanelaDeTempo.resize( NumeroNosDadosSolomon + 1 );
    for( int i = 0; i <= NumeroNosDadosSolomon + 1; i++){
    	JanelaDeTempo[i].resize(2);

	}
    TempoDeServico.resize( NumeroNosDadosSolomon + 1 );

// Guarda os dados a serem lidos

    for( int i = 0; i<12; i++){
        Instancia >>Auxiliar;
        if( EscreveDadosLidos == 1){
        	cout << Auxiliar << "\t";
        }
    }
    if( EscreveDadosLidos == 1){
    	cout << endl;
    }



    for( int i = 0; i <= NumeroNosDadosSolomon; i++){
        Instancia >> NumeroDoNo[i];

        Instancia >> Coordenadas[i][0];
        Instancia >> Coordenadas[i][1];

        Instancia >>Demanda[i];

        Instancia >> JanelaDeTempo[i][0];
        Instancia >> JanelaDeTempo[i][1];

        Instancia >>TempoDeServico[i];

        if( EscreveDadosLidos == 1){
            cout << NumeroDoNo[i] << "\t\t\t\t";
            cout << Coordenadas[i][0] << "\t";
            cout << Coordenadas[i][1] << "\t";
            cout << Demanda[i] << "\t\t";
            cout << JanelaDeTempo[i][0] << "\t";
            cout << JanelaDeTempo[i][1] << "\t\t\t";
            cout << TempoDeServico[i] << "\t\t" << endl;
        }


    }

    //cout << endl << endl << " DadosSolomon " << endl << endl;

    Instancia.close();


}

void DadosSolomon::EscreverDadosLidosInstanciaSolomon(){
	cout << endl << endl;

	cout << "Nome: " << NomeInstancia << endl;
	cout << "Numero de Veiculos: " << NumeroVeiculos<< endl;
	cout << "Capacidade: " << Capacidade << endl << endl;

	cout << " Numero No \t Coordenada X \t Coordenada Y \t Demanda \t InicioJanela \t FimJanela \t TempoServico"<< endl;
    for( int i = 0; i<=NumeroNosDadosSolomon; i++){
        cout << "\t " << NumeroDoNo[i] << "\t\t" << Coordenadas[i][0]  << "\t\t" << Coordenadas[i][1] << "\t\t" << Demanda[i] << "\t\t";
        cout << JanelaDeTempo[i][0]  << "\t\t" << JanelaDeTempo[i][1]  << "\t\t" << TempoDeServico[i] << endl;
    }

    cout << endl << endl;

}

void DadosSolomon::EscreverComandosR(char* a, char TipoArquivoSaida){

	//int LimiteplotarX;
	//int LimiteplotarY;

	//LimiteplotarX = 45;
	//LimiteplotarY = 90;

	double PosicaoTextoX;
	double PosicaoTextoY;
	int TamanhoLetraLegenda;

	PosicaoTextoX = 0.5;
	PosicaoTextoY = 2;
	TamanhoLetraLegenda = 2;

	char *b;
	string TipoComando;
	string NomeArquivoComandoR;
	TipoComando = "./ComR/CmdR-";


	if(!opendir ("ComR")){
		cout <<  "\n Nao tem diretorio \"ComR\"!!            FUDEU MUITO!! \n" << endl;

		if(system("mkdir ComR;") == 0){
			cout << " Criou pasta ComR" << endl;
		}else{
			cout << " Problema ao criar pasta ComR" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		if(!opendir ("ComR")){
			cout << "\n Nao tem diretorio \"ComR\"!!             FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"ComR\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"ComR\" !!  " << endl;
	}


		b = new char[TipoComando.size()+1];
		b[TipoComando.size()]=0;
		memcpy(b,TipoComando.c_str(),TipoComando.size());
		strcat(b,a);

		cout << endl <<  " Arquivo do comando R = " <<   b << endl << endl;

		ComandosR.open(b);

		ComandosR << "require(ggplot2) "<< endl;


		ComandosR << "Dados <- data.frame(nomes = c(" ;
		ComandosR << "\"N" << "0" << "\"";
		for( int c = 1; c <= NumeroClientes; c++){
			ComandosR << "," << "\"C" <<  c << "(" <<  NumeroCarretas[c] << ")"<<  "\"";
		}
		for( int p = 1; p <= NumeroPlantas; p++){
			ComandosR << ","<< "\"P" <<  p <<  "\"";
		}
		ComandosR << ")" << endl;

		//cout << " Aqui 1 " << endl;

		ComandosR << ", x <- c(" ;
		ComandosR << Coordenadas[0][0] ;
		for( int c = 1; c <= NumeroClientes; c++){
			ComandosR << ","<<  Coordenadas[	NoCliente[c] ][0] ;
		}
		for( int p = 1; p <= NumeroPlantas; p++){
			ComandosR << ","<<  Coordenadas[ NoPlanta[p] ][0] ;
		}
		ComandosR << ")" << endl;

		ComandosR << ", y <- c(" ;
		ComandosR << Coordenadas[0][1] ;
		for( int c = 1; c <= NumeroClientes; c++){
			ComandosR << ","<<  Coordenadas[	NoCliente[c] ][1] ;
		}
		for( int p = 1; p <= NumeroPlantas; p++){
			ComandosR << ","<<  Coordenadas[ NoPlanta[p] ][1] ;
		}
		ComandosR << ")" << endl;

		ComandosR << ", tipo <- c(" ;
		ComandosR << "3" ;
		for( int c = 1; c <= NumeroClientes; c++){
				ComandosR << ",6" ;
		}
		for( int p = 1; p <= NumeroPlantas; p++){
				ComandosR << ",4" ;
		}
		ComandosR << ")" << endl;

		ComandosR << ", tamanho <- c(" ;
		ComandosR << "1" ;
		for( int c = 1; c <= NumeroClientes; c++){
				ComandosR << ",1" ;
		}
		for( int p = 1; p <= NumeroPlantas; p++){
			ComandosR << ",2" ;
		}
		ComandosR << ")" << endl << ")"<< endl;


		if(!opendir ("Imagens")){
				cout <<  "\n Nao tem diretorio Imagens!!           FUDEU MUITO!! \n" << endl;

				if( system("mkdir Imagens;") == 0){
					cout << " Criou pasta Imagens " << endl;
				}else{
					cout << " Problema ao criar pasta Imagens " << endl;
				}
		}

		//NomeArquivoComandoR = "./Imagens/";
		NomeArquivoComandoR += a;

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

		//cout << " Aqui 3" << endl;

}

void DadosSolomon::EscreverComandosExcel(char* a){

	/*
	char *b;
	string TipoComando;
	TipoComando = "CmdE-";

	b = new char[TipoComando.size()+1];
	b[TipoComando.size()]=0;
	memcpy(b,TipoComando.c_str(),TipoComando.size());
	strcat(b,a);

	FILE *fp;
	fp = fopen (b, "w");
	if (fp == NULL) {
		for( int i = 0; i <= NumeroNosDadosSolomon; i++){
			printf ("N %d \t %f \t %f \n",i,Coordenadas[i][0],Coordenadas[i][1]);
			fprintf (fp, "N %d \t %f \t %f \n",i,Coordenadas[i][0],Coordenadas[i][1]);
		}
	}
	fclose (fp);


	*/

	char *b;
	string TipoComando;
	TipoComando = "./ComE/CmdE-";




	if(!opendir ("ComE")){
		cout <<  "\n Nao tem diretorio \"ComE\"!!         FUDEU MUITO!! \n" << endl;

		if(system("mkdir ComE;") == 0){
			cout << " Criou pasta ComE" << endl;
		}else{
			cout << " Problema ao criar pasta ComE" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		if(!opendir ("ComE")){
			cout << "\n Nao tem diretorio \"ComE\"!!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"ComE\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"ComE\" !!  " << endl;
	}

	b = new char[TipoComando.size()+1];
	b[TipoComando.size()]=0;
	memcpy(b,TipoComando.c_str(),TipoComando.size());
	strcat(b,a);

	//cout << " galo => " << b << endl << endl;

	ComandosExcel.open(b);

	//cout << " Doido " << endl << endl;



    for( int i = 0; i <= NumeroNosDadosSolomon; i++){
        ComandosExcel << "N" <<  i  << "\t" << Coordenadas[i][0] << "\t" << Coordenadas[i][1] << endl ;
    }

    ComandosExcel.close();


}

void DadosSolomon::CriaPastaInstS(){
	if(!opendir ("InstS")){
		cout <<  "\n\n Nao tem diretorio \"InstS\" !!        FUDEU MUITO!! \n" << endl;

		if(system("mkdir InstS;") == 0){
			cout << " Criou pasta InstS" << endl;
		}else{
			cout << " Problema ao criar pasta InstS" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		if(!opendir ("InstS")){
			cout << "\n Nao tem diretorio  \"InstS\" !!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"InstS\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"InstS\" !!  " << endl;
	}
}

void DadosSolomon::CriaPastaDat(){
	if(!opendir ("Dat")){
		cout <<  "\n\n Nao tem diretorio \"Dat\" !!        FUDEU MUITO!! \n" << endl;

		if(system("mkdir Dat;") == 0){
			cout << " Criou pasta Dat" << endl;
		}else{
			cout << " Problema ao criar pasta Dat" << endl;
		}

		/* Outra maneira de criar arquivos

		SituacaoDiretorio = mkdir("./myfolder", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
		*/

		if(!opendir ("Dat")){
			cout << "\n Nao tem diretorio  \"Dat\" !!        FUDEU MUITO!! \n" << endl;
		}else{
			cout << " Tem diretorio \"Dat\" !!  " << endl;
		}
	}else{
		cout << " Tem diretorio \"Dat\" !!  " << endl;
	}
}

void DadosSolomon::CriarInstanciaSolomon(char* a){


	NumeroVERSAO = 49;
	//NumeroVERSAO = 50;
	//NumeroVERSAO = 51;

	TempoDeDescarga = 0.1666667; // equivaelente a 10 minutos
	TemproEntreEntregas = 0.1666667; // equivaelente a 10 minutos
	TempoPlanta = 0.083333333; // equivalente a 5 minutos(4 min = 0.066667 ; 3min = 0.05 e 2min = 0.0333333)
	TempoDeVidaConcreto = 1.5;

	//binomial_distribution<int> distribution(5,0.5); 		// gera numeros segundo a distribuição binomial

// Cria diretorio caso não exista
	CriaPastaInstS();

// Cria o nome da instancia para o modelo

	Nome.assign(a);
	if( Nome.size() > 3){
		Nome.resize(Nome.size()-4);
		if( NomeInstancia[0] == 'R' || NomeInstancia[0] == 'C'){
			if(NomeInstancia[1] != 'C'){
				if(NomeInstancia[1] == '1'){
					Versao = "-V";
				}else{
					if(NomeInstancia[1] == '2'){
						Versao = "-W";
					}else{
						cout << endl << endl <<  " Arquivo inconforme com as possiveis entradas" << endl << endl;
					}
				}
			}else{
				if(NomeInstancia[0] == 'R' && NomeInstancia[1] == 'C'){
					if(NomeInstancia[2] == '1'){
						Versao = "-V";
					}else{
						if(NomeInstancia[2] == '2'){
							Versao = "-W";
						}else{
							cout << endl << endl <<  " Arquivo inconforme com as possiveis entradas" << endl << endl;
						}
					}
				}
			}
        }else{
            if( NomeInstancia[0] == 'r' && NomeInstancia[1] == '-' && NomeInstancia[2] == 'C'){
                Versao = "-V";
            }else{
                if( NomeInstancia[0] == 'r' && NomeInstancia[1] == '-' && NomeInstancia[2] == 'R'){
                    Versao = "-V";
                }else{
                cout << endl << endl << "  Tipo de instancia nao reconhecida " << endl << endl;
                }
            }
        }
		Versao += NumeroVERSAO;
		Nome.insert(Nome.size(),Versao);
		NomeAux = Nome;
		TXT = ".txt";
		Nome.insert(Nome.size(),TXT);

		cout << "      Nome da Instancia Solomon = " << Nome << endl << endl;

		a = new char[Nome.size()+1];
		a[Nome.size()]=0;
		memcpy(a,Nome.c_str(),Nome.size());

	}else{
		cout << "Arquivo passado com tamanho invaldo " <<  Nome << endl ;
	}

	//cout <<  "  Nome = " << Nome << endl;

	//CaminhoArquivo1 = "./";
	CaminhoArquivo1 = "./InstS/";

	b = new char[CaminhoArquivo1.size()+1];
	b[CaminhoArquivo1.size()]=0;
	memcpy(b,CaminhoArquivo1.c_str(),CaminhoArquivo1.size());
	strcat(b,a);

	cout << endl << "  Arquivo = " << a << "  Caminho = " << b << endl;

// Cria arquivo para guardar os dados da instancia criada

	if( NomeInstancia[0] == 'R' || NomeInstancia[0] == 'C' || NomeInstancia[0] == 'r'){
        InstanciaSolomon.open(b);

        CriaPastaDat();

        CaminhoArquivo2 = "./Dat/";

        aux1 = new char[CaminhoArquivo2.size()+1];
        aux1[CaminhoArquivo2.size()]=0;
        memcpy(aux1,CaminhoArquivo2.c_str(),CaminhoArquivo2.size());
        strcat(aux1,a);
        DadosInstanciaSalomonCriada.open(aux1);

        cout << endl << "  Caminho salvar em pasta Dat = " << aux1 << endl;

        DadosInstanciaSalomonCriada << b << endl;
        InstanciaSolomon << NomeInstancia << endl;

        if(NomeInstancia[0] == 'R' && NomeInstancia[1] == 'C'){

    //Inicializa Parametros

    cout << endl << endl << endl << " Nao devia ter entrado para escrever dados da Instancia RC" << endl << endl << endl;

            NumeroPlantas 	= 1;

            NoPlanta.resize(NumeroPlantas + 1);
            HoraInicioPlanta.resize(NumeroPlantas + 1);
            HoraFinalPlanta.resize(NumeroPlantas + 1);


            NoPlanta[1] = 4;	HoraInicioPlanta[1] = 7; 	HoraFinalPlanta[1] = 18;
            //NoPlanta[2] = 11;	HoraInicioPlanta[2] = 7; 	HoraFinalPlanta[2] = 18;
            //NoPlanta[3] = 19;	HoraInicioPlanta[3] = 7; 	HoraFinalPlanta[3] = 18;

            NumeroClientes 	= 9;
            NoCliente.resize(	NumeroClientes	+	1);
            HoraInicioCliente.resize(	NumeroClientes	+	1);
            HoraFinalCliente.resize( 	NumeroClientes	+	1);
            NumeroCarretas.resize( NumeroClientes + 1 ); // vetor que guarda o numero de carretas por cliente

        /*
        //dados com o gerador => NumeroVERSAO = 49;


        //dados com o gerador => NumeroVERSAO = 50;


        //dados com o gerador => NumeroVERSAO = 51;


        */
            NumeroCaminhoes = 10;

            CaminhoesPlanta.resize(NumeroPlantas + 1);
            CaminhoesPlanta[1] = 10;
            //CaminhoesPlanta[2] = 10;
            //CaminhoesPlanta[3] = 10;

            Velocidade 		= 30;

        }else{
            if( NomeInstancia[0] == 'R' ){
                //Inicializa Parametros

                cout << endl << endl << endl << " Nao devia ter entrado para escrever dados da Instancia R ####################################################################################################" << endl << endl << endl;

                NumeroPlantas 	= 3;

                NoPlanta.resize(NumeroPlantas + 1);
                HoraInicioPlanta.resize(NumeroPlantas + 1);
                HoraFinalPlanta.resize(NumeroPlantas + 1);

                //NoPlanta[1] = 1;	HoraInicioPlanta[1] = 7; 	HoraFinalPlanta[1] = 18;
                //NoPlanta[2] = 5;	HoraInicioPlanta[2] = 7; 	HoraFinalPlanta[2] = 18;
                //NoPlanta[3] = 4;	HoraInicioPlanta[3] = 7; 	HoraFinalPlanta[3] = 18;



                NumeroClientes 	= 15;
                NoCliente.resize(	NumeroClientes	+	1);
                HoraInicioCliente.resize(	NumeroClientes	+	1);
                HoraFinalCliente.resize( 	NumeroClientes	+	1);
                NumeroCarretas.resize( NumeroClientes + 1 ); // vetor que guarda o numero de carretas por cliente

                cout << " +++++++++++  [ R ]  Plantas (" << NumeroPlantas << ")    Construcoes (" << NumeroClientes << ") ++++++++++++++++++" << endl;

         //dados com o gerador => NumeroVERSAO = 49;			************************************ Realizado *******************************************************
                /*      NoCliente[1] = 3;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 8.5;			NumeroCarretas[1] = 3;
				NoCliente[2] = 7;		HoraInicioCliente[2] = 8.5;	 	HoraFinalCliente[2] = 9.5;		    NumeroCarretas[2] = 5;
				NoCliente[3] = 8;		HoraInicioCliente[3] = 9;	 	HoraFinalCliente[3] = 10.5;			NumeroCarretas[3] = 4;
				NoCliente[4] = 9;		HoraInicioCliente[4] = 9.5;	 	HoraFinalCliente[4] = 11;	    	NumeroCarretas[4] = 2;
				NoCliente[5] = 10;		HoraInicioCliente[5] = 10;	 	HoraFinalCliente[5] = 11.5;			NumeroCarretas[5] = 4;
				NoCliente[6] = 11;		HoraInicioCliente[6] = 11;	 	HoraFinalCliente[6] = 12;	    	NumeroCarretas[6] = 1;
				NoCliente[7] = 18;		HoraInicioCliente[7] = 11.5;	HoraFinalCliente[7] = 12.5;			NumeroCarretas[7] = 1;
				NoCliente[8] = 19;		HoraInicioCliente[8] = 12.5; 	HoraFinalCliente[8] = 14;        	NumeroCarretas[8] = 2;
				NoCliente[9] = 20;		HoraInicioCliente[9] = 13; 	 	HoraFinalCliente[9] = 14.5;			NumeroCarretas[9] = 5;

                NoCliente[10] = 2;		HoraInicioCliente[10] = 8;	 	HoraFinalCliente[10] = 9;			NumeroCarretas[10] = 4;
				NoCliente[11] = 13;	 	HoraInicioCliente[11] = 8.5;	HoraFinalCliente[11] = 9;			NumeroCarretas[11] = 3;
				NoCliente[12] = 6;		HoraInicioCliente[12] = 8.5; 	HoraFinalCliente[12] = 10;			NumeroCarretas[12] = 2;
				NoCliente[13] = 14;		HoraInicioCliente[13] = 9.5;	HoraFinalCliente[13] = 11.5;		NumeroCarretas[13] = 5;
				NoCliente[14] = 15;		HoraInicioCliente[14] = 10.5;	HoraFinalCliente[14] = 11.5;		NumeroCarretas[14] = 1;

               NoCliente[15] = 16;		HoraInicioCliente[15] = 11;	 	HoraFinalCliente[15] = 11.5;		NumeroCarretas[15] = 1;
               NoCliente[16] = 17;		HoraInicioCliente[16] = 10.5;	HoraFinalCliente[16] = 12;			NumeroCarretas[16] = 4;

                NoCliente[17] = 12;		HoraInicioCliente[17] = 8;	 	HoraFinalCliente[17] = 9;		    NumeroCarretas[17] = 3;
                NoCliente[18] = 21;		HoraInicioCliente[18] = 8.5;	HoraFinalCliente[18] = 9;			NumeroCarretas[18] = 1;
                NoCliente[19] = 22;		HoraInicioCliente[19] = 8.5; 	HoraFinalCliente[19] = 9.5;			NumeroCarretas[19] = 4;
                NoCliente[20] = 23;		HoraInicioCliente[20] = 9;	 	HoraFinalCliente[20] = 10.5;		NumeroCarretas[20] = 3;
                NoCliente[21] = 24;		HoraInicioCliente[21] = 9;	 	HoraFinalCliente[21] = 11;   		NumeroCarretas[21] = 4;
                NoCliente[22] = 25;		HoraInicioCliente[22] = 9.5;	HoraFinalCliente[22] = 11.5;		NumeroCarretas[22] = 4;
 */

        //dados com o gerador => NumeroVERSAO = 50;			************************************ Realizado ***********************************************************
                /*NoCliente[1] = 3;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 9;		    NumeroCarretas[1] = 3;
                NoCliente[2] = 7;		HoraInicioCliente[2] = 8.5;	 HoraFinalCliente[2] = 9;		    NumeroCarretas[2] = 1;
                NoCliente[3] = 8;		HoraInicioCliente[3] = 8.5;	 HoraFinalCliente[3] = 10;		    NumeroCarretas[3] = 4;
                NoCliente[4] = 9;		HoraInicioCliente[4] = 9;	 HoraFinalCliente[4] = 10;		    NumeroCarretas[4] = 1;
                NoCliente[5] = 10;		HoraInicioCliente[5] = 9.5;	 HoraFinalCliente[5] = 11.5;		NumeroCarretas[5] = 4;
                NoCliente[6] = 11;		HoraInicioCliente[6] = 10;	 HoraFinalCliente[6] = 12;	    	NumeroCarretas[6] = 4;
                NoCliente[7] = 18;		HoraInicioCliente[7] = 11;	 HoraFinalCliente[7] = 12.5;		NumeroCarretas[7] = 2;
                NoCliente[8] = 19;		HoraInicioCliente[8] = 12; HoraFinalCliente[8] = 14;        	NumeroCarretas[8] = 4;
                NoCliente[9] = 20;		HoraInicioCliente[9] = 12.5; 	 HoraFinalCliente[9] = 14.5;	NumeroCarretas[9] = 5;

                NoCliente[10] = 2;		HoraInicioCliente[10] = 8;	 HoraFinalCliente[10] = 9;		    NumeroCarretas[10] = 3;
                NoCliente[11] = 13; 	HoraInicioCliente[11] = 8.5;	 HoraFinalCliente[11] = 10;		NumeroCarretas[11] = 4;
                NoCliente[12] = 6;		HoraInicioCliente[12] = 9.5; 	HoraFinalCliente[12] = 11;		NumeroCarretas[12] = 4;
                NoCliente[13] = 14;		HoraInicioCliente[13] = 10;	 HoraFinalCliente[13] = 11;		    NumeroCarretas[13] = 1;
                NoCliente[14] = 15;		HoraInicioCliente[14] = 10;	 HoraFinalCliente[14] = 11.5;		NumeroCarretas[14] = 4;

                NoCliente[15] = 16;		HoraInicioCliente[15] = 10.5;	 HoraFinalCliente[15] = 12.5;		NumeroCarretas[15] = 5;
                NoCliente[16] = 17;		HoraInicioCliente[16] = 11;	 HoraFinalCliente[16] = 12;		NumeroCarretas[16] = 4;


                NoCliente[17] = 12;		HoraInicioCliente[17] = 8;	 	HoraFinalCliente[17] = 9;		    NumeroCarretas[17] = 4;
                NoCliente[18] = 21;		HoraInicioCliente[18] = 8.5;	HoraFinalCliente[18] = 10;			NumeroCarretas[18] = 5;
                NoCliente[19] = 22;		HoraInicioCliente[19] = 9; 		HoraFinalCliente[19] = 10.5;		NumeroCarretas[19] = 3;
                NoCliente[20] = 23;		HoraInicioCliente[20] = 9.5;	HoraFinalCliente[20] = 10.5;		NumeroCarretas[20] = 2;
                NoCliente[21] = 24;		HoraInicioCliente[21] = 10;		HoraFinalCliente[21] = 11;       	NumeroCarretas[21] = 2;
                NoCliente[22] = 25;		HoraInicioCliente[22] = 12.5;	HoraFinalCliente[22] = 14;			NumeroCarretas[22] = 2;
*/

        //dados com o gerador => NumeroVERSAO = 51;		************************************ Realizado ***********************************************************

                /*NoCliente[1] = 3;		HoraInicioCliente[1] = 8;	 	HoraFinalCliente[1] = 9;		NumeroCarretas[1] = 4;
                NoCliente[2] = 7;		HoraInicioCliente[2] = 8.5;	 	HoraFinalCliente[2] = 9.5;		NumeroCarretas[2] = 3;
                NoCliente[3] = 8;		HoraInicioCliente[3] = 8;	 	HoraFinalCliente[3] = 9.5;		NumeroCarretas[3] = 3;
                NoCliente[4] = 9;		HoraInicioCliente[4] = 9;	 	HoraFinalCliente[4] = 10.5;		NumeroCarretas[4] = 4;
                NoCliente[5] = 10;		HoraInicioCliente[5] = 9.5;	 	HoraFinalCliente[5] = 11.5;		NumeroCarretas[5] = 4;
                NoCliente[6] = 11;		HoraInicioCliente[6] = 11;	 	HoraFinalCliente[6] = 13;	    NumeroCarretas[6] = 5;
                NoCliente[7] = 18;		HoraInicioCliente[7] = 12.5;	HoraFinalCliente[7] = 14.5;		NumeroCarretas[7] = 4;
                NoCliente[8] = 19;		HoraInicioCliente[8] = 13; 		HoraFinalCliente[8] = 15;      	NumeroCarretas[8] = 3;
                NoCliente[9] = 20;		HoraInicioCliente[9] = 13.5; 	HoraFinalCliente[9] = 15;		NumeroCarretas[9] = 2;

                NoCliente[10] = 2;		HoraInicioCliente[10] = 8;		HoraFinalCliente[10] = 9.5;		NumeroCarretas[10] = 5;
				NoCliente[11] = 13; 	HoraInicioCliente[11] = 8.5;	HoraFinalCliente[11] = 10;		NumeroCarretas[11] = 5;
				NoCliente[12] = 6;		HoraInicioCliente[12] = 9.5; 	HoraFinalCliente[12] = 11;		NumeroCarretas[12] = 4;
				NoCliente[13] = 14;		HoraInicioCliente[13] = 10;	 	HoraFinalCliente[13] = 12;	 	NumeroCarretas[13] = 5;
				NoCliente[14] = 15;		HoraInicioCliente[14] = 11.5;	HoraFinalCliente[14] = 12; 		NumeroCarretas[14] = 2;

				NoCliente[15] = 16;		HoraInicioCliente[15] = 11.5;	HoraFinalCliente[15] = 13; 		NumeroCarretas[15] = 4;
                NoCliente[16] = 17;		HoraInicioCliente[16] = 12;		HoraFinalCliente[16] = 13.5;	NumeroCarretas[16] = 3;


                NoCliente[17] = 12;		HoraInicioCliente[17] = 8;	 	HoraFinalCliente[17] = 9;		NumeroCarretas[17] = 4;
                NoCliente[18] = 21;		HoraInicioCliente[18] = 8.5;	HoraFinalCliente[18] = 9;		NumeroCarretas[18] = 1;
                NoCliente[19] = 22;		HoraInicioCliente[19] = 8.5; 	HoraFinalCliente[19] = 9.5;		NumeroCarretas[19] = 4;
                NoCliente[20] = 23;		HoraInicioCliente[20] = 9;		HoraFinalCliente[20] = 10.5;	NumeroCarretas[20] = 2;
                NoCliente[21] = 24;		HoraInicioCliente[21] = 9.5;	HoraFinalCliente[21] = 11;    	NumeroCarretas[21] = 3;
                NoCliente[22] = 25;		HoraInicioCliente[22] = 11.5;	HoraFinalCliente[22] = 13.5;	NumeroCarretas[22] = 4;
*/

                NumeroCaminhoes = 30;

                CaminhoesPlanta.resize(NumeroPlantas + 1);
                CaminhoesPlanta[1] = 10;
                CaminhoesPlanta[2] = 10;
                CaminhoesPlanta[3] = 10;

                Velocidade 		= 30;


            }else{
                if(NomeInstancia[0] == 'C' ){
                    //Inicializa Parametros

                    cout << endl << endl << endl << " Nao devia ter entrado para escrever dados da Instancia C ####################################################################################################" << endl << endl << endl;

                    NumeroPlantas 	= 1;

                    NoPlanta.resize(NumeroPlantas + 1);
                    HoraInicioPlanta.resize(NumeroPlantas + 1);
                    HoraFinalPlanta.resize(NumeroPlantas + 1);

                    NoPlanta[1] = 4 ;/*15; 22;*/	HoraInicioPlanta[1] = 7; 	HoraFinalPlanta[1] = 18;
                    //NoPlanta[2] = 15;	HoraInicioPlanta[2] = 7; 	HoraFinalPlanta[2] = 18;
                    //NoPlanta[3] = 22;	HoraInicioPlanta[3] = 7; 	HoraFinalPlanta[3] = 18;



                    NumeroClientes 	= 5;
                    NoCliente.resize(	NumeroClientes	+	1);
                    HoraInicioCliente.resize(	NumeroClientes	+	1);
                    HoraFinalCliente.resize( 	NumeroClientes	+	1);
                    NumeroCarretas.resize( NumeroClientes + 1 ); // vetor que guarda o numero de carretas por cliente

                    cout << " +++++++++++ [ C ]  Plantas (" << NumeroPlantas << ")    Construcoes (" << NumeroClientes << ") ++++++++++++++++++" << endl;

                //dados com o gerador => NumeroVERSAO = 49;			************************************ Realizado *******************************************************
/*                    NoCliente[1] = 1;		HoraInicioCliente[1] = 8;		HoraFinalCliente[1] = 8.5;		NumeroCarretas[1] = 3; // Gerada com o rand com raiz de 49
                    NoCliente[2] = 2;		HoraInicioCliente[2] = 8.5;	 	HoraFinalCliente[2] = 9.5;		NumeroCarretas[2] = 5;
                    NoCliente[3] = 3;		HoraInicioCliente[3] = 9;	 	HoraFinalCliente[3] = 10.5;		NumeroCarretas[3] = 4;
                    NoCliente[4] = 5;		HoraInicioCliente[4] = 9.5;	 	HoraFinalCliente[4] = 10.5;		NumeroCarretas[4] = 2;
                    NoCliente[5] = 6;		HoraInicioCliente[5] = 10;	 	HoraFinalCliente[5] = 11;		NumeroCarretas[5] = 4;

                    NoCliente[6] = 7;		HoraInicioCliente[6] = 10;	 	HoraFinalCliente[6] = 11.5;		NumeroCarretas[6] = 1;
                    NoCliente[7] = 8;		HoraInicioCliente[7] = 10.5; 	HoraFinalCliente[7] = 11.5;		NumeroCarretas[7] = 1;
                    NoCliente[8] = 9;		HoraInicioCliente[8] = 11;	 	HoraFinalCliente[8] = 12;		NumeroCarretas[8] = 2;

                    NoCliente[9] = 10;		HoraInicioCliente[9] = 11.5; 	HoraFinalCliente[9] = 12.5;		NumeroCarretas[9] = 5;
                    NoCliente[10] = 11;		HoraInicioCliente[10] = 12;	 	HoraFinalCliente[10] = 13;		NumeroCarretas[10] = 4;		// Menos de 300 segundo

                    NoCliente[11] = 12;		HoraInicioCliente[11] = 8;	 	HoraFinalCliente[11] = 8.5;		NumeroCarretas[11] = 3;
                    NoCliente[12] = 13;		HoraInicioCliente[12] = 8; 		HoraFinalCliente[12] = 9;		NumeroCarretas[12] = 2;
                    NoCliente[13] = 14;		HoraInicioCliente[13] = 8.5;	HoraFinalCliente[13] = 10;		NumeroCarretas[13] = 5;
                    NoCliente[14] = 16;		HoraInicioCliente[14] = 9.5;	HoraFinalCliente[14] = 11;		NumeroCarretas[14] = 1;
                    NoCliente[15] = 17;		HoraInicioCliente[15] = 10;	 	HoraFinalCliente[15] = 11;		NumeroCarretas[15] = 1;
  	  	  	  	  	 NoCliente[16] = 18;		HoraInicioCliente[16] = 10;	 	HoraFinalCliente[16] = 11.5;	NumeroCarretas[16] = 4;
                    NoCliente[17] = 19;		HoraInicioCliente[17] = 10.5;	HoraFinalCliente[17] = 12;		NumeroCarretas[17] = 3;		// Menos de 3 segundo

                    NoCliente[18] = 20;		HoraInicioCliente[18] = 8;	 	HoraFinalCliente[18] = 9;		NumeroCarretas[18] = 1;
                    NoCliente[19] = 21;		HoraInicioCliente[19] = 8.5; 	HoraFinalCliente[19] = 10;		NumeroCarretas[19] = 4;
                    NoCliente[20] = 23;		HoraInicioCliente[20] = 8;	 	HoraFinalCliente[20] = 9;		NumeroCarretas[20] = 3;
                    NoCliente[21] = 24;		HoraInicioCliente[21] = 9;	 	HoraFinalCliente[21] = 10.5;	NumeroCarretas[21] = 4;
                    NoCliente[22] = 25;		HoraInicioCliente[22] = 10;	 	HoraFinalCliente[22] = 11;		NumeroCarretas[22] = 4;		// com 14 segundos
                    */


                    NoCliente[1] = 1;		HoraInicioCliente[1] = 8;		HoraFinalCliente[1] = 9;		NumeroCarretas[1] = 4; // Gerada com o rand com raiz de 49
					NoCliente[2] = 2;		HoraInicioCliente[2] = 9.5;	 	HoraFinalCliente[2] = 10.5;		NumeroCarretas[2] = 5;
					NoCliente[3] = 3;		HoraInicioCliente[3] = 8.5;	 	HoraFinalCliente[3] = 9.5;		NumeroCarretas[3] = 5;
					NoCliente[4] = 5;		HoraInicioCliente[4] = 8;	 	HoraFinalCliente[4] = 9;		NumeroCarretas[4] = 4;
					NoCliente[5] = 6;		HoraInicioCliente[5] = 8.5;	 	HoraFinalCliente[5] = 9.5;		NumeroCarretas[5] = 5;

                //dados com o gerador => NumeroVERSAO = 50;         ************************************ Realizado *******************************************************
/*                    NoCliente[1] = 1;		HoraInicioCliente[1] = 8;	 	HoraFinalCliente[1] = 8.5;		NumeroCarretas[1] = 3;
                    NoCliente[2] = 2;		HoraInicioCliente[2] = 8;	 	HoraFinalCliente[2] = 9;		NumeroCarretas[2] = 1;
                    NoCliente[3] = 3;		HoraInicioCliente[3] = 8;	 	HoraFinalCliente[3] = 9;		NumeroCarretas[3] = 4;
                    NoCliente[4] = 5;		HoraInicioCliente[4] = 8;	 	HoraFinalCliente[4] = 9.5;		NumeroCarretas[4] = 1;
                    NoCliente[5] = 6;		HoraInicioCliente[5] = 8.5;	 	HoraFinalCliente[5] = 10;		NumeroCarretas[5] = 4;


                    NoCliente[6] = 7;		HoraInicioCliente[6] = 9;	 	HoraFinalCliente[6] = 10.5;		NumeroCarretas[6] = 4;
                    NoCliente[7] = 8;		HoraInicioCliente[7] = 10;	 	HoraFinalCliente[7] = 11;		NumeroCarretas[7] = 2;
                    NoCliente[8] = 9;		HoraInicioCliente[8] = 10;	 	HoraFinalCliente[8] = 11.5;		NumeroCarretas[8] = 4;

                    NoCliente[9] = 10;		HoraInicioCliente[9] = 10.5;	 	HoraFinalCliente[9] = 12;		NumeroCarretas[9] = 5;
                    NoCliente[10] = 11;		HoraInicioCliente[10] = 11;	 	HoraFinalCliente[10] = 12.5;		NumeroCarretas[10] = 3;				// Resolvido com 1segundo

                    NoCliente[11] = 12;		HoraInicioCliente[11] = 8;	 	HoraFinalCliente[11] = 9;		NumeroCarretas[11] = 4;
                    NoCliente[12] = 13;		HoraInicioCliente[12] = 8; 	 	HoraFinalCliente[12] = 9;		NumeroCarretas[12] = 4;
                    NoCliente[13] = 14;		HoraInicioCliente[13] = 8.5; 	HoraFinalCliente[13] = 9;		NumeroCarretas[13] = 1;
                    NoCliente[14] = 16;		HoraInicioCliente[14] = 8;	 	HoraFinalCliente[14] = 10;		NumeroCarretas[14] = 4;
                    NoCliente[15] = 17;		HoraInicioCliente[15] = 9;	 	HoraFinalCliente[15] = 11;		NumeroCarretas[15] = 5;

                    NoCliente[16] = 18;		HoraInicioCliente[16] = 10;	 	HoraFinalCliente[16] = 11.5;		NumeroCarretas[16] = 4;
                    NoCliente[17] = 19;		HoraInicioCliente[17] = 10.5;	 	HoraFinalCliente[17] = 12;	NumeroCarretas[17] = 4;			// Resolvido com 333 segundos

                    NoCliente[18] = 20;		HoraInicioCliente[18] = 8;	 	HoraFinalCliente[18] = 9;		NumeroCarretas[18] = 5;
                    NoCliente[19] = 21;		HoraInicioCliente[19] = 8.5; 	HoraFinalCliente[19] = 10;		NumeroCarretas[19] = 3;
                    NoCliente[20] = 23;		HoraInicioCliente[20] = 8;	 	HoraFinalCliente[20] = 10;		NumeroCarretas[20] = 2;
                    NoCliente[21] = 24;		HoraInicioCliente[21] = 9;	 	HoraFinalCliente[21] = 11;		NumeroCarretas[21] = 2;
                    NoCliente[22] = 25;		HoraInicioCliente[22] = 9;	 	HoraFinalCliente[22] = 11.5;	NumeroCarretas[22] = 2;		// Resolvido com 160 segundos
                    */

                //dados com o gerador => NumeroVERSAO = 51;			************************************ Realizado *******************************************************
        /*                NoCliente[1] = 1;		HoraInicioCliente[1] = 8;	 	HoraFinalCliente[1] = 9;		NumeroCarretas[1] = 4;
                    NoCliente[2] = 2;		HoraInicioCliente[2] = 8;	 	HoraFinalCliente[2] = 9;		NumeroCarretas[2] = 3;
                    NoCliente[3] = 3;		HoraInicioCliente[3] = 8.5;	 	HoraFinalCliente[3] = 9.5;		NumeroCarretas[3] = 3;
                    NoCliente[4] = 5;		HoraInicioCliente[4] = 9;	 	HoraFinalCliente[4] = 10;		NumeroCarretas[4] = 4;
                    NoCliente[5] = 6;		HoraInicioCliente[5] = 9;	 	HoraFinalCliente[5] = 10.5;		NumeroCarretas[5] = 4;

                    NoCliente[6] = 7;		HoraInicioCliente[6] = 9.5;	 	HoraFinalCliente[6] = 11;		NumeroCarretas[6] = 5;
                    NoCliente[7] = 8;		HoraInicioCliente[7] = 10;	 	HoraFinalCliente[7] = 11.5;		NumeroCarretas[7] = 4;
                    NoCliente[8] = 9;		HoraInicioCliente[8] = 10.5;	HoraFinalCliente[8] = 12;		NumeroCarretas[8] = 3;

                    NoCliente[9] = 10;		HoraInicioCliente[9] = 11;	 	HoraFinalCliente[9] = 12;		NumeroCarretas[9] = 2;
                    NoCliente[10] = 11;		HoraInicioCliente[10] = 11.5;	HoraFinalCliente[10] = 13;		NumeroCarretas[10] = 5;				// Resolveu 14 segundos

                    NoCliente[11] = 12;		HoraInicioCliente[11] = 8;	 	HoraFinalCliente[11] = 9;		NumeroCarretas[11] = 5;
                    NoCliente[12] = 13;		HoraInicioCliente[12] = 8; 	 	HoraFinalCliente[12] = 10;		NumeroCarretas[12] = 4;
                    NoCliente[13] = 14;		HoraInicioCliente[13] = 9.5; 	HoraFinalCliente[13] = 11.5;	NumeroCarretas[13] = 5;
                    NoCliente[14] = 16;		HoraInicioCliente[14] = 11;	 	HoraFinalCliente[14] = 12;		NumeroCarretas[14] = 2;
                    NoCliente[15] = 17;		HoraInicioCliente[15] = 11;		HoraFinalCliente[15] = 12.5;	NumeroCarretas[15] = 4;

                    NoCliente[16] = 18;		HoraInicioCliente[16] = 11.5;	HoraFinalCliente[16] = 12.5;	NumeroCarretas[16] = 3;
                    NoCliente[17] = 19;		HoraInicioCliente[17] = 11.5;	HoraFinalCliente[17] = 13;		NumeroCarretas[17] = 4;			// com 168 segundos

                    NoCliente[18] = 20;		HoraInicioCliente[18] = 8;	 	HoraFinalCliente[18] = 9;		NumeroCarretas[18] = 1;
                    NoCliente[19] = 21;		HoraInicioCliente[19] = 8; 	 	HoraFinalCliente[19] = 9;		NumeroCarretas[19] = 4;
                    NoCliente[20] = 23;		HoraInicioCliente[20] = 8.5;	HoraFinalCliente[20] = 9;		NumeroCarretas[20] = 2;
                    NoCliente[21] = 24;		HoraInicioCliente[21] = 9;	 	HoraFinalCliente[21] = 10;		NumeroCarretas[21] = 3;
                    NoCliente[22] = 25;		HoraInicioCliente[22] = 9;	 	HoraFinalCliente[22] = 10.5;	NumeroCarretas[22] = 4;			// com 210 segundos
*/

                    NumeroCaminhoes = 10;

                    CaminhoesPlanta.resize(NumeroPlantas + 1);
                    CaminhoesPlanta[1] = 10;
                    //CaminhoesPlanta[2] = 10;
                    //CaminhoesPlanta[3] = 10;

                    Velocidade 		= 30;
                }else{
                    if(NomeInstancia[0] == 'r' && NomeInstancia[1] == '-' && NomeInstancia[2] == 'C'){
                        NumeroPlantas 	= 2;

                        cout << endl << endl << endl << " Nao devia ter entrado para escrever dados da Instancia r-C ####################################################################################################" << endl << endl << endl;

                        NoPlanta.resize(NumeroPlantas + 1);
                        HoraInicioPlanta.resize(NumeroPlantas + 1);
                        HoraFinalPlanta.resize(NumeroPlantas + 1);

                        NoPlanta[1] = 4 ;/*15; 22;*/	HoraInicioPlanta[1] = 7; 	HoraFinalPlanta[1] = 18;
                        NoPlanta[2] = 15;	HoraInicioPlanta[2] = 7; 	HoraFinalPlanta[2] = 18;
                        //NoPlanta[3] = 22;	HoraInicioPlanta[3] = 7; 	HoraFinalPlanta[3] = 18;

                        NumeroClientes 	= 5;
                        NoCliente.resize(	NumeroClientes	+	1);
                        HoraInicioCliente.resize(	NumeroClientes	+	1);
                        HoraFinalCliente.resize( 	NumeroClientes	+	1);
                        NumeroCarretas.resize( NumeroClientes + 1 ); // vetor que guarda o numero de carretas por cliente

                        //cout << " +++++++++++ [ r-C ]   Plantas (" << NumeroPlantas << ")    Construcoes (" << NumeroClientes << ") ++++++++++++++++++" << endl;

                    //dados com o gerador => NumeroVERSAO = 49;			************************************ Realizado *******************************************************
              /*        NoCliente[1] = 1;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 8.5;		//3 (1)
                        NoCliente[2] = 2;		HoraInicioCliente[2] = 8;	 HoraFinalCliente[2] = 9;		//5 (2)
                        NoCliente[3] = 5;		HoraInicioCliente[3] = 8.5;	 HoraFinalCliente[3] = 10;		//4	(3)

                        NoCliente[4] = 14;		HoraInicioCliente[4] =8;	 HoraFinalCliente[4] = 8.5;	//2
                        NoCliente[5] = 16;		HoraInicioCliente[5] = 8;	 HoraFinalCliente[5] = 9;		//4	(6)
*/

                    //dados com o gerador => NumeroVERSAO = 50;         ************************************ Realizado *******************************************************
  /*                     NoCliente[1] = 1;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 8.5;		//3 (1)
                        NoCliente[2] = 2;		HoraInicioCliente[2] = 8;	 HoraFinalCliente[2] = 8.5;		//1 (2)
                        NoCliente[3] = 5;		HoraInicioCliente[3] = 8;	 HoraFinalCliente[3] = 9;		//4	(3)

                        NoCliente[4] = 14;		HoraInicioCliente[4] = 8;	 HoraFinalCliente[4] = 8.5;		//1	(5)
                        NoCliente[5] = 16;		HoraInicioCliente[5] = 8;	 HoraFinalCliente[5] = 9;		//4	(6)
*/

                    //dados com o gerador => NumeroVERSAO = 51;			************************************ Realizado *******************************************************
/*
                      NoCliente[1] = 1;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 9;		//4 	(1)
                        NoCliente[2] = 2;		HoraInicioCliente[2] = 8;	 HoraFinalCliente[2] = 8.5;		//3 	(2)
                        NoCliente[3] = 5;		HoraInicioCliente[3] = 8;	 HoraFinalCliente[3] = 8.5;		//3	(3)

                        NoCliente[4] = 14;		HoraInicioCliente[4] = 8;	 HoraFinalCliente[4] = 9;		//4	(5)
                        NoCliente[5] = 16;		HoraInicioCliente[5] = 8;	 HoraFinalCliente[5] = 9;		//4	(6)
*/

                        NumeroCaminhoes = 20;

                        CaminhoesPlanta.resize(NumeroPlantas + 1);
                        CaminhoesPlanta[1] = 10;
                        CaminhoesPlanta[2] = 10;
                        //CaminhoesPlanta[3] = 10;

                        Velocidade 		= 30;
                    }else{
                         if(NomeInstancia[0] == 'r' && NomeInstancia[1] == '-' && NomeInstancia[2] == 'R'){
                            NumeroPlantas 	= 2;

                            cout << endl << endl << endl << " Nao devia ter entrado para escrever dados da Instancia r-R ####################################################################################################" << endl << endl << endl;

                            NoPlanta.resize(NumeroPlantas + 1);
                            HoraInicioPlanta.resize(NumeroPlantas + 1);
                            HoraFinalPlanta.resize(NumeroPlantas + 1);

                            NoPlanta[1] = 1 ;/*15; 22;*/	HoraInicioPlanta[1] = 7; 	HoraFinalPlanta[1] = 18;
                            NoPlanta[2] = 5;	HoraInicioPlanta[2] = 7; 	HoraFinalPlanta[2] = 18;
                            //NoPlanta[3] = 22;	HoraInicioPlanta[3] = 7; 	HoraFinalPlanta[3] = 18;

                            NumeroClientes 	= 5;
                            NoCliente.resize(	NumeroClientes	+	1);
                            HoraInicioCliente.resize(	NumeroClientes	+	1);
                            HoraFinalCliente.resize( 	NumeroClientes	+	1);
                            NumeroCarretas.resize( NumeroClientes + 1 ); // vetor que guarda o numero de carretas por cliente

                            cout << " +++++++++++   [ r-R ]  Plantas (" << NumeroPlantas << ")    Construcoes (" << NumeroClientes << ") ++++++++++++++++++" << endl;

                        //dados com o gerador => NumeroVERSAO = 49;			************************************ Realizado *******************************************************
                            /*          NoCliente[1] = 9;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 8.5;		//3 (1)
                            NoCliente[2] = 10;		HoraInicioCliente[2] = 8;	 HoraFinalCliente[2] = 9;		//5 (2)
                            NoCliente[3] = 20;		HoraInicioCliente[3] = 8.5;	 HoraFinalCliente[3] = 10;		//4	(3)

                            NoCliente[4] = 14;		HoraInicioCliente[4] =8;	 HoraFinalCliente[4] = 8.5;	//2
                            NoCliente[5] = 16;		HoraInicioCliente[5] = 8;	 HoraFinalCliente[5] = 9;		//4	(6)
*/
                        //dados com o gerador => NumeroVERSAO = 50;         ************************************ Realizado *******************************************************
              /*            NoCliente[1] = 9;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 8.5;		//3 (1)
                            NoCliente[2] = 10;		HoraInicioCliente[2] = 8;	 HoraFinalCliente[2] = 8.5;		//1 (2)
                            NoCliente[3] = 20;		HoraInicioCliente[3] = 8;	 HoraFinalCliente[3] = 9;		//4	(3)

                            NoCliente[4] = 14;		HoraInicioCliente[4] = 8;	 HoraFinalCliente[4] = 8.5;		//1	(5)
                            NoCliente[5] = 16;		HoraInicioCliente[5] = 8;	 HoraFinalCliente[5] = 9;		//4	(6)
*/
                        //dados com o gerador => NumeroVERSAO = 51;			************************************ Realizado *******************************************************
/*
                          NoCliente[1] = 9;		HoraInicioCliente[1] = 8;	 HoraFinalCliente[1] = 9;		//4 	(1)
                            NoCliente[2] = 10;		HoraInicioCliente[2] = 8;	 HoraFinalCliente[2] = 8.5;		//3 	(2)
                            NoCliente[3] = 20;		HoraInicioCliente[3] = 8;	 HoraFinalCliente[3] = 8.5;		//3	(3)

                            NoCliente[4] = 14;		HoraInicioCliente[4] = 8;	 HoraFinalCliente[4] = 9;		//4	(5)
                            NoCliente[5] = 16;		HoraInicioCliente[5] = 8;	 HoraFinalCliente[5] = 9;		//4	(6)
*/
                            NumeroCaminhoes = 20;

                            CaminhoesPlanta.resize(NumeroPlantas + 1);
                            CaminhoesPlanta[1] = 10;
                            CaminhoesPlanta[2] = 10;
                            //CaminhoesPlanta[3] = 10;

                            Velocidade 		= 30;
                        }
                    }
                }
            }
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

        srand(NumeroVERSAO);		// O gerador é o numero da versão

     /*   // realizar testes individualmente
        int AuxLixo;
        for(int i = 0; i < 10;i++){
        	AuxLixo = (rand()%5) + 1;
        }
     */

        for(int c =1; c <= NumeroClientes; c++){
        	NumeroCarretas[c] = (rand()%2) + 4;
			//InstanciaSolomon << " No" << i << " ";
			InstanciaSolomon << NumeroCarretas[c] ;
			for( int i= 1; i <= NumeroCarretas[c] ; i++){
				InstanciaSolomon << " " << i;
			}
			InstanciaSolomon << endl;
        }

        // Preenche as localizações das plantas e entradas

        for(int p =1; p <= NumeroPlantas; p++){
            for(int i =1; i <= NumeroClientes; i++){
            	InstanciaSolomon << sqrt( pow( Coordenadas[ NoPlanta[p] ][0] - Coordenadas[	NoCliente[i] ][0],2) + pow( Coordenadas[ NoPlanta[p] ][1] - Coordenadas[ NoCliente[i] ][1],2) ) / Velocidade << " ";
            }
            InstanciaSolomon << endl;
        }

        //InstanciaSolomon << " localidade plantas "<< endl;



        // Preenche as localizações entradas e plantas
        for(int i =1; i <= NumeroClientes; i++){
            for(int p =1; p <= NumeroPlantas; p++){
                InstanciaSolomon << sqrt( pow( Coordenadas[ NoPlanta[p] ][0] - Coordenadas[ NoCliente[i] ][0],2) + pow( Coordenadas[  NoPlanta[p] ][1] - Coordenadas[ NoCliente[i] ][1],2) ) / Velocidade << " ";
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
            DadosInstanciaSalomonCriada <<  "   NoPlanta = " <<  NoPlanta[p];
            DadosInstanciaSalomonCriada << " Horario [ "	<< HoraInicioPlanta[p] << " - "	<< HoraFinalPlanta[p] << " ]" << endl;
        }
        DadosInstanciaSalomonCriada << "Dados dos Clientes " << endl;
        for( int c = 1; c <= NumeroClientes; c++){
            DadosInstanciaSalomonCriada << "  NoCliente = " << NoCliente[c];
            DadosInstanciaSalomonCriada << " \tDemanda em carretas ( " << NumeroCarretas[c] << " ) ";
            DadosInstanciaSalomonCriada << "Horario [ "	<< HoraInicioCliente[c] << " - " << HoraFinalCliente[c] << " ]" << endl;
        }

        DadosInstanciaSalomonCriada << endl << endl<< "Distancia das plantas para construcoes  em minutos" << endl << endl;
        for (int p = 1; p <= NumeroPlantas; p++){
            DadosInstanciaSalomonCriada <<  "   Planta = " <<  p << endl;
            DadosInstanciaSalomonCriada << "Construcao   Tempo de Ida    Tempo de Ida e Volta" << endl;
            for( int c = 1; c <= NumeroClientes; c++){
                DadosInstanciaSalomonCriada << c << "\t\t" << (sqrt( pow( Coordenadas[ NoPlanta[p] ][0] - Coordenadas[ NoCliente[c] ][0],2) + pow( Coordenadas[  NoPlanta[p] ][1] - Coordenadas[ NoCliente[c] ][1],2) ) / Velocidade)*60  << "\t\t";
                DadosInstanciaSalomonCriada << (sqrt( pow( Coordenadas[ NoPlanta[p] ][0] - Coordenadas[ NoCliente[c] ][0],2) + pow( Coordenadas[  NoPlanta[p] ][1] - Coordenadas[ NoCliente[c] ][1],2) ) / Velocidade)*60 + TempoPlanta * 60 + (sqrt( pow( Coordenadas[ NoPlanta[p] ][0] - Coordenadas[ NoCliente[c] ][0],2) + pow( Coordenadas[  NoPlanta[p] ][1] - Coordenadas[ NoCliente[c] ][1],2) ) / Velocidade)*60 << endl;
            }
        }
	}else{

		InstanciaSolomon << " Nao se enquadra! " << endl;
	}

	DadosInstanciaSalomonCriada.close();
	InstanciaSolomon.close();
}

DadosSolomon::~DadosSolomon(){
    for( int i = 0; i <= NumeroNosDadosSolomon; i++){
        Coordenadas[i].clear();
    }
    Coordenadas.clear();
}

#endif /* DADOSSOLOMON_HPP_ */

