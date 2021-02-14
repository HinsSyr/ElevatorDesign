

#include"CenterControl.h"
#include <fstream>
#include <sstream>



int JudgeUpOrDown(int src, int det)  
{
	int flag=0;

	if (det - src > 0) {
		flag = UP;
	}
	else if (det - src < 0) {
		flag = DOWN;
	}

	return flag;
}


CenterControl::CenterControl()
{
	initElevatorBank();
	
}

void CenterControl::Cstart()
{

	elevatorTwo->estart();
	elevatorThree->estart();
	elevatorOne->estart();
	thread th(&CenterControl::elevatorSelec, this);
	elevatorOne->elevatorRun->join();
	elevatorTwo->elevatorRun->join();
	elevatorThree->elevatorRun->join();
	th.join();

}



CenterControl::~CenterControl()
{
	delete(elevatorOne);
	delete(elevatorTwo);
	delete(elevatorThree);

}

void CenterControl::initElevatorBank()    
{
	elevatorOne = new CElevator(1, 1);
	elevatorTwo = new CElevator(2, 1);
	elevatorThree = new  CElevator(3, 1);
}

void CenterControl::elevatorSelec()
{

	while (!allRequest.empty())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		strategeChooseElevator();
	}

	elevatorOne->center_finish = true;
	elevatorTwo->center_finish = true;
	elevatorThree->center_finish = true;
	
	cout << "center finished" << endl;

}


void CenterControl::strategeChooseElevator()
{
	
	typedef struct choice
	{
		CElevator *elevator;
		int sta;
		int rank;
	} slec;
	slec elevatorOneMeg = { elevatorOne,elevatorOne->getElevatorStatus(),1000 };
	slec elevatorTwoMeg = { elevatorTwo,elevatorTwo->getElevatorStatus(),1000 };
	slec elevatorThreeMeg = { elevatorThree,elevatorThree->getElevatorStatus(),1000 };

	lock(elevatorOne->mtx, elevatorTwo->mtx, elevatorThree->mtx);

	Request* cur = allRequest.back();
	int num = allRequest.size();
	requests.push_back(cur->srcfloor);
		cout << "current begin num: " << num << endl;
		cout << " request posted: " << cur->name << " from " << cur->srcfloor << " go to " << cur->desfloor << endl;
		elevatorOneMeg.rank = 1000;
		elevatorTwoMeg.rank = 1000;
		elevatorThreeMeg.rank = 1000;

		int flag = JudgeUpOrDown(cur->srcfloor, cur->desfloor);

		if (elevatorOneMeg.sta != flag && elevatorTwoMeg.sta != flag && elevatorThreeMeg.sta != flag
			&& elevatorOneMeg.sta!=STOP && elevatorTwoMeg.sta != STOP && elevatorThreeMeg.sta != STOP)
		{
			
		
			elevatorOne->mtx.unlock();
			elevatorTwo->mtx.unlock();
			elevatorThree->mtx.unlock();
			return;
		}

		if (elevatorOneMeg.sta == flag) {
				if (flag == UP && elevatorOne->getElevatorCurrentfloor() <= cur->srcfloor)
				{
					elevatorOneMeg.rank = abs(cur->srcfloor - elevatorOne->getElevatorCurrentfloor());
				}
				else if (DOWN == flag && elevatorOne->getElevatorCurrentfloor() >= cur->desfloor) {
					elevatorOneMeg.rank = abs(elevatorOne->getElevatorCurrentfloor() - cur->srcfloor);
				}
			
		}
		else if (elevatorOneMeg.sta == STOP) {
			elevatorOneMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
			elevatorOne->setElevatorStatus(JudgeUpOrDown(elevatorOne->getElevatorCurrentfloor(), cur->srcfloor));
			allRequest.pop_back();
		
			elevatorOne->mtx.unlock();
			elevatorTwo->mtx.unlock();
			elevatorThree->mtx.unlock();
			return;
		}


		if (elevatorTwoMeg.sta == flag) 
		{
				if (flag == UP && elevatorTwo->getElevatorCurrentfloor() <= cur->srcfloor)
				{
					elevatorTwoMeg.rank = abs(cur->srcfloor - elevatorTwo->getElevatorCurrentfloor());
				}
				else if (DOWN == flag && elevatorTwo->getElevatorCurrentfloor() >= cur->desfloor) {
					elevatorTwoMeg.rank = abs(elevatorTwo->getElevatorCurrentfloor() - cur->srcfloor);
				}
			
		}
		else if (elevatorTwoMeg.sta == STOP) {
			elevatorTwoMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
			elevatorTwo->setElevatorStatus(JudgeUpOrDown(elevatorTwo->getElevatorCurrentfloor(), cur->srcfloor));
			allRequest.pop_back();
			elevatorOne->mtx.unlock();
			elevatorTwo->mtx.unlock();
			elevatorThree->mtx.unlock();
			return;
		}

		if (elevatorThreeMeg.sta == flag) {
			 
				if (flag == UP && elevatorThree->getElevatorCurrentfloor() <= cur->srcfloor)
				{
					elevatorThreeMeg.rank = abs(cur->srcfloor - elevatorThree->getElevatorCurrentfloor());
				}
				else if (DOWN == flag && elevatorThree->getElevatorCurrentfloor() >= cur->desfloor) {
					elevatorThreeMeg.rank = abs(elevatorThree->getElevatorCurrentfloor() - cur->srcfloor);
				}
			
		}
		else if (elevatorThreeMeg.sta == STOP) {
			elevatorThreeMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
			elevatorThree->setElevatorStatus(JudgeUpOrDown(elevatorThree->getElevatorCurrentfloor(), cur->srcfloor));
			allRequest.pop_back();
			elevatorOne->mtx.unlock();
			elevatorTwo->mtx.unlock();
			elevatorThree->mtx.unlock();
			return;
		}
		
			
		if (elevatorOneMeg.rank <= elevatorTwoMeg.rank) //1<=2
		{

			if (elevatorOneMeg.rank <= elevatorThreeMeg.rank) //1<=3 1is min
			{
				elevatorOneMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
				allRequest.pop_back();
				elevatorOne->mtx.unlock();
				elevatorTwo->mtx.unlock();
				elevatorThree->mtx.unlock();
				return;

			}
			else //1>3 3 is min
			{
				elevatorThreeMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
				allRequest.pop_back();
				elevatorOne->mtx.unlock();
				elevatorTwo->mtx.unlock();
				elevatorThree->mtx.unlock();
				return;
			}

		}
		else { //1>2
			if (elevatorTwoMeg.rank >= elevatorThreeMeg.rank)   //2>=3  3 is min
			{
				elevatorThreeMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
				allRequest.pop_back();
				elevatorOne->mtx.unlock();
				elevatorTwo->mtx.unlock();
				elevatorThree->mtx.unlock();
				return;
			}
			else  //2<3   2 is min
			{
				elevatorTwoMeg.elevator->addRequest(cur->name, cur->srcfloor, cur->desfloor);
				allRequest.pop_back();
				elevatorOne->mtx.unlock();
				elevatorTwo->mtx.unlock();
				elevatorThree->mtx.unlock();
				return;
			}
		}
 elevatorOne->mtx.unlock();
elevatorTwo->mtx.unlock();
elevatorThree->mtx.unlock();

}

void CenterControl::getClient()
{
	string name;
	int srcfloor;
	int desfloor;
	Request *client;

	ifstream read_file;
	read_file.open("Requests.txt");
	string str;
	while (getline(read_file, str))
	{
		string field;
		istringstream sin(str);

		getline(sin, field, ' ');
		name = field.c_str();
	//	cout << name << " ";

		getline(sin, field, ' ');
		srcfloor = atoi(field.c_str());
	//	cout << srcfloor << " ";

		getline(sin, field, ' ');
		desfloor = atoi(field.c_str());
	////	cout << desfloor << " ";
		//cout << endl;

		bool effect = true;
		if (srcfloor > MAXLEVEL || srcfloor < MINLEVEL)
			effect = false;
		if (desfloor > MAXLEVEL || desfloor < MINLEVEL)
			effect = false;
		if (desfloor == srcfloor)
			effect = false;
		if (effect) {
			centerlocker.lock();
			client = new Request(name, srcfloor, desfloor);
			allRequest.push_back(client);
			centerlocker.unlock();
		}
		else {
			printf("enter uncorrect \n");
		}

	}
	read_file.close();


}