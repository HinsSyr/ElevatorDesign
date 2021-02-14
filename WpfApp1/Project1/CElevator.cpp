

#include "CElevator.h"
#include <iostream>
#include <fstream>

CElevator::CElevator(int inElevatorID, int inCurrentfloor)
{
	elevatorID = inElevatorID;
	currentfloor = inCurrentfloor;
	elevatorStatus = STOP;
	isrun = true;

	
}
void CElevator::estart()
{
	elevatorRun = new thread(&CElevator::run, this);

}

CElevator::~CElevator()
{
	
}


bool CElevator::addArriveList(string inname, int insrc, int indet)
{
	Request *client = new Request(inname, insrc, indet);
	if (arriveList.size() == 0)
	{
		arriveList.push_back(client);
		myarv.push_back(indet);
	}
	else {
		for (vector<Request *>::iterator i = arriveList.begin(); i != arriveList.end(); i++)
		{
			if ((*i)->desfloor >= client->desfloor && elevatorStatus==UP)
			{
				arriveList.insert(i, client);
				myarv.push_back(indet);
				break;
			}
			else if ((*i)->desfloor <= client->desfloor && elevatorStatus == DOWN)
			{
				arriveList.insert(i, client);
				myarv.push_back(indet);
				break;
			}
			else return false;
		}
	}
	return true;
}

bool CElevator::addRequest(string inname, int insrc, int indet)
{
	Request *client = new Request(inname, insrc, indet);
	if (requestList.size() == 0 || elevatorStatus==STOP )
	{
		requestList.push_back(client);
		myreqs.push_back(insrc);
		cout << "elevator id: " << this->elevatorID << " take the request: " << inname << " from " << insrc << " to " << indet <<" first "<< endl;
	}
	else {
		for (vector<Request *>::iterator i = requestList.begin(); i != requestList.end(); i++)
		{
			if ((*i)->srcfloor >= client->srcfloor && elevatorStatus==UP  && (*i)->srcfloor>=currentfloor)
			{
				requestList.insert(i, client);
				myreqs.push_back(insrc);
				cout << "elevator id: " << this->elevatorID << " take the request: " << inname << " from " << insrc << " to " << indet<<" second " << endl;
				break;
			}
			else if((*i)->srcfloor <=client->srcfloor && elevatorStatus==DOWN  && (*i)->srcfloor<=currentfloor)
			{
				myreqs.push_back(insrc);
				requestList.insert(i, client);
				cout << "elevator id: " << this->elevatorID << " take the request: " << inname << " from " << insrc << " to " << indet << " second " << endl;
				break;
			}
			else return false;
		}
	}

	return true;
}



void CElevator::run()
{
	while (this->isrun)
	{
		
		while (!this->requestList.empty() || !arriveList.empty())
		{
			
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			move(); 
			floorlog.push_back(currentfloor);
		}
		elevatorStatus = STOP;
		if (center_finish)
			isrun = false;
	}
	ofstream myfile;
	if (elevatorID == 1)
	{
		
		myfile.open("floor1.txt");
		for (int i = 0; i < floorlog.size(); i++)
			myfile << floorlog[i] << endl;
		myfile.close();

		myfile.open("req1.txt");
		for (int i = 0; i < myreqs.size(); i++)
			myfile << myreqs[i] << endl;
		myfile.close();

		myfile.open("arv1.txt");
		for (int i = 0; i < myarv.size(); i++)
			myfile << myarv[i] << endl;
		myfile.close();
		
	}
	if (elevatorID == 2)
	{
		myfile.open("floor2.txt");
		for (int i = 0; i < floorlog.size(); i++)
			myfile << floorlog[i] << endl;
		myfile.close();

		myfile.open("req2.txt");
		for (int i = 0; i < myreqs.size(); i++)
			myfile << myreqs[i] << endl;
		myfile.close();

		myfile.open("arv2.txt");
		for (int i = 0; i < myarv.size(); i++)
			myfile << myarv[i] << endl;
		myfile.close();

	}
	if (elevatorID == 3)
	{
		myfile.open("floor3.txt");
		for (int i = 0; i < floorlog.size(); i++)
			myfile << floorlog[i] << endl;
		myfile.close();

		myfile.open("req3.txt");
		for (int i = 0; i < myreqs.size(); i++)
			myfile << myreqs[i] << endl;
		myfile.close();

		myfile.open("arv3.txt");
		for (int i = 0; i < myarv.size(); i++)
			myfile << myarv[i] << endl;
		myfile.close();
	}

	

	cout << elevatorID << " finished" << endl;
}


void CElevator::move()    
{
	mtx.lock(); 

	if (elevatorStatus != STOP)
	{
		if (elevatorStatus == UP)
		{
			currentfloor++;
			if (currentfloor == maxfloor)
				elevatorStatus = STOP;

		}
		else if (elevatorStatus == DOWN) {
			currentfloor--;
			if (currentfloor == minfloor)
				elevatorStatus = STOP;
		}
	}
	
	if (arriveList.size() == 0 && requestList.size() == 0) {
		this->elevatorStatus = STOP;
		myreqs.push_back(0);
		myarv.push_back(0);
		return;
	}
	if (requestList.size() == 0)
		myreqs.push_back(0);
	
		

	
	for (vector<Request *>::iterator i = requestList.begin(); i != requestList.end(); )
	{
		if ((*i)->srcfloor == currentfloor)
		{
			cout << this->elevatorID << " has took  " << (*i)->name << " at the" << (*i)->srcfloor << "..." << endl;
		
			myreqs.push_back(0-(*i)->srcfloor);
			addArriveList((*i)->name, (*i)->srcfloor, (*i)->desfloor);
			delete((*i));
			i = requestList.erase(i);
			continue;
		}
		else
		{
			myreqs.push_back((*i)->srcfloor);
		}
		i++;
	}
	if (requestList.size() == 0 && arriveList.size() != 0)
	{
		setElevatorStatus(arriveList.front()->desfloor - currentfloor > 0 ? UP : DOWN);
		
	}



	cout <<"Elevator number: "<< elevatorID << " is going " << (this->elevatorStatus == UP ? " up " : " down ") << " current floor is : " << currentfloor << "..." << endl;
	clientArrive();
	mtx.unlock();
	
}

void CElevator::clientArrive()
{
	if (arriveList.size() == 0)
		myarv.push_back(0);

	for (vector<Request *>::iterator i = arriveList.begin(); i != arriveList.end();)
	{
		if ((*i)->desfloor == currentfloor)
		{
			myarv.push_back(0-(*i)->desfloor);
			std::cout << (*i)->name << " arrive at the " << currentfloor << " the elevator id is " << elevatorID << "..." << endl;
			delete((*i));
			i = arriveList.erase(i);
			continue;
		}
		else
			myarv.push_back((*i)->desfloor);
		i++;
	}
	if (arriveList.size() == 0 && requestList.size() != 0)
	{
		setElevatorStatus(requestList.front()->srcfloor - currentfloor > 0 ? UP : DOWN);
	}

	

	if (arriveList.size() == 0 && requestList.size()==0) {
		this->elevatorStatus = STOP;
		
	}

}

void CElevator::openDoor()
{

}

int CElevator::getElevatorStatus()
{
	return this->elevatorStatus;
}
int CElevator::getElevatorCurrentfloor()
{
	return this->currentfloor;
}


void CElevator::setElevatorStatus(int state)
{
	this->elevatorStatus = state;
}
void CElevator::stopElevator()
{
	this->isrun = false;
}
