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
#include"PolarMission.h"
#include"MountainousMission.h"

class MarsStation
{
protected:
	LinkedPriorityQueue<Event*> EventList;
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

	~MarsStation();
};

