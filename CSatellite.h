/*
 * CSatellite.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CSATELLITE_H_
#define CSATELLITE_H_

#include "CPlanet.h"
#include "CChromosome.h"
#include <vector>
#include <algorithm>
using namespace std;

class CSatellite : CPlanet{
public:
	CSatellite(Par* par);
	virtual ~CSatellite();
	float m_fuel;
	int m_thrustQuant;
	vector<CChromosome> m_thrusts;

};

#endif /* CSATELLITE_H_ */
