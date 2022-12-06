#ifndef TRABALHO_NO_H
#define TRABALHO_NO_H
#include "Aresta.h" // Include of the Aresta class

using namespace std;

// Definição da Classe No
class No{

    // Atributos
private:
    Aresta* primeira_aresta;
    Aresta* ultima_aresta;
    int id;
    unsigned int grau_entrada;
    unsigned int grau_saida;
    float peso;
    No* proximo_no;

public:
    // Construtor
    No(int id);
    // Destrutor
    ~No();
    // Getters
    Aresta* getPrimeiraAresta();
    Aresta* getUltimaAresta();
    int getId();
    int getGrauEntrada();
    int getGrauSaida();
    float getPeso();
    No* getProxNo();
    // Setters
    void setProxNo(No* No);
    void setPeso(float peso);
    // Outras funções
    bool buscaAresta(int alvo_id);
    void inserirAresta(int alvo_id, float peso);
    void removeTodasArestas();
    int  removeAresta(int id, bool direcionado, No* no_alvo);
    void incrementarGrauSaida();
    void decrementarGrauSaida();
    void incrementarGrauEntrada();
    void decrementarGrauEntrada();
    Aresta* temArestaEntre(int alvo_id);
};

#endif //TRABALHO_NO_H
