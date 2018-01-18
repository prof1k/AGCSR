/*
 * TransformPatterns.cpp
 *
 *  Created on: 15 янв. 2018 г.
 *      Author: prof1k
 */

#include "TransformPatterns.h"

const int CACHE_SIZE = 50;
int pattern_size;

string* pattern_cache = NULL;
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

string TransformPatterns::transformation(string vehicleNumber)
{
	bool templ = false;
	for (size_t i = 0; i < pattern_size; i++)
	{
	if (vehicleNumber.length() == pattern_cache[i].length()-3)
	{
		//is_equals_lenght = true;
		string::iterator utf_iterator_vehicle_number = vehicleNumber.begin();
		string::iterator utf_iterator_pattern_regex = pattern_cache[i].begin();
		string result;
		while (utf_iterator_pattern_regex < pattern_cache[i].end() && (*utf_iterator_pattern_regex != '@' && *utf_iterator_pattern_regex != '#'))
		{
			utf_iterator_pattern_regex++;
		}

		while (utf_iterator_vehicle_number < vehicleNumber.end())
		{
			//string utf_character = *utf_iterator_vehicle_number;
			if (*utf_iterator_pattern_regex == '@' && *utf_iterator_vehicle_number == '0')
			{
				result += 'O';
				templ = true;
			} else if (*utf_iterator_pattern_regex == '@' && *utf_iterator_vehicle_number == '8')
			{
				result += 'B';
				templ = true;
			}
			else
			{
				result += *utf_iterator_vehicle_number;
			}
			utf_iterator_vehicle_number++;
			utf_iterator_pattern_regex++;
		}
		vehicleNumber = result;
	}
	if (templ == false)
	{
		vehicleNumber = "";
	}
	}
	return vehicleNumber;
}

void TransformPatterns::initialize(string pathToPatterns)
{
	//char* cstr = &pathToPatterns[0u];
	//strcpy(cstr, pathToPatterns.c_str());
	//ifstream patternsFile(cstr);
	ifstream patternsFile(pathToPatterns.c_str());
	string* str_cache = new string[CACHE_SIZE];

	//std::ios_base::open_mode mode;

	//mode = 8;
	//patternsFile.open(pathToPatterns.c_str());
	try
	{
		//ifstream patternsFileasd(pathToPatterns);
		if (patternsFile)
		{

		string str;
		int i = 0;
		while (getline(patternsFile,str))
		{
			//pattern_cache[i] = str.erase(str.find("ru\t")-1);
			str_cache[i] = str;
			i++;
		}
		patternsFile.close();
		pattern_cache = new string[i+1];
		for (size_t k = 0; k < i+1; k++)
		{
			pattern_cache[k] = str_cache[k];
		}
		pattern_size = i+1;
		}
		else
		{
			throw "Error opening file";
		}
	} catch (const char* ex) {
		cout << ex << endl;
	}
}

