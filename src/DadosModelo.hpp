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

	~DadosModelo();
};

DadosModelo::~DadosModelo(){

	Demandas.clear();
	Veiculos.clear();

	TEMpc.clear();
	TEMcp.clear();
	DESCvi.clear();
	CARRp.clear();
	TETAc.clear();
	S1vii.clear();
	S2vii.clear();
	TMINc.clear();
	TMAXc.clear();
	TMINp.clear();
	TMAXp.clear();

	M1vi.clear();
	M2pc.clear();
	M3c.clear();
	M4vi.clear();
	M5vii.clear();
	M6vii.clear();
	M7c.clear();
	M8vi.clear();
	M9p.clear();
	M10cp.clear();
}


#endif /* DADOSMODELO_HPP_ */
