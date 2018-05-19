#pragma once

#include <vector>
#include <queue>
#include <string>
#include <list>
#include <hex.h>
#include <osrng.h>
#include <pssr.h>
#include <rsa.h>
#include <sha.h>
#include <db_cxx.h>

#include "record.h"
#include "transaction.h"
#include "block.h"
#include "client.h"
#include "blockchainHandler.h"

class Wallet {
private:
	struct KeyPair {
		std::string privateKey;
		std::string publicKey;
	} keyPair;
	std::list<Record> unspentOutputs;
	unsigned long int balance;
	Transaction transaction;
	std::string sign(std::string, std::string);
	std::string getPubKeyHash();
	std::vector<Record> initialiseRecIn(unsigned long int);
	std::vector<Record> initialiseRecOut(unsigned long int, std::string);
public:
	Wallet() = default;
	Wallet(BlockchainHandler*);
	Wallet(BlockchainHandler*, std::string);
	void generateKeyPair();
	unsigned long int getBalance() const;
	Transaction initialiseTransaction(std::string, unsigned long int);
};