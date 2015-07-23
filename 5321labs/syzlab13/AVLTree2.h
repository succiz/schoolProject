//NAME:        Shuyi Zhao
//COURSE:      COSC 2437/5321
//Lab #13:     AVL Trees ¨C Part 2
//ASSIGNED:    Apr 12, 2011
//DUE:         Apr 19, 2011
//OBJECTIVE:   Modify the AVL tree in the previous lab to include 
//             passing functions as parameters
//             printing the tree hierarchically



#ifndef H_AVLTree
#define H_AVLTree
#include <iostream>

using namespace std;

//Definition of the node
template<class elemType>
struct AVLNode
{
   elemType   info;
   int     bfactor;           // balance factor
   AVLNode<elemType> *llink;
   AVLNode<elemType> *rlink;
};


template <class elemType>
class AVLTreeType
{
public:
    void inorderTraversal(void (*visit)(elemType&) ) const;
      //Function to do an inorder traversal of the binary tree.
    void preorderTraversal(void (*visit)(elemType&) ) const;
      //Function to do a preorder traversal of the binary tree.
    void postorderTraversal(void (*visit)(elemType&) ) const;
      //Function to do a postorder traversal of the binary tree.

    int treeHeight() const;
      //Returns the height of the binary tree.
    int treeNodeCount() const;
      //Returns the number of nodes in the binary tree.
    int treeLeavesCount() const;
      //Returns the number of leaves in the binary tree.
    void destroyTree();
      //Deallocates the memory space occupied by the binary tree.
      //Postcondition: root = NULL;

    //functions for AVL tree
	void insert(const elemType &newItem);
	  //insert the elements for the tree
	
	void rnl_inorderTraversal(void (*visit)(elemType&,int));
	  //print the data hierarchially for the binary tree
    
	
	AVLTreeType();   
	 //default constructor; set root to NULL //destructor?


private:
	AVLNode<elemType>* root;

    //binaryTree.h file

    void destroy(AVLNode<elemType>* &p);
      //Function to destroy the binary tree to which p points. 
      //Postcondition: p = NULL

    void inorder(AVLNode<elemType> *p, void (*visit)(elemType&) ) const;
      //Function to do an inorder traversal of the binary
      //tree to which p points.  
    void preorder(AVLNode<elemType> *p, void (*visit)(elemType&) ) const;
      //Function to do a preorder traversal of the binary
      //tree to which p points.  
    void postorder(AVLNode<elemType> *p, void (*visit)(elemType&) ) const;
      //Function to do a postorder traversal of the binary
      //tree to which p points.  

    int height(AVLNode<elemType> *p) const;
      //Function to return the height of the binary tree
      //to which p points. 
    int max(int x, int y) const;
      //Returns the larger of x and y.
    int nodeCount(AVLNode<elemType> *p) const;
      //Function to return the number of nodes in the binary 
      //tree to which p points 
    int leavesCount(AVLNode<elemType> *p) const;
      //Function to return the number of leaves in the binary 
      //tree to which p points 

	//functions for AVLtree
	void rotateToLeft(AVLNode<elemType>* &root);
	  //Function to implement the left rotations of a node. 
      //The pointer of the node requiring the rotation is passed 
      //as a parameter to the function.
	
    void rotateToRight(AVLNode<elemType>* &root);
     //Function to implement the right rotations of a node. 
      //The pointer of the node requiring the rotation is passed 
      //as a parameter to the function.
    
    void balanceFromLeft(AVLNode<elemType>* &root);
     //Founction to reconstruct the tree at a particular node. 
     //use the function rotateToLeft to reconstruct the tree, 
     //and also adjust the balance factors of the nodes affected by the reconstruction
    
	void balanceFromRight(AVLNode<elemType>* &root);
	 //Founction reconstruct the tree at a particular node. 
     //use the function rotateToRight to reconstruct the tree, 
     //and also adjust the balance factors of the nodes affected by the reconstruction
	
    void insertIntoAVL(AVLNode<elemType>* &root,  
		               AVLNode<elemType>  *newNode,  
					   bool& isTaller);
     //Function to inserts a new item into an AVL tree. The item to be 
     //inserted and the pointer of the root node of the AVL tree are passed 
     //as parametes. The insertIntoAVL function is a recursive function.
     
    void rnl_inorder(AVLNode<elemType> *p, void (*visit)(elemType&,int), int mylevel);
     ////print the data hierarchially


};

//Definition of member functions

template <class elemType>
AVLTreeType<elemType>::AVLTreeType()
{
    root = NULL;
}

template <class elemType>
void AVLTreeType<elemType>::inorderTraversal(void (*visit)(elemType&) ) const
{
    inorder(root, *visit);
}

template <class elemType>
void AVLTreeType<elemType>::preorderTraversal(void (*visit)(elemType&) ) const
{
    preorder(root, *visit);
}

template <class elemType>
void AVLTreeType<elemType>::postorderTraversal(void (*visit)(elemType&) ) const
{
    postorder(root, *visit);
}

template <class elemType>
int AVLTreeType<elemType>::treeHeight() const
{
    return height(root);
}

template <class elemType>
int AVLTreeType<elemType>::treeNodeCount() const
{
    return nodeCount(root);
}

template <class elemType>
int AVLTreeType<elemType>::treeLeavesCount() const
{
    return leavesCount(root);
}

template <class elemType>
void AVLTreeType<elemType>::rnl_inorderTraversal(void (*visit)(elemType&,int))
{
     int myLevel=0;
     rnl_inorder(root, *visit, myLevel);
}

template<class elemType>
void AVLTreeType<elemType>::insert(const elemType &newItem)
{    
     bool isTaller = false;
     AVLNode<elemType>  *newNode;

     newNode = new AVLNode<elemType>;
     newNode->info = newItem;
     newNode->bfactor = 0;
     newNode->llink = NULL;
     newNode->rlink = NULL;

     insertIntoAVL(root, newNode, isTaller);
}//end insert

template <class elemType>
void AVLTreeType<elemType>::inorder(AVLNode<elemType> *p, void (*visit)(elemType&)) const
{
    if (p != NULL)
    {
        inorder(p->llink, *visit);
        (*visit)(p->info);
        inorder(p->rlink, *visit);
    }
}

template <class elemType>
void AVLTreeType<elemType>::preorder(AVLNode<elemType> *p, void (*visit)(elemType&)) const
{
	if (p != NULL)
	{
		(*visit)(p->info);
		preorder(p->llink, *visit);
		preorder(p->rlink, *visit);
	}
}

template <class elemType>
void AVLTreeType<elemType>::postorder(AVLNode<elemType> *p, void (*visit)(elemType&)) const
{
    if (p != NULL)
    {
        postorder(p->llink, *visit);
        postorder(p->rlink, *visit);
        (*visit)(p->info);
    }		
}

template <class elemType>
void  AVLTreeType<elemType>::destroy(AVLNode<elemType>* &p)
{
    if (p != NULL)
    {
        destroy(p->llink);
        destroy(p->rlink);
        delete p;
        p = NULL;
    }
}

template <class elemType>
void  AVLTreeType<elemType>::destroyTree()
{
    destroy(root);
}



template <class elemType>
int AVLTreeType<elemType>::height(AVLNode<elemType> *p) const
{
    if (p == NULL)
        return 0;
    else
        return 1 + max(height(p->llink), height(p->rlink));
}

template <class elemType>
int AVLTreeType<elemType>::max(int x, int y) const
{
    if (x >= y)
        return x;
    else
        return y;
}


template <class elemType>
int AVLTreeType<elemType>::nodeCount(AVLNode<elemType> *p) const
{
    if(p == NULL)
        return 0;
    else
        return 1+nodeCount(p->llink)+nodeCount(p->rlink);
}


template <class elemType>
int AVLTreeType<elemType>::leavesCount(AVLNode<elemType> *p) const
{
    if(p == NULL)
        return 0;
    else
    {
        if((p->llink == NULL) && (p->rlink == NULL))
            return 1;
        else
            return leavesCount(p->llink)+leavesCount(p->rlink);
    }
}

template<class elemType>
void AVLTreeType<elemType>::rotateToLeft(AVLNode<elemType>* &root)
{
     AVLNode<elemType> *p; //pointer to the root of the
                           //right subtree of root
     if(root == NULL)
        cerr<<"Error in the tree."<<endl;
     else
        if(root->rlink == NULL)
           cerr<<"Error in the tree:"
               <<" No right subtree to rotate."<<endl;
        else
        {   p = root->rlink;
            root->rlink = p->llink; //the left subtree of p 
                             //becomes the right subtree of root
            p->llink = root; 
            root = p;	//make p the new root node
        }
}//end rotateLeft

template<class elemType>
void AVLTreeType<elemType>::rotateToRight(AVLNode<elemType>* &root)
{
     AVLNode<elemType> *p;  //pointer to the root of	
                            //the left subtree of root

     if(root == NULL)
        cerr<<"Error in the tree."<<endl;
     else
        if(root->llink == NULL)
           cerr<<"Error in the tree:"
               <<" No left subtree to rotate."<<endl;
        else
        {  p = root->llink;
           root->llink = p->rlink; //the right subtree of p 
                           //becomes the left subtree of root
           p->rlink = root; 
           root = p;	//make p the new root node
        }
}//end rotateRight

template<class elemType>
void AVLTreeType<elemType>::balanceFromLeft(AVLNode<elemType>* &root)
{
     AVLNode<elemType> *p;    //child of root
     AVLNode<elemType> *w;    //grandchild of root

     p = root->llink;   //p points to the left subtree of root

     switch(p->bfactor)
     {
     case -1: root->bfactor = 0;
              p->bfactor = 0;
              rotateToRight(root);     //final rotation to right at root
              break;
     case 0:  cerr<<"Error: Cannot balance from the left."<<endl;
              break;
     case 1:  w = p->rlink;
              switch(w->bfactor)  //adjust the balance factors
              {
              case -1: root->bfactor = 1;
                       p->bfactor = 0;
                       break;
              case 0:  root->bfactor = 0;
                       p->bfactor = 0;
                       break; 
              case 1:  root->bfactor = 0;
                       p->bfactor = -1;
              }//end switch

              w->bfactor = 0;	
              rotateToLeft(p);        //double rotation
              root->llink = p;
              rotateToRight(root);    //final rotation to right at root
     }//end switch;
}//end balanceFromLeft

template<class elemType>
void AVLTreeType<elemType>::balanceFromRight(AVLNode<elemType>* &root)
{
     AVLNode<elemType> *p;       //child of root
     AVLNode<elemType> *w;       //grandchild of root

     p = root->rlink;   //p points to the right subtree of root

     switch(p->bfactor)
     {
     case -1: w = p->llink;
              switch(w->bfactor)  //adjust the balance factors
              {
              case -1: root->bfactor = 0;
                       p->bfactor = 1;
                       break;
              case 0:  root->bfactor = 0;
                       p->bfactor = 0;
                       break;		
              case 1:  root->bfactor = -1;
                       p->bfactor = 0;
              }//end switch

              w->bfactor = 0;	
              rotateToRight(p);        //double rotation
              root->rlink = p;
              rotateToLeft(root);      //final rotation to left at root
              break;
     case 0:  cerr<<"Error: Cannot balance from the right."<<endl;
              break;
     case 1:  root->bfactor = 0;
              p->bfactor = 0;
              rotateToLeft(root);      //final rotation to left at root
     }//end switch;
}//end balanceFromRight

template<class elemType>
void AVLTreeType<elemType>::insertIntoAVL(AVLNode<elemType>* &root, 
			   AVLNode<elemType> *newNode, bool& isTaller)
{
    if(root == NULL)
    {
       root = newNode;
       isTaller = true;
    }
    else
       if(root->info == newNode->info)
          cerr<<"No duplicates are allowed."<<endl;
       else
          if(root->info > newNode->info) //newItem goes in 
                                         //the left subtree
          {
             insertIntoAVL(root->llink, newNode, isTaller);

             if(isTaller)             //after insertion, the 
                                      //subtree grew in height
                switch(root->bfactor)
                {
                case -1: balanceFromLeft(root);
                         isTaller = false;
                         break;
                case 0:  root->bfactor = -1;
                         isTaller = true;
                         break;
                case 1:  root->bfactor = 0;
                         isTaller = false;
                }//end switch
          }//end if
          else                     //newNode goes in the right subtree
          {
             insertIntoAVL(root->rlink, newNode, isTaller);

             if(isTaller)              //after insertion, the 
                                       //subtree grew in height
                switch(root->bfactor)
                {
                case -1: root->bfactor = 0;
                         isTaller = false;
                         break;
                case 0:  root->bfactor = 1;
                         isTaller = true;
                         break;
                case 1:  balanceFromRight(root);
                         isTaller = false;
                }//end switch
          }//end else
}//end insertIntoAVL

template<class elemType>
void AVLTreeType<elemType>::rnl_inorder(AVLNode<elemType> *p, void (*visit)(elemType&,int), int myLevel)
{
	 if (p != NULL)
	 {
		rnl_inorder(p->rlink, *visit, myLevel+1);
		(*visit)(p->info, myLevel);
		rnl_inorder(p->llink, *visit, myLevel+1);
	 }
}

#endif
