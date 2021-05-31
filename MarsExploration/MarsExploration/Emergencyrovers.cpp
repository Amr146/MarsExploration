#include "Emergencyrovers.h"

Emergencyrovers::Emergencyrovers(double speed ,int nom,int checkupDuration):Rover(speed,nom,checkupDuration)
{
}
 void Emergencyrovers:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
			//Rover::setspeed(speed);
	}
	double Emergencyrovers:: getspeed()
	{
		return Speed;
	}
	void Emergencyrovers:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Emergencyrovers:: getnumofmissions()
	{
		return Nom;
	}
	void Emergencyrovers:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Emergencyrovers:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	void Emergencyrovers:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Emergencyrovers:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Emergencyrovers:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Emergencyrovers:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Emergencyrovers:: setNomdone (int nomdone)
	 {
		  if (nomdone>0)
			  Nomdone=nomdone;

	 }
	int Emergencyrovers:: getNomdone()
	{
		return Nomdone;
	}
	void Emergencyrovers:: setNumofcheckups (int numofcheckups)
	{
		 if (numofcheckups>0)
			 Numofcheckups=numofcheckups;
	}

	int Emergencyrovers:: getNumofcheckups()
	{
		return Numofcheckups;
	}

Emergencyrovers::~Emergencyrovers(void)
{
}
