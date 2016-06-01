/*
 * DadosModelo.hpp
 *
 *  Created on: May 24, 2016
 *      Author: mateus.vilela
 */

#ifndef DADOSMODELO_HPP_
#define DADOSMODELO_HPP_


class DadosModelo{

public:
	int NP;
	int NV;
	int NE;

	vector < int > Demandas;
	vector < int > Veiculos;

	vector < vector < float > > TEMpc;
	vector < vector < float > > TEMcp;
	vector < vector < vector < float > > > DESCvi;
	vector < float > CARRp;
	float TVC;
	vector < float > TETAc;
	vector < vector < vector < vector < vector < float > > > > > S1vii;
	vector < vector < vector < vector < vector < float > > > > > S2vii;
	vector < float > TMINc;
	vector < float > TMAXc;
	vector < float > TMINp;
	vector < float > TMAXp;

	vector < vector < vector < float > > > M1vi;
	vector < vector < float > > M2pc;
	vector < float > M3c;
	vector < vector < vector < float > > > M4vi;
	vector < vector < vector < vector < vector < float > > > > > M5vii;
	vector < vector < vector < vector < vector < float > > > > > M6vii;
	vector < float > M7c;
	vector < vector < vector < float > > > M8vi;
	vector < float > M9p;
	vector < vector < float > > M10cp;


};


#endif /* DADOSMODELO_HPP_ */
