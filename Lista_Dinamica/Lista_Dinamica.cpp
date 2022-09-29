#include <iostream>
#include "Class_List.h"

using namespace std;

template <typename Trem> List<Trem>::List{
    Head = NULL;
    N = 0;
}

template <typename Trem> List<Trem>::~List(){
    Node<Trem>*P;
    while(Head){
        P = Head -> Next;
        Node::DesmontaNode(Head);
        Head = P;
    }
}
template <typename Trem> bool List<Trem>::insert(Trem x){
    Node<Trem>*P = Node::MontaNode(x);
    if(!P){
        return false;
    }
    P -> Next = Head;
    Head = P;
    N++;
    return true;
}
