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
/*
float CPlanet::potential(){
	float total = 0;
	for (vector<CPlanet>::const_iterator it = m_ss->m_planets.begin();it < m_ss->m_planets.end(); it++) {
		if(it->m_name!=m_name){
			float r = m_dynamics.m_position.distance(it->m_dynamics.m_position);
			total-=m_par->G*m_mass*it->m_mass/r;
		}
	}
	return total;
}
*/
float CPlanet::kinetic(){
	return .5*m_mass*m_dynamics.m_velocity.magSquared();
}
/*
float CPlanet::totalEnergy(){
	return kinetic()+potential();
}
*/

CSVector CPlanet::calcForce(CSolarSystem* ss){
	CSVector zero;
	return zero;
}

float CPlanet::calcEccentricity(){
	return 0;

}

