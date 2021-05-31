#include "FormulationEvent.h"
#include"Mission.h"
#include"EmergencyMission.h"
#include"PolarMission.h"
#include"MountainousMission.h"

FormulationEvent::FormulationEvent(MissionType MT, int ed, int id, double Tloc, int Mdur, double Sig): Event(ed,id)
{
	mt = MT;
	if (Tloc > 0)
		TLOC = Tloc;
	if (Mdur > 0)
		MDUR = Mdur;
	SIG = Sig;
}
void FormulationEvent::Execute(LinkedPriorityQueue<EmergencyMission*>& we, LinkedQueue<PolarMission*>& wp, LinkedList<MountainousMission*>& wm)
{
	switch (mt)
	{
	case E:
		EmergencyMission* newMission = new EmergencyMission(ID, TLOC, MDUR, SIG, ED);
		we.add(newMission, newMission->get_pri());
		break;
	case P:
		PolarMission* newMission1 = new PolarMission(ID, TLOC, MDUR, SIG, ED);
		wp.enqueue(newMission1);
		break;
	case M:
		MountainousMission* newMission2 = new MountainousMission(ID, TLOC, MDUR, SIG, ED);
		wm.insert(newMission2);
			break;
	default:
		break;
	}
}
FormulationEvent::~FormulationEvent()
{

}