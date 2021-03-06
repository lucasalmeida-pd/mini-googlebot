#ifndef _PCHAVE_H_
    #define _PCHAVE_H_

    #include "TADpriorityqueue.h"
    #include "TADavl.h"
    #include "TADsite.h"
    #include <string.h>

    typedef struct palavra_chave_ref PALAVRA_CHAVE_REF;
    


    // Criar a palavra chave na memória Heap
    // - Parâmetros
    //    -> palavra_chave
    //    -> sites_relacioandos: ponteiro para os sites relacioandos  
    // - Retorno
    //    -> ponteiro para estrutura palavra_chave, NULL se der erro
    PALAVRA_CHAVE_REF *pchave_ref_criar(char *palavra_chave, PQUEUE *sites_relacionados);

    // Apaga a palvra chave da memoria
    // - Parâmetros
    //    -> dados: endereço do dado
    // - Retorno
    //    void
    void pchave_ref_apagar(void **dados);



    // Recupera a palavra chave
    // - Parâmetros
    //    -> pchave: palavra chave de interesse 
    // - Retorno
    //    -> retorna a palavra chave caso o parametro nao seja NULL, se for retorna NULL
    char *pchave_get_palavra_chave(PALAVRA_CHAVE_REF *pchave);

    // Recupera os sites relacioandas a palavra chave
    // - Parâmetros
    //    -> pchave: palavra chave de interesse 
    // - Retorno
    //    -> retorna um ponteiro para a fila de prioridade de sites o parametro nao seja NULL, se for retorna NULL
    PQUEUE *pchave_get_sites_relacionados(PALAVRA_CHAVE_REF *pchave);




    // Compara duas palavras chaves
    // - Parâmetros
    //    -> dados1
    //    -> dados2
    // - Retorno
    //    -> retorna 0 se as palavras forem iguais e diferente de 0 se nao forem iguais 
    int pchave_ref_comparar(void *dados1, void *dados2);
    
    // "Seta" uma fila de prioridade de sites a palavra chave passada como parametro
    // - Parâmetros
    //    -> pchave: palavra chave de interesse 
    //    -> sites_relacionados: fila de prioridade com sites
    // - Retorno
    //    void
    void pchave_set_sites_relacionados(PALAVRA_CHAVE_REF *pchave, PQUEUE *sites_relacionados);



    // Imprimi a palavra chave e o site com mais relevancia
    // - Parâmetros
    //    -> dados que deseja imprimir
    // - Retorno
    //      void
    void pchave_ref_imprimir(void *dados);

    // Procura a palavra chave na AVL de palavras chaves
    // - Parâmetros
    //    -> AVL de palavras chaves que deseja fazer a busca
    //    -> palavra chave que deseja buscar
    // - Retorno
    //      ponteiro para a estrutura PALAVRA_CHAVE_REF da palara encontrada
    PALAVRA_CHAVE_REF *pchave_ref_busca_em_avl(AVL *avl_de_palavras_chave, char *palavra_chave);



    // Insere o site na fila de prioridade de uma palavra-chave específica
    // - Parâmetros
    //    -> AVL de palavras chaves
    //    -> Site que deseja fazer a insercao
    //    -> Palavra-chave a ter o site adicionado na fila de prioridade
    // - Retorno
    //     void
    void pchave_insere_site_na_avl_para_palavra_chave_especifica(AVL *avl_de_palavras_chave, SITE *site, char *palavra_chave);

    // Procura as palavras chaves do site na AVL e insere o site na fila de prioridade de cada uma
    // - Parâmetros
    //    -> AVL de palavras chaves que deseja fazer a busca
    //    -> site que deseja fazer a insercao
    // - Retorno
    //     void
    void pchave_insere_site_na_avl(AVL *avl_de_palavras_chave, SITE *site);

    // Procura as palavras chaves do site na AVL e remove o site da fila de prioridade de cada uma
    // - Parâmetros
    //    -> AVL de palavras chaves que deseja fazer a busca
    //    -> site que deseja fazer a remoção
    // - Retorno
    //     void
    void pchave_remove_site_na_avl(AVL *avl_de_palavras_chave, SITE *site);



#endif