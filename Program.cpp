#include <iostream>
#include "Blockchain.h"

int main()
{
	string hash;
	Student_info student;
	const char* dir1 = R"(.\DataBase\QuanLyDiemSinhVien_PHONGDAOTAO.db)";
	const char* dir2 = R"(.\DataBase\QuanLyDiemSinhVien_GIANGVIEN.db)";
	const char* dir3 = R"(.\DataBase\QuanLyDiemSinhVien_TRUONGKHOA.db)";
	const char* dir4 = R"(.\DataBase\QuanLyDiemSinhVien_BOPHANXULYDIEM.db)";
	checkDatabase(dir1, dir2, dir3, dir4, student);
	return 0;
}