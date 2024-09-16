#include <stdio.h>
#include <stdlib.h>

#define TAM 100
#define TAM_ARQ 256

void escreverDadosEmCSV(const char *nomeArquivo);

int main() 
{
    char nomeArquivo[TAM_ARQ];
    
    printf("Digite o nome do arquivo CSV (exemplo: dados.csv): ");
    fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0'; 

    escreverDadosEmCSV(nomeArquivo);

    return 0;
}

void escreverDadosEmCSV(const char *nomeArquivo) 
{
    FILE *file = fopen(nomeArquivo, "w");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    char nome[TAM];
    int idade;
    char continuar;

    fprintf(file, "Nome,Idade\n");

    do {
        printf("Digite o nome do usuario: ");
        fgets(nome, sizeof(nome), stdin);
        nome[strcspn(nome, "\n")] = '\0'; 

        printf("Digite a idade do usuario: ");
        scanf("%d", &idade);
        getchar(); 

        fprintf(file, "%s,%d\n", nome, idade);

        printf("Deseja adicionar outro usuário? (s/n): ");
        scanf(" %c", &continuar);
        getchar(); 

    } while (continuar == 's' || continuar == 'S');

    fclose(file);
    printf("Dados gravados com sucesso no arquivo %s\n", nomeArquivo);
}