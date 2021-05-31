#pragma once
#include"Rover.h"
class Mission
{
protected:
	int id;
	double tloc;
	int mdur;
	double Significance;
	int FD;
	// pointer to rover
	Rover* R;
public:
	Mission( int ID, double Target_location, int mission_duration, double Si, int FD);
	virtual void set_id(int ID);
	virtual int get_id();
	virtual void set_tloc(double Target_location);
	virtual double get_tloc();
	virtual void set_mdur(int mission_duration);
	virtual int get_mdur();
	virtual void set_si(double Si);
	virtual double get_si();
	virtual void set_FD(int fd);
	virtual int get_FD();
	virtual void set_R(Rover* r);
	virtual Rover* get_R();
	~Mission();
};
