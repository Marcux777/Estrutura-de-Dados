#include <iostream>
#include "Class_Queue.h"

using namespace std;

//Criando os metodos da Classe Fila
template <typename Trem> Queue<Trem>::Queue(){
    head = tail = NULL;
    N = 0;
}
template <typename Trem> Queue<Trem>::~Queue<Trem>(){
    Node<Trem>*P = head;
    while(head){
        head = P -> Next;
        Node<Trem>::DesmontaNode(P);
        P = head;
    }
}
template <typename Trem> Trem Queue<Trem>::front(){
    Trem x;
    if(head){
        x = head -> D;
    }
    return x;
}
template <typename Trem> bool Queue<Trem>::push(Trem x){
    Node<Trem> * P = Node<Trem>::MontaNode(x);
    if(!P){
        return false;
    }
    if(head){
        tail -> Next = P;
    }else{
        head = P;
    }
    tail = P;
    tail -> Next = 0;
    N++;
    return true;
}
template <typename Trem> Trem Queue<Trem>::pop(){
    Trem x;
    if(head){
        Node<Trem>*P = head;
        head = head -> Next;
        x = Node<Trem>::DesmontaNode(P);
        if(!head){
            tail = 0;
        }
        N--;
    }
    return x;
}
template <typename Trem> int Queue<Trem>::size(){
    return N;
}
template <typename Trem> bool Queue<Trem>::empty(){
    return !head;
}
template <typename Trem> void Queue<Trem>::clear(){
    Node<Trem> * P = head;
    while(head){
        head = P -> Next;
        Node<Trem>::DesmontaNode(P);
        P = head;
    }
    tail = N = NULL;
}

int main(){
    Queue<int>a;
    cout << "Tamanho da fila: " << a.size() << endl;
    a.push(3);
    a.push(4);
    cout << "Elemento da frente: " <<a.front() << endl;
    cout << "Tamanho da fila: " << a.size() << endl;
    a.pop();
    cout << "Elemento da frente: " << a.front() << endl;
}