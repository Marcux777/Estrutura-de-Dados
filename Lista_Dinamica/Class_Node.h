#include <iostream>
using namespace std;

template <typename Trem> class Node{
    public:
        Trem D;
        Node* Next;
        static Node * MontaNode(Trem dat);
        static Trem DesmontaNode(Node * P);
};
