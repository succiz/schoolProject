//*********************************************************
//
// Shuyi Zhao
// Operating Systems
// Project #4: Implementation of Banker's Algorithm
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
void foundNeed(int** claimM, int** availableM, int** needM, int n, int m);
bool isSafeState(int n, int m, int* available, int** needM);
bool isRequestGranted(int* requestV, int availableV, int** needM, int** allocationM);

int main(int argc, char* argv[])
{
    ifstream myInFile;
    string fileName;
        
    int n=0;//number of processes
    int m=0;//number of resource types
    int* resourceV=new int[m];
    int* avaliableV=new int[m];
    int* requestV=new int[m+1];
    int** claimM=new int*[n];
    for(int i=0; i<n; i++)
        claimM[i]=int[m];
    int** allocationM=new int*[n];
    for(int i=0; i<n, i++)
        allocationM[i]=int[m]; 
    int** needM=new int*[n];
    for(int i = 0; i<n, i++)
        needM[i]=int[m];
    fileName=argv[1];
    
    myInFile=argv[1];
    myInfile.open(fileName);
    
    insertNum(n, m, myInFile);
    insertV(resourceV, m, myInFile);
    insertV(avaliableV, m, myInFIle);
    insertM(clainM, n, m, myInFile);
    insertM(allocationM, n, m, myInFile);
    insertReq(requestV, m, myInFile);
    
    displayNum(n, m);
    displayV(resourceV, m);
    displayV(availabeV, m);
    displayM(claimM, n, m);
    displayM(allocationM, n, m);
    
    foundNeed(claimM, availableM, needM, n, m);
    displayM(needM, n, m);
    
    if(isSafeState(n, m, available, needM))
        {
            cout << "THE SYSTEM IS IN A SAFE STATE" << endl;
            displayReq();
            if(isRequestGranted(requestV, availableV, needM, allocationM))
            {
                if(isSafeState(n, m, available, needM))
                {
                    cout << "THE REQUEST CAN BE GRANTED: NEW STATE FOLLOWS" <<endl;
                    displayV(resourceV, m);
                    displayV(availabeV, m);
                    displayM(claimM, n, m);
                    displayM(allocationM, n, m);
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
    
    return 0;
}

void insertNum(int& n, int& m, ifstream& myInFile)
{
    myInFile >> n;
    myInFile >> m;
}

void insertV(int* array, int m, ifstream& myInFile)
{
    for(int i=0; i<m; i++)
        myInFile >> array[i];  
}

void insertReq(int* requestV, int m, ifstream& myInFile)
{
    char opr;
    myInFile >> requestV[0];
    myInFile >> opr;
    for(int i=1; i<m+1; i++)
        myInFile >> requestV[i];  
}

void insertM(int** array, int n, int m, ifstream& myInFile)
{
     for(int i=0; i<n; i++)
         for(int j=0; j<m; j++)
             myInFile >> array[i][j];  
}

void displayNum(int n, int m)
{
    cout << "There are " << n << " processes and " << m << " resource types in the system." << endl;
}

void displayV(int* array, int m)
{
     for(char a=16; a<16+m; a++ )
         cout << setw(2) << a;
     cout << endl;
     for(int i=0; i<m; i++)
         cout << setw(2) << array[i];
}


void displayM(int** array, int n, int m)
{
     cout << "  ";
     for(char a=16; a<16+m; a++ )
         cout << setw(2) << a;
     cout << endl;
     for(int i=0; i<n; i++)
     {
         cout << i << ":";
         for(int j=0; j<m; j++)
             cout << setw(2) << array[i][j];
     }
}

void foundNeed(int** claimM, int* availableM, int** needM, int n, int m)
{
     for(int i=0; i<n; i++)
         for(int j=0; j<m; j++)
             needM[i][j]=claimM[i][j] - availableM[j];
}

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
    bool changedFinish=false;
    do
    {
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
    while(changedFinish); 
    
    for(int d=0; d<n; d++)
    {
        if(Finish[d] == false)
            return false;
    }
    return true;
}

bool isRequestGranted(int* requestV, int availableV, int** needM, int** allocationM, int m)
{
    int processNum=requestV[0];
    cout << "The Request Vector is..." << endl;
    cout << "  ";
    for(char c=16; c<16+m; c++ )
        cout << setw(2) << c;
    cout << endl;
    cout << requestV[0] << ":" <<endl;
    for(int b=1; b<m+1; b++)
        cout << setw(2) << requestV[b];
    cout << endl;
    
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
