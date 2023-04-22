#include <iostream>
#include "Class_Node.h"

using namespace std;

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

template <typename Trem>
class List
{
public:
    Node<Trem> *Head;
    int N;
    List()
    {
        Head = NULL;
        N = 0;
    }

    ~List()
    {
        Node<Trem> *P;
        while (Head)
        {
            P = Head->Next;
            Node<Trem>::DesmontaNode(Head);
            Head = P;
        }
    }

    int size()
    {
        return N;
    }

    bool insertFront(Trem x)
    {
        Node<Trem> *P = Node<Trem>::MontaNode(x);
        if (!P)
        {
            return false;
        }
        P->Next = Head;
        Head = P;
        N++;
        return true;
    }

    bool insertAfter(Node<Trem> *Prev, Trem x)
    { // Insere depois do nó passado como parametro
        if (!Prev)
        {
            return false;
        }
        Node<Trem> *P = Node<Trem>::MontaNode(x);
        if (!P)
        {
            return false;
        }
        P->Next = Prev->Next;
        Prev->Next = P;
        N++;
        return true;
    }

    bool insertLast(Node<Trem> **head, Trem x)
    { // Insere no fim da lista
        Node<Trem> *P = Node<Trem>::MontaNode(x);
        Node<Trem> *Last = *head;
        if (!(*head))
        {
            *head = P;
            N++;
            return true;
        }
        while (Last->Next)
        {
            Last->Next;
        }
        Last->Next = P;
        N++;
        return true;
    }

    bool search(int m)
    {
        Node<Trem> *P = Head;
        if (!P)
        {
            return false;
        }

        while (P->D != m)
        {
            P = P->Next;
        }
        if (!P)
        {
            return false;
        }
        return true;
    }

    void reverseList()
    {
        Node<Trem> *Aux = Head;
        Node<Trem> *Next = NULL;
        Node<Trem> *Prev = NULL;

        while (!Aux)
        {
            Next = Aux->Next;
            Aux->Next = Prev;
            Prev = Aux;
            Aux = Next;
        }
        Head = Prev;
    }

    void RemoveFront()
    {
        if (!Head)
        {
            return;
        }
        Node<Trem> *P = Head;
        Head = Head->Next;
        Node<Trem>::DesmontaNode(P);
    }

    void RemovePosition(int Position)
    {
        Node<Trem> *Aux = Head;
        Node<Trem> *Prev = Head;
        for (int i = 0; i < Position && Prev; i++)
        {
            if (i == 0 && Position == 1)
            {
                Head = Head->Next;
                Node<Trem>::DesmontaNode(Prev);
            }
            else
            {
                if (i == Position - 1 && Aux)
                {
                    Prev->next = Aux->next;
                    Node<Trem>::DesmontaNode(Aux);
                }
                else
                {
                    Prev = Aux;
                    Aux = Aux->next;
                }
            }
        }
    }

    void removeValor(int V)
    {
        if (!Head)
        {
            return;
        }
        Node<Trem> *P = Head;
        Node<Trem> *Ant = NULL;
        while (P)
        {
            if (P->D == V)
            {
                if (Ant == NULL)
                {
                    Head = P->Next;
                }
                else
                {
                    Ant->Next = P->Next;
                }
                Node<Trem>::DesmontaNode(P);
            }
            else
            {
                Ant = P->Next;
                P = P->Next;
            }
            P = Ant;
        }
    }

    void Print()
    {
        Node<Trem> *curr = Head;
        while (curr != NULL)
        {
            cout << curr->D << " ";
            curr = curr->Next;
        }
        cout << endl;
    }

    int SearchIndex(int Index)
    {
        if (Index >= N)
        {
            return INT64_MIN;
        }
        Node<Trem> *P = Head;
        int cont = 0;
        while (P)
        {
            if (cont == Index)
            {
                return P->D;
            }
            cont++;
            P = P->Next;
        }
    }
};