#include "Node.h"


template <typename Trem> Node<Trem> * Node<Trem>::MontaNode(Trem dat){
    Node<Trem> * P = new Node<Trem>;
    if(P){
        P -> D = dat;
        P -> Right = NULL;
        P -> Left = NULL;
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

template <typename Trem> class AVLTree{
    static void RSD(Node<Trem>*(&R));
    static void RSE(Node<Trem>*(&R));
    static void RDD(Node<Trem>*(&R));
    static void RDE(Node<Trem>*(&R));
    void Insert(Node<Trem> X){
        
    }
};