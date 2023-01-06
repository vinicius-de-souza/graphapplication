#include "../include/Aresta.h"
#include <iostream>

using namespace std;

// Construtor _ Inicializa a aresta, é necessario receber como parâmetro o alvo_id (id do nó do qual a aresta aponta _ seja esse grafo direcionado ou não)
Aresta::Aresta(int alvo_id){

    this->alvo_id = alvo_id;
    this->prox_aresta = nullptr;
    this->peso = 0;

}

// Destrutor _ Deleta todas as arestas que estão ligadas 
Aresta::~Aresta(){ 

    if (this->prox_aresta != nullptr){
        delete this->prox_aresta;
        this->prox_aresta = nullptr;
    }

}

// Gets

//Retorna o id do no para o qual a aresta aponta
int Aresta::getAlvoId(){ //Retorna o id do no para o qual a aresta aponta 

    return this->alvo_id;

}

//Retorna a próxima aresta que está concetada
Aresta* Aresta::getProxAresta(){ 

    return this->prox_aresta;

}

//Retorna o peso da aresta 
float Aresta::getpeso(){ 

    return this->peso;

}

// Sets

//Recebe como parâmetro uma aresta e a defini como a próxima 
void Aresta::setProxAresta(Aresta* Aresta){

    this->prox_aresta = Aresta;

}

//Recebe como parâmetro o peso e o define como o peso daquela aresta
void Aresta::setpeso(float peso){

    this->peso = peso;

}
