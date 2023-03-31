#include "Class_ArvoreBinaria.h"

using namespace std;

int main()
{
     
     BTree<int> B;
     B.Root = Node<int>::MontaNode(10);
     B.Root->left = Node<int>::MontaNode(7);
     B.Root->left->left = Node<int>::MontaNode(4);
     B.Root->left->left->left = Node<int>::MontaNode(2);
     B.Root->left->left->right = Node<int>::MontaNode(5);
     B.Root->left->right = Node<int>::MontaNode(8);
     B.Root->right = Node<int>::MontaNode(12);
     B.Root->right->left = Node<int>::MontaNode(11);
     B.Root->right->right = Node<int>::MontaNode(13);

     B.ImprimeLVLOrder(B.Root);

     B.BurnTree(7);

     

}