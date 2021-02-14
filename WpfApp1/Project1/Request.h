#pragma once

#include<string>

using namespace std;

class Request {

public:
	string name;
	int srcfloor;
	int desfloor;
	Request(string inname, int insrcfloor, int indesfloor);
	~Request();

};