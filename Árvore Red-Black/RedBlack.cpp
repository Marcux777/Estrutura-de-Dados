#include "Class_RedBlack.h"
#include <iostream>

using namespace std;

int main()
{
    RedBlackTree<int> tree;
    
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(15);
    tree.Insert(20);
    tree.Insert(17);
    tree.Insert(3);


    cout << "InOrder:\n";
    tree.InOrder();
    cout << "PosOrder:\n";
    tree.PosOrder();
    cout << "PreOrder:\n";
    tree.PreOrder();
    cout << "\nLevel Order:\n";
    tree.ImprimeLVLOrder(tree.getRoot());

    tree.DeleteValor(10);
    tree.DeleteValor(3);
    tree.DeleteValor(15);

    cout << "InOrder:\n";
    tree.InOrder();
    cout << "PosOrder:\n";
    tree.PosOrder();
    cout << "PreOrder:\n";
    tree.PreOrder();
    cout << "\nLevel Order:\n";
    tree.ImprimeLVLOrder(tree.getRoot());

    return 0;
}