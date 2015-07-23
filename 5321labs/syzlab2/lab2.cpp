//Name:     Shuyi Zhao
//Course:   COSC 5321
//Lab #:    2
//Assigned: Jan 25, 2011
//Due:      Feb  1, 2011
//Purpose:  To create and access an unordered linked list and an ordered linked list.
//
//Input:    create lists using file input from lab2.dat. Use keyboard input for
//            search values.
//
//Output:   All output directed to the screen.
//
//Program Outline/Design:
//          1.creat the objects of unordered linked list and ordered linked list.
//          2.creat a object of interator
//          3.read data from lab2.dat to linked list
//          4.call founctions(eg:insertLast)for each objects

#include <iostream>
#include <fstream>
#include "unorderedLinkedList.h"
#include "orderedLinkedList.h"
#include <cassert>
using namespace std;

void readData1(ifstream& ,unorderedLinkedList<int>& );
void readData2(ifstream& ,unorderedLinkedList<int>& );
void readData3(ifstream& ,orderedLinkedList<int>& );
void print_unorderedLinkedList(unorderedLinkedList<int>& );
void print_orderedLinkedList(orderedLinkedList<int>& );
void iterator_unordered(linkedListIterator<int>& ,unorderedLinkedList<int>& );
void iterator_ordered(linkedListIterator<int>& ,orderedLinkedList<int>& );
void length_unordered(unorderedLinkedList<int>& );
void length_ordered(orderedLinkedList<int>& );
void search_data(unorderedLinkedList<int>& );
void search_dataordered(orderedLinkedList<int>& );
int main()
{  
//
//unorderedLinkedList in forward
//
   //declare my_list, my_it, and open my_ifile
    unorderedLinkedList<int> my_list1;
    unorderedLinkedList<int> my_list2;
    orderedLinkedList<int> my_list3;
	linkedListIterator<int> my_it;
	ifstream my_ifile1;
    ifstream my_ifile2;
    ifstream my_ifile3;
    //read data from lab.dat to my_list1
   	my_ifile1.open("lab2.dat");
   	readData1(my_ifile1,my_list1);
   	my_ifile1.close();
	//display mylist1 with print() function
	cout<<"This is the unorderedLinkedList in forward~!"<<endl;
    print_unorderedLinkedList(my_list1);
	//display list with iterator
	iterator_unordered(my_it,my_list1);
    //length and info feild
    length_unordered(my_list1);
    //search data
    search_data(my_list1);
 //
 //unorderedlinklist in backword
 //
  //read data from lab.dat to my_list2
   	my_ifile2.open("lab2.dat");
   	readData2(my_ifile2,my_list2);
   	my_ifile2.close();
	//display mylist1 with print() function
	cout<<"This is the unorderedLinkedList in backward~!"<<endl;
    print_unorderedLinkedList(my_list2);
	//display list with iterator
	iterator_unordered(my_it,my_list2);
    //length and info feild
    length_unordered(my_list2);
    //search data
    search_data(my_list2);
 
    //ordered linkedlist
	//read data from lab.dat to my_list1
   	my_ifile3.open("lab2.dat");
   	readData3(my_ifile3,my_list3);
   	my_ifile3.close();
	//display mylist1 with print() function
	cout<<"This is the orderedLinkedList!"<<endl;
    print_orderedLinkedList(my_list3);
	//display list with iterator
	iterator_ordered(my_it,my_list3);
    //length and info feild
    length_ordered(my_list3);
    //search data
    search_dataordered(my_list3);
     
     
 return 0;
}  
//
void readData1(ifstream& infile,unorderedLinkedList<int>& list)
{
    int temp;
	infile>>temp;
	while (!infile.eof())//use switch?in one founction
	 {
      list.insertLast(temp);
      infile>>temp;
	 }
}
//
void readData2(ifstream& infile,unorderedLinkedList<int>& list)
{
    int temp;
	infile>>temp;
	while (!infile.eof())//use switch?in one founction
	 {
      list.insertFirst(temp);
      infile>>temp;
	 }
}
//
void print_unorderedLinkedList(unorderedLinkedList<int>& list)
{ cout<<"This is a one line print."<<endl;
  list.print();
  cout<<endl;    
}  
//
void iterator_unordered(linkedListIterator<int>& it,unorderedLinkedList<int>& list)
{  
   cout<<"This is the form."<<endl;
   int i=1;
   for(it=list.begin();it!=list.end();++it)//???
	 { 
       cout<<i<<"   "<<*it<<endl;
       i++;
     }
}
//
void length_unordered(unorderedLinkedList<int>& list )
{
     cout<<"There are "<<list.length()<<" data in lab2.dat"<<endl;
     cout<<"The info field of first node is:"<<list.front()<<endl;
     cout<<"The info field of last node is:"<<list.back()<<endl;     
}     
//
void search_data(unorderedLinkedList<int>& list)
{
     int data;
     cout<<"Please enter the data that you want to seatch:";
     cin>>data;
     if(list.search(data)) cout<<"Your data has been found."<<endl;
     else cout<<"The data does not exit in lab.dat file!"<<endl;
}
void readData3(ifstream& infile,orderedLinkedList<int>& list)
{
    int temp;
	infile>>temp;
	while (!infile.eof())//use switch?in one founction
	 {
      list.insert(temp);
      infile>>temp;
	 }
}
//
void print_orderedLinkedList(orderedLinkedList<int>& list)
{
  cout<<"This is a one line print."<<endl;
  list.print();
  cout<<endl;    
}  
//
void iterator_ordered(linkedListIterator<int>& it,orderedLinkedList<int>& list)
{  
   cout<<"This is the form."<<endl;
   int i=1;
   for(it=list.begin();it!=list.end();++it)//???
	 { 
       cout<<i<<"   "<<*it<<endl;
       i++;
     }
}
//
void length_ordered(orderedLinkedList<int>& list )
{
     cout<<"There are "<<list.length()<<" data in lab2.dat"<<endl;
     cout<<"The info field of first node is:"<<list.front()<<endl;
     cout<<"The info field of last node is:"<<list.back()<<endl;     
}     
//
void search_dataordered(orderedLinkedList<int>& list)
{
     int data;
     cout<<"Please enter the data that you want to seatch:";
     cin>>data;
     if(list.search(data)) cout<<"Your data has been found."<<endl;
     else cout<<"The data does not exit in lab.dat file!"<<endl;
}
