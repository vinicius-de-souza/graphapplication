#include "../include/Grafo.h"
#include "../include/No.h"
#include "../include/Aresta.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>

using namespace std;

// Construtor 
Grafo::Grafo(int ordem, bool direcionado, bool peso_aresta, bool peso_no) //Como essa ordem é passada na hora da leitura do aquivo?
{
    // Inicializa o grafo
    this->ordem = ordem;
    this->direcionado = direcionado;
    this->peso_aresta = peso_aresta;
    this->peso_no = peso_no;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;
}

// Destrutor
Grafo::~Grafo()
{
    // Exclui todos os nós e suas arestas
    No *proximo_no = this->primeiro_no;

    while (proximo_no != nullptr)
    {

        proximo_no->removeTodasArestas();
        No *no_auxiliar = proximo_no->getProxNo();
        delete proximo_no;
        proximo_no = no_auxiliar;
    }
}

// Getters
int Grafo::getOrdem()
{

    return this->ordem;
}
int Grafo::getNumeroArestas()
{

    return this->numero_arestas;
}

bool Grafo::getDirecionado()
{

    return this->direcionado;
}

bool Grafo::getPesoAresta()
{

    return this->peso_aresta;
}

bool Grafo::getPesoNo()
{

    return this->peso_no;
}

No *Grafo::getPrimeiroNo()
{

    return this->primeiro_no;
}

No *Grafo::getUltimoNo()
{

    return this->ultimo_no;
}

// Outras funções 

void Grafo::inserirNo(int id) 
{
    if(this->primeiro_no == nullptr){ //Caso o grafo esteja vazio 
        No * novoNo = new No(id);
        this->primeiro_no = novoNo;
        this->ultimo_no = novoNo;
        return;
    }

    if(this->getNo(id) == nullptr){
        No * novoNo = new No(id);
        this->ultimo_no->setProxNo(novoNo);
        this->ultimo_no = this->ultimo_no->getProxNo();
        return;
    }

}

//
void Grafo::inserirAresta(int id, int target_id, float weight)
{
    if(this->getNo(id) == nullptr){ //Caso ainda não exista o nó de onde sai a aresta
        this->inserirNo(id);
    }

    if(this->getNo(target_id) == nullptr){ //Caso ainda não exista o nó de entrada da aresta
        this->inserirNo(target_id);
    }

    this->getNo(id)->inserirAresta(target_id, weight);

    if(!this->getDirecionado()) //Caso seja um grafo direcionado 
    {
        this->getNo(target_id)->inserirAresta(id, weight);
    }
}

void Grafo::removerNo(int id){ //Remoção de nó
    No * aux = this->getPrimeiroNo();
    No * previo = nullptr;

    No * noParaRemover = this->getNo(id);

    while(aux->getId() != aux->getId()){

        aux = aux->getProxNo();
    }

}

bool Grafo::procurarNo(int id)  //Fazer
{
    No * aux = this->getNo(id);

    if(aux != nullptr)
        return true;

    return false;
}

No *Grafo::getNo(int id)
{
    No * aux = this->getPrimeiroNo();
    while(aux != nullptr){
        if(aux->getId() == id)
            return aux;
        else
            aux = aux->getProxNo();
    }

    return nullptr;
}


// Fazer _ Booleano -> verifica se há um caminho entre dois nós passados por parâmetro 
bool Grafo::buscaProfundidade(int initialId, int targetId){
    return false;
}


// Fazer _ Booleando -> verifica se o grafo é conexo ou não (será implementado dentro de outras funções)
bool Grafo::grafoConectado(){
    return false;
}


// Extra _ Criados para melhor visualização do programa

void Grafo::geraListaAdjacencia(string output){
    ofstream output_file;
    output_file.open(output, ios::trunc);

    if(output_file.is_open()){
        auxGeraListaAdjacencia(output_file);
    }
    else{
        cerr << endl << "Nao foi possivel abrir arquivo <" + output << ">.";
    }
}

void Grafo::auxGeraListaAdjacencia(ofstream &output_file){

    for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){

        output_file << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
            output_file << " " << auxAresta->getAlvoId() << ",";
        }

        output_file << auxNo->getId() << "]" << endl;

    }

}
