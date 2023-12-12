#include "tad.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

// ? ========================================================================= Funcoes de manipulacao da lista:

void adicionarTermosNos(Termo *termo, int valorParaX, int valorParaConstante, int valorDoExpoente){
    termo->coeficiente  = valorParaX;
    termo->algarismo    = valorParaConstante;
    termo->expoente     = valorDoExpoente;
}

Lista * criar()
{
    Lista *n = (Lista *) malloc(sizeof(Lista));
    n->inicio = NULL;
    return n;
}

int listaVazia(Lista *lista)
{
    if (lista == NULL)
        return _FALHA_ALOCACAO;

    if (lista->inicio == NULL)
        return _SUCESSO;    // Lista vazia

    return _ERRO;           // Lista n�o est� vazia
}

int mostrarLista(Lista *lista)
{
    if(lista == NULL || lista->inicio == NULL){
        return _FALHA_ALOCACAO;
    }

    No *aux = lista->inicio;

    while (aux != NULL){
        if ((aux->termo.algarismo == 1) && (aux->termo.expoente != 1))
        {
            printf("x^%d", aux->termo.expoente);
        }else if ((aux->termo.algarismo == 1) && (aux->termo.expoente == 1)){
            printf("x");
        } else{
            printf("%dx^%d", aux->termo.algarismo, aux->termo.expoente);
        }

        if (aux->proximo != NULL)
            printf(" + ");
        aux = aux->proximo;
    }

    return _SUCESSO;
}

int adicionarFim(Lista *lista, Termo *termo)
{
    No *novoNo = (No *)malloc(sizeof(No));  // Alocando um novo n�.

    if (novoNo == NULL)  { return _FALHA_ALOCACAO;  }

    // Atribuindo ao n� auxiliar as informacoes:
    novoNo->termo = *termo;
    novoNo->proximo = NULL;

    if (lista->inicio == NULL) {            // Se a lista est� vazia, sinal que adicionarFim na real estar� sendo um adicionarInicio, ent�o tratamos os ponteiros devidamente:
        novoNo->anterior = NULL;
        lista->inicio = novoNo;
    } else {                                // Se o inicio n�o for vazioo, ent�o vamos encontrar o n� atual do final da lista
        No *aux = lista->inicio;            // N� auxiliar, ele inicia no inicio da lista, e ir� percorrer at� achar o n� que aponta para null (o ultimo n�)
        while (aux->proximo != NULL) {
            aux = aux->proximo;
        }

        /* Ao achar esse final, fazemos o seguinte: */
        novoNo->anterior = aux; // Ligamos o ponteiro ANTERIO do n� alocado, ao ultimo n� da lista
        aux->proximo = novoNo;  // Em seguida, ligamos o PR�XIMO do n� da lista encadeada (que antes apontava pra NULL e isso o tornava o ultimo), para o novoN� alocado
    }                           // Com isso teremos: aux->novoN�->NULL se pensmamos na estrutura do PROXIMO, e aux<-novoN� se pensamos na estrutura ANTERIOR

    return _SUCESSO;
}

int removerInicio(Lista *lista)
{
    if (lista == NULL)
        return _FALHA_ALOCACAO;

    if (listaVazia(lista) == _SUCESSO)
        return _ERRO;                   // Pois se � afirmativa a lista vazia, ele retorna erro na remocao do inicio.


    // Manipulacao dos ponteiros:
    No *aux = lista->inicio;
    lista->inicio = aux->proximo;

    // Caso o inicio n�o seja nulo, � sinal que a lista n�o est� vazia, postanto ajustamos o n� anterior do n� tamb�m, para que assim mantenha o rigor de que o "anterior" do inicio seja NULL.
    if(lista->inicio != NULL){
        lista->inicio->anterior = NULL;
    }

    free(aux);

    return _SUCESSO;
}

int esvaziarLista(Lista *lista){
    if (listaVazia(lista) == _SUCESSO) {
        return _ERRO; // Retorna erro se a lista j� estiver vazia, pois n�o � poss�vel esvaziar uma lista vazia.
    }

    // Usa um loop para remover o in�cio da lista at� que a lista esteja completamente vazia
    while (lista->inicio != NULL) {
        removerInicio(lista);
    }

    return _SUCESSO; // Retorna sucesso ap�s esvaziar a lista com �xito
}

Lista* zerarLista(Lista *lista) {
    // Aloca uma nova lista vazia
    Lista *novaLista = (Lista *)malloc(sizeof(Lista));
    novaLista->inicio = NULL; // Inicializa o in�cio da nova lista como nulo

    // Percorre a lista original e libera a mem�ria de cada n� e termo
    No *atual = lista->inicio;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual); // Libera a mem�ria do n�
        atual = proximo;
    }

    Termo termoZero = {0, 1, 0}; // 0x^0
    No *novoNo = (No *)malloc(sizeof(No));
    novoNo->termo = termoZero;
    novoNo->proximo = NULL;
    novaLista->inicio = novoNo;

    return novaLista;
}

// ? ========================================================================= FUNCOES DE ARMAZENAMENTO:
void addConstante(int *constante, int *chaveParaZerar) {
    char escolha;

    do
    {
        printf("\n- Voce deseja adicionar uma constante?\n(S) Sim\t(N) Nao\n- Digite sua escolha: ");
        fflush(stdin);
        scanf("%c", &escolha);  // Note o espa�o antes de %c para evitar problemas com caracteres em buffer

        escolha = toupper(escolha);

        if (escolha == 'S') {
            do {
                printf("\n- Qual valor para constante? : ");
                scanf("%d", constante);

                if (*constante < 0)
                    printf("Ops, digite novamente!");
            } while (*constante < 0);

            break;
        } else if (escolha == 'N') {
            (*chaveParaZerar)++;
        } else if ((escolha != 'N') && (escolha != 'S')) {
            printf("\n<< Ops! Digitou errado! Tente novamente! >>\n");
        }
    } while (escolha != 'N');
}

void addExpoente(int *expoente, int *chaveParaZerar) {
    char escolha;

    do {
        printf("\n\t- Voce deseja adicionar um expoente?\n\t(S) Sim\t(N) Nao\n\t- Digite sua escolha: ");
        fflush(stdin);
        scanf("%c", &escolha);  // Espa�o antes de %c para evitar problemas com caracteres em buffer
        escolha = toupper(escolha);

        if (escolha == 'S') {
            do {
                printf("\n\t- Qual valor para o expoente? : ");
                scanf("%d", expoente);

                if (*expoente < 0)
                    printf("Ops, digite novamente!");
            } while (*expoente < 0);

            break;
        } else if (escolha == 'N') {
            (*chaveParaZerar)++;
        } else {
            printf("\n<< Ops! Digitou errado! Tente novamente! >>\n");
        }
    } while (escolha != 'N');
}

void maisTermosOuNao(Lista *listaUsuario, int *chaveParaZerar, int valorDaConstante, int valorDoExpoente, int *fimOuNao) {
    char escolha;

    do {
        printf("\n\t- Voce deseja adicionar mais termos?\n\t(S) Sim\t(N) Nao\n\t- Digite sua escolha: ");
        fflush(stdin);      scanf("%c", &escolha);  // Espa�o antes de %c para evitar problemas com caracteres em buffer
        escolha = toupper(escolha);

        if ((escolha != 'S') && (escolha != 'N')) {
            printf("\nOPS! Deu problema!\n");
        }
    } while ((escolha != 'S') && (escolha != 'N'));

    if (escolha == 'N') {
        printf("\n<< Muito bom! Vamos acabar a insercao por aqui!>> \n");
        (*chaveParaZerar)++;

        if (*chaveParaZerar != 3) {
            No *novoNo = (No *)malloc(sizeof(No));
            adicionarTermosNos(&novoNo->termo, 1, valorDaConstante, valorDoExpoente);
            adicionarFim(listaUsuario, &novoNo->termo);
        }
        *fimOuNao = 1;
    } else {
        printf("\nOKAY!\n");
        No *novoNo = (No *)malloc(sizeof(No));
        adicionarTermosNos(&novoNo->termo, 1, valorDaConstante, valorDoExpoente);
        adicionarFim(listaUsuario, &novoNo->termo);
    }
}

void inserirTermo(Lista *lista, int valorParaConstante, int valorDoExpoente) {
    No *atual = lista->inicio;

    // Procurar se o termo j� existe
    while (atual != NULL) {
        if (atual->termo.algarismo == valorParaConstante && atual->termo.expoente == valorDoExpoente) {
            printf("\n- O termo ak'x^k ja existe. O que voce deseja fazer?\n");
            printf("1. Substituir o termo existente\n");
            printf("2. Adicionar ao termo existente\n");
            printf("3. Inserir na posicao correspondente\n- Digite uma opcao: ");
            int escolha;
            scanf("%d", &escolha);

            if (escolha == 1) {
                // Substituir o termo existente
                atual->termo.algarismo = valorParaConstante;
                return;
            } else if (escolha == 2) {
                // Adicionar ao termo existente
                atual->termo.algarismo += valorParaConstante;
                return;
            }
        }

        atual = atual->proximo;
    }

    // Se o termo n�o existe, insira na posi��o correspondente
        No *novoNo = (No *)malloc(sizeof(No));
        adicionarTermosNos(&novoNo->termo, 1, valorParaConstante, valorDoExpoente);
        adicionarFim(lista, &novoNo->termo);
}

void eliminarTermo(Lista *lista, int valorDoExpoente) {
    No *atual = lista->inicio;

    // Procurar o termo com o expoente desejado
    while (atual != NULL) {
        if (atual->termo.expoente == valorDoExpoente) {
            No *anterior = atual->anterior;
            No *proximo = atual->proximo;

            if (anterior != NULL) {
                anterior->proximo = proximo;
            } else {
                lista->inicio = proximo;
            }

            if (proximo != NULL) {
                proximo->anterior = anterior;
            }

            free(atual); // Libere a mem�ria do n� que ser� eliminado

            return; // O termo foi encontrado e removido, saia da fun��o
        }

        atual = atual->proximo;
    }

    printf("Termo com expoente %d nao encontrado no polinomio.\n", valorDoExpoente);
}

Armazenamento *inicializarArmazenamento() {
    Armazenamento *armazenamento = (Armazenamento *)malloc(sizeof(Armazenamento));
    armazenamento->listas = NULL;
    armazenamento->numListas = 0;
    return armazenamento;
}

void adicionarLista(Armazenamento *armazenamento, Lista *lista) {
    armazenamento->listas = (Lista *)realloc(armazenamento->listas, sizeof(Lista) * (armazenamento->numListas + 1));

    if (armazenamento->listas) {
        // Crie uma c�pia da lista
        Lista *copiaLista = (Lista *)malloc(sizeof(Lista));
        copiaLista->inicio = NULL;

        No *atual = lista->inicio;
        No *anterior = NULL;

        while (atual != NULL) {
            No *novoNo = (No *)malloc(sizeof(No));
            novoNo->termo = atual->termo; // Isso copia apenas os ponteiros, n�o cria c�pias profundas
            novoNo->proximo = NULL;
            novoNo->anterior = anterior;

            if (anterior != NULL) {
                anterior->proximo = novoNo;
            }

            if (copiaLista->inicio == NULL) {
                copiaLista->inicio = novoNo;
            }

            anterior = novoNo;
            atual = atual->proximo;
        }

        armazenamento->listas[armazenamento->numListas] = *copiaLista;
        armazenamento->numListas++;

        free(copiaLista); // Libere a c�pia da lista ap�s a adi��o
    } else {
        printf("Falha na alocacao de memoria. Nao e possivel adicionar mais listas.\n");
    }
}

Lista *recuperarLista(Armazenamento *armazenamento, int indice) {
    if (indice >= 0 && indice < armazenamento->numListas) {
        return &armazenamento->listas[indice];
    } else {
        printf("Indice invalido. A lista nao existe no armazenamento.\n");
        return NULL;
    }
}

void mostrarListasArmazenadas(Armazenamento *armazenamento) {
    for (int i = 0; i < armazenamento->numListas; i++) {
        printf("\nIndice (%d) : ", i);

        No *aux = armazenamento->listas[i].inicio;

        while (aux != NULL) {
            if ((aux->termo.algarismo == 1) && (aux->termo.expoente != 1))
            {
                printf("x^%d", aux->termo.expoente);
            } else if ((aux->termo.algarismo == 1) && (aux->termo.expoente == 1)){
                printf("x");
            } else{
            printf("%dx^%d", aux->termo.algarismo, aux->termo.expoente);
            }
            if (aux->proximo != NULL)   printf(" + ");
            aux = aux->proximo;
        }
    }
}

void liberarArmazenamento(Armazenamento *armazenamento) {
    free(armazenamento->listas);
    free(armazenamento);
}

// ? ========================================================================= FUNCOES DE MENU:
void menu(){
        printf("------------------------------------------");
        printf("\n|-> Opcoes de manipulacao:                |\n");
        printf("|1. Inicializar um polinomio              |\n");
        printf("|2. Inserir um novo termo no polinomio    |\n");
        printf("|3. Exibir o polinomio                    |\n");
        printf("|4. Eliminar um termo do polinomio        |\n");
        printf("|5. Reinicializar um polinomio            |\n");
        printf("|6. Salvar o polinomio                    |\n");
        printf("|7. Somar dois polinomios                 |\n");
        printf("|8. Calcular o valor de P(x)              |\n");
        printf("|9. Sair                                  |\n");
        printf("------------------------------------------");
}

void mostrarMensagemPdeX (Lista *lista, int x, unsigned long int resultado){
    printf("\n| P(x) = ");
    mostrarLista(lista);
    printf(", com P(%d) eh de [ %ld ]", x, resultado);
    printf(" |\n");
}

void tchau(){
    printf("------------------------------------------");
    printf("\n|-> Agradecemos a confianca!              |\n");
    printf("------------------------------------------");
}

// ? ========================================================================= FUNCOES DE CALCULO:
unsigned long int calcularPolinomio(Lista *lista, unsigned long int x){
    if(lista == NULL){
        return _ERRO;
    }
    if(listaVazia(lista)== _SUCESSO){
        return _ERRO;
    }
    unsigned long int resultado = 0;
    No *no = lista->inicio;
    while(no != NULL){
        resultado += no->termo.algarismo * pow(x, no->termo.expoente);
        no=no->proximo;
    }
    return resultado;
}

void calcularPparaVariasListas(Armazenamento *armazenamento, int valorParaX) {
    if (armazenamento->numListas == 0) {
        printf("< Nenhuma lista de polinomios armazenada! >\n");
        return;
    }

    unsigned long int menorResultado = -1; // Inicialize com um valor alto
    unsigned long int maiorResultado = 0 ;
    Lista *listaMaior = criar();
    Lista *listaMenor = criar();

    for (int i = 0; i < armazenamento->numListas; i++) {
        Lista *listaAtual = recuperarLista(armazenamento, i);

        if (listaAtual) {
            unsigned long int resultadoX = calcularPolinomio(listaAtual, valorParaX);
            printf("\n-> Resultado do Polinomio P(X) = ");
            mostrarLista(listaAtual);
            printf(" resultou em [%lu] ", resultadoX);

            if (resultadoX < menorResultado) {
                menorResultado = resultadoX;
                listaMenor = listaAtual;
            }

            if (resultadoX > maiorResultado) {
                maiorResultado = resultadoX;
                listaMaior = listaAtual;
            }
        } else {
            printf("Erro ao recuperar a lista de polinomios no indice %d.\n", i);
        }
    }

    printf("\n-> Com isso o menor resultado [ %lu ] veio da lista P(X) = ", menorResultado);
    mostrarLista(listaMenor);
    printf("\n-> Com isso o maior resultado [ %lu ] veio da lista P(X) = ", maiorResultado);
    mostrarLista(listaMaior);
    printf("\n\n");
}

void inserirTermoArm(Lista* lista, Termo termo) {
    No* novoNo = (No*)malloc(sizeof(No));  // Aloca mem�ria para o novo n�
    if (novoNo == NULL) {
        fprintf(stderr, "Erro ao alocar memoria para novo n�.\n");
        exit(1);  // Ou trate o erro de outra maneira adequada ao seu programa
    }

    novoNo->termo = termo;  // Define o termo do novo n�
    novoNo->proximo = NULL; // O novo n� ser� o �ltimo da lista, ent�o o pr�ximo � NULL

    if (lista->inicio == NULL) {
        // Se a lista est� vazia, o novo n� se torna o primeiro n� da lista
        lista->inicio = novoNo;
    } else {
        // Caso contr�rio, percorra a lista e insira o novo n� no final
        No* atual = lista->inicio;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novoNo;
    }
}

Lista* somarPolinomios(Lista* polinomioUm, Lista* polinomioDois) {
    Lista* resultado = criar();  // Fun��o para criar uma nova lista vazia
    No* no1 = polinomioUm->inicio;
    No* no2 = polinomioDois->inicio;

    while (no1 != NULL || no2 != NULL) {
        if (no1 == NULL) {
            inserirTermoArm(resultado, no2->termo);
            no2 = no2->proximo;
        } else if (no2 == NULL) {
            inserirTermoArm(resultado, no1->termo);
            no1 = no1->proximo;
        } else {
            if (no1->termo.expoente < no2->termo.expoente) {
                inserirTermoArm(resultado, no1->termo);
                no1 = no1->proximo;
            } else if (no1->termo.expoente > no2->termo.expoente) {
                inserirTermoArm(resultado, no2->termo);
                no2 = no2->proximo;
            } else {
                Termo novoTermo;
                novoTermo.algarismo = no1->termo.algarismo + no2->termo.algarismo;
                novoTermo.coeficiente = no1->termo.coeficiente;
                novoTermo.expoente = no1->termo.expoente;
                inserirTermoArm(resultado, novoTermo);
                no1 = no1->proximo;
                no2 = no2->proximo;
            }
        }
    }
    return resultado;
}
