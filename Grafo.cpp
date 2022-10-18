#include "Grafo.h"
#include "No.h"
#include "Aresta.h"
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

// Constructor
Grafo::Grafo(int ordem, bool direcionado, bool peso_aresta, bool peso_no)
{

    this->ordem = ordem;
    this->direcionado = direcionado;
    this->peso_aresta = peso_aresta;
    this->peso_no = peso_no;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;
}

// Destructor
Grafo::~Grafo()
{

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

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being direcionado or not.
*/
void Grafo::inserirNo(int id)
{

}

void Grafo::inserirAresta(int id, int target_id, float weight)
{


}

void Grafo::removerNo(int id){

}

bool Grafo::procurarNo(int id)
{

}

No *Grafo::getNo(int id)
{


}


//Function that verifies if there is a path between two nodes
bool Grafo::buscaProfundidade(int initialId, int targetId){

}


void Grafo::breadthFirstSearch(ofstream &output_file){

}


Grafo *Grafo::getComplementar(){

}



//A function that returns a subjacent of a direcionado graph, which is a graph which the arcs have opposite directions to the original graph
Grafo* Grafo::getSubjacente(){

}

bool Grafo::grafoConectado(){

}



bool Grafo::temCircuito(){

}



float** Grafo::floydMarshall(){

}



float* Grafo::dijkstra(int id){

}
