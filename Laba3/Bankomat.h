// Реализовать класс Bankomat (34) используя класс Money (33)

#ifndef OOPLABY_BANKOMAT_H
#define OOPLABY_BANKOMAT_H

#include <string>
#include "Money.h"

class Bankomat {
private:

    static int id;
    std::pair<int,int> amountOfMoney;

    const int minAmountForClient = 10;
    const int maxAmountForClient = 10000;

    Money money;

public:
    /*** Конструктор по умолчанию.
    При вызове генерирует id банкомата***/
    Bankomat();


    /*** Добавление денег в банкомат
     вызывает метод + класса Money
     @param str - сумма денег
     @return *this
     ***/
    void putMoney(std::string str);

    /*** Снятие денег с банкомата
     Проверяет снимаемую сумму на ее корректность и на текущее количество купюр в банкомате, если все нормально то
     вызывается метод - класса Money.
     Если нет, то выводит сообщение о некорректности суммы
     @param str - сумма денег
     @return *this
     ***/
    void takeMoney(std::string str);

    std::string toString();
};

#endif //OOPLABY_BANKOMAT_H
