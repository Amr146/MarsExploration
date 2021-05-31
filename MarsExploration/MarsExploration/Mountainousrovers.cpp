#include "Mountainousrovers.h"


Mountainousrovers::Mountainousrovers(){}
Mountainousrovers::Mountainousrovers(double speed ,int nom,int checkupDuration):Rover(speed,nom,checkupDuration)
{
}
 void Mountainousrovers:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
	}
	double Mountainousrovers:: getspeed()
	{
		return Speed;
	}
	void Mountainousrovers:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Mountainousrovers:: getnumofmissions()
	{
		return Nom;
	}
	void Mountainousrovers:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Mountainousrovers:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	void Mountainousrovers:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Mountainousrovers:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Mountainousrovers:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Mountainousrovers:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Mountainousrovers:: setNomdone (int nomdone)
	 {
		  if (nomdone>0)
			  Nomdone=nomdone;

	 }
	int Mountainousrovers:: getNomdone()
	{
		return Nomdone;
	}
	void Mountainousrovers:: setNumofcheckups (int numofcheckups)
	{
		 if (numofcheckups>0)
			 Numofcheckups=numofcheckups;
	}

	int Mountainousrovers:: getNumofcheckups()
	{
		return Numofcheckups;
	}

Mountainousrovers::~Mountainousrovers(void)
{
}
