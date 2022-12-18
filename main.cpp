#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "include/Grafo.h"
#include "include/Aresta.h"
#include "include/No.h"
#include "src/Grafo.cpp"
#include "src/Aresta.cpp"
#include "src/No.cpp"

using namespace std;

// ofstream classe do <fstream> para criar e escrever em arquivos
// ifstream: classe do <fstream> para ler de arquivos  _ utilizado quando a ação é apenas ler arquivos 
//Função para leitura do grafo, recebe como parâmetro 
Grafo * leitura(ifstream& input_file, bool direcionado, bool peso_aresta, int peso_no){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;

    //Pegando a ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(ordem, direcionado, peso_aresta, peso_no);

    //Leitura de arquivo
    
    if(!grafo->getPesoAresta() && !grafo->getPesoNo()){  // Essa parte funciona

        while(input_file >> idNoFonte >> idNoAlvo) {

            grafo->setNumAresta();
            grafo->inserirAresta(idNoFonte, idNoAlvo, 0);

        }

    }
    else if(grafo->getPesoNo() && !grafo->getPesoAresta()){ // Essa parte funciona

        float pesoIdNofonte, pesoIdNoAlvo;

            while(input_file >> idNoFonte >> pesoIdNofonte >> idNoAlvo >> pesoIdNoAlvo) {

                grafo->setNumAresta();
                grafo->inserirAresta(idNoFonte, idNoAlvo, 0);
                No *aux = grafo->getNo(idNoFonte);
                aux->setPeso(pesoIdNofonte);
                No *aux2 = grafo->getNo(idNoAlvo);
                aux2->setPeso(pesoIdNoAlvo);

        }
    }
    else if(grafo->getPesoAresta() && !grafo->getPesoNo() ){ //Devia estar funcionando

        float edgeWeight;

        while(input_file >> idNoFonte >> idNoAlvo >> edgeWeight) {

            grafo->setNumAresta();
            grafo->inserirAresta(idNoFonte, idNoAlvo, edgeWeight);


        }

    }else if(grafo->getPesoNo() && grafo->getPesoAresta()){

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNoFonte >> nodeSourceWeight >> idNoAlvo >> nodeTargetWeight >> edgeWeight) {

            grafo->setNumAresta();
            grafo->inserirAresta(idNoFonte, idNoAlvo, edgeWeight);
            grafo->getNo(idNoFonte)->setPeso(nodeSourceWeight);
            grafo->getNo(idNoAlvo)->setPeso(nodeTargetWeight);
            No *aux = grafo->getNo(idNoFonte);
            aux->setPeso(nodeSourceWeight);
            No *aux2 = grafo->getNo(idNoAlvo);
            aux2->setPeso(nodeTargetWeight);

        }

    }

    return grafo;
}

int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Grafo Intersecao" << endl;
    cout << "[2] Grafo Diferenca" << endl;
    cout << "[3] Grafo Uniao" << endl;
    cout << "[4] Rede Pert" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Grafo* grafo1, Grafo* grafo2 ,ofstream& output_file, bool direcionado, bool peso_aresta, bool peso_no){

    switch (selecao) {

        //Interseção
        case 1:{
            int ordem1 = grafo1->getOrdem();
            int ordem2 = grafo2->getOrdem();
            if(ordem1 <= ordem2){
                grafo1->intersecao(ordem1, grafo2, direcionado, peso_aresta, peso_no);
            }
            else{
                grafo1->intersecao(ordem2, grafo2, direcionado, peso_aresta, peso_no);
            }
            break;
        }

        //Diferença
        case 2:{
            cout << "Esta entrando na diferenca";
            break;
        }

        //União
        case 3:{
            cout << "Eta entrando na uniao";
            break;
        }

        //Rede Pert
        case 4:{
            cout << "Esta entrando na Rede Pert";
            break;
        }

    }
}

int mainMenu(ofstream& output_file, Grafo* grafo, Grafo* grafo2,bool direcionado, bool peso_aresta, bool peso_no){

    int selecao = 1;

    while(selecao != 0){
        if(selecao >=1 && selecao<=5){
            selecao = menu();

            if(output_file.is_open())
               selecionar(selecao, grafo, grafo2 ,output_file, direcionado, peso_aresta, peso_no);

            else
                cout << "Unable to open the output_file" << endl;

            output_file << endl;
        }
        else{
            cout <<"Opcao selecionada nao existente \nTente novamente\n";
                        selecao = menu();

            if(output_file.is_open())
               selecionar(selecao, grafo, grafo2 ,output_file, direcionado, peso_aresta, peso_no);

            else
                cout << "Unable to open the output_file" << endl;

            output_file << endl;
        }
    }

    return 0;
}

int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram corretamente inseridos 
    //Na ordem esses parâmetros são: int argc _ quantidade de argumentos (devem ser 6) ; char const *argv[] _ nome do programa _ nome do arquivo de entrada _ nome do arquivo de saída _ se é direcionado (bool) _ se tem peso nas arestas (bool) _ se tem peso no nó (bool)
    if (argc != 6) { //Caso não seja passado os parâmetros corretos, uma mensagem de erro é impressa 
        cout << "ERROR: Expecting: ./<program_name> <input_file> <output_file> <directed> <weighted_edge> <weighted_node> " << endl;

        //Adaptação do código para testes 
        bool direcionado, peso_vertice, peso_aresta = false;

        //Adiciona manualmente as informações 
        cout<< "Direcionado: ";
        cin >> direcionado;
        cout<< "Peso vertice: ";
        cin >> peso_vertice;
        cout<< "Peso aresta: ";
        cin >> peso_aresta;

        ifstream arq_grafo; //Rotina para abertura do arquivo 
        arq_grafo.open("input/grafo_teste_naoP_5_1.txt", ios::in); //  abertura do arquivo de teste 
        ofstream output_file;
        output_file.open("arquivo_saida", ios::out | ios::trunc);

        ifstream arq_grafo2;
        arq_grafo2.open("input/grafo_teste_naoP_5_2.txt", ios::in);
        

        if(arq_grafo.is_open() && arq_grafo2.is_open()) { //Caso o arquivo abra normalmente 
            Grafo *grafo = leitura(arq_grafo, direcionado, peso_aresta, peso_vertice); //Chama a função de leitura 
            Grafo *grafo2 = leitura(arq_grafo2, direcionado, peso_aresta, peso_vertice);
            //grafo->geraListaAdjacencia("listaDeAdjacencia.txt"); //Função de criação de uma lista de adjacência para visualização
            //grafo->geraGrafoDot("grafo1.dot");
            //grafo2->geraGrafoDot("grafo2.dot");
            mainMenu(output_file,grafo,grafo2,direcionado,peso_aresta,peso_vertice);
        }
        else{
            cout << "Erro na leitura do arquivo";
        }
        //Faz parte do if _ Fechar o programa após a mensagem de erro 
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
        //atoi _ função que converte string em números inteiros
        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }else
        cout << "Unable to open " << argv[1];


    //mainMenu(output_file, graph, );



    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}