//Name:     Shuyi Zhao
//Course:   COSC 5321
//Lab #:    3
//Assigned: Feb  1, 2011
//Due:      Feb  8, 2011
//Purpose:  To create and access an doubly linked list.
//          
//
//Input:    create lists using file input from lab3.dat. Use keyboard input for
//            search values.
//
//Output:   All output directed to the screen.
//
//Program Outline/Design:
//          1.write copylist function
//          2.modify default constructor, copy constructor, and destructor
//          3.modify insert function
//          4.write getItemForward and getItemReverse function and add private node currentNode for this
//          5.write loops for acting getItemForward and getItemReverse

#include <iostream>
#include <fstream>
#include "doublyLinkedList.h"
using namespace std;

template<class Type>
void readData(ifstream& ,doublyLinkedList<Type>& );

int main()
{  
//
//doublyLinkedList 
//
   //declare my_list and open my_ifile
    doublyLinkedList<int> my_list;
    doublyLinkedList<int> my_copylist;
	ifstream my_ifile;

    //read data from lab.dat to my_list1
   	my_ifile.open("lab2.dat");
   	readData(my_ifile,my_list);
   	my_ifile.close();

	//
	cout<<"This is a forward print:"<<endl;
	my_list.print();
	cout<<endl;

	//
	cout<<endl;
	cout<<"This is a backward print:"<<endl;
	my_list.reversePrint();
	cout<<endl;

	//
	cout<<endl;
	cout<<"This is a getForward print:"<<endl;
    int index1=1;
    while(index1<=my_list.length())
    {
      cout<<index1<<"   ";
	  cout<<my_list.getItemForward(index1)<<endl;
	  index1++;
    }

	//
	cout<<endl;
	cout<<"This is a getReverse print:"<<endl;
    int index2=my_list.length();
	while(index2 >= 1)
    {
      cout<<index2<<"   ";
	  cout<<my_list.getItemReverse(index2)<<endl;
	  index2--;
    }

	//copylist
	my_copylist = my_list;

	//
	cout<<endl;
	cout<<"This is a getForward print of my_copylist:"<<endl;
    int index3=1;
	while(index3 <= my_copylist.length())
    {
      cout<<index3<<"   ";
	  cout<<my_copylist.getItemForward(index3)<<endl;
	  index3++;
    }

	//
	cout<<endl;
    cout<<"This is a getReverse print of my_copylist:"<<endl;
	int index4=my_copylist.length();
	while(index4>=1)
    {
      cout<<index4<<"   ";
	  cout<<my_copylist.getItemReverse(index4)<<endl;
	  index4--;
    }
    system("pause");
	return 0;

}
template<class Type>
void readData(ifstream& infile,doublyLinkedList<Type>& list)
{
    int temp;
	infile>>temp;
	while (!infile.eof())
	 {
      list.insert(temp);
      infile>>temp;
	 }
}

