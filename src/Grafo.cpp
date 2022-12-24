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
Grafo::Grafo(bool direcionado, bool peso_aresta, bool peso_no) {
    // Inicializa o grafo
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
        return;
    }

    if(this->getNo(id) == nullptr){
        No * novoNo = new No(id);
        this->ultimo_no->setProxNo(novoNo);
        this->ultimo_no = this->ultimo_no->getProxNo();
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

void Grafo::removerNo(int id){ //* Funcionando
    if(direcionado){
        No *noRemover = this->getPrimeiroNo();
        No *previo = nullptr;
        if(!procurarNo(id)){
            cout << "No nao encontrado para remocao!";
        }
        else{
            for(noRemover; noRemover->getId()!= id; noRemover = noRemover->getProxNo()){
                previo = noRemover;
            }
            if(previo == nullptr){
                primeiro_no = noRemover->getProxNo();
            }
            else{
                previo->setProxNo(noRemover->getProxNo());
            }
        }
    }
    else{
        No *noRemover = this->getPrimeiroNo();
        No *previo = nullptr;
        if(!procurarNo(id)){
            cout << "No nao encontrado para remocao!";
        }
        else{
            for(noRemover; noRemover->getId()!= id; noRemover = noRemover->getProxNo()){
                previo = noRemover;
            }
            Aresta *auxAre = noRemover->getPrimeiraAresta();
            for(auxAre; auxAre != nullptr; auxAre = auxAre->getProxAresta()){
                int auxId = auxAre->getAlvoId();
                No *aux = getNo(auxId);
                cout << "\n Cheguei nesse no aqui" << aux->getId();
                Aresta *areAux = aux->getPrimeiraAresta();
                Aresta *previa = nullptr;
                for(areAux; areAux->getAlvoId() != id; areAux = areAux->getProxAresta()){
                    previa = areAux;
                }   
                if(previa == nullptr){
                    aux->setPrimeiraAresta(areAux->getProxAresta());
                }
                else{
                previa->setProxAresta(areAux->getProxAresta());
                }
            }
            if(previo == nullptr){
                primeiro_no = noRemover->getProxNo();
            }
            else{
                previo->setProxNo(noRemover->getProxNo());
            }
        }
    }
}

bool Grafo::procurarNo(int id)  //* Funcionando
{
    No * aux = this->getNo(id);

    if(aux != nullptr)
        return true;

    return false;
}

No *Grafo::getNo(int id){ //* Funcionando 
    No * aux = this->getPrimeiroNo();
    while(aux != nullptr){
        if(aux->getId() == id)
            return aux;
        else
            aux = aux->getProxNo();
    }

    return nullptr;
}

float Grafo::getAresta(int idSaida, int idAlvo){ //* Funcionando 
    No *auxNo = this->getNo(idSaida);
    for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
        if(auxAresta->getAlvoId()==idAlvo){
            return auxAresta->getpeso();
            } 
        }
}

//Booleano -> verifica se há um caminho entre dois nós passados por parâmetro 
bool Grafo::buscaProfundidade(int initialId, int targetId){ // ? Essa função precisa ser feita?
    return false;
}

// Booleano -> verifica se o grafo é conexo ou não, será utilizado dentro de outras funções
bool Grafo::grafoConectado(){ //* Funcionando 
    No *vert1 = this->getPrimeiroNo();
    No *vert2 = vert1->getProxNo();
    for(vert1; vert1 != nullptr; vert1 = vert1->getProxNo()){
        vert2 = vert1->getProxNo();
        for(vert2; vert2 != nullptr; vert2 = vert2->getProxNo()){
            if(!buscaProfundidade(vert1->getId(),vert2->getId())){
                return false;
            }
        }
    }
    return true;
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
            output_file << " " << auxAresta->getAlvoId() << " ";
        }

        output_file << "]" << endl;

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
        output_file << "strict digraph G {\n";
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

// Implementações necessárias

void Grafo::intersecao(Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no){ //* Funcionando 
    No* no_grafo1 = this->getPrimeiroNo();
    No* no_grafo2 = grafo2->getPrimeiroNo();
    Grafo *grafo_inter = new Grafo(direcionado, peso_aresta, peso_no);
    for(no_grafo1; no_grafo1 != nullptr ; no_grafo1 = no_grafo1->getProxNo()){
        for(no_grafo2 = grafo2->getPrimeiroNo(); no_grafo2 != nullptr; no_grafo2 = no_grafo2->getProxNo()){
            if(no_grafo1->getId() == no_grafo2->getId()){
                for(Aresta * auxAresta = no_grafo1->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
                    for(Aresta * auxAresta2 = no_grafo2->getPrimeiraAresta(); auxAresta2 != nullptr; auxAresta2 = auxAresta2->getProxAresta()){
                        if(auxAresta->getAlvoId() == auxAresta2->getAlvoId()){
                            if(this->getPesoAresta() && auxAresta->getpeso() == auxAresta2->getpeso()){
                                grafo_inter->inserirAresta(no_grafo1->getId(),auxAresta2->getAlvoId(),auxAresta->getpeso());
                            }
                            if(!this->getPesoAresta()){
                                grafo_inter->inserirAresta(no_grafo1->getId(),auxAresta2->getAlvoId(),0);
                            }
                        }
                    }   
                }
            }
        }
    }
    grafo_inter->geraGrafoDot("testes/intersecao.dot");
    cout << "\nFinalizacao da Funcao Intersecao\n";
    cout << "Arquivo de saida: \"intersecao.dot\" \n\n";
    int sel;
    cout << "Deseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
    cin >> sel;
    if(sel==2){
        cout << "Programa Finalizado";
        exit(0);
    }
}

void  Grafo::diferenca(Grafo* grafo2, bool direcionado, bool peso_aresta, bool peso_no){ //* Funcionando
    Grafo* grafo_dif = new Grafo(direcionado, peso_aresta, peso_no);
    No *no_grafo1 = this->getPrimeiroNo();
    No *no_grafo2 = grafo2->getPrimeiroNo();
    for(no_grafo1; no_grafo1 != nullptr; no_grafo1 = no_grafo1->getProxNo()){
        for(Aresta *aresta = no_grafo1->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            if(peso_aresta)
                grafo_dif->inserirAresta(no_grafo1->getId(),aresta->getAlvoId(),aresta->getpeso());
            else
                grafo_dif->inserirAresta(no_grafo1->getId(),aresta->getAlvoId(),0);
        }
    }
    for(no_grafo2; no_grafo2 != nullptr; no_grafo2 = no_grafo2->getProxNo()){
        No *aux = grafo_dif->getNo(no_grafo2->getId());
        for(Aresta *aresta2 = no_grafo2->getPrimeiraAresta(); aresta2 != nullptr; aresta2 = aresta2->getProxAresta()){
            for(Aresta *aresta1 = aux->getPrimeiraAresta(); aresta1 != nullptr; aresta1 = aresta1->getProxAresta()){
                if(aresta2->getAlvoId() == aresta1->getAlvoId()){
                    grafo_dif->getNo(no_grafo2->getId())->removeAresta(aresta2->getAlvoId(),direcionado,grafo_dif->getNo(aresta2->getAlvoId()));
                }
            }
        }
    }
    grafo_dif->geraGrafoDot("testes/diferenca.dot");
    cout << "\nFinalizacao da Funcao Diferenca\n";
    cout << "Arquivo de saida: \"diferenca.dot\" \n\n";
    int sel;
    cout << "Deseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
    cin >> sel;
    if(sel==2){
        cout << "Programa Finalizado";
        exit(0);
    }
}
    
void Grafo::uniao(Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no){ //* Funcionando
    Grafo* grafo_uni = new Grafo(direcionado,peso_aresta,peso_no);
    No* no_grafo1 = this->getPrimeiroNo();
    No *no_grafo2 = grafo2->getPrimeiroNo();
    for(no_grafo1; no_grafo1 != nullptr; no_grafo1 = no_grafo1->getProxNo()){
        for(Aresta * auxAresta = no_grafo1->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
            if(!peso_aresta){
                grafo_uni->inserirAresta(no_grafo1->getId(),auxAresta->getAlvoId(),0);
            }
            else{
                grafo_uni->inserirAresta(no_grafo1->getId(),auxAresta->getAlvoId(),auxAresta->getpeso());
            }
        }
    }
    for(no_grafo2; no_grafo2 != nullptr; no_grafo2 = no_grafo2->getProxNo()){
        for(Aresta * auxAresta = no_grafo2->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){
            if(!peso_aresta){
                grafo_uni->inserirAresta(no_grafo2->getId(),auxAresta->getAlvoId(),0);
            }
            else{
                grafo_uni->inserirAresta(no_grafo2->getId(),auxAresta->getAlvoId(),auxAresta->getpeso());
            }
        }
    }
    grafo_uni->geraGrafoDot("testes/uniao.dot");
    cout << "\nFinalizacao da Funcao Uniao\n";
    cout << "Arquivo de saida: \"uniao.dot\" \n\n";
    int sel;
    cout << "Deseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
    cin >> sel;
    if(sel==2){
        cout << "Programa Finalizado";
        exit(0);
    }
}
    
void Grafo::redePert(){ 
    if(!this->direcionado){
        cout << "Para a realizacao da Rede Pert o grafo inserido deve ser direcionado!";
        return;
    }
    int id_inicio;
    int id_fim;
    cout << "Para iniciar a Funcao de Rede Pert, indique o id no de inicio (id correspondente a primeira etapa): " ;
    cin >> id_inicio;
    No *inicio = new No(id_inicio);
    cout << "Indique o id do no de fim (id correspondente a ultima etapa): ";
    cin >> id_fim;
    No *fim = new No(id_fim);
}

void Grafo::gulosoConstrutivo(){
    if(this->direcionado){
        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;
    }
    list<int> solucao; //Criação da lista dos vértices de solução (inicalmente vazia) através da função list da biblioeta <stack>
    list<int> vertices; //Criação da lista de todos os vértices do grafo em questão
    No* aux = this->getPrimeiroNo();
    int maior_grau = aux->getGrau();
    No* noMaiorGrau = this->getPrimeiroNo();
    for(aux; aux != nullptr; aux = aux->getProxNo()){ //Preenchendo o vetor de vértices com pesos de cada vertice
        if(aux->getGrau() > maior_grau){
            maior_grau = aux->getGrau();
            noMaiorGrau = aux;
        }
        vertices.push_front(aux->getId());
    }
    int j = vertices.size();
    while(j != 0){
        solucao.push_front(noMaiorGrau->getId());
        for(Aresta *aresta = noMaiorGrau->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){
            vertices.remove(aresta->getAlvoId());
            j = j - 1;
        }
        vertices.remove(noMaiorGrau->getId());
        auto it = vertices.begin();
        int grauMaior = *it;
        for (it; it !=vertices.end(); ++it){
            if(*it > grauMaior)
                grauMaior = *it;
        }
        No *auxiliar = this->getNo(grauMaior);
        noMaiorGrau = auxiliar;
    }
    cout << "Conjunto dos Vertices Originais: [";
    for (auto it = vertices.begin(); it !=vertices.end(); ++it)
        cout << ' ' << *it;
    cout << " ]\n";
    cout << "Conjunto dos Vertices Solucao: [";
    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        cout << ' ' << *it;
    cout << " ]";
}

void Grafo::gulosoRandomizadoAdaptativo(){
    if(this->direcionado){
        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;
    }
}

void Grafo::gulosoRandomizadoReativo(){
    if(this->direcionado){
        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;
    }
}