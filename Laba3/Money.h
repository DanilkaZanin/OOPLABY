//
// Created by danila on 24.11.22.
//

#ifndef OOPLABY_MONEY_H
#define OOPLABY_MONEY_H


class Money{
private:
    int rubles[9][2] = {
            {1,0},
            {2,0},
            {5,0},
            {10,0},
            {50,0},
            {100,0},
            {500,0},
            {1000,0},
            {5000,0}
    };

    int pennies[4][2] = {
            {1,0},
            {5,0},
            {10,0},
            {50,0}
    };

    static std::pair<int,int> takeRublesAndPennies(std::string str);
    void stringToMoney(std::string str);

    int findLvlRubles(int value);
    int findLvlPennies(int value);

    int doSumRubles(int sum, int lvl, int value);
    int doSumPennies(int sum, int lvl, int value);
public:
    /// Конструктор по умолчанию default///
    Money();
    /***Конструктор
     вызывает метод stringToMoney, которая помещает значения строки в массивы rubles и pennies
     @param object строка
     @return *this
     ***/
    Money(std::string object);
    /*** Сложение объекта класса мани со строкой
     @param str строка, значения которой будут прибавляться к текущему объекту класса
     @return *this
     ***/
    Money operator + (std::string str);
    /*** Вычитание из текущего объекта класса строки
    Создается объект класса мани с параметром str, далее от больших значений к меньшим ищется купюра(монета) в новом объекте.
    Когда купюра подходящего номинала находится, ищется такая-же купюра из имеющихся, если ее нет, то пытается добавить недостающую сумму.
    @param str - строка
    @return *this
     ***/
    Money operator - (std::string str);
};


#endif //OOPLABY_MONEY_H
