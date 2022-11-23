//
// Created by danila on 24.11.22.
//

#include <string>
#include "Money.h"

Money::Money()= default;

Money::Money(std::string object) {
    stringToMoney(object);
}


std::pair<int, int> Money::takeRublesAndPennies(std::string str) {
    std::pair<int, int> pair;

    str+=" ";
    std::string str1;

    int r,p;
    for(int i = 0; i< str.length(); i++){
        if(str[i] == '.'){
            r = std::stoi(str1);
            str1 = "";
        }
        else if(str[i] ==' '){
            p = std::stoi(str1);
        }
        else{
            str1 += str[i];
        }
    }

    pair.first = r;
    pair.second = p;

    return pair;
}

void Money::stringToMoney(std::string str) {
    std::pair<int, int> pair = takeRublesAndPennies(std::move(str));
    int r = pair.first ,p = pair.second;


    for(int i = 8; i >= 0; i--){
        if(r >= rubles[i][0]){
            rubles[i][1] = r / rubles[i][0];
            r %= rubles[i][0];
        }
    }

    for(int i = 3; i >=0; i --){
        if(p >= pennies[i][0]){
            pennies[i][1] = p / pennies[i][0];
            p %= pennies[i][0];
        }
    }
}

int Money::findLvlRubles(int value) {
    int i = 8;
    for(; i >= 0; i--){
        if(value % rubles[i][0] != value){
            break;
        }
    }
    return i;
}
int Money::findLvlPennies(int value) {
    int i = 3;
    for(; i >= 0; i--){
        if(value % pennies[i][0] != value){
            break;
        }
    }
    return i;
}

int Money::doSumRubles(int sum, int lvl, int value) {
    while(sum >= value){
        if(rubles[lvl][1] == 0){
            break;
        }
        else if(value + rubles[lvl][1] > sum){
            break;
        }
        else{
            value += rubles[lvl][0];
            rubles[lvl][1] --;
        }
    }

    return value;
}

int Money::doSumPennies(int sum, int lvl, int value) {
    while(sum >= value){
        if(pennies[lvl][1] == 0){
            break;
        }
        else if(value + pennies[lvl][1] > sum){
            break;
        }
        else{
            value += pennies[lvl][0];
            pennies[lvl][1] --;
        }
    }

    return value;
}

Money Money::operator+(std::string str) {
    std::pair<int, int> pair = takeRublesAndPennies(std::move(str));
    int r = pair.first ,p = pair.second;

    for(int i = 8; i >= 0; i--){
        if(r >= rubles[i][0]){
            rubles[i][1] += r / rubles[i][0];
            r %= rubles[i][0];
        }
    }

    for(int i = 3; i >=0; i --){
        if(p >= pennies[i][0]){
            pennies[i][1] += p / pennies[i][0];
            p %= pennies[i][0];
        }
    }

    return *this;
}

Money Money::operator-(std::string str) {
    /*if(!isOperationOk(str)){
        std::cout << "Нет достаточного количества купюр! " << '\n';
    }*/
    std::pair<int, int> pair = takeRublesAndPennies(std::move(str));
    int r = pair.first ,p = pair.second;
    int r1 = r, p1 = p;

    int value = 0;
    int i = findLvlRubles(r1);
    while(r > value){
        if(i == -1)
            break;
        else{
            value = doSumRubles(r, i, value);
            r1 -= rubles[i][0];
            i = findLvlRubles(r1) + 1;
        }
        i--;
    }

    if(r != value){
        p+= (r - value) * 100;
    }

    value = 0;
    i = 3;
    while(p > value){
        if(i == -1)
            break;
        else{
            value = doSumPennies(p,i,value);
            p1 -= pennies[i][0];
            i = findLvlPennies(p1) + 1;
        }
        i--;
    }
    return *this;
}

