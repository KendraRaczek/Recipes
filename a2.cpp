///////////////////////////////////////////////////////////////////////
// File Name:       a2.cpp
//
// Author:          Kendra Raczek
// CS email:        raczek@cs.wisc.edu
//
// Description:     Reads and parses two input files that contain a
//                  list of recipes. Analyses and prints the Set
//                  Intersection and Set Union between them. Outputs a
//                  list of recipes in Intersection and a list of
//                  recipes in Union to separate output text files.
//
// Sources:         GeeksForGeeks
//
// URL(s) of sources:
//                  http://www.geeksforgeeks.org/merge-operations-using
//                  -stl-in-c-merge-includes-set_union-set_intersection
//                  -set_difference/
///////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // first file is valid to open
    bool firstValid = false;
    // name of first file that user enters
    string firstFileName = "";
    // input stream from first file
    ifstream firstFile;

    // second file is valid to open
    bool secondValid = false;
    // name of second file that user enters
    string secondFileName = "";
    // input stream from second file
    ifstream secondFile;

    // user enters name of first file
    while ( firstValid == false ) {
        cout << "Enter the name of the first file: ";
        cin >> firstFileName;

        firstFile.open(firstFileName);

        if (firstFile.is_open()) {
            firstValid = true;
        }
        else {
            cout << "Input file " << firstFileName
                 << " is NOT found. Please try again." << endl;
        }
    }

    // user enters name of first file
    while ( secondValid == false ) {
        cout << "Enter the name of the second file: ";
        cin >> secondFileName;

        secondFile.open(secondFileName);

        if (secondFile.is_open()) {
            secondValid = true;
        }
        else {
            cout << "Input file " << secondFileName
                 << " is NOT found. Please try again." << endl;
        }
    }

    vector<string> firstRecipes;
    vector<string> secondRecipes;

    // parse first file
    for( string line; getline( firstFile, line ); ) {
        firstRecipes.push_back(line);
    }

    // parse second file
    for( string line; getline( secondFile, line ); ) {
        secondRecipes.push_back(line);
    }

    // sort both vectors
    sort(firstRecipes.begin(), firstRecipes.end());
    sort(secondRecipes.begin(), secondRecipes.end());

    cout << endl;
    cout << "Number of recipes in " << firstFileName << " = " << firstRecipes.size() << endl;
    cout << "Number of recipes in " << secondFileName << " = " << secondRecipes.size() << endl;

    // set intersection
    vector<string> intersectionRecipes(firstRecipes.size() + secondRecipes.size());

    auto it1 = set_intersection(firstRecipes.begin(),firstRecipes.end(),
                                secondRecipes.begin(), secondRecipes.end(),
                                intersectionRecipes.begin());

    intersectionRecipes.resize(it1 - intersectionRecipes.begin());

    cout << "Number of recipes that are present in BOTH " << firstFileName << " AND "
         << secondFileName << " = " << intersectionRecipes.size() << endl;

    // set union
    vector<string> unionRecipes(firstRecipes.size() + secondRecipes.size());

    auto it = set_union(firstRecipes.begin(), firstRecipes.end(), secondRecipes.begin(),
                        secondRecipes.end(), unionRecipes.begin());

    unionRecipes.resize(it - unionRecipes.begin());

    cout << "Number of recipes that are in EITHER " << firstFileName << " OR "
         << secondFileName << " = " << unionRecipes.size() << endl << endl;

    // print intersection
    sort(intersectionRecipes.begin(), intersectionRecipes.end());
    if ( intersectionRecipes.size() > 0) {
        cout << "List of recipes that are present in BOTH " << firstFileName << " AND "
             << secondFileName << ":" << endl;

        for (auto it = intersectionRecipes.begin(); it != intersectionRecipes.end(); ++it) {
            cout << *it << endl;
        }
        cout << endl;
    }

    // write intersection output
    sort(intersectionRecipes.begin(), intersectionRecipes.end());
    ofstream intersectionOutput("intersection.txt");

    for (auto it = intersectionRecipes.begin(); it != intersectionRecipes.end(); ++it) {
        intersectionOutput << *it << endl;
    }

    cout << "The set intersection of the two files was written to a file named intersection.txt"
         << endl;

    // write union output
    sort(unionRecipes.begin(), unionRecipes.end());
    ofstream unionOutput("union.txt");

    for (auto it = unionRecipes.begin(); it != unionRecipes.end(); ++it) {
        unionOutput << *it << endl;
    }
    cout << "The set union of the two files was written to a file named union.txt"
         << endl;

    return 0;
}