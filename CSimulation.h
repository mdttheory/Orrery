/*
 * CSimulation.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CSIMULATION_H_
#define CSIMULATION_H_

#include "CPlanet.h"
#include "Parameters.cpp"
#include "CSolarSystem.h"
#include <fstream>
#include <vector>

class CSimulation {
public:
	CSimulation(CSolarSystem solarSystem, Par *par, string name, unsigned short coreNum, unsigned int genNum);
	CSimulation(CSolarSystem solarSystem, Par* par, string name, CSimulation a, CSimulation b, unsigned short coreNum);
	virtual ~CSimulation();
	void RK(CSVector &pos_i, CSVector &vel_i, string name);
	void Euler(CSVector &pos_i, CSVector &vel_i, string name);
	CSVector CalcDv(float dt, vector<CPlanet> planets, unsigned short i);
	CSVector CalcA(CSVector pos, string name, float dt);
	void print_pos(ostream &pos_stream);
	void print_en(ostream &en_stream, double init_en);
	void update(unsigned long currStep);
	string m_name;
	unsigned short m_coreNum;
	unsigned int m_genNum;
	Par* m_par;

	CSolarSystem m_SS;
};

#endif /* CSIMULATION_H_ */
