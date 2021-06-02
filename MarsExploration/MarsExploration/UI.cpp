#include "UI.h"
#include "MarsStation.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

UI::UI(MarsStation* st){		//	constructor
	station = st;
}

void UI::loadInputFile(){						//	loading input file
	ifstream inputFile("inputFile.txt", ios::in);		//	creating input file stream
	
	int M, P, E, SM, SP, SE, N, CM, CP, CE;
	char eventType;
	int ed, id;

	if(inputFile.is_open()){
		inputFile >> M >> P >> E;			//	num of each type of rovers
		inputFile >> SM >> SP >> SE;		//	speed of each type of rovers
		inputFile >> N >> CM >> CP >> CE;	//	num of missions before checkup and the checkup durations

		//	creating rovers
		station->createMrovers(M, SM, N, CM);
		station->createProvers(P, SP, N, CP);
		station->createErovers(E, SE, N, CE);

		inputFile >> N;						//	autoP
		station->setAutoP(N);

		inputFile >> N;						//	num of evevts
		for(int i = 1; i <= N; i++){
			inputFile >> eventType;
			//	formulation event
			if(eventType == 'F'){
				char mType;
				inputFile >> mType;
				//	type of the mission
				MissionType type = (mType == 'E')? MissionType::E : ((mType == 'P')? MissionType::P : MissionType::M);
				int tloc, mdur, sig;
				inputFile >> ed >> id >> tloc >> mdur >> sig;
				station->addFEvent(type, ed, id, tloc, mdur, sig);		//	creating formulation event
			//	promotion event
			}else if(eventType == 'P'){
				inputFile >> ed >> id;
				station->addPEvent(ed, id);		//	creating promotion event
			//	cancellation event
			}else if(eventType == 'X'){
				inputFile >> ed >> id;
				station->addXEvent(ed, id);		//	creating cancellation event
			//	nothing
			}else{
				//	skip this incorrect line
			}
		}
	}
	inputFile.close();		//	closing input file
}

void UI::createOutputFile(){
	LinkedPriorityQueue<Mission*> *CM = station->completedMissions();		//	address of CMList
	LinkedPriorityQueue<Polarrovers*>* P = station->polarRovers();			//	address of WPRList
	LinkedPriorityQueue<Mountainousrovers*>* M = station->mountRovers();	//	address of WMRList
	LinkedPriorityQueue<Emergencyrovers*>* E = station->emergRovers();		//	address of WERList
	
	ofstream outputFile("outputFile.txt", ios::out);			//	creating output file stream
	if(outputFile.is_open()){
		outputFile << "CD ID FD WD ED\n";
		Mission* mission;
		Polarrovers* pRoverPtr;
		Mountainousrovers* mRoverPtr;
		Emergencyrovers* eRoverPtr;

		int totalWait = 0, totalExecution = 0, totalMissions = 0, Emission = 0, Pmission = 0, Mmission = 0;
		int Erovers = 0, Mrovers = 0, Provers = 0;

		//	count num of polar rovers
		while(P->remove(pRoverPtr))
			Provers++;
		//	count num of mount rovers
		while(M->remove(mRoverPtr))
			Mrovers++;
		//	count num of emerg rovers
		while(E->remove(eRoverPtr))
			Erovers++;
		//	count num of missions
		while(CM->remove(mission)){
			totalMissions++;
			if(dynamic_cast<EmergencyMission*>(mission))
				Emission++;
			else if(dynamic_cast<PolarMission*>(mission))
				Pmission++;
			else if(dynamic_cast<MountainousMission*>(mission))
				Mmission++;

			totalWait += mission->get_WD();
			totalExecution += mission->get_ED();

			outputFile << mission->get_CD() << " " << mission->get_id() << " " << mission->get_FD() << " " << mission->get_WD() << " " << mission->get_ED() << "\n";
		}

		outputFile << "....................................................\n....................................................\n";
		//	statistics of the system
		outputFile << "Missions: " << totalMissions << " [M: " << Mmission << ", P: " << Pmission << ", E: " << Emission << "]\n";

		outputFile << "Rovers: " << Provers+Mrovers+Erovers << "[M: " << Mrovers << ", P: " << Provers << ", E: " << Erovers << "]\n";
		if(!totalMissions){
			outputFile << "Avg Wait= " << 0 << ", Avg Exec = " << 0 << "\n";

			outputFile << "Auto-Promoted: " << 0 << "%\n"; 
		}else{
			outputFile << "Avg Wait= " << 1.0*totalWait/totalMissions << ", Avg Exec = " << 1.0*totalExecution/totalMissions << "\n";

			outputFile << "Auto-Promoted: " << 100.0*station->getAutoPromoted()/totalMissions << "%\n"; 
		}
		
	}
	outputFile.close();		//	closing output file
}

void UI::printDataOfDay(int day){
	LinkedQueue<PolarMission*> WPMList(*(station->polarMissions()));				//	Deep copy of waiting polar missions
	LinkedList<MountainousMission*> WMMList(*(station->mountMissions()));			//	Deep copy of waiting mount missions
	LinkedPriorityQueue<EmergencyMission*> WEMList(*(station->emergMissions()));	//	Deep copy of waiting emerg missions

	LinkedPriorityQueue<Mission*> inExecution(*(station->inExec()));				//	Deep copy of in execution missions

	LinkedPriorityQueue<Polarrovers*> WPRList(*(station->polarRovers()));			//	Deep copy of waiting polar rovers
	LinkedPriorityQueue<Mountainousrovers*> WMRList(*(station->mountRovers()));		//	Deep copy of waiting mount rovers
	LinkedPriorityQueue<Emergencyrovers*> WERList(*(station->emergRovers()));		//	Deep copy of waiting emerg rovers
	
	LinkedPriorityQueue<Rover*> ICURList(*(station->inCheck()));					//	Deep copy of in in check-up rovers

	LinkedPriorityQueue<Mission*> CMList(*(station->completedMissions()));			//	Deep copy of in in completed missions
	
	string dayDetails = "[";
	int n = 0;

	PolarMission* pMissionPtr;
	MountainousMission* mMissionPtr;
	EmergencyMission* eMissionPtr;

	Mission* mission;

	Polarrovers* pRoverPtr;
	Mountainousrovers* mRoverPtr;
	Emergencyrovers* eRoverPtr;

	Rover* rover;

	cout << "Current day:" << day << "\n";
	
	//	Printing waiting missions

	//	Getting IDs of waiting emerg missions
	while(WEMList.remove(eMissionPtr)){
		n++;
		dayDetails += (to_string(eMissionPtr->get_id())+",");
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "] (";
	
	//	Getting IDs of waiting polar missions
	while(WPMList.dequeue(pMissionPtr)){
		n++;
		dayDetails += (to_string(pMissionPtr->get_id())+",");
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += ") {";

	//	Getting IDs of waiting mount missions
	int m = 0;
	while(WMMList.remove(m++ ,mMissionPtr)){			//	how to remove each element in this list??
		n++;
		dayDetails += (to_string(mMissionPtr->get_id())+",");
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "}";

	cout << n << " Waiting Missions: " << dayDetails << endl;

	/////////////////////////////////////////////////////////////
	//	printing in execution missions
	n = 0;
	dayDetails = "[";
	string dayDetails2 = "(";
	string dayDetails3 = "{";

	while(inExecution.remove(mission)){
		n++;
		if(dynamic_cast<EmergencyMission*>(mission)){
			dayDetails += (to_string(mission->get_id()) + "/" + to_string(mission->get_R()->getid()));
			dayDetails += ",";
		}else if(dynamic_cast<PolarMission*>(mission)){
			dayDetails2 += (to_string(mission->get_id()) + "/" + to_string(mission->get_R()->getid()));
			dayDetails2 += ",";
		}else if(dynamic_cast<MountainousMission*>(mission)){
			dayDetails3 += (to_string(mission->get_id()) + "/" + to_string(mission->get_R()->getid()));
			dayDetails3 += ",";
		}
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	cout << n << " In-Execution Missions/Rovers: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl;

	/////////////////////////////////////////////////////////////
	//	printing available rovers
	n = 0;
	dayDetails = "[";
	//	Getting IDs of waiting emerg rovers
	while(WERList.remove(eRoverPtr)){
		n++;
		dayDetails += (to_string(eRoverPtr->getid())+",");
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "] (";
	
	//	Getting IDs of waiting polar rovers
	m = 0;
	while(WPRList.remove(pRoverPtr)){
		n++;
		dayDetails += (to_string(pRoverPtr->getid())+",");
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += ") {";

	//	Getting IDs of waiting mount rovers
	while(WMRList.remove(mRoverPtr)){
		n++;
		dayDetails += (to_string(mRoverPtr->getid()) + ",");
	}
	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	dayDetails += "}";

	cout << n << " Available Rovers: " << dayDetails << endl;

	/////////////////////////////////////////////////////////////
	//	printing in checkup rovers
	n = 0;
	dayDetails = "[";
	dayDetails2 = "(";
	dayDetails3 = "{";

	while(ICURList.remove(rover)){
		n++;
		if(dynamic_cast<Emergencyrovers*>(rover))
			dayDetails += (to_string(rover->getid()) + ",");
		else if(dynamic_cast<Polarrovers*>(rover))
			dayDetails2 += (to_string(rover->getid()) + ",");
		else if(dynamic_cast<Mountainousrovers*>(rover))
			dayDetails3 += (to_string(rover->getid()) + ",");
	}

	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	cout << n << " In-Checkup Rovers: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl;

	/////////////////////////////////////////////////////////////
	//	printing in completed missions
	n = 0;
	dayDetails = "[";
	dayDetails2 = "(";
	dayDetails3 = "{";

	while(CMList.remove(mission)){
		n++;
		if(dynamic_cast<EmergencyMission*>(mission))
			dayDetails += (to_string(mission->get_id()) + ",");
		else if(dynamic_cast<PolarMission*>(mission))
			dayDetails2 += (to_string(mission->get_id()) + ",");
		else if(dynamic_cast<MountainousMission*>(mission))
			dayDetails3 += (to_string(mission->get_id()) + ",");
	}

	if(dayDetails.back() == ',')
		dayDetails.pop_back();
	if(dayDetails2.back() == ',')
		dayDetails2.pop_back();
	if(dayDetails3.back() == ',')
		dayDetails3.pop_back();

	dayDetails += "]";
	dayDetails2 += ")";
	dayDetails3 += "}";

	cout << n << " Completed Missions: " << dayDetails << " " << dayDetails2 << " " << dayDetails3 << endl << endl << endl;
}

void UI::silentMode(){
	cout << "Silent Mode\nSimulation Starts...\nSimulation ends, Output file created\n";		//	message of the silent mode
}

void UI::waitEnter(){
	while(true)
		if (cin.get() == '\n'){			//	waiting until enter is pressed
			//cin.ignore();
			break;
		}
}

void UI::waitSecond(){
	_sleep(1000);		//	waiting 1 second
}

int UI::getModeOfSim(){
	cout << "Select The Mode Of Simulation: \n-------------------------------\n";
	cout << "1) Interactive Mode\n";
	cout << "2) Step-By-Step Mode\n";
	cout << "3) Silent Mode\n";
	int mode;
	cin >> mode;
	cin.ignore();
	while(mode != 1 && mode !=  2 && mode != 3){
		cout << "Enter Correct Choice: ";
		cin >> mode;
		cin.ignore();
	}
	return mode;
}
