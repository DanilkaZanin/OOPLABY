//
// Created by danila on 10.12.22.
//

#include <limits>
#include "Controller.h"

Controller::Controller() {
    vector <string> a = readTxt("/home/danila/CLionProjects/OOPLABY/ForMasha/txtFiles/database.txt");//укажи путь до файла
    stringToDatabase(a);

    while (mainPath())
        if(!mainPath())
            break;

}

vector <string> Controller::readTxt(string database) {
    vector <string> vec;
    std::string line;
    std::ifstream in(database); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            vec.push_back(line);
        }
    }
    else
        std::cout << "Ne nashel file" << std::endl;

    in.close();     // закрываем файл
    return vec;
}

void Controller::stringToDatabase(vector<string> vec) {
    for(int i = 0; i < vec.size(); i++){
        Employee employee(vec[i]);
        database.push_back(employee);
    }
}

void Controller::printAllInformation() {
    for(int i =0; i < database.size(); i++){
        Employee &employee = database[i];

        employee.print();
    }
}

void Controller::addToDatabase() {
    string str;
    cout << "Введите данные через разделитель ;" << '\n';
    cout <<"ФИО;Должность;Зарплата;год рождения"<< '\n';
    getline(cin,str);


    Employee employee(str);

    database.push_back(employee);
}

void Controller::refactor(int index, int position, string str) {
    Employee &employee = findElem(index - 1);

    switch (position) {
        case 1:{
            employee.setFio(str);
            break;
        }
        case 2:{
            employee.setPost(str);
            break;
        }
        case 3:{
            employee.setSalary(stod(str));
            break;
        }
        case 4:{
            employee.setYearOfBirth(stoi(str));
            break;
        }
    }
}

Employee &Controller::findElem(int index) {
    if(database.size() >= index){
        Employee &employee = database[index];
        return employee;
    }
}

void Controller::delElem(int index) {
    auto iter = database.cbegin();
    if(database.size() >= index){
        database.erase(iter + index - 1);
    }
}

void Controller::menu() {
    cout <<"------------------------------------------------------------------------------"<<'\n';
    cout << "Меню" << '\n';
    cout <<"------------------------------------------------------------------------------"<<'\n';
    cout <<"Нажмите 1, чтобы вывести всю информацию о сотрудниках" << '\n';
    cout <<"Нажмите 2, чтобы добавить информацию о сотруднике"<<'\n';
    cout <<"Нажмите 3, чтобы удалить информацию о сотруднике"<<'\n';
    cout <<"Нажмите 4, чтобы изменить информацию о сотруднике"<<'\n';
    cout <<"Нажмите 5, чтобы вывести полную информацию о сотруднике"<<'\n';
    cout <<"Нажмите 6, чтобы отсортировать сотрудников по ФИО"<<'\n';
    cout <<"Нажмите 7, чтобы вычислить размер средней заработной платы сотрудников"<<'\n';
    cout <<"Нажмите 8, чтобы закончить работу" <<'\n';
    cout <<"Введите требуемую цифру: ";
}

bool Controller::mainPath() {
    menu();

    int a;
    cin >> a;
    std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); //для очистки потока ввода
    cout <<"------------------------------------------------------------------------------"<<'\n';
    switch (a) {
        case 1:{
            printAllInformation();
            break;
        }
        case 2:{
            cin.clear();
            addToDatabase();
            break;
        }
        case 3:{
            cout << "Введите индекс требуемого сотрудника в базе данных: ";

            int b;
            cin >> b;
            delElem(b);
            break;
        }
        case 4:{
            cout << "Введите индекс требуемого сотрудника в базе данных: ";

            int index;
            cin >> index;

            cout << "Введите 1, чтобы изменить Фио"<<'\n';
            cout << "Введите 2, чтобы изменить должность "<<'\n';
            cout << "Введите 3, чтобы изменить заработную плату"<<'\n';
            cout << "Введите 4, чтобы изменить год рождения"<<'\n';

            int b;
            cin >>b;
            std::cin.ignore( std::numeric_limits<std::streamsize>::max(), '\n' ); //для очистки потока ввода

            cout << "Введите измененную информацию" <<'\n';

            string str;
            getline(cin, str);

            refactor(index,b,str);
            break;
        }
        case 5:{
            cout << "Введите индекс требуемого сотрудника в базе данных:";

            int index;
            cin >> index;

            Employee &employee = database[index - 1];
            employee.print(1);
            break;
        }
        case 6:{
            fioSort();
            break;
        }
        case 7:{
            cout << "Средняя заработная плата: "<< avgSalary() << '\n';
            break;
        }
    }
    if(a > 7){
        return false;
    }
    else{
        cout <<'\n'<<"------------------------------------------------------------------------------"<<'\n';
        cout<<"Для продолжения нажмите на Enter"<< '\n';
        cout <<"------------------------------------------------------------------------------"<<'\n';
        cin.get();

        return true;
    }
}


void Controller::fioSort() {
    bool flag = false;
    for (int i = 0; i < database.size();) {
        if (i == 7) {
            break;
        } else {
            Employee &employee1 = database[i];
            Employee &employee2 = database[i + 1];

            if (employee1.getFio()[0] > employee2.getFio()[0]) {
                swap(employee1, employee2);
                i = 0;
                flag = true;
            } else if (employee1.getFio()[0] == employee2.getFio()[0]) {
                for (int j = 1; j < employee1.getFio().length();) {
                    if (employee1.getFio()[j] == employee2.getFio()[j]){
                        j++;
                    }
                    else if (employee1.getFio()[j] > employee2.getFio()[j]) {
                        swap(employee1, employee2);
                        break;
                    } else
                        break;
                }
            }
            if (flag) {
                flag = false;
            } else
                i++;
        }

    }
}
    long Controller::avgSalary() {
    long d = 0;
    for(int i = 0; i < database.size(); i++){
        Employee &employee = database[i];
        d += employee.getSalary();
    }
    d = d / database.size();

    return d;
}
