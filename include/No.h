#ifndef TRABALHO_NO_H
#define TRABALHO_NO_H
#include "Aresta.h" 

using namespace std;

// Definição da Classe No

class No{
    // Atributos privados 
private:
    Aresta* primeira_aresta; 
    Aresta* ultima_aresta;
    int id; //Id do no _ id do usuario 
    int idInterno; // Id do no _ id de controle pro programa 
    unsigned int grau_entrada;
    unsigned int grau_saida;
    float peso; 
    No* proximo_no; 


    // Atributos publicos _ podem ser utilizados pelo usuario na main 
public:

    int grau; 

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
    float getPesoNo();
    No* getProxNo();
    int getGrau();
    int getIdInterno();

    // Setters
    void setProxNo(No* No);
    void setPeso(float peso);
    void setGrau();
    void setIdInterno(int idInterno);

    // Outras funções
    bool buscaAresta(int alvo_id);
    void inserirAresta(int alvo_id, float peso);
    void removeTodasArestas();
    void removeAresta(int id, bool direcionado, No* no_alvo);
    void incrementarGrauSaida();
    void decrementarGrauSaida();
    void incrementarGrauEntrada();
    void decrementarGrauEntrada();
    void setPrimeiraAresta(Aresta* aresta);
    Aresta* temArestaEntre(int alvo_id);
};

#endif //TRABALHO_NO_H
