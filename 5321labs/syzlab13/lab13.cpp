//NAME:        Shuyi Zhao
//COURSE:      COSC 2437/5321
//Lab #13:     AVL Trees ¨C Part 2
//ASSIGNED:    Apr 12, 2011
//DUE:         Apr 19, 2011
//OBJECTIVE:   Modify the AVL tree in the previous lab to include 
//             passing functions as parameters
//             printing the tree hierarchically


#include <iostream>
#include <fstream>
#include <iomanip>
#include "AVLTree2.h"

using namespace std;

void display(AVLTreeType<int> tree1, AVLTreeType<int> tree2);
void print(int&);
void printTree(int& x, int level);

int main()
{
    AVLTreeType<int> tree1;
    AVLTreeType<int> tree2;
    
    ifstream inFile1;
    ifstream inFile2;
    
    inFile1.open("lab12file1.dat");
    inFile2.open("lab12file2.dat");
    
    while(!inFile1.eof())
    {
        int element1;
        inFile1 >> element1;
        tree1.insert(element1);
    }
    
    while(!inFile2.eof())
    {
        int element2;
        inFile2 >> element2;
        tree2.insert(element2);
    }
    
    display(tree1, tree2);
    
    inFile1.close();
    inFile2.close();
    
    return 0;
}

//Purpose: display function is to display data on screen
//Pre-condition: data has been insert into AVL tree
//post-condition: data was printed out on screen
void display(AVLTreeType<int> tree1, AVLTreeType<int> tree2)
{
	cout << endl << "*****************************************" << endl;
    cout << "The inorder traversal of tree1 is:" << endl;
    tree1.inorderTraversal(print);
    cout << endl <<"The preorder traversal of tree1 is:" << endl;
    tree1.preorderTraversal(print);
    cout << endl <<"The postorder traversal of tree1 is:" << endl;
    tree1.postorderTraversal(print);
    
    cout << endl << endl << "The inorder traversal of tree2 is:" << endl;
    tree2.inorderTraversal(print);
    cout << endl <<"The preorder traversal of tree2 is:" << endl;
    tree2.preorderTraversal(print);
    cout << endl << "The postorder traversal of tree2 is:" << endl;
    tree2.postorderTraversal(print);
    
    cout << endl << "*****************************************" << endl;
    cout << "The height of tree1 is:" << tree1.treeHeight() << endl << endl;
    cout <<"The height of tree2 is:" << tree2.treeHeight() << endl;
    
    cout << "*****************************************" << endl;
    cout << "The number of nodes in tree1 is:" << tree1.treeNodeCount() << endl << endl;
    cout << "The number of leaves in tree1 is:" << tree1.treeLeavesCount() << endl;
    
    cout << "*****************************************" << endl;
    cout << "The number of nodes in tree2 is:" << tree2.treeNodeCount() << endl << endl;
    cout << "The number of leaves in tree2 is:" << tree2.treeLeavesCount() <<endl;
    cout << "*****************************************" << endl;
    
    cout << "*****************************************" << endl;
    cout << "Tree1 is:" << endl;
    tree1.rnl_inorderTraversal(printTree);
    cout << endl << "Tree2 is:" << endl;
    tree2.rnl_inorderTraversal(printTree);
	cout << "*****************************************" << endl;
    
}

//Purpose: pirnt function is passed into function as parameter to print data on screen
//Pre-condition: data has been insert into AVL tree
//post-condition: data was printed out on screen
void print(int& x)
{
     cout << x << " ";                                   
}

//Purpose: pirntTree function is passed into function as parameter to print data on screen
//Pre-condition: data has been insert into AVL tree
//post-condition: data was printed out on screen
void printTree(int& y, int myLevel)
{
     for(int i=1; i <= myLevel; i++)
     {
         cout<< "  " ;
     }
     
     cout << myLevel << ": " << y << endl;
     
}
