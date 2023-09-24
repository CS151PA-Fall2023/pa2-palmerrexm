/**
 * @file main.cpp
 * @author Rex Palmer
 * @brief 
 * @version 0.1
 * @date 9/24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include "index.h"

using namespace std;
int main(){
    vector<Student> gradeData; //vector of original structures uploaded from csv file
    vector<Student*> indexByLastName; //vector of pointers later sorted by lastName member variable
    vector<Student*> indexBySsn; //vector of pointers later sorted by lastName member variable
    vector<Student*> indexByFirstName; //vector of pointers later sorted by lastName member variable
    ifstream file;
    openInputFile(file, "grades.csv");
    readFileIntoVector(file, gradeData);
    makePointerVector(indexByLastName, gradeData);
    makePointerVector(indexBySsn, gradeData);
    makePointerVector(indexByFirstName, gradeData);
    insertionSortPointerVectorLastName(indexByLastName);
    insertionSortPointerVectorSSN(indexBySsn);
    insertionSortPointerVectorFirstName(indexByFirstName);
    initializeAndSelect(indexByLastName, indexBySsn, indexByFirstName);

    
    
    




    file.close();
    return 0;
}