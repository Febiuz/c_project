#ifndef ALBERO_H
#define ALBERO_H

#include "auto.h"  // include la definizione di Auto

typedef struct nodo* Albero;

// Creazione nodo e inserimento
Albero crea_nodo(Auto auto);
void inserisci_auto(Albero *A, Albero nuovo);

// Rimozione e deallocazione
void rimuovi_auto(Albero *A, int km, const char* modello, const char* marca, const char* colore, const char* carburante, int anno, const char* cambio);
void dealloca_albero(Albero *A);

// Stampa
void stampa_albero_inorder(Albero A);

// Ricerca
void cerca_Auto_marca(Albero A, const char* marca, int *trovate);
void cerca_Auto_chilometri(Albero A, int km, int *trovate);
void cerca_Auto_anno(Albero A, int anno_MIN, int anno_MAX, int *trovate);
void cerca_Auto_prezzo(Albero A, float prezzo_MIN, float prezzo_MAX, int *trovate);

#endif
