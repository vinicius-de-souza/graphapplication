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
Grafo::Grafo(int ordem, bool direcionado, bool peso_aresta, bool peso_no) {
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
int Grafo::getOrdem(){ // * Funcionando 
    return this->ordem;
}

int Grafo::getNumeroArestas(){ // * Funcionando
    return this->numero_arestas;
}

void Grafo::setNumAresta(){ // * Funcionando 
    this->numero_arestas = this->numero_arestas + 1;
}

bool Grafo::getDirecionado() // * Funcionando
{
    return this->direcionado;
}

bool Grafo::getPesoAresta() // * Funcionando    
{
    return this->peso_aresta;
}

bool Grafo::getPesoNo() // * Funcionando 
{

    return this->peso_no;
}

No *Grafo::getPrimeiroNo() // * Funcionando 
{
    return this->primeiro_no;
}

No *Grafo::getUltimoNo() // * Funcionando
{

    return this->ultimo_no;
}

// Outras funções 

void Grafo::inserirNo(int id){ //* Funcionando
//Inserção interna de nós _ não muda a ordem
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

void Grafo::inserir_No(int id){ //* Funcionando
//Inserção de nós pelo usuário da main _ precisa mudar a ordem

    if(this->primeiro_no == nullptr){ //Caso o grafo esteja vazio 
        No * novoNo = new No(id);
        this->primeiro_no = novoNo;
        this->ultimo_no = novoNo;
        this->ordem = this->ordem + 1;
        return;
    }

    if(this->getNo(id) == nullptr){
        No * novoNo = new No(id);
        this->ultimo_no->setProxNo(novoNo);
        this->ultimo_no = this->ultimo_no->getProxNo();
        this->ordem = this->ordem + 1;
        return;
    }
}

void Grafo::inserirAresta(int id, int target_id, float weight) // * Funcionando 
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

void Grafo::removerNo(int id){ //TODO: fazer função
    No * aux = this->getPrimeiroNo();
    No * previo = nullptr;

    No * noParaRemover = this->getNo(id);

    while(aux->getId() != aux->getId()){

        aux = aux->getProxNo();
    }

}

bool Grafo::procurarNo(int id)  //* Funcionando
{
    No * aux = this->getNo(id);

    if(aux != nullptr)
        return true;

    return false;
}

No *Grafo::getNo(int id) //* Funcionando
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

float Grafo::getAresta(int idSaida, int idAlvo){
    No *auxNo = this->getNo(idSaida);
    for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
        if(auxAresta->getAlvoId()==idAlvo){
            return auxAresta->getpeso();
            } 
        }
}

// Fazer _ Booleano -> verifica se há um caminho entre dois nós passados por parâmetro 
bool Grafo::buscaProfundidade(int initialId, int targetId){ //TODO: fazer função
    
        No *it = this->getNo(initialId);
        //for(){}
    
    return false;
}


// Fazer _ Booleando -> verifica se o grafo é conexo ou não (será utilizado dentro de outras funções)
bool Grafo::grafoConectado(){ //TODO: fazer função
    return false;
}


// Extra _ Criados para melhor visualização do programa

void Grafo::geraListaAdjacencia(string output){ //* Funcionando
//Geração da lista de adjacência dos nós
    //Recebe como parâmetro o nome do arquivo de saída
    ofstream output_file; //Rotina para abertura e escrita do arquivo 
    output_file.open(output, ios::trunc);

    if(output_file.is_open()){
        auxGeraListaAdjacencia(output_file);
    }
    else{ //Mensagem de erro caso não seja possível gerar arquivo de lista de adjacência 
        cerr << endl << "Nao foi possivel abrir arquivo <" + output << ">.";
    }
}

void Grafo::auxGeraListaAdjacencia(ofstream &output_file){ // * Funcionando
    //Recebe como parâmetro o arquivo de saida

    for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){

        output_file << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
            output_file << " " << auxAresta->getAlvoId() << ",";
        }

        output_file << auxNo->getId() << "]" << endl;

    }

}


void Grafo::geraGrafoDot(string output){ //* Funcionando
//Geração do arquivo de sáida em .dot
    ofstream output_file; //Rotina para abertura e escrita do arquivo 
    output_file.open(output, ios::trunc);

    if(output_file.is_open()){
        auxGeraGrafoDot(output_file);
    }
    else{ //Mensagem de erro caso não seja possível gerar arquivo de lista de adjacência 
        cerr << endl << "Nao foi possivel abrir arquivo <" + output << ">.";
    }
}

void Grafo::auxGeraGrafoDot(ofstream &output_file){ //* Funcionando 
//Recebe como parâmetro o aruivo de saida

    if(direcionado){
        output_file << "digraph G {\n";
        for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){

            for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
                output_file << "\n" << "    " << auxNo->getId() << " -> ";
                output_file << " " << auxAresta->getAlvoId();
                if(peso_aresta){
                    output_file << " " << "[label=\" " << this->getAresta(auxNo->getId(), auxAresta->getAlvoId()) << "\"]";
                }
        }
    }
        output_file << "\n" << "\n }";
    }
    
    else{
        output_file << "strict graph G { \n \n";
        for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){

            for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
                output_file << "\n" << "    " << auxNo->getId() << " -- ";
                output_file << " " << auxAresta->getAlvoId();
                if(peso_aresta){
                    output_file << " " << "[label=\" " << this->getAresta(auxNo->getId(), auxAresta->getAlvoId()) << "\"]";
                }
        }
    }
        output_file << "\n" << "\n }";
    }
}
