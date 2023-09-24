/**
 * @file index.cpp
 * @author Rex Palmer
 * @brief 
 * @version 0.1
 * @date 2023-09-24
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

/**
 * @brief function opens csv file to be read by program
 * 
 * @param file 
 * @param name 
 */
void openInputFile(ifstream &file, string name)
{
    file.open(name);
    if (!file){
        cout<<"Error opening file\n";
        exit(1);
    }
}

/**
 * @brief function reads file into vector
 * 
 * @param file 
 * @param v 
 */
void readFileIntoVector(ifstream &file, vector<Student> &v)
{
    //variable used to read file
    string input;
    //moves past the first line of the file
    getline(file, input);
    getline(file, input, ',');
    


    while (file.peek() != EOF)
    {
        Student nameLine;
        
        istringstream(input)>>nameLine.id;
        getline(file, input, ',');
        input[0] = toupper(input[0]); //changes the first letter of the last name column to upper case. this is done to make sorting correct later.
        nameLine.lastName=input;
        getline(file, input, ',');          
        istringstream(input)>>nameLine.firstName;
        getline(file, input, ',');        
        istringstream(input)>>nameLine.ssn;
        getline(file, input, ',');     
        istringstream(input)>>nameLine.test[0];
        getline(file, input, ',');  
        istringstream(input)>>nameLine.test[1];
        getline(file, input, ',');     
        istringstream(input)>>nameLine.test[2];
        getline(file, input, ',');   
        istringstream(input)>>nameLine.test[3];
        getline(file, input, ',');     
        istringstream(input)>>nameLine.final;
        getline(file, input, '\n');
        istringstream(input)>>nameLine.letterGrade;
        getline(file, input, ',');

        v.push_back(nameLine);
    }
}

/**
 * @brief makes a vector of pointers that is initialized to the addresses of the vector containing the csv contents
 * 
 * @param v 
 * @param o 
 */
void makePointerVector(vector<Student*> &v, vector<Student> &o)
{
    for (size_t i = 0; i<o.size(); i++)
    {
        v.push_back(&o[i]);
    }
}

/**
 * @brief sorts a vector of pointers to structures by the lastName member
 * 
 * @param v 
 */
void insertionSortPointerVectorLastName(vector<Student*> &v)
{
    for (long unsigned int startScan = 1; startScan < v.size(); ++startScan)
    {
        Student* key = v[startScan];
        int index = startScan - 1;

        while (index >= 0 && (*v[index]).lastName > (*key).lastName)
        {
            v[index+1] = v[index];
            --index;
        }
        v[index+1] = key;
    }
}

/**
 * @brief sorts a vector of pointers to structures by the ssn member
 * 
 * @param v 
 */
void insertionSortPointerVectorSSN(vector<Student*> &v)
{
    for (long unsigned int startScan = 1; startScan < v.size(); ++startScan)
    {
        Student* key = v[startScan];
        int index = startScan - 1;

        while (index >= 0 && (*v[index]).ssn > (*key).ssn)
        {
            v[index+1] = v[index];
            --index;
        }
        v[index+1] = key;
    }
}

/**
 * @brief sorts a vector of pointers to structures by the firstName member
 * 
 * @param v 
 */

void insertionSortPointerVectorFirstName(vector<Student*> &v)
{
    for (long unsigned int startScan = 1; startScan < v.size(); ++startScan)
    {
        Student* key = v[startScan];
        int index = startScan - 1;

        while (index >= 0 && (*v[index]).firstName > (*key).firstName)
        {
            //cout<<(*v[index]).firstName<<" is bigger than "<<(*key).firstName<<endl;
            v[index+1] = v[index];
            --index;
        }
        v[index+1] = key;
    }
}

/**
 * @brief displays a vector of pointers to structures 
 * 
 * @param v 
 * @param c 
 */

void displayPointerVector(vector<Student*> &v, int c)
{
    //switch statement to identify which member to display
    string sortBy;
    switch (c)
    {
        case 1: sortBy = "last name";
        break;
        case 2: sortBy = "SSN";
        break;
        case 3: sortBy = "first name";
        break;
    }

    cout<<"Sorted by "<<sortBy<<endl;
    cout<<setw(3)<<left<<"ID"<<setw(10)<<"Last Name"<<setw(11)<<"First Name"<<setw(12)<<"SSN"<<setw(5)<<"Grade"<<endl;
    for (long unsigned int i=0; i<v.size(); i++)
    {
        cout<<setw(3)<<left<<(*v[i]).id<<setw(10)<<(*v[i]).lastName<<setw(11)<<(*v[i]).firstName<<setw(12)<<(*v[i]).ssn<<setw(5)<<(*v[i]).letterGrade<<endl;
    }
}

/**
 * @brief shows the menu presented to the user upon initialization. returns the user's choice.
 * 
 * @return int 
 */
int displayMenu()
{
    int choice;
    cout<<"1. Print data in ascending order by last name"<<endl;
    cout<<"2. Print data in ascending order by SSN"<<endl;
    cout<<"3. Print data in ascending order by first name"<<endl;
    cout<<"4. Search by last name"<<endl;
    cout<<"5. Search by SSN"<<endl;
    cout<<"6. Search by first name"<<endl;
    cout<<"7. Exit"<<endl<<endl;
    cout<<"Select a menu: ";
    cin >> choice;
    while (choice < 1 || choice > 7)
    {
        cout<<"That input is not valid. Enter an integer between 1 and 12. ";
        cin >> choice;
    }
    cout<<endl;
    cin.ignore();
    return choice;   
}

/**
 * @brief function that initializes the program display/menu and prints output based on user selection
 * 
 * @param iLastName 
 * @param iSSN 
 * @param iFirstName 
 */
void initializeAndSelect(vector<Student*> &iLastName, vector<Student*> &iSSN, vector<Student*> &iFirstName)
{
    int select; //variable used to navigate the menu
    bool leave = false; //variable used to check if user has selected exit
    string choice; //variable used to store user selections
    int choiceInt; //variable returned by binary search to find correct pointer to structure selected by user
    do
    {
        select = displayMenu();

        switch (select)
        {
            case 1: displayPointerVector(iLastName, 1);
                enterToContinue();
            break;
            case 2: displayPointerVector(iSSN, 2);
                enterToContinue();
            break;
            case 3: displayPointerVector(iFirstName, 3);
                enterToContinue();
            break;
            case 4: cout<<"Please enter a last name: "<<endl;
                getline(cin >> ws, choice);
                cout<<endl;
                
                choiceInt=binarySearchLastName(iLastName, choice);

                //loop to search for user input while also validating user input
                while(choiceInt == -1)
                {
                    cout<<"That input is invalid. please type in the desired last name with correct capitilization: ";
                    cin.sync();
                    getline(cin >> ws, choice);
                    choiceInt=binarySearchLastName(iLastName, choice);
                }
                cout<<setw(3)<<left<<"ID"<<setw(10)<<"Last Name"<<setw(11)<<"First Name"<<setw(12)<<"SSN"<<setw(5)<<"Grade"<<endl;
                cout<<setw(3)<<left<<(*iLastName[choiceInt]).id<<setw(10)<<(*iLastName[choiceInt]).lastName<<setw(11)<<(*iLastName[choiceInt]).firstName<<setw(12)<<(*iLastName[choiceInt]).ssn<<setw(5)<<(*iLastName[choiceInt]).letterGrade<<endl;

                enterToContinue();
            break;
            case 5: cout<<"Please enter a SSN: "<<endl;
                getline(cin >> ws, choice);
                cout<<endl;
                
                choiceInt=binarySearchSSN(iSSN, choice);

                //loop to search for user input while also validating user input
                while(choiceInt == -1)
                {
                    cout<<"That input is invalid. please type in the desired ssn with hyphens: ";
                    cin.sync();
                    getline(cin >> ws, choice);
                    choiceInt=binarySearchSSN(iSSN, choice);
                }
                cout<<setw(3)<<left<<"ID"<<setw(10)<<"Last Name"<<setw(11)<<"First Name"<<setw(12)<<"SSN"<<setw(5)<<"Grade"<<endl;
                cout<<setw(3)<<left<<(*iSSN[choiceInt]).id<<setw(10)<<(*iSSN[choiceInt]).lastName<<setw(11)<<(*iSSN[choiceInt]).firstName<<setw(12)<<(*iSSN[choiceInt]).ssn<<setw(5)<<(*iSSN[choiceInt]).letterGrade<<endl;

                enterToContinue();
            break;
            case 6: cout<<"Please enter a first name: "<<endl;
                getline(cin >> ws, choice);
                cout<<endl;
                
                choiceInt=binarySearchFirstName(iFirstName, choice);

                //loop to search for user input while also validating user input
                while(choiceInt == -1)
                {
                    cout<<"That input is invalid. please type in the desired first name with correct capitilization: ";
                    cin.sync();
                    getline(cin >> ws, choice);
                    choiceInt=binarySearchFirstName(iFirstName, choice);
                }
                cout<<setw(3)<<left<<"ID"<<setw(10)<<"Last Name"<<setw(11)<<"First Name"<<setw(12)<<"SSN"<<setw(5)<<"Grade"<<endl;
                cout<<setw(3)<<left<<(*iFirstName[choiceInt]).id<<setw(10)<<(*iFirstName[choiceInt]).lastName<<setw(11)<<(*iFirstName[choiceInt]).firstName<<setw(12)<<(*iFirstName[choiceInt]).ssn<<setw(5)<<(*iFirstName[choiceInt]).letterGrade<<endl;

                enterToContinue();
            break;
            case 7: leave = true;
            break;
        }
    } while (leave != true);
}

/**
 * @brief function used to prompt user to press enter before program continues
 * 
 */
void enterToContinue()
{
    //string enter;
    //cin.ignore();
    cout<<"Press enter to continue...";
    //getline(cin, enter);
    cin.ignore();
    cout<<endl;
}

/**
 * @brief function returns position of lastName member variable requested by user in vector of pointers to structures after performing a binary search.
 * 
 * @param v 
 * @param lName 
 * @return int 
 */
int binarySearchLastName(vector<Student*> &v, string lName)
{
    int first = 0, // First array element
        last = v.size() - 1, // Last array element
        middle, // Midpoint of search
        position = -1; // Position of search value
    bool found = false; // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2; // Calculate midpoint
        if ((*v[middle]).lastName == lName) // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if ((*v[middle]).lastName > lName) // If value is in lower half
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1; // If value is in upper half
        }
    }
    return position;
}

/**
 * @brief function returns position of ssn member variable requested by user in vector of pointers to structures after performing a binary search.
 * 
 * @param v 
 * @param sNumber 
 * @return int 
 */
int binarySearchSSN(vector<Student*> &v, string sNumber)
{
    int first = 0, // First array element
        last = v.size() - 1, // Last array element
        middle, // Midpoint of search
        position = -1; // Position of search value
    bool found = false; // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2; // Calculate midpoint
        if ((*v[middle]).ssn == sNumber) // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if ((*v[middle]).ssn > sNumber) // If value is in lower half
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1; // If value is in upper half
        }
    }
    return position;
}

/**
 * @brief function returns position of firstName member variable requested by user in vector of pointers to structures after performing a binary search.
 * 
 * @param v 
 * @param fName 
 * @return int 
 */
int binarySearchFirstName(vector<Student*> &v, string fName)
{
    int first = 0, // First array element
        last = v.size() - 1, // Last array element
        middle, // Midpoint of search
        position = -1; // Position of search value
    bool found = false; // Flag

    while (!found && first <= last)
    {
        middle = (first + last) / 2; // Calculate midpoint
        if ((*v[middle]).firstName == fName) // If value is found at mid
        {
            found = true;
            position = middle;
        }
        else if ((*v[middle]).firstName > fName) // If value is in lower half
        {
            last = middle - 1;
        }
        else
        {
            first = middle + 1; // If value is in upper half
        }
    }
    return position;
}