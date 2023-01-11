#include "../include/No.h"
#include "../include/Grafo.h"
#include "../include/Aresta.h"
#include <iostream>

using namespace std;


// Construtor _ Inicializa o nó, é necesário receber como parâmetro apenas o id (id do usuário) e os outros parâmetros são inicializados "nulos"
No::No(int id){ 

    this->id = id;
    this->idInterno = 0;
    this->grau_entrada = 0;
    this->grau_saida = 0;
    this->peso = 0;
    this->primeira_aresta = nullptr;
    this->ultima_aresta = nullptr;
    this->proximo_no = nullptr;
    this->grau = 0;

};

// Destrutor _ Deleta todas as arestas que são ligadas a esse nó
No::~No(){ 

    Aresta* proxima_aresta = this->primeira_aresta;

    while(proxima_aresta != nullptr){

        Aresta* aux_Aresta = proxima_aresta->getProxAresta();
        delete proxima_aresta;
        proxima_aresta = aux_Aresta;

    }

};

// Getters

// Retorna um objeto aresta referente a primeira aresta do no em questão
Aresta* No::getPrimeiraAresta(){

    return this->primeira_aresta;

}

// Retorna um objeto aresta referente a ultima aresta do no em questão 
Aresta* No::getUltimaAresta(){

    return this->ultima_aresta;

}

// Retorna o id do nó em questão 
int No::getId(){

    return this->id;

}

//Retorna o grau de entrada do nó
int No::getGrauEntrada(){

    return this->grau_entrada;

}

// Retorn o grau de saída do nó
int No::getGrauSaida(){

    return this->grau_saida;

}

// Função booleana que retorna verdadeiro ou falso caso o nó tenha peso ou não
float No::getPesoNo(){

    return this->peso;

}

// Retorna um objeto nó referente ao próximo nó na lista de adjacência do grafo
No* No::getProxNo(){

    return this->proximo_no;

}

// Retorna o grau do nó
int No::getGrau(){

    this->setGrau();

    return this->grau/2;

}

// Retorna o id interno do nó
int No::getIdInterno(){

    return this->idInterno;

}

// Setters

// Recebe como parâmetro um objeto nó e o define como o próximo nó do grafo, dentro da lista de adjacência 
void No::setProxNo(No* proximo_no){

    this->proximo_no = proximo_no;

}

//Recebe como parâmetro um objeto aresta e define como a próxima aresta do nó
void No::setPrimeiraAresta(Aresta* aresta){

    this->primeira_aresta = aresta;

}

//Recebe como parâmetro o peso do nó e o define 
void No::setPeso(float peso){

    this->peso = peso;

}

//Anda pelas arestas e define o grau do nó
void No::setGrau(){

    this->grau = 0;

    for(Aresta *aux = this->getPrimeiraAresta(); aux != nullptr; aux = aux->getProxAresta()){
        grau = grau + 1;
    }

}

//Recebe como parâmetro o id interno e o define _ utilizado para a leitura da parte II do trabalho
void No::setIdInterno(int idinterno){

    this->idInterno = idinterno;

}

// Outras funções

//Recebe como parâmetro o id do nó e o peso referente a aresta que será inserida entre esses dois nós 
void No::inserirAresta(int alvo_id, float peso){

    //Caso o nó já tenha pelo menos uma aresta
    if(this->primeira_aresta != nullptr){

        Aresta* aresta = new Aresta(alvo_id);
        aresta->setpeso(peso);
        this->ultima_aresta->setProxAresta(aresta);
        this->ultima_aresta = aresta;

    }

    else{ // Caso o nó ainda não tenha nenhuma aresta
        
        this->primeira_aresta = new Aresta(alvo_id);
        this->primeira_aresta->setpeso(peso);
        this->ultima_aresta = this->primeira_aresta;

    }

}

//Função que tem como objetivo remover todas as arestas ligadas àquele nó
void No::removeTodasArestas(){  

    // Caso tenha arestas
    if(this->primeira_aresta != nullptr){
        Aresta* next = nullptr;
        Aresta* aux = this->primeira_aresta;
        //Começa da primeira aresta e vai deletando todas
        while(aux != nullptr){ 

            next = aux->getProxAresta();
            delete aux;
            aux = next->getProxAresta();
            delete next;

        }
    }

    // Caso não tenha arestas
    this->primeira_aresta = this->ultima_aresta = nullptr;

}

//Função que recebe como parâmetro o id de um nó, o booleano se o grafo é ou não direcionado e um obejto nó referente a aresta que deve ser removida 
void No::removeAresta(int id, bool directed, No* target_node){ 

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

        if(aux->getProxAresta() == this->ultima_aresta) 
            this->ultima_aresta = aux->getProxAresta();

        delete aux;

        if(directed) //Caso ele seja direcionado 
            this->decrementarGrauSaida();

        else{

            this->decrementarGrauEntrada();
            target_node->decrementarGrauEntrada();

        }

    }

    // Caso não exista a aresta, não faz nada
}

//Função booleana que recebe como prâmetro o id alvo de uma aresta e verifica se tal aresta (que liga o nó em questão e o nó passado como parâmetro) existe
bool No::buscaAresta(int target_id) {

    //Caso haja pelo menos uma aresta no nó
    if(this->primeira_aresta != nullptr){

        //Procurando a aresta
        for(Aresta* aux = this->primeira_aresta; aux != nullptr; aux = aux->getProxAresta())
            if(aux->getAlvoId() == target_id)
                return true;

    }

    //Caso a aresta não exista 
    return false;

}

//Incrementa o grau de entrada do nó _ caso ele seja direcionado 
void No::incrementarGrauEntrada() {

    this->grau_entrada++;

}

//Incrementa o grau de saída do nó _ caso ele seja direcionado 
void No::incrementarGrauSaida(){

    this->grau_saida++;

}

//Decrementa o grau de entrada do nó _ caso ele seja direcionado 
void No::decrementarGrauEntrada() {

    this->grau_entrada--;

}

//Decrementa o grau de entrada do nó _ caso ele seja direcionado 
void No::decrementarGrauSaida(){

    this->grau_saida--;

}

//Recebe como parâmetro o id do nó alvo e verifica se tem aresta entre o nó em questão e esse nó (caso tenha a aresta a função retorna a aresta encontrada)
Aresta* No::temArestaEntre(int alvo_id) {

    for(Aresta *auxAresta = this->primeira_aresta; auxAresta != nullptr; auxAresta = auxAresta->getProxAresta())
    {
        if(auxAresta->getAlvoId() == alvo_id)
            return auxAresta;
    }

    return nullptr;

}