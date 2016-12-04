/*=================================================================================================
This program computes the optimal cache partition for two programs running concurrently
==================================================================================================*/
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;
int main()
{
    int cacheSize = 10;        // Maximum cache size
    int A = 0, B = 0;          // Variable to store the cache partition for programs A and B
    double MA[cacheSize];      // Array to hold miss rate average for program A
    double MB[cacheSize];      // Array to hold miss rate average for program B

    int i = 0;

    //Get input data file
    ifstream file("dedup vs swaptions.txt");

    if (file)
    {
        string line;

        // Fill in MA and MB from file
        for(int j = 0; j < cacheSize; j++)
        {
            getline(file, line);
            stringstream sep(line);
            string word;

            getline(sep, word, ',');
            MA[i] = atof(word.c_str());

            getline(sep, word, ',');
            MB[i++] = atof(word.c_str());
        }

        //Partition Cache Iteratively
        for(i = 2; i < cacheSize; i++) // Loop from 2 to cacheSize since we initially allocated 2MB above
        {
            //cout << "comparing: " << (MA[A] - MA[A+1]) << "\t  and  \t\t" << (MB[B] - MB[B+1]) << endl;

            if ( (MA[A] - MA[A+1]) > (MB[B] - MB[B+1]) ) // Find who benefits the most
                A++;
            else
                B++;

        }

        cout << "A is allocated " << A+1 << "MB \t B is allocated " << B+1 << "MB\n"; // Adding 1 since c's index starts from 0
    }
    else
    {
        cout << "ERROR: File failed to open.\n";
    }

    return 0;
}
