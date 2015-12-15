/*
 * BuscaLocal.hpp
 *
 *  Created on: Dec 15, 2015
 *      Author: mateus.vilela
 */

#ifndef BUSCALOCAL_HPP_
#define BUSCALOCAL_HPP_

#include "Bibliotecas.hpp"


class BuscaLocal{
public:

// estruturas que armazenam os dados da instancia
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	double Makespan;


	BuscaLocal();

	void CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);		// Carrega os dados da instancia e a solução até o momento
	int SelecionaConstrucao( int &ConstrucaoEscolhida, int &IndiceConstrucaoEscolhida);
	void EncontraPlantaMenorDistanciaConstrucao( int c, int& NumPlantaAnalisando, string frase);		// encontra a planta mais perto da construção que ainda não foi analisada

	int AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao , int imprime, string frase);		// função que tenta alocar uma demanda
	double CalculaMakespanSolucoes();				// calcula o makespan
	int ExisteConstrucaoParaRetirar( int IndiceConstrucaoEscolhida, int &ConstrucaoComDeandaRetirar, int &IndiceConstrucaoComDeandaRetirar);

	int BuscaLocalRetiraTarefasUmaConstrucao(int Imprime);

	~BuscaLocal();
};

// construtora da classe
BuscaLocal::BuscaLocal(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
	Makespan = -13;
}


// Carrega os dados da instancia e a solução até o momento
void BuscaLocal::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
}

int BuscaLocal::SelecionaConstrucao( int &ConstrucaoEscolhida, int &IndiceConstrucaoEscolhida ){
	double RankInicial;
	int Ativo;

	// inicia variaveis
	Ativo = 0;
	RankInicial = DBL_MAX;

	// passa por todas as construções
	for( int c = 0; c < NE; c++){
		// seleciona a que tem um rank maior que a selecionada no momento
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			// verifica se a construção ainda pode ser analisada
			if( ConstrucoesInstancia.ConstrucoesAnalizadas[c] == 0){
				// armazena os dados da cosntrução corrente
				ConstrucaoEscolhida = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
				IndiceConstrucaoEscolhida = c;
				RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
				// marca que encontrou uma construção
				Ativo = 1;
			}
		}
	}
	if( Ativo == 1){
		// retorna 1 caso encontrou uma construção
		return 1;
	}else{
		// retorna 0 caso não encontrou uma construção
		return 0;
	}

}

// encontra a planta mais perto da construção que ainda não foi analisada
void BuscaLocal::EncontraPlantaMenorDistanciaConstrucao( int c, int& NumPlantaAnalisando, string frase){
	double DistanciaConstrucaoPlanta;

	// inicializa as variaveis
	NumPlantaAnalisando = -13;
	DistanciaConstrucaoPlanta = DBL_MAX;

	// percorre todas as plantas
	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
			// planta que ainda não foi analisada
			if( PlantasInstancia.PlantasAnalizadas[p] == 0){
				NumPlantaAnalisando = p;
				DistanciaConstrucaoPlanta = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
			}
		}
	}

	// caso naço encontre nenhuma planta
	if(NumPlantaAnalisando == -13){
		cout << endl << endl << endl << frase << endl << endl << endl;
	}
}

// função que tenta alocar uma demanda
int BuscaLocal::AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao , int imprime, string frase){
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
	int c;
	int  p ;

	// Guarda as tarefas movidada no processo de mudar o horario de atendimento de uma demanda anterior visando atender uma posterior
	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;

	// variaveis de controle
	int SituacaoAlocacao;

	// variavel que indica se ira realizar a verificação da solução
	int VerificaViabilidade;
	VerificaViabilidade = 0;

	int ParaPrograma;

	// inicializa os vetores que armazenam os horarios que as plantas podem atender a demanda da construção caso se caia no caso de -2 na Analise da planta. Se é inicializado com os valores maximos de Double
	PlantasInstancia.InicializaVetorHorarioQuePlantaPodeAtender();
	// aloca o indice da construção
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, " <<<<<<<<<<<<<<<<< BuscaLocal::AdicionaTarefa  >>>>>>>>>>>>>>>>>>>>>>>>>>") == 1 ){
		// verifica se a construção já foi atendida em sua totatlidade, cao não entra no if
		if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
			// faz com que nenhuma planta tenha sido analisada até o momento
			PlantasInstancia.InicializaPlantasAnalizadas();
			// só entra no loop enquanto se tem uma planta para analisar
			while( PlantasInstancia.AnalizouTodasPLanats() == 0){
				// encontra a planta mais perto d aconstrução
				EncontraPlantaMenorDistanciaConstrucao(c,  p , "   &&&&&&&&&&&&& Problema em fornecer valor de   p  em adiciona tarefa  ->BuscaLocal::AdicionaTarefa &&&&&&&&&&&&& ");
				// ordena as britadeiras
				PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
				// percorre todos os veículos da planta
				for( int v = 0; v < PlantasInstancia.Plantas[ p ].NumeroVeiculos; v++){
					// inicializa o tempo inicio que a planta corrente ira começar a analise se pode atender a demanda corrente, caso
					if( ( ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[ p ].TempoPlanta ) > PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento ){
						//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela construção.
						HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[ p ].TempoPlanta;
					}else{
						//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela planta.
						HorarioInicioPlanta = PlantasInstancia.Plantas[ p ].TempoMinimoDeFuncionamento;
					}
					// enquanto estiver na janela de tempo possivel para atendimeto se realiza o loop abaixo.
					do{
						// atualiza os horarios na construção e planta
						HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[ p ].TempoPlanta;
						HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
						HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][Demanda];
						HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[ p ].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];

						// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta
						DisponibilidadePlanta = PlantasInstancia.Plantas[ p ].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
						DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
						DisponibilidadeCarreta = PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);

						// caso se puder realizar a terefa se entra nos If
						if( DisponibilidadePlanta == 1){
							if( DisponibilidadeCarreta == 1){
								if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
									// se consegue atender a demanda com essa planta, carreta e nessa construção
									ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(VerificaExistencia, HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[ p ].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[ p ].NumeroDaPlanta, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, DadosTarefasMovidas);
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
											cout <<  "           (-) Caso atrazar da para alocar, demanda em analise [" << Construcao << "-" << Demanda<< "] no horario " << HorarioChegaContrucao << " na planta [" << PlantasInstancia.Plantas[ p ].NumeroDaPlanta << "] no veiculo [" << v << "]" << endl;
										}
									}
								}
							}
						}
						// acrescenta o horario do inicio da planta para se percorrer todos os possiveis horarios de alocação da demanda por essa planta corrente
						HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
					// realiza o loop até que os intervalos de de funcionamento da planta e da construção ainda sejam respeitados
					}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[ p ].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
				}

				// caso a planta não tenha sido assinalada com -2, que ela pode atender a demanda caso atraze as outras demandas anteriores, se marca a planta com 1 para sinalizar que ela não consegue atender a está demanda.
				if (PlantasInstancia.PlantasAnalizadas[ p ] != -2){
					PlantasInstancia.PlantasAnalizadas[ p ] = 1;
				}
			}
			if( imprime == 1){
				cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   sem atrazar as outra demandas -> BuscaLocal::AdicionaTarefa &&&&&&&&&&&&& " << endl;

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
				if ( ConstrucoesInstancia.Construcoes[c].AtrazaDemandasParaAtenderMaster( Demanda, PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeReceberDemanda() - ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas  + IntervaloDeTempo,DadosTarefasMovidasAuxiliar, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, SituacaoAlocacao, TipoOrdenacao, imprime, frase) == 1 ){
					if( imprime == 1){
						cout << endl << endl << "       ******* adicionei demanda [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "] com o processo de atraso " << endl << endl;
						cout << "DadosTarefasMovidasAuxiliar" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
						cin >> ParaPrograma;
					}
					// funde as tarefas adicionadas e retiradas no processo de atraso e as do procedimento corrente
					if( MergeDadosTarefa( DadosTarefasMovidas, DadosTarefasMovidasAuxiliar) == 0 ){
						cout << endl << endl << " <<<<<<<<<<<< Problema em adicionar DadosTarefasMovidasAuxiliar em DadosTarefasMovidas, DadosTarefasMovidasAuxiliar -> BuscaLocal::AdicionaTarefa  [[[" << frase << "]]] >>>>>>>>>>>>> " << endl << endl;
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
					if( ConstrucoesInstancia.ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasAuxiliar, PlantasInstancia ) == 0){
						cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial -> BuscaLocal::AdicionaTarefa" << endl << endl;
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
				cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   MESMO SE atrazar as outra demandas -> BuscaLocal::AdicionaTarefa &&&&&&&&&&&&& " << endl;
			}
			// retorna 0 caso não conseguir atender a demansa em qeustão
			return 0;
		}else{
			cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema -> Construcao [" << c << "-" << Demanda << "] com demanda ja atendida -> BuscaLocal::AdicionaTarefa &&&&&&&&&&&&& " << endl << endl << endl;
			// retorna 0 pois a demanda que se quer atender já estiver sido atendida
			return 0;
		}
	}
	cout << endl << endl << endl << "      <<<<<<<<<<<< Passou por toda a função e não entrou em nada!!! OLHAR ISSO!  -> BuscaLocal::AdicionaTarefa " << endl << endl << endl;
	// retorna 0 pois não encontrou a cosntrução passada
	return 0;

}

// calcula o makespan
double BuscaLocal::CalculaMakespanSolucoes(){
	// calcula o makespan da solução corrente de suas construções
	ConstrucoesInstancia.CalculaMakespansConstrucoes();
	// calcula o makespan da solução corrente de suas plantas
	PlantasInstancia.CalculaMakespanPlantas();
	// calcula o makespan da solução
	Makespan = ConstrucoesInstancia.MakespanConstrucoes + PlantasInstancia.MakespanPLantas;
	return Makespan;

}

int BuscaLocal::ExisteConstrucaoParaRetirar( int IndiceConstrucaoEscolhida, int &ConstrucaoComDeandaRetirar, int &IndiceConstrucaoComDeandaRetirar){
	for( int c = 0; c < NE; c++){
		if( c != IndiceConstrucaoEscolhida ){
			for( int d = 0; d < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; d++){
				if( ConstrucoesInstancia.Construcoes[c].SituacaoRemocao[d] == 0){
					ConstrucaoComDeandaRetirar = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					IndiceConstrucaoComDeandaRetirar = c;
					return 1;
				}
			}
		}
	}
	return 0;
}

int BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao(int Imprime){

	int ConstrucaoEscolhida;
	int IndiceConstrucaoEscolhida;

	int ConstrucaoComDeandaRetirar;
	int IndiceConstrucaoComDeandaRetirar;
	int DemandaRetirar;

	vector < DadosTarefa > DadosTarefasMovidasConstrucaoEscolhida;
	vector < DadosTarefa > DadosTarefasMovidasAdicionaTarefaDeslocada;

	double MakespanAnterior;


	if( ConstrucoesInstancia.Construcoes.size() > 1){
		// Faz com que nenhuma construção tenha sido retirada no procedimento
		ConstrucoesInstancia.InicializaConstrucoesAnalizadas();

		MakespanAnterior = CalculaMakespanSolucoes();

		while( VerificaSeTemUmValorVetorInt( 0, ConstrucoesInstancia.ConstrucoesAnalizadas ) == 1){
			// reinicia o estado de deslocamento e remoção de todas as demandas de todas as construções
			ConstrucoesInstancia.ReiniciaTarefasRetiradas();


			if( SelecionaConstrucao( ConstrucaoEscolhida, IndiceConstrucaoEscolhida) == 0){
				cout << endl << endl << "       >>>>>>>>>> Problema! Não encontrou uma construção para ser analisada na busca local! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
			}

			if( Imprime == 1){
				cout << endl <<  " Escolheu a construção [" << ConstrucaoEscolhida << "] para retirar suas demandas " << endl ;
			}

			if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoEscolhida].DeletaTarefas(0, 0,DadosTarefasMovidasConstrucaoEscolhida, PlantasInstancia) == 0){
				cout << endl << endl << "       >>>>>>>>>> Problema! Não consegui deletar todas as demandas da construção [" << ConstrucaoEscolhida << "] ! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao" << endl << endl;
			}

			while( ExisteConstrucaoParaRetirar( IndiceConstrucaoEscolhida, ConstrucaoComDeandaRetirar, IndiceConstrucaoComDeandaRetirar) == 1 ){



				if( CalculaMakespanSolucoes() < MakespanAnterior ){
					// retorna um caso consiga melhorar a solução
					return 1;
				}
			}

			ConstrucoesInstancia.ConstrucoesAnalizadas[IndiceConstrucaoEscolhida] = 1;

			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia,0);

		}
		// retorna zero caso não consiga melhorar a solução
		return 0;
	}else{
		if( Imprime == 1){
			cout << endl << endl << "       >>>>>>>>>>>>>>>>>>>>> Não possui construções suficientes para realizar este procedimento! -> BuscaLocal::BuscaLocalRetiraTarefasUmaConstrucao <<<<<<<<<<<<<<<<<<< " << endl << endl;
		}
	}
}

BuscaLocal::~BuscaLocal(){

}


#endif /* BUSCALOCAL_HPP_ */
