#pragma once

#include <db_cxx.h>

class DB {
private:
	Db db;
	std::string dbFileName;
	u_int32_t cFlags;
	void close();
public:
	DB(std::string, std::string);
	void write(std::string, std::string);
	~DB();
};


