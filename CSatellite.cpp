/*
 * CSatellite.cpp
 *
 *  Created on: Apr 20, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSatellite.h"
using namespace std;

bool thrustLessCompare(CChromosome lhs, CChromosome rhs){
		return(lhs.m_t<rhs.m_t);
	}

CSatellite::CSatellite(Par* par, CSolarSystem* ss, string name, vector<bool> flag) : CPlanet(flag) {

	m_thrustQuant = par->thrustQuant;
	for(int i = 0; i < m_thrustQuant; i++){
		CChromosome a(par);
		a;//TODO fix max values
		float z = a.m_dvx.size();
		m_thrusts.push_back(a);
	}
	sort(m_thrusts.begin(), m_thrusts.end(),thrustLessCompare);

	m_homePlanetName = par->homePlanetName;

	m_fuel = par->startFuel;
	m_ss = ss;
	m_mass = par->satMass;
	m_perihelion = -1;
	m_aphelion = -1;

//TODO: uncomment  / fix
//	for (vector<CPlanet>::iterator it = ss->m_planets.begin();
//				it < ss->m_planets.end(); it++) {
//		if(it->m_name == m_homePlanetName){
//			m_dynamics = it->getDynamics();
//		}
//	}
	m_name = name;
	m_angle = -1;

}

CSatellite::CSatellite() {
	m_fuel = -1;
	m_thrustQuant = -1;
	cout << "ERROR: Default constructor of CSatellite called.\n";
}

CSatellite::~CSatellite() {
	// TODO Auto-generated destructor stub
}

void CSatellite::printThrust(ostream &output){
	for(int i = 0; i < m_thrustQuant; i++){
		m_thrusts[i].printChrom(output);
	}
	output << "\n";
}

