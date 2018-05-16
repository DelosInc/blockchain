#pragma once

#include <db_cxx.h>
#include "block.h"

class myDB {
private:
	Db db;
	std::string dbFileName;
	u_int32_t cFlags;
	void close();
public:
	myDB(std::string, std::string);
	void write(unsigned int, Block);
	~myDB();
};


