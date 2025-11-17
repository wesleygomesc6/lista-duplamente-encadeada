/* * ARQUIVO DE IMPLEMENTAÇÃO: listadupla.c
 * * Contém o código "secreto" do TAD ListaDupla.
 * Define as estruturas de dados reais e implementa as
 * funções da interface.
 */

#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h" // Inclui os protótipos da interface

// --- DEFINIÇÕES DAS ESTRUTURAS REAIS (OCULTAS) ---

// 1. Estrutura do Nó (oculta do usuário)
// Contém o dado e DOIS ponteiros: um para o próximo e um para o anterior.
typedef struct no
{
    int informacao;
    struct no *prox;
    struct no *ant; // A "mágica" da lista duplamente encadeada
} No;

// 2. Estrutura Descritora da Lista (o TAD em si)
// Esta é a definição real da 'struct lista' opaca.
// Ela guarda ponteiros para o primeiro e o último nó.
struct lista
{
    No *inicio;
    No *fim;
};

// --- IMPLEMENTAÇÃO DAS OPERAÇÕES ---

// Operação de Criação (similar a Ponto_cria)
Lista *lista_cria()
{
    // Aloca memória para a ESTRUTURA da lista (o descritor)
    Lista *lista = (Lista *)malloc(sizeof(Lista));

    // Se a alocação funcionar, inicializa os campos
    if (lista != NULL)
    {
        lista->inicio = NULL; // Lista começa vazia
        lista->fim = NULL;    // Lista começa vazia
    }
    return lista;
}

int lista_vazia(Lista *lista)
{
    // A lista só está vazia se o 'inicio' for nulo.
    // (Um TAD nulo também é considerado "vazio" neste caso)
    return (lista == NULL || lista->inicio == NULL);
}

// Operação de Inserção (Início)
int lista_insere_inicio(Lista *lista, int valor)
{
    // 1. Validação do TAD
    if (lista == NULL)
        return 0; // TAD não existe

    // 2. Alocação do novo nó (que contém o dado)
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
        return 0; // Falha de alocação

    // 3. Preenchimento do nó
    novo->informacao = valor;
    novo->prox = lista->inicio; // O próximo do novo é o antigo 'inicio'
    novo->ant = NULL;           // O anterior do novo é NULL (ele é o primeiro)

    // 4. Encadear o nó na lista
    if (lista_vazia(lista))
    {
        // Se a lista estava vazia, o 'inicio' E o 'fim' apontam para o novo nó
        lista->inicio = novo;
        lista->fim = novo;
    }
    else
    {
        // Se a lista NÃO estava vazia, o 'ant' do antigo 'inicio'
        // deve apontar para o novo nó.
        lista->inicio->ant = novo; // era NULL
        lista->inicio = novo;      // Atualiza o 'inicio' da lista
    }
    return 1; // Sucesso
}

// Operação de Inserção (Fim)
int lista_insere_fim(Lista *lista, int valor)
{
    // 1. Validação do TAD
    if (lista == NULL)
        return 0;

    // 2. Alocação do novo nó
    No *novo = (No *)malloc(sizeof(No));
    if (novo == NULL)
        return 0;

    // 3. Preenchimento do nó
    novo->informacao = valor;
    novo->prox = NULL;      // O próximo do novo é NULL (ele é o último)
    novo->ant = lista->fim; // O anterior do novo é o antigo 'fim'

    // 4. Encadear o nó na lista
    if (lista_vazia(lista))
    {
        // Se estava vazia, é o mesmo caso do insere_inicio
        lista->inicio = novo;
        lista->fim = novo;
    }
    else
    {
        // Se NÃO estava vazia, o 'prox' do antigo 'fim'
        // deve apontar para o novo nó.
        lista->fim->prox = novo; // era NULL
        lista->fim = novo;       // Atualiza o 'fim' da lista
    }
    return 1; // Sucesso
}

// Operação de Impressão (para frente)
void lista_imprime_frente(Lista *lista)
{
    if (lista_vazia(lista))
    {
        printf("Lista: [vazia]\n");
        return;
    }

    No *p = lista->inicio; // Ponteiro auxiliar 'p' começa no início
    printf("Lista (->): ");
    while (p != NULL)
    {
        printf("%d <=> ", p->informacao);
        p = p->prox; // Caminha para o próximo
    }
    printf("NULL\n");
}

// Operação de Impressão (para trás)
void lista_imprime_tras(Lista *lista)
{
    if (lista_vazia(lista))
    {
        printf("Lista: [vazia]\n");
        return;
    }

    No *p = lista->fim; // Ponteiro auxiliar 'p' começa no fim
    printf("Lista (<-): ");
    while (p != NULL)
    {
        printf("%d <=> ", p->informacao);
        p = p->ant; // Caminha para o anterior
    }
    printf("NULL\n");
}

// Operação de Remoção (a mais complexa)
int lista_remove(Lista *lista, int valor)
{
    if (lista_vazia(lista))
        return 0;

    // 1. Encontrar o nó a ser removido
    No *p = lista->inicio;
    while (p != NULL && p->informacao != valor)
    {
        p = p->prox;
    }

    // 2. Se não achou (p == NULL), retorna 0
    if (p == NULL)
        return 0; // Valor não encontrado

    // 3. Se achou, precisamos re-conectar a lista

    // Se 'p' não é o primeiro, o 'prox' do anterior a 'p' aponta para o 'prox' de 'p'
    if (p->ant != NULL)
    {
        p->ant->prox = p->prox;
    }
    else
    {
        // Se 'p' é o primeiro, o 'inicio' da lista vira o 'prox' de 'p'
        lista->inicio = p->prox;
    }

    // Se 'p' não é o último, o 'ant' do próximo a 'p' aponta para o 'ant' de 'p'
    if (p->prox != NULL)
    {
        p->prox->ant = p->ant;
    }
    else
    {
        // Se 'p' é o último, o 'fim' da lista vira o 'ant' de 'p'
        lista->fim = p->ant;
    }

    // 4. Liberar a memória do nó 'p'
    free(p);
    return 1; // Sucesso
}

// Operação de Destruição (similar a Ponto_libera)
void lista_libera(Lista **lista)
{
    if (lista == NULL || *lista == NULL)
        return; // Verifica se o ponteiro é válido

    No *primeiroNo = (*lista)->inicio; // Pega o primeiro nó
    while (primeiroNo != NULL)
    {
        No *temporario = primeiroNo->prox; // Salva o próximo nó
        free(primeiroNo);                  // Libera o nó atual
        primeiroNo = temporario;           // Avança para o próximo
    }

    // No final, libera a estrutura da lista (o descritor)
    free(*lista);

    // Anula o ponteiro original na main para evitar "uso após liberação"
    *lista = NULL;
}