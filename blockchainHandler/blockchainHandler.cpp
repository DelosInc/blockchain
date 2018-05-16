#include "BlockchainHandler.h"

BlockchainHandler::BlockchainHandler() {
	

	/*options.create_if_missing = true;
	status = leveldb::DB::Open(options, "/testdb", &db);
	assert(status.ok());
	initList(1);*/
}

void BlockchainHandler::addBlock(Block const& block) {
	height++;
	db.write(height, block);
	/*std::ostringstream archiveStream;
	boost::archive::text_oarchive archive(archiveStream);
	archive << block;
	if (status.ok()) {
		leveldb::WriteOptions write_options;
		write_options.sync = true;
		status = db->Put(leveldb::WriteOptions(), height, archiveStream.str());
	}
	blockchain.push_back(block);
	height = std::to_string(stoi(height) + 1);*/

}

Block BlockchainHandler::getBlock(unsigned int height) {
	/*std::string archiveData;
	std::istringstream archiveStream(archiveData);
	boost::archive::text_iarchive archive(archiveStream);
	status = db->Get(leveldb::ReadOptions(), std::to_string(height), &archiveData);
	Block block;
	archive >> block;
	return block;*/
}

unsigned int BlockchainHandler::getHeight() {
	return height;
}

std::string BlockchainHandler::getBlockHash() {


	/*leveldb::Iterator* it = db->NewIterator(leveldb::ReadOptions());
	it->SeekToLast();
	return getBlock(stoi(it->key().ToString())).getBlockHash();*/
}