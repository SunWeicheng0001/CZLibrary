#include "Basics.h"
#include <iostream>
using namespace cz;
using namespace std;

int main(){
	DateTime dateTime;
	dateTime = DateTime::LocalTime();
	std::cout << dateTime.month << " " << dateTime.day << " " << dateTime.dayOfweek << " " << dateTime.hour << " " << dateTime.minute << std::endl;
	return 0;
}