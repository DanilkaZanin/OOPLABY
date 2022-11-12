#ifndef OOPLABY_FRACTION_H
#define OOPLABY_FRACTION_H


#include <utility>
#include <errno.h>

typedef enum fraction_ret_code_e
{
    F_RET_OK = 0,
    F_RET_ERR,
} fraction_ret_code_t;

class Fraction {
private:
    long a;
    unsigned short b;
    unsigned int null;
    bool flag;

    unsigned short dellNull(unsigned short _b);
    unsigned short toSize(unsigned short _b, unsigned short length1);
    void toSameLength(Fraction &object);
    unsigned short length(unsigned short _b);
    fraction_ret_code_t findNulls(unsigned short _b1, unsigned short _b2,std::string symbol);
public:
    Fraction();
    Fraction(long _a, unsigned short _b);

    void setA(long _a);
    void setB(unsigned short _b);

    long getA();
    unsigned short getB();

    void addition(Fraction object); // сложение
    void subtraction(Fraction object); // вычитание
    void multiplication(Fraction object); //умножение

    //сравнение
    bool isBigger(Fraction object);
    bool isSmaller(Fraction object);
    bool isSame(Fraction object);

    std::string toString();

};
#endif //OOPLABY_FRACTION_H
