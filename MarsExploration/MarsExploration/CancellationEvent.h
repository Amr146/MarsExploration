#pragma once
#include "Event.h"
class CancellationEvent :
    public Event
{
public:
    CancellationEvent(int ed, int id);
    void Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm);
    ~CancellationEvent();
};

