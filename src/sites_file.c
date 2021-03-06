#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADitem.h"
#include "TADlista.h"
#include "TADsite.h"
#include "TADavl.h"
#include "TADpriorityqueue.h"
#include "TADpchave.h"
#include "sites_file.h"


//funcao que le a linha de um arquivo ate encontrar o \n ou o fim do arquivo
char *readline(FILE *stream) {
    char *string = (char *) malloc(700);
    int pos = 0;
    do{
        string[pos] = (char) fgetc(stream);
    }while(string[pos] != '\n' && !feof(stream) && ++pos);

    string[pos] = '\0';

    return string;
}


//conta quantos sites tem no arquivo googlebot.txt
int conta_sites(FILE *arquivo){
    int num_sites = 1;

    while(!feof(arquivo)){
        char c = fgetc(arquivo);
        //se n for de fato o fim do arquvo e encontrar um \n contamos um site
        if(!feof(arquivo) && c == '\n')
            num_sites++;
    }
    return num_sites;
}


//funcao que separa os dados e os atribui para o item
ITEM *separa_dados(char *dados){
    ITEM *item;
    char *token;
    int aux, i = 1;
    //sabemos quais sao as informacoes de um site e a ordem: Chave, Nome, Relevancia, link, Palavras-chave
    //obtendo a chave
    token = strtok(dados, ",");
    aux = atoi(token);
    item = item_criar(aux, site_criar());

    //obtendo os outros dados
    while( token != NULL ){
        token = strtok(NULL, ",");
        if(i == 1)
            site_set_nome(item_get_conteudo(item), token);
        else if(i == 2){
            aux = atoi(token);
            site_set_relevancia(item_get_conteudo(item), aux);
        }
        else if(i == 3)
            site_set_link(item_get_conteudo(item), token);
        else
            site_add_palavra_chave(item_get_conteudo(item), token);
        i++;
   }
   return item;
}


//funcao que recebe os dados do googlebot.txt e os insere na lista
void recebe_dados(FILE *arquivo, int num_sites, LISTA **lista_de_sites, AVL **avl_de_palavras_chave) {
    char *dados_site;
    int i = 0;
    ITEM *item;

    LISTA *lista = lista_criar();
    AVL *avl = avl_criar();

    avl_set_dados_comparar(avl, &pchave_ref_comparar);
    avl_set_dados_apagar(avl, &pchave_ref_apagar);
    avl_set_dados_imprimir(avl, &pchave_ref_imprimir);

    //posicionando o cursor no inicio do arquivo
    fseek(arquivo, 0, SEEK_SET);

    //lendo os dados do arquivo
    while(i < num_sites){            
        dados_site = readline(arquivo);
        item = separa_dados(dados_site);
        free(dados_site);
        
        // Inserindo item contendo chave na lista
        lista_inserir(lista, item);
        
        // Inserindo o site na avl de palavras-chave
        // (insere as palavras-chave e o site na pqueue de sites_relacionados)
        SITE *site = (SITE *) item_get_conteudo(item);
        pchave_insere_site_na_avl(avl, site);

        i++;
    }
    
    *avl_de_palavras_chave = avl;
    *lista_de_sites = lista;
}

// Função que recebe grava os dados de uma lista de sites em um arquivo
boolean gravar_dados(const char* filename_saida, LISTA *lista_de_sites) {
    
    // arquivo de saída e vetor de itens criados
    FILE *arquivo_de_saida = fopen(filename_saida, "w");
    if (!arquivo_de_saida) return FALSE;

    // cada um dos sites sendo impressos no arquivo de saída
    lista_imprimir_conteudo(lista_de_sites, arquivo_de_saida, (void (*) (void *, FILE *)) &site_imprimir, "%04d,");

    // liberação de memória e retorno
    fclose(arquivo_de_saida);
    return TRUE;
}
