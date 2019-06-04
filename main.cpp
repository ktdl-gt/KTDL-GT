/*
	ĐỒ ÁN CẤU TRÚC DỮ LIỆU VÀ GIẢI THUẬT
	Thành Viên:
		Phạm Tến Đạt
		Nguyễn Hoàng Duy
		Bùi Văn Huy
		Trần Thanh Thái
*/
#include<iostream>
#include<string>
#include<Windows.h>
#include<iomanip>
#include<fstream>
#include<conio.h>
#include<ctime>

#define MAX 100
using namespace std;

struct Taikhoan
{
	string sUser;
	string sPass;
	string sPin;
	string sHoten;
	float fTien;
	string sLoaitien;
};
struct ID
{
	string thoigian;
	string sUser;
	string sPass;
	string sPin;
	string chucnang;
	string sHoten;
	float fTien;
	string sLoaitien;
};

//NGUYEN MAU HAM
void FileInput(ID TK[], string User, string Pin, int nN);
int demdong(); //dem so dong trong file ID.dat
void KTGD(ID TK[], string User, string Pin, int &nN);	//Kiem Tra giao dich
void chuyentien(Taikhoan TK[], string User, string Pin, int nN); //chuyen tien
int timkiem(Taikhoan TK[], string User, string Pin, int nN);//tim kiem tai khoan
void giaodienruttien();//giao dien rut tien
void RutTien(Taikhoan TK[], string User, string Pin, int nN);	//rut tien
string kiemTraTime(string sX);
void dangnhap(Taikhoan TK[], ID ID[], string User, string Pin, int nN);	//Dang nhap
void color(int nN);	//mau chu
void DocFile(Taikhoan TK[], int &nSoTK);	//Doc file
void xuat(Taikhoan TK[], int nSoTK);
string Dau_sao();	//doi mat khau thanh dau *
//CHUONG TRINH CHINH
void main()
{
	ID id[MAX];
	Taikhoan TK[MAX];
	string User, Pin;
	int nSoTK;
	DocFile(TK, nSoTK);
	//tao khung dang nhap
	color(14);
	cout << "\t\t\t\t*********************************\n";
	cout << "\t\t\t\t*";
	color(10);
	cout << "\tDANG NHAP HE THONG\t";
	color(14);
	cout << "*\n";
	cout << "\t\t\t\t*********************************\n";

	dangnhap(TK, id, User, Pin, nSoTK);

	system("pause");
}

//DINH NGHIA HAM CON
//dang nhap he thong
void dangnhap(Taikhoan TK[], ID ID[], string User, string Pin, int nN)
{

	int nChon;
	int j = 0;
	do {
		color(14);
		cout << setw(29) << "User:\t"; rewind(stdin); getline(cin, User);

		Pin = Dau_sao();
		if (User != TK[j].sUser && Pin != TK[j].sPass)
		{
			color(12);
			cout << "\n\tBan da Nhap sai lan: " << j + 1 << endl;
			if (j == 3)
			{
				cout << "Ban da nhap qua so lan quy dinh\n";
				break;
			}

		}
		else {
			do {
				system("cls");
				color(11);
				cout << "\tDang Nhap Thanh Cong \n";
				color(7);
				cout << "\t\t1.Rut tien:\n";
				cout << "\t\t2.Chuyen Tien:\n";
				cout << "\t\t3.Xem noi dung giao dich\n";
				cout << "\t\t4.Chon 0 de thoat chung trinh\n";
				color(11);
				cout << "\t Moi Ban Chon Chuc Nang\n";
				cin >> nChon;
				switch (nChon)
				{
				case 1:
					RutTien(TK, User, Pin, nN);
					break;
				case 2:
					chuyentien(TK, User, Pin, nN);
					break;
				case 3:
					int dong;
					KTGD(ID, User, Pin, dong);
					break;
				case 0:
					break;
				}

			} while (nChon = 0);
		}
		j++;
	} while (TK[j].sUser != User && TK[j].sPass != Pin);

}
//Kiem tra giao dich
void KTGD(ID TK[], string User, string Pin, int &nN) {
	FileInput(TK, User, Pin, nN);
	nN = demdong();
	for (int i = 0; i < nN; i++)
	{
		if (TK[i].sUser == User && TK[i].sPass == Pin)
		{
			cout << TK[i].thoigian << "#" << TK[i].chucnang << "#" << TK[i].sPin << "#" << TK[i].sHoten << "#" << TK[i].fTien << "#"
				<< TK[i].sLoaitien;
		}
	}
}
//doc file ID
void FileInput(ID TK[], string User, string Pin, int nN)
{
	ifstream fcin;
	fcin.open("Id.dat");

	rewind(stdin);
	getline(fcin, TK->thoigian, '\n');
	fcin.ignore('#');

	rewind(stdin);
	getline(fcin, TK->sUser, '#');

	rewind(stdin);
	getline(fcin, TK->sPass, '#');

	rewind(stdin);
	getline(fcin, TK->sPin, '#');

	rewind(stdin);
	getline(fcin, TK->sHoten, '#');

	fcin >> TK->fTien;
	fcin.ignore(1);

	rewind(stdin);
	getline(fcin, TK->sLoaitien, '\n');
}
//chuyen tien
void chuyentien(Taikhoan TK[], string User, string Pin, int nN)
{
	string time;
	string STK;
	float ht;
	float ct;
	int timTK = timkiem(TK, User, Pin, nN);
	if (timTK != -1)
	{
		color(2);
		cout << "Nhap so TK thu huong: ";
		cin >> STK;
		for (int i = 0; i < nN; i++)
		{
			if (TK[i].sPin == STK)
			{
				do {
					do {
						color(2);
						cout << "Nhap so tien can chuyen: ";
						cin >> ct;
						if (TK[timTK].fTien - ct < 50000)
						{
							color(12);
							cout << "Tai khoan quy khach khong du vui long kiem tra lai\n";
						}
						else {
							ht = TK[i].fTien + ct;
							cout << "Ban da chyen tien thanh cong\n";
							ofstream os;
							os.open("ID.dat", ios::app);
							os << kiemTraTime(time) << "#" << "Chuyen tien" << "#" << TK[i].sUser << "#" << TK[i].sPin << "#" << TK[i].sPass
								<< "#" << TK[i].sHoten << "#" << TK[i].fTien - ct << "#" << TK[i].sLoaitien << "\n";
							os.close();
						}

					} while ((ct < 50000));
				} while ((TK[timTK].fTien - ct < 50000));
			}
		}
	}
}
//Rut tien
void RutTien(Taikhoan TK[], string User, string Pin, int nN)
{
	string time;
	float tien;
	float sodu;
	int timTK = timkiem(TK, User, Pin, nN);
	color(2);

	{
		if (timTK != -1)
		{
			system("cls");

			color(14);
			cout << "\t\t\t\t*********************************\n";
			cout << "\t\t\t\t*";
			color(10);
			cout << "\t\tRut TIen\t";
			color(14);
			cout << "*\n";
			cout << "\t\t\t\t*********************************\n";
			do {
				do {
					color(2);
					cout << "Nhap so tien can rut: ";
					cin >> tien;
					sodu = TK[timTK].fTien - tien;

					if (sodu < 50000)
					{
						color(12);
						cout << "Tai khoan quy khach khong du vui long kiem tra lai\n";
					}
					else {
						cout << "Ban da rut tien thanh cong\n";
						ofstream os;
						os.open("ID.dat", ios::app);
						os << kiemTraTime(time) << "Rut tien" << "#" << TK[timTK].sUser << "#" << TK[timTK].sPin << "#" << TK[timTK].sPass
							<< "#" << TK[timTK].sHoten << "#" << sodu << "#" << TK[timTK].sLoaitien << "\n";
						os.close();
					}
				} while ((tien < 50000));
			} while ((sodu < 50000));
		}
	}
}
//tim kiem tuan tu
int timkiem(Taikhoan TK[], string User, string Pin, int nN)
{
	int nLeft = 0;
	int nRight = nN - 1;
	int nM = 0;
	while (nLeft <= nRight)
	{
		nM = (nLeft + nRight) / 2;
		if (TK[nM].sUser == User && TK[nM].sPass == Pin)
			return nM;
		else if (TK[nM].sUser < User && TK[nM].sPass < Pin)
			nLeft = nM + 1;
		else nRight = nM - 1;
	}
	return -1;
}

//Doc File
void DocFile(Taikhoan TK[], int &nSoTK)
{
	ifstream fcin;
	fcin.open("taikhoan.txt");
	fcin >> nSoTK;
	fcin.ignore(1);
	for (int i = 0; i < nSoTK; i++)
	{
		rewind(stdin);
		getline(fcin, TK[i].sUser, '#');

		rewind(stdin);
		getline(fcin, TK[i].sPass, '#');

		rewind(stdin);
		getline(fcin, TK[i].sPin, '#');

		rewind(stdin);
		getline(fcin, TK[i].sHoten, '#');


		fcin >> TK[i].fTien;
		fcin.ignore(1);

		rewind(stdin);
		getline(fcin, TK[i].sLoaitien, '\n');
	}
	fcin.close();
}

//mau chu
void color(int nN)
{
	HANDLE hC;
	hC = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hC, nN);
}

//doi mat khau thanh dau *
string Dau_sao()
{

	color(14);
	cout << setw(29) << "Pin:\t";

	char password[10];
	int i = 0;
	char a;// tam thoi
	while (14)//vong lap vo han cho den khi dap ung duoc khoi lenh 
			  //true tuong duong voi so khac 0 ( >1) //flase tuong duong voi so 0 (=0)
	{
		a = _getch();
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))//dieu kien cho phep nhap chu va so
		{
			password[i] = a;
			i++;
			cout << "*";
		}
		if (a == '\b' && i >= 1)//ham xoa, ho tro nguoi dung xoa khi nhap sai Mat Khau
		{
			cout << "\b \b";// \b dap ung ma backspace, \b one xoa du lieu, \b two xoa *
			i--;
		}
		if (a == 13)//13 = enter 
		{
			password[i] = '\0';
			break;
		}
	}
	return password;

}

//Lay thoi gian
string kiemTraTime(string sX)
{
	time_t now = time('\0');
	tm *t = localtime(&now);
	char *ch = asctime(t);
	return ch;
}
int demdong()
{
	ifstream f1;
	char c;
	int numchars, numlines;

	f1.open("ID.dat");

	numchars = 0;
	numlines = 0;
	f1.get(c);
	while (f1) {
		while (f1 && c != '\n') {
			numchars = numchars + 1;
			f1.get(c);
		}
		numlines = numlines + 1;
		f1.get(c);
	}
	return numlines / 2;
}