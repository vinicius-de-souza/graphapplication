#ifndef TRABALHO_GRAFO_H
#define TRABALHO_GRAFO_H
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

    //Construtor
    Grafo(int ordem, bool direcionado, bool peso_aresta, bool peso_no);

    //Destrutor
    ~Grafo();

    //Getters
    int getOrdem();
    int getNumeroArestas();
    bool getDirecionado();
    bool getPesoAresta();
    bool getPesoNo();
    No* getPrimeiroNo();
    No* getUltimoNo();

    //Outras funções necessárias
    void inserirNo(int id);
    void inserir_No(int id);
    void inserirAresta(int id, int target_id, float weight);
    void removerNo(int id);
    bool procurarNo(int id);
    No* getNo(int id);
    bool buscaProfundidade(int idInicial, int idAlvo);
    bool grafoConectado();
    void setNumAresta();

    // Extra _ Criados para melhor visualização do programa
    void geraListaAdjacencia(string output);
    void auxGeraListaAdjacencia(ofstream &output_file);

    //Saida em .dot
    void auxGeraGrafoDot(ofstream &output_file);
    void geraGrafoDot(string output);


};

#endif //TRABALHO_GRAFO_H
