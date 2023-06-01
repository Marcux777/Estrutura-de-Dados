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
        P->fb = 0;
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

// Criando a classe da Arvore AVL
template <typename Trem>
class AVLTree
{
private:
    int GetHeight(Node<Trem> *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return node->fb;
    }

    int GetBalanceFactor(Node<Trem> *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return GetHeight(node->left) - GetHeight(node->right);
    }

    void UpdateHeight(Node<Trem> *node)
    {
        int leftHeight = GetHeight(node->left);
        int rightHeight = GetHeight(node->right);
        node->fb = max(leftHeight, rightHeight) + 1;
    }

    Node<Trem> *RotateLeft(Node<Trem> *node)
    {
        Node<Trem> *newRoot = node->right;
        node->right = newRoot->left;
        newRoot->left = node;
        UpdateHeight(node);
        UpdateHeight(newRoot);
        return newRoot;
    }

    Node<Trem> *RotateRight(Node<Trem> *node)
    {
        Node<Trem> *newRoot = node->left;
        node->left = newRoot->right;
        newRoot->right = node;
        UpdateHeight(node);
        UpdateHeight(newRoot);
        return newRoot;
    }

    Node<Trem> *Balance(Node<Trem> *node)
    {
        UpdateHeight(node);
        int balanceFactor = GetBalanceFactor(node);

        if (balanceFactor > 1)
        {
            if (GetBalanceFactor(node->left) < 0)
            {
                node->left = RotateLeft(node->left);
            }
            return RotateRight(node);
        }
        if (balanceFactor < -1)
        {
            if (GetBalanceFactor(node->right) > 0)
            {
                node->right = RotateRight(node->right);
            }
            return RotateLeft(node);
        }
        return node;
    }

    Node<Trem> *Insert(Node<Trem> *root, Trem value)
    {
        if (root == NULL)
        {
            // A árvore está vazia, então criamos um novo nó
            return Node<Trem>::MontaNode(value);
        }

        if (value < root->D)
        {
            // O valor é menor do que o valor do nó atual, então inserimos na subárvore esquerda
            root->left = Insert(root->left, value);
        }
        else if (value > root->D)
        {
            // O valor é maior do que o valor do nó atual, então inserimos na subárvore direita
            root->right = Insert(root->right, value);
        }
        else
        {
            // O valor já existe na árvore, não fazemos nada
            return root;
        }

        // Atualizamos a altura do nó
        UpdateHeight(root);

        // Verificamos e realizamos as rotações necessárias para balancear a árvore
        root = Balance(root);

        return root;
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

    void PrintLevelOrder(Node<Trem> *root)
    {
        if (root == NULL)
        {
            return;
        }

        queue<Node<Trem> *> q;
        q.push(root);

        int level = 1;
        int nodesInCurrentLevel = 1;
        int nodesInNextLevel = 0;

        cout << "Level " << level << " - ";

        while (!q.empty())
        {
            Node<Trem> *current = q.front();
            q.pop();

            cout << current->D << " ";
            nodesInCurrentLevel--;

            if (current->left != NULL)
            {
                q.push(current->left);
                nodesInNextLevel++;
            }

            if (current->right != NULL)
            {
                q.push(current->right);
                nodesInNextLevel++;
            }

            if (nodesInCurrentLevel == 0)
            {
                // Todos os nós do nível atual foram visitados
                cout << endl;

                if (nodesInNextLevel > 0)
                {
                    // Existem mais nós para imprimir no próximo nível
                    level++;
                    cout << "Level " << level << " - ";
                    nodesInCurrentLevel = nodesInNextLevel;
                    nodesInNextLevel = 0;
                }
            }
        }
    }

    Node<Trem> *minValueNode(Node<Trem> *node)
    {
        Node<Trem> *current = node;

        while (current->left != NULL)
            current = current->left;

        return current;
    }

    int max(int a, int b)
    {
        return (a > b) ? a : b;
    }

    Node<Trem> *deleteNode(Node<Trem> *root, int key)
    {
        if (root == NULL)
            return root;

        if (key < root->D)
            root->left = deleteNode(root->left, key);
        else if (key > root->D)
            root->right = deleteNode(root->right, key);
        else
        {
            if (root->left == NULL || root->right == NULL)
            {
                Node<Trem> *temp = root->left ? root->left : root->right;

                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                    *root = *temp;

                Node<Trem>::DesmontaNode(temp);
            }
            else
            {
                Node<Trem> *temp = minValueNode(root->right);
                root->D = temp->D;
                root->right = deleteNode(root->right, temp->D);
            }
        }

        if (root == NULL)
            return root;

        root->fb = 1 + max(GetHeight(root->left), GetHeight(root->right));

        int balance = GetBalanceFactor(root);

        if (balance > 1 && GetBalanceFactor(root->left) >= 0)
            return RotateRight(root);

        if (balance > 1 && GetBalanceFactor(root->left) < 0)
        {
            root->left = RotateLeft(root->left);
            return RotateRight(root);
        }

        if (balance < -1 && GetBalanceFactor(root->right) <= 0)
            return RotateLeft(root);

        if (balance < -1 && GetBalanceFactor(root->right) > 0)
        {
            root->right = RotateRight(root->right);
            return RotateLeft(root);
        }

        return root;
    }

    Node<Trem> *Search(Node<Trem> *root, Trem value)
    {
        if (root == NULL || root->D == value)
        {
            return root;
        }

        if (value < root->D)
        {
            return Search(root->left, value);
        }
        else
        {
            return Search(root->right, value);
        }
    }

public:
    Node<Trem> *Root;
    int N;
    AVLTree()
    {
        Root = NULL;
        N = 0;
    }

    void Insert(Trem value)
    {
        Root = Insert(Root, value);
        N++;
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

    void LevelOrder()
    {
        PrintLevelOrder(Root);
    }

    void Remove(Trem value)
    {
        Root = deleteNode(Root, value);
        N--;
    }

    bool Search(Trem value)
    {
        Node<Trem> *result = Search(Root, value);
        return result != NULL;
    }
};