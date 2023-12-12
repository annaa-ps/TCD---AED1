#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include "tad.h"


int main()
{
    Armazenamento *armazenamento = inicializarArmazenamento();  // Estrutura de armazenamento
    Lista   *lista               = criar();                     // Lista input do usuario
    Lista   *listaAux            = criar();                     // Lista auxiliar para manipulacao da informacao
    int     fim                  = 0      ;                     // Variavel que recebe a decisao de fim ou nao da insercao de termos
    int     zerada               = 0      ;                     // Saber a situacao da lista ser zerda
    char    opcao                         ;                     // Opcao de menu do usuario
    int     verificacao                   ;                     // Recebe retorno da variavel de calculo do polinomio para garantir que esteja tudo certo
    int     count                = 0      ;                     // Countador de quantas vezes o usuario decidiu adicionar nos
    int     indice               = 0      ;                     // Indice de escolha do hist�rico de polinomios
    int     primeiraVez          = 1      ;                     // Variavel que funciona como booleano para saber se � a primeira vez executando o programa
    int     umaOuVarias                   ;                     // Saber a escolha do usuario sobre o calculo de polinomios

    // Todas j� inicializam com 1, para garantir uma boa atribuicao caso o usuario escolha n�o passar algo:
    int     valorParaX          = 1      ,  // Variavel para o valor de x
            valorParaConstante  = 1      ,  // Variavel para o algarismo ao lado esquerdo de x
            valorDoExpoente     = 1      ;  // variavel para o expoente que eleve o x

    // Funcionamento do programa:
    do {
        menu();
        printf("\n-> Escolha uma opcao: ");
        fflush(stdin);  scanf("%c", &opcao);

        switch (opcao) {
            case '1':
                //! opcao 1: cadastra polinomio
                if (listaVazia(lista) == -1){
                    printf("\n< Quer cadastrar mais um polinomio? Escolha (5) no menu, e reinicialize! >\n< Nao esqueca de escolher (6) caso queira salvar antes de reinicializar! >\n");
                } else {
                    if (primeiraVez){
                        printf("\n[ O polinomio P(x) = ");
                        lista = zerarLista(lista);
                        mostrarLista(lista);
                        esvaziarLista(lista);
                        printf(" esta inicializado ]\n");

                        primeiraVez = 0;
                    }
                    while (fim != 1)
                    {
                        valorParaX = 1, valorParaConstante = 1, valorDoExpoente = 1;
                        addConstante(&valorParaConstante, &zerada);
                        addExpoente(&valorDoExpoente, &zerada);
                        maisTermosOuNao (lista, &zerada,valorParaConstante,valorDoExpoente,&fim);
                        count++;
                    }
                    if ((zerada == 3) && (count == 1)){
                        lista = zerarLista(lista);
                        esvaziarLista(lista);
                    }
                    zerada = 0;
                    fim = 0;
                }
            break;

            case '2':
                //! opcao 2: adiciona termo na expressao e verifica
                if (listaVazia(lista) == 0)
                {
                    printf("\n< Para adicionar um termo no polinomio, cadastre um primeiro! >\n");
                }else{
                    valorParaX = 1, valorParaConstante = 1, valorDoExpoente = 1;
                    addConstante(&valorParaConstante, &zerada);
                    addExpoente(&valorDoExpoente, &zerada);
                    inserirTermo(lista, valorParaConstante, valorDoExpoente);
                }
            break;

            case '3':
                //! opcao 3: Exibir o polinomio:
                if (listaVazia(lista) == 0)
                {
                    printf("\n< Cadastre um polinomio primeiro! >\n");
                }else{
                    printf("\n- O polinomio P(x) = ");
                    mostrarLista(lista);
                    printf("\n");
                }
            break;

            case '4':
                //! opcao 4: Eliminar um termo do polinomio
                if (listaVazia(lista) == 0)
                {
                    printf("\n< Cadastre um polinomio primeiro! >\n");
                }else{
                    valorParaX = 1, valorParaConstante = 1, valorDoExpoente = 1;
                    printf("\n| Considernado o polinomio P(x) = ");     mostrarLista(lista);    printf(" |\n");
                    printf("\n- Informe o expoente do termo que deseja remover: ");
                    scanf("%d", &valorDoExpoente);
                    eliminarTermo(lista, valorDoExpoente);
                }
            break;

            case '5':
                //! opcao 5: Reinicializar um polinomio
                if (listaVazia(lista) == 0)
                {
                    printf("\n< Nao eh necessario! Cadastre algo para depois querer reinicializar! >\n");
                } else{
                    lista = zerarLista(lista);
                    printf("\n- O polinomio foi reinicializado\tVoltou ao: P(0) = ");
                    mostrarLista(lista);
                    esvaziarLista(lista);
                    printf("\n");
                }
            break;

            case '6':
                //! Opcao 6: Guardar o polinomio.
                if (listaVazia(lista) == 0){
                    printf("\n< Cadastre um polinomio primeiro! >\n");
                } else{
                    printf("\n< OK! P(X) = ");
                    mostrarLista(lista);
                    printf(" esta guardado! >\n\n");
                    adicionarLista(armazenamento, lista);
                }
            break;

            case '7':
                //! Opcao 7 : Somar dois polinomios.
                if (listaVazia(lista) == 0){
                    printf("\n< Cadastre um polinomio primeiro! >\n");
                } else{
                    mostrarListasArmazenadas(armazenamento);

                    printf("\n-> Escolha o indice da primeira: ");
                    scanf("%d", &indice);
                    Lista *listaCancatUm = recuperarLista(armazenamento, indice);

                    printf("\n-> Escolha o indice da segunda: ");
                    scanf("%d", &indice);
                    Lista *listaCancatDois = recuperarLista(armazenamento, indice);

                    Lista* resultadoSoma = somarPolinomios(listaCancatUm, listaCancatDois);
                    printf("\nResultado da soma:\n");
                    mostrarLista(resultadoSoma);
                    printf("\n");
                }
            break;

            case '8':
                //! Opcao 8: Calcular o valor de P(x).
                if (listaVazia(lista) == 0){
                    printf("\n< Cadastre um polinomio primeiro! >\n");
                }else{
                    do
                    {
                        printf("\n\t-> Informe o valor para x: ");
                        scanf("%d", &valorParaX);

                        if (valorParaX <= 0) printf("\n-> Digite algo igual ou superior a 1 >\n");
                    } while (valorParaX <= 0);

                    do
                    {
                        printf("\n|(1) Quer calcular para apenas um polinomio;\n|(2) Para varios polinomios.\n\n-> Digite sua escolha:  ");
                        scanf("%d", &umaOuVarias);

                        if ((umaOuVarias != 1) && (umaOuVarias != 2)) printf("\n->Digite 1 ou 2! >\n");
                    } while ((umaOuVarias != 1) && (umaOuVarias != 2));

                    if (umaOuVarias == 1){
                        mostrarListasArmazenadas(armazenamento);

                        printf("\n\n-> Escolha o indice da que quer calcular: ");
                        scanf("%d", &indice);
                        listaAux = recuperarLista(armazenamento, indice);
                        unsigned long int resultadoX = calcularPolinomio(listaAux, valorParaX);
                        verificacao = calcularPolinomio(listaAux,valorParaX);

                        if(verificacao == -1){
                        printf("\n< Ocorreu um erro! Tente novamente! >\n");
                        } else{
                            mostrarMensagemPdeX(listaAux, valorParaX, resultadoX);
                        }
                    }else if(umaOuVarias == 2){
                        calcularPparaVariasListas(armazenamento, valorParaX);
                    }
                }
            break;

            case '9':
                //! Opcao 9: Apenas a sa�da do programa.
                tchau();
            break;

            default:
                printf("\n < Opcao invalida. Tente novamente. >\n");
        }
    } while (opcao != '9');

    // Liberar memoria
    esvaziarLista(lista);
    free(lista);

    return 0;
}
