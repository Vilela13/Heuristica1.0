/*
 * SwitchStatus.hpp
 *
 *  Created on: 11 de out de 2016
 *      Author: mavus
 */

#ifndef FUNCOESDOCPP_HPP_
#define FUNCOESDOCPP_HPP_

void DescobreStatus( int Status, FILE *ArquivoExcelResposta){
	switch (Status){
		//case 0:	ArquivoExcelResposta <<  "Unknow" << '\t';						break;
		case 0:	fprintf(ArquivoExcelResposta, "Unknow \t");						break;
		//case 1:	ArquivoExcelResposta <<  "Feasible" << '\t';					break;
		case 1:	fprintf(ArquivoExcelResposta, "Feasible \t");						break;
		//case 2:	ArquivoExcelResposta <<  "Optimal" << '\t';						break;
		case 2:	fprintf(ArquivoExcelResposta, "Optimal \t");						break;
		//case 3:	ArquivoExcelResposta <<  "Infeasible" << '\t';					break;
		case 3:	fprintf(ArquivoExcelResposta, "Infeasible \t");						break;
		//case 4:	ArquivoExcelResposta <<  "Unbounded" << '\t';					break;
		case 4:	fprintf(ArquivoExcelResposta, "Unbounded \t");						break;
		//case 5: ArquivoExcelResposta <<  "Infeasible Or Unbounded" << '\t';		break;
		case 5:	fprintf(ArquivoExcelResposta, "Infeasible Or Unbounded \t");		break;
		//default: ArquivoExcelResposta <<  "Erro" << '\t';
		default: fprintf(ArquivoExcelResposta, "Erro \t");
	}
}



#endif /* FUNCOESDOCPP_HPP_ */
