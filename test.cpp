#include "SockClient.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace cz;
using namespace cz::czsocket;
using namespace std;

int main(){
	CZClient client("58.196.155.190", "9000");
	string str = "Hello ¹þ¹þ¹þ";
	string remoteName = client.getRemoteAddress();
	cout << remoteName << endl;
	client.Send(str);
	while (true)
	{

	}
	return 0;
}