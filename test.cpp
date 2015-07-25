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
	CZString str2("2.txt");
	vector<CZString> array = filename.Split('.');
	for (int i = 0; i < array.size(); ++i){
		cout << array[i] << " ";
	}
	return 0;
}