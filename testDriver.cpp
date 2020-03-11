/*
Filname: testDriver.cpp
Author : Shafi Gilanizadeh
Due    : 02/26/2020
Purpose: The purpose of the test driver is to allow the user to enter the input and output file names, the information from the input file will be imported
		 to the program and using the class chunklist instances the operations will be performed. the test driver controls all the comments asswell as the opening 
		 and closing the text files.
*/
#include "ChunkList.h"
#include<fstream>
#include <iostream>
using namespace std;

int main()
{
	ChunkList<int> classObject;									// we assume the user inputs integers to the chunklist


	// Creating objects to read and write text files
	ifstream readfile;
	ofstream printfile;

	int choice, userInput=0;
	string Label;
	string command;
	string infilName;	// variable to hold in put file name 
	string outfileName; // variable to hold output file name

	cout << "Enter name of input command file  : ";
	cin >> infilName;
	readfile.open(infilName.c_str());							// open the input file to read data
	
	string Name;
	cout << "Name of the textfile for output.  : ";
	cin >> Name;
	printfile.open(Name.c_str());							   // open the output file to print data to the file

	cout << "Enter name of the test run : ";
	cin >> Label;											   // enter the test run number
	printfile << "\n\t\tWelcome to test run : " << Label << " \n";
	printfile << "\t\t=======================\n\n";
	
	readfile >> command;										// read the first command
	cout << "Data is outputed in the output file  : " << Name << ".txt" << endl;
	
	while (command != "Quit")								// Read all commands until its not Quit
	{
		if (command == "Append")
		{
			readfile >> userInput;				
			//classObject.Append(userInput);
			classObject + userInput;						// append the elements in the list			
		}
		else if (command == "Print")
		{
			printfile << "Printing.....\n\n";
			try
			{
				classObject.Print(printfile);
			}
			catch (EmptyListError err)
			{
				cerr << "There is nothing to print " << endl;
				printfile << "There is nothing to print " << endl;
			}
		}
		else if (command == "Getlengt")
		{
			try
			{
				printfile << "\nTotal number of elments in the chunklist : " << classObject.GetLength() << "\n\n";
			}
			catch(EmptyListError err)
			{
				printfile << "chunkList is empty.... " << endl;
			}
		}
		else if (command == "Getindex")
		{
			int itemAt;
			readfile >> itemAt;
			try
			{
				printfile << "Item found at location " << itemAt << " : [" << classObject.GetIndex(itemAt) << "] " << endl;
			}
			catch (EmptyListError error)
			{
				cerr << "The list is empty..." << endl;
				printfile << "The list is empty..." << endl;
			}
		}
		else if (command == "Isempty")
		{
			try
			{
				printfile << "The ChunkList is  : " << classObject.IsEmpty() << "\n\n";
			}
			catch (EmptyListError err)
			{
				cout << "List is empty" << endl;
				printfile << "List is Empty" << endl;
			}
		}
		else if (command == "Remove")
		{
			readfile >> userInput;
			printfile << "Removing elemen [" << userInput << "]  From the chunklist ....\n\n";
			try
			{
				classObject.Remove(userInput);
			}
			catch (wrongelement err)
			{
				printfile << "The element is not in the chunklist " << endl;
			}
		}
		else if (command == "Quit")
		{
			printfile << "End of the program " << endl;
			printfile.close();			// close the input and output files when your done
			readfile.close();
			break;			    
		}
		else
		{
			printfile  << " Command is not recognized......  " << endl;
		}
		readfile >> command;
	}

}
