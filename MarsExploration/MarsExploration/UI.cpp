#include "UI.h"
#include <iostream>
#include <fstream>
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
				inputFile >> ed >> id;
				char mType;
				inputFile >> mType;
				MissionType type = (mType == 'E')? MissionType::E : ((mType == 'P')? MissionType::P : MissionType::M);
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
	if(outputFile.is_open){
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

		while(!CM->remove(mission)){
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

		outputFile << "Avg Wait= " << 1.0*totalWait/totalMissions << ", Avg Exec = " << 1.0*totalExecution/totalMissions << "\n";

		outputFile << "Auto-Promoted: " << 100.0*station->getAutoPromoted()/totalMissions << "%\n"; 
		
	}
	outputFile.close();
}

void UI::interactiveMode(){
	createOutputFile();

}

void UI::stepByStepMode(){
	createOutputFile();

}

void UI::silentMode(){
	createOutputFile();
	cout << "Silent Mode\nSimulation Starts...\nSimulation ends, Output file created\n";
}