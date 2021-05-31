#include "Mission.h"
class PolarMission: public Mission
{
public:
	PolarMission();
	PolarMission( int ID, int Target_location, int mission_duration, int Si);
	virtual void set_id(int ID);
	virtual int get_id();
	virtual void set_tloc(int Target_location);
	virtual int get_tloc();
	virtual void set_mdur(int mission_duration);
	virtual int get_mdur();
	virtual void set_si(int Si);
	virtual int get_si();
	~PolarMission();
};