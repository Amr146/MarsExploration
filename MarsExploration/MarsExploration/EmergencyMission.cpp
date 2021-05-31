#include "EmergencyMission.h"

EmergencyMission::EmergencyMission()
{

}

EmergencyMission::EmergencyMission( int ID, int Target_location, int mission_duration, int Si, int fd):Mission(ID,Target_location,mission_duration,Si, fd)
{
	priority=float(Significance/(tloc*mdur));
}

void EmergencyMission::set_id(int ID)
{
	id=ID;
}

int EmergencyMission::get_id()
{
	return id;
}

void EmergencyMission::set_tloc(int Target_location)
{
	tloc=Target_location;
}

int EmergencyMission::get_tloc()
{
	return tloc;
}

void EmergencyMission::set_mdur(int mission_duration)
{
	mdur=mission_duration;
}

int EmergencyMission::get_mdur()
{
	return mdur;
}

void EmergencyMission::set_si(int Si)
{
	Significance=Si;
}

int EmergencyMission::get_si()
{
	return Significance;
}

void EmergencyMission::set_pri(int Target_location, int mission_duration, int Si)
{
	priority=float(Significance/(tloc*mdur));
}

float EmergencyMission::get_pri()
{
	return priority;
}

void EmergencyMission::set_FD(int fd)
{
	FD = fd;
}
int EmergencyMission::get_FD()
{
	return FD;
}

void EmergencyMission::set_R(Rover* r)
{
	R = r;
}
Rover* EmergencyMission::get_R()
{
	return R;
}

EmergencyMission::~EmergencyMission()
{

}
