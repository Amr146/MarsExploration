#include "MarsStation.h"
#include"UI.h"

MarsStation::MarsStation(){
	ui = new UI(this);
	auto_promoted = 0;
	Day=1;
	modeOfSim = ui->getModeOfSim();
}

void MarsStation::Simulate()
{
	ReadInput();
	while (!EventList.isEmpty() || !WPMList.isEmpty() || !WMMList.isEmpty() || !WEMList.isEmpty() || !IEList.isEmpty())
	{
		bool condition1=true;
		while(!ICURList.isEmpty()&&condition1)
		{
			Rover *R;
			
			ICURList.peek(R);
			if (int (R->getFinishcheckupday()) == Day)
			{
				ICURList.remove(R);
				
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
					R1->setNomdone(0);
                        WERList.add(R1,R->getspeed());
                     }     
				Polarrovers* R2 = dynamic_cast<Polarrovers*>(R);
				if(R2){
					R2->setNomdone(0);
                        WPRList.add(R2,R->getspeed());
                     }  
				Mountainousrovers* R3 = dynamic_cast<Mountainousrovers*>(R);
				if(R3){
					R3->setNomdone(0);
                        WMRList.add(R3,R->getspeed());
                     } 

			}
			else 
				condition1=false;
		}
		////////////////////////////////////////////////////////////////////////////////////
		bool condition2=true;
		while(!IMRList.isEmpty()&&condition2)
		{
			Rover *R;
			
			IMRList.peek(R);
			if (int (R->getFinishMaintenanceday()) == Day)
			{
				IMRList.remove(R);
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
                        WERList.add(R1,R->getspeed());
                     }     
				Polarrovers* R2 = dynamic_cast<Polarrovers*>(R);
				if(R2){
                        WPRList.add(R2,R->getspeed());
                     }  
				Mountainousrovers* R3 = dynamic_cast<Mountainousrovers*>(R);
				if(R3){
                        WMRList.add(R3,R->getspeed());
                     } 

			}
			else 
				condition2=false;
		}
		/////////////////////////////////////////////////////////////////////////////
		bool condition3=true;
		while (!EventList.isEmpty()&&condition3 )
		{
			Event *E;
			EventList.peek(E);
			if (E->getED()==Day)
			{
				EventList.remove(E);
				FormulationEvent* E1 = dynamic_cast<FormulationEvent*>(E);
				if (E1)
				{
					E1->Execute(WEMList,WPMList,WMMList);
				}
				CancellationEvent* E2 = dynamic_cast<CancellationEvent*>(E);
				if (E2)
				{
					E2->Execute(WEMList,WPMList,WMMList);
				}
				PromotionEvent* E3 = dynamic_cast<PromotionEvent*>(E);
				if (E3)
				{
					E3->Execute(WEMList,WPMList,WMMList);
				}

			}
			else 
				condition3=false;

		}
		///////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////

		// we should handle the AutoP for mountains mission here
		bool z=true;
		while (!WMMList.isEmpty()&&z)
		{
			int index;
	  MountainousMission* temp;
	  int N = WMMList.getLength();
	for (index = 0; index < N; index++)
	{
		if (WMMList.getEntry(index)->getAutoPDay() == Day)
		{
			z=true;
			WMMList.remove(index, temp);
	EmergencyMission* newMission = new EmergencyMission(temp->get_id(), temp->get_tloc(), temp->get_mdur(), temp->get_si(), temp->get_FD());
	delete temp;
	WEMList.add(newMission, newMission->get_pri());
		}
		else
			z=false;
	}
	

		}

		/////////////////////////////////////////////////////////
		/////////////////////////////////////////////////////////
		bool condition4=true;
		while (!WEMList.isEmpty()&&condition4)
		{
			EmergencyMission * ME;
			if (!WERList.isEmpty())
			{
				WEMList.remove(ME);
				Emergencyrovers * R;
				WERList.remove(R);
				ME->set_R(R);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
			}
			else if (!WMRList.isEmpty())
			{
				WEMList.remove(ME);
				Mountainousrovers * R;
				WMRList.remove(R);
				ME->set_R(R);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
			}
			else if (!WPRList.isEmpty())
			{
				WEMList.remove(ME);
				Polarrovers * R;
				WPRList.remove(R);
				ME->set_R(R);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
			}
			else if (!IMRList.isEmpty())
			{
				LinkedPriorityQueue<Rover*>temp;
				Rover * R;
				bool found=false;
				while (!IMRList.isEmpty()&& !found)
				{
				IMRList.remove(R);
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
                       R1->setspeed(R1->getspeed()/2);
					   ME->set_R(R1);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R1->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}

				while (!temp.isEmpty()&& !found)
				{
					IMRList.remove(R);
				Mountainousrovers* R2 = dynamic_cast<Mountainousrovers*>(R);
				if(R2){
                       R2->setspeed(R2->getspeed()/2);
					   ME->set_R(R2);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R2->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					IMRList.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}
				while (!IMRList.isEmpty()&& !found)
				{
				IMRList.remove(R);
				Polarrovers* R3 = dynamic_cast<Polarrovers*>(R);
				if(R3){
                       R3->setspeed(R3->getspeed()/2);
					   ME->set_R(R3);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R3->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}
				while (!temp.isEmpty())
				{
					temp.remove(R);
					IMRList.add(R,(1.0/R->getFinishMaintenanceday()));
				}
				condition4=found;
			}
			else 
				condition4=false;

		}
		///////////////////////////////////////////////////////////////////////////////////
		bool condition5=true;
		while (!WPMList.isEmpty()&&condition5)
		{
			PolarMission * ME;
			
			 if (!WPRList.isEmpty())
			{
				WPMList.dequeue(ME);
				Polarrovers * R;
				WPRList.remove(R);
				ME->set_R(R);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
			}
			 else if (!IMRList.isEmpty())
			{
				LinkedPriorityQueue<Rover*>temp;
				Rover * R;
				bool found=false;
				
				while (!IMRList.isEmpty()&& !found)
				{
				IMRList.remove(R);
				Polarrovers* R3 = dynamic_cast<Polarrovers*>(R);
				if(R3){
                       R3->setspeed(R3->getspeed()/2);
					   ME->set_R(R3);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R3->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1/(R->getFinishMaintenanceday()));
				}
				}
				while (!temp.isEmpty())
				{
					temp.remove(R);
					IMRList.add(R,(1.0/R->getFinishMaintenanceday()));
				}
				condition5=found;
			 }
			else 
				condition5=false;

		}
		////////////////////////////////////////////////////////////////////////////
		bool condition6=true;
		while (!WMMList.isEmpty()&&condition6)
		{
			MountainousMission * ME;
			if (!WMRList.isEmpty())
			{
				WMMList.remove(0,ME);
				Mountainousrovers * R;
				WMRList.remove(R);
				ME->set_R(R);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
			}
			else if (!WERList.isEmpty())
			{
				WMMList.remove(0,ME);
				Emergencyrovers * R;
				WERList.remove(R);
				ME->set_R(R);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
			}
			else if (!IMRList.isEmpty())
			{
				LinkedPriorityQueue<Rover*>temp;
				Rover * R;
				bool found=false;
				while (!IMRList.isEmpty()&& !found)
				{
				IMRList.remove(R);
				Mountainousrovers* R2 = dynamic_cast<Mountainousrovers*>(R);
				if(R2){
                       R2->setspeed(R2->getspeed()/2);
					   ME->set_R(R2);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R2->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}

				while (!temp.isEmpty()&& !found)
				{
					IMRList.remove(R);
				Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
                       R1->setspeed(R1->getspeed()/2);
					   ME->set_R(R1);
				ME->set_WD((Day-(ME->get_FD())));   //setting waiting days of the mission
				int D =R1->getExecutionDays(ME->get_tloc(),ME->get_mdur());
				ME->set_ED(D);
				ME->set_CD(ME->get_WD()+ME->get_FD()+ME->get_ED());
				IEList.add(ME,(1.0/(ME->get_CD())));
				found=true;
                     }     
				else
				{
					temp.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				}
				
				while (!temp.isEmpty())
				{
					temp.remove(R);
					IMRList.add(R,(1.0/R->getFinishMaintenanceday()));
				}
				condition6=found;
			}
		
			else 
				condition6=false;
			

		}
		/////////////////////////////////////////////////////////////////////
		bool condition7=true;
		while (!IEList.isEmpty()&&condition7)
		{
			Mission * M;
			IEList.peek(M);

			if (int (M->get_CD())==Day)
			{
				IEList.remove(M);
				CMList.add(M,(1/(M->get_CD())));
				Rover * R=M->get_R();
				R->incrementmissionsdone();
				if (R->getNomdone()==R->getnumofmissions())
				{
					R->incrementNumofcheckups();
					R->setFinishcheckupday(Day+R->getCheckupDuration());
					ICURList.add(R,1.0/(R->getFinishcheckupday()));
				}
				//////////////////////add maintance condition here//////////////
				else if (R->getNumofcheckups()>2 && R->getNomdone()==(R->getnumofmissions()+1)/2)
				{
				int z=	(R->getCheckupDuration()+1)/2;
				int m=Day+z;
				R->setFinishMaintenanceday(m);
				IMRList.add(R,1.0/(R->getFinishMaintenanceday()));
				}
				else
				{
					Emergencyrovers* R1 = dynamic_cast<Emergencyrovers*>(R);
				if(R1){
                        WERList.add(R1,R->getspeed());
                     }     
				Polarrovers* R2 = dynamic_cast<Polarrovers*>(R);
				if(R2){
                        WPRList.add(R2,R->getspeed());
                     }  
				Mountainousrovers* R3 = dynamic_cast<Mountainousrovers*>(R);
				if(R3){
                        WMRList.add(R3,R->getspeed());
                     } 
				}
				
			}
			else 
				condition7=false;
		}
		////////////////////////////////////////////////////////////////////////////////////////////////
		if(modeOfSim == 1){
			ui->printDataOfDay(Day);
			ui->waitEnter();
		}else if(modeOfSim == 2){
			ui->printDataOfDay(Day);
			ui->waitSecond();
		}
		Day++;
	}
	if(modeOfSim == 3)
		ui->silentMode();
}

void MarsStation::ReadInput(){
	ui->loadInputFile();
}

void MarsStation::AssignMissions(){}

void MarsStation::WriteOutput(){}

void MarsStation::createMrovers(int n, double speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Mountainousrovers* newMrover = new Mountainousrovers(speed, nom, checkUp);
		WMRList.add(newMrover, 0);		//	what is the default priority
	}
}

void MarsStation::createProvers(int n, double speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Polarrovers* newMrover = new Polarrovers(speed, nom, checkUp);
		WPRList.add(newMrover, 0);		//	what is the default priority
	}
}

void MarsStation::createErovers(int n, double speed, int nom, int checkUp){
	for(int i = 0; i < n; i++){
		Emergencyrovers* newMrover = new Emergencyrovers(speed, nom, checkUp);
		WERList.add(newMrover, 0);		//	what is the default priority
	}
}

void MarsStation::setAutoP(int n){
	autoP = n;
}

void MarsStation::addFEvent(MissionType type, int ed, int id, int tloc, int mdur, int sig){
	FormulationEvent* fEvent = new FormulationEvent(type, ed, id, tloc, mdur, sig);
	EventList.add(fEvent, 10.0/ed);					//	what is the priority of this queue
}

void MarsStation::addXEvent(int ed, int id){
	CancellationEvent* xEvent = new CancellationEvent(ed, id);
	EventList.add(xEvent, 10.0/ed);					//	what is the priority of this queue
}

void MarsStation::addPEvent(int ed, int id){
	PromotionEvent* pEvent = new PromotionEvent(ed, id);
	EventList.add(pEvent, 10.0/ed);					//	what is the priority of this queue
}

LinkedPriorityQueue<Mission*>* MarsStation::completedMissions(){
	return &CMList;
}

LinkedPriorityQueue<Polarrovers*>* MarsStation::polarRovers(){
	return &WPRList;
}

LinkedPriorityQueue<Mountainousrovers*>* MarsStation::mountRovers(){
	return &WMRList;
}

LinkedPriorityQueue<Emergencyrovers*>* MarsStation::emergRovers(){
	return &WERList;
}

LinkedQueue<PolarMission*>* MarsStation::polarMissions(){
	return  &WPMList;
}

LinkedList<MountainousMission*>* MarsStation::mountMissions(){
	return &WMMList;
}

LinkedPriorityQueue<EmergencyMission*>* MarsStation::emergMissions(){
	return &WEMList;
}

LinkedPriorityQueue<Mission*>* MarsStation::inExec(){
	return &IEList;
}

LinkedPriorityQueue<Rover*>* MarsStation::inCheck(){
	return &ICURList;
}

LinkedPriorityQueue<Mission*>* MarsStation::compMissions(){
	return &CMList;
}

void MarsStation::setMode(int mode){
	modeOfSim = mode;
}

int MarsStation::getMode(){
	return modeOfSim;
}

int MarsStation::getAutoPromoted(){
	return auto_promoted;
}

MarsStation::~MarsStation(){
	ui->createOutputFile();
	delete ui;
}