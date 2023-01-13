/*REFERÊNCIAS DO TRABALHO 

[1] _ Iterador da função <list> -> https://linuxhint.com/list-iterator-cpp/

[2] _ Como contar o tempo de processamento de uma função -> https://acervolima.com/meca-o-tempo-de-execucao-com-alta-precisao-em-c-c/

[3] _ Como usar a srand e rand -> https://www.cmmprogressivo.net/2019/12/Como-Gerar-Numeros-Aleatorios-Randomicos-rand-srand.html

[4] _ QuickSort Implementation -> https://www.geeksforgeeks.org/quick-sort/


*/

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
//#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime> 
#include "time.h" // Referência [2]

using namespace std;

/*void swapA(vector<No*> &arr, int a, int b)
{
    No* t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}
*/

int partition(vector<No*> &arr, int low, int high){
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
    
void quickSort(vector<No*> &arr, int low, int high) 
    {
        
        if (low < high) {
            /* pi is partitioning index, arr[p] is now
            at right place */
            int pi = partition(arr, low, high); 
    
            // Separately sort elements before
            // partition and after partition
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }


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

    grafo_inter->geraSaidaParteI(output_file); //Chamada da função para a geração do arquivo de saída .txt ou .dat (de acordo com o que foi informado na linha de comando)

    grafo_inter->geraGrafoDot("testes/intersecao.dot"); //Chamada da função de geração do arquivo .dot 

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

    cout << "\nFinalizacao da Funcao Uniao\n";
    cout << "Arquivo de saida: \"uniao.dot\" \n\n";


}

// Função de criação da Rede Pert de um grafo direcionado _ Não necessita receber nada como parâmetro   
void Grafo::redePert(){ 

    if(!this->direcionado){ //Para que seja possível realizar a análise de Rede Pert, o grafo deve ser direcionado

        cout << "Para a realizacao da Rede Pert o grafo inserido deve ser direcionado!";
        return;

    }

    //Etapa de verificação do início e fim da Rede Pert _ É possível que o primeiro nó inserido não seja referente a primeira etapa da Rede Pert
    int id_inicio;
    int id_fim;

    cout << "Para iniciar a Funcao de Rede Pert, indique o id no de inicio (id correspondente a primeira etapa): " ;
    cin >> id_inicio;
    No *inicio = new No(id_inicio);

    cout << "Indique o id do no de fim (id correspondente a ultima etapa): ";
    cin >> id_fim;
    No *fim = new No(id_fim);


}

//Função que tem como objetivo geração do arquivo de saída da Parte I do trabalho
void Grafo::geraSaidaParteI(ofstream &output_file){

    output_file << "Ta saindo";

}


//Implementações Parte II


// Função de implementação do algoritmo Guloso Construtivo _ A heurística utilizada foi adicionar ao conjunto solução o vértice de maior grau entre aqueles disponíveis 
void Grafo::gulosoConstrutivo(ofstream &output_file){ 

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado
        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

    time_t start, end; //Utilizado para contagem de tempo da função 
    time(&start);

    list<int> solucao; //Criação da lista dos vértices de solução (inicalmente vazia) 
    list<int> vertices; //Criação da lista de todos os vértices do grafo em questão 

    int peso_total = 0; 

    No* aux = this->getPrimeiroNo();  

    int maior_grau = aux->getGrau(); //Nova heurística 

    No* noMaiorGrau = this->getPrimeiroNo(); 

    for(aux; aux != nullptr; aux = aux->getProxNo()){ //Percorre todos os nós do grafo

        if(aux->getGrau() > maior_grau){ // Caso o nó em questao tenha um grau maior que o último, esse passa a ser o nó de maior grau

            maior_grau = aux->getGrau();
            noMaiorGrau = aux; 

        }

        vertices.push_front(aux->getId()); // Conforme faço essa análise, já preencho o vetor de vertices com todos os nós do grafo

    }

    //Enquanto minha lista de vertices estiver com vertices, eu faço a analise _ Pela heurística em algum momento essa lista estará vazia
    while(vertices.size() != 0){ 

        solucao.push_front(noMaiorGrau->getId()); // O vértice selecionado no looping entra na solução 
        // -> push_front: função que adiciona no inicio da lista o valor passado como parametro _ aqui decidimos adicionar na solucao os id dos vertices como forma de identificação dos mesmos _ esses ids foram inseridos na leitura dos arquivos 

        peso_total = peso_total + noMaiorGrau->getPesoNo(); //Somando os pesos 

        for(Aresta *aresta = noMaiorGrau->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){ //Lopping das arestas

            vertices.remove(aresta->getAlvoId()); //Pela descrição do problema, a cada vértice selecionado, os seus vizinhos não precisam estar na solução
            // -> vertices.remove(): função da classe que recebe como parâmetro um valor e percorre toda a lista para procurá-lo e excluí-lo quantas vezes o mesmo aparecer

        }

        vertices.remove(noMaiorGrau->getId());//Removo da lista de vertices, o vertice de maior grau tmb

        if(vertices.size() == 0) //Pode ser que durante essa iteração, a lista fique vazia, caso isso ocorra paramos o while
            break;

        auto it = vertices.begin(); // Funcao para pegar o valor do primeiro item da lista de vertice (referência [1])

        maior_grau = this->getNo(*it)->getGrau(); // A variável de maior grau recebe o valor do grau do primeiro vertice que esta na lista de vertices

        noMaiorGrau = this->getNo(*it);


        for (it; it !=vertices.end(); ++it){ // Iteração para descobrir o novo vertice de maior grau 

            No* iteracao = this->getNo(*it);

            if(iteracao->getGrau() > maior_grau){

                maior_grau = iteracao->getGrau(); // Guardo o valor do grau
                noMaiorGrau = iteracao;

            }

        }

    }

    time(&end); //Utilizado para contagem de tempo da função
    double time_taken = double(end - start);

    this->saidaTelaGulosoConstrutivo(peso_total, time_taken); // A função para saída em tela é chamada 
    
    cout << "\nFim do Algoritmo Guloso Construtivo!" << endl ;

    this->geraSaidaGulosoConstrutivo(output_file, solucao, peso_total); // A função para gerar o arquivo de saída é chamada _ Essa função recebe como parâmetro o arquivo de saída, a lista dos vértices de solução e o valor do peso total

    cout << "\nArquivo de saida gerado." << endl;

}

// Função de implementação do algoritmo Guloso Randomizado Adaptativo
void Grafo::gulosoRandomizadoAdaptativo(){

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado

        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

}

// Função de implementação do algoritmo Guloso Construtivo _ A heurística utilizada foi ordenar a lista de candidatos de forma com que esse vetor contenha de forma crescente a função peso/grau para cada nó. Com esse critério escolhemos de forma aleatória um vértice e o adicionamos no conjunto solução, após isso atualizamos a lista de candidatos, retirando apenas os vértices que entraram na solução e para todo adjacente de um vértice na solução o seu grau também é atualizado. E por fim, a cada iteração verificamos se o conjunto solução é dominante, quando isso ocorrer, o nosso código está finalizado. 
void Grafo::gulosoRandomizadoReativo(float alfa, unsigned semente, ofstream& output_file){

    if(this->direcionado){ //Para o problema do Subconjunto Dominante Ponderado, por definição, o grafo deve ser não direcionado

        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

    time_t start, end; //Utilizado para contagem de tempo da função 
    time(&start);

    int iteracoes = 3; //Quantidade de iteracoes do código _ Definido inicialmente 

    float melhor_peso = 0; //Variável que armazena a melhor solução das iterações
    float peso;
    int i = 1; //Variável utilizada para controle das iterações 
    float k;  //Variável utilizada para manipulação do valor aleatório


    vector<int> solucao; //Vetor para armazenar o conjunto solucao durante as iterações
    vector<int> melhor_solucao; //Vetor para armazenar o conjunto final de melhor solução
    vector<No*> listaCandidatos; //Vetor de candidatos para a solução

    //Preenchimento inicial da lista de candidatos _ Todos os vértices entram na lista 
    No* aux = this->getPrimeiroNo();  
    int j = 0;
    for(aux; aux != nullptr; aux = aux->getProxNo()){ 

        listaCandidatos.push_back(aux); //A lista de candidatos recebe todos os vértices 
        melhor_peso =  melhor_peso + aux->getPesoNo(); //Dessa forma eu inicializo o meu menor peso com a soma total dos pesos de todos os vértices
        j++;

    }

    /*int size = listaCandidatos.size();
    quickSort(listaCandidatos,0,size-1); 

    for(int n=0; n<size; n++){

        cout << "No de id " << listaCandidatos[n]->getId() << " com peso " << listaCandidatos[n]->getPesoNo()/listaCandidatos[n]->getGrau() << endl;
 
    }*/

    while(i<iteracoes){ //Processamento do while para controle das iterações 

        i++; 

        int size = listaCandidatos.size();
        int kInt; //Variável que guarda o valor aleatorio k (float) em int
        int sol;
        int v = 0;
        int y = 0;
        quickSort(listaCandidatos,0,size-1); //A lista de candidatos é atualizada de acordo com a heurística determinada do problema 

        solucao.clear(); //Limpa toda a lista de solucao para uma nova iteracao 
        float xy = (alfa*size) - 1;


        while(!ehDominante){
            
            float k = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/xy)); 
            kInt = static_cast<int>(k); //Converte valor aleatório de float para int
            sol = listaCandidatos[kInt]->getId();
            solucao.push_back(sol);
            y++;
            peso = peso + listaCandidatos[kInt]->getPesoNo();
            this->atualizaListaCandidatos(listaCandidatos, kInt, size);
            cout << "Iteracao " << v << endl;
            cout << "O id escolhido para ser removido foi " << listaCandidatos[kInt]->getId();
            cout << "Lista de candidatos ";
            for(int h=0; h<listaCandidatos.size(); h++){

                cout << "No de id " << listaCandidatos[h]->getId() << " com peso/grau " << listaCandidatos[h]->getPesoNo()/listaCandidatos[h]->getGrau() << endl;

            }
            
        }
        
        if(peso < melhor_peso){

            melhor_peso =  peso;
            melhor_solucao = solucao;
            

        }

    }

    time(&end); //Utilizado para contagem de tempo da função
    double time_taken = double(end - start);

    this->saidaTelaGulosoRandomizado(melhor_peso, time_taken, semente); // A função para saída em tela é chamada 
    
    cout << "\nFim do Algoritmo Guloso Randomizado!" << endl ;

    this->geraSaidaGulosoRandomizado(output_file, melhor_solucao, melhor_peso); // A função para gerar o arquivo de saída é chamada 

}

void Grafo::ordenaListaCandidatos(vector<No*> lista, int size){ //Função auxiliar para ordenação da lista de candidatos _ A heurística utilizada foi dar preferência para os vértices com menor valor da relação peso/grau .
    
    quickSort(lista,0,size-1); //Utilizamos a função quickSort já conhecida para ordenação dessa lista _ Referência [4]

}   

void Grafo::atualizaListaCandidatos(vector<No*> lista, int kInt , int size){

    lista.remove(lista[kInt]->getId()); //Removo da lista de candidatos o vértice da posição kInt (referente ao alfa)

    //É necessário decrementar em um grau todos os vértices adjacentes do vértice que foi colocado na solução

    No* aux = this->getNo(lista[kInt]->getId());

    for(Aresta *aresta = aux->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){

        this->getNo(aresta->getAlvoId())->grau = this->getNo(aresta->getAlvoId())->getGrau() - 1; 

    }

    quickSort(lista,0,size-1); 

}

//Essa função recebe como parâmetro o arquivo de saída, o nome do arquivo de entrada (para determinação da qualidade do programa), a lista dos vértices de solução e o valor do peso total e gera o arquivo de saída para o Algoritmo Guloso Construtivo
void Grafo::geraSaidaGulosoConstrutivo(ofstream &output_file, list<int> solucao, int peso_total){

    output_file << "Conjunto dos Vertices Solucao: [";

    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        output_file << ' ' << *it;

    output_file << " ]";

    output_file << "\nQualidade da solucao: " << peso_total;

    cout << "\nArquivo de saida gerado." << endl;

}

//Função que gera as saídas em tela para o algoritmo Guloso Construtivo _ Recebe como parâmetro o peso calculado no algoritmo e o nome do arquivo para comparação da qualidade e o tempo de processamento
void Grafo::saidaTelaGulosoConstrutivo(int peso_total, double tempo){

    cout << "\nO Algoritmo Guloso Construtivo atingiu uma qualidade de: " << peso_total << endl;

    cout << "Tempo gasto para a geracao da solucao do Algoritmo Guloso Construtivo: " << tempo << "s";

}

//Função que gera as saídas em tela para o algoritmo Guloso Randomizado
void Grafo::saidaTelaGulosoRandomizado(int peso_total, double tempo, int semente){

    cout << "\nO Algoritmo Guloso Randomizado atingiu uma qualidade de: " << peso_total << endl;

    cout << "Tempo gasto para a geracao da solucao do Algoritmo Guloso Construtivo: " << tempo << "s" << endl;

    cout<< "A semente de randomizacao para esse Algoritmo foi: " << semente << endl;

    cout << "Uma vez que o programa testa a todo momento se o conjunto solucao eh dominante ou nao, a nossa solucao sempre eh viavel." << endl;

}

//Essa função recebe como parâmetro o arquivo de saída, o nome do arquivo de entrada (para determinação da qualidade do programa), a lista dos vértices de solução e o valor do peso total e gera o arquivo de saída para o Algoritmo Guloso Construtivo
void Grafo::geraSaidaGulosoRandomizado(ofstream &output_file, vector<int> solucao, int peso_total){

    output_file << "Conjunto dos Vertices Solucao: [";

    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        output_file << ' ' << *it;

    output_file << " ]";

    output_file << "\nQualidade da solucao: " << peso_total;

    cout << "\nArquivo de saida gerado." << endl;

}


bool Grafo::ehDominante(vector<int> sol){

    No *aux = this->getPrimeiroNo();

    for(aux; aux != nullptr; aux = aux->getProxNo()){

        int key = aux->getId();

        if(!(std::count(sol.begin(), sol.end(), key)))
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