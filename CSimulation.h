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

class CSimulation {
public:
	CSimulation(CSolarSystem solarSystem, Par *par);
	virtual ~CSimulation();
	void RK4();
	CSVector CalcDv(float dt, vector<CPlanet> planets, unsigned short i);
	Par* m_par;
	CSolarSystem m_SS;
};

#endif /* CSIMULATION_H_ */
