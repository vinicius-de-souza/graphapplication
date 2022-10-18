#include "Aresta.h"
#include <iostream>

using namespace std;

// Construtor
Aresta::Aresta(int alvo_id){

    this->alvo_id = alvo_id;
    this->prox_aresta = nullptr;
    this->peso = 0;

}

// Destrutor
Aresta::~Aresta(){

    if (this->prox_aresta != nullptr){
        delete this->prox_aresta;
        this->prox_aresta = nullptr;
    }

}

// Gets
int Aresta::getAlvoId(){

    return this->alvo_id;

}

Aresta* Aresta::getProxAresta(){

    return this->prox_aresta;

}

float Aresta::getpeso(){

    return this->peso;

}

// Sets
void Aresta::setProxAresta(Aresta* Aresta){

    this->prox_aresta = Aresta;

}

void Aresta::setpeso(float peso){

    this->peso = peso;

}
