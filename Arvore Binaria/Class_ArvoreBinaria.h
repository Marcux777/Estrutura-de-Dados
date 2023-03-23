#include "Class_Node.h"
#include <stack>
#include <queue>

// Criando os metodos Node
template <typename Trem>
Node<Trem> *Node<Trem>::MontaNode(Trem dat)
{
    Node<Trem> *P = new Node<Trem>;
    if (P)
    {
        P->D = dat;
        P->left = NULL;
        P->right = NULL;
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

// Criando a classe da Arvore /Binaria
template <typename Trem>
class BTree
{
public:
    Node<Trem> *Root; // Nó raiz
    int N;            // Para Contar quantos nós temos

    // Metodos:
    BTree()
    {
        Root = NULL;
        N = 0;
    }
 
    ~BTree()
    {
        ClearBTree();
    }

    void ClearBTree()
    {
        LimpaArvore(Root);
    }

    bool IsEmpty()
    { // Verificar se está vazia
        return !Root;
    }

    Node<Trem> *search(Trem dat) // Buscar Item na arvore
    {
        return search(Root, dat);
    }

    Trem getMin()
    {
        Node<Trem> *P = Root;

        while (P != NULL && P->left != NULL)
        {
            P = P->left;
        }

        return P->D;
    }

    Trem getMax()
    {
        Node<Trem> *P = Root;

        while (P != NULL && P->right != NULL)
        {
            P = P->right;
        }

        return P->D;
    }

    void insertNaoRecursivo(Trem x) // Inserir na arvore iterativamente
    {
        Node<Trem> *p = Root;
        Node<Trem> *q = NULL;

        while (p != NULL)
        {
            q = p;
            if (x < p->D)
            {
                p = p->left;
            }
            else
            {
                if (x > p->D)
                {
                    p = p->right;
                }
                else
                {
                    return; // Elemento já existe na árvore
                }
            }
        }

        Node<Trem> *newNode = Node<Trem>::MontaNode(x);
        if (q == NULL)
        { // A árvore estava vazia, o novo nó será a raiz
            Root = newNode;
        }
        else
        {
            if (x < q->D)
            {
                q->left = newNode;
            }
            else
            {
                q->right = newNode;
            }
        }
        N++;
    }

    bool insertRecursivo(Trem x)
    {
        Root = insertRec(Root, x);
        N++;
        return true;
    }

    void InOrder()
    {
        PrintInOrder(Root);
    }

    void PreOrder()
    {
        PrintPreOrder(Root);
    }

    void PosOrder()
    {
        PrintPosOrder(Root);
    }

    void Breadthfirstsearch()
    {
        if (Root == NULL)
            return;

        queue<Node<Trem> *> q;
        q.push(Root);

        while (!q.empty())
        {
            Node<Trem> *p = q.front();
            q.pop();

            cout << p->D << " ";

            if (p->left != NULL)
                q.push(p->left);

            if (p->right != NULL)
                q.push(p->right);
        }
    }

    int DeaphTree()
    {
        return Profundidade(Root);
    }

    bool InsertLVLOrder(Trem x)
    {
        Root = InsertLVL(Root, x);
        N++;
        return true;
    }

    int MaxSumPath(Node<Trem> *P)
    {
        int X = -2147483647;

        int val = MaxSumP(P, X);

        if (P->left && P->right)
        {
            return X;
        }
        return maior(X, val);
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

    bool Espelhada(Node<Trem> *P)
    {
        if (!P)
        {
            return false; // Arvore Vazia
        }
        return IsEspelhada(P, P);
    }

    int size(){
        return N;
    }

private:
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

    bool IsEspelhada(Node<Trem> *R1, Node<Trem> *R2)
    {
        // If both trees are empty, then they are mirror images
        if (R1 == NULL && R2 == NULL)
            return true;
        if (R1 && R2 && R1->D == R2->D)
        {
            return IsEspelhada(R1->left, R2->right) && IsEspelhada(R1->right, R2->left);
        }
        return false;
    }

    void ImprimeLVLOrder(Node<Trem> *P, int Altura)
    {
        if (!P)
        {
            return;
        }
        if (Altura == 1)
        {
            cout << P->D << " ";
        }
        else
        {
            ImprimeLVLOrder(P->left, Altura - 1);
            ImprimeLVLOrder(P->right, Altura - 1);
        }
    }

    int MaxSumP(Node<Trem> *P, int &X)
    {
        if (!P)
        {
            return 0;
        }
        if (!P->left && !P->right)
        {
            return P->D;
        }

        int LadoEsq = MaxSumP(P->left, X);
        int LadoDir = MaxSumP(P->right, X);

        if (P->left && P->right)
        {
            X = maior(X, LadoEsq + LadoDir + P->D);

            return maior(LadoEsq, LadoDir) + P->D;
        }

        return (!P->left) ? LadoDir + P->D : LadoEsq + P->D;
    }

    int maior(int a, int b)
    {
        return (a >= b) ? a : b;
    }

    Node<Trem> *InsertLVL(Node<Trem> *P, Trem x)
    {
        if (!P)
        {
            return Node<Trem>::MontaNode(x);
        }

        queue<Node<Trem> *> q;
        q.push(P);

        while (!q.empty())
        {
            Node<Trem> *temp = q.front();
            q.pop();

            if (temp->left != NULL)
                q.push(temp->left);
            else
            {
                temp->left = Node<Trem>::MontaNode(x);
                return P;
            }

            if (temp->right != NULL)
                q.push(temp->right);
            else
            {
                temp->right = Node<Trem>::MontaNode(x);
                return P;
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

    Node<Trem> *insertRec(Node<Trem> *p, Trem x)
    {
        if (p == NULL)
        {
            return Node<Trem>::MontaNode(x);
        }
        if (x < p->D)
        {
            p->left = insertRec(p->left, x);
        }
        else
        {
            if (x > p->D)
            {
                p->right = insertRec(p->right, x);
            }
        }
        return p;
    }

    Node<Trem> *search(Node<Trem> *node, Trem dat)
    {
        if (node == NULL || node->D == dat)
        {
            return node;
        }

        if (dat < node->D)
        {
            return search(node->left, dat);
        }
        else
        {
            return search(node->right, dat);
        }
    }

    void LimpaArvore(Node<Trem> *P)
    {
        // Limpar a arvore
        if (!P)
        {
            if (P->left)
            {
                LimpaArvore(P->left);
            }
            if (P->right)
            {
                LimpaArvore(P->right);
            }
            Node<Trem>::DesmontaNode(P);
            return;
        }
    }
};