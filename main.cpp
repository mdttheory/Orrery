/*
 * main.cpp
 *
 *  Created on: Apr 8, 2015
 *      Author: Mark Wittekind and Drew Murray
 */
#include "CSolarSystem.h"
#include "Parameters.cpp"
#include <algorithm>
#include <fstream>

using namespace std;

int main()
{
	streambuf * pos_buf;
	ofstream pos_of;
	//set to filename
	pos_of.open("data/raw_positions.txt");
	pos_buf = pos_of.rdbuf();
	ostream pos_stream(pos_buf);


	Par par;
	CSolarSystem newSS(&par);
	cout << newSS << "\n";
	cout << "0 Kinetic " << newSS.kinetic()[0] << "\n";
	cout << "1 Kinetic " << newSS.kinetic()[1] << "\n";
	cout << "0 Potential " << newSS.potential()[0] << "\n";
	cout << "1 Potential " << newSS.potential()[1] << "\n";
	cout << "0 Total " << newSS.totalEnergy(newSS.kinetic(),newSS.potential())[0] << "\n";
	cout << "1 Total " << newSS.totalEnergy(newSS.kinetic(),newSS.potential())[1] << "\n";

	pos_stream << newSS;
	/*
	for (vector<CPlanet>::iterator it = m_planets.begin();it < m_planets.end(); it++) {
		pos_stream << it->getDynamicsPtr()->m_position.m_x
	}
	*/



	return 0;
}


