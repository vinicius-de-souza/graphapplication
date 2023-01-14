        //Problema do Subconjunto Dominante Ponderado: Algoritmo Construtivo Guloso 
       case 1:{

            grafo1->gulosoConstrutivo(output_file);

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