#include "myDB.h"



myDB::myDB(std::string path, std::string dbFileName)
	: db(NULL, 0),
	dbFileName(path + dbFileName),
	cFlags(DB_CREATE) {
	try {
		db.set_error_stream(&std::cerr);
		db.open(NULL, dbFileName.c_str(), NULL, DB_QUEUE, cFlags, 0);
	}
	catch (DbException &e) {
		std::cerr << "Error opening database\n";
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error opening database\n";
		std::cerr << e.what() << std::endl;
	}
}

void myDB::write(unsigned int height, Block block) {
	Dbt key(&height, sizeof(height));
	Dbt data(&block, sizeof(block));
	int ret = db.put(NULL, &key, &data, DB_NOOVERWRITE);
	if (ret == DB_KEYEXIST) {
		db.err(ret, "Write failed since key already exists");
	}
}

void myDB::close() {
	try {
		db.close(0);
		std::cout << "Database closed";
	}
	catch (DbException &e) {
		std::cerr << "Error closing database\n";
		std::cerr << e.what() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Error closing database\n";
		std::cerr << e.what() << std::endl;
	}
}


myDB::~myDB() {
	close();
}
