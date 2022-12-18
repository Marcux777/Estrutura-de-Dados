#include "Class_NodeD.h"

template <typename Trem> NodeD<Trem> * NodeD<Trem>::MontaNode(Trem dat){
    NodeD<Trem> * P = new NodeD<Trem>;
    if(P){
        P -> D = dat;
        P -> Next = NULL;
        P -> Prev = NULL;
    }
    return P;
}
template <typename Trem> Trem NodeD<Trem>::DesmontaNode(NodeD<Trem> * P){
    Trem X;
    if(P){
        X = P -> D;
        delete P;
    }
    return X;
}

//Classe Lista Duplamente Encadeada
template <typename Trem> class CList_DE{
    public:
        NodeD<Trem> * Head;
        NodeD<Trem> * It;
        int N;
        CList_DE(); //Feito
        ~CList_DE(); 
        bool Insert(Trem x); 
        bool Search(Trem x);
        bool Empty();
        void It_Begin();
        Trem Erase();
        void imprime_Lista();
};