/*
 * CSolarSystem.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CSolarSystem.h"
#include <math.h>

CSolarSystem::CSolarSystem() {
	m_par = NULL;
}

CSolarSystem::CSolarSystem(Par* par) {


	m_par = par;
	float sm = m_par->SolarMass;
	CSVector zero;

	{
	//Sun
	CCoordSet ccs_Sun(zero,zero,zero);
	CPlanet Sun(0,sm,0,0, ccs_Sun, string("Sun"),m_par,this);
	m_planets.push_back(Sun);
	}{
	//Mercury
	CCoordSet ccs_Mercury(zero,zero,zero);
	CPlanet Mercury(0.110653875,sm*1.66012*pow(10,-7),46001200000,69816900000, ccs_Mercury, string("Mercury"),m_par,this);
	m_planets.push_back(Mercury);
	}{
	//Venus
	CCoordSet ccs_Venus(zero,zero,zero);;
	CPlanet Venus(0.0382227106,sm*2.44781*pow(10,-6),107477000000,108939000000, ccs_Venus, string("Venus"),m_par,this);
	m_planets.push_back(Venus);
	}{
	//Earth
	CCoordSet ccs_Earth(zero,zero,zero);;
	CPlanet Earth(0.0274016693,sm*3.003467*pow(10,-6),147095000000,151930000000, ccs_Earth, string("Earth"),m_par,this);
	m_planets.push_back(Earth);
	}{
	//Mars
	CCoordSet ccs_Mars(zero,zero,zero);;
	CPlanet Mars(0.0291469985,sm*3.22713*pow(10,-7),206700000000,249200000000, ccs_Mars, string("Mars"),m_par,this);
	m_planets.push_back(Mars);
	}{
	//Jupiter
	CCoordSet ccs_Jupiter(zero,zero,zero);;
	CPlanet Jupiter(0.00558505361,sm*9.5458*pow(10,-4),740573600000,816520800000, ccs_Jupiter, string("Jupiter"),m_par,this);
	m_planets.push_back(Jupiter);
	}{
	//TODO Saturn pos/vel
	CCoordSet ccs_Saturn(zero,zero,zero);;
	CPlanet Saturn(0.016231562,sm*2.85812*pow(10,-4),1353572956000,1513325783000, ccs_Saturn, string("Saturn"),m_par,this);
	m_planets.push_back(Saturn);
	}{
	//TODO Uranus pos/vel
	CCoordSet ccs_Uranus(zero,zero,zero);;
	CPlanet Uranus(0.0178023584,sm*4.36576*pow(10,-5),2735118100000,3006224700000, ccs_Uranus, string("Uranus"),m_par,this);
	m_planets.push_back(Uranus);
	}{
	//TODO Neptune pos/vel
	CCoordSet ccs_Neptune(zero,zero,zero);;
	CPlanet Neptune(0.0125663706,sm*5.15028*pow(10,-5),4459504400000,4537580900000, ccs_Neptune, string("Neptune"),m_par,this);
	m_planets.push_back(Neptune);
	}{
	//TODO Pluto pos/vel
	CCoordSet ccs_Pluto(zero,zero,zero);;
	CPlanet Pluto(0.296705973,sm*6.583*pow(10,-9),4437000000000,7311000000000, ccs_Pluto, string("Pluto"),m_par,this);
	m_planets.push_back(Pluto);
	}
	//cout << "m_aphelion*tan(0.296705973) = " << Pluto.m_aphelion*tan(0.296705973) << "\n";
	for (vector<CPlanet>::iterator it = m_planets.begin();it < m_planets.end(); it++) {
		it->getDynamicsPtr()->m_position.m_x=it->m_aphelion*cos(it->m_angle);
		it->getDynamicsPtr()->m_position.m_z=it->m_aphelion*sin(it->m_angle);
		it->getDynamicsPtr()->m_velocity.m_y=it->calcTheorVel();
	}
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
	for (unsigned int i = 0; i < kinetic.size(); i++){
		energies.push_back(kinetic[i] + potential[i]);
	}
	return energies;
}
