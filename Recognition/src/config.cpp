/*
 * config.cpp
 *
 *  Created on: 18 янв. 2018 г.
 *      Author: prof1k
 */

#include "config.h"
#include "simpleini/SimpleIni.h"
#include "constans.h"


Config::Config() {
	// TODO Auto-generated constructor stub

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

void Config::read_config()
{
	const char *pszVal = 0;

	CSimpleIniA ini;
	ini.SetUnicode();
	ini.LoadFile(CONFIG_FILE);
	//ini.GetAllValues("dbhost", a_pKey, a_values)
	bool bHasMulti;
	ini.GetValue("mysql", "dbhost", "localhost", &bHasMulti);

	cout << pszVal;

}
