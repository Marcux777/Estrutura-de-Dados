#include <iostream>
using namespace std;

enum Color
{
    Black,
    Red
};

template <typename Trem>
class Node
{
public:
    Trem D;
    Node *left;
    Node *right;
    Node *parent;
    Color color;

    static Node *MontaNode(Trem dat)
    {
        Node<Trem> *P = new Node<Trem>;
        if (P)
        {
            P->D = dat;
            P->left = NULL;
            P->right = NULL;
            P->parent = NULL;
            P->color = Red;
        }
        return P;
    }

    static Trem DesmontaNode(Node *P)
    {
        Trem X;
        if (P)
        {
            X = P->D;
            delete P;
        }
        return X;
    }

    Node *uncle()
    {
        // If no parent or grandparent, then no uncle
        if (parent == NULL || parent->parent == NULL)
            return NULL;

        if (parent->isOnLeft())
            // uncle on right
            return parent->parent->right;
        else
            // uncle on left
            return parent->parent->left;
    }

    bool isOnLeft()
    {
        return this == parent->left;
    }

    Node *sibling()
    {
        if (parent == NULL)
            return NULL;

        if (isOnLeft())
            return parent->right;

        return parent->left;
    }

    void moveDown(Node *nParent)
    {
        if (parent != NULL)
        {
            if (isOnLeft())
            {
                parent->left = nParent;
            }
            else
            {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }

    bool hasRedChild()
    {
        return (left != NULL && left->color == Red) ||
               (right != NULL && right->color == Red);
    }
};