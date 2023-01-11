/*REFERENCIAS
    [1] _ Função que converte string em float -> https://www.techiedelight.com/pt/convert-a-string-to-a-float-in-cpp/
*/

#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <chrono>
#include "include/Grafo.h"
#include "include/Aresta.h"
#include "include/No.h"
#include "src/Grafo.cpp"
#include "src/Aresta.cpp"
#include "src/No.cpp"

using namespace std;

//Função de leitura dos grafos da Primeira Parte _ Recebe como parâmetro o arquivo de texto do grafo, se o grafo é direcionado ou não, se tem peso nas arestas ou não e se tem peso no nó ou não _ Retorna o objeto grafo que foi criado a partir da leitura
Grafo * leituraParteI(ifstream& input_file, bool direcionado, bool peso_aresta, int peso_no){

    //Variáveis para auxiliar na criação do Grafo
    int idNoFonte;
    int idNoAlvo;
    int ordem;

    //Inserção da ordem do grafo
    input_file >> ordem;

    //Criando objeto grafo
    Grafo* grafo = new Grafo(direcionado, peso_aresta, peso_no);

    //Leitura do arquivo

    if(!grafo->getPesoAresta() && !grafo->getPesoNo()){ //Caso o grafo não tenha peso no nó e nem nas arestas 

        while(input_file >> idNoFonte >> idNoAlvo) { //Lê o arquivo enquanto houver dados a serem lidos 

            grafo->setNumAresta();
            grafo->inserirAresta(idNoFonte, idNoAlvo, 0);

        }

    }
 
    else if(grafo->getPesoNo() && !grafo->getPesoAresta()){ //Caso o grafo tenha peso no nó e não tenha peso nas arestas 

        float pesoIdNofonte, pesoIdNoAlvo;

            while(input_file >> idNoFonte >> pesoIdNofonte >> idNoAlvo >> pesoIdNoAlvo) { //Lê o arquivo enquanto houver dados a serem lidos 

                grafo->setNumAresta();
                grafo->inserirAresta(idNoFonte, idNoAlvo, 0);

                No *aux = grafo->getNo(idNoFonte);
                aux->setPeso(pesoIdNofonte);

                No *aux2 = grafo->getNo(idNoAlvo);
                aux2->setPeso(pesoIdNoAlvo);

            }

    }

    else if(grafo->getPesoAresta() && !grafo->getPesoNo() ){ //Caso o grafo não tenha peso no nó e tenha peso nas arestas 

        float edgeWeight;
        
             while(input_file >> idNoFonte >> idNoAlvo >> edgeWeight) { //Lê o arquivo enquanto houver dados a serem lidos 

                grafo->setNumAresta();
                grafo->inserirAresta(idNoFonte, idNoAlvo, edgeWeight);

            }

    }

    else if(grafo->getPesoNo() && grafo->getPesoAresta()){ //Caso o grafo tenha peso no nó e nas arestas 

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

//Função de leitura dos grafos da Segunda Parte _ Recebe como parâmetro o arquivo de texto do grafo, se o grafo é direcionado ou não, se tem peso nas arestas ou não e se tem peso no nó ou não _ Retorna o objeto grafo que foi criado a partir da leitura
Grafo *leituraParteII(ifstream& input_file, bool direcionado, bool peso_aresta, int peso_no){

    //Variáveis para auxiliar na criação do grafo
    string linha;
    string ord;
    string no;

    //Criação do novo objeto grafo 
    Grafo* grafo = new Grafo(direcionado, peso_aresta, peso_no);

    getline(input_file,linha); //Leitura da primeira linha 
    getline(input_file,ord); //Leitura da segunda linha _ ordem do grafo

    int ordem = stoi(ord); // A ordem do grfo fica guardada numa variável int _ função stoi transforma uma string em um inteiro

    const char *c; //Será utilizada na leitura da matriz de adjacência 

    int j  = 3; //Iterador para andar no arquivo _ Duas linhas já foram lidas, começamos pela terceira 

    while(j < ordem+5){ //Anda no arquinvo até a linha que inicia os valores dos nós _ Esse valor foi encontrado através do estudo dos arquivos disponíveis 

        getline(input_file,linha); //Essas linhas são referentes as posições (x,y) _ Não utilizaremos essa informação no trabalho, portanto, apenas passamos por essas linhas 
        j = j + 1;

    }

    int i  = 1; //Iterador utilizado para criação dos ids internos 

    while(j <= (2*ordem)+4){ // Encontra os nós do arquivo e adiciona os nós no grafo _ Cada linha é um novo vértice com seu peso _ Esse valor foi encontrado através do estudo dos arquivos disponíveis 

        getline(input_file,no);

            float peso = std::strtof(no.c_str(),nullptr); //Função que transforma string em float _ Referência [1]

            grafo->inserirNo(i); //Inserimos o nó no grafo com um id 

            grafo->getNo(i)->setPeso(peso); //Inserimos o peso do nó

        //Incrementamos os iteradores 
        i = i + 1;
        j = j + 1;

    }
   
    getline(input_file,linha); //Pega a linha antes da matriz de adjacência 
    
    j = j + 1; //O iterador j recebe mais um pela linha lida acima 

    int cont = 0; //Será utilizado para a manipulação dos ids internos


    while(j <= (3*ordem)+5){ //Percorre até o final do arquivo _ Esse valor foi encontrado através do estudo dos arquivos disponíveis 

        getline(input_file,linha);

        c = linha.c_str(); //A linha lida como string é transformada em um vetor de char

        for(int k=0 ;  c[k] != '\0' ; k++){ //Percorre todo o vetor criado a partir da string , por definição o final de uma string é \0, por isso a iteração ocorre até encontrarmos esse caractere 

            if(c[k]=='1' && k!=cont){ //Pela definição, caso haja aresta entre um nó e outro na matriz de adjacência, o número 1 aparece _   k!=cont -> controle para que não sejam criadad aresta do nó para ele mesmo

                grafo->inserirAresta((j-((2*ordem)+5)),(k/2)+1,0);

            }

        }

        j = j + 1 ;

        cont = cont + 2 ; // Variável para evitar que sejam criadas arestas do nó para ele mesmo

    }
    
    return grafo;

}

// Função para apresentação do menu em tela da Primeira Parte _ Retorna o valor inserido pelo usuário 
int menuParteI(){

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

// Função para apresentação do menu em tela da Segunda Parte _ Retorna o valor inserido pelo usuário 
int menuParteII(){
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

//Função que atráves da utilização do switch, acessa a função escolhida atráves do menu na classe do grafo, essa implementação funciona para a Primeira Parte _ Recebe como parâmetro o valor inserido no menu, o grafo, o arquivo de saída, se é direcionado ou não, se tem peso na aresta ou não e se tem peso no nó ou não
void selecionarParteI(int selecao, Grafo* grafo1, ofstream& output_file, bool direcionado, bool peso_aresta, bool peso_no){

    switch (selecao) {

        //Interseção 
        case 1:{

            //Orientações para a inserção do novo grafo 
            cout << "--------------------------------------------------------";
            cout << "\nA opcao escolhida foi a INTERSECAO!\nPara a utilizacao dessa funcao um novo grafo deve ser inserido." << "\nLembrando que o novo grafo deve ter as mesmas configuracoes do grafo principal, ou seja, deve ser:";

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


            //Inserindo o novo grafo 
            string input_file_name;
            cout << "\nInsira o nome do arquivo do novo grafo:";
            cin >> input_file_name;

            //Rotina de abertura do arquivo do novo grafo
            ifstream input_file;
            input_file.open(input_file_name, ios::in);

            //Criação de um novo objeto grafo 
            Grafo *grafo2;

            //Será utilizado para a geração do novo arquivo de saída 
            Grafo *final;

            if(input_file.is_open()){

                grafo2 = leituraParteI(input_file, direcionado, peso_aresta, peso_no); //Chama a leitura referente a Primeira Parte

                final = grafo1->intersecao(grafo2, direcionado, peso_aresta, peso_no); //Chama a função de interseção  

            
                //Verificação da continuação do programa
                int sel;
                cout << "\nDeseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
                cin >> sel;

                if(sel==2){//Caso o usuário opte por finalizar o programa

                    cout << "Programa Finalizado";
                    exit(0);

                }

            }

            else

                cout << "Unable to open " << input_file_name;


            break;

        }

        //Diferença
        case 2:{

            //Orientações para a inserção do novo grafo 
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

            //Inserindo o novo grafo 
            string input_file_name;
            cout << "\nInsira o nome do arquivo do novo grafo:";
            cin >> input_file_name;

            //Rotina de abertura do arquivo do novo grafo
            ifstream input_file;
            input_file.open(input_file_name, ios::in);

            //Criação de um novo objeto grafo 
            Grafo *grafo2;

            //Será utilizado para a geração do novo arquivo de saída 
            Grafo *final;

            if(input_file.is_open()){

                grafo2 = leituraParteI(input_file, direcionado, peso_aresta, peso_no); //Chama a leitura referente a Primeira Parte
                
                final = grafo1->diferenca(grafo2, direcionado, peso_aresta, peso_no); //Chama a função de diferença

                //Verificação da continuação do programa
                int sel;
                cout << "\nDeseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
                cin >> sel;

                if(sel==2){//Caso o usuário opte por finalizar o programa

                    cout << "Programa Finalizado";
                    exit(0);

                }

            }

            else

                 cout << "Unable to open " << input_file_name;

            break;

        }

        //União
        case 3:{

            //Orientações para a inserção do novo grafo 
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

            //Inserindo o novo grafo 
            string input_file_name;
            cout << "\nInsira o nome do arquivo do novo grafo:";
            cin >> input_file_name;

            //Rotina de abertura do arquivo do novo grafo
            ifstream input_file;
            input_file.open(input_file_name, ios::in);

             //Criação de um novo objeto grafo 
            Grafo *grafo2;

            //Será utilizado para a geração do novo arquivo de saída 
            Grafo* final;

            if(input_file.is_open()){

                grafo2 = leituraParteI(input_file, direcionado, peso_aresta, peso_no); //Chama a leitura referente a Primeira Parte
                
                final = grafo1->uniao(grafo2, direcionado, peso_aresta, peso_no); //Chama a função de união


                //Verificação da continuação do programa
                int sel;
                cout << "\nDeseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
                cin >> sel;

                if(sel==2){//Caso o usuário opte por finalizar o programa

                    cout << "Programa Finalizado";
                    exit(0);

                }

            }

            else

                cout << "Unable to open " << input_file_name;

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

//Função que atráves da utilização do switch, acessa a função escolhida atráves do menu na classe do grafo, essa implementação funciona para a Segunda Parte _ Recebe como parâmetro o valor inserido no menu, o grafo, o arquivo de saída, se é direcionado ou não, se tem peso na aresta ou não e se tem peso no nó ou não
void selecionarParteII(int selecao, Grafo* grafo1, ofstream& output_file, string input_file_name, bool direcionado, bool peso_aresta, bool peso_no){

    switch(selecao){

        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso 
       case 1:{

            grafo1->gulosoConstrutivo(output_file, input_file_name);

            //Verificação da continuação do programa
                int sel;
                cout << "\nDeseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
                cin >> sel;

                if(sel==2){//Caso o usuário opte por finalizar o programa

                    cout << "Programa Finalizado";
                    exit(0);

                }

            break;

        }

        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso Randomizado e Adaptativo
        case 2:{

            grafo1->gulosoRandomizadoAdaptativo();

            //Verificação da continuação do programa
                int sel;
                cout << "\nDeseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
                cin >> sel;

                if(sel==2){//Caso o usuário opte por finalizar o programa

                    cout << "Programa Finalizado";
                    exit(0);

                }

            break;
            
        }

        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso Randomizado Reativo
        case 3:{

            grafo1->gulosoRandomizadoReativo();

            //Verificação da continuação do programa
                int sel;
                cout << "\nDeseja realizar mais operacoes?\n[1] Sim \n[2] Nao\n";
                cin >> sel;

                if(sel==2){//Caso o usuário opte por finalizar o programa

                    cout << "Programa Finalizado";
                    exit(0);

                }

            break;

        }

    }

}

//Menu principal para a implementação da Primeira Parte _ Recebe como parâmetro o arquivo de saída, o grafo gerado a partir da leitura, se é direcionado ou não, se tem peso na aresta ou não e se tem peso no nó ou não 
int mainMenuParteI(ofstream& output_file, Grafo* grafo, bool direcionado, bool peso_aresta, bool peso_no){

    int selecao = 1;

    while(selecao != 0){ //O menu retorna após a utilização de uma função 

        if(selecao >=1 && selecao<=4){ //Verifica se o valor informado é uma opção do menu 

            selecao = menuParteI(); //Chama a função do Menu 

            if(output_file.is_open()) 

               selecionarParteI(selecao, grafo,output_file, direcionado, peso_aresta, peso_no); //Função que leva para as funções dentro da classe grafo

            else 

                cout << "Unable to open the output_file" << endl;

            output_file << endl;

        }

        else{ // Caso o valor informado não seja uma opção do menu

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

//Menu principal para a implementação da Segunda Parte _ Recebe como parâmetro o arquivo de saída, o grafo gerado a partir da leitura, se é direcionado ou não, se tem peso na aresta ou não e se tem peso no nó ou não 
int mainMenuParteII(string input_file_name, ofstream& output_file, Grafo* grafo, bool direcionado, bool peso_aresta, bool peso_no){

    int selecao = 1;

    while(selecao != 0){  //O menu retorna após a utilização de uma função 

        if(selecao >=1 && selecao<=3){ //Verifica se o valor informado é uma opção do menu 

            selecao = menuParteII(); //Chama a função do menu

            if(output_file.is_open())

               selecionarParteII(selecao, grafo, output_file, input_file_name, direcionado, peso_aresta, peso_no); //Função que leva para as funções dentro da classe grafo

            else

                cout << "Unable to open the output_file" << endl;

            output_file << endl;

        }

        else{ // Caso o valor informado não seja uma opção do menu

            cout <<"\nOpcao selecionada nao existente \nTente novamente\n";

            selecao = menuParteII();

            if(output_file.is_open())

               selecionarParteII(selecao, grafo, output_file, input_file_name, direcionado, peso_aresta, peso_no);

            else

                cout << "Unable to open the output_file" << endl;

            output_file << endl;

        }

    }

    return 0;

}

//Main do programa 
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
        arq_grafo.open("input_parteII/Problem_150_150_3.dat", ios::in); //  abertura do arquivo de teste 
        ofstream output_file;
        output_file.open("arquivo_saida.txt", ios::out | ios::trunc);
    
        string input_file_name = "input_parteII/Problem_150_150_3.dat" ;

        if(arq_grafo.is_open()) { 
            Grafo *grafo;//Caso o arquivo abra normalmente 

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
                    mainMenuParteII(input_file_name, output_file,grafo, direcionado, peso_aresta, peso_vertice);
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


    //Definindo as variáveis nome do programa e nome do arquivo de saída 
    string program_name(argv[0]);
    string input_file_name(argv[1]);


    //Abrindo arquivo de entrada _ rotina de abertura de arquivo 
    ifstream input_file;
    ofstream output_file;

    input_file.open(argv[1], ios::in);
    output_file.open(argv[2], ios::out | ios::trunc);

    //Criação de um objeto grafo 
    Grafo* grafo;

    if(input_file.is_open()){
        
        int sel;

        //Esse MENU foi implementado pois a leitura do arquivo é feita de formas diferentes para a Primeira Parte e a Segunda Parte do Trabalho
        cout << "\nMENU" << endl;
        cout << "--------------------------------------------------------" << endl;
        cout << "Para acessar funcionalidades da Primeira Parte do Trabalho Pratico digite [1]" << endl;
        cout << "Para acessar funcionalidades da Segunda Parte do Trabalho Pratico digite [2]" << endl;

        cin >> sel;

        if(sel==1 || sel==2){ //Verificação se o usuário informou uma funcionalidade válida

            if(sel==1){ //Implementação para a Primeira Parte do Trabalho

                grafo = leituraParteI(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5])); //atoi _ função que converte string em números inteiros
                mainMenuParteI(output_file,grafo, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

            }

            if(sel==2){ //Implementação para a Segunda Parte do Trabalho 

                grafo = leituraParteII(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5])); //atoi _ função que converte string em números inteiros
                mainMenuParteII(input_file_name, output_file,grafo, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

            }          

        }
        else

           cout << "O valor informado nao e reconhecido!";
        
    }

    else //Caso não seja possível abrir o arquivo de entrada 

        cout << "Unable to open " << argv[1];


    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    output_file.close();

    return 0;
}