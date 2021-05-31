#include "PolarMission.h"

PolarMission::PolarMission()
{

}

PolarMission::PolarMission( int ID, int Target_location, int mission_duration, int Si, int fd):Mission(ID,Target_location,mission_duration,Si, fd)
{

}

void PolarMission::set_id(int ID)
{
	id=ID;
}

int PolarMission::get_id()
{
	return id;
}

void PolarMission::set_tloc(int Target_location)
{
	tloc=Target_location;
}

int PolarMission::get_tloc()
{
	return tloc;
}

void PolarMission::set_mdur(int mission_duration)
{
	mdur=mission_duration;
}

int PolarMission::get_mdur()
{
	return mdur;
}

void PolarMission::set_si(int Si)
{
	Significance=Si;
}

int PolarMission::get_si()
{
	return Significance;
}

void PolarMission::set_FD(int fd)
{
	FD = fd;
}
int PolarMission::get_FD()
{
	return FD;
}

void PolarMission::set_R(Rover* r)
{
	R = r;
}
Rover* PolarMission::get_R()
{
	return R;
}

PolarMission::~PolarMission()
{

}
