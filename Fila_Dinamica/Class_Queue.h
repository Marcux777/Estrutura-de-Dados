#include <iostream>
#include "Class_Node.h"
using namespace std;

// Criando os metodos Node
template <typename Trem>
Node<Trem> *Node<Trem>::MontaNode(Trem dat)
{
    Node *P = new Node;
    if (P)
    {
        P->D = dat;
        P->Next = NULL;
    }
    return P;
}
template <typename Trem>
Trem Node<Trem>::DesmontaNode(Node *P)
{
    Trem X;
    if (P)
    {
        X = P->D;
        delete P;
    }
    return X;
}

// Criando a Class Queue
template <typename Trem>
class Queue
{
public:
    Node<Trem> *head;
    Node<Trem> *tail;
    int N;
    
    Queue()
    {
        head = tail = NULL;
        N = 0;
    }
    
    ~Queue()
    {
        Node<Trem> *P = head;
        while (head)
        {
            head = P->Next;
            Node<Trem>::DesmontaNode(P);
            P = head;
        }
    }
    
    bool push(Trem x)
    {
        Node<Trem> *P = Node<Trem>::MontaNode(x);
        if (!P)
        {
            return false;
        }
        if (head)
        {
            tail->Next = P;
        }
        else
        {
            head = P;
        }
        tail = P;
        N++;
        return true;
    }
    
    Trem front()
    {
        Trem x;
        if (head)
        {
            x = head->D;
        }
        return x;
    }
    
    Trem pop()
    {
        Trem x;
        if (head)
        {
            Node<Trem> *P = head;
            head = head->Next;
            x = Node<Trem>::DesmontaNode(P);
            if (!head)
            {
                tail = NULL;
            }
            else
            {
                tail->Next = head;
            }
            N--;
        }
        return x;
    }
    
    int size()
    {
        return N;
    }
    
    bool empty()
    {
        return !head;
    }
    
    void clear()
    {
        Node<Trem> *P = head;
        while (head)
        {
            head = P->Next;
            Node<Trem>::DesmontaNode(P);
            P = head;
        }
        tail = N = NULL;
    }
};