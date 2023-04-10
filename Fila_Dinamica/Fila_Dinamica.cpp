#include <iostream>
#include "Class_Queue.h"

using namespace std;

int main()
{
    Queue<int> a;
    cout << "Tamanho da fila: " << a.size() << endl;
    a.push(3);
    a.push(4);
    cout << "Elemento da frente: " << a.front() << endl;
    cout << "Tamanho da fila: " << a.size() << endl;
    a.pop();
    cout << "Elemento da frente: " << a.front() << endl;
}