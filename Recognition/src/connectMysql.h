/*
 * connectMysql.h
 *
 *  Created on: 17 янв. 2018 г.
 *      Author: prof1k
 */

#include <mysql++/mysql++.h>
#include <string>
#include <iostream>


using namespace std;

#ifndef CONNECTMYSQL_H_
#define CONNECTMYSQL_H_

class connectMysql {
public:
	connectMysql(string db, string server, string user, string password, int port);
	virtual ~connectMysql();
	void connect(string db, string server, string user, string password, int port);
	bool AddVehicleNumber(string vehicle_number, bool allowed_entry, bool single_entry, string name_of_company_organization);
};

#endif /* CONNECTMYSQL_H_ */
