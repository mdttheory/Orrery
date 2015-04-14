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
	CSimulation(CSolarSystem solarSystem, Par *par);
	virtual ~CSimulation();
	void RK();
	CSVector CalcDv(float dt, vector<CPlanet> planets, unsigned short i);
	void print_pos(ostream &pos_stream);
	void update();
	Par* m_par;
	CSolarSystem m_SS;
};

#endif /* CSIMULATION_H_ */
