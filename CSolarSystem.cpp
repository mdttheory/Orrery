/*
 * CSolarSystem.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSolarSystem.h"

CSolarSystem::CSolarSystem() {
	m_par = NULL;
}

CSolarSystem::CSolarSystem(Par* par) {
	//Sun
	CSVector zero;
	m_par = par;
	CCoordSet ccs(zero,zero,zero);
	CPlanet Sun(m_par->SolarMass, ccs, string("Sun"),m_par,this);
	m_planets.push_back(Sun);

	//TODO Mercury stats
	CSVector pos(10,100,1000);
	CSVector vel(1,2,3);
	CCoordSet ccs2(pos,vel,zero);
	CPlanet Mercury(m_par->SolarMass/5, ccs2, string("Mercury"),m_par,this);
	m_planets.push_back(Mercury);

}

CSolarSystem::~CSolarSystem() {
}

vector<double> CSolarSystem::potential(){
	short n = m_planets.size();
	short i = 0;
	vector<double> energies (n,1);
	for(i = 0; i < n; i++){
		for(short j = i + 1; j < n; j++){
			float r = m_planets[i].getDynamics().m_position.distance(m_planets[j].getDynamics().m_position);
			double total = -m_par->G*double(m_planets[i].m_mass)*double(m_planets[j].m_mass)/double(r);
			energies[i] += total;
			energies[j] += total;
		}
	}
	return energies;
}

vector<double> CSolarSystem::kinetic(){
	vector<double> energies;
	for (vector<CPlanet>::iterator it = m_planets.begin();it < m_planets.end(); it++) {
		energies.push_back(double(.5)*it->m_mass*it->getDynamics().m_velocity.magSquared());
	}
	return energies;
}

vector<double> CSolarSystem::totalEnergy(vector<double> kinetic, vector<double> potential){
	vector<double> energies;
	for (short i = 0; i < kinetic.size(); i++){
		energies.push_back(kinetic[i] + potential[i]);
	}
	return energies;
}

