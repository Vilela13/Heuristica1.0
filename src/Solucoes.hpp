/*
 * Solucoes.hpp
 *
 *  Created on: Sep 11, 2015
 *      Author: mateus.vilela
 */

#ifndef SOLUCOES_HPP_
#define SOLUCOES_HPP_

#include "Bibliotecas.hpp"
#include "DadosTarefa.hpp"
#include "FuncoesSolucoes.hpp"

class Solucao{
public:
	Solucao();

// estruturas que armazenam os dados da instancia
	int NP;
	ConjuntoPlantas PlantasInstancia;
	int NE;
	ConjuntoConstrucoes ConstrucoesInstancia;
	int NV;
	double Velocidade;
	double TempoDeVidaConcreto;

	double Makespan;

	void CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC);		// Carrega os dados da instancia e a solução até o momento
	void EncontraPlantaMenorDistanciaConstrucao(int c, int& NumPlantaAnalisando, string frase);											// encontra a planta mais perto da construção que ainda não foi analisada

	void Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes);									// imprime os dados da solução

	int DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas);					// deleta demandas atendidas na construção após certa demanda que é passada com parametro
	int AdicionaTarefa(int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao , string frase);		// função que tenta alocar uma demanda

	int ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia,  int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao);				// Tenta alocar uma demanda que não era alocada anteriormente
	void ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao);						// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior

	int ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas);		// readiciona tarefas deletadas e deleta tarefas adicionadas visando restaurar a configuração inicial da solução

	void ProcessoViabilizacao1(int );


	// M###################################################################################################
/*
	int SelecionaConstrucao(int&, int&, vector < int >);
	int SelecionaPlanta(int&, int&, int, vector < int >);

	int  ProcuraConstrucaoNaoAtendida(int&, int&);
	void AlocaTempoSaiDaPlanta(int , vector < double >&, int);
	int DeletaTarefasAposTempoSaiPlanta(vector < double >&, vector < DadosTarefa >&,  int );

	void SinalizaTarefaAdicionadaInicialmente( int, int, int);
	int SelecionaCarreta(int, int, int, int, vector < DadosTarefa >&, int);
	int SelecionaCarretaComHoraInicio(double, int, int, int, int, vector < DadosTarefa > &, int);

	int ColocarTarefaAtrazandoAsOutras(int , int , double, vector < DadosTarefa > &, int, int);

	void ProcessoViabilizacao2(int);
*/

	~Solucao();
};

// construtora da classe
Solucao::Solucao(){
	NP = -13;
	NE = -13;
	NV = -13;
	Velocidade = -13;
	TempoDeVidaConcreto = -13;
	Makespan = -13;
}

// Carrega os dados da instancia e a solução até o momento
void Solucao::CarregaSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	NP = np;
	PlantasInstancia = Plantas;
	NE = ne;
	ConstrucoesInstancia = Construcoes;
	NV = nv;
	Velocidade = v;
	TempoDeVidaConcreto = TDVC;
}

// encontra a planta mais perto da construção que ainda não foi analisada
void Solucao::EncontraPlantaMenorDistanciaConstrucao( int c, int& NumPlantaAnalisando, string frase){
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


// imprime os dados da solução
void Solucao::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes ){
	int VerificaViabilidade;
	VerificaViabilidade = 1;

	// Imprime os dados das plantas
	if( ImprimePlanta == 1 ){
		PlantasInstancia.Imprime(1,1);
	}
	// Imprime os dados das construções
	if( ImprimeConstrucao == 1){
		ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
	}
	// imprime a situação das entregas nas construções
	if( IntervalosRespeitadosConstrucaoes == 1){
		ConstrucoesInstancia.VerificaIntervaloContrucoes();
	}
}


// deleta demandas atendidas na construção após certa demanda que é passada com parametro
int Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao(int VerificaExistencia, int Construcao, int Demanda, vector < DadosTarefa >& DadosTarefasMovidas){
	int c;

	// verifica se a construção passada existe
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, " -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao" ) == 1){
		// deleta demandas que estavam alocadas apos a demnada passada, e inclusive a demanda passada
		if( ConstrucoesInstancia.Construcoes[c].DeletaTarefas( VerificaExistencia, Demanda, DadosTarefasMovidas, PlantasInstancia) == 0 ){
			cout << endl << endl << "   problema em retirar tarefas -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao " << endl << endl;
			return 0;
		}
		//cout << endl << endl;
		//ConstrucoesInstancia.Construcoes[c].ImprimeContrucao();

		//consegui retirar as demandas
		return 1;
	}
	cout << endl << endl << " <<<<<<<<<< Não encontrei a construção [" << Construcao << "] passada -> Solucao::DeletaAlocacaoTarefasPosterioresMesmaConstrucao  >>>>>>>>>>>> "<< endl << endl;
	return 0;

}

// função que tenta alocar uma demanda
int Solucao::AdicionaTarefa( int VerificaExistencia, int Construcao, int Demanda , vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRemocao, int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao , string frase){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	int c;
	int NumPlantaAnalisando;

	int ParaPrograma;

	// Guarda as tarefas movidada no processo de mudar o horario d eatendimento de uma demanda anterior visando atender uma posterior
	vector < DadosTarefa > DadosTarefasMovidasAuxiliar;

	int SituacaoAlocacao;

	int VerificaViabilidade;
	VerificaViabilidade = 0;

// inicializa os vetores que armazenam os horarios que as palnats podem atender a demanda da construção caso se caia no caso de -2 na Analise da planta. Se é inicializado com os valores maximos de Double
	PlantasInstancia.InicializaVetorHorarioQuePlantaPodeAtender();

// aloca o indice da planta
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, " <<<<<<<<<<<<<<<<< Solucao::AdicionaTarefa  >>>>>>>>>>>>>>>>>>>>>>>>>>") == 1 ){

		// verifica se a construção já foi atendida em sua totatlidade, cao não entra no if
		if ( ConstrucoesInstancia.Construcoes[c].NumeroDemandas > ConstrucoesInstancia.Construcoes[c].StatusAtendimento){
			// faz com que nenhuma planta tenha sido analisada até o momento
			PlantasInstancia.InicializaPlantasAnalizadas();

			// só entra no loop enquanto se tem uma planta para analisar
			while( PlantasInstancia.AnalizouTodasPLanats() == 0){
				// encontra a planta mais perto d aconstrução
				EncontraPlantaMenorDistanciaConstrucao(c, NumPlantaAnalisando, "   &&&&&&&&&&&&& Problema em fornecer valor de  NumPlantaAnalisando em adiciona tarefa  ->Solucao::AdicionaTarefa &&&&&&&&&&&&& ");
				// ordena as britadeiras
				PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);
				// percorre todos os veículos da planta
				for( int v = 0; v < PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroVeiculos; v++){

					// inicializa o tempo inicio que a planta corrente ira começar a analise se pode atender a demanda corrente, caso
					if( ( ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta ) > PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento ){
						//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela construção.
						HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
					}else{
						//caso o tempo de inicio do carregamento da britadeira na plantar for restrito pela planta.
						HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMinimoDeFuncionamento;
					}

					// enquanto estiver na janela de tempo possivel para atendimeto se realiza o loop abaixo.
					do{
						// atualiza os horarios na construção e planta
						HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].TempoPlanta;
						HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
						HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][Demanda];
						HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[NumPlantaAnalisando].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];

						// verifica se é possivel realizar o atendiemnto da demanda tanto na planta, construção e carreta
						DisponibilidadePlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
						DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);
						DisponibilidadeCarreta = PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);

						// caso se puder realizar a terefa se entra nos If
						if( DisponibilidadePlanta == 1){
							if( DisponibilidadeCarreta == 1){
								if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
									// se consegue atender a demanda com essa planta, carreta e nessa construção
									ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(VerificaExistencia, HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[NumPlantaAnalisando].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[NumPlantaAnalisando].NumeroDaPlanta, SituacaoDemanda, SituacaoRemocao, PlantasInstancia, DadosTarefasMovidas);
									// se dieminui o nível de iniviabilidade da solução
									ConstrucoesInstancia.NivelDeInviabilidade = ConstrucoesInstancia.NivelDeInviabilidade - 1;
									// retorna 1 indicando que se foi possivel alocar a demanda corrente
									return 1;
								}else{
									// caso se poss a atender a demanda se atender a demanda anterior em um horario diferente
									if( DisponibilidadeConstrucao == -2){
										cout <<  "                     Caso atrazar da para alocar, demanda em analise [" << Construcao << "-" << Demanda<< "] no horario " << HorarioChegaContrucao << endl;
										// caso for  aprimeira vez que se verifique a valor -2 para a DisponibilidadeConstrução, se atualiza os hoarios iniciais tanto na planta e na construção que a planta corrente pode vir a atender a construção
										if( PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] == 0){
											PlantasInstancia.HorarioQuePlantaPodeAtender[NumPlantaAnalisando] = HorarioInicioPlanta;
											PlantasInstancia.HorarioQueConstrucaoPodeAtenderDemanda[NumPlantaAnalisando] = HorarioChegaContrucao;
										}
										// se atualiza a situação da planta corrente com -2 e coloca o tempo de inicio da planta como o tempo maximo de funcionamento da planta para se forçar sair do loop do while
										PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] = -2;
										HorarioInicioPlanta = PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento;
									}
								}

							}
						}
						// acrescenta o horario do inicio da planta para se percorrer todos os possiveis horarios de alocação da demanda por essa planta corrente
						HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
					// realiza o loop até que os intervalos de de funcionamento da planta e da construção ainda sejam respeitados
					}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[NumPlantaAnalisando].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
				}

				// caso a planta não tenha sido assinalada com -2, que ela pode atender a demanda caso atraze as outras demandas anteriores, se marca a planta com 1 para sinalizar que ela não consegue atender a está demanda.
				if (PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] != -2){
					PlantasInstancia.PlantasAnalizadas[NumPlantaAnalisando] = 1;
				}
			}


			cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   sem atrazar as outra demandas -> Solucao::AdicionaTarefa &&&&&&&&&&&&& " << endl;

			cout << endl << endl <<  " Imprimir SituacaoPlantaAtenderCasoAtrazar" << endl;
			ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
			ImprimeVetorDouble( PlantasInstancia.HorarioQuePlantaPodeAtender);
			ImprimeVetorDouble( PlantasInstancia.HorarioQueConstrucaoPodeAtenderDemanda);
			cin >> ParaPrograma;

			// caso não se tenha conseguido atender a demanda corrente, se verifica se tem alguma planta que pode atender a demanda caso se mude o horario de atendiemnto das outras demandas posteriores a está. Caso se possa, se entra no if e tenta mudar o horario das demandas anteriores para se tentar atender a demanda corrente
			if( PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() == 1){
				DadosTarefasMovidasAuxiliar.clear();


				/* problema aqui. falta adicionar a ultima tarefa (a demanda corrente). só adiciona até uma antes dela. */



				cout << endl << endl << "      Função que atraza demandas - horario que pode atender construção = " << PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeAtenderDemanda() << endl << endl;
	// função que realiza o atrazo das tarefas para atender uma demanda anterior


				if ( ConstrucoesInstancia.Construcoes[c].AtrazaDemandasParaAtenderMaster( Demanda, PlantasInstancia.RetornaMenorHorarioQueConstrucaoPodeAtenderDemanda() - ConstrucoesInstancia.Construcoes[c].TempoMaximoEntreDescargas + IntervaloDeTempo,DadosTarefasMovidasAuxiliar, PlantasInstancia, SituacaoAlocacao, TipoOrdenacao, frase) == 1 ){
					cout << endl << endl << "       ******* adicionei demanda [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "] com o processo de atrazo " << endl << endl;
					cout << "DadosTarefasMovidasAuxiliar" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
					cin >> ParaPrograma;

					if( MergeDadosTarefa( DadosTarefasMovidas, DadosTarefasMovidasAuxiliar) == 0 ){
						cout << endl << endl << " <<<<<<<<<<<< Problema em adicionar DadosTarefasMovidasAuxiliar em DadosTarefasMovidas, DadosTarefasMovidasAuxiliar -> Solucao::AdicionaTarefa  [[[ frase ]]] >>>>>>>>>>>>> " << endl << endl;
					}

					cout << endl << endl << "Deleta DadosTarefasMovidasAuxiliar" << endl << endl;

					cout << "DadosTarefasMovidasAuxiliar" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);
					cin >> ParaPrograma;

					return 1;
				}else{
					if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidasAuxiliar ) == 0){
						cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
					}
				}

				DadosTarefasMovidasAuxiliar.clear();

				cout << endl << endl <<  " Fim do atraza tarefas" << endl;
				cout << "DadosTarefasMovidasAuxiliar" << endl;
				ImprimeVetorDadosTarefa( DadosTarefasMovidasAuxiliar);

				ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);

				cin >> ParaPrograma;


			}
			// retorna 0 caso não conseguir atender a demansa em qeustão
			cout << "   &&&&&&&&&&&&& Nao consigo atender contrucao [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << Demanda << "]   MESMO SE atrazar as outra demandas -> Solucao::AdicionaTarefa &&&&&&&&&&&&& " << endl;
			return 0;

		}else{
			cout << endl << endl << endl << "   &&&&&&&&&&&&& Problema -> Construcao [" << c << "-" << Demanda << "] com demanda ja atendida -> Solucao::AdicionaTarefa&&&&&&&&&&&&& " << endl << endl << endl;
			return 0;
		}

	}
	cout << endl << endl << endl << "      <<<<<<<<<<<< Passou por toda a função e não entrou em nada!!! OLHAR ISSO!  -> Solucao::AdicionaTarefa " << endl << endl << endl;
	return 0;

}

// Tenta alocar uma demanda que não era alocada anteriormente
int Solucao::ProcessoParaAlocarTarefaNaoAtendida(int VerificaExistencia, int Construcao, int Demanda, int& NovaTarefaAlocadaConstrucao , int& NovaTarefaAlocadaDemanda ,  vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda, int SituacaoRetirada,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao){
	int c;

	// variavel que guarda a situação da demanda corrente. se ela foi alocada ou não
	int Alocou;
	Alocou = 0;

	// verifica se a construção passada existe na instancia
	if( ConstrucoesInstancia.RetornaIndiceConstrucao(Construcao, c, "  <<<<    Solucao::ProcessoParaAlocarTarefaNaoAtendida  >>>>>") == 0){
		return -1;
	}

	// percorre todas as construções
	for( unsigned int contrucoes = 0; contrucoes < ConstrucoesInstancia.Construcoes.size(); contrucoes++){
		// percorre todas as demandas da construção corrente
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[contrucoes].NumeroDemandas; demandas++){
			// não tenta aloca demandas da construçãoq ue teve uma demanda retirada anteriormente
			if( contrucoes != c){
				// verifica se a demnada corrente ainda não foi alocada
				if( ConstrucoesInstancia.Construcoes[contrucoes].SituacaoDemanda[demandas] == 0){
					//cout << "   tenta alocar [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "]  -> Solucao::ProcessoParaAlocarTarefa";

					// tenta alocar a demanda
					Alocou = AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, SituacaoRetirada, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, "Solucao::ProcessoParaAlocarTarefaNaoAtendida");
					//caso alocar a demanda
					if( Alocou == 1){
						//cout << " => Alocou [" << ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao << "-" << demandas << "] -> Solucao::ProcessoParaAlocarTarefa" << endl;

						// retorna a cosntruçãoq ue teve uma demanda alocada
						NovaTarefaAlocadaConstrucao = ConstrucoesInstancia.Construcoes[contrucoes].NumeroDaConstrucao;
						// retorna a demanda adicionada
						NovaTarefaAlocadaDemanda = demandas;
						// sai da função e avisa que consegui alocar uma demanda
						return 1;
					}else{
						//cout << " => Falhou! " << endl;
					}
				}
			}
		}
	}
	// não conseguir alocar a demanda da função, retorna 0
	return 0;
}

// após adicionar uma demanda que não era alocada antes, se tenta readicionar as demandas retiradas na construção anterior
void Solucao::ReadicionaTarefas(int VerificaExistencia, int construcao, vector < DadosTarefa > &DadosTarefasMovidas, int SituacaoDemanda,int RealizaProcessoDeAtrazarTarefas, int TipoOrdenacao){
	int c;

	// verifica se existe a construção passada
	if( ConstrucoesInstancia.RetornaIndiceConstrucao( construcao, c, " <<<<<<<<<<<<<<<<<<<<<<< Solucao::ReadicionaTarefas >>>>>>>>>>>>>>>>>>>>") == 1 ){
		// percorre as demanda da cosntrução
		for ( int demandas = 0; demandas < ConstrucoesInstancia.Construcoes[c].NumeroDemandas; demandas++){
			// caso a demanda corrente não tenha sido atendida
			if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[demandas] == 0){
				//cout << " entrei " << endl;

				// readiciona a demanda corrente na construção
				if( AdicionaTarefa(VerificaExistencia, ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao,demandas, DadosTarefasMovidas, SituacaoDemanda, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao, "Solucao::ReadicionaTarefas") == 1 ){
					cout << " adicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
				}else{
					cout << " Nao readicionou [" << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << "-" << demandas << "]" << endl;
					// caso não se consiga readicionar uma demanda, se para o programa
					return;
				}
			}
		}
	}

}

// readiciona tarefas deletadas e deleta tarefas adicionadas visando restaurar a configuração inicial da solução
int Solucao::ReadicionaDeletaTarefasApartirDeDados( vector < DadosTarefa > DadosTarefasMovidas){
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




void Solucao::ProcessoViabilizacao1(int TipoOrdenacao){

	int InviabilidadeSolucaoAnterior;
	bool ExisteTarefa;
	bool TarefaDeletada;
	int NovaTarefaAlocadaConstrucao;
	int NovaTarefaAlocadaDemanda;
	bool TarefaAlocada;
	int Readicionou;
	int ConstrucaoAnalisandoRetirada;
	int DemandaAnalisandoRetirada;

	int PararPrograma;

	vector < DadosTarefa > DadosTarefasMovidas;
	vector < DadosTarefa > AuxiliarLixo;

	// variavel que indica se deve imprimir o que esta acontecendo
	int Imprime;

	Imprime = 0;

	// variavel que controla se deve realizar o processo de atrazo de tarefas para tentar atrazar uma outra mais posterior que pode ser atendida caso se atraze as tarefas anteriores a ela
	int RealizaProcessoDeAtrazarTarefas;

	RealizaProcessoDeAtrazarTarefas = 1;

	int VerificaViabilidade;
	VerificaViabilidade = 0;



	//ConstrucoesInstancia.ImprimeContrucoes();
	//PlantasInstancia.Imprime(1,1);

	// guarda o nivel de inviabilidade da solução anterior para ser utilizado posteriormente para ver se a solução melhorou
	InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
	// Encontra primeira tarefa que pode ser retirada
	ExisteTarefa = ConstrucoesInstancia.ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, Imprime);
	if( Imprime == 1){
		cin >> PararPrograma;
	}


	// enquanto existir uma tarefa que pode ser retirada
	while( ExisteTarefa == 1 && ConstrucoesInstancia.NivelDeInviabilidade > 0){
		if( Imprime == 1){
			cout << endl << endl << "        Inicia procediemnto " << endl << endl;
		}
		// limpa o vetor de dados que foram removidos no processo
		DadosTarefasMovidas.clear();
		// deleta demanda alocada e as demandas posteriores a esta nesta construção corrente
		TarefaDeletada = DeletaAlocacaoTarefasPosterioresMesmaConstrucao(0, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, DadosTarefasMovidas);	// Deleta tarefa
		// calcula o nível de iniviabilidade da solução
		ConstrucoesInstancia.CalcularNivelDeInviabilidade();

		if( Imprime == 1){
			cout << endl << endl << "    deleta tarefas apos a demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;
			cout << "DadosTarefasMovidas" << endl;
			ImprimeVetorDadosTarefa( DadosTarefasMovidas);
			ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
			//PlantasInstancia.Imprime(1,1);
			cin >> PararPrograma;
		}


		// caso conseguiu deletar a demanda e suas posteriores entra no if
		if ( TarefaDeletada == 1){
			// Aloca valores aos inidices da construção e da demanda que não era atendida antes  equa passara a ser atendia
			AlocaValoresIniciaisIndices( NovaTarefaAlocadaConstrucao, NovaTarefaAlocadaDemanda);

			//ConstrucoesInstancia.ImprimeContrucoes();

			// tenta alocar a demanda que não era atendida antes


			TarefaAlocada = ProcessoParaAlocarTarefaNaoAtendida(0, ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada , NovaTarefaAlocadaConstrucao , NovaTarefaAlocadaDemanda,  DadosTarefasMovidas, 1, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);
			// calcula o nível de iniviabilidade da solução
			ConstrucoesInstancia.CalcularNivelDeInviabilidade();

			// caso conseguir alocar a demanda que não era atendida antes
			if( TarefaAlocada == 1){

				if( Imprime == 1){
					cout << endl << endl << "         Aloca demanda não atendida anteriormente [ " << NovaTarefaAlocadaConstrucao << "-" << NovaTarefaAlocadaDemanda << "]" << endl << endl;
					cout << endl << "  tenta alocar tarefa" << endl;
					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
					//PlantasInstancia.Imprime(1,1);
					cin >> PararPrograma;
				}

				// tento readicionar as demandas que foram retiradas
				ReadicionaTarefas(0, ConstrucaoAnalisandoRetirada,DadosTarefasMovidas, 1, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);
				// calcula o nível de iniviabilidade da solução
				ConstrucoesInstancia.CalcularNivelDeInviabilidade();

				if( Imprime == 1){
					cout << endl << endl << "         Readiciona tarefas deletadas " << endl << endl;
					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);
					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
					//PlantasInstancia.Imprime(1,1);
					cin >> PararPrograma;
				}

				// verifica se melhorou a solução
				if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
					if( Imprime == 1){
						cout << endl << "  								!!!!!!!!! Melhorou !!!!!!!!!!! "  << endl;
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
						ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}

					// marca a demanda retirada
					ConstrucoesInstancia.MarcaTarefaNaoRemovidaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, "ProcessoViabilizacao1" );
					DadosTarefasMovidas.clear();

				}else{
					if( Imprime == 1){
						cout << endl << "  								!!!!!!!!! Nao melhorou !!!!!!!!!!! " << endl;
						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
						ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}

					if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas ) == 0){
						cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
					}
					DadosTarefasMovidas.clear();

					ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);

					if( Imprime == 1){
						cout << endl << endl << "          Deleta tarefas adicionadas, readiciona as deletadas e marca demanda [" << ConstrucaoAnalisandoRetirada << "-" << DemandaAnalisandoRetirada << "]" << endl << endl;

						cout << "DadosTarefasMovidas" << endl;
						ImprimeVetorDadosTarefa( DadosTarefasMovidas);
						ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
						//PlantasInstancia.Imprime(1,1);

						cin >> PararPrograma;
					}
				}
			}else{


				if( ReadicionaDeletaTarefasApartirDeDados(  DadosTarefasMovidas ) == 0){
					cout << endl << endl << "   problema em adicionar e deletar tarefas para se retornar a solução inicial ->  Solucao::ProcessoViabilizacao1" << endl << endl;
				}
				DadosTarefasMovidas.clear();

				ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 1);

				if( Imprime == 1){
					cout << endl << endl << "            Nao consegui adicionar nova tarefa - readiciona tarefas e marca terafa como removida" << endl << endl;

					cout << "DadosTarefasMovidas" << endl;
					ImprimeVetorDadosTarefa( DadosTarefasMovidas);

					ConstrucoesInstancia.ImprimeContrucoes(PlantasInstancia, VerificaViabilidade);
					//PlantasInstancia.Imprime(1,1);

					cin >> PararPrograma;
				}
			}
		}else{
			 cout << endl << endl << endl << "   #######################  Tarefa não deletada ######################## " << endl << endl << endl;
		}

		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;
		ExisteTarefa = ConstrucoesInstancia.ConstrucaoTemTarefaParaRemover(ConstrucaoAnalisandoRetirada, DemandaAnalisandoRetirada, 0);

		//cout << endl << endl << " ExisteTarefa = " << ExisteTarefa << " ConstrucoesInstancia.NivelDeInviabilidade = " << ConstrucoesInstancia.NivelDeInviabilidade << endl << endl;

	}

}

//  Mudando
/*
int Solucao::SelecionaConstrucao( int &ConstrucaoParaAtender, int &ConstrucaoParaAtenderIndice, vector < int > ConstrucoesAnalizadas){
	double RankInicial;
	int Ativo;

	Ativo = 0;
	RankInicial = DBL_MAX;


	for( int c = 0; c < NE; c++){
		if ( RankInicial > ConstrucoesInstancia.Construcoes[c].RankTempoDemandas){
			if(ConstrucoesInstancia.Construcoes[c].StatusAtendimento < ConstrucoesInstancia.Construcoes[c].NumeroDemandas){
				if( ConstrucoesAnalizadas[c] == 0){
					ConstrucaoParaAtender = ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao;
					ConstrucaoParaAtenderIndice = c;
					RankInicial = ConstrucoesInstancia.Construcoes[c].RankTempoDemandas;
					Ativo = 1;
				}
			}
		}
	}
	if( Ativo == 1){
		return 1;
	}else{
		return 0;
	}
}

int Solucao::SelecionaPlanta( int &PlantaAtender, int &PlantaAtenderIndice, int c, vector < int > PlantasAnalizadas ){
	double DistanciaConstrucaoPlanta;
	int Ativo;

	Ativo = 0;
	DistanciaConstrucaoPlanta = DBL_MAX;

	for( int p = 0; p < NP; p++){
		if( DistanciaConstrucaoPlanta > ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia){
			if( PlantasAnalizadas[p] == 0){
				PlantaAtenderIndice = p;
				PlantaAtender = PlantasInstancia.Plantas[p].NumeroDaPlanta;
				DistanciaConstrucaoPlanta = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[p].Distancia;
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

int  Solucao::ProcuraConstrucaoNaoAtendida(int &ConstrucaoNaoAtendida, int &DemandaNaoAtendida){

	// Encontra a construção que possui a menor distancia a uma planta dentre todas as construções com demandas não atendidas

	int ConstrucaoTemporario;
	int IndiceConstrucaoTemporario;
	int DemandaTemporaria;

	ConstrucaoTemporario = -13;
	DemandaTemporaria = -13;

	double DistanciaPlantaTemporaria;

	DistanciaPlantaTemporaria = DBL_MAX;

	for ( int i = 0; i < NE; i++){
		for ( int d = ConstrucoesInstancia.Construcoes[i].NumeroDemandas - 1; d >= 0  ; d--){
			if( ConstrucoesInstancia.Construcoes[i].SituacaoDemanda[d] == 0){
				for ( int p = 0; p < NP; p++){
					if( DistanciaPlantaTemporaria > ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[p].Distancia){
						DistanciaPlantaTemporaria = ConstrucoesInstancia.Construcoes[i].DistanciaPlantas[p].Distancia;
						ConstrucaoTemporario = ConstrucoesInstancia.Construcoes[i].NumeroDaConstrucao;
						IndiceConstrucaoTemporario = i;
						DemandaTemporaria = d;
					}
				}
			}
		}
	}

	if( ConstrucaoTemporario == -13 || DemandaTemporaria == -13 ){
		return 0;
	}
	ConstrucaoNaoAtendida = ConstrucaoTemporario;
	DemandaNaoAtendida = DemandaTemporaria;

	return 1;
}

void Solucao::AlocaTempoSaiDaPlanta(int IndiceConstrucaoNaoAtendida, vector < double > &TempoSaiPlanta, int Imprime){

// Aloca o tempo inicial que se pode sair uma carreta da planta para suprir a construção.

	for( int p = 0; p < NP; p++){
		if( PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento  < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia){
			TempoSaiPlanta[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].TempoMinimoDeFuncionamento - ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].DistanciaPlantas[ p ].Distancia;
		}else{
			TempoSaiPlanta[p] = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
		}
	}

// Aloca o tempo inicial que se pode sair da planta como sendo o tempo da ultima carreta que realizou o ultimo carregamento naquela planta para está construção
	if( ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento > 0){
		for( int d = 0; d < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].StatusAtendimento; d++ ){
			for( int p = 0; p < NP; p++){
				if( TempoSaiPlanta[p] < ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia){
					TempoSaiPlanta[p] = ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].Descarregamentos[d].HorarioInicioDescarregamento - ConstrucoesInstancia.Construcoes[IndiceConstrucaoNaoAtendida].DistanciaPlantas[p].Distancia;
				}
			}
		}
	}

// Imprimir o conteudo do vetor Tempo de saida da planta
	if( Imprime == 1){
		for( int p = 0; p < NP; p++){
			cout << " TempoSaiPlanta[" << p << "] = " << TempoSaiPlanta[p] << endl;
		}
	}
}

int Solucao::DeletaTarefasAposTempoSaiPlanta(vector < double > &TempoSaiPlanta, vector < DadosTarefa > &DadosTarefasDesalocadas,  int Imprime){

	int TarefaDeletada;
	int PlantaAux;
	double DistanciaAux;
	int Ativa;

	Ativa = 0;

	//cout << endl << endl << "   Galo 1" << endl << endl;

	for( int c = 0; c < NE; c++){
		//cout << endl << endl << "  Construcao " << c << endl << endl;
		for( int d = ConstrucoesInstancia.Construcoes[c].StatusAtendimento - 1; d >= 0 ; d--){
			//cout << " demanda = " << d << endl;
			PlantaAux = ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor;
			DistanciaAux = ConstrucoesInstancia.Construcoes[c].DistanciaPlantas[ PlantaAux ].Distancia;


			if( ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento - DistanciaAux > TempoSaiPlanta[PlantaAux]){
				if( Imprime == 1){
					cout << "	-> Planta = " << PlantaAux << "   Construcao = " << ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " (" << c << ")" << endl;
					ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].Imprime();
				}
				TarefaDeletada = ConstrucoesInstancia.Construcoes[c].DeletaAtividadeLocomovendoAsOutrasTarefasSalvandoDados( ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioInicioDescarregamento, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].HorarioFinalDescarregamento, d,  ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumPlantaFornecedor, ConstrucoesInstancia.Construcoes[c].Descarregamentos[d].NumCarretaUtilizada,PlantasInstancia,  DadosTarefasDesalocadas);
				ConstrucoesInstancia.NivelDeInviabilidade++;
				//cout << endl << endl << "   Galo 2" << endl << endl;

				if( TarefaDeletada == 1){
					Ativa = 1;
					if( Imprime == 1 ){
						cout << "                  Tarefa deletada " << endl << endl;
					}
				}
			}
		}
	}

	if( Ativa == 1){
		return 1;
	}
	return 0;

}

void Solucao::SinalizaTarefaAdicionadaInicialmente( int TarefaAdicionada, int IndiceConstrucaoNaoAtendida, int DemandaNaoAtendida){		// Sinalisa se a tarefa foi antendida colocando os valores 2 em sua situação remoção. Caso não, a situação tem valor -1 e a remoção 3.
		if( TarefaAdicionada == 1){
			//cout << "                  Tarefa adicionada    -> Solucao::SinalizaTarefaAdicionadaInicialmente" << endl << endl;
			ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] = 2;
			ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDaConstrucao, DemandaNaoAtendida, 2);		// coloca o valor 2 em sua situação remoção
		}else{
			//cout << "                  Tarefa NAO adicionada " << endl << endl;
			for( int d = DemandaNaoAtendida; d < ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDemandas; d++){
				ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ d ] = -1;									// marca com -1, já tento alocar mas não conseguiu
				ConstrucoesInstancia.MarcaTarefaDeletadaNoVetor(ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].NumeroDaConstrucao, d, 3);		// marca com 3 a situação remoção
			}
		}
}

int Solucao::SelecionaCarreta(int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas, int TipoOrdenacao ){		//verifica se é possivel alocar a demanda da construção pela planta em questão
// dados a armazenar
	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;
// decisões a tomar
	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[NumeroDemanda] == 0){		// verifica se a demanda não foi atendida ainda
		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);			// ordena os veiculos da planta que serão analisados
		for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){
			// fixa o horario inicial que se inicia o carregamento na planta
			if( (ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta) > PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = ConstrucoesInstancia.Construcoes[c].TempoMinimoDeFuncionamento - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta;
			}else{
				HorarioInicioPlanta = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
			}

			do{
				// aloca valores dos horarios
				HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[p].TempoPlanta;
				HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][NumeroDemanda];
				HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				// verifica a viabilidades da alocação que está sendo analisada no momento
				DisponibilidadePlanta = PlantasInstancia.Plantas[p].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeCarreta = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
				DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);

				if( DisponibilidadePlanta == 1){		// possivel o atendimento pela planta
					if( DisponibilidadeCarreta == 1){		// possivel o atendimento pelo carregamento
						if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){	// Possivel alocação pela construção, os números 1, 2 e 3 são referentes a posição onde a demanda será alocada em relação as outras demandas já alocadas na construção
							ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[p].NumeroDaPlanta,  1,0, PlantasInstancia, DadosTarefasAdicionadas);	// aloca a demanda tanto no veículo, construção e planta
							return 1;
						}
						if( DisponibilidadeConstrucao == -2){	// sinaliza que no momento não é possivel alocar a demanda, mas caso atrazar as outras demandas já atendidas talvéz seja possivel atender essa demanda
							return -2;
						}
					}
				}
				HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;	// acrescenta o horario que se ira analizar a colocação da demanda
			}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);		// verifica se violou os tempos maximos de funcionamento tanto da construção ou da planta. caso se violar ele sai do loop e informa que a demanda em analise não pode ser atendida pela planat em analise
		}
		return 0;
	}else{
		cout << endl << endl << " Está tentando alocar uma demanda que já foi alocada -> construção " <<  ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao << " [" << c << " - " << NumeroDemanda << "] " << endl << endl;
		return -13;
	}
}

int Solucao::SelecionaCarretaComHoraInicio( double HoraInicio, int c, int p, int  NumeroDemanda, int SituacaoDemanda, vector < DadosTarefa > &DadosTarefasAdicionadas , int TipoOrdenacao){

	double HorarioInicioPlanta;
	double HorarioSaiDaPlanta;
	double HorarioRetornaPlanta;
	double HorarioChegaContrucao;
	double HorarioSaiConstrucao;

	int DisponibilidadePlanta;
	int DisponibilidadeConstrucao;
	int DisponibilidadeCarreta;

	//int ParaPrograma;

	if( ConstrucoesInstancia.Construcoes[c].SituacaoDemanda[NumeroDemanda] == 0){

		PlantasInstancia.Plantas[p].VeiculosDaPlanta.OrdenaCarretasPorNumeroDeTarefasRealizadas(TipoOrdenacao);

		for( int v = 0; v < PlantasInstancia.Plantas[p].NumeroVeiculos; v++){

			if( (HoraInicio - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta) > PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento){
				HorarioInicioPlanta = HoraInicio - PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao] - PlantasInstancia.Plantas[p].TempoPlanta;
			}else{
				HorarioInicioPlanta = PlantasInstancia.Plantas[p].TempoMinimoDeFuncionamento;
			}
			do{
				HorarioSaiDaPlanta = HorarioInicioPlanta + PlantasInstancia.Plantas[p].TempoPlanta;

				HorarioChegaContrucao = HorarioSaiDaPlanta + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				HorarioSaiConstrucao = HorarioChegaContrucao +  PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].TempoParaDescarregarNaConstrucao[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao][NumeroDemanda];
				HorarioRetornaPlanta = HorarioSaiConstrucao + PlantasInstancia.Plantas[p].DistanciaConstrucoes[ConstrucoesInstancia.Construcoes[c].NumeroDaConstrucao];
				DisponibilidadePlanta = PlantasInstancia.Plantas[p].VerificaDisponibilidade(HorarioInicioPlanta, HorarioSaiDaPlanta );
				DisponibilidadeCarreta = PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].VerificaDisponibilidade(HorarioInicioPlanta, HorarioRetornaPlanta);
				DisponibilidadeConstrucao = ConstrucoesInstancia.Construcoes[c].VerificaDisponibilidade( HorarioChegaContrucao, HorarioSaiConstrucao);

				if( DisponibilidadePlanta == 1){
					if( DisponibilidadeCarreta == 1){
						if( DisponibilidadeConstrucao == 1 || DisponibilidadeConstrucao == 2 || DisponibilidadeConstrucao == 3){
							ConstrucoesInstancia.Construcoes[c].AlocaAtividadeSalvandoDados(HorarioChegaContrucao, HorarioSaiConstrucao, PlantasInstancia.Plantas[p].VeiculosDaPlanta.Carretas[v].NumeroDaCarreta, PlantasInstancia.Plantas[p].NumeroDaPlanta,  0, 1, PlantasInstancia, DadosTarefasAdicionadas);
							return 1;
						}
						if( DisponibilidadeConstrucao == -2){
							return -2;
						}
					}
				}
				HorarioInicioPlanta = HorarioInicioPlanta + IntervaloDeTempo;
			}while( HorarioInicioPlanta <= PlantasInstancia.Plantas[p].TempoMaximoDeFuncionamento ||  HorarioChegaContrucao <= ConstrucoesInstancia.Construcoes[c].TempoMaximoDeFuncionamento);
		}
	}

	return 0;
}

int Solucao::ColocarTarefaAtrazandoAsOutras(int ConstrucaoParaAtenderIndice, int demanda , double HoraInicio, vector < DadosTarefa > & DadosAdicionaAux, int TipoOrdenacao, int Imprime){
	vector < int > SituacaoPlantas;
	vector < int > SituacaoDemandas;
	double HorarioInicioConstrucao;

	int ExistePlanta;
	int PlantaAtender;
	int PlantaAtenderIndice;

	int PermiteAtendimentoDemanda;

	vector < DadosTarefa > TemporarioAdiciona;
	vector < DadosTarefa > AuxiliarRetira;

	HorarioInicioConstrucao = HoraInicio + IntervaloDeTempo;	// aumenta o tempo que a primeira demanda pode ser atendida

	SituacaoPlantas.resize(NP);					// Vetor que armazena se a planta foi analisada ou não para atender certa demanda
	SituacaoDemandas.resize(demanda + 1); 		// Tem que somar mais um pelo fato de se contar o 0 como um elemento

	while(HorarioInicioConstrucao <  ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento ){

		if ( Imprime == 1){
			//cout << "  HorarioInicioConstrucao " << HorarioInicioConstrucao << " / " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].TempoMaximoDeFuncionamento << endl;
		}
		IniciaVetorIntComZero(SituacaoDemandas);
		for( int d = 0; d <= demanda; d++){
			IniciaVetorIntComZero(SituacaoPlantas);
			ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );		// seleciona planta a atender
			PermiteAtendimentoDemanda = 0;
			while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < demanda + 1 && PermiteAtendimentoDemanda == 0){
				SituacaoPlantas[PlantaAtenderIndice] = 1;							// Marca planta atendida
				PermiteAtendimentoDemanda = SelecionaCarretaComHoraInicio( HorarioInicioConstrucao, ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, TemporarioAdiciona, TipoOrdenacao); 		// aloca atendimento da demanda se 1, 0 se não
				if( PermiteAtendimentoDemanda == 1){		// se alocou a demanda
					IniciaVetorIntComZero(SituacaoPlantas);		// zera o vetor do status das plantas
					SituacaoDemandas[d] = 1;					// coloca a demanda como atendida
				}else{
					if( PermiteAtendimentoDemanda == 0){
						SituacaoPlantas[PlantaAtender] = 1;			// marca planta já analisada
					}
					if ( PermiteAtendimentoDemanda == -2){
						SituacaoPlantas[PlantaAtender] = -2;		// marca planata já analisada, mas que poderia atender a demnada caso a demanda anterior fosse mais tarde
					}
				}
				ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, SituacaoPlantas );	// retorna a planta que ira atender a proxima demanda
			}
			if ( VerificaTodosValoresVetorInt( 1, SituacaoDemandas) == 1){
				DadosAdicionaAux = TemporarioAdiciona;		// retorna as tarefas adicionadas no procediemnto
				return 1;
			}
		}
		if ( VerificaSeTemUmValorVetorInt( -2, SituacaoPlantas) == 1){
			ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);		//deleta tarefas anteriores ao horario inicio, pois ainda há possibilidade de atender a demanda que ainda não conseguimos atender
			TemporarioAdiciona.clear();													// deleta conteudo do vetor de tarefas adicionadas, pois elas forma deletadas no procedimento acima
			HorarioInicioConstrucao = HorarioInicioConstrucao + IntervaloDeTempo;		// aumenta o tempo que se começa a alocar as tarefas
		}else{
			// Não se consegue adicionar a demanda mesmo atrazando as atnteriores
			//ImprimeVetorInt( SituacaoPlantas);
			//ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, AuxiliarRetira);		// deleta todas as tarefas adicionadas
			TemporarioAdiciona.clear();			// limpa vetor com as tarefas adicionadas durante o procedimento
			return 0;
		}
	}
	// ultrapassou o limite de tempo na construção
	if ( Imprime == 1){
		cout << endl << endl << "  Não da para atrazar " << endl << endl;
	}
	TemporarioAdiciona.clear();				// limpa vetor com as tarefas adicionadas durante o procedimento
	return 0;

}

void Solucao::ProcessoViabilizacao2(int TipoOrdenacao){

	int InviabilidadeSolucaoAnterior;


	int	ConstrucaoNaoAtendida;
	int IndiceConstrucaoNaoAtendida;
	int DemandaNaoAtendida;

	int DeletouAlgumaTarefa;

	vector < double > TempoSaiPlanta;

	vector < DadosTarefa > DadosTarefasDesalocadas;
	vector < DadosTarefa > DadosTarefasAdicionadas;

	int TarefaAdicionada;

	int ConstrucaoParaAtender;
	int ConstrucaoParaAtenderIndice;
	int PossuiConstrucaoParaAnalisar;

	int d;

	int PlantaAtender;
	int PlantaAtenderIndice;
	int ExistePlanta;

	int PermiteAtendimentoDemanda;


	vector< int > PlantasPodemAtenderTarefa;

// estrutura para processo de atrazar tarefas
	double HoraInicio;
	vector < DadosTarefa > DadosRetirandoAux;
	vector < DadosTarefa > DadosAdicionaAux;
	int ConseguiAlocarTarefa;

	//Plantas que podem atender as tarefas caso as tarefas posteriores forem atrasadas

	int Imprime;
	int PararPrograma;

	Imprime = 1;

	int RealizaProcessoDeAtrazarTarefas;

	RealizaProcessoDeAtrazarTarefas = 0;

// Encontra demanda ainda não atendida

	ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();		// Marca as construções que já foram completamente atenddidas com 1, as que não forma com 0

	while( ConstrucoesInstancia.VerificaConstrucaoPodeAtender() == 1){			// Verifica se pode atender uma construção ainda, se tem uma com demanda não atendida

		InviabilidadeSolucaoAnterior = ConstrucoesInstancia.NivelDeInviabilidade;		// guarda o nivel de inviabilidade
		ConstrucoesInstancia.ReiniciaTarefasRetiradas();								// reinicia o estado de deslocamento e remoção de todas as demandas de todas as construções
		ProcuraConstrucaoNaoAtendida( ConstrucaoNaoAtendida, DemandaNaoAtendida);		// retorna a demanda e a construção que serão analisados inicialmente
		TempoSaiPlanta.resize(NP);														// inicia o tamanho do vetor de tempo do inicio das plantas com 0
		if( Imprime == 1){
			cout << " ConstrucaoNaoAtendida = " << ConstrucaoNaoAtendida <<" DemandaNaoAtendida = " << DemandaNaoAtendida << endl << endl;
		}
		ConstrucoesInstancia.RetornaIndiceConstrucao(ConstrucaoNaoAtendida, IndiceConstrucaoNaoAtendida, " inicio -> Solucao::ProcessoViabilizacao2" );		// retorna o incide da cosntrução que tem qeu ser analisada no momento
	// deleta tarefas que são atendidas antes desta tarefa não alocada
		AlocaTempoSaiDaPlanta(IndiceConstrucaoNaoAtendida,TempoSaiPlanta, 0);		// aloca no vetor TempoSaiPlanta os tempos que as plantas podem atender
		DeletouAlgumaTarefa = DeletaTarefasAposTempoSaiPlanta(TempoSaiPlanta, DadosTarefasDesalocadas,  0);		// deleta tarefas que são atendidas antes dos tempos armazenadaos no vetor TempoSaiPlanta
		if( Imprime == 1){
			cout << "   							<<<<<<<<<<< Deteta tarefas >>>>>>>>>>>>>> ";
			ConstrucoesInstancia.ImprimeContrucoes();
			cin >> PararPrograma;
		}
	// Adiciona a tarefa que não era alocada antes
		TarefaAdicionada = AdicionaTarefa( ConstrucaoNaoAtendida, DemandaNaoAtendida, DadosTarefasAdicionadas,DadosTarefasAdicionadas, 2, 0, RealizaProcessoDeAtrazarTarefas, TipoOrdenacao);		// tenta adicionar a demanda não atendida anteriormente. Caso consegui retorna 1, caso contrario retorna 0.
		SinalizaTarefaAdicionadaInicialmente( TarefaAdicionada, IndiceConstrucaoNaoAtendida, DemandaNaoAtendida);						// atualiza os valores de situação e remoção da demanda. caso for atendida coloca 2 em ambos, caso não, a situação tem valor -1 e a remoção 3
		if( ConstrucoesInstancia.Construcoes[ IndiceConstrucaoNaoAtendida ].SituacaoDemanda[ DemandaNaoAtendida ] == -1){		// Verifa se conseguiu alocar a demnada não alocada antes.
			// Caos não aloque a demanda
			if( Imprime == 1){
				cout << endl << endl << "   Não consigo alocar tarefa [" << ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "] que não foi alocada antes -> Solucao::ProcessoViabilizacao2 " << endl << endl;
			}
			ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas);	// retorna a solução inicial
			DadosTarefasDesalocadas.clear();								// deleta conteudo do vetor

			//ConstrucoesInstancia.AlocaValoresConstrucaoPodeAtender();		// Marca as construções que já foram completamente atendidas com 1, as que não forma com 0

			ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 4;		// marca cosntrução como já analisada e que não se consegue alocar a demanda utilizando esse procedimento já no inicio após deletar todas as tarefas. Ou seja, não se consegue alocar essa tarefa usando as plantas que se tem.
		}else{

			if( Imprime == 1){
				cout << "   						<<<<<<<<<<< Coloca tarfea não alocada anterioremnte [" <<  ConstrucaoNaoAtendida << "-" << DemandaNaoAtendida << "]  >>>>>>>>>>>>>>> ";
				ConstrucoesInstancia.ImprimeContrucoes();
				ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cin >> PararPrograma;
			}

	// marca construções com tarefas a alocar
			ConstrucoesInstancia.InicializaConstrucoesAnalizadas();										// marca todas as construções como possiveis a alocar demandas, todas com 0 em ConstrucoesAnalisadas
			ConstrucoesInstancia.AlocaValoresConstrucoesAnalizadas( IndiceConstrucaoNaoAtendida);		// marca as construções com todas suas demandas atendidas com 2, e a construção que tinha uma demanda sem atender e que agora foi atendida com 3
	// Verifica se tem tarefa a se colocar
			PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucoesAnalizadas);					// escolhe a construção com o menor indice e que pode ser atendida ( todas as construções com 0 em CosntruçõesAnalisadas, estas são as que não tem suas demandas todas atendidas e que não sejá a que passou a ter uma demanda que não era atendida antes e agora é atendida)
			if( Imprime == 1){
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1, ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cout << "   <<<<<<<<<<< Readiciona demandas   >>>>>>>>>>>>>>> " << endl;
				//cin >> PararPrograma;
			}
			while( PossuiConstrucaoParaAnalisar == 1){				// caso se tenha uma construção ainda para se adicionar demnadas
				ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucaoParaAtenderIndice] = 1;			// marca cosntrução como analisada
				d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;	// coloca a demanda que se tem que alocar no momento
				if( Imprime == 1){
					cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]";
				}
				PlantasInstancia.InicializaPlantasAnalizadas();											// faz com que nenhuma planta tenha sido analisada
				ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a planta mais proxima que pode atender a planta
				if( Imprime == 1){
					//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
					//cin >> PararPrograma;
				}
				while( ExistePlanta == 1 && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){		//  caso ainda for possivel atender uma demanda da construção continuar
					PlantasInstancia.PlantasAnalizadas[PlantaAtenderIndice] = 1;					// marca planta como já analisada
					PermiteAtendimentoDemanda = SelecionaCarreta(ConstrucaoParaAtenderIndice, PlantaAtenderIndice, d, 3, DadosTarefasAdicionadas , TipoOrdenacao);		// verifica se a demanda pode ser atendida por essa planta, caso for retorna 1, caso não, retorna -2 se é possivel caso atraze as demandas já alocadas ou 0 caso a planta não possa ser utilizada para atender essa demnada com as demandas que ela atende no momento
					if( Imprime == 1){
						//cout << "     		Tenta Planta " << PlantaAtender << " [" << PlantaAtenderIndice << "]" << endl;
						//ConstrucoesInstancia.ImprimeContrucoes();
						//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 0,  DadosTarefasDesalocadas, 0,  DadosTarefasAdicionadas, 1,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
					}
					if( PermiteAtendimentoDemanda == 1){	// demanda é alocada
						if( Imprime == 1){
							cout << "      Atendida " << endl;
							//cout << "             +++++   Planta [" << PlantaAtenderIndice << "] " << PlantasInstancia.Plantas[PlantaAtenderIndice].NumeroDaPlanta << "  atende demanda " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						}
						if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){			// caso a demanda não for a ultima que temq eu ser alocada na construção. isto se dá pois temq eu se contra com a dmenada 0
							d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;		// atualiza a variavel "d" com a proxima demanda que temq eu ser atendida
								if( Imprime == 1){
									if( d != ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
										cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]" ;
									}
								}
								PlantasInstancia.InicializaPlantasAnalizadas();		// faz com que nenhuma planta tenah sido atendida
								ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );	// seleciona a primeira planta que pode atender a demanda referente a demnada "d"
						}else{
							// caso for a demnada que foi alocada ser a ultima que tem que ser atendida na construção
							PlantasInstancia.InicializaPlantasAnalizadas();		// faz com que nenhuma planta tenah sido atendida, isto qtem que ser feito para fugir do "if" que pega as demnadas não atendidas
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a primeira planta que pode atender
						}
					}else{
						if( PermiteAtendimentoDemanda == 0){		// não é possivel atender a demanda com essa planta
							PlantasInstancia.PlantasAnalizadas[PlantaAtender] = 1;		// maraca planta como analisada
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a primeira planta que pode atender
						}
						if ( PermiteAtendimentoDemanda == -2){		// no momento não é possivel atender a demanda, mas caso atarzar as demandas que já foram alocadas na cosntrução pode ser possivel que ela possa ser atendida por essa planta
							PlantasInstancia.PlantasAnalizadas[PlantaAtender] = -2;		// marca planta como sendo possivel atender a demanda em questão caso atraze as outras demandas ja atendidas na cosntrução
							ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );		// seleciona a primeira planta que pode atender
						}


// Verifica se pode atrazar

						if( ExistePlanta == 0 && PlantasInstancia.VerificaPlantasAnalizadasPodemAtenderSeAtrazar() && ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento >= 1){		// verifica se pode atrazar. isto é, caso não se tenha mais nenhuma planta para se analisar se pode atender a demanda, caso se tenha uma planat que pode atender a demnada caso se atraze suas demandas e caso a construção tenha uma ou mais demandas já atendidas
							if( Imprime == 1){
								cout << endl << endl << "   	Pode atrazar tarefas da construção " << ConstrucaoParaAtender << " [" << ConstrucaoParaAtenderIndice << "] - d = " << d << " para alocar outra " << endl;
								ImprimeVetorInt(PlantasInstancia.PlantasAnalizadas);
								ConstrucoesInstancia.ImprimeContrucoes();
								cout  << endl << endl;
							}

							ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].DeletaTodasAtividadesDaContrucaoSalvandoDados(HoraInicio, PlantasInstancia, DadosRetirandoAux);		// deleta todas as demandas atendidas na construção
							ConseguiAlocarTarefa = ColocarTarefaAtrazandoAsOutras( ConstrucaoParaAtenderIndice, d , HoraInicio, DadosAdicionaAux, TipoOrdenacao, Imprime);						// Tenta recolocar as demandas deletadas acima ao atrazar o atendimento das demandas iniciais

							if( ConseguiAlocarTarefa == 1){			// consegui alocara demanda
								PermiteAtendimentoDemanda = 1;		// marco que consegui alocar a demanda não atendida inicialmente
								if( Imprime == 1){
									cout << endl << "      Atendida apos atrazar" << endl;
								}
								if(d < ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){		// atualizo a variável "d" com a proxima demanda da construção caso está existir
									d = ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].StatusAtendimento;	// atualizo a variável "d"
									if( Imprime == 1){
										if( d != ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDemandas){
											cout << " Demanda [" << ConstrucaoParaAtender << "-" << d << "]" ;
										}
									}
									PlantasInstancia.InicializaPlantasAnalizadas();				// faz com que nenhuma planta tenah sido atendida
									ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );	// seleciona a primeira planta que pode atender a demanda referente a demnada "d"
								}else{
									PlantasInstancia.InicializaPlantasAnalizadas();				// faz com que nenhuma planta tenah sido atendida
									ExistePlanta = SelecionaPlanta( PlantaAtender,PlantaAtenderIndice, ConstrucaoParaAtenderIndice, PlantasInstancia.PlantasAnalizadas );	// seleciona a primeira planta que pode atender a demanda referente a demnada "d"
								}

								cout << endl << endl << " depois processo de tentar atrazar terefas " << endl << endl;

								ConstrucoesInstancia.ImprimeContrucoes();

								cout << endl << endl << "    Antes na função " << endl << endl;

								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cout << endl << endl << "    Dados da função " << endl << endl;

								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1, DadosRetirandoAux, 1,  DadosAdicionaAux, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cin >> PararPrograma;

								for( unsigned int i = 0; i < DadosRetirandoAux.size();i++){

									if( VerificaElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas ,DadosRetirandoAux[i] ) == 1){
										// caso eu retire uma tarefa no procedimento atraza, se está tarefa já tiver sido colocada no vetor de tarefas adicionadas, eu a retiro desse vetor (é como se essa tarefa nunca tivesse existido )
										if( RetiraElementoVetorDadosTarefaApartirEstrutura(DadosTarefasAdicionadas, DadosRetirandoAux[i]) == 0){
											cout << "    Não retirou " << endl;
											if( Imprime == 1){
												//DadosRetirandoAux[i].Imprimir();
												//cout << "             DadosRetirandoAux" << endl ;
											}
										}
									}else{
										// caso eu retire uma tarefa no procedimento atraza, se está tarefa não já tiver sido colocada no vetor de tarefas adicionadas anteriormente, ela é originaria do sequencimanto original. Logo eu a coloco no vetor de tarefas retiradas
										if( AdicionaElementoVetorDadosTarefaApartirEstrutura(1,DadosTarefasDesalocadas, DadosRetirandoAux[i]) == 0){
											cout << "    Não adicionou " << endl;
											if( Imprime == 1){
												//DadosRetirandoAux[i].Imprimir();
												//cout << "             DadosRetirandoAux" << endl ;
											}
										}
									}
								}

								for( unsigned int i = 0; i < DadosAdicionaAux.size();i++){
									// Todas as tarefas  adicionadas no procedimento no vetor de tarefas que foram adicionadas
									if( AdicionaElementoVetorDadosTarefaApartirEstrutura(1,DadosTarefasAdicionadas, DadosAdicionaAux[i] ) == 0){
										cout << "    Naõ adicionou " << endl;
										if( Imprime == 1){
											//DadosRetirandoAux[i].Imprimir();
											//cout << "             DadosAdicionaAux" << endl ;
										}
									}
								}

								cout << endl << endl << "    Depois na função " << endl << endl;


								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cout << endl << endl << "    Dados da função " << endl << endl;

								ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1, DadosRetirandoAux, 1,  DadosAdicionaAux, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

								cin >> PararPrograma;

							}else{
								// neste caso, não foi possivel adicionar a demanda. O procedimento já deleta as tarefas alocadas nele para a construção. Aqui se é readicionado as demandas deletadas inicialmente para que o sequenciamento fique como era antes de se executar o procedimento.
								ReadicionaTarefasApartirDeDados( DadosRetirandoAux, 1);
								DadosRetirandoAux.clear();
							}

							//cout << endl << endl << "    depois de atualizar vetores " << endl << endl;
							//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

							//cin >> PararPrograma;


						}


					}

					// Entra aqui caso não se consiga atender a demanda em questão por nenhuma planta
					if( ExistePlanta == 0 ){
						if( Imprime == 1){
							cout << "     -> Não atendida" << endl;
							//cout << " Nao se pode colocar tarefa da construcao [" << ConstrucaoParaAtenderIndice << "] " << ConstrucoesInstancia.Construcoes[ConstrucaoParaAtenderIndice].NumeroDaConstrucao << "-" << d << endl;
						}
						ConstrucoesInstancia.ConstrucoesAnalizadas[ConstrucaoParaAtenderIndice] = 4;		// marca a cosntrução com 4, para saber que não se consegue alocar mais demandas nela com a configuração atual do sequenciamento.
						if( Imprime == 1){
							//ImprimeVetorInt( PlantasInstancia.PlantasAnalizadas );
							//ConstrucoesInstancia.ImprimeContrucoes();
						}
					}
				}
				PossuiConstrucaoParaAnalisar = SelecionaConstrucao( ConstrucaoParaAtender, ConstrucaoParaAtenderIndice, ConstrucoesInstancia.ConstrucoesAnalizadas);	// se passa para a proxima construção que se pode atender
				if( Imprime == 1){
					//ConstrucoesInstancia.ImprimeContrucoes();
					//PlantasInstancia.Imprime(1,1);
					//cin >> PararPrograma;
				}

			}

			ConstrucoesInstancia.CalcularNivelDeInviabilidade();		// calcula o nivel de inviabilidade que ira mostrar se a soluçpão melhorou ou não

			if( Imprime == 1){
				cin >> PararPrograma;
				ConstrucoesInstancia.ImprimeContrucoes();
				//PlantasInstancia.Imprime(1,1);
			}

			// verifica se a solução melhorou
			if( InviabilidadeSolucaoAnterior > ConstrucoesInstancia.NivelDeInviabilidade){
				if( Imprime == 1){
					cout << endl << endl << "    Melhorou !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes();
				}
				// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();		// atualiza a situação da construçãoq ue teve todas as suas demandas atendidas

			}else{
				if( Imprime == 1){
					cout << endl << endl << "    Não melhorou !!!!!!" << endl << endl;
					ConstrucoesInstancia.ImprimeContrucoes();
					cin >> PararPrograma;
				}

				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);

				cout << endl << " aqui 1" << endl;
				if( DeletaTarefasApartirDeDados(  DadosTarefasAdicionadas ) == 0){			// deleta as tarefas adicionadas durante o procedimento
					if( Imprime == 1){
						cout << endl << endl << "   problema em deletar " << endl << endl;
					}
				}
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cout << endl << " aqui 2" << endl;

				if( ReadicionaTarefasApartirDeDados( DadosTarefasDesalocadas) == 0){		// readiciona as tarefas que foram deletadas anteriormente, visando a retornar ao sequenciamento que se tinha inicialmente
					if( Imprime == 1){
						cout << endl << endl << "   problema em realocar " << endl << endl;
					}
				}
				//ImprimeDadosRetiradoAdicionadoVetorConstrucaoAnalisada( 1,  DadosTarefasDesalocadas, 1,  DadosTarefasAdicionadas, 0,  ConstrucoesInstancia.ConstrucoesAnalizadas, 0);
				cout << endl << " aqui 3" << endl;
				// limpa o conteudo dos vetores que guardam os dados das tarefas retiradas e adicionadas
				DadosTarefasDesalocadas.clear();
				DadosTarefasAdicionadas.clear();
				ConstrucoesInstancia.AtualizaValoresConstrucaoPodeAtender();		// atualiza a situação da construçãoq ue teve todas as suas demandas atendidas
				ConstrucoesInstancia.ConstrucaoPodeAvaliar[IndiceConstrucaoNaoAtendida] = 3;	// Marca a construção qeu logo após deletar as tarefas, adicionar a demanda não alocada dela e depois readicionar as demandas deletadas antes, não se chegou em um sequenciamento melhor.
			}

			//cin >> PararPrograma;
		}
	}
}

*/
Solucao::~Solucao(){

}

class ConjuntoSolucoes{
public:
	vector < Solucao > Solucoes;
	ConjuntoSolucoes();			// classe construtoora
	void InsereSolucao(int, ConjuntoPlantas, int, ConjuntoConstrucoes,	int, double, double);			// carrega uma solução ao vetor das soluções
	void CalculaMakespanSolucoes();		// calcula o makespan das soluções
	void Imprime(bool, bool, bool);		// imprime as soluções
	~ConjuntoSolucoes();

};

// classe construtoora
ConjuntoSolucoes::ConjuntoSolucoes(){
}

// carrega uma solução ao vetor das soluções
void ConjuntoSolucoes::InsereSolucao(int np, ConjuntoPlantas Plantas, int ne, ConjuntoConstrucoes Construcoes, int nv, double v,double TDVC){
	Solucao S1;
	// carrega dasos da solução
	S1.CarregaSolucao( np, Plantas, ne, Construcoes, nv, v, TDVC);
	// colocar a solução carregada nbo vetor de soluções
	Solucoes.push_back(S1);
}

// calcula o makespan das soluções
void ConjuntoSolucoes::CalculaMakespanSolucoes(){
	// percorre por todas as soluções
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		// calcula o makespan da solução corrente de suas construções
		Solucoes[s].ConstrucoesInstancia.CalculaMakespansConstrucoes();
		// calcula o makespan da solução corrente de suas plantas
		Solucoes[s].PlantasInstancia.CalculaMakespanPlantas();
		// calcula o makespan da solução
		Solucoes[s].Makespan = Solucoes[s].ConstrucoesInstancia.MakespanConstrucoes + Solucoes[s].PlantasInstancia.MakespanPLantas;
	}
}

// imprime as soluções
void ConjuntoSolucoes::Imprime(bool ImprimePlanta, bool ImprimeConstrucao, bool IntervalosRespeitadosConstrucaoes){
	// percorre por todas as soluções
	for( unsigned  int s = 0; s <  Solucoes.size(); s++){
		// imprime a solução corrente
		cout << endl << endl << "   Solucao " << s << endl << endl;
		 Solucoes[s].Imprime(ImprimePlanta,ImprimeConstrucao, IntervalosRespeitadosConstrucaoes);
		 // escreve o makespan total da solução
		 cout << "         Makespan total = " << Solucoes[s].Makespan << endl ;
	}
}



ConjuntoSolucoes::~ConjuntoSolucoes(){

}



#endif /* SOLUCOES_HPP_ */
