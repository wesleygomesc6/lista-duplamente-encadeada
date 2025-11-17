/* * ARQUIVO DE INTERFACE: listadupla.h
 * * Define o Tipo Abstrato de Dados (TAD) para uma Lista Duplamente Encadeada.
 * Segue o princípio da "caixa-preta": o usuário não sabe
 * como a lista é implementada, apenas quais operações existem.
 */

// 1. DEFINIÇÃO DO TIPO OPACO
// O usuário não sabe o que há dentro da 'struct lista'.
// Ele só pode declarar ponteiros (Lista*) para ela.
// Isso é idêntico ao 'typedef struct ponto Ponto;' do PDF
typedef struct lista Lista;

// --- Protótipos das Operações (a "interface" pública) ---

/**
 * @brief Cria e aloca memória para uma nova lista vazia.
 * @return Um ponteiro para o TAD Lista.
 */
Lista *lista_cria();

/**
 * @brief Libera toda a memória alocada pela lista (nós e a própria lista).
 * Recebe um ponteiro para o ponteiro da lista (Lista**) para
 * poder anular o ponteiro original na 'main' (boa prática).
 * @param lista O endereço do ponteiro para a lista.
 */
void lista_libera(Lista **lista);

/**
 * @brief Verifica se a lista está vazia.
 * @param lista Ponteiro para a lista.
 * @return 1 (true) se a lista estiver vazia, 0 (false) caso contrário.
 */
int lista_vazia(Lista *lista);

/**
 * @brief Insere um novo elemento no início da lista.
 * @param lista Ponteiro para a lista.
 * @param valor O valor inteiro a ser inserido.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int lista_insere_inicio(Lista *lista, int valor);
/**
 * @brief Insere um novo elemento no final da lista.
 * @param lista Ponteiro para a lista.
 * @param valor O valor inteiro a ser inserido.
 * @return 1 em caso de sucesso, 0 em caso de falha.
 */
int lista_insere_fim(Lista *lista, int valor);
/**
 * @brief Remove a primeira ocorrência de um valor da lista.
 * @param lista Ponteiro para a lista.
 * @param valor O valor a ser removido.
 * @return 1 se o valor foi removido, 0 se não foi encontrado.
 */
int lista_remove(Lista *lista, int valor);
/**
 * @brief Imprime os elementos da lista do início para o fim.
 * @param lista Ponteiro para a lista.
 */
void lista_imprime_frente(Lista *lista);

/**
 * @brief Imprime os elementos da lista do fim para o início.
 * (Demonstra a utilidade do ponteiro 'anterior').
 * @param lista Ponteiro para a lista.
 */
void lista_imprime_tras(Lista *lista);