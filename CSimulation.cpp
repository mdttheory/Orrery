/*
 * CSimulation.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSimulation.h"

CSimulation::CSimulation(CSolarSystem solarSystem, Par* par, string name, unsigned short coreNum, unsigned int genNum) {
	m_par = par;
	m_name = name;
	m_coreNum = coreNum;
	m_genNum = genNum;
	m_SS = solarSystem;
	vector<bool> flag;
	CCoordSet tempSet;
	for (unsigned int i = 0; i<m_par->satsPerCore;i++){
		SatName newSatelliteName;
		newSatelliteName.coreNum=coreNum;
		newSatelliteName.genNum=genNum;
		CSatellite a(m_par, &m_SS, newSatelliteName, flag);
		a.m_name.selfID=a.unsignedLongLongRand();

		tempSet = m_SS.getPlanetDynamics(a.m_homePlanetName);

		//TODO Set velocity based on thrust[0] (force thrust[0] to start at t=0)
		tempSet.m_velocity.m_y += solarSystem.m_planets[3].calcEscapeVel(6371000)*((i-2.0)/2.0);
		tempSet.m_position.m_x = tempSet.m_position.m_x+6371000;



		a.setDynamics(tempSet);

		a.m_thrusts[0].m_t[0]=0;
		m_SS.m_sats.push_back(a);
		}
}

CSimulation::CSimulation(CSolarSystem solarSystem, Par* par, string name, CSimulation b, CSimulation c, unsigned short coreNum) {
	m_par = par;
	m_name = name;
	m_SS = solarSystem;
	m_coreNum = coreNum;
	m_genNum = b.m_genNum + 1;
	vector<bool> flag;
	CCoordSet tempSet;
	for (unsigned int i = 0; i<m_par->satsPerCore;i++){
		CSatellite a(b.m_SS.m_sats[i], flag);
		a = b.m_SS.m_sats[i]*c.m_SS.m_sats[i];
		tempSet = m_SS.getPlanetDynamics(a.m_homePlanetName);
		//TODO Set velocity based on thrust[0] (force thrust[0] to start at t=0)
		tempSet.m_velocity.m_x = tempSet.m_velocity.m_y*10*i;
		a.setDynamics(tempSet);
		m_SS.m_sats.push_back(a);
	}
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

//CSVector CSimulation::CalcDv(float dt, vector<CPlanet> planets,
//		unsigned short i) {
//	CSVector v_init, new_v, sum, r_vec, zero;
//	float G = this->m_SS.m_par->G;
//	float dist;
//
//	sum = zero;
//	for (vector<CPlanet>::iterator it = m_SS.m_planets.begin();
//			it < m_SS.m_planets.end(); it++) {
//		dist = m_SS.m_planets[i].getDynamics().m_position.distance(
//				it->getDynamics().m_position);
//
//		if (dist > 0) {
//			//TODO: Check direction of r_vec
//			r_vec = it->getDynamics().m_position
//					+ m_SS.m_planets[i].getDynamics().m_position * -1.0;
//			sum += (r_vec / pow(dist, 3)) * (it->m_mass);
//
//		}
//	}
//
//	return (sum * dt * G);
//}

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
	for (vector<CSatellite>::iterator it = m_SS.m_sats.begin();
			it < m_SS.m_sats.end(); it++) {
		pos_stream << (*(it->getDynamicsPtr())).m_position << "\n";
	}
	pos_stream << "-\n";

}

void CSimulation::print_en(ostream &en_stream, double init_en) {

	en_stream << (m_SS.totalEnergy()-init_en)/init_en;

}

void CSimulation::update(unsigned long currStep) {
	//cout << "Using integration method " << m_par->integration_method << "\n";
	CSolarSystem newSS(m_SS);

	for (vector<CSatellite>::iterator it = newSS.m_sats.begin();
				it < newSS.m_sats.end(); it++) {
		if(it->m_thrusts[it->m_thrusts.size()-1].m_t[0] == currStep){
			it->getDynamicsPtr()->m_velocity.m_x+=it->m_thrusts[it->m_thrusts.size()-1].m_dvx[0];
			it->getDynamicsPtr()->m_velocity.m_y+=it->m_thrusts[it->m_thrusts.size()-1].m_dvy[0];
			it->getDynamicsPtr()->m_velocity.m_z+=it->m_thrusts[it->m_thrusts.size()-1].m_dvz[0];
			it->m_thrusts.pop_back();
		}
	}

	for (vector<CPlanet>::iterator it = newSS.m_planets.begin();
				it < newSS.m_planets.end(); it++) {
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
	for (vector<CSatellite>::iterator it = newSS.m_sats.begin();
					it < newSS.m_sats.end(); it++) {
			if (m_par->integration_method == 4) {
				RK(it->getDynamicsPtr()->m_position, it->getDynamicsPtr()->m_velocity, "NULL");
			}
			else if (m_par->integration_method == 1) {
				Euler(it->getDynamicsPtr()->m_position, it->getDynamicsPtr()->m_velocity, "NULL");
			}

			else
				cout << "ERROR, integration method set to " << m_par->integration_method
						<< "\n";
	}
	m_SS = newSS;
}
