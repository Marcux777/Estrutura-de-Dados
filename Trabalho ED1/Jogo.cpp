#include <iostream>
#include "Class_Stack.h"
#include "Class_Queue.h"

using namespace std;


//Criando os metodos da Classe Fila
template <typename Trem> Queue<Trem>::Queue(){
    head = tail = NULL;
    N = 0;
}
template <typename Trem> Queue<Trem>::~Queue<Trem>(){
    Node <Trem> *P = head;
    while(head){
        head = P -> Next;
        Node<Trem>::DesmontaNode(P);
        P = head;
    }
}
template <typename Trem> Trem Queue<Trem>::front(){
    Trem x;
    if(head){
        x = head -> D;
    }
    return x;
}
template <typename Trem> bool Queue<Trem>::push(Trem x){
    Node<Trem> * P = Node<Trem>::MontaNode(x);
    if(!P){
        return false;
    }
    if(head){
        tail -> Next = P;
    }else{
        head = P;
    }
    tail = P;
    tail -> Next = 0;
    N++;
    return true;
}
template <typename Trem> Trem Queue<Trem>::pop(){
    Trem x;
    if(head){
        Node<Trem>*P = head;
        head = head -> Next;
        x = Node<Trem>::DesmontaNode(P);
        if(!head){
            tail = 0;
        }
        N--;
    }
    return x;
}
template <typename Trem> int Queue<Trem>::size(){
    return N;
}
template <typename Trem> bool Queue<Trem>::empty(){
    return !head;
}
template <typename Trem> void Queue<Trem>::clear(){
    Node<Trem> * P = head;
    while(head){
        head = P -> Next;
        Node<Trem>::DesmontaNode(P);
        P = head;
    }
    tail = N = NULL;
}

//Criando os metodos da Stack
template <typename Trem> Stack<Trem>::Stack(){
    Top = NULL;
    N = 0;
}
template <typename Trem> bool Stack<Trem>::push(Trem X){
    Node<Trem> * P = Node<Trem>::MontaNode(X);
    if(!P){
        return false;
    }
    P -> Next = Top;
    Top = P;
    N++;
    return true;
}
template <typename Trem> Trem Stack<Trem>::top(){
    Trem X;
    if(Top){
        X = Top -> D;
    }
    return X;
}
template <typename Trem> int Stack<Trem>::size(){
    return N;
}
template <typename Trem> bool Stack<Trem>::empty(){
    return !Top;
}
template <typename Trem> Trem Stack<Trem>::pop(){
    Trem X;
    if(Top){
        Node<Trem> * P = Top;
        Top = Top -> Next;
        X = Node<Trem>::DesmontaNode(P);
        N--;
    }
    return X;
}
template <typename Trem> Stack<Trem>::~Stack<Trem>(){
    Node<Trem> *P;
    while(Top){
		P = Top;
		Top = Top -> Next;
		Node<Trem>::DesmontaNode(P);
	}
}

class fixa{
    public:
        char cor;
        char jogador;
        char torre;
};


int main(){
    fixa a;
    Stack <fixa> Torre[7];
    Queue <fixa> Jogador1;
    Queue <fixa> Jogador2;
    Queue <fixa> Jogador3;
    Queue <fixa> Jogador4;

    string str;
    //distribuir as fichas Não Pretas
    cout << "Digite as Fichas coloridas (44 fichas): ";
    for(int i = 0; i < 44; i++){
        cin >> str;
        a.cor = str[1];
        a.jogador = str[0];
        a.torre = str[2];
        cout << "Cor: " << a.cor << "\nJogador: " << a.jogador << "\nTorre: " << a.torre << endl;
        if(a.jogador == '1'){
            Jogador1.push(a);
        }else{
            if(a.jogador == '2'){
                Jogador2.push(a);
            }else{
                if(a.jogador == '3'){
                    Jogador3.push(a);
                }else{
                    Jogador4.push(a);
                }
            }
        }
        
    }
    cout << "Digite as fichas pretas (8 fichas): ";
    //distribuir as fichas pretas
    for(int i = 0; i < 8; i++){
        cin >> str;
        a.cor = str[1];
        a.torre = str[2];
        a.jogador = str[0];
        if(a.jogador == '1'){
            Jogador1.push(a);
        }else{
            if(a.jogador == '2'){
                Jogador2.push(a);
            }else{
                if(a.jogador == '3'){
                    Jogador3.push(a);
                }else{
                    Jogador4.push(a);
                }
            }
        }
    }

    //A fila de jogadores, na sequencia que irão jogar
    Queue <Queue<fixa>> FilaDeJogadores;
    FilaDeJogadores.push(Jogador1);
    FilaDeJogadores.push(Jogador2);
    FilaDeJogadores.push(Jogador3);
    FilaDeJogadores.push(Jogador4);

    //Jogadas enquanto todas as torres não estiverem cheias (igual a 6)
    while(Torre[1].size() <= 6 || Torre[2].size() <= 6 || Torre[3].size() <= 6 || Torre[4].size() <= 6 || Torre[5].size() <= 6 || Torre[6].size() <= 6){
        
        int torre_Ficha = FilaDeJogadores.front().front().torre - '0';
        if(FilaDeJogadores.front().front().cor == 'P'){
            if(!Torre[torre_Ficha].empty()){
                Torre[torre_Ficha].pop();
            }
            Torre[torre_Ficha].push(FilaDeJogadores.front().front());
            FilaDeJogadores.front().pop();
        }
        if(Torre[torre_Ficha].size() == 6){
            while((Torre[1].size() <= 6 || Torre[2].size() <= 6 || Torre[3].size() <= 6 || Torre[4].size() <= 6 || Torre[5].size() <= 6 || Torre[6].size() <= 6) && Torre[torre_Ficha].size() == 6){
                torre_Ficha++;
                if(torre_Ficha%6 == 0){
                    torre_Ficha = (torre_Ficha + 1)%6;
                }else{
                    torre_Ficha = torre_Ficha%6;
                }
            }
           
        }
        Torre[torre_Ficha].push(FilaDeJogadores.front().front());
        FilaDeJogadores.front().pop();
        FilaDeJogadores.push(FilaDeJogadores.front());
        FilaDeJogadores.pop();
    }

    //Desempilhando e Pontuando cada Jogador

    for(int i = 1; i <= 6; i++){
        int azul, roxo, vermelho, branco;
        azul = roxo = vermelho = branco = 0;
        fixa aux;
        int j = 1;
        while(j--){
            aux = Torre[i].top();
            Torre[i].pop();
        }
        if(aux.cor == 'A'){
            azul++;
        }else{
            if(aux.cor == 'R'){
                roxo++;
            }else{
                if(aux.cor == 'V'){
                    vermelho++;
                }else{
                    branco++;
                }
            }
        }
        cout << "Pontos do Azul: " << azul << endl;
        cout << "Pontos do Roxo: " << roxo << endl;
        cout << "Pontos do Vermelho: " << vermelho << endl;
        cout << "Pontos do Branco: " << branco << endl;
        if(azul > roxo && azul > vermelho && azul > branco){
            cout << "Azul Ganhou!!!" << endl;
        }else{
            if(roxo > azul && roxo > vermelho && roxo > branco){
                cout << "Roxo Ganhou!!!" << endl;
            }else{
                if(vermelho > azul && vermelho > roxo && vermelho > branco){
                    cout << "Vermelho Ganhou!!!" << endl;
                }else{
                    if(branco > azul && branco > vermelho && branco > roxo){
                        cout << "Branco Ganhou!!!" << endl;
                    }else{
                        cout << "Houve Empate!!!" << endl;
                    }
                }
            }
        }
    }
}