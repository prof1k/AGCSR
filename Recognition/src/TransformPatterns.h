/*
 * TransformPatterns.h
 *
 *  Created on: 15 янв. 2018 г.
 *      Author: prof1k
 */

#include <string>
#include <iostream>
#include <fstream>
//#include <sstream>
//#include <iterator>

using namespace std;

#ifndef TRANSFORMPATTERNS_H_
#define TRANSFORMPATTERNS_H_

class TransformPatterns {

public:
	TransformPatterns(string pathToPatterns);
	virtual ~TransformPatterns();
	// Заменяем нули на буквы
	string transformation(string vehicleNumber, string pattern_regex);
private:
	void initialize(string pathToPatterns);
};



#endif /* TRANSFORMPATTERNS_H_ */
