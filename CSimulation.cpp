/*
 * CSimulation.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSimulation.h"

CSimulation::CSimulation(CSolarSystem solarSystem, Par* par, string name) {
	m_par = par;
	m_name = name;
	m_SS = solarSystem;

}

CSimulation::~CSimulation() {
}

void CSimulation::Euler(CSVector &pos_i, CSVector &vel_i, string name){
	float dt = m_par->dt;
	CSVector new_pos = pos_i + vel_i*dt;
	vel_i += CalcA(pos_i,name,dt)*dt;
	pos_i = new_pos;
}

void CSimulation::RK(CSVector &pos_i, CSVector &vel_i, string name) {
	// http://doswa.com/2009/01/02/fourth-order-runge-kutta-numerical-integration.html

	float dt = m_par->dt;

	CSVector pos[4], vel[4], acc[4];
	pos[0] = pos_i;
	vel[0] = vel_i;
	acc[0] = CalcA(pos[0], name, dt / 2.0);

	pos[1] = pos_i + vel[0] * (dt * 0.5);
	vel[1] = vel_i + acc[0] * (dt * 0.5);
	acc[1] = CalcA(pos[1], name, dt / 2.0);

	pos[2] = pos_i + vel[1] * (dt * 0.5);
	vel[2] = vel_i + acc[1] * (dt * 0.5);
	acc[2] = CalcA(pos[2], name, dt / 2.0);

	pos[3] = pos_i + vel[2] * dt;
	vel[3] = vel_i + acc[2] * dt;
	acc[3] = CalcA(pos[3], name, dt);

	pos_i += (vel[0] + vel[1] * 2.0 + vel[2] * 2.0 + vel[3]) * (dt / 6.0);
	vel_i += (acc[0] + acc[1] * 2.0 + acc[2] * 2.0 + acc[3]) * (dt / 6.0);

	return;
}

CSVector CSimulation::CalcDv(float dt, vector<CPlanet> planets,
		unsigned short i) {
	CSVector v_init, new_v, sum, r_vec, zero;
	float G = this->m_SS.m_par->G;
	float dist;

	sum = zero;
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {
		dist = m_SS.m_planets[i].getDynamics().m_position.distance(
				it->getDynamics().m_position);

		if (dist > 0) {
			//TODO: Check direction of r_vec
			r_vec = it->getDynamics().m_position
					+ m_SS.m_planets[i].getDynamics().m_position * -1.0;
			sum += (r_vec / pow(dist, 3)) * (it->m_mass);

		}
	}

	return (sum * dt * G);
}

CSVector CSimulation::CalcA(CSVector pos, string name, float dt) {
	CSVector sum, r_vec;
	float G = this->m_SS.m_par->G;
	double dist;

	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {
		dist = pos.distance(it->getDynamics().m_position);
		double dist_cubed = pow(dist, 3);
		if (dist_cubed == 0) dist_cubed = pow(10,-200);

		if (it->m_name != name) {
			r_vec = it->getDynamics().m_position + pos * -1.0;
			sum += (r_vec / dist_cubed) * (it->m_mass);
		}
		//else if (name == "Pluto")cout<<"v: "<<it->getDynamics().m_velocity << "\n";
	}

	return (sum * G);
}

void CSimulation::print_pos(ostream &pos_stream) {
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
			it < m_SS.m_planets.end(); it++) {
		pos_stream << (*(it->getDynamicsPtr())).m_position << "\n";
	}
	pos_stream << "-\n";

}

void CSimulation::print_en(ostream &en_stream, double init_en) {

	en_stream << (m_SS.totalEnergy()-init_en)/init_en;

}

void CSimulation::update() {
	//cout << "Using integration method " << m_par->integration_method << "\n";
	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
				it < m_SS.m_planets.end(); it++) {
		if (m_par->integration_method == 4) {
			RK(it->getDynamicsPtr()->m_position, it->getDynamicsPtr()->m_velocity, it->m_name);
		}
		else if (m_par->integration_method == 1) {
			Euler(it->getDynamicsPtr()->m_position, it->getDynamicsPtr()->m_velocity, it->m_name);
		}

		else
			cout << "ERROR, integration method set to " << m_par->integration_method
					<< "\n";
	}
}
