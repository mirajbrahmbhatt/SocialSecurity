//
//  main.cpp
//

//  Copyright © 2016 Miraj Brahmbhatt. All rights reserved.


#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;


int extractMethod(int Element_number) //Extract the certain degits when read the file
{
    string initial ="000000000"; //Social 9 digit number to place under string
    char *valueC= new char[100];
    sprintf(valueC, "%i", Element_number);
    string value = (string) valueC;
    
    int j=0;
    
    //Takes everything in value and converting occurs
    for( int i=0; i<value.size(); i++)
    {
        initial[i] = value[j];
        j++;
    }
    //extract 3,5,7,8 digits from the social
    string final = "0000";
    final[0] = initial[2];
    final[1] = initial[4];
    final[2] = initial[6];
    final[3] = initial[7];
    
    //returns the extraxted digits
    return atoi(final.c_str());
    
}

int quadratic_probe(int Hashtable[], int Index, int max) //max = user input
{
    int pos,i, square;
    //Position is set to the key and finds the remainder of the user_input
    pos=Index%max;
    
    square = 1;
    // if there is a collision then use quad_prob
    for(i=1; i<100000; i++)
    {
        if(Hashtable[pos+(max+i)*(max+i)] == 0) //quad_prob squares the number
        {
            return Index;
        }
    }
    
    return -1;	//table overflow
}


int main()
{
    //Sets the filenames for fileline, nums, data.
    string fileline;
    string nums;
    ifstream Data;
    int User_number = 0;
    
    //Creates a hashtable
    int * hashTable;
    hashTable=new int [100000]; //Dynamic Array size is 100,000
    
    //For every element 'i' less then 100000 then create a hash table
    for (int i = 0; i < 100000; i++)
    {
        hashTable[i] = 0;
    }
    
    //opens the file
    Data.open("everybodys_socials.txt");
    
    //If not open then give a error
    if(!Data.is_open())
    {
        cout << "The file could not be opened. Check the location.\t";
        
    }
    
    vector<int> allNums; //store all the numbers in a vector
    while(Data)
    {
        getline(Data,fileline);
        istringstream ss(fileline);
        while(getline(ss, nums,',')) //excludes the comma
        {
            
            allNums.push_back(atoi(nums.c_str())); //Convert string to integer for allNums
        }
        
        /*
         for (int i = 0; i < allNums.size(); i++) {
         cout << allNums[i] << endl;
         }
         */
        
        //User enters a number
        cout << "Enter a number between 1 and 450 million: ";
        cin >> User_number;
        
        User_number= User_number%100000; //Makes sure it doesnt go over 450 Million
        
        if (User_number < 1 || User_number > 450000000) //Set the conditions between 1-450 million
        {
            //if not give a error
            cout << "The number must be in the range 1 to 450 million.\n";
            cout << "Please Enter another number: ";
            cin >> User_number;
        }
        
        else
        {
            cout << "The Number You Entered is: " << User_number << endl; //Output the number the user_input choose
        }
        
        
        int index;
        for (int i = 0; i < allNums.size(); i++)
        {
            //Hash all the numbers
            index = extractMethod(allNums[i]); //Stores the extracted address of numbers
            
            //If address is aviable then store the number
            if (hashTable[index] == 0) {
                hashTable[index] = allNums[i];
                cout << allNums[i] << ": THERE ARE NO COLLISION" << endl;
            }
            
            else { //if not avaiable then use quad_prob for next space
                index = quadratic_probe(hashTable, index, User_number);
                if (index == -1) {
                    cout << "TABLE FULL" << endl;
                }
                else { //After probing puts the number into next index location
                    hashTable[index] = allNums[i];
                    cout << allNums[i] << ": COLLISION DETECTED: Moved to POSITION " << index << endl;
                }
            }
        }
        
        //Writes the file resutls into 'hashed_socials.txt'
        ofstream out;
        out.open("hashed_socials.txt");
        
        //Writing hashtable files
        for( int i=0; i<100000;i++)
        {
            out << hashTable[i];
            if(i<99999)out << ',';
            
        }
        out.clear();
        out.close();
        
    }
    return 0;
}
