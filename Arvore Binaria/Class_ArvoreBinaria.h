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

    long long int MaxSumPath(Node<Trem> *P)
    {
        long long int X = INT64_MIN;

        long long int val = MaxSumP(P, X);

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

    int size()
    {
        return N;
    }

    void Delete(Trem x)
    {
        removeNode(Root, x);
        N--;
    }

    void BurnTree(Trem destino)
    {
        Node<Trem> *P = Root;
        queue<Node<Trem> *> fila;

        // Chamada de função
        burnTree(P, destino, fila);

        // O loop while é executado até que a fila esteja vazia
        while (!fila.empty())
        {
            int tamanhoFila = fila.size();
            while (tamanhoFila--)
            {
                Node<Trem> *temp = fila.front();

                // Imprimir os nós queimados
                cout << temp->D;

                // Remove o nó da árvore
                // removeNode(Root, temp->D);

                // Inserir o filho esquerdo na fila, se existir
                if (temp->left)
                {
                    fila.push(temp->left);
                }
                // Inserir o filho direito na fila, se existir
                if (temp->right)
                {
                    fila.push(temp->right);
                }

                if (fila.size() != 1)
                {
                    cout << " ";
                }

                fila.pop();
            }
        }
        cout << endl;
    }

private:
    int burnTree(Node<Trem> *P, Trem destino, queue<Node<Trem> *> &q)
    {
        // Base, pra retornar caso chegue em algum nó nulo
        if (!P)
        {
            return 0;
        }

        // Verifica se o nó alvo foi encontrado
        if (P->D == destino)
        {
            cout << P->D << " ";

            // Busca e Remove o nó queimado da minha árvore OBS: NÃO CONSEGUI REMOVER
            // removeNode(Root, P->D);

            if (P->left)
            {
                q.push(P->left);
            }
            if (P->right)
            {
                q.push(P->right);
            }

            // Retorna 1 para evitar overflow
            return 1;
        }
        // Primeiro lado esquerdo
        int a = burnTree(P->left, destino, q);

        if (a == 1)
        {
            int qsize = q.size();

            // Executa o loop enquanto a fila não estiver vazia
            while (qsize--)
            {
                Node<Trem> *temp = q.front();

                // Imprime os nós queimados
                cout << temp->D << " ";

                // Busca e Remove o nó queimado da minha árvore OBS: NÃO CONSEGUI REMOVER
                // removeNode(Root, temp->D);

                q.pop();

                // Verifica a condição para a subarvore esquerda
                if (temp->left)
                {
                    q.push(temp->left);
                }

                // Verifica a condição para a subarvore direita
                if (temp->right)
                {
                    q.push(temp->right);
                }
            }

            if (P->right)
            {
                q.push(P->right);
            }

            cout << P->D << " ";

            // Busca e Remove o nó queimado da minha árvore OBS: NÃO CONSEGUI REMOVER
            // removeNode(Root, P->D);

            // Retorna 1 para evitar overflow
            return 1;
        }

        // Agora o lado direito
        int b = burnTree(P->right, destino, q);

        if (b == 1)
        {
            int qsize = q.size();
            // Executa o loop enquanto a fila não estiver vazia

            while (qsize--)
            {
                Node<Trem> *temp = q.front();

                // Imprime os nós queimados
                cout << temp->D << " ";

                // Busca e Remove o nó queimado da minha árvore OBS: NÃO CONSEGUI REMOVER
                // removeNode(Root, temp->D);

                q.pop();

                // Verifica a condição para a subárvore esquerda
                if (temp->left)
                {
                    q.push(temp->left);
                }

                // Verifica a condição para a subárvore direita
                if (temp->right)
                {
                    q.push(temp->right);
                }
            }

            if (P->left)
            {
                q.push(P->left);
            }

            cout << P->D << " ";

            // Busca e Remove o nó queimado da minha árvore OBS: NÃO CONSEGUI REMOVER
            // removeNode(Root, P->D);

            // Retorna 1 para evitar chamadas adicionais da função
            return 1;
        }
    }
 
    Node<Trem> *findMinNode(Node<Trem> *P)
    {
        Node<Trem> *q = P;
        while (q && q->left != NULL)
        {
            q = q->left;
        }
        return q;
    }

    Node<Trem> *removeNode(Node<Trem> *P, Trem key)
    {
        if (P == NULL)
        {
            return P;
        }
        else
        {
            if (key < P->D)
            {
                P->left = removeNode(P->left, key);
            }
            else
            {
                if (key > P->D)
                {
                    P->right = removeNode(P->right, key);
                }
                else
                {
                    if (P->left == NULL)
                    {
                        Node<Trem> *temp = P->right;
                        Node<Trem>::DesmontaNode(P);
                        return temp;
                    }
                    else
                    {
                        if (P->right == NULL)
                        {
                            Node<Trem> *temp = P->left;
                            Node<Trem>::DesmontaNode(P);
                            return temp;
                        }
                        else
                        {
                            Node<Trem> *temp = findMinNode(P->right);
                            P->D = temp->D;
                            P->right = removeNode(P->right, temp->D);
                        }
                    }
                }
            }
        }
        return P;
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

    long long int MaxSumP(Node<Trem> *P, long long int &X)
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

    long long int maior(long long int a, long long int b)
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