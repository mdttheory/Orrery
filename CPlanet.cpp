/*
 * CPlanet.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CPlanet.h"

CPlanet::CPlanet() {
	m_par = NULL;
	m_ss = NULL;
	m_mass = -1;
	m_dynamics = CCoordSet();
	m_name = "uninitialized";
	cout << "ERROR: default constructor of CPlanet called\n";
	return;
}

CPlanet::CPlanet(const CPlanet& rhs) {
	m_par = rhs.m_par;
	m_ss = rhs.m_ss;
	m_mass = rhs.m_mass;
	m_dynamics = rhs.m_dynamics;
	m_name = rhs.m_name;
}

CPlanet::CPlanet(float mass, CCoordSet ccs, string name,Par* par, CSolarSystem* ss) {
	m_ss = ss;
	m_par = par;
	m_mass = mass;
	m_dynamics = ccs;
	m_name = name;
}

CPlanet::~CPlanet() {

}

CSVector CPlanet::calcForce(CSolarSystem* ss){
	CSVector zero;
	return zero;
}

float CPlanet::calcEccentricity(){
	return 0;

}
void CPlanet::setDynamics(CCoordSet newSet){
	m_dynamics = newSet;
	if(m_dynamics.m_position.mag() > m_aphelion){
		m_aphelion = m_dynamics.m_position.mag();
	} else if(m_dynamics.m_position.mag() < m_perihelion){
		m_perihelion = m_dynamics.m_position.mag();
	}
	return;
}

