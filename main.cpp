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
#include "CSimulation.h"

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

	CSimulation my_Sim(newSS, &par);
	my_Sim.print_pos(pos_stream);

	for(unsigned int t = 0; t<par.maxTimeSteps; t++){
		cout << "Timetstep " << t << " of " << par.maxTimeSteps << "\n";
		my_Sim.update();
		my_Sim.print_pos(pos_stream);
	}

	pos_of.close();
	return 0;
}


