#pragma once
#include"Event.h"
class PromotionEvent : public Event
{
    PromotionEvent(int ed, int id);
    void Execute(LinkedList<MountainousMission*>& wm, LinkedPriorityQueue<EmergencyMission*>& we);
    ~PromotionEvent();
};

