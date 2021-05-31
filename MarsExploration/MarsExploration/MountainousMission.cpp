#include "MountainousMission.h"

MountainousMission::MountainousMission()
{

}

MountainousMission::MountainousMission( int ID, int Target_location, int mission_duration, int Si):Mission(ID,Target_location,mission_duration,Si)
{

}

void MountainousMission::set_id(int ID)
{
	id=ID;
}

int MountainousMission::get_id()
{
	return id;
}

void MountainousMission::set_tloc(int Target_location)
{
	tloc=Target_location;
}

int MountainousMission::get_tloc()
{
	return tloc;
}

void MountainousMission::set_mdur(int mission_duration)
{
	mdur=mission_duration;
}

int MountainousMission::get_mdur()
{
	return mdur;
}

void MountainousMission::set_si(int Si)
{
	Significance=Si;
}

int MountainousMission::get_si()
{
	return Significance;
}

MountainousMission::~MountainousMission()
{

}
