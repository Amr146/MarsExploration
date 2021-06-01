#include "Mission.h"

Mission::Mission( int ID, double Target_location, int mission_duration, double Si, int fd)
{
	id=ID;
	tloc=Target_location;
	mdur=mission_duration;
	Significance=Si;
	FD = fd;
	R = nullptr;
}

void Mission::set_id(int ID)
{
	id=ID;
}

int Mission::get_id()
{
	return id;
}

void Mission::set_tloc(double Target_location)
{
	tloc=Target_location;
}

double Mission::get_tloc()
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

void Mission::set_si(double Si)
{
	Significance=Si;
}

double Mission::get_si()
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

void Mission::set_WD(int wd){
	WD = wd;
}

int Mission::get_WD(){
	return WD;
}

void Mission::set_CD(int cd){
	CD = cd;
}

int Mission::get_CD(){
	return CD;
}

void Mission::set_ED(int ed){
	ED = ed;
}

int Mission::get_ED(){
	return ED;
}


Mission::~Mission()
{

}

