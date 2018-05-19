#include <iostream>

#include "wallet.h"


Wallet::Wallet(BlockchainHandler *handler) {
	Block current;
	balance = 0;
	generateKeyPair();
	std::string address = getPubKeyHash();
	std::vector <Record> ownInputs;
	std::queue <Record> ownOutputs;
	for (unsigned int height = handler->getHeight(); height >= 1; height--) {
		current = handler->getBlock(height);
		for (unsigned int tx_i = 0; tx_i < 6; tx_i++) {
			for (unsigned int recOut_i = 0; recOut_i < 2; recOut_i++) {
				if (current.getTransaction(tx_i).getRecOut(recOut_i).getOutSig().compare(address) == 0) {
					ownOutputs.push(current.getTransaction(tx_i).getRecOut(recOut_i));
				}
			}
			for (unsigned int recIn_i = 0; recIn_i < current.getTransaction(tx_i).getRecInSize(); recIn_i++) {
				if (current.getTransaction(tx_i).getRecIn(recIn_i).getInSig().pubKey.compare(address) == 0) {
					ownInputs.push_back(current.getTransaction(tx_i).getRecIn(recIn_i));
				}
			}
		}
	}
	while (!ownOutputs.empty()) {
		for (std::vector<Record>::iterator it = ownInputs.begin(); it != ownInputs.end(); it++) {
			if (*it == ownOutputs.front()) {
				ownOutputs.pop();
				break;
			}
			balance += ownOutputs.front().getAmount();
			unspentOutputs.push_back(ownOutputs.front());
			ownOutputs.pop();
		}
	}
}

Wallet::Wallet(BlockchainHandler *handler, std::string address) {
	Block current;
	balance = 0;
	std::vector <Record> ownInputs;
	std::queue <Record> ownOutputs;
	for (unsigned int height = handler->getHeight(); height >= 1; height--) {
		current = handler->getBlock(height);
		for (unsigned int tx_i = 0; tx_i < 6; tx_i++) {
			for (unsigned int recOut_i = 0; recOut_i < 2; recOut_i++) {
				if (current.getTransaction(tx_i).getRecOut(recOut_i).getOutSig().compare(address) == 0) {
					ownOutputs.push(current.getTransaction(tx_i).getRecOut(recOut_i));
				}
			}
			for (unsigned int recIn_i = 0; recIn_i < current.getTransaction(tx_i).getRecInSize(); recIn_i++) {
				if (current.getTransaction(tx_i).getRecIn(recIn_i).getInSig().pubKey.compare(address) == 0) {
					ownInputs.push_back(current.getTransaction(tx_i).getRecIn(recIn_i));
				}
			}
		}
	}
	while (!ownOutputs.empty()) {
		for (std::vector<Record>::iterator it = ownInputs.begin(); it != ownInputs.end(); it++) {
			if (*it == ownOutputs.front()) {
				ownOutputs.pop();
				break;
			}
			balance += ownOutputs.front().getAmount();
			unspentOutputs.push_back(ownOutputs.front());
			ownOutputs.pop();
		}
	}
}

std::string Wallet::sign(std::string privateKeyHex, std::string record) {
	using Signer = CryptoPP::RSASS<CryptoPP::PSSR, CryptoPP::SHA256>::Signer;

	CryptoPP::RSA::PrivateKey privateKey;
	privateKey.Load(CryptoPP::StringSource(privateKeyHex, true, new CryptoPP::HexDecoder()).Ref()); // decode and load keys

	std::string signature;
	Signer signer(privateKey);
	CryptoPP::AutoSeededRandomPool rng;
	CryptoPP::StringSource ss(record, true,
		new CryptoPP::SignerFilter(rng, signer,
			new CryptoPP::HexEncoder(
				new CryptoPP::StringSink(signature)))); //sign
	return signature;
}

std::string Wallet::getPubKeyHash() {
	CryptoPP::SHA256 hash;
	std::string pubKey = keyPair.publicKey;
	std::string digest;
	CryptoPP::StringSource s(pubKey, true, new CryptoPP::HashFilter(hash, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
	return digest;
}

std::vector<Record> Wallet::initialiseRecIn(unsigned long int amount) {
	unsigned long int sum = 0;
	std::vector<Record> recIn;
	for (std::list<Record>::iterator it = unspentOutputs.begin(); it != unspentOutputs.end(); ++it) {
		if (amount > sum) {
			std::string concatenatedRecord = std::to_string(it->getAmount()) + it->getOutSig();
			it->setInSig(sign(keyPair.privateKey, concatenatedRecord), keyPair.publicKey, concatenatedRecord);
			sum += it->getAmount();
			recIn.push_back(*it);
			unspentOutputs.pop_front();
		}
		else {
			break;
		}
	}
	return recIn;
}

std::vector<Record> Wallet::initialiseRecOut(unsigned long int amount, std::string address) {
	std::vector<Record> recOut;
	recOut[0].setAmount(amount);
	recOut[0].setInSig(nullptr, nullptr, nullptr);
	recOut[0].setOutSig(address); //outgoing amount
	recOut[1].setAmount(getBalance() - amount);
	recOut[1].setInSig(nullptr, nullptr, nullptr);
	recOut[1].setOutSig(getPubKeyHash()); //crediting change to self
	return recOut;
}

void Wallet::generateKeyPair() {
	CryptoPP::AutoSeededRandomPool rng; //random pool generator

	CryptoPP::RSA::PrivateKey privateKey;
	privateKey.GenerateRandomWithKeySize(rng, 10);
	CryptoPP::RSA::PublicKey publicKey(privateKey); //generate keys

	publicKey.Save(CryptoPP::HexEncoder(new CryptoPP::StringSink(keyPair.publicKey)).Ref());
	privateKey.Save(CryptoPP::HexEncoder(new CryptoPP::StringSink(keyPair.privateKey)).Ref()); //save keys
}

unsigned long int Wallet::getBalance() const {
	return balance;
}

Transaction Wallet::initialiseTransaction(std::string address, unsigned long int amount) {
	transaction.setRecIn(initialiseRecIn(amount));
	transaction.setRecOut(initialiseRecOut(amount, address));
	transaction.setTimestamp();
	transaction.setTID();
	return transaction;
}

int main() {
	char choice;
	std::string path, filename;
	std::cout << "Enter filename and path";
	std::cin >> path >> filename;
	BlockchainHandler handler(path, filename);
	std::cout << "Do you have an address (Y/n)";
	std::cin >> choice;
	Wallet w;
	if (choice == 'Y') {
		try {
			std::string address;
			std::cout << "Enter address";
			w = Wallet(&handler, address);
		}
		catch (DbException& e) {
			std::cerr << "Error opening database\n";
			std::cerr << e.what() << std::endl;
		}
		catch (std::exception &e) {
			std::cerr << "Error opening database\n";
			std::cerr << e.what() << std::endl;
		}
	}
	else {
		try {
			std::string address;
			std::cout << "Enter address";
			w = Wallet(&handler, address);
		}
		catch (DbException& e) {
			std::cerr << "Error opening database\n";
			std::cerr << e.what() << std::endl;
		}
		catch (std::exception &e) {
			std::cerr << "Error opening database\n";
			std::cerr << e.what() << std::endl;
		}
	}
	unsigned long int balance = w.getBalance();
	unsigned long int amount;
	std::string outputAddress;
	std::string hostname, port;
	std::cout << "Enter the hostname: ";
	std::cin >> hostname;
	std::cout << "Enter the port: ";
	std::cin >> port;
	std::cout << "Enter recipient address: ";
	std::cin >> outputAddress;
	std::cout << "Enter amount to be sent: ";
	std::cin >> amount;
	if (amount >= balance) {
		try {
			boost::asio::io_context io_context;
			Client client(io_context, hostname, port);
			client.setTransaction(w.initialiseTransaction(outputAddress, amount));
			io_context.run();
		}
		catch (std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
	return 0;
}