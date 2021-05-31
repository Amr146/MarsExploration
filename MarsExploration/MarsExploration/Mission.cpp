#include "Mission.h"

Mission::Mission()
{

}


Mission::Mission( int ID, int Target_location, int mission_duration, int Si, int fd)
{
	id=ID;
	tloc=Target_location;
	mdur=mission_duration;
	Significance=Si;
	FD = fd;
}

void Mission::set_id(int ID)
{
	id=ID;
}

int Mission::get_id()
{
	return id;
}

void Mission::set_tloc(int Target_location)
{
	tloc=Target_location;
}

int Mission::get_tloc()
{
	return tloc;
}

void Mission::set_mdur(int mission_duration)
{
	mdur=mission_duration;
}

int Mission::get_mdur()
{
	return mdur;
}

void Mission::set_si(int Si)
{
	Significance=Si;
}

int Mission::get_si()
{
	return Significance;
}

void Mission::set_FD(int fd)
{
	FD = fd;
}
int Mission::get_FD()
{
	return FD;
}

void Mission::set_R(Rover* r)
{
	R = r;
}
Rover* Mission::get_R()
{
	return R;
}

Mission::~Mission()
{

}

