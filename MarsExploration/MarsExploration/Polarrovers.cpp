#include "Polarrovers.h"


Polarrovers::Polarrovers(){}
Polarrovers::Polarrovers(double speed ,int nom,int checkupDuration):Rover(speed,nom,checkupDuration)
{
}
 void Polarrovers:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
	}
	double Polarrovers:: getspeed()
	{
		return Speed;
	}
	void Polarrovers:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Polarrovers:: getnumofmissions()
	{
		return Nom;
	}
	void Polarrovers:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Polarrovers:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	void Polarrovers:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Polarrovers:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Polarrovers:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Polarrovers:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Polarrovers:: setNomdone (int nomdone)
	 {
		  if (nomdone>0)
			  Nomdone=nomdone;

	 }
	int Polarrovers:: getNomdone()
	{
		return Nomdone;
	}
	void Polarrovers:: setNumofcheckups (int numofcheckups)
	{
		 if (numofcheckups>0)
			 Numofcheckups=numofcheckups;
	}

	int Polarrovers:: getNumofcheckups()
	{
		return Numofcheckups;
	}
Polarrovers::~Polarrovers(void)
{
}
