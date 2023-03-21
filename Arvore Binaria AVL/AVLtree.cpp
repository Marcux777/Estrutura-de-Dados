#include "AVLTree.h"

using namespace std;

template <typename Trem> AVLTree<Trem>::AVLTree(){
    R = NULL;
}

template <typename Trem> AVLTree<Trem>::~AVLTree(){
    DeleteTree(R);
}

template <typename Trem> void AVLTree<Trem>::DeleteTree(Node<Trem>* X){
    if (X != NULL){
        DeleteTree(X->Left);

        DeleteTree(X->Right);

        Node<Trem>::DesmontaNode(X);
    }
}

template <typename Trem> void AVLTree<Trem>::RSD(Node<Trem>*(&R)){
    Node<Trem>* Aux = R->Left;
    R->Left = Aux->Right;
    Aux->Right = R;
    R = Aux;
}

template <typename Trem> void AVLTree<Trem>::RSE(Node<Trem>*(&R)){
    Node<Trem>* Aux = R->Right;
    R->Right = Aux->Left;
    Aux->Left = R;
    R = Aux;
}

template <typename Trem> void AVLTree<Trem>::RDD(Node<Trem>*(&R)){
    Node<Trem>* Aux = R->Right;
    static AVLTree::RSD(Aux);
    R->Right = Aux;
    static AVLTree::RSE(R);
}

template <typename Trem> void AVLTree<Trem>::RDE(Node<Trem>*(&R)){
    Node<Trem>* Aux = R->Left;
    AVLTree::RSE(Aux);
    R->Left = Aux;
    AVLTree::RSD(R);
}

template <typename Trem> void AVLTree<Trem>::Insert(Node<Trem> *)
