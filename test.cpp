#include "Basics.h"
#include "String.h"
#include "FileStream.h"
#include <iostream>
#include <string>
#include <vector>
using namespace cz;
using namespace cz::stream;
using namespace std;

int main(){
	CZString filename("1.txt");
	CZFileStream myFile(filename,CZFileStream::ReadOnly);
	char buffer[512];
	int num = myFile.Read(buffer, 512);
	printf("%s", buffer);
	return 0;
}