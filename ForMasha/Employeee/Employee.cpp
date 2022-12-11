//
// Created by danila on 10.12.22.
//

using namespace std;

#include <vector>
#include <iostream>
#include "Employee.h"

string &Employee::getFio() {
    return FIO;
}

void Employee::setFio(const string &fio) {
    FIO = fio;
}

string &Employee::getPost(){
    return post;
}

void Employee::setPost(const string &post) {
    Employee::post = post;
}

double Employee::getSalary() const {
    return salary;
}

void Employee::setSalary(double salary) {
    Employee::salary = salary;
}

unsigned short Employee::getYearOfBirth(){
    return yearOfBirth;
}

void Employee::setYearOfBirth(unsigned short yearOfBirth) {
    Employee::yearOfBirth = yearOfBirth;
}

void Employee::toEmployee(std::string str) {
    vector <string> a = toVector(str);

    FIO = a[0];
    post = a[1];
    salary = stod(a[2]);
    yearOfBirth = stoi(a[3]);
}

vector <string> Employee::toVector(string str) {
    int i =0;
    vector <string> a;
    string b;

    while(str[i]){
        if(str[i] != ';'){
            b += str[i];
        }
        else{
            a.push_back(b);
            b = "";
        }
        i++;
    }
    return a;
}

Employee::Employee(string str) {
    toEmployee(str);
}

string Employee::toString() {
    return FIO + ";" + post + ";" + to_string(salary) + ";" + to_string(yearOfBirth);
}

void Employee::print() {
    cout << FIO << " " << post <<" " << salary<<" "<<yearOfBirth<<'\n';
}

void Employee::print(int something) {
    cout <<"ФИО: "<< FIO <<'\n'<< "Должность: "<< post <<'\n'<<"Зарплата: "<< salary<<'\n'<<"Год рождения: "<<yearOfBirth<<'\n';
}




/*
Kiseleva Maria Sergeevna ; Manager ; 19500.00 ; 2003 ;  */
