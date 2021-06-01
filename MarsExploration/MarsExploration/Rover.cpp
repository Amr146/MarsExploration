#include "Rover.h"
Rover:: Rover(){}
   Rover:: Rover(double speed ,int nom,int checkupDuration )
    {
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
	 void Rover:: incrementNumofcheckups()
	 {
		 Numofcheckups++;
	 }
	

	int Rover:: getNumofcheckups()
	{
		return Numofcheckups;
	}
	int Rover:: getExecutionDays(double TL,int MD)
	{
		//TL is the target loction km
		//MD is the mission duration in days
		int z;
		z=int (2*(TL/Speed));
		z=int (z/25);
		return (z+MD);
	}
	void Rover:: incrementmissionsdone()
	{
       Nomdone++;
    }
Rover::~Rover(void)
{
}
