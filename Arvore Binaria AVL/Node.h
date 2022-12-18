#include <iostream>
using namespace std;

template <typename Trem> class Node{
    public:
        Trem D;
        Node<Trem>* Right;
        Node<Trem>* Left;
        static Node<Trem> * MontaNode(Trem dat);
        static Trem DesmontaNode(Node<Trem> * P);
};