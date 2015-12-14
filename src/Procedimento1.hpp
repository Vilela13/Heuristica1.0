/*
 * Procedimento1.hpp
 *
 *  Created on: Aug 20, 2015
 *      Author: mateus.vilela
 */

#ifndef PROCEDIMENTO1_HPP_
#define PROCEDIMENTO1_HPP_



class Procedimento1{

public:
	Procedimento1();

	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	void CarregaDados(int InstNP, ConjuntoPlantas InstPlantasInstancia, int InstNE, ConjuntoConstrucoes InstConstrucoesInstancia, int InstNV, double InstVelocidade, double InstTempoDeVidaConcreto);

// Seleciona uma construção baseada em um rank que elas possuem
	int SelecionaConstrucao(  int &ConstrucaoVaiSerSuprida, int &IndiceConstrucaoVaiSerSuprida);
// Seleciona a planta mais perto
	int SelecionaPlantaMenorDistanciaConstrucao( int IndiceConstrucaoVaiSerSuprida, int &PlantaMaisPerto, int &IndicePlantaMaisPerto );
// Seleciona carreta menos utilizada
	int SelecionaCarreta(Planta& PlantaMaisPerto, Construcao& ConstrucaoVaiSerSuprida, int  NumeroDemanda, int SituacaoDemandaAnalisada, int TipoOrdenacao);

// funções de verificação
	void ConfereSeNaoEncontrouUmaPlanta( int);
	int ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas);
	int AdicionaTarefa(int IndiceConstrucaoVaiSerSuprida, int Demanda, int TipoOrdenacao  , int imprime);

	void VerificaAlocacaoDemandaConstrucao(int IndiceConstrucaoVaiSerSuprida, int &Viabilidade);

// executa o procedimento de realizar o sequenciamento da produção e despache de concreto
	int Executa(int);

    ~Procedimento1();
};

Procedimento1::Procedimento1(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
}

void Procedimento1::CarregaDados(int InstNP, ConjuntoPlantas InstPlantasInstancia, int InstNE, ConjuntoConstrucoes InstConstrucoesInstancia, int InstNV, double InstVelocidade, double InstTempoDeVidaConcreto){
	NP = InstNP;
	PlantasInstancia = InstPlantasInstancia;
	NE = InstNE;
	ConstrucoesInstancia  = InstConstrucoesInstancia;
	NV = InstNV;
	Velocidade = InstVelocidade;
	TempoDeVidaConcreto = InstTempoDeVidaConcreto;
}

// Seleciona uma construção baseada em um rank = Janela de tempo / numero de demandas
int Procedimento1::SelecionaConstrucao( int &ConstrucaoVaiSerSuprida, int &IndiceConstrucaoVaiSerSuprida ){
	int Ativo;
	double RankInicial;

	Ativo = 0;
	RankInicial = DBL_MAX;

	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			// Seleciona a construção que não possui todas as suas demandas já atendidas e que ainda não foi analisada
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas &&  ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] == 0){
				ConstrucaoVaiSerSuprida = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
				IndiceConstrucaoVaiSerSuprida = c;
				RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
				Ativo = 1;
			}
		}
	}

	if( Ativo == 1){
		return 1;
	}else{
		return 0;
	}
}

// Seleciona a planta mais perto
int Procedimento1::SelecionaPlantaMenorDistanciaConstrucao( int IndiceConstrucaoVaiSerSuprida, int &PlantaMaisPerto, int &IndicePlantaMaisPerto ){
	int Ativo;
	double DistanciaConstrucaoPlanta;

	Ativo = 0;
	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].DistanciaPlantas[p].Distancia){
			// seleciona a planta que ainda não foi analisada
			if( PlantasInstancia.PlantasAnalizadas[p] == 0){
				PlantaMaisPerto = PlantasInstancia.Plantas[p].NumeroDaPlanta;
				IndicePlantaMaisPerto = p;
				DistanciaConstrucaoPlanta = ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].DistanciaPlantas[p].Distancia;
				Ativo = 1;
			}
		}
	}

	if( Ativo == 1){
		return 1;
	}else{
		return 0;
	}
}


// Verifica se não encontrou uma planta
void Procedimento1::ConfereSeNaoEncontrouUmaPlanta( int  PlantaSelecionada){
	if( PlantaSelecionada == 0){
		cout  << endl << endl << endl;
		cout << " ################################################################################" << endl;
		cout << "           Não encontrou Planta para se alocar <<<<<<< Problema >>>>>>>>>>>" << endl;
		cout << " ################################################################################" << endl;
		cout << endl << endl;
	}
}

// readiciona tarefas deletadas e deleta tarefas adicionadas visando restaurar a configuração inicial da solução
int Procedimento1::ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas){
	int c;

	// percorre trodos os elementos das tarefas que foram removidas e adicionadas no vetor
	for( int i = DadosTarefasMovidas.size() - 1 ; i >= 0; i--){

		// caso a tarefa tenha sido retirada da solução, ela é adicionada novamente
		if( DadosTarefasMovidas[i].Status == 'r'){
			// coleta o inidice da construção
			if(ConstrucoesInstancia.RetornaIndiceConstrucao( DadosTarefasMovidas[i].DadosDasTarefas[0]  , c, " Solucao::DeletaTarefasApartirDeDados") == 0 ){
				return 0;
			}
			// Aloca a tarefa caso possivel
			if( ConstrucoesInstancia.Construcoes[c].AlocaAtividade( DadosTarefasMovidas[i].HorariosDasTarefas[2],DadosTarefasMovidas[i].HorariosDasTarefas[3], DadosTarefasMovidas[i].DadosDasTarefas[2], DadosTarefasMovidas[i].DadosDasTarefas[1], DadosTarefasMovidas[i].DadosDasTarefas[3], DadosTarefasMovidas[i].DadosDasTarefas[4], PlantasInstancia) == 0 ){
				cout << endl << endl << "       <<<<<<<<<<< Problema em adicionar -> Solucao::ReadicionaDeletaTarefasApartirDeDados >>>>>>>>>>>>>>>>> " << endl;
				DadosTarefasMovidas[i].Imprimir();
				cout << endl;
				return 0;
			}
			//Atualiza o Indice de Inviabilidade da solução
			ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
		}

		// caso a tarefa tenha sido adicionada a solução, ela é retirada da solução
		if( DadosTarefasMovidas[i].Status == 'a'){
			// coleta o inidice da construção
			if(ConstrucoesInstancia.RetornaIndiceConstrucao( DadosTarefasMovidas[i].DadosDasTarefas[0]  , c, " Solucao::DeletaTarefasApartirDeDados") == 0 ){
				return 0;
			}
			// deleta a tarefa caso possivel
			if( ConstrucoesInstancia.Construcoes[c].DeletaTarefasAnteriormenteAdicionadasDados( DadosTarefasMovidas[i], PlantasInstancia) == 0){
				cout << endl << endl << "       <<<<<<<<<<< Problema em remover -> Solucao::ReadicionaDeletaTarefasApartirDeDados >>>>>>>>>>>>>>>>> " << endl;
				DadosTarefasMovidas[i].Imprimir();
				cout << endl;
				return 0;
			}
			//Atualiza o Indice de Inviabilidade da solução
			ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade + 1;
		}
	}
	return 1;
}

int Procedimento1::AdicionaTarefa(int IndiceConstrucaoVaiSerSuprida, int Demanda, int TipoOrdenacao  , int imprime){
	// armazena os horarios de uma tarefa
	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;
	// arqmazena os estados de disponibilidade da tarefa na planta, na coonstrução e no caminhão
	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;
	// indice da construção e planta
	int  p ;
	int PlantaMaisPerto;

	// Guarda as tarefas movidada no processo de mudar o horario de atendimento de uma demanda anterior visando atender uma posterior
	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;

	// variaveis de controle
	int SituacaoAlocacao;



	int VerificaExistencia;
	int SituacaoDemanda;
	int SituacaoRemocao;

	VerificaExistencia = 0;
	SituacaoDemanda = 1;
	SituacaoRemocao = 0;

	// variavel que indica se ira realizar a verificação da solução
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	int ParaPrograma;

	// inicializa os vetores que armazenam os horarios que as plantas podem atender a demanda da construção caso se caia no caso de -2 na Analise da planta. Se é inicializado com os valores maximos de Double
	PlantasInstancia.InicializaVetorHorarioQuePlantaPodeAtender();

	// verifica se a construção já foi atendida em sua totatlidade, cao não entra no if
	if ( ConstrucoesInstancia.Construcoes[ IndiceConstrucaoVaiSerSuprida ].NumeroDemandas > ConstrucoesInstancia.Construcoes[ IndiceConstrucaoVaiSerSuprida ].StatusAtendimento){
		// faz com que nenhuma planta tenha sido analisada até o momento
		PlantasInstancia.InicializaPlantasAnalizadas();
		// só entra no loop enquanto se tem uma planta para analisar
		while( PlantasInstancia.AnalizouTodasPLanats() == 0){
			// encontra a planta mais perto d aconstrução
			SelecionaPlantaMenorDistanciaConstrucao( IndiceConstrucaoVaiSerSuprida, PlantaMaisPerto, p );
			// ordena as britadeiras
			PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
			// percorre todos os veículos da planta
			for( int v = 0; v < PlantasInstancia.Plantas[ p ].NumeroVeiculos; v++){
				// inicializa o tempo inicio que a planta corrente ira começar a analise se pode atender a demanda corrente, caso
				if( ( ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao] - PlantasInstancia.Plantas[ p ].TempoPlanta ) > PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento ){
					//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela construção.
					HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao] - PlantasInstancia.Plantas[ p ].TempoPlanta;
				}else{
					//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela planta.
					HorarioInicioPlanta = PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento;
				}
				// enquanto estiver na janela de tempo possivel para atendimeto se realiza o loop abaixo.
				do{
					// atualiza os horarios na construção e planta
					HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[ p ].TempoPlanta;
					HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao];
					HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao][Demanda];
					HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao];

					// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta
					DisponibilidadePlanta = PlantasInstancia.Plantas[ p ].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
					DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
					DisponibilidadeCarreta = PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);

					// caso se puder realizar a terefa se entra nos If
					if( DisponibilidadePlanta == 1){
						if( DisponibilidadeCarreta == 1){
							if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
								// se consegue atender a demanda com essa planta, carreta e nessa construção
								ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].AlocaAtividadeSalvandoDados(VerificaExistencia, HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[ p ].NumeroDaPlanta, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, DadosTarefasMovidasAuxiliar);
								// se dieminui o nível de iniviabilidade da solução
								ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
								// retorna 1 indicando que se foi possivel alocar a demanda corrente
								return 1;
							}else{
								// caso se possa atender a demanda se atender as demandas anterior em um horario diferente
								if( DisponibilidadeConstrucao == -2){
									// caso for  aprimeira vez que se verifique a valor -2 para a DisponibilidadeConstrução, se atualiza os hoarios iniciais tanto na planta e na construção que a planta corrente pode vir a atender a construção
									if( PlantasInstancia.PlantasAnalizadas[ p ] == 0){
										PlantasInstancia.HorarioQuePlantaPodeAtender[ p ] = HorarioInicioPlanta;
										PlantasInstancia.HorarioQueConstrucaoPodeReceberDemanda[ p ] = HorarioChegaContrucao;
									}
									// se atualiza a situação da planta corrente com -2 e coloca o tempo de inicio da planta como o tempo maximo de funcionamento da planta para se forçar sair do loop do while
									PlantasInstancia.PlantasAnalizadas[ p ] = -2;
									HorarioInicioPlanta = PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento + IntervaloDeTempo;

									if( imprime == 1){
										//cout <<  "           (-) Caso atrazar da para alocar, demanda em analise [" << ConstrucoesInstancia.Construcoes[ IndiceConstrucaoVaiSerSuprida ].NumeroDaConstrucao << "-" << Demanda << "] no horario " << HorarioChegaContrucao << " na planta [" << PlantasInstancia.Plantas[ p ].NumeroDaPlanta << "] no veiculo [" << v << "]" << endl;
									}
								}
							}
						}
					}
					// acrescenta o horario do inicio da planta para se percorrer todos os possiveis horarios de alocação da demanda por essa planta corrente
					HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
					// realiza o loop até que os intervalos de de funcionamento da planta e da construção ainda sejam respeitados
				}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].TempoMaximoDeFuncionamento);
			}
				// caso a planta não tenha sido assinalada com -2, que ela pode atender a demanda caso atraze as outras demandas anteriores, se marca a planta com 1 para sinalizar que ela não consegue atender a está demanda.
			if (PlantasInstancia.PlantasAnalizadas[ p ] != -2){
				PlantasInstancia.PlantasAnalizadas[ p ] = 1;
			}
		}
		if( imprime == 1){
			cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao << "-" << Demanda << "]   sem atrazar as outra demandas  -> Solucao::AdicionaTarefa &&&&&&&&&&&&& " << endl;

			cout << endl << endl <<  " SituacaoPlantaAtenderCasoAtrazar" << endl;
			ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
			cout <<   " HorarioQuePlantaPodeAtender" << endl;
			ImprimeVetorDouble( PlantasInstancia.HorarioQuePlantaPodeAtender);
			cout <<   " HorarioQueConstrucaoPodeReceberDemanda" << endl;
			ImprimeVetorDouble( PlantasInstancia.HorarioQueConstrucaoPodeReceberDemanda);
			cin >> ParaPrograma;
		}
		// caso não se tenha conseguido atender a demanda corrente, se verifica se tem alguma planta que pode atender a demanda caso se mude o horario de atendiemnto das outras demandas posteriores a está. Caso se possa, se entra no if e tenta mudar o horario das demandas anteriores para se tentar atender a demanda corrente
		if( PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() == 1){
			// limpa o vetor que aramzena as tarefas adicionadas e removidas no processo de atraso
			DadosTarefasMovidasAuxiliar.clear();
			if( imprime == 1){
				cout << endl << endl << "      Função que atraza demandas - horario que pode atender construção = " << PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() << endl << endl;
			}
			// função que realiza o atraso das tarefas para atender uma demanda anterior, caso cosnseguir alocar entra no if
			if ( ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].AtrazaDemandasParaAtenderMaster( Demanda, PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() - ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].TempoMaximoEntreDescargas  + IntervaloDeTempo,DadosTarefasMovidasAuxiliar, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, SituacaoAlocacao, TipoOrdenacao, imprime, " Procedimento1::AdicionaTarefa ") == 1 ){
				if( imprime == 1){
					cout << endl << endl << "       ******* adicionei demanda [" << ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao << "-" << Demanda << "] com o processo de atraso " << endl << endl;
					cout << "DadosTarefasMovidasAuxiliar" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
					cin >> ParaPrograma;
				}
				// retorna 1, conseguiu alocar a demanda em questão
				return 1;
			// caso não se consiga alocar a demanda
			}else{
				// retorna a solução até o ponto que ela estava antes do processo de atraso das demandas para atender a ultima demanda
				if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasAuxiliar ) == 0){
					cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
				}
			}
			// limpa as demandas adicionadas e retiradas no processo de atraso de demandas para atender a ultima demanda
			DadosTarefasMovidasAuxiliar.clear();
			if( imprime == 1){
				cout << endl << endl <<  " Fim do atraza tarefas" << endl;
				cout << "DadosTarefasMovidasAuxiliar" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);

				cin >> ParaPrograma;
			}
		}
		if( imprime == 1){
			cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao << "-" << Demanda << "]   MESMO SE atrazar as outra demandas -> Solucao::AdicionaTarefa &&&&&&&&&&&&& " << endl;
		}
		// retorna 0 caso não conseguir atender a demansa em qeustão
		return 0;

	}else{
		//cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema -> Construcao [" << IndiceConstrucaoVaiSerSuprida << "-" << Demanda << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
		// retorna 0 pois a demanda que se quer atender já estiver sido atendida
		return 0;
	}

	//cout << endl << endl << endl << "      <<<<<<<<<<<< Passou por toda a função e não entrou em nada!!! OLHAR ISSO!  -> Solucao::AdicionaTarefa " << endl << endl << endl;
	// retorna 0 pois não encontrou a cosntrução passada
	return 0;
}

// Verifica se consegue atender as demandas da construção
void Procedimento1::VerificaAlocacaoDemandaConstrucao( int IndiceConstrucaoVaiSerSuprida, int &Viabilidade){
	if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].StatusAtendimento < ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDemandas ){
		cout << endl;
		cout << " ##############################################################" << endl;
		cout << "           Não consigo alocar demandas da contrucao " << ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDaConstrucao << endl;
		cout << " ##############################################################" << endl;
		Viabilidade = 0;
	}
}

// executa o procedimento de construção da solução
int Procedimento1::Executa( int TipoOrdenacao){

	int ConstrucaoVaiSerSuprida;
	int IndiceConstrucaoVaiSerSuprida;


	int Demanda;

	int ConstrucaoSelecionada;

	int Viabilidade;
	int PermiteAtendimentoDemanda;

	int paraPrograma;

	Viabilidade = 1;

	int imprime;
	imprime = 1;

	// faz com que nenhuma construção tenha sido avaliada para o atendimento de suas demandas
	ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

	for( int c = 0; c < ConstrucoesInstancia.NumeroConstrucoes; c++ ){
		// Seleciona a construção caso ela já não tiver sido analisada
		ConstrucaoSelecionada = SelecionaConstrucao( ConstrucaoVaiSerSuprida, IndiceConstrucaoVaiSerSuprida);
		if( ConstrucaoSelecionada == 1){
			// marca a construção escolhida como já analisada
			ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoVaiSerSuprida] =  1;
			// Entrar no loop enqaunto tiver demandas a serem atendidas e planatas que ainda puderem atender a demanda
			do{
				// atualiza a demanda que será analisada para ser atendida
				Demanda = ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].StatusAtendimento;
				PermiteAtendimentoDemanda = 0;




				AdicionaTarefa(IndiceConstrucaoVaiSerSuprida,Demanda, TipoOrdenacao  , imprime);





			}while( ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].StatusAtendimento < ConstrucoesInstancia.Construcoes[IndiceConstrucaoVaiSerSuprida].NumeroDemandas && PlantasInstancia.AnalizouTodasPLanats() == 0);
			// verifica se todas as demandas da construção corrente foi atendida
			VerificaAlocacaoDemandaConstrucao(IndiceConstrucaoVaiSerSuprida, Viabilidade);
		}else{
			cout << endl << endl << " &&&&&&&&&&&&&& Nao conseguiu selecionar uma construcao &&&&&&&&&&&&&& " << endl << endl;
		}
	}
	// Calcula o nivel de viabilidade
	ConstrucoesInstancia.CalcularNivelDeInviabilidade();
	if( Viabilidade == 1){
		return 1;
	}else{
		return 0;
	}
}

Procedimento1::~Procedimento1(){

}

#endif /* PROCEDIMENTO1_HPP_ */
