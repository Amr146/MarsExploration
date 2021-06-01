#include "Rover.h"
int Rover::count = 0;
   Rover:: Rover(double speed ,int nom,int checkupDuration )
    {
		ID = ++count;

		if (speed>0 && nom>0 && checkupDuration>0)
		{
			Speed=speed;
			Nom=nom;
			CheckupDuration=checkupDuration;
		}
		else
		{
			Speed = 0;
			Nom = 0;
			CheckupDuration = 0;
		}
		Nomdone=0;    //intaial value
		Numofcheckups=0; //intaial value
		Finishcheckupday = 0;
		FinishMaintenanceday = 0;
    }
   void Rover:: setspeed(double speed)
	{
		if (speed>0)
			Speed=speed;
	}
	double Rover:: getspeed()
	{
		return Speed;
	}
	void Rover:: setnumofmissions(int nom)
	{
		if  (nom>0)
			Nom=nom;
	}
	int Rover:: getnumofmissions()
	{
		return Nom;
	}
	void Rover:: setCheckupDuration(int checkupDuration)
	{
		if ( checkupDuration>0)
			CheckupDuration=checkupDuration;
	}
	int Rover:: getCheckupDuration()
	{
		return CheckupDuration;
	}
	 void Rover:: setFinishcheckupday(int day)
	 {
		 if (day>0)
			 Finishcheckupday=day;
	 }
	 int Rover:: getFinishcheckupday()
	 {
		 return Finishcheckupday;
	 }
	 void Rover:: setFinishMaintenanceday(int day)
	 {
		  if (day>0)
			 FinishMaintenanceday=day;
	 }
	 int Rover:: getFinishMaintenanceday()
	 {
		 return FinishMaintenanceday;
	 }
	 void Rover:: setNomdone (int nomdone)
	 {
		  if (nomdone>0)
			  Nomdone=nomdone;

	 }
	int Rover:: getNomdone()
	{
		return Nomdone;
	}
	void Rover:: setNumofcheckups (int numofcheckups)
	{
		 if (numofcheckups>0)
			 Numofcheckups=numofcheckups;
	}

	int Rover:: getNumofcheckups()
	{
		return Numofcheckups;
	}

	void Rover::setid(int id){
		ID = id;
	}

	int Rover::getid(){
		return ID;
	}


Rover::~Rover(void)
{
}
