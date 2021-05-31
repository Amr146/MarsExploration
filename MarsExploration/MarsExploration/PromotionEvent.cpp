#include "PromotionEvent.h"

PromotionEvent::PromotionEvent(int ed, int id) : Event(ed, id)
{
}
void PromotionEvent::Execute(LinkedList<MountainousMission*>& wm, LinkedPriorityQueue<EmergencyMission*>& we)
{
	int index;
	MountainousMission* temp;
	int N = wm.getLength();
	for (index = 0; index < N; index++)
	{
		if (wm.getEntry(index)->get_id() == ID)
			break;
	}
	wm.remove(index, temp);
	EmergencyMission* newMission = new EmergencyMission(temp->get_id(), temp->get_tloc(), temp->get_mdur(), temp->get_si(), temp->get_FD());
	delete temp;
	we.add(newMission, newMission->get_pri());
}
PromotionEvent::~PromotionEvent() {}