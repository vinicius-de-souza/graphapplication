#ifndef TRABALHO_GRAFO_H
#define TRABALHO_GRAFO_H
#include "No.h"
#include <fstream>
#include <stack>
#include <list>
#include <stdio.h>
#include <vector>

using namespace std;

// Definição da Classe Grafo 

class Grafo{

    //Atributos privados 
private:
    int numero_arestas;
    bool direcionado;
    bool peso_aresta;
    bool peso_no;
    No* primeiro_no;
    No* ultimo_no;

    //Atributos publicos _ podem ser utilizados pelo usuario na main 
public:

    int ordem;

    //Construtor
    Grafo(bool direcionado, bool peso_aresta, bool peso_no);

    //Destrutor
    ~Grafo();

    //Getters
    int getNumeroArestas();
    bool getDirecionado();
    bool getPesoAresta();
    bool getPesoNo();
    int getOrdem();
    No* getPrimeiroNo();
    No* getUltimoNo();
    float getAresta(int idSaida, int idAlvo);
    No* getNo(int id);
    
    //Setters
    void setNumAresta();

    //Outras funções necessárias
    void inserirNo(int id);
    void inserirAresta(int id, int target_id, float weight);
    void removerNo(int id);
    bool procurarNo(int id);
    bool ehDominante(vector <int> sol);

    // Extra _ Criados para melhor visualização do programa
    void geraListaAdjacencia(string output);
    void auxGeraListaAdjacencia(ofstream &output_file);

    //Saida em .dot
    void auxGeraGrafoDot(ofstream &output_file);
    void geraGrafoDot(string output);

    // Parte I _ Implementações necessárias
    void intersecao(ofstream &output_file, Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no);
    void diferenca(ofstream &output_file, Grafo* grafo2,bool direcionado, bool peso_aresta, bool peso_no);
    void uniao(ofstream &output_file, Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no);

    //Parte 2 _ Algoritmos Gulosos
    void gulosoConstrutivo(ofstream &output_file, unsigned semente);
    void gulosoRandomizadoAdaptativo(unsigned semente, ofstream& output_file);
    void gulosoRandomizadoReativo(float alfa, unsigned semente, ofstream& output_file);

};

#endif //TRABALHO_GRAFO_H
