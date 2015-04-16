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

class CSimulation {
public:
	CSimulation(CSolarSystem solarSystem, Par *par, string name);
	virtual ~CSimulation();
	void RK(CSVector &pos_i, CSVector &vel_i, string name);
	void Euler(CSVector &pos_i, CSVector &vel_i, string name);
	CSVector CalcDv(float dt, vector<CPlanet> planets, unsigned short i);
	CSVector CalcA(CSVector pos, string name, float dt);
	void print_pos(ostream &pos_stream);
	void print_en(ostream &en_stream, double init_en);
	void update();
	string m_name;
	Par* m_par;
	CSolarSystem m_SS;
};

#endif /* CSIMULATION_H_ */
