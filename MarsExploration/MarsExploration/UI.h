#pragma once
#ifndef UI_CLASS
#define UI_CLASS

//#include "MarsStation.h"
class MarsStation;
class UI
{
	MarsStation* station;

public:
	UI(MarsStation* st);
	void loadInputFile();
	void createOutputFile();
	void interactiveMode();
	void stepByStepMode();
	void silentMode();
};
#endif