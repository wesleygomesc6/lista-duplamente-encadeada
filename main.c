/* * ARQUIVO DO USUÁRIO: main.c
 * * Simula um programa que usa o TAD ListaDupla.
 * Ele só inclui a interface ".h" e não tem acesso
 * direto à implementação.
 */

#include <stdio.h>
#include <stdlib.h>
#include "listadupla.h" // 1. Inclui APENAS a interface

int main()
{
    printf("--- Testando o TAD Lista Duplamente Encadeada ---\n");

    // 2. Declara um ponteiro para o TAD
    Lista *minha_lista;

    // Lista l_erro; // ERRO! Tipo 'Lista' é opaco [cite: 239]

    // 3. Usa as operações da interface
    minha_lista = lista_cria();
    lista_imprime_frente(minha_lista); // Testa impressão com lista vazia

    // 4. Testando inserções
    printf("\n--- Inserindo ---\n");
    lista_insere_fim(minha_lista, 10);
    lista_insere_fim(minha_lista, 20);
    lista_insere_inicio(minha_lista, 5);

    // TENTATIVA DE QUEBRAR O TAD (dar erro de compilação)
    // minha_lista->inicio = NULL; // ERRO: 'lista' has incomplete type
    // Isso prova que o encapsulamento funciona!

    // 5. Testando impressões (frente e trás)
    lista_imprime_frente(minha_lista); // Esperado: 5 <=> 10 <=> 20 <=> NULL
    lista_imprime_tras(minha_lista);   // Esperado: 20 <=> 10 <=> 5 <=> NULL

    // 6. Testando remoções
    printf("\n--- Removendo ---\n");

    printf("Removendo 10 (meio)...\n");
    lista_remove(minha_lista, 10);
    lista_imprime_frente(minha_lista); // Esperado: 5 <=> 20 <=> NULL

    printf("Removendo 5 (inicio)...\n");
    lista_remove(minha_lista, 5);
    lista_imprime_frente(minha_lista); // Esperado: 20 <=> NULL

    printf("Removendo 20 (fim/ultimo)...\n");
    lista_remove(minha_lista, 20);
    lista_imprime_frente(minha_lista); // Esperado: Lista: [vazia]

    // 7. Testando liberação
    printf("\n--- Liberando memoria ---\n");
    lista_libera(&minha_lista);

    if (minha_lista == NULL)
    {
        printf("Ponteiro da lista anulado com sucesso.\n");
    }

    return 0;
}