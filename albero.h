#ifndef ALBERO_H
#define ALBERO_H

#include "auto.h"

typedef struct nodo* Albero;
struct nodo{
    Auto automobile;
    Albero sx;
    Albero dx;
};

// Creazione nodo
Albero crea_nodo(Auto AUTO);

// Inserimento
void inserisci_auto(Albero *A, Albero nuovo);

// Rimozione
void rimuovi_auto(Albero *A, int km, const char* modello, const char* marca, const char* colore, const char* carburante, int anno, const char* cambio);
void elimina_nodo(Albero *A);

// Dealocazione
void dealloca_albero(Albero *A);

// Stampa
void stampa_albero_inorder(Albero A);

// Ricerche
void cerca_Auto_marca(Albero A, const char* marca, int *trovate);
void cerca_Auto_chilometri(Albero A, int km, int *trovate);
void cerca_Auto_anno(Albero A, int anno_MIN, int anno_MAX, int *trovate);
void cerca_Auto_prezzo(Albero A, float prezzo_MIN, float prezzo_MAX, int *trovate);

#endif
