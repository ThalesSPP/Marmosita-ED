#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

//Struct da placa:
typedef struct Placa_Marmore{

    char nome[255];

    float tamanho;

    float preco;

} Placa_Marmore;

//Struct do marmorista:
typedef struct Marmorista_Pessoa{

    int cadastro;

    char nome[255];

    //Criando um ponteiro pilha da struct 'Placa_Marmore':
    Placa_Marmore *pilha;

    int comeco;

    //Criando um ponteiro prox da struct 'Marmorista_Pessoa':
    struct Marmorista_Pessoa *prox;

} Marmorista_Pessoa;

//Criando um ponteiro fila da struct 'Marmorista_Pessoa':
Marmorista_Pessoa *fila = NULL;

//Chamando a função do cadastro:
void Cadastro();

//Chamando a função de remover:
void Deletar();

//Chamando a função do  menu:
void menu();

int main(void){

    int escolha = 0;

    while(escolha != 9){

        menu();

        printf("Selecione a opcao desejada: ");

        scanf("%d",&escolha);

        switch(escolha){

            case 1:

                Cadastro();

                break;

            case 2:

                Deletar();

                break;

            case 9:

                return 0;

            default:

                printf("Erro, escolha uma opcao valida!\n");

                break;

        }

    }

    return 0;

}

//Declaração da função Cadastro:
void Cadastro(){

    //Alocando um ponteiro do tipo 'Marmorista_Pessoa':
    Marmorista_Pessoa *novo_cadastro = (Marmorista_Pessoa*) malloc(sizeof(Marmorista_Pessoa));

    printf("Digite o nome do Marmorista que voce deseja cadastrar:\n");

    scanf("%s", novo_cadastro->nome);

    printf("Digite o cadastro (apenas numeros) do marmorista:\n");

    scanf("%d", &novo_cadastro->cadastro);

    //Incluindo o Marmorista dentro da pilha:
    novo_cadastro->pilha = NULL;

    novo_cadastro->comeco = -1;

    novo_cadastro->prox = NULL;

    int placas_qtd = 0;

    printf("Quantas placas o marmorista %s tera?", novo_cadastro->nome);

    scanf("%d", &placas_qtd);

    if(placas_qtd > 0){

        printf("Digite as informacoes da placa:\n");

        novo_cadastro->pilha = (Placa_Marmore*) malloc(placas_qtd *sizeof(Placa_Marmore));

        for(int i = 0; i < placas_qtd; i++){

            printf("Placa %d:\n", i + 1);

            printf("Nome:\n");

            scanf("%s", novo_cadastro->pilha[i].nome);

            printf("Tamanho (em m2):\n");

            scanf("%f", &novo_cadastro->pilha[i].tamanho);

            printf("Preco por m2:\n");

            scanf("%f", &novo_cadastro->pilha[i].preco);

            novo_cadastro->comeco++;

        }

    }

    if(fila == NULL){

        fila = novo_cadastro;

    }

    else{
        
        Marmorista_Pessoa *atual = fila;

        while(atual->prox != NULL){

            atual = atual->prox;

        }

        atual->prox = novo_cadastro;

    }

}

/*
A Função 'Cadastro' registra um novo marmorista, permitindo que o usuário digite o nome e o código 
do mesmo, após isso, ele informa o número de placas que será incluído na pilha do Marmorista. 
O programa aloca dinamicamente a pilha com o tamanho especificado e pede ao usuário que digite o nome, 
o tamanho (em m2) e o preço por metro quadrado de cada placa. As informações  são armazenadas na pilha 
do marmorista.
*/

//Declaração da função Deletar:
void Deletar(){

    if(fila == NULL){

        printf("Nao existem marmoristas cadastrados.\n");

        return;

    }

    Marmorista_Pessoa *primeiro = fila;

    printf("Marmorista %s, com o cadastro %d esta zerado.\n", primeiro->nome, primeiro->cadastro);

    float valorTotal = 0;

    if(primeiro->pilha != NULL){

        printf("Placas que vao ser cortadas:\n");

        for(int i = primeiro->comeco; i >= 0; i--){

            printf("Nome: %s.\n", primeiro->pilha[i].nome);

            printf("Tamanho: %.2f m2.\n", primeiro->pilha[i].tamanho);

            printf("Preco por cada m2: %.2f\n", primeiro->pilha[i].preco);

            valorTotal += primeiro->pilha[i].tamanho * primeiro->pilha[i].preco;

        }

        free(primeiro->pilha);

        primeiro->pilha = NULL;

        primeiro->comeco = -1;

    }

    fila = primeiro->prox;

    free(primeiro);

    primeiro = NULL;

    printf("Valor total que o marmorista arrecadou: R$ %.2f\n", valorTotal);

}

/*
A Função 'Deletar' remove o primeiro marmorista da fila e exibe na tela as informações 
do marmorista e das placas que ele recebeu para trabalhar. Logo após, é calculado o valor 
total obtido pelo marmorista ao cortar as placas e exibe na tela.
*/

//Declaração da função menu:
void menu(){

    printf("\n-----Marmorista-----\n\n");

    printf("1 ~ Cadastrar marmorista.\n");

    printf("2 ~ Deletar marmorista.\n");

    printf("9 ~ Sair.\n");

}

/*
Função para exibir o Menu de opções.
*/