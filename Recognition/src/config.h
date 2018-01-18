/*
 * config.h
 *
 *  Created on: 18 янв. 2018 г.
 *      Author: prof1k
 */

#include <iostream>

using namespace std;

#ifndef CONFIG_H_
#define CONFIG_H_

class Config {
public:
	Config();
	virtual ~Config();
	void read_config();
};

#endif /* CONFIG_H_ */
