#include "MarsStation.h"
MarsStation::MarsStation(){
	ui = new UI(this);
	auto_promoted = 0;
}

void MarsStation::Simulate(){}

void MarsStation::ReadInput(){
	ui->loadInputFile();
}

void MarsStation::AssignMissions(){}

void MarsStation::WriteOutput(){}

void MarsStation::createMrovers(int n, double speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Mountainousrovers* newMrover = new Mountainousrovers(speed, nom, checkUp);
		WMRList.add(newMrover, 0);		//	what is the default priority
	}
}

void MarsStation::createProvers(int n, double speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Polarrovers* newMrover = new Polarrovers(speed, nom, checkUp);
		WPRList.add(newMrover, 0);		//	what is the default priority
	}
}

void MarsStation::createErovers(int n, double speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Emergencyrovers* newMrover = new Emergencyrovers(speed, nom, checkUp);
		WERList.add(newMrover, 0);		//	what is the default priority
	}
}

void MarsStation::setAutoP(int n){
	autoP = n;
}

void MarsStation::addFEvent(MissionType type, int ed, int id, int tloc, int mdur, int sig){
	FormulationEvent* fEvent = new FormulationEvent(type, ed, id, tloc, mdur, sig);
}

void MarsStation::addXEvent(int ed, int id){
	CancellationEvent* xEvent = new CancellationEvent(ed, id);
}

void MarsStation::addPEvent(int ed, int id){
	PromotionEvent* pEvent = new PromotionEvent(ed, id);
}

LinkedPriorityQueue<Mission*>* MarsStation::completedMissions(){
	return &CMList;
}

LinkedPriorityQueue<Polarrovers*>* MarsStation::polarRovers(){
	return &WPRList;
}

LinkedPriorityQueue<Mountainousrovers*>* MarsStation::mountRovers(){
	return &WMRList;
}

LinkedPriorityQueue<Emergencyrovers*>* MarsStation::emergRovers(){
	return &WERList;
}

LinkedQueue<PolarMission*>* MarsStation::polarMissions(){
	return  &WPMList;
}

LinkedList<MountainousMission*>* MarsStation::mountMissions(){
	return &WMMList;
}

LinkedPriorityQueue<EmergencyMission*>* MarsStation::emergMissions(){
	return &WEMList;
}

LinkedPriorityQueue<Mission*>* MarsStation::inExec(){
	return &IEList;
}

LinkedPriorityQueue<Rover*>* MarsStation::inCheck(){
	return &ICURList;
}

LinkedPriorityQueue<Mission*>* MarsStation::compMissions(){
	return &CMList;
}


int MarsStation::getAutoPromoted(){
	return auto_promoted;
}

MarsStation::~MarsStation(){
	delete ui;
}