#include "Class_Node.h"
#include <stack>
#include <string>

using namespace std;

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

template <typename Trem>
class ExpTree
{
public:
    Node<Trem> *Root; // Raiz da árvore
    int N;            // Para Contar quantos nós temos

    void Insert(string s)
    {
        Root = MontaArvore(s);
    }

    void ImprimeLVLOrder(Node<Trem> *P, int nivel = 0)
    {
        if (!P)
        {
            return;
        }
        ImprimeLVLOrder(P->left, nivel + 1); // Imprime filho esquerdo primeiro

        for (int i = 0; i < nivel; i++)
            cout << "   ";

        cout << P->D << endl;

        ImprimeLVLOrder(P->right, nivel + 1); // Depois imprime filho direito
    }

    void imprimeInfixa()
    {
        ImprimeInfixa(Root);
    }

private:
    Node<Trem> *MontaArvore(string str)
    {
        stack<Node<Trem> *> s;
        for (int i = str.size() - 1; i >= 0; i--)
        {
            char c = str[i];
            if (isdigit(c) || isalpha(c))
            {
                // Se for um dígito ou uma letra, cria um nó folha com o valor do dígito
                s.push(Node<Trem>::MontaNode(c));
            }
            else
            {
                // Se for um operador, cria um nó interno com o operador e os operandos
                Node<Trem> *node = Node<Trem>::MontaNode(c);
                node->left = s.top();
                s.pop();
                node->right = s.top();
                s.pop();
                s.push(node);
            }
        }
        return s.top();
    }

    void ImprimeInfixa(Node<Trem> *P)
    {
        if (!P)
        {
            return;
        }
        bool precisa_parentesis = false;
        if (P->left)
        {
            // Se o filho esquerdo existir, é necessário colocar parentesis se ele for um operador de menor precedência
            precisa_parentesis = (P->left->D == '+' || P->left->D == '-') && (P->D == '*' || P->D == '/');
            if (precisa_parentesis)
            {
                cout << "(";
            }
            ImprimeInfixa(P->left);
            if (precisa_parentesis)
            {
                cout << ")";
            }
        }

        cout << P->D;

        if (P->right)
        {
            // Se o filho direito existir, é necessário colocar parentesis se ele for um operador de menor precedência
            precisa_parentesis = (P->right->D == '+' || P->right->D == '-') && (P->D == '*' || P->D == '/');
            if (precisa_parentesis)
            {
                cout << "(";
            }
            ImprimeInfixa(P->right);
            if (precisa_parentesis)
            {
                cout << ")";
            }
        }
    }
};