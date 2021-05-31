#include "MountainousMission.h"

MountainousMission::MountainousMission()
{

}

MountainousMission::MountainousMission( int ID, int Target_location, int mission_duration, int Si, int fd):Mission(ID,Target_location,mission_duration,Si, fd)
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

void MountainousMission::set_FD(int fd)
{
	FD = fd;
}
int MountainousMission::get_FD()
{
	return FD;
}

void MountainousMission::set_R(Rover* r)
{
	R = r;
}
Rover* MountainousMission::get_R()
{
	return R;
}

MountainousMission::~MountainousMission()
{

}
