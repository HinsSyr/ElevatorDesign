#include "Request.h"
#include <string>
#include<iostream>

using namespace std;

Request::Request(string inname,int insrcfloor, int indesfloor)
{
	name = inname;
	srcfloor = insrcfloor;
	desfloor = indesfloor;

}

Request::~Request()
{

}