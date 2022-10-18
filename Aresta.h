#ifndef Aresta_H_INCLUDED
#define Aresta_H_INCLUDED

using namespace std;

// Definindo a classe das Arestas 
class Aresta{
private:
    int alvo_id;
    Aresta* prox_aresta;
    float peso;

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

#endif // Aresta_H_INCLUDED