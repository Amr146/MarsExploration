#pragma once
#ifndef UI_H
#define UI_H
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
	void interactiveMode();
	void stepByStepMode();
	void silentMode();
};
#endif