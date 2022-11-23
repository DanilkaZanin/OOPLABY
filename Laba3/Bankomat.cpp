//
// Created by danila on 16.11.22.
//

#include "Bankomat.h"
#include <iostream>
#include <utility>

int Bankomat::id = 0;

Bankomat::Bankomat() {
    ++id;
}

void Bankomat::putMoney(std::string str) {
    if(std::stoi(str) >= minAmountForClient && std::stoi(str) <= maxAmountForClient){
        money + str;

        std::string str1;
        str += " ";

        for(int i = 0; i < str.length(); i++){
            if(str[i] == '.'){
                amountOfMoney.first += std::stoi(str1);
                str1 = "";
            }
            else if(str[i] ==' '){
                amountOfMoney.second += std::stoi(str1);
            }
            else{
                str1 += str[i];
            }
        }
    }
    else{
        std::cout <<"Сумма некорректна! " <<'\n';
    }
}

void Bankomat::takeMoney(std::string str) {
    if(std::stoi(str) >= minAmountForClient && std::stoi(str) <= maxAmountForClient){
        std::string str1;
        str += "";

        std::pair<int, int> p;
        for(int i = 0; i < str.length(); i++){
            if(str[i] == '.'){
                p.first = std::stoi(str1);
                str1 = "";
            }
            else if(str[i] ==' '){
                p.second = std::stoi(str1);
            }
            else{
                str1 += str[i];
            }
        }
        if(amountOfMoney.first >= p.first && amountOfMoney.second >= p.second){
            money - str;
            amountOfMoney.first -= p.first;
            amountOfMoney.second -= p.second;
        }
        else{
            std::cout <<"Купюр недостаточно! " << '\n';
        }
    }
    else{
        std::cout << "Сумма некорректна! "<< '\n';
    }
}

std::string Bankomat::toString() {
    std::string str;

    str = std::to_string(amountOfMoney.first)+ "."+ std::to_string(amountOfMoney.second);

    return str;
}

