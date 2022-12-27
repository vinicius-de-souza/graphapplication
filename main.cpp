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
Grafo * leituraParteI(ifstream& input_file, bool direcionado, bool peso_aresta, int peso_no){//* OK

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;

    //Pegando a ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(direcionado, peso_aresta, peso_no);

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

Grafo *leituraParteII(ifstream& input_file, bool direcionado, bool peso_aresta, int peso_no){

}

int menuParteI(){//* OK

    int selecao;

    cout << "\n                       MENU                           " << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Funcionalidades da Primeira Parte do Trabalho Pratico" << endl;
    cout << "[1] Grafo Intersecao" << endl;
    cout << "[2] Grafo Diferenca" << endl;
    cout << "[3] Grafo Uniao" << endl;
    cout << "[4] Rede Pert" << endl;
    cout << "[0] Sair\n";

    cin >> selecao;

    return selecao;

}

int menuParteII(){//* OK
    int selecao;

    cout << "\n                       MENU                           " << endl;
    cout << "--------------------------------------------------------" << endl;
    cout << "Funcionalidades da Segunda Parte do Trabalho Pratico" << endl;
    cout << "[1] Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso" << endl;
    cout << "[2] Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso Randomizado e Adaptativo " << endl;
    cout << "[3] Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso Randomizado Reativo" << endl;
    cout << "[0] Sair" << endl;

    cin >> selecao;

    return selecao;
}

void selecionarParteI(int selecao, Grafo* grafo1, ofstream& output_file, bool direcionado, bool peso_aresta, bool peso_no){//* OK

    switch (selecao) {

        //Interseção 
        case 1:{
            cout << "--------------------------------------------------------";
            cout << "\nA opcao escolhida foi a INTERSECAO!\nPara a utilizacao dessa funcao um novo grafo deve ser inserido." << "\nLembrando que o novo grafo deve ter as mesmas configuracoes do grafo principal, ou seja, deve ser:";
            if(direcionado){
                cout <<"\n[1] Direcionado";
            }else{
                cout <<"\n[1] Nao direcionado";
            }if(peso_aresta){
                cout << "\n[2] Com peso nas arestas";
            }else{
                cout << "\n[2] Sem peso nas arestas";
            }if(peso_no){
                cout << "\n[3] Com peso nos vertices";
            }else{
                cout <<"\n[3] Sem peso nos vertices";
            }string input_file_name;
            cout << "\nInsira o nome do arquivo do novo grafo:";
            cin >> input_file_name;
            ifstream input_file;
            input_file.open(input_file_name, ios::in);
            Grafo *grafo2;
            if(input_file.is_open())
                grafo2 = leituraParteI(input_file, direcionado, peso_aresta, peso_no);
            else
                cout << "Unable to open " << input_file_name;
            grafo1->intersecao(grafo2, direcionado, peso_aresta, peso_no);
            break;
        }

        //Diferença
        case 2:{
            cout << "--------------------------------------------------------" << endl;
            cout << "A opcao escolhida foi a DIFERENCA!\nPara a utilizacao dessa funcao um novo grafo deve ser inserido." << "\nLembrando que o novo grafo deve ter as mesmas configuracoes do grafo principal, ou seja, deve ser:";
            if(direcionado)
                cout <<"\n[1] Direcionado";
            else
                cout <<"\n[1] Nao direcionado";
            if(peso_aresta)
                cout << "\n[2] Com peso nas arestas";
            else
                cout << "\n[2] Sem peso nas arestas";
            if(peso_no)
                cout << "\n[3] Com peso nos vertices";
            else
                cout <<"\n[3] Sem peso nos vertices";
            string input_file_name;
            cout << "\nInsira o nome do arquivo do novo grafo:";
            cin >> input_file_name;
            ifstream input_file;
            input_file.open(input_file_name, ios::in);
            Grafo *grafo2;
            if(input_file.is_open())
                grafo2 = leituraParteI(input_file, direcionado, peso_aresta, peso_no);
            else
                 cout << "Unable to open " << input_file_name;
            grafo1->diferenca(grafo2, direcionado, peso_aresta, peso_no);
            break;
        }

        //União
        case 3:{
            cout << "--------------------------------------------------------" << endl;
            cout << "A opcao escolhida foi a UNIAO!\nPara a utilizacao dessa funcao um novo grafo deve ser inserido." << "\nLembrando que o novo grafo deve ter as mesmas configuracoes do grafo principal, ou seja, deve ser:";
            if(direcionado)
                cout <<"\n[1] Direcionado";
            else
                cout <<"\n[1] Nao direcionado";
            if(peso_aresta)
                cout << "\n[2] Com peso nas arestas";
            else
                cout << "\n[2] Sem peso nas arestas";
            if(peso_no)
                cout << "\n[3] Com peso nos vertices";
            else
                cout <<"\n[3] Sem peso nos vertices";
            string input_file_name;
            cout << "\nInsira o nome do arquivo do novo grafo:";
            cin >> input_file_name;
            ifstream input_file;
            input_file.open(input_file_name, ios::in);
            Grafo *grafo2;
            if(input_file.is_open())
                grafo2 = leituraParteI(input_file, direcionado, peso_aresta, peso_no);
            else
                cout << "Unable to open " << input_file_name;
            grafo1->uniao(grafo2, direcionado, peso_aresta, peso_no);
            break;
        }

        //Rede Pert
        case 4:{
            cout << "--------------------------------------------------------" << endl;
            cout << "A opcao escolhida foi a Rede Pert!" << endl;
            grafo1->redePert();
            break;
        }

    }
}

void selecionarParteII(int selecao, Grafo* grafo1, ofstream& output_file, bool direcionado, bool peso_aresta, bool peso_no){//* OK

    switch(selecao){

        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso 
       case 1:{
            grafo1->gulosoConstrutivo();
            break;
        }

        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso Randomizado e Adaptativo
        case 2:{
            grafo1->gulosoRandomizadoAdaptativo();
            break;
        }

        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso Randomizado Reativo
        case 3:{
            grafo1->gulosoRandomizadoReativo();
            break;
        }

    }
}

int mainMenuParteI(ofstream& output_file, Grafo* grafo, bool direcionado, bool peso_aresta, bool peso_no){//* OK

    int selecao = 1;

    while(selecao != 0){
        if(selecao >=1 && selecao<=4){
            selecao = menuParteI();

            if(output_file.is_open())
               selecionarParteI(selecao, grafo,output_file, direcionado, peso_aresta, peso_no);

            else
                cout << "Unable to open the output_file" << endl;

            output_file << endl;
        }
        else{
            cout <<"\nOpcao selecionada nao existente \nTente novamente\n";
            selecao = menuParteI();

            if(output_file.is_open())
               selecionarParteI(selecao, grafo,output_file, direcionado, peso_aresta, peso_no);

            else
                cout << "Unable to open the output_file" << endl;

            output_file << endl;
        }
    }

    return 0;
}

int mainMenuParteII(ofstream& output_file, Grafo* grafo, bool direcionado, bool peso_aresta, bool peso_no){//*OK

    int selecao = 1;

    while(selecao != 0){
        if(selecao >=1 && selecao<=3){
            selecao = menuParteII();

            if(output_file.is_open())
               selecionarParteII(selecao, grafo,output_file, direcionado, peso_aresta, peso_no);

            else
                cout << "Unable to open the output_file" << endl;

            output_file << endl;
        }
        else{
            cout <<"\nOpcao selecionada nao existente \nTente novamente\n";
            selecao = menuParteII();

            if(output_file.is_open())
               selecionarParteII(selecao, grafo,output_file, direcionado, peso_aresta, peso_no);

            else
                cout << "Unable to open the output_file" << endl;

            output_file << endl;
        }
    }

    return 0;
}

int main(int argc, char const *argv[]) {//*OK

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
        arq_grafo.open("input_parteII/Problem_50_50_3.txt", ios::in); //  abertura do arquivo de teste 
        ofstream output_file;
        output_file.open("arquivo_saida", ios::out | ios::trunc);
    

        if(arq_grafo.is_open()) { //Caso o arquivo abra normalmente 
            Grafo *grafo = leituraParteI(arq_grafo, direcionado, peso_aresta, peso_vertice); //Chama a função de leitura 
            //grafo->geraListaAdjacencia("testes/listaDeAdjacencia_grafo1.txt");
            //grafo->geraGrafoDot("testes/grafo1.dot");
            int sel;
            cout << "\nMENU"<< endl;
            cout << "--------------------------------------------------------" << endl;
            cout << "Para acessar funcionalidades da Primeira Parte do Trabalho Pratico digite [1]" << endl;
            cout << "Para acessar funcionalidades da Segunda Parte do Trabalho Pratico digite [2]" << endl;
            cin >> sel;
            if(sel==1 || sel==2){
                if(sel==1){
                    grafo = leituraParteI(arq_grafo, direcionado, peso_aresta, peso_vertice);
                    mainMenuParteI(output_file,grafo, direcionado, peso_aresta, peso_vertice);
                }
                if(sel==2){
                    grafo = leituraParteII(arq_grafo, direcionado, peso_aresta, peso_vertice);
                    mainMenuParteII(output_file,grafo, direcionado, peso_aresta, peso_vertice);
                }            
            }
            else{
                cout << "O valor informado nao e reconhecido!";
            }
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



    Grafo* grafo;

    if(input_file.is_open()){
        //atoi _ função que converte string em números inteiros
        int sel;
        cout << "\nMENU" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Para acessar funcionalidades da Primeira Parte do Trabalho Pratico digite [1]" << endl;
        cout << "Para acessar funcionalidades da Segunda Parte do Trabalho Pratico digite [2]" << endl;
        cin >> sel;
        if(sel==1 || sel==2){
            if(sel==1){
                grafo = leituraParteI(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
                mainMenuParteI(output_file,grafo, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
            }
            if(sel==2){
                grafo = leituraParteII(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
                mainMenuParteII(output_file,grafo, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));
            }            
        }
        else{
           cout << "O valor informado nao e reconhecido!";
        }
    }
    else
        cout << "Unable to open " << argv[1];

    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}