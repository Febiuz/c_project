#ifndef AUTO_H
#define AUTO_H

typedef struct caratteristiche* Auto;
struct caratteristiche{
    int cilindrata;
    int cavalli;
    float peso;
    int porte;
    int chilometri;
    char modello[30];
    char marca[30];
    int anno;
    char colore[30];
    char cambio[30];
    char carburante[30];
    int posti;
    float prezzo;
};

Auto crea_auto(
    int cc, int cv, float kg, int porte, int km,
    const char* modello, const char* marca, int anno,
    const char* colore, const char* cambio,
    const char* carburante, int posti, float prezzo
);

#endif