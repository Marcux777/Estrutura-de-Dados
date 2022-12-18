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

    cout << "fichas pretas (8 fichas): ";
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

    //distribuir as fichas Não Pretas
    cout << "Demais Fichas (44 fichas): ";
    for(int i = 0; i < 44; i++){
        cin >> str;
        a.cor = str[1];
        a.jogador = str[0];
        a.torre = str[2];
        //cout << "Cor: " << a.cor << "\nJogador: " << a.jogador << "\nTorre: " << a.torre << endl;
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
    cout << "Todas as fixas foram distribuidas" << endl;
    
    //Jogadas até preencher as torres
    for(int i = 0; i < 36; i++){
        int torre_Ficha;
        printf("Jogada: ");
        fixa aux; //para comparar com outras fixas
        cin >> str; //Ler a ficha que será jogada
        aux.cor = str[1];
        aux.jogador = str[0];
        aux.torre = str[2];

        //qual jogador vai jogar
        if(i%4 == 0){

            //Procurar a ficha com o while do cachorro
            while(Jogador1.front().cor != aux.cor && Jogador1.front().torre != aux.torre){
                Jogador1.push(Jogador1.front());
                Jogador1.pop();
            }

            //cheguei aqui, então achei a ficha
            torre_Ficha = Jogador1.front().torre - '0';

            //se o elemento na fila é uma ficha preta
            if(Jogador1.front().cor == 'P'){
                if(!Torre[torre_Ficha].empty()){
                    Torre[torre_Ficha].pop();
                }
                Torre[torre_Ficha].push(Jogador1.front());
                Jogador1.pop();
            }

            //Torre cheia, passa para a proxima
            if(Torre[torre_Ficha].size() == 6){
                if((torre_Ficha+1) == 6){
                    torre_Ficha = (torre_Ficha+1)%6;
                }else{
                    torre_Ficha = torre_Ficha%6;
                }
                torre_Ficha++;
            }

            //põe a fixa pra torre
            Torre[torre_Ficha].push(Jogador1.front());
            Jogador1.pop();
        }else{
            if(i%4 == 1){

                //Procurar a ficha com o while do cachorro
                while(Jogador2.front().jogador != aux.jogador && Jogador2.front().torre != aux.torre){
                    Jogador2.push(Jogador2.front());
                    Jogador2.pop();
                }

                //cheguei aqui, então achei a ficha
                torre_Ficha = Jogador2.front().torre - '0';

                //se o elemento na fila é uma ficha preta
                if(Jogador2.front().cor == 'P'){
                    if(!Torre[torre_Ficha].empty()){
                    Torre[torre_Ficha].pop();
                    }
                    Torre[torre_Ficha].push(Jogador2.front());
                    Jogador2.pop();
                }

                //Torre cheia, passa para a proxima
                if(Torre[torre_Ficha].size() == 6){
                    if((torre_Ficha+1) == 6){
                        torre_Ficha = (torre_Ficha+1)%6;
                    }else{
                        torre_Ficha = torre_Ficha%6;
                    }
                    torre_Ficha++;
                }

                //põe a fixa pra torre
                Torre[torre_Ficha].push(Jogador1.front());
                Jogador1.pop();
            }else{
                if(i%4 == 2){

                    //Procurar a ficha com o while do cachorro
                    while(Jogador3.front().jogador != aux.jogador && Jogador3.front().torre != aux.torre){
                        Jogador3.push(Jogador3.front());
                        Jogador3.pop();
                    }

                    //cheguei aqui, então achei a ficha
                    torre_Ficha = Jogador3.front().torre - '0';

                    //se o elemento na fila é uma ficha preta
                    if(Jogador3.front().cor == 'P'){
                        if(!Torre[torre_Ficha].empty()){
                            Torre[torre_Ficha].pop();
                        }
                        Torre[torre_Ficha].push(Jogador3.front());
                        Jogador3.pop();
                    }

                    //Torre cheia, passa para a proxima
                    if(Torre[torre_Ficha].size() == 6){
                        if((torre_Ficha+1) == 6){
                            torre_Ficha = (torre_Ficha+1)%6;
                        }else{
                            torre_Ficha = torre_Ficha%6;
                        }
                        torre_Ficha++;
                    }

                    //põe a fixa pra torre
                    Torre[torre_Ficha].push(Jogador3.front());
                    Jogador3.pop();

                }else{
                    //Procurar a ficha com o while do cachorro
                    while(Jogador4.front().jogador != aux.jogador && Jogador4.front().torre != aux.torre){
                        Jogador4.push(Jogador4.front());
                        Jogador4.pop();
                    }

                    //cheguei aqui, então achei a ficha
                    torre_Ficha = Jogador4.front().torre - '0';

                    //se o elemento na fila é uma ficha preta
                    if(Jogador4.front().cor == 'P'){
                        if(!Torre[torre_Ficha].empty()){
                            Torre[torre_Ficha].pop();
                        }
                        Torre[torre_Ficha].push(Jogador4.front());
                        Jogador4.pop();
                    }

                    //Torre cheia, passa para a proxima
                    if(Torre[torre_Ficha].size() == 6){
                        if((torre_Ficha+1) == 6){
                            torre_Ficha = (torre_Ficha+1)%6;
                        }else{
                            torre_Ficha = torre_Ficha%6;
                        }
                        torre_Ficha++;
                    }

                    //põe a fixa pra torre
                    Torre[torre_Ficha].push(Jogador4.front());
                    Jogador4.pop();
                }
            }
        }

        //Incrementa quando não a ficha não é Preta
        /*if(aux.cor != 'P'){
            i++;
        }*/
    }

    

    int azul, roxo, vermelho, branco, j;
    azul = roxo = vermelho = branco = 0;

    //Desempilhando e Pontuando cada Jogador
    for(int i = 1; i <= 6; i++){
        
        fixa aux;
        j = 1;
        while(j--){
            aux.cor = Torre[i].top().cor;
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
        j++;
    }

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