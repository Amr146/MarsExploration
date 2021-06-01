#pragma once



#ifndef UI_CLASS
#define UI_CLASS


//#include "MarsStation.h"
class MarsStation;
class UI
{
private:
	MarsStation* station;

public:
	UI(MarsStation* st);
	void loadInputFile();
	void createOutputFile();
	void printDataOfDay(int day);
	void silentMode();
};
#endif