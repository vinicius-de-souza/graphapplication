#include "../include/No.h"
#include "../include/Grafo.h"
#include "../include/Aresta.h"
#include <iostream>

using namespace std;


// Construtor
No::No(int id){

    this->id = id;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->peso = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;

};

// Destrutor
No::~No(){

    Aresta* proxima_aresta = this->primeira_aresta;

    while(proxima_aresta != nullptr){

        Aresta* aux_Aresta = proxima_aresta->getProxAresta();
        delete proxima_aresta;
        proxima_aresta = aux_Aresta;

    }

};

// Getters
Aresta* No::getPrimeiraAresta(){

    return this->primeira_aresta;

}

Aresta* No::getUltimaAresta(){

    return this->ultima_aresta;

}

int No::getId(){

    return this->id;

}

int No::getGrauEntrada(){

    return this->grau_entrada;

}

int No::getGrauSaida(){

    return this->grau_saida;

}

float No::getPeso(){

    return this->peso;

}

No* No::getProxNo(){

    return this->proximo_no;

}

// Setters

void No::setProxNo(No* proximo_no){

    this->proximo_no = proximo_no;

}

void No::setPeso(float peso){

    this->peso = peso;

}

// Other methods
void No::inserirAresta(int alvo_id, float peso){
    // Verifies whether there are at least one Aresta in the node
    if(this->primeira_aresta != nullptr){
        // Allocating the new Aresta and keeping the integrity of the Aresta list
        Aresta* aresta = new Aresta(alvo_id);
        aresta->setpeso(peso);
        this->ultima_aresta->setProxAresta(aresta);
        this->ultima_aresta = aresta;

    }
    else{
        // Allocating the new Aresta and keeping the integrity of the Aresta list
        this->primeira_aresta = new Aresta(alvo_id);
        this->primeira_aresta->setpeso(peso);
        this->ultima_aresta = this->primeira_aresta;

    }

}

void No::removeTodasArestas(){
    // Verifies whether there are at least one Aresta in the node
    if(this->primeira_aresta != nullptr){

        Aresta* next = nullptr;
        Aresta* aux = this->primeira_aresta;
        // Removing all Arestas of the node
        while(aux != nullptr){

            next = aux->getProxAresta();
            delete aux;

        }

    }

    this->primeira_aresta = this->ultima_aresta = nullptr;

}

int No::removeAresta(int id, bool directed, No* target_node){
    // Verifies whether the Aresta to remove is in the node
    if(this->buscaAresta(id)){

        Aresta* aux = this->primeira_aresta;
        Aresta* previous = nullptr;
        // Searching for the Aresta to be removed
        while(aux->getAlvoId() != id){

            previous = aux;
            aux = aux->getProxAresta();

        }
        // Keeping the integrity of the Aresta list
        if(previous != nullptr)
            previous->setProxAresta(aux->getProxAresta());

        else
            this->primeira_aresta = aux->getProxAresta();

        if(aux == this->ultima_aresta)
            this->ultima_aresta = previous;

        if(aux->getProxAresta() == this->ultima_aresta)
            this->ultima_aresta = aux->getProxAresta();

        delete aux;
        // Verifies whether the graph is directed
        if(directed)
            this->decrementarGrauSaida();

        else{

            this->decrementarGrauEntrada();
            target_node->decrementarGrauEntrada();

        }

        return 1;

    }

    return 0;

}

bool No::buscaAresta(int target_id) {
    // Verifies whether there are at least one Aresta in the node
    if(this->primeira_aresta != nullptr){
        // Searching for a specific Aresta of target id equal to target id
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
            if(aux->getAlvoId() == target_id)
                return true;

    }

    return false;

}



void No::incrementarGrauEntrada() {

    this->grau_entrada++;

}

void No::incrementarGrauSaida(){

    this->grau_saida++;

}

void No::decrementarGrauEntrada() {

    this->grau_entrada--;

}

void No::decrementarGrauSaida(){

    this->grau_saida--;

}

Aresta* No::temArestaEntre(int alvo_id)
{

    for(Aresta *auxAresta = this->primeira_aresta; auxAresta != nullptr; auxAresta = auxAresta->getProxAresta())
    {
        if(auxAresta->getAlvoId() == alvo_id)
            return auxAresta;
    }
    return nullptr;
}
