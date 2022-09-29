#include <iostream>
//#include "Class_Node.h"
using namespace std;

/*//Criando os metodos Node
template <typename Trem> Node<Trem> * Node<Trem>::MontaNode(Trem dat){
    Node * P = new Node;
    if(P){
        P -> D = dat;
        P -> Next = NULL;
    }
    return P;
}
template <typename Trem> Trem Node<Trem>::DesmontaNode(Node * P){
    Trem X;
    if(P){
        X = P -> D;
        delete P;
    }
    return X;
}*/

//Criando a Class Queue
template <typename Trem> class Queue{
    public:
    Node<Trem> * head;
    Node<Trem>* tail;
    int N;
    Queue();
    ~Queue();
    bool push(Trem x);
    Trem front();
    Trem pop();
    int size();
    bool empty();
    void clear();
};