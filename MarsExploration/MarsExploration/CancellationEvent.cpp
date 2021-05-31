#include "CancellationEvent.h"

CancellationEvent::CancellationEvent(int ed, int id): Event(ed, id)
{
}
void CancellationEvent::Execute(LinkedList<MountainousMission*>& wm)
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
	delete temp;
}
CancellationEvent::~CancellationEvent(){}