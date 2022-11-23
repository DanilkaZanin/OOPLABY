//
// Created by danila on 11.10.22.
//

#include <iostream>
#include "Multiset.h"

Multiset::Node *Multiset::nodeInit(int value) {
    Node *list = new Node;
    list -> value = value;
    list -> count = 1;
    list -> next = nullptr;
    return list;
}

Multiset::Node *Multiset::nodeInit(int value, int count) {
    Node *list = new Node;
    list -> value = value;
    list -> count = count;
    list -> next = nullptr;
    return list;
}

void Multiset::pushBack(int value) {

    Node *mas1 = mas;

    while(true){
        if(mas1->value == value){
            mas1->count++;
            break;
        }

        else if(!mas1 -> next){
            Node *elem = nodeInit(value);
            mas1 -> next = elem;
            break;
        }
        mas1 = mas1 -> next;
    }

    Node *cur, *par;
    par = mas;
    cur = mas->next;
    if (par->value == value)
    {
        par->count++;
    }
    else
    {
        while (cur)
        {
            if (cur->value == value)
            {
                cur->count++;
                break;
            }
            par = cur;
            cur = cur->next;
        }
    }
    if (!cur)
        par->next = nodeInit(value);
}

void Multiset::pushBack(int value, int count) {
    Node *mas1 = mas;
    Node *elem = nodeInit(value,count);

    while(mas1 -> next){
        mas1 = mas1 -> next;
    }

    mas1 -> next = elem;
}

Multiset::Node *Multiset::findPrev(Multiset::Node *list) {
    Node *l1 = mas;

    if(l1 == list){
        return nullptr;
    }

    while(l1 -> next != list){
        l1 = l1 -> next;
    }
    return l1;
}

void Multiset::delElem(int value, int count) {
    Node *list = mas;

    while(list){
        if(list -> value == value){
            if(list -> count <= count){
              Node *prev = findPrev(list);

              if(prev){
                    prev -> next = list -> next;
                    delete list;
                    break;
              }

              else{
                  prev = mas;
                  mas = mas -> next;
                  delete prev;
                  break;
              }
            }

            else{
                list -> count -= count;
                break;
            }
        }
        list = list -> next;
    }


}


void Multiset::stringToMas(std::string str) {
    str += " ";

    std::string str1;
    int i = 0;

    while(str[i] == ' '){
        i++;
    }
    while(str[i] != ' '){
        str1 += str[i];
        i++;
    }

    mas = nodeInit(std::stoi(str1));
    str1 ="";

    for(; i< str.length(); i++){
        if(str[i] != ' '&& str[i + 1] == ' '){
            str1 +=str[i];
            pushBack(std::stoi(str1));
            str1 = "";
        }
        else if(str[i] != ' '){
            str1 += str[i];
        }
    }
}

void Multiset::clearMas() {
    Node *mas1;

    while(mas){
        if(!mas -> next){
            delete mas;
            mas = nullptr;
            break;
        }
        mas1 = mas;
        mas = mas->next;

        delete mas1;
    }
}
Multiset::Multiset() = default;

Multiset::Multiset(std::string str) {
    stringToMas(str);
}

Multiset::Multiset(Multiset &multiset) {
    Node *mas1 = multiset.mas;
    mas = nodeInit(mas1->value,mas1->count);

    mas1 = mas1 -> next;

    while(mas1){
        pushBack(mas1-> value,mas1->count);
        mas1 = mas1 -> next;
    }

}

Multiset::~Multiset() {
    Node *mas1;

    while(mas){
        if(!mas -> next){
            delete mas;
            mas = nullptr;
            break;
        }
        mas1 = mas;
        mas = mas->next;

        delete mas1;
    }
}
Multiset Multiset::operator + (Multiset multiset) {
    Node *mas1 = mas;
    Node *mas2 = multiset.mas;
    while(mas2){
        if(mas2 -> value == mas1 -> value){
            mas1 ->count += mas2-> count;

            mas1 = mas;
            mas2 = mas2 -> next;
        }
        else if(mas1 -> value != mas2 -> value && !mas1 -> next){
            Node *elem = nodeInit(mas2-> value, mas2->count);

            mas1 ->next = elem;

            mas1 = mas;
            mas2 = mas2 ->next;
        }
        mas1 = mas1->next;
    }
    return *this;
}

Multiset Multiset::operator-(Multiset multiset) {
    Node *mas1 = mas;
    Node *mas2 = multiset.mas;

    while(mas2){
        if(!mas1){
            mas1 = mas;
            mas2 = mas2 -> next;
        }

        else if(mas2 -> value == mas1 -> value){
            delElem(mas2->value,mas2->count);
            mas1 = mas;

            mas2 = mas2 ->next;

            continue;
        }

        mas1 = mas1 -> next;
    }
    return *this;
}

Multiset Multiset::operator*(Multiset multiset) {
    Node *mas1 = mas;
    Node *mas2 = multiset.mas;

    int value;
    int count;

    while (mas1){
        if(mas1 -> value == mas2 -> value){
            if(mas1 -> count == mas2 -> count){
                mas1 = mas1 -> next;
                mas2 = multiset.mas;
            }
            else if(mas1 -> count > mas2 -> count){
                mas1 -> count = mas2 -> count;

                mas1 = mas1 -> next;
                mas2 = multiset.mas;
            }
        }
        if(!mas2 -> next){
            value = mas1 -> value;
            count = mas1 -> count;

            mas1 = mas1 -> next;
            mas2 = multiset.mas;

            delElem(value, count);
        }
        mas2 = mas2 -> next;
    }
    return *this;
}

Multiset &Multiset::operator = (const Multiset &multiset) {
    clearMas();
    Node *mas1 = multiset.mas;
    mas = nodeInit(mas1->value,mas1->count);

    mas1 = mas1 -> next;

    while(mas1){
        pushBack(mas1-> value,mas1->count);
        mas1 = mas1 -> next;
    }

    return *this;
}

bool Multiset::operator==(Multiset multiset) {
    Node *mas1 = mas;
    Node *mas2 = multiset.mas;

    bool flag = false;

    while(mas1) {
        while (mas2) {
            if (mas2->value == mas1->value) {
                if (mas2->count == mas1->count) {
                    flag = true;
                    break;
                } else
                    break;
            }
            mas2 = mas2->next;
        }
        if(!flag)
            return false;
        else{
            flag = false;

            mas2 = multiset.mas;
            mas1 = mas1 -> next;
        }
    }

    return true;
}

bool Multiset::operator!=(Multiset multiset) {
    return !operator==(multiset);
}

std::ostream &operator << (std::ostream &os, Multiset &obj) {
    Multiset::Node *mas1 = obj.mas;

    while(mas1){
        os << "< " << mas1->value <<", " << mas1 -> count << " >" << '\n';
        mas1 = mas1 -> next;
    }
    return os;
}

std::istream &operator>>(std::istream &os, Multiset &obj) {
    std::string str;

    getline(os,str);
    obj.stringToMas(str);
    return os;
}

