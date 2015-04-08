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

