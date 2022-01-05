#include "Blockchain.h"
#define _CRT_SECURE_NO_DEPRECATE
#pragma warning (disable : 4996)


Student_info sv;
string getHash;
int getIndex;
int nonce;

vector <Block> Chain;
vector <string> hashChain;
string getName;
string getCode;

int insertNewStudent(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student)
{
	const char* s[4] = { s1, s2, s3, s4 };
	sqlite3* DB;
	char* messageError;
	blockChain bc(student);

	string sql("INSERT INTO SinhVien (\"Code\", \"Name\") VALUES('" + student.code + "', '" + student.name + "'); "
		"INSERT INTO Diem (\"Index\", \"Code\", \"Subject\", \"Score\", \"Hash\", \"PreHash\") VALUES( 0, '" + student.code + "', '" + student.subject + "', '" + to_string(student.score) + "', '" + bc.hash + "', '0'); ");
	int i;
	for (i = 0; i < 4; i++)
	{
		int exit = sqlite3_open(s[i], &DB);

		exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
		if (exit != SQLITE_OK) {
			cerr << "Da xay ra loi khi them thong tin sinh vien!" << endl;
			sqlite3_free(messageError);
			return 0;
		}
	}
	return 1;
}

int insertOldStudent(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student)
{
	const char* s[4] = { s1, s2, s3, s4 };
	sqlite3* DB;
	char* messageError;
	string hashTemp, finalHash;
	hashTemp = generateHash(student);
	finalHash = mine(student, hashTemp);
	string sql = "INSERT INTO Diem (\"Index\", \"Code\", \"Subject\", \"Score\", \"Hash\", \"PreHash\") VALUES( " + to_string(getIndex) + ", '" + student.code + "', '" + student.subject + "', '" + to_string(student.score) + "', '" + finalHash + "', '" + getHash + "'); ";
	int i;
	for (i = 0; i < 4; i++)
	{

		int exit = sqlite3_open(s[i], &DB);
		exit = sqlite3_exec(DB, sql.c_str(), NULL, NULL, &messageError);

		if (exit != SQLITE_OK) {
			cerr << "Da xay ra loi khi them diem!" << endl;
			sqlite3_free(messageError);
			return 0;
		}
	}
	return 1;
}

int checkMaSinhVien(const char* s, Student_info student)
{
	sv.code = "";
	sqlite3* DB;
	char* messageError;
	string sql = "SELECT * FROM Diem WHERE Code = '" + student.code + "' ORDER BY ID DESC LIMIT 1; ";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callMa, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi kiem tra ma so sinh vien!" << endl;
		sqlite3_free(messageError);
	}
	else
	{
		if (sv.code != "")
		{
			return 0;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int callMa(void* data, int argc, char** argv, char** azColName)
{
	char* numstr = argv[1];
	getIndex = atoi(numstr);
	getIndex++;
	getHash = argv[5];
	sv.code = argv[2];
	sv.subject = argv[3];
	sv.score = stod(argv[4]);
	return 0;
}

int checkName(const char* s, Student_info student)
{
	sv.name = "";
	sqlite3* DB;
	char* messageError;
	string sql = "SELECT * FROM SinhVien WHERE Code = '" + student.code + "';";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callName, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi kiem tra thong tin sinh vien!" << endl;
		sqlite3_free(messageError);
	}
	else
	{
		if (sv.name != "" && sv.name != student.name)
		{
			return 0;
		}
		else if (sv.name != "" && sv.name == student.name)
		{
			return 1;
		}
		else
		{
			return -1;
		}
	}
	return 0;
}

int callName(void* data, int argc, char** argv, char** azColName)
{
	sv.name = argv[2];
	return 0;
}

int printData(const char* s, Student_info student)
{
	sv.code = "";
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM Diem WHERE Code = '" + student.code + "'";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi in thong tin sinh vien!" << endl;
		sqlite3_free(messageError);
	}
	else
	{
		if (sv.code == "")
		{
			cout << "Sinh vien chua co thong tin" << endl;
		}
	}
	return 0;
}

int callback(void* NotUsed, int argc, char** argv, char** azColName)
{
	sv.code = argv[2];
	for (int i = 3; i < 5; i++)
	{
		cout << azColName[i] << ": " << argv[i] << endl;
	}
	cout << endl;
	return 0;
}

void createFile(const char* s, Student_info student)
{
	sv.code = "";
	sqlite3* DB;
	char* messageError;
	string sql1 = "SELECT * FROM SinhVien WHERE Code = '" + student.code + "';";
	int exit = sqlite3_open(s, &DB);
	exit = sqlite3_exec(DB, sql1.c_str(), callFile1, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi xuat file du lieu!" << endl;
		sqlite3_free(messageError);
	}
	else
	{
		if (sv.code == "")
		{
			cout << "Sinh vien chua co thong tin" << endl;
		}
		else
		{
			string sql2 = "SELECT * FROM Diem WHERE Code = '" + student.code + "';";
			int exit = sqlite3_open(s, &DB);
			exit = sqlite3_exec(DB, sql2.c_str(), callFile2, NULL, &messageError);
			if (exit != SQLITE_OK)
			{
				cerr << "Da xay ra loi khi xuat file du lieu!" << endl;
				sqlite3_free(messageError);
			}
			else
			{
				if (sv.code == "")
				{
					cout << "Sinh vien chua co thong tin" << endl;
				}
				else
				{
					cout << "Xuat file du lieu thanh cong" << endl;
				}
			}
		}
	}
}

int callFile1(void* NotUsed, int argc, char** argv, char** azColName)
{
	sv.code = argv[1];
	const char* name = "QuanLyDiemSinhVien.txt";
	ofstream output;
	output.open(name, ios::out);
	if (output.is_open())
	{
		int i;
		for (i = 1; i < 3; i++)
		{
			string colName = azColName[i];
			string Argv = argv[i] ? argv[i] : "NULL";
			output << colName + ": " + Argv << endl;
		}
		output << endl;
		output.close();
	}
	else
		cout << "\nMo file " << name << " that bai" << endl;
	return 0;
}

int callFile2(void* NotUsed, int argc, char** argv, char** azColName)
{
	sv.code = argv[2];
	const char* name = "QuanLyDiemSinhVien.txt";
	ofstream output;
	output.open(name, ios::app);
	if (output.is_open())
	{
		int i;
		for (i = 3; i < 5; i++)
		{
			string colName = azColName[i];
			string Argv = argv[i] ? argv[i] : "NULL";
			output << colName + ": " + Argv << endl;
		}
		output << endl;
		output.close();
	}
	else
		cout << "\nMo file " << name << " that bai" << endl;
	return 0;
}

string difficult(int level)
{
	string dif = string(level, '0');
	return dif;
}

string generateHash(Student_info student)
{
	string hash1;
	string hash2;
	string finalHash;
	finalHash = sha256(student.code + student.name + student.subject + to_string(student.score) + getHash + to_string(nonce));
	return finalHash;
}

string mine(Student_info student, string blockHash)
{
	nonce = 0;
	while (blockHash.find(difficult(4), 0) != 0)
	{
		nonce++;
		blockHash = generateHash(student);
	}
	return blockHash;
}

void file2compare1(const char* s1)
{
	const char* name = "GiangVien.txt";
	ofstream output;
	output.open(name, ios::out);
	output.close();
	sqlite3* DB;
	char* messageError;
	string sql("SELECT * FROM SinhVien;" "SELECT * FROM Diem;");
	int exit = sqlite3_open(s1, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), call2compare1, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi xuat file du lieu!" << endl;
		sqlite3_free(messageError);
	}
}

int call2compare1(void* NotUsed, int argc, char** argv, char** azColName)
{
	const char* name = "GiangVien.txt";
	ofstream output;
	output.open(name, ios::app);
	if (output.is_open())
	{
		int i;
		for (i = 1; i < argc; i++)
		{
			string colName = azColName[i];
			string Argv = argv[i] ? argv[i] : "NULL";
			output << colName + ": " + Argv << endl;
		}
		output << endl;
		output.close();
	}
	else
		cout << "\nMo file " << name << " that bai" << endl;
	return 0;
}

void file2compare2(const char* s2)
{
	const char* name = "PhongDaoTao.txt";
	ofstream output;
	output.open(name, ios::out);
	output.close();
	sqlite3* DB;
	char* messageError;
	string sql("SELECT * FROM SinhVien;" "SELECT * FROM Diem;");
	int exit = sqlite3_open(s2, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), call2compare2, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi xuat file du lieu!" << endl;
		sqlite3_free(messageError);
	}
}

int call2compare2(void* NotUsed, int argc, char** argv, char** azColName)
{
	const char* name = "PhongDaoTao.txt";
	ofstream output;
	output.open(name, ios::app);
	if (output.is_open())
	{
		int i;
		for (i = 1; i < argc; i++)
		{
			string colName = azColName[i];
			string Argv = argv[i] ? argv[i] : "NULL";
			output << colName + ": " + Argv << endl;
		}
		output << endl;
		output.close();
	}
	else
		cout << "\nMo file " << name << " that bai" << endl;
	return 0;
}

void file2compare3(const char* s3)
{
	const char* name = "TruongBoMon.txt";
	ofstream output;
	output.open(name, ios::out);
	output.close();
	sqlite3* DB;
	char* messageError;
	string sql("SELECT * FROM SinhVien;" "SELECT * FROM Diem;");
	int exit = sqlite3_open(s3, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), call2compare3, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi xuat file du lieu!" << endl;
		sqlite3_free(messageError);
	}
}

int call2compare3(void* NotUsed, int argc, char** argv, char** azColName)
{
	const char* name = "TruongBoMon.txt";
	ofstream output;
	output.open(name, ios::app);
	if (output.is_open())
	{
		int i;
		for (i = 1; i < argc; i++)
		{
			string colName = azColName[i];
			string Argv = argv[i] ? argv[i] : "NULL";
			output << colName + ": " + Argv << endl;
		}
		output << endl;
		output.close();
	}
	else
		cout << "\nMo file " << name << " that bai" << endl;
	return 0;
}

void file2compare4(const char* s4)
{
	const char* name = "BoPhanXuLyDiem.txt";
	ofstream output;
	output.open(name, ios::out);
	output.close();
	sqlite3* DB;
	char* messageError;
	string sql("SELECT * FROM SinhVien;" "SELECT * FROM Diem;");
	int exit = sqlite3_open(s4, &DB);
	exit = sqlite3_exec(DB, sql.c_str(), call2compare4, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi xuat file du lieu!" << endl;
		sqlite3_free(messageError);
	}
}

int call2compare4(void* NotUsed, int argc, char** argv, char** azColName)
{
	const char* name = "BoPhanXuLyDiem.txt";
	ofstream output;
	output.open(name, ios::app);
	if (output.is_open())
	{
		int i;
		for (i = 1; i < argc; i++)
		{
			string colName = azColName[i];
			string Argv = argv[i] ? argv[i] : "NULL";
			output << colName + ": " + Argv << endl;
		}
		output << endl;
		output.close();
	}
	else
		cout << "\nMo file " << name << " that bai" << endl;
	return 0;
}

bool compareFile(const char* fname1, const char* fname2)
{
	FILE* fp1, * fp2;
	int ch1, ch2;
	fp1 = fopen(fname1, "r");
	fp2 = fopen(fname2, "r");
	if (fp1 == NULL)
	{
		printf("Khong the mo file %s.", fname1);
		exit(1);
	}
	else if (fp2 == NULL)
	{
		printf("Khong the mo file %s.", fname2);
		exit(1);
	}
	else
	{
		ch1 = getc(fp1);
		ch2 = getc(fp2);
		while ((ch1 != EOF) && (ch2 != EOF) && (ch1 == ch2)) {
			ch1 = getc(fp1);
			ch2 = getc(fp2);
		}
		if (ch1 == ch2)
		{
			return true;
		}
		else if (ch1 != ch2)
		{
			return false;
		}
	}
}

int checkSecurity(const char* s1, const char* s2, const char* s3, const char* s4)
{
	file2compare1(s1);
	file2compare2(s2);
	file2compare3(s3);
	file2compare4(s4);

	if (compareFile("GiangVien.txt", "PhongDaoTao.txt"))
	{
		if (compareFile("GiangVien.txt", "TruongBoMon.txt"))
		{
			if (compareFile("GiangVien.txt", "BoPhanXuLyDiem.txt"))
				return 1;
			else
				return 0;
		}
		else
			return 0;
	}
	else
	{
		return 0;
	}
}


int getGenesisFromDataBase(const char* s, Student_info student)
{
	getCode = "";
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM SinhVien WHERE Code = '" + student.code + "'";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callGenesis, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi lay thong tin sinh vien!" << endl;
		sqlite3_free(messageError);
	}
	else
	{
		if (getCode == "")
		{
			cout << "Sinh vien chua co thong tin" << endl;
		}
	}
	return 0;
}

int callGenesis(void* NotUsed, int argc, char** argv, char** azColName)
{
	getCode = argv[1];
	getName = argv[2];
	return 0;
}

int getBlockchainFromDataBase(const char* s, Student_info student)
{
	sv.code = "";
	sqlite3* DB;
	char* messageError;

	string sql = "SELECT * FROM Diem WHERE Code = '" + student.code + "'";

	int exit = sqlite3_open(s, &DB);

	exit = sqlite3_exec(DB, sql.c_str(), callBlockChain, NULL, &messageError);
	if (exit != SQLITE_OK)
	{
		cerr << "Da xay ra loi khi lay thong tin sinh vien!" << endl;
		sqlite3_free(messageError);
	}
	else
	{
		if (sv.code == "")
		{
			cout << "Sinh vien chua co thong tin" << endl;
		}
	}
	return 0;
}

int callBlockChain(void* NotUsed, int argc, char** argv, char** azColName)
{
	sv.code = argv[2];
	Student_info data;
	data.name = getName;
	data.code = getCode;
	data.subject = argv[3];
	data.score = stod(argv[4]);
	
	int index = stod(argv[1]);
	string Hash = argv[5];
	string PrevHash = argv[6];
	Block newBlock(index, data, PrevHash);
	
	Chain.push_back(newBlock);
	hashChain.push_back(Hash);
	return 0;
}


void isBlockChainValid(const char* s, Student_info student)
{
	getGenesisFromDataBase(s, student);
	getBlockchainFromDataBase(s, student);
	int size = Chain.size() == hashChain.size() ? Chain.size() : -1;
	if (size != -1)
	{
		for (int i = 0; i < size; i++ )
		{
			if (hashChain[i] != Chain[i].getHash())
			{
				cout << "BlockChain khong bao toan!";
				Chain.clear();
				hashChain.clear();
				return;
			}
			if (i != 0)
			{
				Block previousBlock = Chain[i - 1];
				if (previousBlock.getHash() != Chain[i].getPreviousHash())
				{
					cout << "BlockChain khong bao toan!";
					Chain.clear();
					hashChain.clear();
					return;
				}
			}
		}
		cout << "BlockChain bao toan!";
	}
	else
		cout << "BlockChain khong bao toan!";
	Chain.clear();
	hashChain.clear();
}

