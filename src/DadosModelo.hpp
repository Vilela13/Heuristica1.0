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

	vector < vector < double > > TEMpc;
	vector < vector < double > > TEMcp;
	vector < vector < vector < double > > > DESCvi;
	vector < double > CARRp;
	double TVC;
	vector < double > TETAc;
	vector < vector < vector < vector < vector < double > > > > > S1vii;
	vector < vector < vector < vector < vector < double > > > > > S2vii;
	vector < double > TMINc;
	vector < double > TMAXc;
	vector < double > TMINp;
	vector < double > TMAXp;

	vector < vector < vector < double > > > M1vi;
	vector < vector < double > > M2pc;
	vector < double > M3c;
	vector < vector < vector < double > > > M4vi;
	vector < vector < vector < vector < vector < double > > > > > M5vii;
	vector < vector < vector < vector < vector < double > > > > > M6vii;
	vector < double > M7c;
	vector < vector < vector < double > > > M8vi;
	vector < double > M9p;
	vector < vector < double > > M10cp;


};


#endif /* DADOSMODELO_HPP_ */
