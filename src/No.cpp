#include "../include/No.h"
#include "../include/Grafo.h"
#include "../include/Aresta.h"
#include <iostream>

using namespace std;


// Construtor
No::No(int id){ //Recebe o id _ De onde esse id vem na leitura de arquivos?

    this->id = id;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->peso = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;

};

// Destrutor
No::~No(){ //Deleta todas as arestas que são ligadas a esse nó

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

// Outras funções
void No::inserirAresta(int alvo_id, float peso){
    //Caso o nó já tenha pelo menos uma aresta
    if(this->primeira_aresta != nullptr){
        Aresta* aresta = new Aresta(alvo_id);
        aresta->setpeso(peso);
        this->ultima_aresta->setProxAresta(aresta);
        this->ultima_aresta = aresta;
    }
    else{
        // Caso o nó ainda não tenha nenhuma aresta
        this->primeira_aresta = new Aresta(alvo_id);
        this->primeira_aresta->setpeso(peso);
        this->ultima_aresta = this->primeira_aresta;
    }

}

void No::removeTodasArestas(){  
    // Caso tenha arestas
    if(this->primeira_aresta != nullptr){
        Aresta* next = nullptr;
        Aresta* aux = this->primeira_aresta;
        //Começa da primeira aresta e vai deletando todas
        while(aux != nullptr){  //Esse raciocínio ta certo??
            next = aux->getProxAresta();
            delete aux;
            aux = next->getProxAresta();
            delete next;
        }
    }
    // Caso não tenha arestas
    this->primeira_aresta = this->ultima_aresta = nullptr;
}

int No::removeAresta(int id, bool directed, No* target_node){ //Está funcionando?
    //Verifica se a aresta pedida pra ser removida existe 
    if(this->buscaAresta(id)){

        Aresta* aux = this->primeira_aresta;
        Aresta* previous = nullptr;
        // Procura a aresta para ser removida
        while(aux->getAlvoId() != id){
            previous = aux;
            aux = aux->getProxAresta();
        }
        if(previous != nullptr) //Conecto o nó da aresta anterior com o nó da proxima aresta
            previous->setProxAresta(aux->getProxAresta());
        else //Caso seja a primeira aresta a ser removida
            this->primeira_aresta = aux->getProxAresta();
        if(aux == this->ultima_aresta) //Caso seja a ultima aresta
            this->ultima_aresta = previous;
        if(aux->getProxAresta() == this->ultima_aresta) //
            this->ultima_aresta = aux->getProxAresta();
        delete aux;
        if(directed) //Caso ele seja direcionado 
            this->decrementarGrauSaida();
        else{
            this->decrementarGrauEntrada();
            target_node->decrementarGrauEntrada();
        }

        return 1;

    }
    // Caso não exista a aresta não faz nada
    return 0;
}

bool No::buscaAresta(int target_id) {
    //Caso haja pelo menos uma aresta no nó
    if(this->primeira_aresta != nullptr){
        //Procurando a aresta
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

Aresta* No::temArestaEntre(int alvo_id) //Verifica se há aresta entre dois nós
{

    for(Aresta *auxAresta = this->primeira_aresta; auxAresta != nullptr; auxAresta = auxAresta->getProxAresta())
    {
        if(auxAresta->getAlvoId() == alvo_id)
            return auxAresta;
    }
    return nullptr;
}
