#include "Class_CListDE.h"


template <typename Trem> CList_DE<Trem>::CList_DE(){
    Head = It = NULL;
    N = 0;
}

template <typename Trem> CList_DE<Trem>::~CList_DE(){
    
}

template <typename Trem> bool CList_DE<Trem>::Insert(Trem x){
    NodeD<Trem>* P = NodeD<Trem>::MontaNode(x);
    if(!P){
        return false;
    }
    if(!Head){
        Head = It = P->Next = P->Prev = P;
    }else{
        P -> Prev = Head -> Prev;
        P -> Next = Head;
        (Head -> Prev) -> Next = P;
        Head -> Prev = P;
        Head = P;
    }
    N++;
    return true;
}

template <typename Trem> bool CList_DE<Trem>::Search(Trem x){
    if(!Head){
        return false;
    }
    It = It->Next;
    while(It != Head && (It->D) != x){
        It = It->Next;
    }
    if((It->D) == x){
        return true;
    }
    return false;
}

template <typename Trem> Trem CList_DE<Trem>::Erase(){
    Trem x;
    if(!Head){
        return x;
    }
    NodeD<Trem>* Aux = It;
    if(It->Next != It){
        (It->Next)->Prev = It->Prev;
        (It->Prev)->Next = It->Next;
    }else{
        Head = NULL;
    }
    if(Head == It){
        Head = It = It->Next;
    }else{
        It = It->Next;
    }
    x = NodeD<Trem>::DesmontaNode(Aux);
    N--;
    return x;
}

template <typename Trem> bool CList_DE<Trem>::Empty(){
    return !Head;
}

template <typename Trem> void CList_DE<Trem>::It_Begin(){
    It = Head;
}

template <typename Trem> void CList_DE<Trem>::imprime_Lista(){
    if(!Head){
        return;
    }
    It = Head->Next;
    while(It != Head){
        cout << It->D;
        It = It->Next;
    }
}

int main(){
    CList_DE<int> Lista;
    cout << Lista.Empty() << endl;
    for(int i = 0; i < 10; i++){
        Lista.Insert(i);
    }
    Lista.imprime_Lista();
}