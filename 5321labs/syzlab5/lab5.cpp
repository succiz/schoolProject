//Name: SHUYI ZHAO
//COURSE:      COSC 5321
//Lab #5:      Recursive Function ¨C Phase 2
//ASSIGNED:    Feb  8, 2011
//DUE:         Feb 15, 2011
//OBJECTIVE:   Create a recursive function to convert a decimal (base 10) integer 
//             to another base.

#include<iostream>
#include<math.h>
using namespace std;


void decToBase(int, int);
void swap(int);


int main()
{   
    int num;
    int base;
    char wish;
    do
    {
         cout<<"Do you want to convert a number? (Y/N):";
         cin>>wish;
         if(wish == 'N')
            return 0;
         else
            if(wish == 'Y') 
            { 
                  cout<<"Please enter the number you want to convert:";
                  cin>>num;
                  cout<<"Please enter the base you want to use:";
                  cin>>base;
                  if(base<2 || base>20)
                        cout<<"Your base is illegal."<<endl;
                  else
                     {
                        cout<<num<<" is ";
                        decToBase(num,base);
                        cout<<"(base "<<base<<")."<<endl<<endl;
                     }
            }   
            else
                  cout<<"Wrong command."<<endl;
     }
     while(wish != 'N');
     system("pause");
    return 0;
}

//Purpose: to get the number base 2-20
//Pre-condition:the number(dec) and base have been input from keyboard
//Post-condition:the number(dec) turned into number base a base between 2 to 20 
void decToBase(int num,int base)
{
  if(num > 0)
  { 
      decToBase(num/base,base);
      if(num%base < 10)
         cout<<num%base;
      else
         swap(num%base);    
   }
}

//Purpose:swap numbers into charactors
//Pre-condition:transfer number base a number more than 9
//Post-condition:10-19 swap to A-J
void swap(int moreThan10)
{
   switch(moreThan10)
         {
            case 10: cout<<'A';
                     break;
            case 11: cout<< 'B';
                     break;
            case 12: cout<< 'C';
                     break;
            case 13: cout<< 'D';
                     break;
            case 14: cout<< 'E';
                     break;
            case 15: cout<< 'F';
                     break;
            case 16: cout<< 'G';
                     break;
            case 17: cout<< 'H';
                     break;
            case 18: cout<< 'I';
                     break;
            case 19: cout<< 'J';
                     break;
            default: cout<<"Wrong!"<<endl;  
          }  
}

