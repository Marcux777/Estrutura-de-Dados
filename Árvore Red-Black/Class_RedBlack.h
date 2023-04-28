#include <iostream>
#include <queue>
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

template <typename Trem>
class RedBlackTree
{
    Node<Trem> *Root;

    void leftRotate(Node<Trem> *x)
    {
        Node<Trem> *nParent = x->right;

        if (x == Root)
            Root = nParent;

        x->moveDown(nParent);

        x->right = nParent->left;

        if (nParent->left != NULL)
            nParent->left->parent = x;

        nParent->left = x;
    }

    void rightRotate(Node<Trem> *x)
    {
        Node<Trem> *nParent = x->left;

        if (x == Root)
            Root = nParent;

        x->moveDown(nParent);

        x->left = nParent->right;

        if (nParent->right != NULL)
            nParent->right->parent = x;

        nParent->right = x;
    }

    void swapColors(Node<Trem> *x1, Node<Trem> *x2)
    {
        Color temp;
        temp = x1->color;
        x1->color = x2->color;
        x2->color = temp;
    }

    void swapValues(Node<Trem> *u, Node<Trem> *v)
    {
        Trem temp;
        temp = u->D;
        u->D = v->D;
        v->D = temp;
    }

    void fixRedRed(Node<Trem> *x)
    {
        // se x é a raiz, colore-a de preto e retorna
        if (x == Root)
        {
            Root->color = Black;
            return;
        }
        // inicializa pai, avô e tio
        Node<Trem> *parent = x->parent, *grandparent = parent->parent,
                   *uncle = x->uncle();

        if (parent->color != Black)
        {
            if (uncle != NULL && uncle->color == Red)
            {
                // tio vermelho, realiza recoloração e recursão
                parent->color = Black;
                uncle->color = Black;
                grandparent->color = Red;
                fixRedRed(grandparent);
            }
            else
            {
                // Senão, realiza LR, LL, RL, RR
                if (parent->isOnLeft())
                {
                    if (x->isOnLeft())
                    {
                        // para esquerda-direita
                        swapColors(parent, grandparent);
                    }
                    else
                    {
                        leftRotate(parent);
                        swapColors(x, grandparent);
                    }
                    // para esquerda-esquerda e esquerda-direita
                    rightRotate(grandparent);
                }
                else
                {
                    if (x->isOnLeft())
                    {
                        // para direita-esquerda
                        rightRotate(parent);
                        swapColors(x, grandparent);
                    }
                    else
                    {
                        swapColors(parent, grandparent);
                    }

                    // para direita-direita e direita-esquerda
                    leftRotate(grandparent);
                }
            }
        }
    }

    Node<Trem> *successor(Node<Trem> *x)
    {
        Node<Trem> *temp = x;

        while (temp->left != NULL)
            temp = temp->left;

        return temp;
    }

    Node<Trem> *Replace(Node<Trem> *x)
    {
        // quando o nó tem 2 filhos
        if (x->left != NULL && x->right != NULL)
            return successor(x->right);

        // quando é folha
        if (x->left == NULL && x->right == NULL)
            return NULL;

        // quando tem um filho
        if (x->left != NULL)
            return x->left;
        else
            return x->right;
    }

    void deleteNode(Node<Trem> *v)
    {
        Node<Trem> *u = Replace(v);

        bool uvBlack = ((u == NULL || u->color == Black) && (v->color == Black));
        Node<Trem> *parent = v->parent;

        if (u == NULL)
        {
            if (v == Root)
            {
                Root = NULL;
            }
            else
            {
                if (uvBlack)
                {
                    fixDoubleBlack(v);
                }
                else
                {
                    if (v->sibling() != NULL){
                        v->sibling()->color = Red;
                    }
                }

                if (v->isOnLeft())
                {
                    parent->left = NULL;
                }
                else
                {
                    parent->right = NULL;
                }
            }
            Node<Trem>::DesmontaNode(v);
            return;
        }

        if (v->left == NULL || v->right == NULL)
        {
            if (v == Root)
            {
                v->D = u->D;
                v->left = v->right = NULL;
                Node<Trem>::DesmontaNode(u);
            }
            else
            {
                if (v->isOnLeft())
                {
                    parent->left = u;
                }
                else
                {
                    parent->right = u;
                }
                Node<Trem>::DesmontaNode(v);
                u->parent = parent;
                if (uvBlack)
                {
                    fixDoubleBlack(u);
                }
                else
                {
                    u->color = Black;
                }
            }
            return;
        }

        swapValues(u, v);
        deleteNode(u);
    }

    void fixDoubleBlack(Node<Trem> *x)
    {
        if (x == Root)
            return;

        Node<Trem> *sibling = x->sibling();
        Node<Trem> *parent = x->parent;
        if (sibling == NULL)
        {
            fixDoubleBlack(parent);
        }
        else
        {
            if (sibling->color == Red)
            {
                parent->color = Red;
                sibling->color = Black;
                if (sibling->isOnLeft())
                {
                    rightRotate(parent);
                }
                else
                {
                    leftRotate(parent);
                }
                fixDoubleBlack(x);
            }
            else
            {
                if (sibling->hasRedChild())
                {
                    if (sibling->left && sibling->left->color == Red)
                    {
                        if (sibling->isOnLeft())
                        {
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }
                        else
                        {
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling->isOnLeft())
                        {
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                        else
                        {
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                    }
                    parent->color = Black;
                }
                else
                {
                    sibling->color = Red;
                    if (parent->color == Black)
                        fixDoubleBlack(parent);
                    else
                        parent->color = Black;
                }
            }
        }
    }

    void PrintPosOrder(Node<Trem> *P)
    {
        if (P)
        {
            PrintPosOrder(P->left);
            PrintPosOrder(P->right);
            cout << P->D << " ";
        }
        return;
    }

    void PrintPreOrder(Node<Trem> *P)
    {
        if (P)
        {
            cout << P->D << " ";
            PrintPreOrder(P->left);
            PrintPreOrder(P->right);
        }
        return;
    }

    void PrintInOrder(Node<Trem> *P)
    {
        if (P)
        {
            PrintInOrder(P->left);
            cout << P->D << " ";
            PrintInOrder(P->right);
        }
        return;
    }

    int Profundidade(Node<Trem> *P)
    {
        if (!P)
        {
            return 0;
        }
        int esquerda = Profundidade(P->left);
        int direita = Profundidade(P->right);

        if (esquerda > direita)
        {
            return esquerda + 1;
        }
        return direita + 1;
    }

    void ImprimeLVLOrder(Node<Trem> *P, int Altura)
    {
        if (!P)
        {
            return;
        }
        if (Altura == 1)
        {
            cout << P->D << " " << P->color << " ";
        }
        else
        {
            ImprimeLVLOrder(P->left, Altura - 1);
            ImprimeLVLOrder(P->right, Altura - 1);
        }
    }

    void ClearRedBlackTree(Node<Trem>* P){
        if(!P){
            return;
        }

        ClearRedBlackTree(P->left);
        ClearRedBlackTree(P->right);
        Node<Trem>::DesmontaNode(P);
    }

public:
    RedBlackTree()
    {
        Root = NULL;
    }

    ~RedBlackTree(){
        ClearRedBlackTree(Root);
    }

    void Clear(){
        ClearRedBlackTree(Root);
    }

    void ImprimeLVLOrder(Node<Trem> *P)
    {
        int h = Profundidade(P);
        for (int i = 1; i <= h; i++)
        {
            cout << "Level " << i << ": ";
            ImprimeLVLOrder(P, i);
            cout << endl;
        }
    }

    Node<Trem> *getRoot()
    {
        return Root;
    }

    Node<Trem> *search(Trem n)
    {
        Node<Trem> *temp = Root;
        while (temp != NULL)
        {
            if (n < temp->D)
            {
                if (temp->left == NULL)
                    break;
                else
                    temp = temp->left;
            }
            else if (n == temp->D)
            {
                break;
            }
            else
            {
                if (temp->right == NULL)
                    break;
                else
                    temp = temp->right;
            }
        }

        return temp;
    }

    void Insert(Trem n)
    {
        Node<Trem> *newNode = Node<Trem>::MontaNode(n);
        if (Root == NULL)
        {
            newNode->color = Black;
            Root = newNode;
            return;
        }
        Node<Trem> *temp = search(n);

        if (temp->D == n)
        {
            return;
        }

        newNode->parent = temp;

        if (n < temp->D)
            temp->left = newNode;
        else
            temp->right = newNode;

        fixRedRed(newNode);
    }

    void DeleteValor(Trem n)
    {
        if (Root == NULL)
            return;

        Node<Trem> *v = search(n);

        deleteNode(v);
    }

    void InOrder()
    {
        PrintInOrder(Root);
        cout << endl;
    }

    void PreOrder()
    {
        PrintPreOrder(Root);
        cout << endl;
    }

    void PosOrder()
    {
        PrintPosOrder(Root);
        cout << endl;
    }
};
