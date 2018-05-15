#include "DB.h"



DB::DB(std::string path, std::string dbFileName)
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

void DB::write(std::string keystr, std::string datastr) {
	Dbt key(&keystr, keystr.size());
	Dbt data(&datastr, datastr.size());
	int ret = db.put(NULL, &key, &data, DB_NOOVERWRITE);
	if (ret == DB_KEYEXIST) {
		db.err(ret, "Write failed since key already exists", keystr);
	}
}

void DB::close() {
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


DB::~DB() {
	close();
}
