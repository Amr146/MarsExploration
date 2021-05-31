#pragma once
#include "Event.h"
class CancellationEvent :
    public Event
{
public:
    CancellationEvent(int ed, int id);
    void Execute(LinkedList<MountainousMission*> &wm);
    ~CancellationEvent();
};

