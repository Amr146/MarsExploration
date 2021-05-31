#pragma once
#include "Event.h"

class FormulationEvent :
    public Event
{
private:
    //mission Type enum to indicate the mission type
    MissionType mt;
    //missionís target location (in kilometers from the base station) 
    double TLOC;
    //the number of days needed to fulfill the mission requirements at target location
    int MDUR;
    //the missionís significance
    double SIG;
public:
    FormulationEvent(MissionType MT, int ed, int id, double Tloc, int Mdur, double Sig);
    void Execute(LinkedPriorityQueue<EmergencyMission*> &we, LinkedQueue<PolarMission*> &wp, LinkedList<MountainousMission*>& wm);
    ~FormulationEvent();
};

