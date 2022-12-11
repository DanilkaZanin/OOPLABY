//
// Created by danila on 10.12.22.
//

#ifndef OOPLABY_EMPLOYEE_H
#define OOPLABY_EMPLOYEE_H


#include <string>
#include <list>
#include <vector>
#include <iostream>

using namespace std;

class Employee {
private:
    string FIO;
    string post;
    double salary;
    unsigned short yearOfBirth;

    vector <string> toVector(string str);
    void toEmployee(string str);
public:
    Employee(string str);

    string &getFio();
    void setFio(const string &fio);

    string &getPost();
    void setPost(const string &post);

    double getSalary() const;
    void setSalary(double salary);

    unsigned short getYearOfBirth();
    void setYearOfBirth(unsigned short yearOfBirth);


    string toString();
    void print();
    void print(int something);

};


#endif //OOPLABY_EMPLOYEE_H
