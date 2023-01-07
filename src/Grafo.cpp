/*REFERÊNCIAS DO TRABALHO 

[1] _ Iterador da função <list> -> https://linuxhint.com/list-iterator-cpp/

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
#include <iomanip>

using namespace std;

// Construtor _ Inicializa o grafo recebendo como parâmetro as funções booleanas que indicam se o grafo é direciondo, se há peso na aresta e se há peso no nó
Grafo::Grafo(bool direcionado, bool peso_aresta, bool peso_no) {

    this->direcionado = direcionado;
    this->peso_aresta = peso_aresta;
    this->peso_no = peso_no;
    this->primeiro_no = this->ultimo_no = nullptr;
    this->numero_arestas = 0;

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

//Função para geração do arquivo de saída do novo grafo _ Recebe como parâmetro o arquivo de saída
void Grafo::geraArquivoSaida(ofstream &output_file){

    ofstream output_file; //Rotina para abertura e escrita do arquivo 

    if(output_file.is_open())

        cout << "Chega aqui direitinho";
        //auxGeraArquivoSaida(output_file);
    
    /*else//Mensagem de erro caso não seja possível gerar arquivo de lista de adjacência 

        cout << endl << "Nao foi possivel abrir arquivo <" << output ;*/

}

//Função para geração do arquivo de saída do novo grafo _  Recebe como parâmetro o arquivo de saída 
void Grafo::auxGeraArquivoSaida(ofstream &output_file){  

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
Grafo* Grafo::intersecao(Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no){ 

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

    cout << "\nFinalizacao da Funcao Intersecao\n";
    cout << "Arquivo .dot: \"intersecao.dot\" \n";
    

    //Verificação da continuação do programa
    int sel;
    cout << "Deseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
    cin >> sel;

    if(sel==2){//Caso o usuário opte por finalizar o programa

        cout << "Programa Finalizado";
        exit(0);

    }

    return grafo_inter;

}

//Função da diferença de dois grafos _ Recebe como parâmetro o segundo grafo para realização da função, se o grafo é direcionado ou não, se o grafo tem peso na aresta ou não e se o grafo tem peso no nó ou não
void  Grafo::diferenca(Grafo* grafo2, bool direcionado, bool peso_aresta, bool peso_no){ 

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

    //Verificação da continuação do programa
    int sel;
    cout << "Deseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
    cin >> sel;

    if(sel==2){//Caso o usuário opte por finalizar o programa

        cout << "Programa Finalizado";
        exit(0);

    }

}
    
//Função de união de dois grafos _ Recebe como parâmetro o segundo grafo para realização da função, se o grafo é direcionado ou não, se o grafo tem peso na aresta ou não e se o grafo tem peso no nó ou não    
void Grafo::uniao(Grafo *grafo2, bool direcionado, bool peso_aresta, bool peso_no){ 

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

    //Verificação da continuação do programa
    int sel;
    cout << "Deseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
    cin >> sel;

    if(sel==2){ //Caso o usuário opte por finalizar o programa

        cout << "Programa Finalizado";
        exit(0);

    }

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


//Implementações Parte II


// Função de implementação do algoritmo Guloso Construtivo _ A heurística utilizada foi adicionar ao conjunto solução o vértice de maior grau entre aqueles disponíveis 
void Grafo::gulosoConstrutivo(){ 

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado
        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

    list<int> solucao; //Criação da lista dos vértices de solução (inicalmente vazia) 
    list<int> vertices; //Criação da lista de todos os vértices do grafo em questão 

    int peso_total = 0; 

    No* aux = this->getPrimeiroNo();  

    int maior_grau = aux->getGrau(); 

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
        // -> push_front: função que adiciona no inicio da lista o valor passado como parametro _ aqui decidimos adicionar na solucao os pesos dos vertices como forma de identificação dos mesmos

        peso_total = peso_total + noMaiorGrau->getPeso(); //Somando os pesos 

        for(Aresta *aresta = noMaiorGrau->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta()){ //Lopping das arestas

            vertices.remove(aresta->getAlvoId()); //Pela descrição do problema, a cada vértice selecionado, os seus vizinhos não precisam estar na solução
            // -> vertices.remove(): função da classe que recebe como parâmetro um valor e percorre toda a lista para procurá-lo e excluí-lo quantas vezes o mesmo aparecer

        }

        vertices.remove(noMaiorGrau->getId());//Removo da lista de vertices, o vertice de maior grau tmb

        auto it = vertices.begin(); // Funcao para pegar o valor do primeiro item da lista de vertice (referência [1])

        maior_grau = *it; // A variável de maior grau recebe o valor do grau do primeiro vertice que esta na lista de vertices

        for (it; it !=vertices.end(); ++it){ // Iteração para descobrir o novo vertice de maior grau 

            No* iteracao = this->getNo(*it);

            if(iteracao->getGrau() >= maior_grau){

                maior_grau = iteracao->getGrau(); // Guardo o valor do grau
                noMaiorGrau = iteracao;

            }

        }

    }  

    // Saidas para teste de funcionalidades
    cout << "\nConjunto dos Vertices Originais: [";

    for (auto it = vertices.begin(); it !=vertices.end(); ++it)
        cout << ' ' << *it;

    cout << " ]\n";

    cout << "Conjunto dos Vertices Solucao: [";

    for(auto it = solucao.begin(); it !=solucao.end(); ++it)
        cout << ' ' << *it;

    cout << " ]";

    cout << "\nPeso total calculado: " << peso_total;

}

// Função de implementação do algoritmo Guloso Randomizado Adaptativo
void Grafo::gulosoRandomizadoAdaptativo(){

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado

        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }

}

// Função de implementação do algoritmo Guloso Construtivo _ A heurística utilizada foi adicionar ao conjunto solução o vértice de maior grau entre aqueles disponíveis 
void Grafo::gulosoRandomizadoReativo(){

    if(this->direcionado){ //Para o problema do Subconjuento Dominante Ponderado, por definição, o grafo deve ser não direcionado

        cout << "Para a analise do problema do Subconjunto Dominante Ponderado o grafo deve ser nao direcionado.\n";
        return;

    }
    
}