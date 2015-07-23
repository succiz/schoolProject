//NAME:        Shuyi Zhao
//COURSE:      COSC 2437/5321
//Lab #6:      Convert infix notation to postfix notation
//ASSIGNED:    Feb 15, 2011
//DUE:         Feb 22, 2011
//OBJECTIVE:   Use a stack (linked implementation) to convert infix notation 
//             to postfix notation
#include <fstream>
#include <iostream>
#include "stackADT.h"
#include "linkedStack.h"
#include "string.h"

using namespace std;

//***********************************************************************************
//
//int j=0;
//char myOperator;
void InToPost(char [] , char []);
int priority(char );
//***********************************************************************************
//main() function
int main()
{
    //
   ifstream myFile;
   char myInfixString[30];
   char myPostfixString[30];
    
    //
   myFile.open("lab6.dat");
   while(myFile.getline(myInfixString,29))
   {
      cout<<endl;
      cout<<"*********************"<<endl;
      cout<<"This is the infix string: "<<myInfixString<<endl;
      InToPost(myInfixString,myPostfixString);
      cout<<"This is the postfix string: "<<myPostfixString<<endl; 
      cout<<"*********************"<<endl;
      cout<<endl;
                                                                                               
   }//end while
   myFile.close();     
 return 0;     
}//end main()

//******************************************************************************************
//priority of operator
int priority(char i)
{
    if(i == '*' || i == '/')
      return 2;
    else if(i == '+' || i == '-')
      return 1;
    else return 0;
}

//*******************************************************************************************
//InToPost function
void InToPost(char myInfixString[], char myPostfixString[])
{  
   //declare a stack & a char & a interge
   linkedStackType<char> myStack;
   char myOperator;
   int j=0;
      
   //initialize myStack
   myStack.initializeStack();

   //for loop to push every charactor in infix string to postfix string
   for(int i=0;i<strlen(myInfixString);i++)
   {  
      if(myInfixString[i] != '+' && myInfixString[i] != '-' && myInfixString[i] != '*' 
                            && myInfixString[i] != '/' && myInfixString[i] != '(' && myInfixString[i] != ')' )
      {
         myPostfixString[j]=myInfixString[i];
         ++j;
      }
      else   
      {
         switch( myInfixString[i])
         {
            case '(': myStack.push(myInfixString[i]);
                      break;//end case '('
            case ')': myOperator=myStack.top();
					  myStack.pop();
                      while(myOperator != '(')
                      {
                          myPostfixString[j]=myOperator;
						  ++j;
                          if(!myStack.isEmptyStack())
						  {
							  myOperator=myStack.top();
                              myStack.pop();
						  }//end if()
                          else break;
                       }//end while()
                       break;//end case ')'
            default: if(myStack.isEmptyStack())
                        myStack.push(myInfixString[i]);
                     else
					 {
						 myOperator=myStack.top();
						 myStack.pop();
                         while (priority(myOperator) >= priority(myInfixString[i]))
					     {
						    myPostfixString[j]=myOperator;
						    ++j;
                            if (!myStack.isEmptyStack())
							{
							   myOperator=myStack.top();
                               myStack.pop();
							}
                            else break;
					     }//end while
                         if (priority(myOperator) < priority(myInfixString[i]))
							 myStack.push(myOperator);
					     myStack.push(myInfixString[i]);
					  }//end else
			}//end switch
		 }//end else
	  }//end for
	  
	  while (!myStack.isEmptyStack())
	  {  
		  myPostfixString[j]=myStack.top();
		  myStack.pop();
		  j++;
	  }//end while
	  myPostfixString[j]='\0';
}//end void InToPost

