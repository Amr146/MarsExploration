#pragma once
class Rover
{
	static int count;
protected:
	
	int ID;
	double Speed;
	int Nom;   //=4   //number of missions can be done before checkup
	int CheckupDuration;  //number of days to finish checkup
	int Finishcheckupday;  //the day that the rover finish checkup in and ready to take mission
	int FinishMaintenanceday; //(bonus)the day that the rover finish Maintenance in and ready to take mission
	int Nomdone;     //number of missions done by rover before its checkup
	int Numofcheckups; //number of checkups done fore the rover
public:
	Rover(double speed ,int nom,int checkupDuration );
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
	virtual void setid(int id);
	virtual int getid();

	~Rover(void);
};

