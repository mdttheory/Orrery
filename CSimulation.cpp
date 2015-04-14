/*
 * CSimulation.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSimulation.h"

CSimulation::CSimulation(CSolarSystem solarSystem,Par* par) {
	m_par = par;
	m_SS = solarSystem;

}

CSimulation::~CSimulation() {
}

void CSimulation::RK() {
	// https://math.okstate.edu/people/yqwang/teaching/math4513_fall11/Notes/rungekutta.pdf
	vector<CSVector> k1, k2, k3, k4;

	float dt = this->m_SS.m_par->dt;

	unsigned short i = 0;
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {

		k1.push_back(it->getDynamics().m_velocity * dt);
		i++;
	}
	cout << "k1[1] " << k1[1] << "\n";

	i = 0;
	CSolarSystem new_SS(m_SS);
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {
		new_SS.m_planets[i].getDynamicsPtr()->m_position += k1[i] / 2;

		k2.push_back(CalcDv(dt / 2.0, new_SS.m_planets,i));
		i++;
	}
	cout << "k2[1] " << k2[1] << "\n";

	i = 0;
	new_SS = m_SS;
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {
		new_SS.m_planets[i].getDynamicsPtr()->m_position += k2[i] / 2;

		k3.push_back(CalcDv(dt / 2, new_SS.m_planets,i));
		i++;
	}
	cout << "k3[1] " << k3[1] << "\n";

	i = 0;
	new_SS = m_SS;
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();	it < m_SS.m_planets.end(); it++) {
		new_SS.m_planets[i].getDynamicsPtr()->m_position += k3[i];

		k4.push_back(CalcDv(dt, new_SS.m_planets,i));

		i++;
	}
	cout << "k4[1] " << k4[1] << "\n";
	i = 0;
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {
		CCoordSet newCCS = m_SS.m_planets[i].getDynamics();
		newCCS.m_position = it->getDynamics().m_position+ (k1[i] + k2[i]*2 +k3[i]*2 + k4[i]) * (1.0 / 6.0);
		newCCS.m_velocity = (k1[i] + k2[i]*2 +k3[i]*2 + k4[i]) * (1.0 / 6.0) / dt;
		m_SS.m_planets[i].setDynamics(newCCS);
		i++;
	}
	return;
}

CSVector CSimulation::CalcDv(float dt, vector<CPlanet> planets,unsigned short i) {
	CSVector v_init, new_v, sum, r_vec, zero;
	float G = this->m_SS.m_par->G;
	float dist;

	sum = zero;
	 for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();it < m_SS.m_planets.end(); it++) {
		 dist = m_SS.m_planets[i].getDynamics().m_position.distance(it->getDynamics().m_position);

		 if(dist > 0){
			 //TODO: Check direction of r_vec
			 r_vec = it->getDynamics().m_position + m_SS.m_planets[i].getDynamics().m_position*-1;
			 sum += (r_vec/pow(dist,3))*(it->m_mass);

		 }
	 }


	return (sum * dt * G);
}


void CSimulation::print_pos(ostream &pos_stream)
{
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();it < m_SS.m_planets.end(); it++) {
			pos_stream << (*(it->getDynamicsPtr())).m_position << "\n";
		}
		pos_stream << "-\n";
}

void CSimulation::update(){
	cout << "Using integration method " << m_par->integration_method << "\n";
	if (m_par->integration_method==4){
		float x = m_SS.m_planets[1].getDynamics().m_position.m_x;
		RK();
		x = m_SS.m_planets[1].getDynamics().m_position.m_x;
		int y = 0;

	}
	else cout << "ERROR, integration method set to " << m_par->integration_method << "\n";
}
