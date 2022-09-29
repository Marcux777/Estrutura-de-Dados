#include <iostream>
#include "Class_Node.h"

using namespace std;

template <typename Trem> Node<Trem> * Node<Trem>::MontaNode(Trem dat){
    Node<Trem> * P = new Node<Trem>;
    if(P){
        P -> D = dat;
        P -> Next = NULL;
    }
    return P;
}
template <typename Trem> Trem Node<Trem>::DesmontaNode(Node<Trem> * P){
    Trem X;
    if(P){
        X = P -> D;
        delete P;
    }
    return X;
}

template <typename Trem> class List{
    public:
    Node<Trem> * Head;
    int N;
    List();
    ~List();
    bool insert(Trem x);
    bool search(int m, Trem * PX);
};