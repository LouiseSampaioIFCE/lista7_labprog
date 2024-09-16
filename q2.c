#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM 100
#define TAM_ARQ 256
#define NUM_REGISTROS 100

typedef struct 
{
    char nome[TAM];
    int quantidade;
    float custo;
} Ferramenta;

void inicializarArquivo(const char *nomeArquivo);
void adicionarFerramenta(const char *nomeArquivo);
void listarFerramentas(const char *nomeArquivo);
void excluirFerramenta(const char *nomeArquivo);
void atualizarFerramenta(const char *nomeArquivo);


int main() {
    char nomeArquivo[TAM_ARQ];
    int opcao;

    printf("Digite o nome do arquivo de inventario (exemplo: hardware.dat): ");
    fgets(nomeArquivo, sizeof(nomeArquivo), stdin);
    nomeArquivo[strcspn(nomeArquivo, "\n")] = '\0'; 

    do {
        printf("\n1. Inicializar arquivo\n");
        printf("2. Adicionar ferramenta\n");
        printf("3. Listar ferramentas\n");
        printf("4. Excluir ferramenta\n");
        printf("5. Atualizar ferramenta\n");
        printf("6. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) 
        {
            case 1:
                inicializarArquivo(nomeArquivo);
                break;
            case 2:
                adicionarFerramenta(nomeArquivo);
                break;
            case 3:
                listarFerramentas(nomeArquivo);
                break;
            case 4:
                excluirFerramenta(nomeArquivo);
                break;
            case 5:
                atualizarFerramenta(nomeArquivo);
                break;
            case 6:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
                break;
        }
    } while (opcao != 6);

    return 0;
}


void inicializarArquivo(const char *nomeArquivo) 
{
    FILE *file = fopen(nomeArquivo, "wb");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Ferramenta ferramenta = {"", 0, 0.0};
    for (int i = 0; i < NUM_REGISTROS; i++) 
    {
        fwrite(&ferramenta, sizeof(Ferramenta), 1, file);
    }

    fclose(file);
    printf("Arquivo inicializado com %d registros vazios.\n", NUM_REGISTROS);
}

void adicionarFerramenta(const char *nomeArquivo) 
{
    FILE *file = fopen(nomeArquivo, "r+b");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Ferramenta ferramenta;
    int id;

    printf("Digite o numero do registro (0 a %d): ", NUM_REGISTROS - 1);
    scanf("%d", &id);
    getchar(); 

    if (id < 0 || id >= NUM_REGISTROS) 
    {
        printf("Numero de registro invalido.\n");
        fclose(file);
        return;
    }

    fseek(file, id * sizeof(Ferramenta), SEEK_SET);

    printf("Digite o nome da ferramenta: ");
    fgets(ferramenta.nome, sizeof(ferramenta.nome), stdin);
    ferramenta.nome[strcspn(ferramenta.nome, "\n")] = '\0'; 

    printf("Digite a quantidade: ");
    scanf("%d", &ferramenta.quantidade);

    printf("Digite o custo: ");
    scanf("%f", &ferramenta.custo);
    getchar();

    fwrite(&ferramenta, sizeof(Ferramenta), 1, file);
    fclose(file);
    printf("Ferramenta adicionada com sucesso.\n");
}

void listarFerramentas(const char *nomeArquivo) 
{
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Ferramenta ferramenta;
    for (int i = 0; i < NUM_REGISTROS; i++) 
    {
        fseek(file, i * sizeof(Ferramenta), SEEK_SET);
        fread(&ferramenta, sizeof(Ferramenta), 1, file);

        if (ferramenta.quantidade > 0) 
        {
            printf("Registro %d: Nome: %s, Quantidade: %d, Custo: %.2f\n", i, ferramenta.nome, ferramenta.quantidade, ferramenta.custo);
        }
    }

    fclose(file);
}

void excluirFerramenta(const char *nomeArquivo) 
{
    FILE *file = fopen(nomeArquivo, "r+b");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Ferramenta ferramenta = {"", 0, 0.0};
    int id;

    printf("Digite o numero do registro para excluir (0 a %d): ", NUM_REGISTROS - 1);
    scanf("%d", &id);
    getchar(); 

    if (id < 0 || id >= NUM_REGISTROS) 
    {
        printf("Numero de registro invalido.\n");
        fclose(file);
        return;
    }

    fseek(file, id * sizeof(Ferramenta), SEEK_SET);
    fwrite(&ferramenta, sizeof(Ferramenta), 1, file);

    fclose(file);
    printf("Registro excluido com sucesso.\n");
}

void atualizarFerramenta(const char *nomeArquivo) 
{
    FILE *file = fopen(nomeArquivo, "r+b");
    if (file == NULL) 
    {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    Ferramenta ferramenta;
    int id;

    printf("Digite o numero do registro para atualizar (0 a %d): ", NUM_REGISTROS - 1);
    scanf("%d", &id);
    getchar();

    if (id < 0 || id >= NUM_REGISTROS) 
    {
        printf("Numero de registro invalido.\n");
        fclose(file);
        return;
    }

    fseek(file, id * sizeof(Ferramenta), SEEK_SET);
    fread(&ferramenta, sizeof(Ferramenta), 1, file);

    if (ferramenta.quantidade <= 0) 
    {
        printf("Registro vazio. Nao é possivel atualizar.\n");
        fclose(file);
        return;
    }

    printf("Digite o novo nome da ferramenta (deixe em branco para manter o atual): ");
    fgets(ferramenta.nome, sizeof(ferramenta.nome), stdin);
    ferramenta.nome[strcspn(ferramenta.nome, "\n")] = '\0'; 

    printf("Digite a nova quantidade (digite -1 para manter o atual): ");
    int novaQuantidade;
    scanf("%d", &novaQuantidade);
    getchar(); 
    if (novaQuantidade != -1) 
    {
        ferramenta.quantidade = novaQuantidade;
    }

    printf("Digite o novo custo (digite -1 para manter o atual): ");
    float novoCusto;
    scanf("%f", &novoCusto);
    getchar(); 
    if (novoCusto != -1) 
    {
        ferramenta.custo = novoCusto;
    }

    fseek(file, id * sizeof(Ferramenta), SEEK_SET);
    fwrite(&ferramenta, sizeof(Ferramenta), 1, file);

    fclose(file);
    printf("Registro atualizado com sucesso.\n");
}