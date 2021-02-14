#pragma once
#include <mutex>
#include "Request.h"
#include "CElevator.h"


class CenterControl {

private:
	mutex centerlocker, emtx;
	void strategeChooseElevator();

public:
	CElevator *elevatorOne;
	CElevator *elevatorTwo;
	CElevator *elevatorThree;
	vector<int> requests;
	void getClient();
	CenterControl();
	~CenterControl();
	void initElevatorBank();
	void Cstart();
	vector<Request *> allRequest;
	void elevatorSelec();
};