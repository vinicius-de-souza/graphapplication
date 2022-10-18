#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Grafo.h"
#include "Node.h"

using namespace std;

Grafo* leitura(ifstream& input_file, int direcionado, int peso_aresta, int peso_no){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;

    //Pegando a ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem, direcionado, peso_aresta, peso_no);

    //Leitura de arquivo

    if(!grafo->getPesoAresta() && !grafo->getPesoNo()){

        while(input_file >> idNoFonte >> idNoAlvo) {

            grafo->inserirAresta(idNoFonte, idNoAlvo, 0);

        }

    }else if(grafo->getPesoAresta() && !grafo->getPesoNo() ){

        float edgeWeight;

        while(input_file >> idNoFonte >> idNoAlvo >> edgeWeight) {

            grafo->inserirAresta(idNoFonte, idNoAlvo, edgeWeight);

        }

    }else if(grafo->getPesoAresta() && !grafo->getPesoAresta()){

        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNoFonte >> nodeSourceWeight >> idNoAlvo >> nodeTargetWeight) {

            grafo->inserirAresta(idNoFonte, idNoAlvo, 0);
            grafo->getNo(idNoFonte)->setWeight(nodeSourceWeight);
            grafo->getNo(idNoAlvo)->setWeight(nodeTargetWeight);

        }

    }else if(grafo->getPesoNo() && grafo->getPesoAresta()){

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNoFonte >> nodeSourceWeight >> idNoAlvo >> nodeTargetWeight) {

            grafo->inserirAresta(idNoFonte, idNoAlvo, edgeWeight);
            grafo->inserirNo(idNoFonte)->setPeso(nodeSourceWeight);
            grafo->getNo(idNoAlvo)->setWeight(nodeTargetWeight);

        }

    }

    return grafo;
}

Grafo* leituraInstancia(ifstream& input_file, int direcionado, int peso_aresta, int peso_no){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order >> numEdges;

    //Criando objeto grafo
    Grafo* graph = new Grafo(order, direcionado, peso_aresta, peso_no);

    //Leitura de arquivo
    while(input_file >> idNodeSource >> idNodeTarget) {

        graph->inserirAresta(idNodeSource, idNodeTarget, 0);

    }

    return graph;
}

int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Complementar do grafo" << endl;
    cout << "[2] Imprimir caminhamento em largura" << endl;
    cout << "[3] Busca em profundidade" << endl;
    cout << "[4] Imprimir componentes conexas" << endl;
    cout << "[5] Imprimir componentes fortemente conexas" << endl;
    cout << "[6] Imprimir ordenacao topológica" << endl;
    cout << "[7] Árvore Geradora Mínima de Prim" << endl;
    cout << "[8] Caminho Mínimo Dijkstra" << endl;
    cout << "[9] Caminho Mínimo Floyd" << endl;
    cout << "[10] Algoritmos Gulosos (Abre um submenu)" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* graph, ofstream& output_file){

    switch (selecao) {

        //Complementar
        case 1:{

            break;
        }

            //BFS
        case 2:{

            break;
        }

            //DFS
        case 3:{

            break;
        }

            //Componentes Conexas
        case 4:{

            break;
        }

            //Componentes Fortementes Conexas
        case 5:{

            break;
        }

            //Ordenação Topológica
        case 6:{

            break;
        }

        case 7:{

            break;
        }

            //Algoritmo de Prim
        case 8:
        {

            break;
        }

            //Algoritmo de Dijkstra
        case 9:
        {

            break;
        }

            //Algoritmo de Floyd
        case 10:
        {

            break;

        }

    }
}

int mainMenu(ofstream& output_file, Grafo* grafo){

    int selecao = 1;

    while(selecao != 0){
        system("clear");
        selecao = menu();

        if(output_file.is_open())
            selecionar(selecao, grafo, output_file);

        else
            cout << "Unable to open the output_file" << endl;

        output_file << endl;

    }

    return 0;
}



int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;


    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream output_file;
    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);



    Grafo* graph;

    if(input_file.is_open()){

        graph = leituraInstancia(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }else
        cout << "Unable to open " << argv[1];


    mainMenu(output_file, graph);



    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}