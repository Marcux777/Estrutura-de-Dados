#include <iostream>
using namespace std;

template <typename Trem>
class Node
{
public:
    int fb; //fator de balanceamento
    Trem D;
    Node *left;
    Node *right;
    static Node *MontaNode(Trem dat);
    static Trem DesmontaNode(Node *P);
};
