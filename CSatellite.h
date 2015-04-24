/*
 * CSatellite.h
 *
 *  Created on: Apr 20, 2015
 *      Author: Mark Wittekind and Drew Murray
 */

#ifndef CSATELLITE_H_
#define CSATELLITE_H_

#include "CPlanet.h"

class CSatellite : CPlanet{
public:
	CSatellite();
	virtual ~CSatellite();
	float fuel;

};

#endif /* CSATELLITE_H_ */
