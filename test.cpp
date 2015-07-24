#include "Basics.h"
#include "String.h"
#include <iostream>
#include <string>
#include <vector>
using namespace cz;
using namespace std;

int main(){
	//CZString myString(src);
	CZString myString("1234");
	myString.Insert(0, '5');
	cout << myString.toString() << endl;
	CZString temp = myString.Sub(0, 5);
	cout << temp.toString() << endl;
	return 0;
}