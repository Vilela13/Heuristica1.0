/*
 * Bibliotecas.hpp
 *
 *  Created on: Aug 13, 2015
 *      Author: mateus.vilela
 */

#ifndef BIBLIOTECAS_HPP_
#define BIBLIOTECAS_HPP_

#include <sstream>

#include <iostream>     // Biblioteca padrão de c++
#include <istream>      // Biblioteca padrão de c++
#include <list>         // Biblioteca que contem a estrutura listas
#include <string>       // Biblioteca que contem a estrutura string ( vetor de caracteres)
#include <fstream>      // Biblioteca que contem a estrutura para acessar arquivos txt
#include <vector>       // Biblioteca que contem a estrutura Vector

#include <stdio.h>      // Biblioteca padão de C, principalmente a operações de entrada e saída
#include <stdlib.h>     // Biblioteca padão de C, possui funções envolvendo alocação de memória, controle de processos, conversões e outras.
#include <string.h>		// Biblioteca que contem a classe de strings

#include <algorithm>	// Biblioteca contendo um conjunto de funções como a sort para ordenação

#include <time.h>		// Biblioteca que contem as classes e tipos para controle de tempo

#include <math.h>		// Biblioteca contendo funções para operações matematicas
#include <limits.h>	// Biblioteca com o valor limite das variaveis (int, char)
#include <float.h>	// Biblioteca com o valor limite da variavel float


#include <dirent.h> 	// Manipulação de arquivos em C (meu caso, ver se arquivo existe)

//#include <random>		// Biblioteca para gerar numeros segundo probabilidades

/* Outra maneira de criar arquivos
#include <sys/types.h>
#include <sys/stat.h>		// Manipulação de arquivos em C (meu caso, criar arquivo )
*/

using namespace std;

#define IntervaloDeTempo 0.0083333 // meio minuto
//0.016666; // um minuto

#define PenalidadeNaoAtendimentoDemanda	500

#include "DadosSolomon.hpp"
#include "Carretas.hpp"
#include "Plantas.hpp"

#include "DadosTarefa.hpp"

#include "Construcoes.hpp"
#include "Procedimento1.hpp"
#include "Solucoes.hpp"
#include "Heuristica.hpp"





#endif /* BIBLIOTECAS_HPP_ */
