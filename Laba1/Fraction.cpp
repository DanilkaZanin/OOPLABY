#include <valarray>
#include <iostream>
#include "Fraction.h"

Fraction::Fraction(){
    a = 0;
    b = 0;
    null = 0;
    flag = false;
}

Fraction::Fraction(long _a, unsigned short _b) {
    a = _a;
    b = _b;
    null = 0;
    flag = false;
}

void Fraction::setA(long _a) {
    a = _a;
}
void Fraction::setB(unsigned short _b) {
    b = _b;
}

long Fraction::getA() {
    return a;
}
unsigned short Fraction::getB() {
    return b;
}

unsigned short Fraction::dellNull(unsigned short _b) {
    while(_b%10 == 0){

        _b = b/10;
    }
    return _b;
}

unsigned short Fraction::length(unsigned short _b) {
    unsigned short i = 0;

    while(_b != 0){
        _b = _b/10;
        i++;
    }
    return i;
}

unsigned short Fraction::toSize(unsigned short _b, unsigned short length1) {
    unsigned short lengthB = length(_b);

    for(int i = 0; i < length1 - lengthB; i++){
        _b *=10;
    }

    return _b;
}

void Fraction::toSameLength(Fraction &object) {
    if(length(b) > length(object.b)){
        object.b = toSize(object.b, length(b));
    }
    else if(length(b) < length(object.b)){
        b = toSize(b, length(object.b));
    }
}

fraction_ret_code_t Fraction::findNulls(unsigned short _b1, unsigned short _b2, std::string symbol) {
    fraction_ret_code_t ret = F_RET_OK;
    errno = 0;
    if(symbol == "+"){
        if(length(_b1 + _b2) - length((_b1 + _b2) % (unsigned short) pow(10,length(_b1 + _b2) - 1)) > 1){
            null = length(_b1 + _b2) - length((_b1+_b2) % (unsigned short) pow(10,length(_b1 + _b2) - 1)) - 1 ;
        }
    }
    else if(symbol =="-"){
        if(length(_b1) - length(_b1-_b2) > 0 ){
            null = length(_b1) - length(_b1-_b2);
        }
    }
    else{
        errno = EINVAL;
        ret = F_RET_ERR;
    }
    return ret;
}

void Fraction::addition(Fraction object) {

    b = dellNull(b);
    object.b = dellNull(object.b);

    toSameLength(object);

    if(a >= 0 && object.a >= 0){
        //если длина суммы больше длины переменных
        if(length(b + object.b) > length(b) && length(object.b)){

            findNulls(b,object.b,"+");
            a += object.a + (b + object.b)/(unsigned short ) pow(10,(length(b+ object.b) - 1));
            b = (b+ object.b)%(unsigned short ) pow(10,(length(b+ object.b)) - 1);
        }

        else{
            a += object.a;
            b += object.a;
        }
    }
    else if(a >= 0 && object.a < 0){
        object.a = - object.a;
        subtraction(object);
    }
    else if(a < 0 && object.a > 0 ){
        object.a = - object.a;
        subtraction(object);
    }
    else{ //если обе переменных меньше нуля

        a = -a;
        object.a = -object.a;
        flag = true;

        addition(object);
    }

}

void Fraction::subtraction(Fraction object) {
    b = dellNull(b);
    object.b = dellNull(object.b);

    toSameLength(object);

    if(a > object.a){
        if(a >= 0){
            if(object.a >= 0){
                if(b >= object.b){ //когда a > obj.a && b > obj.b
                    findNulls(b,object.b,"-");

                    a = a - object.a;
                    b = b - object.b;
                }
                else{
                    findNulls(object.b,b,"-");
                    a = a - object.a - 1;
                    b = object.b - b;

                }
            }
            else{ //когда a положительное, а obj.a отрицательное
                object.a = -object.a;
                addition(object);
            }


        }
        else{ // когда а < 0 && object.a < 0 && a > object.a
            if(object.b > b){
                findNulls(object.b,b,"-");

                a = a- object.a;
                b = object.b - b;
            }
            else{
                findNulls(object.b +(unsigned short ) pow(10,length(object.b)),b,"-");

                a = a - object.a - 1;
                b = object.b +(unsigned short ) pow(10,length(object.b)) - b;
            }
        }
    }
    else if(a == object.a){
        if(a >= 0){
            if(b >= object.b){
                findNulls(b,object.b,"-");
                b = b - object.b;
            }
            else{
                flag = true;
                findNulls(object.b,b,"-");
                b = object.b - b;
            }
        }
        else{ //когда a == obj.a && < 0
            if(b > object.b){
                flag = true;
                if (findNulls(b,object.b,"-") != F_RET_OK)
                {
                    return;
                };
                b = b - object.b;
            }
            else{
                findNulls(object.b,b,"-");
                b = object.b - b;
            }
        }
        a = 0;
    }
    else{ // когда obj.a > a;
        if(object.a >= 0){
            if(a >= 0){
                if(object.b > b){
                    flag = true;
                    findNulls(object.b,b,"-");

                    a = object.a - a;
                    b = object.b - b;
                }
                else{
                    flag = true;
                    findNulls(object.b +(unsigned short ) pow(10,length(object.b)),b,"-");

                    a = object.a -a -1;
                    b = object.b +(unsigned short ) pow(10,length(object.b)) - b;
                }
            }
            else{
                object.a = -object.a;
                addition(object);
            }
        }
        else{
            flag = true;
            a = -a;
            object.a = -object.a;

            if(b > object.b){
                findNulls(b,object.b,"-");

                a = a - object.a;
                b = b - object.b;
            }
            else{
                findNulls(b + (unsigned short ) pow(10,length(object.b)),object.b,"-");
                a = a - object.a - 1;
                b =  b +(unsigned short ) pow(10,length(object.b)) - object.b;

            }
        }
    }
}

void Fraction::multiplication(Fraction object) {
    long mul;
    unsigned short mul1;
    if(a ==0 || object.a == 0){
        mul = 0;
        mul1 = 0;
    }
    else if(a < 0 && object.a > 0 || a > 0 && object.a < 0){
        flag = true;
        if(a < 0)
            a = -a;
        else
            object.a = -object.a;

    }
    else if (a < 0 && object.a < 0){
        a = -a;
        object.a = -object.a;
    }

    mul = a * object.a + a * object.b / (long) pow(10, length(object.b)) + b * object.a / (long) pow(10, length(b));

    mul1 = toSize(a * object.b % (long) pow(10, length(object.b)), length(b * object.b))
           + toSize(b * object.a % (long) pow(10, length(b)), length(b * object.b))
           + b * object.b;

    if(length(mul1) > length(b*object.b)){
        mul += mul1 /(long) pow(10, length(mul1)-1);
        mul1 %= (long) pow(10, length(mul1)-1);
    }

    a = mul;
    b = mul1;
}

bool Fraction::isBigger(Fraction object) {
    if(a > object.a){
        return true;
    }
    else if(a < object.a){
        return false;
    }
    else{
        toSameLength(object);

        if(b > object.b){
            return true;
        }
        else
            return false;
    }
}

bool Fraction::isSmaller(Fraction object) {
    if(a < object.a){
        return true;
    }
    else if(a > object.a){
        return false;
    }
    else{
        toSameLength(object);

        if(b < object.b){
            return true;
        }
        else
            return false;
    }
}

bool Fraction::isSame(Fraction object) {
    if(a == object.a){
        toSameLength(object);

        if(b == object.b){
            return true;
        }
    }
    else
        return false;
}


std::string Fraction::toString() {
    std::string str;
    if(flag){
     str += "-";
    }

    str += std::to_string(a) + ".";

    if(null != 0){
        for(int i = 0; i < null; i++){
            str += "0";
        }
    }
    str += std::to_string(b);

    return str;
}