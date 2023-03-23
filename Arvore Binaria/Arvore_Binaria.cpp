#include "Class_ArvoreBinaria.h"

using namespace std;

int main()
{
    BTree<int> A;
    A.Root = Node<int>::MontaNode(8);
    A.Root->left = Node<int>::MontaNode(3);
    A.Root->left->left = Node<int>::MontaNode(1);
    A.Root->left->right = Node<int>::MontaNode(-6);
    A.Root->left->right->left = Node<int>::MontaNode(4);
    A.Root->left->right->right = Node<int>::MontaNode(7);
    A.Root->right = Node<int>::MontaNode(10);
    A.Root->right->right = Node<int>::MontaNode(14);
    A.Root->right->right->left = Node<int>::MontaNode(13);
    cout << "BFS: ";
    A.Breadthfirstsearch();

    cout << "\n\nIn Order: ";
    A.InOrder();

    cout << "\n\nPre Order: ";
    A.PreOrder();

    cout << "\n\nPos Order: ";
    A.PosOrder();

    cout << endl
         << endl;
    cout << "Altura da Arvore: " << A.DeaphTree() << endl
         << endl;

    cout << "Valor mais a direita da Arvore: " << A.getMax() << endl
         << endl;
    cout << "Valor mais a esquerda da Arvore: " << A.getMin() << endl
         << endl;

    cout << "Arvore Por nivel: \n";
    A.ImprimeLVLOrder(A.Root);

    cout << "\nMaior soma do caminho entre as folhas: " << A.MaxSumPath(A.Root) << endl
         << endl;

    cout << "E espelhada? ";
    if (A.Espelhada(A.Root))
    {
        cout << "True\n";
    }
    else
    {
        cout << "False\n";
    }
}