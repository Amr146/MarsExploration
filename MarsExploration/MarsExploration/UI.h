#pragma once
#include "MarsStation.h"
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