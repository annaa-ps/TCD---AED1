
#ifndef TAD_H
#define TAD_H

#include "tad.h"  // Inclua quaisquer bibliotecas necess�rias

#define _ERRO -1
#define _SUCESSO 0
#define _FALHA_ALOCACAO 1

// ? ========================================================================= Estrutura de armazenamento individual do polinomio:
/**
 * @brief Estrutura que existe dentro do n�.
 * @note 4x^2, exemplo usado na definicao dos parametros.
 * @param algarismo Neste caso, seria o 4. Ele � o parametro da "constante".
 * @param coeficiente Neste caso, seria o x. Que dado um valor para ele, hevar� uma alocacao de memoria e casting.
 * @param expoente Neste caso, seria o 2. Valor inteiro e positivo que ser� eleveado o x.
*/
struct termo{
    int algarismo;          // Valor que acompanha a esquerda de X
    int coeficiente;    // Valor da base X. Por padrao 1, mas mude e caso de ter um X dado.
    int expoente;           // Expoente pelo qual o coeficiente � elevado
}; typedef struct termo Termo;

/**
 * @brief Estrutura n�.
 * @param proximo Basicamente o n� seguinte do atual.
 * @param anterior Basicamente o n� anterior ao atual.
*/
struct no{
    Termo termo;
    struct no *proximo;
    struct no *anterior;
}; typedef struct no No;

/**
 * @brief Estrutura da lista.
 * @param inicio Parametro que inicia a lista encadeada.
*/
struct lista{
    No *inicio;
}; typedef struct lista Lista;

// ? ========================================================================= Estrutura de armazenamento individual do polinomio:
/**
 * @brief Estrutura que armazena todos os polinomios.
 * @param listas As listas
 * @param numListas Numero de listas
 */
struct armazenamento {
    Lista *listas;
    int numListas;
}; typedef struct armazenamento Armazenamento;


// ? ========================================================================= Funcoes de manipulacao da lista:
/**
 * @brief Funcao que serve apenas para incrementar coisas na lista.
 * @param termo Lista que queremos inserir informacoes.
 * @param valorParaX Por padrao � o caracter X.
 * @param valorParaConstante Algarismo para multiplicar x.
 * @param valorDoExpoente Expoente para a base X.
 * @note 4x^2. 4 � valorParaConstante, x � valorParaX, 2 � valorDoExcoente*/
void adicionarTermosNos(Termo *termo, int valorParaX, int valorParaConstante, int valorDoExpoente);

/**
 * @brief Funcao que cria a lista.
 * @param Vazio.
 * @return uma lista N, ser� retornada para a variavel atribuida.*/
Lista * criar();

/**
 * @brief Funcao que verifia se a lista est� vazia.
 * @param lista. Lista que voce quer verificar.
 * @return _ERRO (-1) Caso ela tenha elementos. // _SUCESSO (0) Para o caso dela ser realmente vazia. // _FALHA_ALOCACAO (1) Para uma lista n�o alocada.*/
int listaVazia(Lista *lista);

/**
 * @brief Funcao que imprime a lista.
 * @param lista Que queremos mostrar.,
 * @return _FALHA_ALOCACAO = 1 para falha em alocacao // _SUCESSO = 0 para tudo certo.
 * @note Ela ja determina X como X, use-a apenas para mostrar as expressoes.*/
int mostrarLista(Lista *lista);

/**
 * @brief Fun��o que adiciona um n� ao final da lista.
 * @param lista A lista � qual queremos adicionar o n�.
 * @param termo O n� que queremos inserir.
 * @return _FALHA_ALOCACAO = 1 para falha em alocacao // _SUCESSO = 0 para tudo certo. // _ERRO: Erro l�gico da funcao.*/
int adicionarFim(Lista *lista, Termo *termo);

/**
 * @brief Funcao que remove o n� inicio.
 * @param lista Lista que queremos retirar o inicio.
 * @return _FALHA_ALOCACAO = 1 para falha em alocacao // _SUCESSO = 0 para tudo certo. // _ERRO: Erro l�gico da funcao.*/
int removerInicio(Lista *lista);

/**
 * @brief Fun��o para esvaziar a lista, removendo todos os elementos.
 * @param lista A lista que desejamos esvaziar.
 * @return _SUCESSO (0) se a lista for esvaziada com sucesso. // _ERRO (-1) se ocorrer um erro l�gico na fun��o, como tentar esvaziar uma lista j� vazia.
 */
int esvaziarLista(Lista *lista);

/**
 * @brief Fun��o para zerar a lista, removendo todos os elementos deixando no padr�o.
 * @param lista A lista que desejamos zerar para o formato padr�o.
 * @return Por ser do tipo lista, atribua a funcao a lista que quer zerar.
 */
Lista* zerarLista(Lista *lista);

// ? ========================================================================= FUNCOES DE ARMAZENAMENTO:
/**
 * @brief Funcao que TRATA o input da constante.
 * @param constante    Onde ser� guardado o input de constante do usuario.
 * @param chaveParaZerar Variavel que checa se a pessoa s� dir� n�o, e portanto ser� uma expressao zerada. * @param listaZerada
 * @return VOID.*/
void addConstante(int *constante, int *chaveParaZerar);

/**
 * @brief Funcao que TRATA o input da constante.
 * @param expoente    Onde ser� guardado o input de constante do usuario.
 * @param chaveParaZerar Variavel que checa se a pessoa s� dir� n�o, e portanto ser� uma expressao zerada. * @param listaZerada
 * @return VOID.*/
void addExpoente(int *expoente, int *chaveParaZerar);

/**
 * @brief Funcao que trata o input do usuario.
 * @param listaUsuario Lista que queremos adicionar conteudo.
 * @param chaveParaZerar Variavel que checa se a pessoa s� dir� n�o, e portanto ser� uma expressao zerada.
 * @param valorDaConstante Valor para o algarismo ao lado esquerdo de X.
 * @param valorDoExpoente Valor do expoente do termo atual.
 * @param fimOuNao Saber se ir� ter mais termos para adicionar.
 * @return VOID.
 * @note Essa funcao trata todo o input lido at� ent�o, para inserir no n�. E ela que deternina o fim do while de insercoes nos n�s.*/
void maisTermosOuNao(Lista *listaUsuario, int *chaveParaZerar, int valorDaConstante, int valorDoExpoente, int *fimOuNao);

/**
 * @brief Fun��o que lida com a adicao de UM novo termo na lista atual.
 * @param lista A lista que desejamos atribuir esse novo n�.
 * @param valorParaConstante Variavel input do usuario para o algarismo da constante
 * @param valorDoExpoente Variavel input do usuario para o expoente
 * @note As variaveis sao usadas pra comparacoes
 * @return N�o h�. Tudo � ajustado em tempo de excucao.
 */
void inserirTermo(Lista *lista, int valorParaConstante, int valorDoExpoente);

/**
 * @brief Fun��o que lida com a retirada de UM novo termo na lista atual.
 * @param lista A lista que desejamos atribuir esse novo n�.
 * @param valorDoExpoente Variavel input do usuario para o expoente.
 * @note O expoente � usado na verificacao.
 * @return N�o h�. Tudo � ajustado em tempo de excucao.
 */
void eliminarTermo(Lista *lista, int valorDoExpoente);

/**
 * @brief Fun��o para inicializar a estrutura de armazenamento.
 * @return A estrutura de armazenamento inicializada.
 */
Armazenamento *inicializarArmazenamento();

/**
 * @brief Fun��o para adicionar uma lista ao armazenamento.
 * @param armazenamento A estrutura de armazenamento.
 * @param lista A lista a ser adicionada.
 */
void adicionarLista(Armazenamento *armazenamento, Lista *lista);

/**
 * @brief Fun��o para recuperar uma lista armazenada com base no �ndice.
 * @param armazenamento A estrutura de armazenamento.
 * @param indice O �ndice da lista a ser recuperada.
 * @return A lista recuperada ou NULL se o �ndice for inv�lido.
 */
Lista *recuperarLista(Armazenamento *armazenamento, int indice);

/**
 * @brief Fun��o para mostrar as listas armazenadas.
 * @param armazenamento A estrutura de armazenamento.
 */
void mostrarListasArmazenadas(Armazenamento *armazenamento);

/**
 * @brief Fun��o para liberar a mem�ria alocada para a estrutura de armazenamento.
 * @param armazenamento A estrutura de armazenamento a ser liberada.
 */
void liberarArmazenamento(Armazenamento *armazenamento);

/**
 * @brief Funcao que printa o menu principal.
 * @return N�o h�. Apenas printfs.
 */
void menu();

/**
 * @brief Funcao apenas para mostrar a funcao P(X) que est� sendo calculada.
 * @param lista A lista que estamos lidando.
 * @param x valor do x calculado.
 * @param resultado Retorno do polinomio calculado.
*/
void mostrarMensagemPdeX (Lista *lista, int x, unsigned long int resultado);

/**
 * @brief Funcao que printa um tchau.
 * @return N�o h�. Apenas printfs.
 */
void tchau();

// ? ========================================================================= FUNCOES DE CALCULO:
/**
 * @brief Funcao que dada uma lista, e um valor x, retorna o calculo do polinomio.
 * @param lista A lista escolhida pelo usario
 * @param x
 * @note O usigned long int foi lidar com um intervalo maior de resultados.
 *
*/
unsigned long int calcularPolinomio(Lista *lista, unsigned long int x);

/**
 * @brief Fun��o para calcular o valor de P(x) para v�rias listas de polin�mios.
 * @param armazenamento A estrutura de armazenamento que cont�m as listas de polin�mios.
 * @param valorParaX O valor de x para o qual P(x) deve ser calculado.
 */
void calcularPparaVariasListas(Armazenamento *armazenamento, int valorParaX);

/**
 * @brief Esta fun��o insere um novo termo em uma lista armazenada. Ela aloca dinamicamente um novo n�, define o termo nesse n� e o adiciona ao final da lista.
 * @param lista A lista qual o n� ser� inserido.
 * @param termo O termo a ser inserido na lista.
 */
void inserirTermoArm(Lista* lista, Termo termo);

/**
 * @brief Esta fun��o soma dois polin�mios representados por listas encadeadas, considerando os termos com expoentes iguais. O resultado � armazenado em uma nova lista.
 * @param polinomioUm Se trata do primeiro polinomio escolhido pelo usuario
 * @param polinomioDois Se trata do segudo polinomio escolhido pelo usuario
 */
Lista* somarPolinomios(Lista* polinomioUm, Lista* polinomioDois);
#endif
