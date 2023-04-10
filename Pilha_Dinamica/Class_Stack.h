#include "Class_Node.h"

// Criando os metodos Node
template <typename Trem>
Node<Trem> *Node<Trem>::MontaNode(Trem dat)
{
    Node<Trem> *P = new Node<Trem>;
    if (P)
    {
        P->D = dat;
        P->Next = NULL;
    }
    return P;
}
template <typename Trem>
Trem Node<Trem>::DesmontaNode(Node<Trem> *P)
{
    Trem X;
    if (P)
    {
        X = P->D;
        delete P;
    }
    return X;
}

// Classe Stack
template <typename Trem>
class Stack
{
public:
    Node<Trem> *Top;
    int N;
    Stack()
    {
        Top = NULL;
        N = 0;
    }
    ~Stack()
    {
        Node<Trem> *P;
        while (Top)
        {
            P = Top;
            Top = Top->Next;
            Node<Trem>::DesmontaNode(P);
        }
    }
    bool push(Trem X)
    {
        Node<Trem> *P = Node<Trem>::MontaNode(X);
        if (!P)
        {
            return false;
        }
        P->Next = Top;
        Top = P;
        N++;
        return true;
    }
    Trem top()
    {
        Trem X;
        if (Top)
        {
            X = Top->D;
        }
        return X;
    }
    Trem pop()
    {
        Trem X;
        if (Top)
        {
            Node<Trem> *P = Top;
            Top = Top->Next;
            X = Node<Trem>::DesmontaNode(P);
            N--;
        }
        return X;
    }
    int size()
    {
        return N;
    }
    bool empty()
    {
        return !Top;
    }
};
