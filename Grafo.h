#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "No.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Grafo{

    //Atributos
private:
    int ordem;
    int numero_arestas;
    bool direcionado;
    bool peso_aresta;
    bool peso_no;
    No* primeiro_no;
    No* ultimo_no;

public:

    //Constructor
    Grafo(int ordem, bool direcionado, bool peso_aresta, bool peso_no);

    //Destructor
    ~Grafo();

    //Getters
    int getOrdem();
    int getNumeroArestas();
    bool getDirecionado();
    bool getPesoAresta();
    bool getPesoNo();
    No* getPrimeiroNo();
    No* getUltimoNo();

    //Other methods
    void inserirNo(int id);
    void inserirAresta(int id, int target_id, float weight);
    void removerNo(int id);
    bool procurarNo(int id);
    No* getNo(int id);
    bool buscaProfundidade(int idInicial, int idAlvo);
    void breadthFirstSearch(ofstream& output_file);
    Grafo* getComplementar();
    Grafo* getSubjacente();
    bool temCircuito();
    bool grafoConectado();
    float** floydMarshall();
    float* dijkstra(int id);

private:
    //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED
