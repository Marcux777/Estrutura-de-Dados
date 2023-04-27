#include "Class_RedBlack.h"
#include <iostream>

using namespace std;

int main()
{
    RedBlackTree<int> tree;
    int a;
    while(cin >> a && a){
        tree.Insert(a);
    }
    cout << "InOrder:\n";
    tree.InOrder();
    cout << "PosOrder:\n";
    tree.PosOrder();
    cout << "PreOrder:\n";
    tree.PreOrder();
    cout << "\nLevel Order:\n";
    tree.ImprimeLVLOrder(tree.getRoot());

    /*while(cin >> a && a){
        tree.DeleteValor(a);
    }

    cout << "InOrder:\n";
    tree.InOrder();
    cout << "PosOrder:\n";
    tree.PosOrder();
    cout << "PreOrder:\n";
    tree.PreOrder();
    cout << "\nLevel Order:\n";
    tree.ImprimeLVLOrder(tree.getRoot());

    tree.Clear();
    if(tree.getRoot()){
        cout << "Árvore Vazia" << endl;
    }else{
        cout << "Árvore com elemento" << endl;
    }*/

    return 0;
}