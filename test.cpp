#include "SockClient.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace cz;
using namespace cz::czsocket;
using namespace std;

int main(){
	CZClient client("127.0.0.1", "8800");
	string str = "Hello ¹þ¹þ¹þ";
	client.Send(str);
	while (true)
	{

	}
	return 0;
}