#include <iostream>
#include "Class_Stack.h"

using namespace std;

//Criando os metodos da Stack
template <typename Trem> Stack<Trem>::Stack(){
    Top = NULL;
    N = 0;
}
template <typename Trem> bool Stack<Trem>::push(Trem X){
    Node<Trem> * P = Node<Trem>::MontaNode(X);
    if(!P){
        return false;
    }
    P -> Next = Top;
    Top = P;
    N++;
    return true;
}
template <typename Trem> Trem Stack<Trem>::top(){
    Trem X;
    if(Top){
        X = Top -> D;
    }
    return X;
}
template <typename Trem> int Stack<Trem>::size(){
    return N;
}
template <typename Trem> bool Stack<Trem>::empty(){
    return !Top;
}
template <typename Trem> Trem Stack<Trem>::pop(){
    Trem X;
    if(Top){
        Node<Trem> * P = Top;
        Top = Top -> Next;
        X = Node<Trem>::DesmontaNode(P);
        N--;
    }
    return X;
}
template <typename Trem> Stack<Trem>::~Stack<Trem>(){
    Node<Trem> *P;
    while(Top){
		P = Top;
		Top = Top -> Next;
		Node<Trem>::DesmontaNode(P);
	}
}

int main(){
    Stack<int> a1;
    a1.push(3);
    cout << a1.empty() << endl;
    cout << a1.top() << endl;
    cout << a1.size() << endl;
	a1.pop();
    cout << a1.empty() << endl;
    cout << a1.size() << endl;
}
