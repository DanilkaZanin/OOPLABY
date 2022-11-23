//Мультимножества. Множество представить в виде динамического массива.
#ifndef OOPLABY_MULTISET_H
#define OOPLABY_MULTISET_H


#include <ostream>

class Multiset {
private:
    struct Node{
        int value;
        int count;
        Node *next;
    };
    Node *mas = nullptr;

    Node *nodeInit(int value);
    Node *nodeInit(int value, int count);
    void pushBack(int value);
    void pushBack(int value, int count);
    Node *findPrev(Node *list);
    void delElem(int value, int count);
    void stringToMas(std::string str);
    void clearMas();
public:
    /**Конструктор по умолчанию */
    Multiset();
    /**Конструктор
    @param str - строка для формирования массива
    **/
    explicit Multiset(std::string str);
    /**Конструктор копирования
    @param multiset - объект класса Multiset для копирования
    **/
    Multiset(Multiset &multiset);
    /** Деструктор */
    ~Multiset();
    /** + (Объединение)
     По значению элемента multiset.mas -> value ищет значение в mas -> value. Если находит, то добавляет количество, если не находит, то добавляет новый элемент в конец

     @param multiset - объект класса Multiset
     @return *this
     **/
    Multiset operator + (Multiset multiset); // Объединение
    /**  - (Разность)
     * Ищет совпадения с объектом multiset если находит то смотрит на количество этих элементов. Если количество одинаковое, то удаляет элемент. Если количество больше,
     * то записывает в поле mas-> count разность.
     * @param multiset - объект класса Multiset
     * @return *this
     **/
    Multiset operator - (Multiset multiset); // Разность
    /**  * (Пересечение)
     Поочередно берет элементы из массива и ищет совпадение с multiset.mas. Если находит, то сравнивает их количество
     и присваивает наименьшее. Если совпадений не находит, то удаляет элемент.
     @param multiset - объект класса Multiset
     @return *this
     **/
    Multiset operator * (Multiset multiset); // Пересечение
    /**  = (Присваивание)
     Сначала очищает массив от имеющихся элементов. Далее заполняет его элементами объекта multiset
     @param multiset - константная ссылка на объект multiset
     @return *this
     */
    Multiset &operator = (const Multiset &multiset);
    /**
      == (Сравнение двух объектов)

     Циклом по очереди сравниваются элементы. Если находится элемент которого нету в другом массиве, то цикл останавливается.
     @param multiset - объект класса multiset
     @return
     true - если все элементы массива совпадают
     false - если не совпадают
     */
    bool operator == (Multiset multiset);
    /**
      != (Сравнение двух объектов)
     вызывает метод == и берет обратное значение
     @param multiset - объект класса multiset
     @return
     true - если элементы массива не совпадаю
     false - если совпадают
     */
    bool operator != (Multiset multiset);
    /**
     << (cout)
     Функция выводит значения элементов массива
     @param os - ссылка на объект метода ostream
     @param obj - ссылка на объект класса Multiset
     @return os
     */
    friend std::ostream &operator << (std::ostream &os, Multiset &obj);
    /**
     >> (cin)
     Записывает значения из консоли в строку и преобразовывает их в массив.
     @param os - ссылка на объект метода istream
     @param obj - ссылка на объект класса Multiset
     @return os
     */
    friend std::istream &operator >> (std::istream &os, Multiset &obj);

};

/*
Multiset multiset("1 2 3 5 6");
Multiset multiset1("1 3 2 7 8 9");
Multiset multiset2 = multiset1;
std::cout << multiset2 << multiset1;
int a = 1, b = 2;
a + b;
*/

#endif //OOPLABY_MULTISET_H
