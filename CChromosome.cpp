/*
 * CChromosome.cpp
 *
 *  Created on: Apr 24, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#include "CChromosome.h"

CChromosome::CChromosome(Par* par, default_random_engine &gen) {
	uniform_real_distribution<float> distThrust(-1.0*(par->maxThrusterVel),par->maxThrusterVel);
	uniform_int_distribution<int> distTime(0,par->maxTimeSteps);
	m_gen = gen;
	m_par = par;

	m_dvx[1] = -1.0*(par->maxThrusterVel);
	m_dvx[2] = (par->maxThrusterVel);
	m_dvx[0] = distThrust(m_gen);

	m_dvy[1] = -1.0*(par->maxThrusterVel);
	m_dvy[2] = (par->maxThrusterVel);
	m_dvy[0] = distThrust(m_gen);

	m_dvz[1] = -1.0*(par->maxThrusterVel);
	m_dvz[2] = (par->maxThrusterVel);
	m_dvz[0] = distThrust(m_gen);

	m_t[1] = 0;
	m_t[2] = float((par->maxTimeSteps));
	m_t[0] = float(distTime(m_gen));
}
CChromosome::CChromosome(const CChromosome &rhs, default_random_engine &gen) {
	m_gen = gen;
	m_par = rhs.m_par;

	m_dvx[1] = rhs.m_dvx[1];
	m_dvx[2] = rhs.m_dvx[2];
	m_dvx[0] = rhs.m_dvx[0];

	m_dvy[1] = rhs.m_dvy[1];
	m_dvy[2] = rhs.m_dvy[2];
	m_dvy[0] = rhs.m_dvy[0];

	m_dvz[1] = rhs.m_dvz[1];
	m_dvz[2] = rhs.m_dvz[2];
	m_dvz[0] = rhs.m_dvz[0];

	m_t[1] = rhs.m_t[1];
	m_t[2] = rhs.m_t[2];
	m_t[0] = rhs.m_t[0];
}


CChromosome::~CChromosome() {
	// TODO Auto-generated destructor stub
}

CChromosome CChromosome::operator*(CChromosome& rhs)
{
	uniform_real_distribution<float> distZOne(0.0,1.0);

	CChromosome newChrom(rhs, m_gen);
	float r = distZOne(m_gen);
	for(unsigned short i = 0;i<newChrom.chromSize();i++){
		// TODO: Figure out how to NOT re-create the distribution each time
		uniform_real_distribution<float> dist(newChrom[i][1],newChrom[i][2]);
		if (r < m_par->mutateChance){
			newChrom[i][0] = dist(m_gen);
		}
		else if (r < (m_par->mutateChance+1.0)/2.0){
			newChrom[i][0] = (*this)[i][0];
		}
		else newChrom[i][0] = rhs[i][0];
	}
	return newChrom;
}

float* CChromosome::operator[](const int nIndex)
{
	if (nIndex==0)return m_dvx;
	else if (nIndex==1)return m_dvy;
	else if (nIndex==2)return m_dvz;
	else if (nIndex==3)return m_t;
	else{
		cout << "ERROR CChromosome::operator[] has invalid index " << nIndex << "\n";
		float* x = NULL;
		return x;
	}

}

bool CChromosome::operator==(const CChromosome& rhs)
{
	if(m_dvx[0]==rhs.m_dvx[0] && m_dvy[0]==rhs.m_dvy[0] && m_dvz[0]==rhs.m_dvz[0] && m_t[0]==rhs.m_t[0])
		return true;
	return false;
}

bool CChromosome::operator!=(const CChromosome& rhs)
{
	if(m_dvx[0]!=rhs.m_dvx[0] || m_dvy[0]!=rhs.m_dvy[0] || m_dvz[0]!=rhs.m_dvz[0] || m_t[0]!=rhs.m_t[0])
		return true;
	return false;
}

bool CChromosome::operator<(const CChromosome& rhs){
	return(this->m_t[0]<rhs.m_t[0]);
}
bool CChromosome::operator>(const CChromosome& rhs){
	return(this->m_t[0]>rhs.m_t[0]);
}
bool CChromosome::operator>=(const CChromosome& rhs){
	return(this->m_t[0]>=rhs.m_t[0]);
}
bool CChromosome::operator<=(const CChromosome& rhs){
	return(this->m_t[0]<=rhs.m_t[0]);
}