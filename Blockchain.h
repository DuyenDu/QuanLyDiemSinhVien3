#include <iostream>
#include <stdio.h>
#include <functional>
#include <string>
#include <vector>
#include <fstream>
#include "sha256.h"
#include <sqlite3.h>
#include <limits>

using namespace std;

struct Student_info
{
	string code;
	string name;
	string subject;
	double score;
};

struct Block
{
	int index;
	string blockHash;
	string previousHash;
	Student_info data;
	int nonce;

	string difficult(int level)
	{
		string dif = string(level, '0');
		return dif;
	}

	string generateHash()
	{
		string finalHash;
		finalHash = sha256(data.code + data.name + data.subject + to_string(data.score) + previousHash + to_string(nonce));
		return finalHash;
	}

	string mine()
	{
		nonce = 0;
		while (blockHash.find(difficult(4), 0) != 0)
		{
			nonce++;
			blockHash = generateHash();
		}
		return blockHash;
	}

	Block(int i, Student_info d, string preHash)
	{
		index = i;
		data = d;
		previousHash = preHash;
		blockHash = mine();
	}

	int getIndex()
	{
		return index;
	}
	string getHash()
	{
		return blockHash;
	}

	string getPreviousHash()
	{
		return previousHash;
	}

	bool isHashValid()
	{
		return generateHash() == blockHash;
	}
	double getScore()
	{
		return data.score;
	}
	string getName()
	{
		return data.name;
	}
	string getSubject()
	{
		return data.subject;
	}
	string getID()
	{
		return data.code;
	}
};

struct blockChain
{
	string hash;
	vector<Block> chain;
	blockChain(Student_info student)
	{
		Block genesis = createGenesisBlock(student);
		chain.push_back(genesis);
	}

	Block createGenesisBlock(Student_info student)
	{
		Block genesis(0, student, "0");
		hash = genesis.blockHash;
		return genesis;
	}
	Block* getLastedBlock()
	{
		return &chain.back();
	}
	void addBlock(Student_info student)
	{
		int index = (int)chain.size();
		string preHash = (int)chain.size() > 0 ? getLastedBlock()->getHash() : "0";
		Block newBlock(index, student, preHash);
		chain.push_back(newBlock);
	}
	bool isChainValid()
	{
		vector <Block>::iterator it;
		int chainLength = (int)chain.size();
		for (it = chain.begin(); it != chain.end(); ++it)
		{
			Block currentBlock = *it;
			if (!currentBlock.isHashValid())
			{
				return false;
			}
			if (it != chain.begin())
			{
				Block preBlock = *(it - 1);
				if (currentBlock.getPreviousHash() != preBlock.getHash())
				{
					return false;
				}
			}
		}
		return true;
	}
};

void checkDatabase(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student);
void getInfor(const char* s, Student_info& student);
void checkInfo(const char* s, Student_info& student);
void menu(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student);
void menuProofOfWork(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student);
int checkChoice(const char* s, Student_info student);
int printData(const char* s, Student_info student);
int callFile1(void* NotUsed, int argc, char** argv, char** azColName);
int callFile2(void* NotUsed, int argc, char** argv, char** azColName);
void createFile(const char* s, Student_info student);

int insertNewStudent(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student);
int insertOldStudent(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student);
int checkMaSinhVien(const char* s, Student_info student);
int callMa(void* NotUsed, int argc, char** argv, char** azColName);
int callback(void* NotUsed, int argc, char** argv, char** azColName);
int checkName(const char* s, Student_info student);
int callName(void* data, int argc, char** argv, char** azColName);

string difficult(int level);
string generateHash(Student_info student);
string mine(Student_info student, string blockHash);

void file2compare1(const char* s1);
int call2compare1(void* NotUsed, int argc, char** argv, char** azColName);
void file2compare2(const char* s2);
int call2compare2(void* NotUsed, int argc, char** argv, char** azColName);
void file2compare3(const char* s3);
int call2compare3(void* NotUsed, int argc, char** argv, char** azColName);
void file2compare4(const char* s3);
int call2compare4(void* NotUsed, int argc, char** argv, char** azColName);
bool compareFile(const char* fname1, const char* fname2);
int checkSecurity(const char* s1, const char* s2, const char* s3, const char* s4);

int getGenesisFromDataBase(const char* s, Student_info student);
int callGenesis(void* NotUsed, int argc, char** argv, char** azColName);
int getBlockchainFromDataBase(const char* s, Student_info student);
int callBlockChain(void* NotUsed, int argc, char** argv, char** azColName);
void isBlockChainValid(const char* s, Student_info student);
