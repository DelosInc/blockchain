#include "BlockchainHandler.h"

BlockchainHandler::BlockchainHandler() {

	options.create_if_missing = true;
	status = leveldb::DB::Open(options, "/testdb", &db);
	assert(status.ok());
	initList(1);
}

void BlockchainHandler::addBlock(Block const& block) {
	std::ostringstream archiveStream;
	boost::archive::text_oarchive archive(archiveStream);
	archive << block;
	if (status.ok()) {
		status = db->Put(leveldb::WriteOptions(), height, archiveStream.str());
	}
	blockchain.push_back(block);
	height = std::to_string(stoi(height) + 1);

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

void BlockchainHandler::initList(unsigned int height) {
	for (unsigned int i = MAXHEIGHT; i >= 1; i--) {
		blockchain.push_back(getBlock(i));
	}
}