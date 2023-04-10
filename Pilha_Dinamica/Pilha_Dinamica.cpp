#include <iostream>
#include "Class_Stack.h"

using namespace std;

int main()
{
    Stack<int> a1;
    a1.push(3);
    cout << a1.empty() << endl;
    cout << a1.top() << endl;
    cout << a1.size() << endl;
    a1.pop();
    cout << a1.empty() << endl;
    cout << a1.size() << endl;
}
