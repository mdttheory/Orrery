/*
 * CSatellite.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSatellite.h"
using namespace std;

CSatellite::CSatellite(Par* par) {
	m_fuel = par->startFuel;
	for(int i = 0; i < m_thrustQuant; i++){
		CChromosome a(&par);
		m_thrusts.push_back(a);
	}
	sort(m_thrusts.begin(), m_thrusts.end());
}

CSatellite::~CSatellite() {
	// TODO Auto-generated destructor stub
}

