//NAME:       Shuyi Zhao
//COURSE:     COSC 2437/5321
//Lab #7:     Simulation: Airport Delay Problem
//            (Categorize data using queue class)
//ASSIGNED:   Feb 22, 2011
//DUE:        Mar  1, 2011
//OBJECTIVE:  Simulate an "instance" of resolving a departure delay problem 
//            for an airport runway by categorizing data and then adding the 
//            data to the appropriate queue category

#include<iostream>
#include<fstream>
#include<iomanip>
#include<math.h>
#include"linkedQueue.h"
#include"queueADT.h"
using namespace std;

//structure for flight
struct FlightRecord
{
   int flightNum;      //a 4-digit airplane flight number
   int arrivalHour;    //runway arrival hour
   int arrivalMinute;  //runway arrival minute
};

void delayTime(linkedQueueType<FlightRecord>& ,int , int , ofstream& );


//main() function
int main()
{  
   //declare 
   char flightType;
   int i=0;
   int departHour=10;
   int departMinute=50;
   ifstream myInFile;
   ofstream myOutFile;
   FlightRecord myFlight;
   linkedQueueType<FlightRecord> interQ;
   linkedQueueType<FlightRecord> nationQ;
   linkedQueueType<FlightRecord> localQ;
   
   myInFile.open("lab7.dat");
   myOutFile.open("lab7.txt");

   myOutFile<<"*****************************************************"<<endl;
   myOutFile<<"The order in which the airplanes arrive at the runway:\n";
   myOutFile<<"*****************************************************"<<endl;
   myOutFile<<"Number"<<setw(15)<<"arrival time\n";

   myInFile>>flightType;
   while(!myInFile.eof())
   {
      myInFile>>myFlight.flightNum;
      myInFile>>myFlight.arrivalHour;
      myInFile>>myFlight.arrivalMinute;
	  myInFile.ignore();
	  
	  myOutFile<<"#"<<myFlight.flightNum<<setw(12)<<myFlight.arrivalHour<<":"<<myFlight.arrivalMinute<<endl;
	  
   
      if(flightType == 'I')
         interQ.addQueue(myFlight);
      else if(flightType == 'N')
         nationQ.addQueue(myFlight);
      else
         localQ.addQueue(myFlight);

	  myInFile>>flightType;
   }
   
   myOutFile<<endl;
   myOutFile<<"*****************************************************"<<endl;
   myOutFile<<"The order in which the airplanes depart at the runway:\n";
   myOutFile<<"*****************************************************"<<endl;
   myOutFile<<"Number"<<setw(15)<<"arrival time"<<setw(15)<<"depart time"<<setw(15)<<"delay time"<<endl;
   
   while(!interQ.isEmptyQueue())
	   delayTime(interQ,departMinute,departHour,myOutFile);
   while(!nationQ.isEmptyQueue())
	   delayTime(nationQ,departMinute,departHour,myOutFile);
   while(!localQ.isEmptyQueue())
	   delayTime(localQ,departMinute,departHour,myOutFile);
	   
   myInFile.close();   
   myOutFile.close();
   cout<<"It works!"<<endl;
   return 0;
}

//purpose:calculate the delay time of each flight
//procondition:
//postcondition:
void delayTime(linkedQueueType<FlightRecord>& myQueue,int departMinute, int departHour, ofstream& myOutFile)
{  
   int delayHour;
   int delayMinute;
   FlightRecord temp;

   temp=myQueue.front();

   //calculate the daparture time
   departMinute=departMinute+5;
   if(departMinute >= 60)
   {
	  departMinute=departMinute-60;
      departHour=departHour+1;
   }
   
   //calculate the delay time
   if(departMinute < temp.arrivalMinute)
   {   
	   delayMinute=departMinute+60-temp.arrivalMinute;
       delayHour=departHour-1-temp.arrivalHour;
   }
   else
   {
	   delayMinute=departMinute-temp.arrivalMinute;
	   delayHour=departHour-temp.arrivalHour;
   }
   myQueue.deleteQueue();
   myOutFile<<"#"<<temp.flightNum<<setw(13)<<temp.arrivalHour<<":"<<temp.arrivalMinute<<setw(12)
                            <<departHour<<":"<<departMinute<<setw(12)<<delayHour<<":"<<delayMinute<<endl;//?
}
