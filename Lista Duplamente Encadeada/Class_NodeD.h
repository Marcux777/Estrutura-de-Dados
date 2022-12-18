#include <iostream>
using namespace std;

template <typename Trem> class NodeD{
    public:
        Trem D;
        NodeD<Trem>* Next;
        NodeD<Trem>* Prev;
        static NodeD<Trem> * MontaNode(Trem dat);
        static Trem DesmontaNode(NodeD<Trem> * P);
};
