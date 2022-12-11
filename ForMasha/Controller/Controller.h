//
// Created by danila on 10.12.22.
//

#ifndef OOPLABY_CONTROLLER_H
#define OOPLABY_CONTROLLER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <utility>
#include <list>
#include "../Employeee/Employee.h"

using namespace std;

class Controller{
private:
    vector <Employee> database;

    vector <string> readTxt(string database);
    void stringToDatabase(vector<string> vec);
    Employee &findElem(int index);
    void addToDatabase();
    void refactor(int index, int position, string str);
    void delElem(int index);
    void printAllInformation();
    void fioSort();
    long avgSalary();
    void menu();
    bool mainPath();
public:
    Controller();


};

#endif //OOPLABY_CONTROLLER_H
