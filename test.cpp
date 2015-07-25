#include "Basics.h"
#include "String.h"
#include "FileStream.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace cz;
using namespace cz::stream;
using namespace std;

int main(){
	CZString filename("1.txt");
	//CZFileStream myFile(filename,CZFileStream::ReadOnly);
	//char buffer[512];
	//int num = myFile.Read(buffer, 512);
	CZString str2;
	cin >> str2;
	string str3 = "1.txt";
	bool flag = str2 == 'x';
	cout << boolalpha << flag << endl;
	vector<CZString> array = filename.Split('.');
	for (int i = 0; i < array.size(); ++i){
		cout << array[i] << " ";
	}
	cout << str2;
	return 0;
}