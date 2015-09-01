/**
-----------------------------------------
-----------------------------------------
A program implementing Dijstras Algorithm
in order to find the shortest flight path
between two cities
Author: Christian Davidson
Date: November 5th 2011
-----------------------------------------
-----------------------------------------
*/

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <cmath>
using namespace std;

struct city
{
        string name;
        double longi;
        double lat;
	double key;
	double dist;
	int parentIndex;
        city(string tempname = "", double templong = 0, double templat = 0)
        {
                name = tempname;
                longi = templong;
                lat = templat;
		key = 0;
		dist = 0;
		parentIndex = -1;
        }

};


int main (int argc, const char * argv[])
{

//Reading in various
//user information
	string kill;
        cout << "What is the name of the cities file?" << endl;
        string input;
        cin >> input;
	cout << "What is the radius for connecting cities?" << endl;
	double radius;
	cin >> radius;
	cout << "What is the name of the starting city?" << endl;
	string startCity;
	getline(cin, kill);
	getline(cin, startCity);
	cout << "What is the name of the destination city?" << endl;
	string destCity;
	getline(cin, destCity);
//Initializing
//variables

        fstream inFile(input.c_str());
        char tempChar;
        string tempString = "";
        string structString = "";
        double structLong = 0;
        double structLat = 0;
        int index = 0;
        city cityArray[1000];
        if (!inFile)
        {
                cout << "Unable to open file.";
                exit(1);
        }  
        while(inFile.peek() != EOF)
        {
//Getting
//the String
//for city
                tempChar = inFile.get();
                while(tempChar != '\t')
                {
                        tempString += tempChar;
                        tempChar = inFile.get();
                }
                structString = tempString;
                tempString = "";
//Getting
//the Longitude
                tempChar = inFile.get();
                while(tempChar != '\t') 
                {
                        tempString += tempChar;
                        tempChar = inFile.get();
                }
                std::istringstream stm;
                stm.str(tempString);
                stm >> structLong;
//Getting
//the Latitude
                tempString = "";
                tempChar = inFile.get();
                while(tempChar != '\n')
                {
                        tempString += tempChar;
                        tempChar = inFile.get();
                }
                stm.clear();  
                stm.str(tempString);
                stm >> structLat;
//Creating the
//city structure
//and putting it
//in an array
                
                cityArray[index] = city(structString, structLong, structLat);
                index++;
                tempString = "";
        }   
        inFile.close();


//Creating an adjacency matrix
//with distance values between cities
                
        double distArray[index][index];
        for(int j = 0; j < index; j++)
        {
                city tempCity1 = cityArray[j];  
                for(int i = 0; i < index; i++)
                {
                        city tempCity2 = cityArray[i];
                        distArray[j][i] = sqrt(pow(cityArray[i].longi - cityArray[j].longi, 2) + pow(cityArray[i].lat - cityArray[j].lat, 2));
			if(distArray[j][i] > radius)
				distArray[j][i] = 0;
                }
        }

//Creating and initializing an adjacency matrix
//to hold key values
                 
        int AdjMatrix[index][index];
        for(int j = 0; j < index; j++)
        {
                for(int i = 0; i < index; i++)
                        AdjMatrix[j][i] = 0;
        }

	int startIndex = -1;
	int destIndex = -1;
	for(int i = 0; i < index; i++)
	{
		if(startCity == cityArray[i].name)
			startIndex = i;
		if(destCity == cityArray[i].name)
			destIndex = i;
	}
	if(startIndex == -1 || destIndex == -1)
	{
		cout << "Could not find at least one of the cities given.";
		exit(1);
	}


	cityArray[startIndex].key = 1;
	int numEdges = 0;
	double tempDist = 0;
	int tempIndex1 = -1;
	int tempIndex2 = -1;
	while(numEdges < index - 1)
	{
		double min = 9999;
		for(int j = 0; j < index; j++)
		{
			if(cityArray[j].key != 0)
			{
				for(int i = 0; i < index; i++)
				{
					tempDist = cityArray[j].dist + distArray[j][i];
					if(cityArray[i].key == 0 && tempDist < min && distArray[j][i] > 0)
					{
						min = tempDist;
						tempIndex1 = i;
						tempIndex2 = j;
					}
				}
			}
		}
		cityArray[tempIndex1].dist = min;
		distArray[tempIndex2][tempIndex1] = 0;
		distArray[tempIndex2][tempIndex1] = 0;
		AdjMatrix[tempIndex2][tempIndex1] = 1;
		AdjMatrix[tempIndex1][tempIndex2] = 1;
		cityArray[tempIndex1].key = 1;		
		numEdges++;
		cityArray[tempIndex1].parentIndex = tempIndex2;
	}			


	cout << "Shortest Path:" << endl;					
	int tempCity = destIndex;
	int tempCity2 = -1;
	double totalLength = 0;
	while( tempCity != startIndex)
	{

		cout << cityArray[tempCity].name << "(" << cityArray[tempCity].lat << ", " << cityArray[tempCity].longi << ") <- ";
		tempCity2 = tempCity;
		tempCity = cityArray[tempCity].parentIndex;
		totalLength += sqrt(pow(cityArray[tempCity2].longi - cityArray[tempCity].longi, 2) + pow(cityArray[tempCity2].lat - cityArray[tempCity].lat, 2));
	}
        cout << cityArray[tempCity].name << "(" << cityArray[tempCity].lat << ", " << cityArray[tempCity].longi << ")" << endl; 
	cout << "Total path length:" << totalLength;
	
}
