//*********************************************************
//
// Shuyi Zhao
// Operating Systems
// Project #4: Implementation of Banker's Algorithm
// April 13, 2011
//
//**********************************************************
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

void insertNum(int& n, int& m, ifstream& myInFile);
void insertV(int* array, int m, ifstream& myInfile);
void insertReq(int* requestV, int m, ifstream& myInFile);
void insertM(int** array, int n, int m, ifstream& myInfile);
void displayNum(int n, int m);
void displayV(int* array, int m);
void displayM(int** array, int n, int m);
void foundNeed(int** claimM, int** allocationM, int** needM, int n, int m);
bool isSafeState(int n, int m, int* available, int** needM);
bool isRequestGranted(int* requestV, int* availableV, int** needM, int** allocationM, int m);

int main(int argc, char* argv[])
{
    ifstream myInFile;
       
    int n;//number of processes
    int m;//number of resource types
    
    //fileName=argv[1];
    myInFile.open(argv[1]); 
    insertNum(n, m, myInFile);

	int* resourceV=new int[m];
    int* availableV=new int[m];
    int* requestV=new int[m+1];
    int** claimM=new int*[n];
    for(int i=0; i<n; i++)
    {
        claimM[i]=new int[m];
    }
    int** allocationM=new int*[n];
    for(int i=0; i<n; i++)
    {
        allocationM[i]=new int[m];
    } 
    int** needM=new int*[n];
    for(int i = 0; i<n; i++)
    {
        needM[i]=new int[m];
    }

    insertV(resourceV, m, myInFile);
    insertV(availableV, m, myInFile);
    insertM(claimM, n, m, myInFile);
    insertM(allocationM, n, m, myInFile);
    insertReq(requestV, m, myInFile);

    
    displayNum(n, m);
    cout << "The Resource Vector is..." << endl;
    displayV(resourceV, m);
    cout << "The Available Vector is..." << endl;
    displayV(availableV, m);
	cout << "The Claim Matrix is..." << endl;
    displayM(claimM, n, m);
	cout << "The Allocation Matrix is..." << endl;
    displayM(allocationM, n, m);
	cout << "The Need Matrix is..." << endl;
    foundNeed(claimM, allocationM, needM, n, m);
    displayM(needM, n, m);
    
    if(isSafeState(n, m, availableV, needM))
    {
		cout << "THE SYSTEM IS IN A SAFE STATE" << endl << endl;
        if(isRequestGranted(requestV, availableV, needM, allocationM, m))
            {
                if(isSafeState(n, m, availableV, needM))
                {
                    cout << "THE REQUEST CAN BE GRANTED: NEW STATE FOLLOWS" <<endl;
					cout << "The Resource Vector is..." << endl;
                    displayV(resourceV, m);
					cout << "The Available Vector is..." << endl;
                    displayV(availableV, m);
					cout << "The Claim Matrix is..." << endl;
                    displayM(claimM, n, m);
					cout << "The Allocation Matrix is..." << endl;
                    displayM(allocationM, n, m);
					cout << "The Need Matrix is..." << endl;
                    displayM(needM, n, m);
                }
                else
                    cout << "THE REQUEST CANNOT BE GRANTED" << endl;
            }
            else
            cout << "THE REQUEST CANNOT BE GRANTED" << endl;    
    }
    else
        cout << "THE SYSTEM IS NOT IN A SAFE STATE" << endl;
    
    
    delete[] resourceV;
    delete[] availableV;
    delete[] requestV;
    for(int i=0;i <n;i++) 
        delete[]   claimM[i]; 
    delete[]   claimM; 
    for(int i=0; i <n; i++) 
        delete[]   allocationM[i]; 
    delete[]   allocationM; 
    for(int i=0; i <n; i++) 
        delete[]   needM[i]; 
    delete[]   needM; 
    
    return 0;
}

//************************************************************
//
// Insert Number Function
//
// This function read the numbers of processes and types from file into parameters 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          n                      the number of processes
// int          m                      the number of types
// ifstream  myInFile                  streamReader
// Local Variables
// ---------------
// NONE
//
//*******************************************************************
void insertNum(int& n, int& m, ifstream& myInFile)
{
    myInFile >> n;
    myInFile >> m;
}

//************************************************************
//
// Insert Vector Function
//
// This function read data from file into array 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          *array                 the pointer point to a array
// int          m                      the number of types
// ifstream  myInFile                  streamReader
// Local Variables
// ---------------
// int          i
//
//*******************************************************************
void insertV(int* array, int m, ifstream& myInFile)
{
    for(int i=0; i<m; i++)
    {
        myInFile >> array[i]; 
    } 
}

//************************************************************
//
// Insert requestVector Function
//
// This function read data from file into request array 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          *requestV              the pointer point to request array
// int          m                      the number of types
// ifstream  myInFile                  streamReader
// Local Variables
// ---------------
// int          i
//
//*******************************************************************
void insertReq(int* requestV, int m, ifstream& myInFile)
{
    char opr;
    myInFile >> requestV[0];
    myInFile >> opr;
    for(int i=1; i<m+1; i++)
        myInFile >> requestV[i];  
}

//************************************************************
//
// Insert Matrix Function
//
// This function read data from file into 2D array 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          **array                the pointer point to a array which stores pointers point to array
// int          n                      the number of processes
// int          m                      the number of types
// ifstream  myInFile                  streamReader
// Local Variables
// ---------------
// int          i
// int          j
//
//*******************************************************************
void insertM(int** array, int n, int m, ifstream& myInFile)
{

     for(int i=0; i<n; i++)
     {
         for(int j=0; j<m; j++)
         {
             myInFile >> array[i][j]; 
         }
     }       
}

//************************************************************
//
// Display Number Function
//
// This function display the numbers of processes and types 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          n                      the number of processes
// int          m                      the number of types
// Local Variables
// ---------------
// NONE
//
//*******************************************************************
void displayNum(int n, int m)
{
    cout << "There are " << n << " processes and " << m << " resource types in the system." << endl << endl;
}

//************************************************************
//
// Display Vector Function
//
// This function display data from a array 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          *array                 the pointer point to a array
// int          m                      the number of types
// Local Variables
// ---------------
// char         a
// int          i
//
//*******************************************************************
void displayV(int* array, int m)
{
     for(char a='A'; a<'A'+m; a++ )
         cout << setw(2) << a;
     cout << endl;
     for(int i=0; i<m; i++)
         cout << setw(2) << array[i];
	 cout << endl << endl;
}

//************************************************************
//
// Display Matrix Function
//
// This function display data from 2D array 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          **array                the pointer point to a array which stores pointers point to array
// int          n                      the number of processes
// int          m                      the number of types
// Local Variables
// ---------------
// char         a
// int          i
// int          j
//
//*******************************************************************
void displayM(int** array, int n, int m)
{
     cout << "  ";
     for(char a='A'; a<'A'+m; a++ )
         cout << setw(2) << a;
     cout << endl;
     for(int i=0; i<n; i++)
     {
         cout << i << ":";
         for(int j=0; j<m; j++)
             cout << setw(2) << array[i][j];
		 cout << endl;
     }
	 cout << endl;
}

//************************************************************
//
// Find need matrix Function
//
// This function read data from claim matrix and allocation matrix to calculate the need matrix 
// 
//
// Return Value
// ------------
// void
//
// Reference Parameters
// --------------------
// int          **claimM               the pointer point to clainM[] which stores pointers point to claimM[][]
// int          **allocationM          the pointer point to allocationM[] which stores pointers point to allocationM[][]
// int          **needM                the pointer point to needM[] which stores pointers point to needM[][]
// int          n                      the number of processes
// int          m                      the number of types
// Local Variables
// ---------------
// int          i
// int          j
//
//*******************************************************************
void foundNeed(int** claimM, int** allocationM, int** needM, int n, int m)
{
     for(int i=0; i<n; i++)
         for(int j=0; j<m; j++)
             needM[i][j]=claimM[i][j] - allocationM[i][j];
	 
}

//********************************************************************
//
// Is Safe State Function
//
// This function test if the state is safe, if is, return true, 
// otherwise, return false.
//
// Return Value
// ------------
// bool                         True/False if state is safe
//
// Value Parameters
// ----------------
// int          *availableV            the pointer point to available array
// int          **needM                the pointer point to needM[] which stores pointers point to needM[][]
// int          n                      the number of processes
// int          m                      the number of types
//
// Local Variables
// ---------------
// int           *workV         the pointer point to work array
// bool          *Finish        the pointer point to finish array which stores the finish state of a process
// bool          changedFinish  hold the state if the process finish state has been changed in a loop
// int           counter        hold the number of elements in needM satisfied the conditions
// int           i
// int           j
// int           a
// int           b
//*******************************************************************
bool isSafeState(int n, int m, int* availableV, int** needM)
{
    //initialize step 1
    int* workV = new int[m];
    for(int i=0; i<m; i++)
        workV[i]=availableV[i];
    bool *Finish = new bool[n];
    for(int j=0; j<n; j++)
        Finish[j]=false;
    int counter;
    //bool safeState;
     
    //step2 step3
    bool changedFinish=true;
    while(changedFinish)
    {
		changedFinish=false;
        for(int a=0; a<n; a++)
        {
            if(Finish[a] == false)
            {
                counter=0;
                for(int b=0; b<m; b++)
                {
                    if(needM[a][b] <= workV[b])
                        counter++;                    
                }
                if(counter == m)
                {
                    for(int c=0; c<m; c++)
                    {
                        workV[c]=workV[c]+availableV[c];
                    }
                    Finish[a]=true;
                    changedFinish=true;
                }//end if(counter==m)                
            }//end if(Finish[a]==false)
        }//end for
    }  
    
    for(int d=0; d<n; d++)
    {
        if(Finish[d] == false)
            return false;
    }
    return true;
}

//********************************************************************
//
// Is Request Granted Function
//
// This function test is the new require vector is acceptable, if is
// display new state after accept vecotr, otherwise, display not granted 
//
// Return Value
// ------------
// bool                       
//
// Reference Parameters
// --------------------
// int          *availableV            the pointer point to available array
// int          **needM                the pointer point to needM[] which stores pointers point to needM[][]
// int          **allocationM          the pointer point to allocationM[] which stores pointers point to allocationM[][]
// int          **needM                the pointer point to needM[] which stores pointers point to needM[][]
// int          m                      the number of types
//
// Local Variables
// ---------------
// int		processNum	               read the requst process number from requestV
// int      a
// int      b
// int      c
//
//*******************************************************************
bool isRequestGranted(int* requestV, int* availableV, int** needM, int** allocationM, int m)
{
    int processNum=requestV[0];
    cout << "The Request Vector is..." << endl;
    cout << "  ";
    for(char c='A'; c<'A'+m; c++ )
        cout << setw(2) << c;
    cout << endl;
    cout << requestV[0] << ":";
    for(int b=1; b<m+1; b++)
        cout << setw(2) << requestV[b];
    cout << endl << endl;
    
    for(int a=0; a<m; a++)
    {
        if(requestV[a+1] <= needM[processNum][a])
        {
            if(requestV[a+1] <= availableV[a])
            {
                availableV[a]=availableV[a]-requestV[a+1];
                allocationM[processNum][a]=allocationM[processNum][a]+requestV[a+1];
                needM[processNum][a]=needM[processNum][a]-requestV[a+1];                
            }
            else
                return false;
        }
        else
            return false;
    } 
}
