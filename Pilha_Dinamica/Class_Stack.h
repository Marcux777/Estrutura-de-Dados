#include "Class_Node.h"

//Criando os metodos Node
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

//Classe Stack
template <typename Trem> class Stack{
    public:
        Node<Trem> * Top;
        int N;
        Stack();
        ~Stack();
        bool push(Trem X);
        Trem top();
        Trem pop();
        int size();
        bool empty();
};
