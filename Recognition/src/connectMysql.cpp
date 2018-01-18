/*
 * connectMysql.cpp
 *
 *  Created on: 17 янв. 2018 г.
 *      Author: prof1k
 */

#include "connectMysql.h"

mysqlpp::Connection conn(false);

connectMysql::connectMysql(string db, string server, string user, string password, int port) {
	// "DB NAME", "DB HOST", "DB USER", "DB PASSWORD", "DB PORT"
	connect(db, server, user, password, port);

}

connectMysql::~connectMysql() {
	// TODO Auto-generated destructor stub
	conn.disconnect();
}

bool connectMysql::AddVehicleNumber(string vehicle_number, bool allowed_entry, bool single_entry, string name_of_company_organization)
{
	try
	{
		mysqlpp::Query query = conn.query();
		query << "INSERT INTO Accounts " <<
				"VALUES ('" <<
				vehicle_number << "','" <<
				allowed_entry << "','" <<
				single_entry << "','" <<
				name_of_company_organization << "');";
		query.execute();
		return 1;
	}
	catch (mysqlpp::BadQuery& er)
	{
		cerr << "[MySQL error: " << er.what() << "]" << endl;
		return 0;
	}
	catch (const mysqlpp::BadConversion& er)
	{
		cerr << "[MySQL conversion error: " << er.what() << endl <<
				"\tretrivied data size: " << er.retrieved <<
				", actual size: " << er.actual_size << endl;
		return 0;
	}
	catch (const exception& er)
	{
		cerr << "[MySQL error: " << er.what() << endl;
		return 0;
	}
}

bool FindVehicleNumber(string vehicle_number)
{
	try
		{
			mysqlpp::Query query = conn.query();
			query << "SELECT * FROM ACCOUNTS where `VehicleNumber` = " <<
					"'" <<vehicle_number << "'";
			mysqlpp::StoreQueryResult store = query.store();
			if (store.num_rows() > 0)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		catch (mysqlpp::BadQuery& er)
		{
			cerr << "[MySQL error: " << er.what() << "]" << endl;
			return 0;
		}
		catch (const mysqlpp::BadConversion& er)
		{
			cerr << "[MySQL conversion error: " << er.what() << endl <<
					"\tretrivied data size: " << er.retrieved <<
					", actual size: " << er.actual_size << endl;
			return 0;
		}
		catch (const exception& er)
		{
			cerr << "[MySQL error: " << er.what() << endl;
			return 0;
		}
}

void connectMysql::connect(string db, string server, string user, string password, int port)
{
	try
	{
		conn.connect(db.c_str(), server.c_str(), user.c_str(), password.c_str(), port);
		mysqlpp::Query query = conn.query();

	}
	catch (mysqlpp::BadQuery& er)
	{
		cerr << "[MySQL error: " << er.what() << "]" << endl;
	}
	catch (const mysqlpp::BadConversion& er)
	{
		cerr << "[MySQL conversion error: " << er.what() << endl <<
				"\tretrivied data size: " << er.retrieved <<
				", actual size: " << er.actual_size << endl;
	}
	catch (const exception& er)
	{
		cerr << "[MySQL error: " << er.what() << endl;
	}
}
