#include <iostream>
#include "Class_List.h"

using namespace std;

int main()
{
    List<int> list;
    list.insertFront(1);
    list.insertFront(2);
    list.insertFront(3);
    list.Print(); // Output: 3 2 1
    list.RemoveFront();
    list.Print(); // Output: 2 1
    list.removeValor(2);
    list.Print(); // Output: 1
    list.RemoveFront();
    list.Print();
    return 0;
}