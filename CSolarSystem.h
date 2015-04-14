/*
 * CSolarSystem.h
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CSOLARSYSTEM_H_
#define CSOLARSYSTEM_H_

#include "CPlanet.h"
#include "Parameters.cpp"
#include <vector>

using namespace std;

class CSolarSystem {
public:
	CSolarSystem();
	CSolarSystem(Par* par);
	virtual ~CSolarSystem();
	vector<CPlanet> m_planets;
	Par* m_par;
	vector<double> potential();
	vector<double> kinetic();
	vector<double> totalEnergy(vector<double> kinetic, vector<double> potential);

	friend ostream &operator<<(ostream &output, const CSolarSystem &D) {
		for (vector<CPlanet>::const_iterator it = D.m_planets.begin();it < D.m_planets.end(); it++) {
			output << *it;
		}
		output << "-\n";
		return output;
	}

};

#endif /* CSOLARSYSTEM_H_ */
