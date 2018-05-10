#pragma once

#include <vector>
#include <string>
#include <list>
#include <leveldb\db.h>
#include <hex.h>
#include <osrng.h>
#include <pssr.h>
#include <rsa.h>
#include <sha.h>
#include "record.h"
#include "transaction.h"

class Wallet {
private:
	struct KeyPair {
		std::string privateKey;
		std::string publicKey;
	} keyPair;
	std::list<Record> unspentOutputs; //constructor
	unsigned long int balance; //constructor
	Transaction transaction;
	std::string sign(std::string, std::string);
	std::string getPubKeyHash();
	std::vector<Record> initialiseRecIn(unsigned long int);
	std::vector<Record> initialiseRecOut(unsigned long int, std::string);
	std::string initialiseTID();
public:
	Wallet(leveldb::DB*);
	void generateKeyPair();
	unsigned long int getBalance() const;
	Transaction initialiseTransaction(std::string, unsigned long int);
};