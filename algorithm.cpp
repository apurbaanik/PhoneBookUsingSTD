/*
Title: Homework 3.2 Using algorithms from the standard library.
Author: Anik Barua
Version: 1.0
Date: 04-18-2021

Description: Using standard library algorithms to output the information from the "phoneno.txt". It will
print the size of map (where data was read from file), count the numbers of area code with 347, the ID's
of same phone numbers, size of vectors with 212 area code numbers and duplicates removed from the vector. 
*/

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>
using namespace std;

//Boolean function that returns true if the substring equals to the area code of 347
bool IsAreaCode(string s)
{
    return s.substr(0, 3) == "347";
}

//Boolean function that returns true if the string equals to the number 212-536-6331
bool IsNumber(pair<int, string> x)
{
    return x.second == "212-536-6331";
}

//Boolean function that returns true if the substring equals to the area code of 212
bool IsCode(pair<int, string> x)
{
    return (x.second).substr(0, 3) == "212";
}

int main()
{
    try
    {
        ifstream inFile("phoneno.txt"); //inFile object is created to open the phoneno.txt file
        if (!inFile.good())
        {
            throw string("Failure opening the phoneno.txt");
        }

        string line; //line that will read whole line from the document
        int id;
        string number;
        map<int, string> Map; //Map where the ID and numbers will be stored

        //Iterating through the map
        while (getline(inFile, line)){
            id = stoi(line.substr(0, 5)); //Convert string to int
            number = line.substr(7, 12);
            Map.insert(make_pair(id, number)); //Insetion to map (Removes duplicates)
        }

        cout << "Size of the map: " << Map.size() << endl; //Prints the size of the map

        vector<string> vecNumbers; //Vector that will store all the phone numbers
        for (auto &x : Map)
        {
            vecNumbers.push_back(x.second);
        }

        //Using "count_if" from the algoritm that will return the number of phone numbers with the area code of 347.
        int areacodeCount = count_if(vecNumbers.begin(), vecNumbers.end(), IsAreaCode);

        cout << "Count of phone# with area code 347: " << areacodeCount << endl; //prints count of phone# with area code 347

        vector<int> vecOfID; //Vector that will store the the ID's with number "212-536-6331"
        vector<pair<int, string> > vecMap; //Vector that will have a copy of Map elements

        for (auto x : Map)
        {
            vecMap.push_back(make_pair(x.first, x.second)); //Reading the map values
        }

        //Using "find_if" from algorithm that will return the element if it satisfies the IsNumber (bool function) that returns true if equal to "212-536-6331"
        for (vector<pair<int, string> >::iterator itr = vecMap.begin(); (itr = find_if(itr, vecMap.end(), IsNumber)) != vecMap.end(); ++itr)
        {
            vecOfID.push_back((*itr).first);
        }

        cout << "The ID(s) with the given phone#: "; //Prints the ID(s) with the given phone number.
        for (auto &x : vecOfID)
        {
            if (x == vecOfID.at(vecOfID.size() - 1))
            {
                cout << x << "\n";
            }
            else
            {
                cout << x << ", ";
            }
        }

        vector<string> vecOf212; //Vector that will stores all phone numbers with area code 212, from the map

        //Using "find_if" from algorithm that will return the element if it satisfies the IsCode (bool function) that returns true if equal to "212"
        for (vector<pair<int, string> >::iterator i = vecMap.begin(); (i = find_if(i, vecMap.end(), IsCode)) != vecMap.end(); ++i)
        {
            vecOf212.push_back((*i).second); // Reads in the phone number's
        }
        //Prints the size of the vector with all (212) numbers
        cout << "Size of the vector with all (212) numbers: " << vecOf212.size() << endl;

        vector<string> vecNoDup; //Vector vecNoDup will store all from step 4's result, with all duplicates of 212 numbers removed

        vecNoDup.assign(vecOf212.begin(), vecOf212.end()); //Using "assign" to copy the elements from vecOf212

        //Using "sort" from algorithm to sort the elements in the range [first,last) into ascending order.
        sort(vecNoDup.begin(), vecNoDup.end());

        //Using "unique" from the algoritm and "erase" from vector to remove the consecutive items and erase them from the vector.
        //The ersased elements are the duplicates of 212 numbers.
        vecNoDup.erase(unique(vecNoDup.begin(), vecNoDup.end()), vecNoDup.end());

        //Prints the size of the vector with unique (212) numbers
        cout << "Size of the vector with unique (212) numbers: " << vecNoDup.size() << endl;

        inFile.close(); //Closing the phoneno.txt
        return 0;
    }
    catch (string message)
    {
        cerr << message << endl; //Prints out the error message
        exit(1);
    }
}