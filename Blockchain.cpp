#include "Blockchain.h"

using namespace std;

int checkMa;
int checkTen;

void getInfor(const char* s, Student_info& student)
{
	cout << "\n--------------------------------------------------------------------------------------";
	cout << "\n---------------------------- Nhap thong tin sinh vien --------------------------------" << endl;
	cout << "\tMoi nhap MSSV: ";
	cin >> student.code;
	cout << "\tMoi nhap ten: ";
	getline(cin.ignore(), student.name);
	cout << "\tMoi nhap mon hoc: ";
	getline(cin, student.subject);
	cout << "\tMoi nhap diem: ";
	while (!(cin >> student.score))
	{
		cerr << "Vui long nhap vao 1 so diem hop le: ";
		cin.clear();
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	checkInfo(s, student);
}

void checkInfo(const char* s, Student_info& student)
{
	checkTen = checkName(s, student);
	checkMa = checkMaSinhVien(s, student);
	if (checkTen == 0)
	{
		cout << "Co the ban da nhap sai ma so hoac ten cua sinh vien nay! Xin moi nhap lai thong tin!" << endl;
		getInfor(s, student);
	}
}

int checkChoice(const char* s, Student_info student)
{
	if (checkTen == -1)
	{
		string flag = "";
		cout << "\t\t\tKhong tim thay thong tin cua sinh vien!" << endl;
		cout << "\t\t\tBan muon cap nhat thong tin vao he thong?" << endl;
		cout << "\t\t\tNhan y de tiep tuc - Nhan n de dung lai" << endl;
		cin >> flag;
		while (flag != "y" && flag != "n")
		{
			cout << "\t\t\tChi duoc nhap y hoac n. Moi ban nhap lai!" << endl;
			cin >> flag;
		}
		if (flag == "y")
			return 1;
		else
			return 0;
	}
	else if (checkTen == 1)
	{
		string flag = "";
		cout << "\t\t\tThong tin cua sinh vien da co trong he thong" << endl;
		cout << "\t\t\tBan muon them diem moi vao he thong?" << endl;
		cout << "\t\t\tNhan y de tiep tuc - Nhan n de dung lai" << endl;
		cin >> flag;
		while (flag != "y" && flag != "n")
		{
			cout << "\t\t\tChi duoc nhap y hoac n. Moi ban nhap lai!" << endl;
			cin >> flag;
		}
		if (flag == "y")
			return 1;
		else
			return 0;
	}
}

void menuProofOfWork(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student)
{
	int i;
	const char* name[4] = { "GIANG VIEN", "PHONG DAO TAO", "TRUONG KHOA", "BO PHAN XU LY DIEM" };
	
		for (i = 0; i < 4; i++)
		{
			cout << "\t\t\t----------------------------------------" << endl;
			cout << "\t\t\t THONG BAO CHO " << name[i] << endl;
			cout << "\t\t\t CANH BAO CO SINH VIEN THAY DOI THONG TIN" << endl;
			cout << "\t\t\t----------------------------------------" << endl;
			int check = checkChoice(s1, student);
			if (check == 0)
			{
				cout << "Khong the them thong tin sinh vien vi khong nhan duoc su dong y cua " << name[i] << "." << endl;
				break;
			}
		}
		if (i == 4)
		{
			if (checkTen == -1)
			{
				int x = insertNewStudent(s1, s2, s3, s4, student);
				if (x == 1)
					cout << "Them thong tin sinh vien thanh cong!" << endl;
			}
				
			else if (checkTen == 1)
			{
				int x = insertOldStudent(s1, s2, s3, s4, student);
				if (x == 1)
					cout << "Them diem thanh cong!" << endl;
			}	
		}

}

void checkDatabase(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student)
{
	if (checkSecurity(s1, s2, s3, s4) == 1)
	{
		menu(s1, s2, s3, s4, student);
	}
	else
	{
		cout << "Database da bi thay doi du lieu nen ban khong the thuc hien bat ki thao tac nao!\nXin hay kiem tra lai du lieu o cac Database!!" << endl;
		return;
	}
}


void menu(const char* s1, const char* s2, const char* s3, const char* s4, Student_info student)
{
	int choice;
	cout << "\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t|  CHUONG TRINH QUAN LY DIEM SINH VIEN  |" << endl;
	cout << "\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t	1. Nhap thong tin sinh vien" << endl;
	cout << "\t\t\t	2. In diem sinh vien" << endl;
	cout << "\t\t\t	3. Xuat file du lieu" << endl;
	cout << "\t\t\t	4. Kiem tra tinh bao toan cua du lieu" << endl;
	cout << "\t\t\t	5. Thoat" << endl;
	cout << "\t\t\t----------------------------------------" << endl;
	cout << "\t\t\t  Nhap mot trong cac phim de lua chon: [1/2/3/4/5]" << endl;
	cout << "\t\t\t----------------------------------------" << endl;
	cout << "Ban chon: ";
	do {
		cin >> choice;
		switch (choice)
		{
		case 1:
			if (checkSecurity(s1, s2, s3, s4) == 1)
			{
				getInfor(s1, student);
				menuProofOfWork(s1, s2, s3, s4, student);
				cout << "\nNhap phim de tiep tuc [1/2/3/4/5]: ";
				break;
			}
			else
			{
				cout << "Database da bi thay doi du lieu nen ban khong the thuc hien bat ki thao tac nao!\nXin hay kiem tra lai du lieu o cac Database!!" << endl;
				return;
			}
		case 2:
			if (checkSecurity(s1, s2, s3, s4) == 1)
			{
				cout << "\nNhap MSSV ban muon xem diem: ";
				cin >> student.code;
				printData(s1, student);
				cout << "\nNhap phim de tiep tuc [1/2/3/4/5]: ";
				break;
			}
			else
			{
				cout << "Database da bi thay doi du lieu nen ban khong the thuc hien bat ki thao tac nao!\nXin hay kiem tra lai du lieu o cac Database!!" << endl;
				return;
			}
		case 3:
			if (checkSecurity(s1, s2, s3, s4) == 1)
			{
				cout << "\nBan da chon xuat file du lieu" << endl;
				cout << "\nNhap MSSV muon xuat file: ";
				cin >> student.code;
				createFile(s1, student);
				cout << "\nNhap phim de tiep tuc [1/2/3/4/5]: ";
				break;
			}
			else
			{
			cout << "Database da bi thay doi du lieu nen ban khong the thuc hien bat ki thao tac nao!\nXin hay kiem tra lai du lieu o cac Database!!" << endl;
			return;
			}
		case 4:
			if (checkSecurity(s1, s2, s3, s4) == 1)
			{
				cout << "\nBan da chon kiem tra bao toan du lieu" << endl;
				cout << "\nNhap MSSV de kiem tra BlockChain tuong ung: ";
				cin >> student.code;
				isBlockChainValid(s1, student);
				cout << "\nNhap phim de tiep tuc [1/2/3/4/5]: ";
				break;
			}
			else
			{
				cout << "Database da bi thay doi du lieu nen ban khong the thuc hien bat ki thao tac nao!\nXin hay kiem tra lai du lieu o cac Database!!" << endl;
				return;
			}
		case 5:
			cout << "\nBan da chon thoat chuong trinh";
			return;
		default:
			cout << "\nKhong co chuc nang nay";
			cout << "\nNhap phim de tiep tuc [1/2/3/4/5]: ";
			break;
		}
	} while (choice != 5);
}