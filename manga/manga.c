#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "manga.h"

// Indices primario e secundario para registros de mangas
PrimaryIndex primaryIndex[MAX_MANGAS];
SecondaryIndex secondaryIndex[MAX_MANGAS];
// Contagem de registros de mangas
int mangaCount = 0;

void saveManga(Manga *m) {
    // Abre o arquivo de dados em modo de adicao
    FILE *dataFile = fopen(DATA_FILE, "ab");
    if (!dataFile) {
        perror("Erro ao abrir o arquivo de dados");
        exit(1);
    }
    // Move o ponteiro do arquivo para o final do arquivo
    fseek(dataFile, 0, SEEK_END);
    // Obtem a posicao atual do ponteiro do arquivo
    long position = ftell(dataFile);
    // Escreve o registro de manga no arquivo
    fwrite(m, sizeof(Manga), 1, dataFile);
    // Fecha o arquivo
    fclose(dataFile);

    // Atualiza os indices primario e secundario
    strcpy(primaryIndex[mangaCount].isbn, m->isbn);
    primaryIndex[mangaCount].position = position;
    strcpy(secondaryIndex[mangaCount].title, m->title);
    secondaryIndex[mangaCount].position = position;
    // Incrementa a contagem de mangas
    mangaCount++;
}

// Funcao para adicionar um novo registro de manga
void addManga() {
    // Verifica se o numero maximo de mangas foi alcancado
    if (mangaCount >= MAX_MANGAS) {
        printf("Numero maximo de mangas alcancado.\n");
        return;
    }

    // Obtem os detalhes do manga do usuario
    Manga m;
    printf("Digite o ISBN: ");
    scanf("%s", m.isbn);
    printf("Digite o titulo: ");
    scanf("%s", m.title);
    printf("Digite os autores: ");
    scanf("%s", m.authors);
    printf("Digite o ano de inicio: ");
    scanf("%d", &m.start_year);
    printf("Digite o ano de fim: ");
    scanf("%d", &m.end_year);
    printf("Digite o genero: ");
    scanf("%s", m.genre);
    printf("Digite a revista: ");
    scanf("%s", m.magazine);
    printf("Digite a editora: ");
    scanf("%s", m.publisher);
    printf("Digite o ano da edicao: ");
    scanf("%d", &m.edition_year);
    printf("Digite o numero total de volumes: ");
    scanf("%d", &m.total_volumes);
    printf("Digite o numero de volumes adquiridos: ");
    scanf("%d", &m.acquired_volumes);

    // Obtem os detalhes dos volumes do usuario
    for (int i = 0; i < m.acquired_volumes; i++) {
        printf("Digite o volume %d: ", i + 1);
        scanf("%d", &m.volume_list[i]);
    }

    // Salva o registro de manga
    saveManga(&m);
}

void displayMangas() {
    // Abre o arquivo de dados em modo de leitura
    FILE *dataFile = fopen(DATA_FILE, "rb");
    if (!dataFile) {
        perror("Erro ao abrir o arquivo de dados");
        exit(1);
    }
    // Le e exibe cada registro de manga
    for (int i = 0; i < mangaCount; i++) {
        // Move o ponteiro do arquivo para a posicao do registro do manga
        fseek(dataFile, primaryIndex[i].position, SEEK_SET);
        Manga m;
        // Le o registro do manga do arquivo
        fread(&m, sizeof(Manga), 1, dataFile);
        // Exibe os detalhes do manga
        printf("Manga %d:\n", i + 1);
        printf("ISBN: %s\n", m.isbn);
        printf("Titulo: %s\n", m.title);
        printf("Autores: %s\n", m.authors);
        printf("Ano de inicio: %d\n", m.start_year);
        printf("Ano de fim: %d\n", m.end_year);
        printf("Genero: %s\n", m.genre);
        printf("Revista: %s\n", m.magazine);
        printf("Editora: %s\n", m.publisher);
        printf("Ano da edicao: %d\n", m.edition_year);
        printf("Numero total de volumes: %d\n", m.total_volumes);
        printf("Volumes adquiridos: %d\n", m.acquired_volumes);
        // Exibe os detalhes dos volumes
        for (int j = 0; j < m.acquired_volumes; j++) {
            printf("Volume %d: %d\n", j + 1, m.volume_list[j]);
        }
        printf("\n");
    }

    fclose(dataFile);
}

// Funcao para deletar um registro de manga
void deleteManga() {
    // Obtem o ISBN do manga a ser deletado do usuario
    char isbn[20];
    printf("Digite o ISBN do manga a ser deletado: ");
    scanf("%s", isbn);
    // Encontra o registro do manga no indice primario
    for (int i = 0; i < mangaCount; i++) {
        if (strcmp(primaryIndex[i].isbn, isbn) == 0) {
            // Pede confirmacao antes de deletar
            printf("Voce tem certeza que quer deletar o manga intitulado '%s'? (sim/nao): ", secondaryIndex[i].title);
            char confirmation[4];
            scanf("%s", confirmation);

            if (strcmp(confirmation, "sim") == 0) {
                // Move os registros de manga restantes nos indices
                for (int j = i; j < mangaCount - 1; j++) {
                    primaryIndex[j] = primaryIndex[j + 1];
                    secondaryIndex[j] = secondaryIndex[j + 1];
                }
                // Decrementa a contagem de mangas
                mangaCount--;
                // Salva os indices atualizados
                saveIndices();
                printf("Manga deletado com sucesso.\n");
                return;
            } else {
                printf("Delecao cancelada.\n");
                return;
            }
        }
    }
    printf("Manga nao encontrado.\n");
}

// Funcao para editar um registro de manga
void editManga() {
    // Obtem o ISBN do manga a ser editado do usuario
    char isbn[20];
    printf("Digite o ISBN do manga a ser editado: ");
    scanf("%s", isbn);

    // Encontra o registro do manga no indice primario
    for (int i = 0; i < mangaCount; i++) {
        if (strcmp(primaryIndex[i].isbn, isbn) == 0) {
            FILE *dataFile = fopen(DATA_FILE, "rb+");
            if (!dataFile) {
                perror("Erro ao abrir o arquivo de dados");
                exit(1);
            }

            // Move o ponteiro do arquivo para a posicao do registro do manga
            fseek(dataFile, primaryIndex[i].position, SEEK_SET);
            Manga m;
            // Le o registro do manga do arquivo
            fread(&m, sizeof(Manga), 1, dataFile);

            printf("Editando Manga: %s\n", m.title);
            // Obtem os novos detalhes do manga do usuario
            printf("Digite a nova revista (atual: %s): ", m.magazine);
            scanf("%s", m.magazine);
            printf("Digite a nova editora (atual: %s): ", m.publisher);
            scanf("%s", m.publisher);
            printf("Digite o novo numero total de volumes (atual: %d): ", m.total_volumes);
            scanf("%d", &m.total_volumes);
            printf("Digite o novo numero de volumes adquiridos (atual: %d): ", m.acquired_volumes);
            scanf("%d", &m.acquired_volumes);

            // Obtem os novos detalhes dos volumes do usuario
            for (int j = 0; j < m.acquired_volumes; j++) {
                printf("Digite o novo volume %d (atual: %d): ", j + 1, m.volume_list[j]);
                scanf("%d", &m.volume_list[j]);
            }

            // Move o ponteiro do arquivo de volta para a posicao do registro do manga
            fseek(dataFile, primaryIndex[i].position, SEEK_SET);

            // Escreve o registro de manga atualizado no arquivo
            fwrite(&m, sizeof(Manga), 1, dataFile);

            // Fecha o arquivo
            fclose(dataFile);
            printf("Manga editado com sucesso.\n");
            return;
        }
    }
    printf("Manga nao encontrado.\n");
}

// Funcao para salvar os indices em arquivos
void saveIndices() {
    // Abre os arquivos de indices em modo de escrita
    FILE *primaryFile = fopen(PRIMARY_INDEX_FILE, "w");
    FILE *secondaryFile = fopen(SECONDARY_INDEX_FILE, "w");

    // Escreve cada indice no arquivo correspondente
    for (int i = 0; i < mangaCount; i++) {
        fprintf(primaryFile, "%s %ld\n", primaryIndex[i].isbn, primaryIndex[i].position);
        fprintf(secondaryFile, "%s %ld\n", secondaryIndex[i].title, secondaryIndex[i].position);
    }

    // Fecha os arquivos
    fclose(primaryFile);
    fclose(secondaryFile);
}

// Funcao para carregar os indices dos arquivos
void loadIndices() {
    // Abre os arquivos de indices em modo de leitura
    FILE *primaryFile = fopen(PRIMARY_INDEX_FILE, "r");
    FILE *secondaryFile = fopen(SECONDARY_INDEX_FILE, "r");
    // Se os arquivos de indices nao existirem, cria novos

    if (primaryFile == NULL && secondaryFile == NULL) {
        printf("Criando novos arquivos de indices.\n");
        saveIndices();
        return;
    }
    // Le cada indice do arquivo correspondente
    mangaCount = 0;
    while (mangaCount < MAX_MANGAS && fscanf(primaryFile, "%s %ld", primaryIndex[mangaCount].isbn, &primaryIndex[mangaCount].position) != EOF) {
        mangaCount++;
    }

    int count = 0;
    while (count < MAX_MANGAS && fscanf(secondaryFile, "%s %ld", secondaryIndex[count].title, &secondaryIndex[count].position) != EOF) {
        count++;
    }
    // Fecha os arquivos
    fclose(primaryFile);
    fclose(secondaryFile);
}

int main() {
    int choice;
    // Carrega os indices
    loadIndices();
    do {
        // Exibe o menu
        printf("1. Adicionar Manga\n");
        printf("2. Exibir Mangas\n");
        printf("3. Deletar Manga\n");
        printf("4. Editar Manga\n");
        printf("5. Sair\n");
        printf("Digite sua escolha: ");
        scanf("%d", &choice);
        // Executa a operacao escolhida
        switch (choice) {
            case 1:
                addManga();
                saveIndices();
                break;
            case 2:
                displayMangas();
                break;
            case 3:
                deleteManga();
                saveIndices();
                break;
            case 4:
                editManga();
                saveIndices();
                break;
            case 5:
                printf("Saindo...\n");
                break;
            default:
                printf("Escolha invalida. Por favor, tente novamente.\n");
        }
    } while (choice != 5);

    return 0;
}
