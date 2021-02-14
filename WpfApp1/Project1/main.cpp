#include<stdio.h>
#include "CenterControl.h"


using namespace std;



void main()
{
	CenterControl *center =  new CenterControl();
	center->getClient();
	center->Cstart();

}