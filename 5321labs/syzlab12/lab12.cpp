//NAME:        Shuyi Zhao
//COURSE:      COSC 2437/5321
//Lab #12:     AVL Trees
//ASSIGNED:    Apr  5, 2011
//DUE:         Apr 12, 2011
//OBJECTIVE:   Create the class AVLTreeType
//             Create two AVL trees and invoke some of the class functions

#include <iostream>
#include <fstream>
#include <iomanip>
#include "AVLTree.h"

using namespace std;

void display(AVLTreeType<int> tree1, AVLTreeType<int> tree2);

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
    
    display(tree1,tree2);
    
    inFile1.close();
    inFile2.close();
 
    return 0;
}

void display(AVLTreeType<int> tree1, AVLTreeType<int> tree2)
{
	cout << endl << "*****************************************" << endl;
    cout << "The inorder traversal of tree1 is:" << endl;
    tree1.inorderTraversal();
    cout << endl <<"The preorder traversal of tree1 is:" << endl;
    tree1.preorderTraversal();
    cout << endl <<"The postorder traversal of tree1 is:" << endl;
    tree1.postorderTraversal();
    
    cout << endl << endl << "The inorder traversal of tree2 is:" << endl;
    tree2.inorderTraversal();
    cout << endl <<"The preorder traversal of tree2 is:" << endl;
    tree2.preorderTraversal();
    cout << endl << "The postorder traversal of tree2 is:" << endl;
    tree2.postorderTraversal();
    
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
}
