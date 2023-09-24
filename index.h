/**
 * @file   index.h
 * @brief  Declaration file
 * @author Rex Palmer
 * @date   9/24
 *
 */
// START GUARD CODES
#ifndef INDEX_H
#define INDEX_H

// INCLUDE THE HEADER FILES NEEDED FOR THE FUNCTIONS TO WORK
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;
struct Student
{
    int id;
    string lastName;
    string firstName;
    string ssn;
    float test[3];
    float final;
    string letterGrade;
};
void openInputFile(ifstream &file, string name);
void readFileIntoVector(ifstream &file, vector<Student> &v);
void makePointerVector(vector<Student*> &v, vector<Student> &o);
void insertionSortPointerVectorLastName(vector<Student*> &v);
void insertionSortPointerVectorFirstName(vector<Student*> &v);
void insertionSortPointerVectorSSN(vector<Student*> &v);
void displayPointerVector(vector<Student*> &v, int c);
int displayMenu();
void initializeAndSelect(vector<Student*> &iLastName, vector<Student*> &iSSN, vector<Student*> &iFirstName);
void enterToContinue();
int binarySearchLastName(vector<Student*> &v, string lName);
int binarySearchSSN(vector<Student*> &v, string sNumber);
int binarySearchFirstName(vector<Student*> &v, string fName);
#endif