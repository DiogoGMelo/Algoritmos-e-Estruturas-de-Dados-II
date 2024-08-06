// manga.h

#ifndef MANGA_H
#define MANGA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MANGAS 100
#define MAX_TITLE_LENGTH 100
#define DATA_FILE "mangas.dat"
#define PRIMARY_INDEX_FILE "primary_index.txt"
#define SECONDARY_INDEX_FILE "secondary_index.txt"

typedef struct {
    char isbn[20];
    char title[MAX_TITLE_LENGTH];
    char authors[100];
    int start_year;
    int end_year;
    char genre[50];
    char magazine[50];
    char publisher[50];
    int edition_year;
    int total_volumes;
    int acquired_volumes;
    int volume_list[100];
} Manga;

typedef struct {
    char isbn[20];
    long position;
} PrimaryIndex;

typedef struct {
    char title[MAX_TITLE_LENGTH];
    long position;
} SecondaryIndex;

void saveManga(Manga *m);
void addManga();
void displayMangas();
void deleteManga();
void editManga();
void saveIndices();
void loadIndices();

#endif // MANGA_H