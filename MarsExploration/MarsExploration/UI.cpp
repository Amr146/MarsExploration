#include "UI.h"
#include "MarsStation.h"

#include <iostream>
#include <fstream>

#include "MarsStation.h"

#include <string>

using namespace std;

UI::UI(MarsStation* st){
	station = st;
}

void UI::loadInputFile(){
	ifstream inputFile("inputFile.txt", ios::in);
	
	int M, P, E, SM, SP, SE, N, CM, CP, CE;
	char eventType;
	int ed, id;

	if(inputFile.is_open()){
		inputFile >> M >> P >> E;			//	num of each type of rovers
		inputFile >> SM >> SP >> SE;		//	speed of each type of rovers
		inputFile >> N >> CM >> CP >> CE;	//	num of missions before checkup and the checkup durations

		station->createMrovers(M, SM, N, CM);
		station->createProvers(P, SP, N, CP);
		station->createErovers(E, SE, N, CE);

		inputFile >> N;						//	autoP
		station->setAutoP(N);

		inputFile >> N;						//	num of evevts
		for(int i = 1; i <= N; i++){
			inputFile >> eventType;
			if(eventType == 'F'){
				char mType;
				inputFile >> mType;
				MissionType type = (mType == 'E')? MissionType::E : ((mType == 'P')? MissionType::P : MissionType::M);
				inputFile >> ed >> id;
				int tloc, mdur, sig;
				inputFile >> tloc >> mdur >> sig;
				station->addFEvent(type, ed, id, tloc, mdur, sig);		//	creating formulation event
			
			}else if(eventType == 'P'){
				inputFile >> ed >> id;
				station->addPEvent(ed, id);		//	creating promotion event
			
			}else if(eventType == 'X'){
				inputFile >> ed >> id;
				station->addXEvent(ed, id);		//	creating cancellation event
			
			}else{
				//	skip this incorrect line
			}
		}
	}
	inputFile.close();
}

void UI::createOutputFile(){
	LinkedPriorityQueue<Mission*> *CM = station->completedMissions();	//	address of CMList
	LinkedPriorityQueue<Polarrovers*>* P = station->polarRovers();
	LinkedPriorityQueue<Mountainousrovers*>* M = station->mountRovers();
	LinkedPriorityQueue<Emergencyrovers*>* E = station->emergRovers();
	
	ofstream outputFile("outputFile.txt", ios::out);
	if(outputFile.is_open()){
		outputFile << "CD ID FD WD ED\n";
		Mission* mission;
		Polarrovers* pRoverPtr;
		Mountainousrovers* mRoverPtr;
		Emergencyrovers* eRoverPtr;

		int totalWait = 0, totalExecution = 0, totalMissions = 0, Emission = 0, Pmission = 0, Mmission = 0;
		int Erovers = 0, Mrovers = 0, Provers = 0;

		while(P->remove(pRoverPtr))
			Provers++;

		while(M->remove(mRoverPtr))
			Mrovers++;

		while(E->remove(eRoverPtr))
			Erovers++;

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
	outputFile.close();
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
	cout << "Silent Mode\nSimulation Starts...\nSimulation ends, Output file created\n";
}