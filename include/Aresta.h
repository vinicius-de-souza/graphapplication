#ifndef TRABALHO_ARESTA_H
#define TRABALHO_ARESTA_H
using namespace std;

// Definindo a classe das Arestas

class Aresta{

//Atributos privados 
private:
    int alvo_id;
    Aresta* prox_aresta;
    float peso;

//Atributos publicos _ podem ser utilizados pelo usuario na main 
public:
    // Construtor
    Aresta(int alvo_id);

    // Destrutor
    ~Aresta();

    // Gets
    int getAlvoId();
    Aresta* getProxAresta();
    float getpeso();

    // Sets
    void setProxAresta(Aresta* Aresta);
    void setpeso(float peso);

};

#endif //TRABALHO_ARESTA_H
