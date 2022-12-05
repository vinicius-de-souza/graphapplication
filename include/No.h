#ifndef TRABALHO_NO_H
#define TRABALHO_NO_H
#include "Aresta.h" // Include of the Aresta class

using namespace std;

// Definição da Classe No
class No{

    // Attributes
private:
    Aresta* primeira_aresta;
    Aresta* ultima_aresta;
    int id;
    unsigned int grau_entrada;
    unsigned int grau_saida;
    float peso;
    No* proximo_no;

public:
    // Constructor
    No(int id);
    // Destructor
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
    // Other methods
    bool buscaAresta(int alvo_id);
    void inserirAresta(int alvo_id, float peso);
    void removeTodasArestas();
    int  removeAresta(int id, bool direcionado, No* no_alvo);
    void incrementarGrauSaida();
    void decrementarGrauSaida();
    void incrementarGrauEntrada();
    void decrementarGrauEntrada();
    Aresta* temArestaEntre(int alvo_id);
    // Auxiliar methods

};

#endif //TRABALHO_NO_H
