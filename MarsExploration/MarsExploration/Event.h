#pragma once
#include"Constants.h"
#include"LinkedPriorityQueue.h"
#include"LinkedList.h"
#include"LinkedQueue.h"
#include"EmergencyMission.h"
#include"PolarMission.h"
#include"MountainousMission.h"
class Event{
protected:
	//Event day
	int ED;
	//mission ID
	int ID;
public:
	Event(int ed, int id)
	{
		if (ed > 0)
			ED = ed;
		else
			ED = 0;
		ID = id;
	}
	void setED( int D)
	{
		if (D>0)
			ED=D;
	}
	virtual int getED()
	{
		return ED;
	}
	virtual void Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm) = 0;
	virtual ~Event(){}
};