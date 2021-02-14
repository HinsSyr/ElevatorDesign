#pragma once

#include <mutex>
#include "Request.h"
#include <atomic>
#include <vector>
#include <iostream>

#define UP 1
#define DOWN -1
#define STOP 0
#define MAXLEVEL 30
#define MINLEVEL 1



class CElevator {

private:

	int elevatorID;
	int currentfloor;
	int maxfloor;
	int minfloor;
	int elevatorStatus;
	bool isrun;
	
	
	void move();
	void clientArrive();
	void openDoor();

public:
	mutex mtx;
	void run();
	thread *elevatorRun;
	vector<Request *> requestList;
	vector<Request *> arriveList;
	vector<int> floorlog;
	vector<int> myreqs;
	vector<int> myarv;
	void estart();
	bool addArriveList(string inname, int insrc, int indet);
	bool addRequest(string inname, int insrc, int indet);
	int getElevatorStatus();
	int getElevatorCurrentfloor();
	void setElevatorStatus(int state);
	void stopElevator();
	bool center_finish = false;
	~CElevator();
	CElevator(int inElevatorID, int inCurrentfloor);
};