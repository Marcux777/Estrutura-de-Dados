#include "Class_AVL.h"
#include <locale.h>

int main()
{
    ArvBinaria<int> avlTree;

    avlTree.Insert(50);
    avlTree.Insert(30);
    avlTree.Insert(20);
    avlTree.Insert(40);
    avlTree.Insert(70);
    avlTree.Insert(60);
    avlTree.Insert(80);

    cout << "In Order traversal: ";
    avlTree.InOrder();
    cout << endl;

    cout << "Pre Order traversal: ";
    avlTree.PreOrder();
    cout << endl;

    cout << "Pos Order traversal: ";
    avlTree.PosOrder();
    cout << endl;

    cout << "Level Order traversal: \n";
    avlTree.LevelOrder();
    cout << endl;

    // Remover um nó da árvore
    avlTree.Remove(30);

    cout << "Depois da Remocao: " << endl;
    avlTree.LevelOrder();
    cout << endl;

    int value = 30;

    if (avlTree.Search(value))
    {
        cout << "O valor " << value << " foi encontrado na arvore." << endl;
    }
    else
    {
        cout << "O valor " << value << " nao foi encontrado na arvore." << endl;
    }

    return 0;
}

