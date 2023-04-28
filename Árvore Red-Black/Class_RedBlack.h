#include <iostream>
#include "Class_Node.h"
#include <queue>
using namespace std;

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
        /*começa verificando se o nó em questão é a raiz da árvore.
        Caso positivo, ele colore a raiz de preto e retorna.
        Caso contrário, o método utiliza as propriedades da árvore red-black
        para realizar as operações de balanceamento necessárias para manter
        a árvore balanceada e preservar as suas propriedades.*/

        /*Se o nó pai não é preto,
        isso indica que ocorreu uma violação da propriedade da árvore red-black,
        e o método verifica se o tio (irmão do pai) é vermelho.
        Se o tio é vermelho, o método realiza uma recoloração para balancear a árvore e,
        em seguida, realiza uma recursão para verificar
        se a operação de balanceamento afetou outros nós da árvore.*/

        /*se o tio é preto ou inexistente,
        o método realiza as operações de rotação necessárias para equilibrar a árvore,
        dependendo da posição do nó em relação ao pai e ao avô.
        Se o nó estiver na posição esquerda-esquerda ou direita-direita,
        o método realiza uma rotação à direita ou à esquerda, respectivamente.
        Se o nó estiver na posição esquerda-direita ou direita-esquerda,
        o método realiza duas rotações: uma à esquerda ou à direita,
        seguida de uma à direita ou à esquerda, respectivamente.*/

        // se x é a raiz, colore-a de preto e retorna
        if (x == Root)
        {
            Root->color = Black;
            return;
        }
        // inicializa pai, avô e tio
        Node<Trem> *parent = x->parent, *grandparent = parent->parent,
                   *uncle = x->uncle();

        if (parent->color != Black) // se o pai não é preto
        {
            if (uncle != NULL && uncle->color == Red) // se tem tio e ele é red
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
                    if (v->sibling() != NULL)
                    {
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
        /*a função verifica o irmão de x usando o método sibling().
        Se o irmão de x for nulo, significa que o irmão é um nó nulo,
        então a função chama fixDoubleBlack com o pai de x.
        Caso contrário, há três possibilidades:

        1 - O irmão de x é vermelho: nesse caso, a função troca as cores do pai e do irmão de x,
        e em seguida realiza uma rotação simples na direção oposta ao lado do irmão de x.
        Então, a função chama fixDoubleBlack com x novamente.

        2 - O irmão de x é preto e tem pelo menos um filho vermelho:
        nesse caso, a função verifica se o filho vermelho do irmão de x está no mesmo lado do irmão de x
        em relação ao pai de x. Se estiver,
        a função realiza uma rotação simples na direção oposta ao lado do irmão de x
        e troca as cores do pai, irmão de x e filho vermelho.
        Caso contrário, a função realiza uma rotação dupla:
        primeiro uma rotação simples no mesmo lado do irmão de x,
        seguida por uma rotação simples no lado oposto do irmão de x.
        Novamente, a função troca as cores do pai, irmão de x e filho vermelho.
        Em ambos os casos, a função define a cor do pai como preta.

        3 - O irmão de x é preto e não tem filho vermelho: nesse caso, 
        a função simplesmente define a cor do irmão de x como vermelha 
        e chama fixDoubleBlack com o pai de x. 
        Se o pai de x for preto, a função define a cor do pai como vermelha, 
        caso contrário, define a cor do pai como preta.*/

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

    void ClearRedBlackTree(Node<Trem> *P)
    {
        if (!P)
        {
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

    ~RedBlackTree()
    {
        ClearRedBlackTree(Root);
    }

    void Clear()
    {
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
