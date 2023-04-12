#include "Expression_Tree.h"
#include <vector>

using namespace std;

int main()
{
    //Todos os casos de teste
    vector<string> s = {"+ab", "+a*bc", "*+abc", "++a*bcd", "*+ab+cd", "+++abcd", "+34"};

    for (int i = 0; i < int(s.size()); i++)
    {
        cout << "Expressao " << i+1 << endl << endl;
        ExpTree<char> arvore;

        arvore.Insert(s[i]); // Cria a árvore de expressão correspondente

        cout << "Expressao Infixa: ";
        arvore.imprimeInfixa();
        cout << endl << endl;
        arvore.ImprimeLVLOrder(arvore.Root); // Imprime a árvore em nível-ordem
        cout << endl << endl;

        
    }
    return 0;
}
