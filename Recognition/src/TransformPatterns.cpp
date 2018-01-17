/*
 * TransformPatterns.cpp
 *
 *  Created on: 15 янв. 2018 г.
 *      Author: prof1k
 */

#include "TransformPatterns.h"

const int CACHE_SIZE = 50;

string pattern_cache[CACHE_SIZE];
/// <summary>
/// Описание метода
/// </summary>
/// <param name="pathToPatterns">Описание параметра</param>
/// <returns>Ogbcfybt возвращаемого значения</returns>
TransformPatterns::TransformPatterns(string pathToPatterns) {
	// TODO Auto-generated constructor stub
	initialize(pathToPatterns);
}

TransformPatterns::~TransformPatterns() {
	// TODO Auto-generated destructor stub
}

string TransformPatterns::transformation(string vehicleNumber, string pattern_regex)
{
	if (vehicleNumber.length() == pattern_regex.length())
	{
	string::iterator utf_iterator_vehicle_number = vehicleNumber.begin();
	string::iterator utf_iterator_pattern_regex = pattern_regex.begin();
	string result;

	while (utf_iterator_vehicle_number < vehicleNumber.begin())
	{
		//string utf_character = *utf_iterator_vehicle_number;
		if (*utf_iterator_pattern_regex == '@' && *utf_iterator_vehicle_number == '0')
		{
			result += 'O';
		}
		else
		{
			result += *utf_iterator_vehicle_number;
		}
		utf_iterator_vehicle_number++;
		utf_iterator_pattern_regex++;
	}
	vehicleNumber = result;
	return vehicleNumber;
	}
	else
	{
		return vehicleNumber;
	}
}

void TransformPatterns::initialize(string pathToPatterns)
{
	ifstream patternsFile(pathToPatterns.c_str());
	try
	{
		//ifstream patternsFileasd(pathToPatterns);
		if (patternsFile.is_open())
		{
		string str;
		int i = 0;
		while (getline(patternsFile,str))
		{
			pattern_cache[i] = str;
			i++;
		}
		patternsFile.close();
		}
		else
		{
			throw "Error opening file";
		}
	} catch (char* ex) {
		cout << ex << endl;
	}
}

