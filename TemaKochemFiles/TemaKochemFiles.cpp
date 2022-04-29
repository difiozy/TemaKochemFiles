#include<iostream>
#include<Windows.h>
#include<string.h>
#include<iomanip>
#include<fstream>

using namespace std;
struct houselist
{
	char name[40];
	char date[40];
	char pdata[40];
	int hnum;
	char statues[40];
};

const string bin_file_name = "resault_bin.bin";
int const n = 3;

void binoutput(int x)
{
	ifstream binin(bin_file_name, ios::binary);
	cout << "Содержимое бинаррного файла:" << endl;
	houselist temp;
	for (int i = 0; i < x; i++)
	{
		binin.read((char*)&temp.name, sizeof(temp.name));
		cout << temp.name << endl;
		binin.read((char*)&temp.date, sizeof(temp.date));
		cout << temp.date << endl;
		binin.read((char*)&temp.pdata, sizeof(temp.pdata));
		cout << temp.pdata << endl;;
		binin.read((char*)&temp.hnum, sizeof(temp.hnum));
		cout << temp.hnum << endl;;
		binin.read((char*)&temp.statues, sizeof(temp.statues));
		cout << temp.statues << endl;
		cout << endl;
	}
	binin.close();
}

void main()
{	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	houselist* sp = new houselist[10];
	houselist temp;
	char line[40];
	char line2[40];
	int k;
	
	houselist test;
	ifstream in;
	ofstream out;
	ofstream bin(bin_file_name, ios::binary);
	in.open("text1.txt");

	if ((!in.is_open()) || (!bin.is_open()))
	{
		cout << "Файл не найден" << endl;
		return;
	}

	for (int i = 0; i < n; i++)
	{
		in.getline(sp[i].name, 40);
		bin.write((char*)&sp[i].name, sizeof(sp[i].name));
		in.getline(sp[i].date, 40);
		bin.write((char*)&sp[i].date, sizeof(sp[i].date));
		in.getline(sp[i].pdata, 40);
		bin.write((char*)&sp[i].pdata, sizeof(sp[i].pdata));
		in >> sp[i].hnum;
		bin.write((char*)&sp[i].hnum, sizeof(sp[i].hnum));
		in.ignore();
		in.getline(sp[i].statues, 40);
		bin.write((char*)&sp[i].statues, sizeof(sp[i].statues));
	}
	bin.close();
	binoutput(n);

	cout << "Введите номер записи жильца которое хотите изменить\n";
	cin >> k;

	cout << "Введите название поля которое хотите изменить (ФИО, Дата рождения, Номер паспорта, Номер квартиры, Статус)\n";
	cin.ignore();
	cin.getline(line, 40);

	long long g = 0;

	if (strstr(line, "ФИО"))
	{
		g = 0;
	}
	else if (strstr(line, "Дата рождения"))
	{
		g = sizeof(sp[k].name);
	}
	else if (strstr(line, "Номер паспорта"))
	{
		g = sizeof(sp[k].name) + sizeof(sp[k].date);
	}
	else if (strstr(line, "Номер квартиры"))
	{
		g = sizeof(sp[k].name) + sizeof(sp[k].date) + sizeof(sp[k].pdata);
	}
	else if (strstr(line, "Статус"))
	{
		g = sizeof(sp[k].name) + sizeof(sp[k].date) + sizeof(sp[k].pdata) + sizeof(sp[k].hnum);
	}

	ofstream binout(bin_file_name, ios::binary | ios::in);
	binout.seekp(sizeof(houselist) * (k-1) + g, ios::beg);
	
	if (strstr(line, "Номер квартиры"))
	{
		int x;
		cout << "Введите новый номер квартиры: " << endl;
		cin >> x;
		cin.ignore();
		binout.write((char*)&x, sizeof(x));
	}
	else
	{
		cout << "Введите новую информацию" << endl;
		cin.getline(line2, 40);
		binout.write((char*)&line2, sizeof(line2));
	}
	binout.close();

	binoutput(n);
}
