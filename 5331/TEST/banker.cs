//********************************************************************
//
// Yuzhe Wei
// Operating Systems
// Programming Project #4: Banker's Algorithm
// Nov 23, 2010
// Instructor: Dr. Michael C. Scherger
//
//********************************************************************
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace ConsoleApplication1
{
    public struct InputInfo     //struct store info from file 
    {
        public int process_num;
        public int resource_num;
        public int[] res_vec;
        public int[] avil_vec;
        public int[,] claim_Mrx;
        public int[,] allo_Mrx;
        public int pro_num;
        public int[] req_vec;
        public int[,] needMrx;
    }

    class Program
    {
        static void Main(string[] args)
        {
            string fileName;
            fileName = Console.ReadLine();
            StreamReader sr = File.OpenText(fileName);
            InputInfo Info = new InputInfo();
            readFile(ref sr, ref Info);
            Console.WriteLine("There are {0} processes and {1} resource types in the system.", Info.process_num, Info.resource_num);
            Console.WriteLine();
            Console.WriteLine("The resource Vector is ...");
            displayInfo(Info);
            Console.WriteLine();
            if (testState(Info))
            {
                Console.WriteLine("THE SYSTEM IS IN A SAFE STATE");
                allocRes(ref Info);
            }
            else
                Console.WriteLine("THE SYSTEM IS NOT IN A SAFE STATE");
                
            sr.Close(); //close reader
            
            Console.ReadKey();
        }

        //********************************************************************
        //
        // Read File Function
        //
        // This function read numbers from file and store them in the struct 
        // 
        //
        // Return Value
        // ------------
        // None
        //
        // Reference Parameters
        // --------------------
        // sr     StreamReader              Reader
        // Info   Inputinfo                 Struct hold file information
        // Local Variables
        // ---------------
        // temp		string	           temporary stroe one line in the file
        // m	    string		       temporary store one character
        //
        //*******************************************************************

        public static void readFile(ref StreamReader sr, ref InputInfo Info)
        {
            string temp;
            //read number of processes and resources
            temp = sr.ReadLine();
            string m;
            m = temp[0].ToString();
            Info.process_num = Int32.Parse(m);
            m = temp[2].ToString();
            Info.resource_num = Int32.Parse(m);

            int r = Convert.ToInt32(Info.resource_num);
            int p = Convert.ToInt32(Info.process_num);
            Info.res_vec = new int[r];
            Info.avil_vec = new int[r];
            Info.claim_Mrx = new int[p, r];
            Info.allo_Mrx = new int[p, r];
            Info.req_vec = new int[r];
            Info.needMrx = new int[p, r];


            //read 1*M resource  vector
            sr.ReadLine();
            temp = sr.ReadLine();
            temp = temp.Replace(" ", ""); //take out space from string

            for (int i = 0; i < temp.Length; i++)
            {
                int intTemp = Convert.ToInt32(temp[i]) - 48;
                Info.res_vec[i] = intTemp;

            }

            //read 1*M abaiable vector 
            sr.ReadLine();
            temp = sr.ReadLine();

            temp = temp.Replace(" ", ""); //take out space from string

            for (int i = 0; i < temp.Length; i++)
            {
                int intTemp = Convert.ToInt32(temp[i]) - 48;
                Info.avil_vec[i] = intTemp;

            }

            //read N*M claim Matrix       

            sr.ReadLine();
            for (int i = 0; i < p; i++)
            {
                temp = sr.ReadLine();
                temp = temp.Replace(" ", "");

                for (int j = 0; j < r; j++)
                {
                    int intTemp = Convert.ToInt32(temp[j]) - 48;
                    Info.claim_Mrx[i, j] = intTemp;
                }
            }

            //read a N*M allocation vector
            sr.ReadLine();
            for (int i = 0; i < p; i++)
            {
                temp = sr.ReadLine();
                temp = temp.Replace(" ", "");

                for (int j = 0; j < r; j++)
                {
                    int intTemp = Convert.ToInt32(temp[j]) - 48;
                    Info.allo_Mrx[i, j] = intTemp;
                }

            }

            //read i: 1*m request vector
            sr.ReadLine();
            temp = sr.ReadLine();

            Info.pro_num = temp[0] - 48;

            temp = temp.Replace(" ", "");
            temp = temp.Replace(":", "");


            for (int i = 1; i < temp.Length; i++)
            {
                int intTemp = Convert.ToInt32(temp[i]) - 48;
                Info.req_vec[i - 1] = intTemp;

            }

            //need matrix
            for (int i = 0; i < p; i++)
            {
                for (int j = 0; j < r; j++)
                {
                    Info.needMrx[i, j] = Info.claim_Mrx[i, j] - Info.allo_Mrx[i, j];
                }

            }

        }

        public static void displayInfo(InputInfo Info)
        {
            int r = Info.resource_num;
            char A = 'A';
           

            Console.Write("   ");
            for (int i = 0; i < r; i++)
            {
                Console.Write(A++);
                Console.Write(" ");
            }

            Console.WriteLine();
            Console.Write("   ");
            for (int i = 0; i < r; i++)
            {
                Console.Write(Info.res_vec[i]);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.WriteLine();
            //display avialable matrix
            Console.WriteLine("The resource Available Matrix is ...");
            Console.Write("   ");
            A = 'A';
            for (int i = 0; i < r; i++)
            {
                Console.Write(A++);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.Write("   ");
            for (int i = 0; i < r; i++)
            {
                Console.Write(Info.avil_vec[i]);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.WriteLine();
            //display claim matrix
            Console.WriteLine("The Claim Matrix is ...");
            Console.Write("   ");
            A = 'A';
            for (int i = 0; i < r; i++)
            {
                Console.Write(A++);
                Console.Write(" ");
            }
            Console.WriteLine();
            for (int i = 0; i < Info.process_num; i++)
            {
                Console.Write("{0}: ", i);

                for (int j = 0; j < r; j++)
                {

                    Console.Write(Info.claim_Mrx[i, j]);
                    Console.Write(" ");
                }
                Console.WriteLine();
            }


            Console.WriteLine();
            //display allocation matrix
            Console.WriteLine("The Allocation Matrix is ...");
            Console.Write("   ");
            A = 'A';
            for (int i = 0; i < r; i++)
            {
                Console.Write(A++);
                Console.Write(" ");
            }
            Console.WriteLine();
            for (int i = 0; i < Info.process_num; i++)
            {
                Console.Write("{0}: ", i);

                for (int j = 0; j < r; j++)
                {

                    Console.Write(Info.allo_Mrx[i, j]);
                    Console.Write(" ");
                }
                Console.WriteLine();
            }


            Console.WriteLine();

            //display need matrix
            Console.WriteLine("The Need Matrix is ...");
            Console.Write("   ");
            A = 'A';
            for (int i = 0; i < r; i++)
            {
                Console.Write(A++);
                Console.Write(" ");
            }
            Console.WriteLine();
            for (int i = 0; i < Info.process_num; i++)
            {
                Console.Write("{0}: ", i);

                for (int j = 0; j < r; j++)
                {

                    Console.Write(Info.needMrx[i, j]);
                    Console.Write(" ");
                }
                Console.WriteLine();
            }
        }

        //********************************************************************
        //
        // Test State Function
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
        // Info  	  InputInfo	        struct stored information of file
        //
        // Local Variables
        // ---------------
        // state		 bool		    the return value
        // process_count int            process counter
        // temp          int[]          hold one safe state process array
        //*******************************************************************
        public static bool testState(InputInfo Info)
        {
            bool state = false;
            bool[] finalState = new bool[Info.process_num];
            int process_count = 0;
            int[] temp = new int[Info.process_num];

            for (int i = 0; i < Info.resource_num; i++)
            {
                temp[i] = Info.avil_vec[i];
            }

            for (int i = 0; i < Info.process_num; i++)
            {
                finalState[i] = false;
            }

            for (int a = 0; a < Info.process_num; a++)
            {
                for (int i = 0; i < Info.process_num; i++)
                {
                    for (int j = 0; j < Info.resource_num; j++)
                    {
                        if (Info.needMrx[i, j] <= temp[j] && finalState[i] == false)
                            process_count++;

                        if (process_count == Info.resource_num)
                        {
                            finalState[i] = true;
                            for (int k = 0; k < Info.resource_num; k++)
                            {
                                temp[k] = temp[k] + Info.allo_Mrx[i, k];
                            }
                        }
                    }
                    process_count = 0;//reset process counter
                }
            }
            //check state
            for (int i = 0; i < Info.process_num; i++)
            {
                if (finalState[i] == true)
                    state = true;
                else
                    return false;
            }
            return state;

        }


        //********************************************************************
        //
        // Allocation Resource Function
        //
        // This function test is the new require vector is acceptable, if is
        // display new state after accept vecotr, otherwise, display not granted 
        //
        // Return Value
        // ------------
        // None                       
        //
        // Reference Parameters
        // --------------------
        // Info     InputInfo             struct stored information of file
        //
        // Local Variables
        // ---------------
        // A		char	 format for display: different resource
        //
        //*******************************************************************
        public static void allocRes(ref InputInfo Info)
        {
           
            char A;
            Console.WriteLine();
            Console.WriteLine("The request vector is ...");
            Console.Write("   ");
            A = 'A';
            for (int i = 0; i < Info.resource_num; i++)
            {
                Console.Write(A++);
                Console.Write(" ");
            }
            Console.WriteLine();
            Console.Write("{0}: ",Info.pro_num);
            for (int i = 0; i < Info.resource_num; i++)
            {
                Console.Write(Info.req_vec[i]);
                Console.Write(" ");
            }
            Console.WriteLine();
        
            for(int i = 0; i< Info.resource_num;i++)
                Info.avil_vec[i] = Info.avil_vec[i]-Info.req_vec[i];

            for (int i = 0; i < Info.resource_num; i++)
                Info.allo_Mrx[Info.pro_num, i] = Info.allo_Mrx[Info.pro_num, i]+Info.req_vec[i];

            for (int i = 0; i < Info.process_num; i++)
            {
                for (int j = 0; j < Info.resource_num; j++)
                {
                    Info.needMrx[i, j] = Info.claim_Mrx[i, j] - Info.allo_Mrx[i, j];
                }

            }
            
            if (testState(Info))
            {
                Console.WriteLine("THE REQUEST CAN BE GRANTED: NEW STATE FOLLOWS");
                displayInfo(Info);
            }
            else
            {
                Console.WriteLine("THE REQUEST CANNOT BE GRANTED");
                            
            }
        }

    }
   
}









