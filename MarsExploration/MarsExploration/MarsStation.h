#pragma once
#include"LinkedPriorityQueue.h"
#include"LinkedList.h"
#include"LinkedQueue.h"
#include"Event.h"
#include"EmergencyMission.h"
#include"Rover.h"
#include"Emergencyrovers.h"
#include"Polarrovers.h"
#include"Mountainousrovers.h"
#include"FormulationEvent.h"
#include"CancellationEvent.h"
#include"PromotionEvent.h"
#include"PolarMission.h"
#include"MountainousMission.h"
#include"UI.h"

class MarsStation
{
private:
	UI* ui;
	int autoP;
	int auto_promoted;
protected:
	LinkedPriorityQueue<Event*> EventList;		//	why not only queue ?
	LinkedQueue<PolarMission*> WPMList;
	LinkedList<MountainousMission*> WMMList;
	LinkedPriorityQueue<EmergencyMission*> WEMList;
	LinkedPriorityQueue<Mission*> IEList;
	LinkedPriorityQueue<Mission*> CMList;
	LinkedPriorityQueue<Polarrovers*> WPRList;
	LinkedPriorityQueue<Mountainousrovers*> WMRList;
	LinkedPriorityQueue<Emergencyrovers*> WERList;
	LinkedPriorityQueue<Rover*> IMRList;
	LinkedPriorityQueue<Rover*> ICURList;
public:
	MarsStation();

	void Simulate();

	void ReadInput();

	void AssignMissions();

	void WriteOutput();

	void createMrovers(int n, double speed, int nom, int checkUp);

	void createProvers(int n, double speed, int nom, int checkUp);

	void createErovers(int n, double speed, int nom, int checkUp);

	void setAutoP(int n);

	void addFEvent(MissionType type, int ed, int id, int tloc, int mdur, int sig);

	void addXEvent(int ed, int id);

	void addPEvent(int ed, int id);

	LinkedPriorityQueue<Mission*>* completedMissions();

	LinkedPriorityQueue<Polarrovers*>* polarRovers();
	LinkedPriorityQueue<Mountainousrovers*>* mountRovers();
	LinkedPriorityQueue<Emergencyrovers*>* emergRovers();

	int getAutoPromoted();

	~MarsStation();
};
