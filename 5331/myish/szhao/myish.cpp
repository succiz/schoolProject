//*********************************************************
//
// Shuyi Zhao
// Operating Systems
// Project #1: Writing Your Own Shell: myish
//
//*********************************************************


//*********************************************************
//
// Includes and Defines
//
//*********************************************************
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <cstdlib>
#include <stdlib.h> 
#include <stdio.h> 
#include <vector>
#include <sys/time.h>
#include <fcntl.h>


using namespace std;
int ccCounter=0;
int czCounter=0;
int cqCounter=0;
void mycolor(char* , char* , char* );
void myPrompt();
void myexit();
void ccHandler(int );
void czHandler(int );
void cqHandler(int );
void myhist(vector<char**>);
void displaycommand(char **);
void myAccess(char *, int );
void myrename(char *, char *);
void mytimer(); 
void mysignalinfo(int);
void mylink(char*,char*);
void myreout(char**,int );
void myrein(char**,int );
void myexec(vector<char**> , char** );

//*********************************************************
//
// Extern Declarations
//
//*********************************************************
using namespace std;
extern "C"
{
  extern char **gettoks();
} 


//*********************************************************
//
// Main Function
//
//*********************************************************
int main( int argc, char *argv[] )
{
  // local variables
  int ii;
  char **toks;
  int retval;

  // initialize local variables
  ii = 0;
  toks = NULL;
  retval = 0;


  // define myhistVector
  vector<char **> myhistVector;
  
  //traps
  //trap ^ c
  signal( SIGINT, ccHandler);
  //traps ^ z
  signal( SIGTSTP, czHandler);
  //traps ^ "\\"
  signal( SIGQUIT, cqHandler);
  //for mytimer
  signal(SIGALRM, mysignalinfo);
      
  // main (infinite) loop
  while( true )
    {
      //prompt
      myPrompt();
      toks = gettoks();

      if( toks[0] != NULL )
	{  
	  // simple loop to echo all arguments
	 /* for( ii=0; toks[ii] != NULL; ii++ )
	    {
	      cout << "Argument " << ii << ": " << toks[ii] << endl;
	    }*/
     //insert elements
      myhistVector.push_back(toks);
      //myhist
      if(strcmp(toks[0],"myhist")==0)
         myhist(myhistVector);
      //myexit command
      if(strcmp(toks[0],"myexit") == 0)
           {  
             myexit();              
           }
      if(strcmp(toks[0],"myAccess") == 0)
           {  
             myAccess(toks[1], 12);
           }
      if(strcmp(toks[0],"myrename") == 0)
           {
              myrename(toks[1],toks[2]); 
           }
      if(strcmp(toks[0],"mytimer") == 0)
           {
              mytimer();
           }
      if(strcmp(toks[0],"mylink") == 0)
           {
              mylink(toks[1],toks[2]);
           }
      for(int i=1;i<myhistVector.size();i++)
      {
         if(strcmp(toks[i],"<") == 0)
         {
            myreout(toks,i);
         }
         if(strcmp(toks[i],">") ==0)
         {
            myrein(toks,i);
         }
      }
	}
	myexec(myhistVector,toks);
    }
  // return to calling environment
  return( retval );
}

//***************************************************************************
//function for prompt
void myPrompt()
{  
   //char cwd;
   string cwd;
   cout<<"[myish:szhao]";
   char *buf=NULL;//[100];
   cwd=getcwd(buf, 100);
   if (cwd=="") 
       false;//error
   else 
       cout<<cwd<<"$"<<endl;//success! print out
}

//**************************************************************************
//Function to exit
void myexit()
{ 
   int status; 
   status = 1;  
   cout<<"trap ^C "<<ccCounter<<" times."<<endl;
   cout<<"trap ^Z "<<czCounter<<" times."<<endl;
   cout<<"trap ^\\ "<<cqCounter<<" times."<<endl;
   exit(status );
}

//***************************************************************************
//Function to trap Ctrl C signal 
void ccHandler(int signo)
{
       ccCounter++;
}
//***************************************************************************
//Function to trap Ctrl Z signal
void czHandler(int signo)
{
     czCounter++;  
}
//***************************************************************************
//Function to trap Ctrl 
void cqHandler(int signo)
{
     
     cqCounter++;
}

//****************************************************************************
//function to store history
void myhist(vector<char**> myhistVector)
{
    int low_index=
        myhistVector.size()>10?
        myhistVector.size()-10:
        0;
    for(int i=low_index;i<myhistVector.size();i++)
      {
            cout<<i<<"   ";
             displaycommand(myhistVector[i]);
      }
}

//*****************************************************************************
//function to diaplay history
void displaycommand(char **toks)
{
   for(int i=0; toks[i]!=NULL;i++)
     {
       cout<<toks[i];
     }
   cout<<endl;
}

//*****************************************************************
//my own function to access
void myAccess(char *filename, int amode) 
{ 
  cout<<"Does "<<*filename<<" exist?"<<endl; 
  if(access(filename, 0) == 0)
    cout<<"Yes"<<endl;
  else
    cout<<"No"<<endl; 
} 

//*****************************************************************
//own function to remame a file
void myrename(char *oldname, char *newname)
{  
   // Rename the file 
   if (rename(oldname, newname) == 0) 
      cout<<"Renamed "<<oldname<<" to "<<newname<<endl; 
   else 
      perror("rename"); 

}
//*****************************************************************
// own function - signal
void mysignalinfo(int x)
{
    cout<<"This is myish!"<<endl;
}

//*****************************************************************
//own function to time
void mytimer()
{
    /*struct itimerval
    {
      struct timeval it_interval; // timer reboot 
      struct timeval it_value;    //initialize timer value
    };


    struct timeval 
    {
       long tv_sec;                //second
       long tv_usec;               //(1/10000) sec
    };*/

    struct itimerval tick;
    tick.it_value.tv_sec = 20;  
    tick.it_value.tv_usec = 0;
    tick.it_interval.tv_sec  = 30;
    tick.it_interval.tv_usec = 0;


    //setitimer trigers SIGPROF
    int ret = setitimer(ITIMER_REAL, &tick,NULL);

    if ( ret != 0)
    {
        cout<<"Set timer error."<<endl;

    }

    cout<<"Wait 20 seconds!"<<endl;

    getchar();
}

//*********************************************************************
//own function to link two files
void mylink(char* FILE1,char* FILE2)   
{    
      link(FILE1,FILE2);
} 

//*********************************************************************
//external function 
void myexec(vector<char**> myhistVector, char** toks)
{
    pid_t pid;
    if(toks[0] != NULL)
    if(toks[0]!=NULL)
    {                    
       pid=fork();
       int stat;
       if(pid<0)//error occurred
       {
          cout<<endl<<"Cannot fork.";
       }
       else if (pid==0)//child process
       {
          execvp(toks[0],toks);
          exit(-1);
       }
       else//parent process
       {
          wait(stat);
          exit(0);
       }
     }//end if()   
} 

//********************************************************************
//redirect a out put
void myreout(char** toks, int i)
{  
   int pid;
   
   if(pid==0)
   {
      int temp;
      temp=open(toks[i],O_RDWR);
      dup2(temp,1);//?
      close(temp);
      toks[i]=NULL;
      execvp(toks[0],toks);
   }
}

//*********************************************************************
//redirect a input
void myrein(char** toks, int i)
{  
   int pid;
   
   if(pid==0)
   {
      int temp;
      temp=open(toks[i],O_RDWR);
      dup2(temp,0);//?
      close(temp);
      toks[i]=NULL;
      execvp(toks[0],toks);
   }
}
