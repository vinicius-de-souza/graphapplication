#include "../include/Grafo.h"
#include "../include/No.h"
#include "../include/Aresta.h"
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime> 
#include "time.h" // - > Referência [2]

using namespace std;

// Construtor _ Inicializa o grafo recebendo como parâmetro as funções booleanas que indicam se o grafo é direciondo, se há peso na aresta e se há peso no nó
Grafo::Grafo(bool direcionado, bool peso_aresta, bool peso_no) {

    this->direcionado = direcionado;
    this->peso_aresta = peso_aresta;
    this->peso_no = peso_no;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;
    this->ordem = 0;

}

// Destrutor _ Exclui todos os nós e suas arestas, ou seja, exclui o grafo por inteiro
Grafo::~Grafo(){

    No *proximo_no = this->primeiro_no;

    while (proximo_no != nullptr){

        proximo_no->removeTodasArestas();
        No *no_auxiliar = proximo_no->getProxNo();
        delete proximo_no;
        proximo_no = no_auxiliar;

    }
}


// Getters


//Retorna o número de arestas do grafo
int Grafo::getNumeroArestas(){

    return this->numero_arestas;
}

//Verifica se o grafo é direcionado ou não _ função booleana
bool Grafo::getDirecionado(){

    return this->direcionado;

}

//Verifica se o grafo tem peso na aresta ou não _ função booleana
bool Grafo::getPesoAresta() {

    return this->peso_aresta;

}

//Verifica se o grafo tem peso no nó ou não _ função booleana
bool Grafo::getPesoNo(){

    return this->peso_no;

}

//Retorna um objeto nó referente ao primeiro nó do grafo
No *Grafo::getPrimeiroNo(){

    return this->primeiro_no;

}

//Retorna um objeto nó referente ao último nó do grafo
No *Grafo::getUltimoNo(){

    return this->ultimo_no;

}

//Recebe como parâmetro o id de um nó e retorna o objeto nó referente aquele id
No *Grafo::getNo(int id){ 

    No * aux = this->getPrimeiroNo();

    while(aux != nullptr){

        if(aux->getId() == id)
            return aux;

        else
            aux = aux->getProxNo();

    }

    return nullptr;
}

//Função que retorna a ordem do grafo
int Grafo::getOrdem(){

    return this->ordem;

}

//Setters

//Define o número de arestas do grafo 
void Grafo::setNumAresta(){ 

    this->numero_arestas = this->numero_arestas + 1;

}


// Outras funções 

//Inserção interna de nós, utilizada na hora da leitura do grafo _ não muda a ordem pois a ordem já está sendo informada no início da leitura do arquivo 
void Grafo::inserirNo(int id){ 
    if(this->primeiro_no == nullptr){ //Caso o grafo esteja vazio 

        No * novoNo = new No(id);
        this->primeiro_no = novoNo;
        this->ultimo_no = novoNo;
        return;

    }

    if(this->getNo(id) == nullptr){

        No * novoNo = new No(id);
        this->ultimo_no->setProxNo(novoNo);
        this->ultimo_no = this->ultimo_no->getProxNo();
        return;

    }
}

//Inserção de arestas através do objeto grafo _ recebe os nós que será ligados e o peso da aresta 
void Grafo::inserirAresta(int id, int target_id, float weight){

    if(this->getNo(id) == nullptr){ //Caso ainda não exista o nó de onde sai a aresta
        this->inserirNo(id);
    }

    if(this->getNo(target_id) == nullptr){ //Caso ainda não exista o nó de entrada da aresta
        this->inserirNo(target_id);
    }

    this->getNo(id)->inserirAresta(target_id, weight); //Chama a função de inserção de aresta da classe do nó

    if(!this->getDirecionado()) //Caso não seja um grafo direcionado
    {
        this->getNo(target_id)->inserirAresta(id, weight);
    }

}

//Função para a remoção de um nó, recebe como parâmetro o id do nó que deve ser removido 
void Grafo::removerNo(int id){ 

    //Primeiro caso, o grafo é direcionado 
    if(direcionado){

        No *noRemover = this->getPrimeiroNo();
        No *previo = nullptr;

        if(!procurarNo(id)){ //Verifica se o nó solicitado para remoção existe 

            cout << "No nao encontrado para remocao!";

        }

        else{ // Caso o nó exista _ Vamos encontra-lo na lista de adjacência e remove-lo ligando o nó prévio ao seu p´roximo nó

            for(noRemover; noRemover->getId()!= id; noRemover = noRemover->getProxNo())

                previo = noRemover;
        
            if(previo == nullptr)

                primeiro_no = noRemover->getProxNo();

            
            else

                previo->setProxNo(noRemover->getProxNo());
            
        }
    }
    
    //Segundo caso, o grafo não é direcionado
    else{

        No *noRemover = this->getPrimeiroNo();
        No *previo = nullptr;

        if(!procurarNo(id))//Verifica se o nó solicitado para remoção existe 

            cout << "No nao encontrado para remocao!";
        
        else{

            for(noRemover; noRemover->getId()!= id; noRemover = noRemover->getProxNo()){ //Itera na lista de nós até encontrar o nó que deve ser removido

                previo = noRemover;

            }

            Aresta *auxAre = noRemover->getPrimeiraAresta(); //Pega a primeira aresta do nó que deve ser removido 

            for(auxAre; auxAre != nullptr; auxAre = auxAre->getProxAresta()){

                int auxId = auxAre->getAlvoId();
                No *aux = getNo(auxId);

                Aresta *areAux = aux->getPrimeiraAresta();
                Aresta *previa = nullptr;

                for(areAux; areAux->getAlvoId() != id; areAux = areAux->getProxAresta()){

                    previa = areAux;

                }

                if(previa == nullptr)

                    aux->setPrimeiraAresta(areAux->getProxAresta());
                
                else

                previa->setProxAresta(areAux->getProxAresta());
                
            }

            if(previo == nullptr)

                primeiro_no = noRemover->getProxNo();
            
            else
                previo->setProxNo(noRemover->getProxNo());
            
        }
    }
}

//Função que verifica se o nó referente ao id passado como parâmetro existe no grafo _ função booleana 
bool Grafo::procurarNo(int id){ 

    No * aux = this->getNo(id);

    if(aux != nullptr)

        return true;

    return false;
}

//Função que recebe como parâmetro dois ids (id do nó de saída da aresta e id do nó de entrada da aresta) e retorna o valor do peso da aresta entre elas
float Grafo::getAresta(int idSaida, int idAlvo){ 
    if(!peso_aresta)  //Caso não haja peso nas arestas desse grafo

        return 0;

    else{

        No *auxNo = this->getNo(idSaida);

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){

            if(auxAresta->getAlvoId()==idAlvo)

                return auxAresta->getpeso();
                 
        }
    }

    return 404;

}



// Extra _ Criados para melhor visualização do programa


//Função criada para melhor visualização do programa _ gera a lista de adjacência do grafo
void Grafo::geraListaAdjacencia(string output){ 

    //Recebe como parâmetro o nome do arquivo de saída

    ofstream output_file; //Rotina para abertura e escrita do arquivo
    output_file.open(output, ios::trunc);

    if(output_file.is_open())

        auxGeraListaAdjacencia(output_file); //Função auxiliar para geração dessa lista
    
    else //Mensagem de erro caso não seja possível gerar arquivo de lista de adjacência 
        cout << endl << "Nao foi possivel abrir o arquivo " << output;
    
}

//Função criada para melhor visualização do programa _ auxilia na geração da lista de adjacência do grafo
void Grafo::auxGeraListaAdjacencia(ofstream &output_file){
    //Recebe como parâmetro o arquivo de saida

    for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        output_file << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            output_file << " " << auxAresta->getAlvoId() << " ";
        
        }

        output_file << "]" << endl;

    }

}

//Função para geração do arquivo de saída em .dot _ Recebe como parâmetro o arquivo de saída
void Grafo::geraGrafoDot(string output){

    ofstream output_file; //Rotina para abertura e escrita do arquivo 
    output_file.open(output, ios::trunc);

    if(output_file.is_open())

        auxGeraGrafoDot(output_file);
    
    else//Mensagem de erro caso não seja possível gerar arquivo de lista de adjacência 

        cout << endl << "Nao foi possivel abrir arquivo <" << output ;
    
}

//Função para geração do arquivo de saída em .dot _  Recebe como parâmetro o arquivo de saída 
void Grafo::auxGeraGrafoDot(ofstream &output_file){  

    //Caso o grafo seja direcionado 
    if(direcionado){
        output_file << "strict digraph G {\n"; //Definição própria do .dot para geração de grafos direcionados sem multiaresta
        for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

            for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre todas as arestas do nó

                output_file << "\n" << "    " << auxNo->getId() << " -> ";
                output_file << " " << auxAresta->getAlvoId();

                if(peso_aresta)

                    output_file << " " << "[label=\" " << this->getAresta(auxNo->getId(), auxAresta->getAlvoId()) << "\"]";

        }
    }
        output_file << "\n" << "\n }";
    }
    
    //Caso o grafo não seja direcionado   
    else{
        output_file << "strict graph G { \n \n"; //Definição própria do .dot para geração de grafos não direcionados sem multiaresta
        for( No * auxNo = this->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

            for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre todas as arestas do nó

                output_file << "\n" << "    " << auxNo->getId() << " -- ";
                output_file << " " << auxAresta->getAlvoId();

                if(peso_aresta)

                    output_file << " " << "[label=\" " << this->getAresta(auxNo->getId(), auxAresta->getAlvoId()) << "\"]";
                
            }
        }

        output_file << "\n" << "\n }";

    }
}


// Implementações necessárias Parte I


//Função de interseção de dois grafos _ Recebe como parâmetro o segundo grafo para realização da função, se o grafo é direcionado ou não, se o grafo tem peso na aresta ou não e se o grafo tem peso no nó ou não
void Grafo::intersecao(ofstream &output_file, Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no){ 

    No* no_grafo1 = this->getPrimeiroNo(); 
    No* no_grafo2 = grafo2->getPrimeiroNo();

    Grafo *grafo_inter = new Grafo(direcionado, peso_aresta, peso_no);

    for(no_grafo1; no_grafo1 != nullptr ; no_grafo1 = no_grafo1->getProxNo()){ //Percorre os nós do primeiro grafo

        for(no_grafo2 = grafo2->getPrimeiroNo(); no_grafo2 != nullptr; no_grafo2 = no_grafo2->getProxNo()){ //Percorre os nós do segundo grafo 

            if(no_grafo1->getId() == no_grafo2->getId()){ //Caso encontre o mesmo nó nos grafos, algo deve ser feito 

                for(Aresta * auxAresta = no_grafo1->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre as arestas do primeiro nó 

                    for(Aresta * auxAresta2 = no_grafo2->getPrimeiraAresta(); auxAresta2 != nullptr; auxAresta2 = auxAresta2->getProxAresta()){ //Percorre as arestas do segundo nó

                        if(auxAresta->getAlvoId() == auxAresta2->getAlvoId()){ //Caso uma aresta igual seja encontrada 

                            if(this->getPesoAresta() && auxAresta->getpeso() == auxAresta2->getpeso()) //Se o grafo tenha peso nas arestas, além da aresta existir é necessário garantir que seus pesos são iguais 

                                    grafo_inter->inserirAresta(no_grafo1->getId(),auxAresta2->getAlvoId(),auxAresta->getpeso()); // A aresta é adicionada no grafo de interseção
                            
                            if(!this->getPesoAresta()) // Se o grafo não tem peso nas arestas

                                    grafo_inter->inserirAresta(no_grafo1->getId(),auxAresta2->getAlvoId(),0); // A aresta é adicionada no grafo de interseção

                        }

                    }   

                }

            }

        }

    }

    grafo_inter->geraGrafoDot("testes/intersecao.dot"); //Chamada da função de geração do arquivo .dot 

    //Saida no arquivo _ Saida em forma de lista de adjacência 
    output_file.clear();

    output_file << "\n\nGrafo gerado a partir da intersecao\n" << endl;

    for( No * auxNo = grafo_inter->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        output_file << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            output_file << " " << auxAresta->getAlvoId() << " ";
        
        }

        output_file << "]" << endl;

    }    

    

    //Saida em tela do novo grafo _ Saida em forma de lista de adjacência 
    cout << "\n\nGrafo gerado a partir da intersecao\n" << endl;

    for( No * auxNo = grafo_inter->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        cout << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            cout << " " << auxAresta->getAlvoId() << " ";
        
        }

        cout << "]" << endl;

    }    

    cout << "\nFinalizacao da Funcao Intersecao\n";
    cout << "Arquivo .dot: \"intersecao.dot\" \n\n";

}

//Função da diferença de dois grafos _ Recebe como parâmetro o segundo grafo para realização da função, se o grafo é direcionado ou não, se o grafo tem peso na aresta ou não e se o grafo tem peso no nó ou não
void Grafo::diferenca(ofstream &output_file, Grafo* grafo2, bool direcionado, bool peso_aresta, bool peso_no){ 

    No *no_grafo1 = this->getPrimeiroNo();
    No *no_grafo2 = grafo2->getPrimeiroNo();

    Grafo* grafo_dif = new Grafo(direcionado, peso_aresta, peso_no);

    for(no_grafo1; no_grafo1 != nullptr; no_grafo1 = no_grafo1->getProxNo()){ //Percorre todos os nós do primeiro grafo

        for(Aresta *aresta = no_grafo1->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){ //Percorre cada aresta do nó 

            if(peso_aresta) //Caso tenha peso na aresta, é realizada essa inserção de aresta 

                grafo_dif->inserirAresta(no_grafo1->getId(),aresta->getAlvoId(),aresta->getpeso());

            else // Caso não tenha peso na aresta, é realizada essa inserção de aresta

                grafo_dif->inserirAresta(no_grafo1->getId(),aresta->getAlvoId(),0);

        }

    }

    //Nesse estágio, o grafo de diferença é igual ao grafo 1, agora ao percorrer o grafo 2 iremos remover todos os nós e arestas que são iguais 

    for(no_grafo2; no_grafo2 != nullptr; no_grafo2 = no_grafo2->getProxNo()){ //Percorrendo os nós do grafo 2

        No *aux = grafo_dif->getNo(no_grafo2->getId());

        for(Aresta *aresta2 = no_grafo2->getPrimeiraAresta(); aresta2 != nullptr; aresta2 = aresta2->getProxAresta()){ // Percorre as arestas do nó

            for(Aresta *aresta1 = aux->getPrimeiraAresta(); aresta1 != nullptr; aresta1 = aresta1->getProxAresta()){ // Percorre as arestas do grafo de diferença

                if(aresta2->getAlvoId() == aresta1->getAlvoId()) //Se encontrar arestas iguais, essa aresta é removida 

                    grafo_dif->getNo(no_grafo2->getId())->removeAresta(aresta2->getAlvoId(),direcionado,grafo_dif->getNo(aresta2->getAlvoId()));
                
            }

        }

    }

    //Chamada da função para geração do arquivo .dot
    grafo_dif->geraGrafoDot("testes/diferenca.dot");

    //Saida no arquivo do novo grafo _ Saida em forma de lista de adjacência 

    output_file << "\n\nGrafo gerado a partir da diferenca\n" << endl;

    for( No * auxNo = grafo_dif->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        output_file << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            output_file << " " << auxAresta->getAlvoId() << " ";
        
        }

        output_file << "]" << endl;

    }    


    //Saida em tela do novo grafo _ Saida em forma de lista de adjacência 
    cout << "\n\nGrafo gerado a partir da diferenca\n" << endl;

    for( No * auxNo = grafo_dif->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        cout << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            cout << " " << auxAresta->getAlvoId() << " ";
        
        }

        cout << "]" << endl;

    }

    cout << "\nFinalizacao da Funcao Diferenca\n";
    cout << "Arquivo de saida: \"diferenca.dot\" \n\n";

}
    
//Função de união de dois grafos _ Recebe como parâmetro o segundo grafo para realização da função, se o grafo é direcionado ou não, se o grafo tem peso na aresta ou não e se o grafo tem peso no nó ou não    
void Grafo::uniao(ofstream &output_file, Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no){ 

    Grafo* grafo_uni = new Grafo(direcionado,peso_aresta,peso_no);
    
    No* no_grafo1 = this->getPrimeiroNo();
    No *no_grafo2 = grafo2->getPrimeiroNo();

    // Adicionando o grafo 1 ao grafo uniao

    for(no_grafo1; no_grafo1 != nullptr; no_grafo1 = no_grafo1->getProxNo()){ //Percorre os nós do primeiro grafo

        for(Aresta * auxAresta = no_grafo1->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre as arestas do nó

            if(!peso_aresta) //Caso os grafos não tenham peso nas arestas

                grafo_uni->inserirAresta(no_grafo1->getId(),auxAresta->getAlvoId(),0);
            
            else // Caso o grafo tenha peso nas arestas 

                grafo_uni->inserirAresta(no_grafo1->getId(),auxAresta->getAlvoId(),auxAresta->getpeso());
            
        }

    }

    // Adicionando o grafo 2 ao grafo uniao

    for(no_grafo2; no_grafo2 != nullptr; no_grafo2 = no_grafo2->getProxNo()){ //Percorre os nós do segundo grafo

        for(Aresta * auxAresta = no_grafo2->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre as arestas do nó

            if(!peso_aresta) //Caso os grafos não tenham peso nas arestas

                grafo_uni->inserirAresta(no_grafo2->getId(),auxAresta->getAlvoId(),0);
            
            else //Caso os grafos tenham peso nas arestas

                grafo_uni->inserirAresta(no_grafo2->getId(),auxAresta->getAlvoId(),auxAresta->getpeso());
            
        }

    }
    
    //Chamada da função para geração do arquivo .dot
    grafo_uni->geraGrafoDot("testes/uniao.dot");

    //Saida em arquivo do novo grafo _ Saida em forma de lista de adjacência 
    output_file << "\n\nGrafo gerado a partir da uniao\n" << endl;

    for( No * auxNo = grafo_uni->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        output_file << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            output_file << " " << auxAresta->getAlvoId() << " ";
        
        }

        output_file << "]" << endl;

    }    


   //Saida em tela do novo grafo _ Saida em forma de lista de adjacência 
    cout << "\n\nGrafo gerado a partir da uniao\n" << endl;

    for( No * auxNo = grafo_uni->getPrimeiroNo(); auxNo != nullptr ; auxNo = auxNo->getProxNo()){ //Percorre todos os nós do grafo

        cout << auxNo->getId() << " - [";

        for(Aresta * auxAresta = auxNo->getPrimeiraAresta(); auxAresta != nullptr; auxAresta = auxAresta->getProxAresta()){ //Percorre toda as aresta do nó 

            cout << " " << auxAresta->getAlvoId() << " ";
        
        }

        cout << "]" << endl;

    }

    cout << "\nFinalizacao da Funcao Uniao\n";
    cout << "Arquivo de saida: \"uniao.dot\" \n\n";


}


//Implementações Parte II

int atualizaAlfa(vector<float>prob, int aleatorio){ //Recebe um vector de probabilidades, um inteiro aleatório e retorna o novo valor de alfa a ser utilizado com base nas probabilidades

    if(aleatorio <= prob[0]*1000)
            return 0;
    else if((aleatorio > (prob[0] * 1000)) && (aleatorio <= ((prob[0] +prob[1]) * 1000)))
            return 1; 
    else if((aleatorio > ((prob[0] + prob[1]) * 1000)) && (aleatorio <= ((prob[0] + prob[1] + prob[2]) * 1000)))
            return 2;
    else if((aleatorio > ((prob[0] + prob[1] + prob[2]) * 1000)) && (aleatorio <= ((prob[0] + prob[1] + prob[2] + prob[3]) * 1000)))
            return 3;
    else if((aleatorio > ((prob[0] + prob[1] + prob[2] + prob[3]) * 1000)) && (aleatorio <= 1000))
            return 4;

    return 404;

}

int partition(vector<No*> &arr, int low, int high){ //Função auxiliar de particionamento do algoritmo de QuickSort
        int pivot = high;
        int j = low;
        for(int i=low;i<high;++i){
            if((arr[i]->getPesoNo()/arr[i]->getGrau()) < (arr[pivot]->getPesoNo()/arr[pivot]->getGrau())){
             swap(arr[i],arr[j]);
                ++j;
            }
        }
        swap(arr[j],arr[pivot]);
        return j;
    }
    
void quickSort(vector<No*> &arr, int low, int high){ //Função principal do QuickSort. *Retirado da web e referenciado no trabalho (referências na main.cpp)
        
        if (low < high) {

            int pi = partition(arr, low, high); 
    
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

bool Grafo::ehDominante(vector<int> sol){ //Função que verifica se um subconjunto é dominante. Recebe como parâmetro um vetor de int (subconjunto).

    No *aux = this->getPrimeiroNo();

    for(aux; aux != nullptr; aux = aux->getProxNo()){

        int chave = aux->getId();

        if(!(std::count(sol.begin(), sol.end(), chave)))
        {

            bool coberto = false;

            for(Aresta *aresta = aux->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
            {
                
                if(std::count(sol.begin(), sol.end(), aresta->getAlvoId())){

                    coberto = true;
                    break;

                }

            }

            if(!coberto){
                return false;
            }
        }
        
    }

    return true;

}

// Função de implementação do algoritmo Guloso Construtivo: a heurística utilizada foi ordenar a lista de candidatos (lista dos nós) de forma crescente a partir da relação peso/grau de cada nó, com essa ordenação foi possível estabelecer os vértices que devem entrar na solução (sempre os primeiros da lista). Após cada vértice ser inserido no conjunto solução ele e seus adjacentes saem da lista de candidatos. Essa iteração ocorre até que o conjunto solução seja dominante (essa condição é verificada pela função ehDominante())
void Grafo::gulosoConstrutivo(ofstream& output_file){  

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado
        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

    time_t start, end; //Utilizado para contagem de tempo da função 
    time(&start);

    vector<int> solucao; //Criação da lista dos vértices de solução (inicalmente vazia) _ Armazena os ids dos vértices 
    vector<No*> listaCandidatos; //Criação da lista de todos os vértices do grafo 

    float  peso_total = 0;//Variável que armazena os valores dos pesos para análise 

    float melhor_peso; //Variável que armazena a melhor solução do problema 

    //É necessário preencher o vetor de candidatos com todos os vértices do grafo
    No* aux = this->getPrimeiroNo();  
    for(aux; aux != nullptr; aux = aux->getProxNo()){ 

        listaCandidatos.push_back(aux);
        melhor_peso =  melhor_peso + aux->getPesoNo(); //Dessa forma eu inicializo o menor peso com a soma total dos pesos de todos os vértices (maior peso possível)

    }

    int size = listaCandidatos.size();

    while(!ehDominante(solucao)){ //Iteração que ocorre até que o conjunto solução seja dominante 

        size = listaCandidatos.size(); // A cada iteração é necessário verificar o tamanho da lista de candidatos 

        quickSort(listaCandidatos,0,size-1); //A função quickSort é chamada para ordenar a lista de candidatos. É passado como parâmetro a lista, o index do primeiro nó e o index do último nó. O quickSort ordena de forma crescente os vértices a partir da relação peso/grau de cada nó. Como temos um problema de minimização, escolhemos o menor valor de peso/grau. 

        solucao.push_back(listaCandidatos[0]->getId()); // O vértice selecionado no looping entra na solução _ No Algoritmo Guloso Construtivo sempre adicionamos na solução o vértice melhor rankeado de acordo com a heurística

        peso_total = peso_total + listaCandidatos[0]->getPesoNo(); //Somando os pesos 

        //Atualização da lista de candidatos _ Retiro da lista de candidatos o valor que acabou de entrar na solução e seus adjacentes 
        auto it = listaCandidatos.begin();

        No *noaRemover = this->getNo(listaCandidatos[0]->getId());

        for(Aresta* aresta = noaRemover->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){ //Iteração para remover da lista atual de candidatos todos os vértices que são adjacentes ao vértice escolhido para entrar na solução
            
            int noRemover = aresta->getAlvoId();
            
            for(it; it != listaCandidatos.end(); it++){
    
                if((*it)->getId() == noRemover){

                    listaCandidatos.erase(it);
                    break;

                }

            }

        }

        it = listaCandidatos.begin();
            
        for(it; it != listaCandidatos.end(); it++){ //Removo da lista de candidatos o vértice que entrou na solução 
            if((*it)->getId() == noaRemover->getId()){

                listaCandidatos.erase(it);
                break;

            }

        }

    }

    time(&end); //Utilizado para contagem de tempo da função
    double time_taken = double(end - start);

    //Saidas em tela do Algoritmo 
    cout << "---------------------------------------------------------------------------------------------------------------------" <<endl;

    cout << "\nQualidade da solucao: " << peso_total << endl;

    cout << "\nTempo de processamento: " << time_taken << "s" << endl;

    cout << "\nO conjunto solucao encontrado sempre eh viavel pois pela heuristica sempre entregamos um conjunto dominante" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------" <<endl;

    //Saida do arquivo
    output_file.clear();
        
    output_file << "Qualidade final encontrada " << peso_total;

    output_file << "\n";

    output_file << "Conjunto dos Vertices Solucao: [";

    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        output_file << ' ' << *it;

    output_file << " ]" << endl;


}

// Função de implementação do Algoritmo Guloso Adaptativo _ A heurística utilizada foi ordenar a lista de candidatos de forma com que esse vetor contenha de forma crescente a função peso/grau para cada nó. Com esse critério escolhemos de forma aleatória (levando em conta as probabilidades) o valor de alfa e consequentemente um vértice na posição gerada aleatoriamente e o adicionamos no conjunto solução, após isso atualizamos a lista de candidatos, retirando os vértices que entraram na solução E seus adjacentes. E por fim, a cada iteração verificamos se o conjunto solução é dominante, quando isso ocorrer, o nosso código está finalizado (para aquela iteração).
void Grafo::gulosoRandomizadoAdaptativo(ofstream& output_file){ 

    unsigned seed = static_cast <unsigned> (time(0)); //Será utilizado para geração de números aleatório dentro da construção dos Algoritmos Gulosos 
    srand(seed); 

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado

        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

    time_t start, end; //Utilizado para contagem de tempo da função 
    time(&start);

    int iteracoes = 2500; 

    float melhor_peso = 0; //Variável que armazena a melhor solução das iterações
    float peso = 0; //Variável que armazena o peso a cada iteração 
    int i = 1; //Variável utilizada para controle das iterações 
    int bloco = 250; // Variável que controla quando iremos atualizar a lista de probabilidades
    float k;  //Variável utilizada para manipulação do valor aleatório


    vector<int> solucao; //Vetor para armazenar o conjunto solucao durante as iterações
    vector<int> melhor_solucao; //Vetor para armazenar o conjunto final de melhor solução
    vector<No*> listaCandidatos; //Vetor de candidatos para a solução

    //Inicialização dos vetores de média, alfa, probabilidades, conAlfas e totalAlfas
    vector<float> alfas;
    vector<float> contAlfas;
    vector<float> totalAlfas;
    vector<float> probabilidades;
    vector<float> medias;

    // Valores pré-definidos de alfa
    alfas.push_back(0.05);
    alfas.push_back(0.10);
    alfas.push_back(0.15);
    alfas.push_back(0.30);
    alfas.push_back(0.50);

    //Cada alfa inicia com a mesma probabilidade 
    probabilidades.push_back(0.20);
    probabilidades.push_back(0.20);
    probabilidades.push_back(0.20);
    probabilidades.push_back(0.20);
    probabilidades.push_back(0.20);

    //Vetor que será responsável por armazenar a soma dos pesos _ Inicia com valor 0 _ Será utilizado para cálculo das médias de cada alfa
    totalAlfas.push_back(0);
    totalAlfas.push_back(0);
    totalAlfas.push_back(0);
    totalAlfas.push_back(0);
    totalAlfas.push_back(0);

    //Vetor responsável por contar as vezes em que cada valor de alfa é utilizado _ Inicia com valor 0 _ Será utilizado para cálculo das médias de cada alfa
    contAlfas.push_back(0);
    contAlfas.push_back(0);
    contAlfas.push_back(0);
    contAlfas.push_back(0);
    contAlfas.push_back(0);

    //Vetor de médias _ _ Inicia com valor 0 
    medias.push_back(0);
    medias.push_back(0);
    medias.push_back(0);
    medias.push_back(0);
    medias.push_back(0);

    //Iteração para calcular o valor que a variável melhor_peso deve iniciar _ Se inicia com o valor da soma de todos os pesos (maior valor possível)
    No* auxn = this->getPrimeiroNo();  

    for(auxn; auxn != nullptr; auxn = auxn->getProxNo()){ 

        melhor_peso =  melhor_peso + auxn->getPesoNo(); //Dessa forma eu inicializo o meu menor peso com a soma total dos pesos de todos os vértices (maior peso possível)

    }

    while(i<iteracoes){ //Processamento para controle do while


        if( i % bloco == 0){ //Caso isso ocorra, é momento de atualizar a lista de probabilidades do alfa 

            //Criação de um vetor q que recebe a cada posição relativa de alfa (de 0 a 4) o valor de melhor_peso (encontrado até agora nas iterações) dividido pelas médias de cada valor de alfa _ Esse valor é elevado a uma constante delta = 10.
            vector<double> q;
            q.push_back(powf((melhor_peso/medias[0]),10.0));
            q.push_back(powf((melhor_peso/medias[1]),10.0));
            q.push_back(powf((melhor_peso/medias[2]),10.0));
            q.push_back(powf((melhor_peso/medias[3]),10.0));
            q.push_back(powf((melhor_peso/medias[4]),10.0));

            double sq = 0;

            //Iteração que encontra o valor da variável sq _ Variável que armazena a soma dos valores de q[alfa] 
            for (int c = 0; c< 5; c++) {
                sq += q[c];
            }

            //Iteração que calcula os novos valores de probabilidades _ As novas probabilidades recebem o valor de q[alfa] divido pelo valor de sq
            for (int d = 0; d< 5; d++) {
                probabilidades[d] = q[d]/sq;
            }
      
        }   

        i++; //Controle das iterações 

        //A cada nova iteração minha lista de candidatos precisa ser esvaziada e novamente preenchida
        listaCandidatos.clear(); 

        No* aux = this->getPrimeiroNo();  
        for(aux; aux != nullptr; aux = aux->getProxNo()){ 

            listaCandidatos.push_back(aux); //A lista de candidatos recebe todos os vértices 

        }

        //Esvaziando a lista de soluções para uma nova iteração 
        solucao.clear(); 

        int size = listaCandidatos.size(); //Variável que armazena o tamanho da lista de candidatos 
        
        int sol; //Variável que será utilizada para adicionar no vetor de solução o id do vértice escolhido a cada iteração 

        quickSort(listaCandidatos,0,size-1); //A função quickSort é chamada para ordenar a lista de candidatos. É passado como parâmetro a lista, o index do primeiro nó e o index do último nó. O quickSort ordena de forma crescente os vértices a partir da relação peso/grau de cada nó.

        //Seleciono o valor de alfa de acordo com as probabilidades 
        int aInt = rand() % 1000;
        int a = atualizaAlfa(probabilidades, aInt);
        float alfa = alfas[a];

        contAlfas[a]++; //Cada vez que um valor de alfa é utilizado devemos atualizar o valor de contAlfas na posição do alfa 

        peso = 0; // Para iniciar uma nova iteração o peso deve ser zerado para comparação 

        while(!ehDominante(solucao)){ //Iteração para encontrar meu conjunto solução _ Só para quando o conjunto encontrado é dominante 
            
            //Geração do valor aleatório 
            float k = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/(alfa*size)-1)); 
            int kInt = static_cast<int>(k); //Converte valor aleatório de float para int

            //Adiciono na lista de solução o id do vértice escolhido 
            sol = listaCandidatos[kInt]->getId();
            solucao.push_back(sol);

            //Incrementando o grau com o peso do novo nó que entrou na solução 
            peso = peso + listaCandidatos[kInt]->getPesoNo();

            //Atualiza lista de Candidatos _ Nessa parte retiramos da lista de Candidatos os vértices que entram na solução e seus adjacentes 
            auto it = listaCandidatos.begin();

            No *noaRemover = this->getNo(listaCandidatos[kInt]->getId());

            for(Aresta* aresta = noaRemover->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){ //Iteração para remover da lista atual de candidatos todos os vértices que são adjacentes ao vértice escolhido para entrar na solução
            
                int noRemover = aresta->getAlvoId();
            
                for(it; it != listaCandidatos.end(); it++){
    
                    if((*it)->getId() == noRemover){

                        listaCandidatos.erase(it);
                        break;

                    }

                }

            }

            it = listaCandidatos.begin();
            
            for(it; it != listaCandidatos.end(); it++){//Removo da lista de candidatos o vértice da posição kInt (referente ao alfa)
    
                if((*it)->getId() == noaRemover->getId()){

                    listaCandidatos.erase(it);
                    break;

                }

            }
            
        }

        //Atualização do vetor totalAlfas _ O vetor é somado com o novo valor de peso encotrado 
        totalAlfas[a] = totalAlfas[a] + peso; 

        //Atualização do vetor medias _ O vetor recebe o valor do totalAlfas dividido pelo contAlfas
        medias[a] = (totalAlfas[a] / contAlfas[a]);

        //A cada iteração guarda a melhor solução até o momento 
        if(peso < melhor_peso){

            melhor_peso =  peso;
            melhor_solucao = solucao;    

        }
    }

    time(&end); //Utilizado para contagem de tempo da função
    double time_taken = double(end - start);

    //Saidas em tela do Algoritmo 

    cout << "---------------------------------------------------------------------------------------------------------------------" <<endl;

    cout << "\nQualidade da solucao: " << melhor_peso << endl;

    cout << "\nTempo de processamento: " << time_taken << "s" << endl;

    cout << "\nSemente de randomizacao: " << seed << endl;

    cout << "\nO conjunto solucao encontrado sempre eh viavel pois pela heuristica sempre entregamos um conjunto dominante" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------" <<endl;

    //Saida do arquivo
    output_file.clear();
        
    output_file << "Qualidade final encontrada " << melhor_peso;

    output_file << "\n";

    output_file << "Conjunto dos Vertices Solucao: [";

    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        output_file << ' ' << *it;

    output_file << " ]" << endl;

}

// Função de implementação do Algoritmo Guloso Randomizado Reativo _ A heurística utilizada foi ordenar a lista de candidatos de forma com que esse vetor contenha de forma crescente a função peso/grau para cada nó. Com esse critério escolhemos de forma aleatória(de acordo com o valor de alfa)um vértice e o adicionamos no conjunto solução, após isso atualizamos a lista de candidatos, retirando os vértices que entraram na solução e seus adjacentes. E por fim, a cada iteração verificamos se o conjunto solução é dominante, quando isso ocorrer, o nosso código está finalizado. 
void Grafo::gulosoRandomizadoReativo(float alfa, ofstream& output_file){ 

    unsigned seed = static_cast <unsigned> (time(0)); //Será utilizado para geração de números aleatório dentro da construção dos Algoritmos Gulosos 
    srand(seed); 

    if(this->direcionado){ //Para o problema do Subconjunto Dominante Ponderado, por definição, o grafo deve ser não direcionado

        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

    time_t start, end; //Utilizado para contagem de tempo da função 
    time(&start);

    int iteracoes = 500; //Quantidade de iteracoes do código _ Definido inicialmente 

    float melhor_peso = 0; //Variável que armazena a melhor solução das iterações
    float peso = 0;  //Variável que armazena o peso a cada iteração 
    int i = 1; //Variável utilizada para controle das iterações 
    float k;  //Variável utilizada para manipulação do valor aleatório


    vector<int> solucao; //Vetor para armazenar o conjunto solucao durante as iterações
    vector<int> melhor_solucao; //Vetor para armazenar o conjunto final de melhor solução
    vector<No*> listaCandidatos; //Vetor de candidatos para a solução
    

    while(i<iteracoes){ //Processamento do while para controle das iterações 

        i++; //Controle das iterações 

        peso = 0; //A cada iteração o valor do peso deve ser zerado 

        //Preenchimento da lista de candidatos _ Todos os vértices entram na lista 
        listaCandidatos.clear(); 
        No* aux = this->getPrimeiroNo();  
        for(aux; aux != nullptr; aux = aux->getProxNo()){ 

            listaCandidatos.push_back(aux); //A lista de candidatos recebe todos os vértices 
            melhor_peso =  melhor_peso + aux->getPesoNo(); //Dessa forma eu inicializo o meu menor peso com a soma total dos pesos de todos os vértices (maior peso possível)

        }

        int size = listaCandidatos.size();
        
        int kInt; //Variável que guarda o valor aleatorio k (float) em int
        int sol;
        quickSort(listaCandidatos,0,size-1); //A lista de candidatos é ordenada de acordo com a heurística determinada do problema 

        solucao.clear(); //Limpa toda a lista de solucao para uma nova iteracao 
        float xy = (alfa*size) - 1; //Valor máximo para o número aleatório gerado 


        while(!ehDominante(solucao)){
            
            float k = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/xy)); 
            kInt = static_cast<int>(k); //Converte valor aleatório de float para int
            sol = listaCandidatos[kInt]->getId();
            solucao.push_back(sol);
            peso = peso + listaCandidatos[kInt]->getPesoNo();

            auto it = listaCandidatos.begin();

            No *noaRemover = this->getNo(listaCandidatos[kInt]->getId());

            for(Aresta* aresta = noaRemover->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){ //Iteração para remover da lista atual de candidatos todos os vértices que são adjacentes ao vértice escolhido para entrar na solução
            
                int noRemover = aresta->getAlvoId();
            
                for(it; it != listaCandidatos.end(); it++){
    
                    if((*it)->getId() == noRemover){

                        listaCandidatos.erase(it);
                        break;

                    }

                }

            }

            it = listaCandidatos.begin();
            
            for(it; it != listaCandidatos.end(); it++){//Removo da lista de candidatos o vértice da posição kInt (referente ao alfa)
    
                if((*it)->getId() == noaRemover->getId()){

                    listaCandidatos.erase(it);
                    break;

                }

            }
            
        }
        
        if(peso < melhor_peso){

            melhor_peso =  peso;
            melhor_solucao = solucao;    

        }

    }

    time(&end); //Utilizado para contagem de tempo da função
    double time_taken = double(end - start);

    //Saidas em tela do Algoritmo 
    cout << "---------------------------------------------------------------------------------------------------------------------" <<endl;

    cout << "\nQualidade da solucao: " << melhor_peso << endl;

    cout << "\nTempo de processamento: " << time_taken << "s" << endl;

    cout << "\nSemente de randomizacao: " << seed<< endl;

    cout << "\nO conjunto solucao encontrado sempre eh viavel pois pela heuristica sempre entregamos um conjunto dominante" << endl;

    cout << "---------------------------------------------------------------------------------------------------------------------" << endl;

    //Saida do arquivo
    output_file.clear();
        
    output_file << "Qualidade final encontrada " << melhor_peso;

    output_file << "\n";

    output_file << "Conjunto dos Vertices Solucao: [";

    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        output_file << ' ' << *it;

    output_file << " ]" << endl;

}



