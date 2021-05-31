#pragma once
#include "Rover.h"
class Emergencyrovers : public Rover
{
private:

public:
	Emergencyrovers();
	Emergencyrovers(double speed ,int nom,int checkupDuration);
	virtual void setspeed(double speed);
	virtual double getspeed();
	virtual void setnumofmissions(int nom);
	virtual int getnumofmissions();
	virtual void setCheckupDuration(int checkupDuration);
	virtual int getCheckupDuration();
	virtual void setFinishcheckupday(int day);
	virtual int getFinishcheckupday();
	virtual void setFinishMaintenanceday(int day);
	virtual int getFinishMaintenanceday();
	virtual void setNomdone (int nomdone);
	virtual int getNomdone();
	virtual void setNumofcheckups (int numofcheckups);
	virtual int getNumofcheckups();
	~Emergencyrovers(void);
};

