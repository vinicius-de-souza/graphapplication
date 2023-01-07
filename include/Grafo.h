#ifndef TRABALHO_GRAFO_H
#define TRABALHO_GRAFO_H
#include "No.h"
#include <fstream>
#include <stack>
#include <list>

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

    //Construtor
    Grafo(bool direcionado, bool peso_aresta, bool peso_no);

    //Destrutor
    ~Grafo();

    //Getters
    int getNumeroArestas();
    bool getDirecionado();
    bool getPesoAresta();
    bool getPesoNo();
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

    // Extra _ Criados para melhor visualização do programa
    void geraListaAdjacencia(string output);
    void auxGeraListaAdjacencia(ofstream &output_file);

    //Saida em .dot
    void auxGeraGrafoDot(ofstream &output_file);
    void geraGrafoDot(string output);

    //Geração do arquivo de saída
    void geraArquivoSaida(ofstream &output_file);
    void auxGeraArquivoSaida(ofstream &output_file);

    // Parte I _ Implementações necessárias
    Grafo* intersecao(Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no);
    Grafo* diferenca(Grafo* grafo2,bool direcionado, bool peso_aresta, bool peso_no);
    Grafo* uniao(Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no);
    void redePert();

    //Parte 2 _ Algoritmos Gulosos
    void gulosoConstrutivo();
    void gulosoRandomizadoAdaptativo();
    void gulosoRandomizadoReativo();
};

#endif //TRABALHO_GRAFO_H
