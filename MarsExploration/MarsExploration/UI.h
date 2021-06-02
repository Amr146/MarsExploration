#pragma once

#ifndef UI_CLASS
#define UI_CLASS

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
	void waitEnter();
	void waitSecond();
	int getModeOfSim();
};
#endif