#include "BlockchainHandler.h"

BlockchainHandler::BlockchainHandler() {

	options.create_if_missing = true;
	status = leveldb::DB::Open(options, "/testdb", &db);
	assert(status.ok());
}

void BlockchainHandler::addBlock(Block const& block) {
	std::ostringstream archiveStream;
	boost::archive::text_oarchive archive(archiveStream);
	archive << block;
	if (status.ok()) {
		status = db->Put(leveldb::WriteOptions(), height, archiveStream.str());
	}
}

Block BlockchainHandler::getBlock(unsigned int height) {
	std::string archiveData;
	std::istringstream archiveStream(archiveData);
	boost::archive::text_iarchive archive(archiveStream);
	status = db->Get(leveldb::ReadOptions(), std::to_string(height), &archiveData);
	Block block;
	archive >> block;
	return block;
}


BlockchainHandler::~BlockchainHandler() {
	delete db;
}
