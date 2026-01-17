#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auto.h"
#include "albero.h"


Albero crea_nodo(Auto AUTO){
    if (AUTO == NULL) return NULL; // aggiunto controllo

    Albero nuovo = (Albero)malloc(sizeof(struct nodo));
    if(nuovo == NULL){
        printf("Errore allocazione nodo\n");
        return NULL; // invece di exit
    }
    nuovo->automobile = AUTO;
    nuovo->sx = NULL;
    nuovo->dx = NULL;
    return nuovo;
}

// ordino le auto in base ai chilometri
void inserisci_auto(Albero *A, Albero nuovo){
    if(*A==NULL){
        *A = nuovo;
        return;
    }

    if(nuovo->automobile->chilometri < (*A)->automobile->chilometri)
        inserisci_auto(&((*A)->sx), nuovo);
    else
        inserisci_auto(&((*A)->dx), nuovo);
}

// --- QUI definiamo prima rimuovi_auto (così elimina_nodo può usarla)
void rimuovi_auto(Albero *A, int km, const char* modello, const char* marca, const char* colore, const char* carburante, int anno, const char* cambio);

// --- elimina_nodo
void elimina_nodo(Albero *A) {
    if (*A == NULL)
        return;

    // Caso 1: nessun figlio
    if ((*A)->sx == NULL && (*A)->dx == NULL) {
        free((*A)->automobile);
        free(*A);
        *A = NULL;
        return;
    }

    // Caso 2: solo figlio sinistro
    if((*A)->dx == NULL) {
        Albero temp = (*A)->sx;
        free((*A)->automobile);
        free(*A);
        *A = temp;
        return;
    }
    // Caso 3: solo figlio destro
    else if((*A)->sx == NULL) {
        Albero temp = (*A)->dx;
        free((*A)->automobile);
        free(*A);
        *A = temp;
        return;
    }
    // Caso 4: due figli → trova il successore (minimo del sottoalbero destro)
    else{
        Albero succ = (*A)->dx;
        while (succ->sx != NULL){
            succ = succ->sx;
        }

        // Copia i dati del successore nel nodo attuale
        (*A)->automobile->chilometri = succ->automobile->chilometri;
        strncpy((*A)->automobile->modello, succ->automobile->modello, sizeof((*A)->automobile->modello)-1);
        (*A)->automobile->modello[sizeof((*A)->automobile->modello)-1] = '\0';
        strncpy((*A)->automobile->marca, succ->automobile->marca, sizeof((*A)->automobile->marca)-1);
        (*A)->automobile->marca[sizeof((*A)->automobile->marca)-1] = '\0';
        strncpy((*A)->automobile->colore, succ->automobile->colore, sizeof((*A)->automobile->colore)-1);
        (*A)->automobile->colore[sizeof((*A)->automobile->colore)-1] = '\0';
        strncpy((*A)->automobile->carburante, succ->automobile->carburante, sizeof((*A)->automobile->carburante)-1);
        (*A)->automobile->carburante[sizeof((*A)->automobile->carburante)-1] = '\0';
        (*A)->automobile->anno = succ->automobile->anno;
        strncpy((*A)->automobile->cambio, succ->automobile->cambio, sizeof((*A)->automobile->cambio)-1);
        (*A)->automobile->cambio[sizeof((*A)->automobile->cambio)-1] = '\0';

        // Elimina ricorsivamente il successore
        rimuovi_auto(&((*A)->dx),
                     succ->automobile->chilometri,
                     succ->automobile->modello,
                     succ->automobile->marca,
                     succ->automobile->colore,
                     succ->automobile->carburante,
                     succ->automobile->anno,
                     succ->automobile->cambio);
    }
}

// --- definizione completa di rimuovi_auto
void rimuovi_auto(Albero *A, int km, const char* modello, const char* marca, const char* colore, const char* carburante, int anno, const char* cambio)
{
    if (*A == NULL)
        return;

    if (km < (*A)->automobile->chilometri)
        rimuovi_auto(&((*A)->sx), km, modello, marca, colore, carburante, anno, cambio);

    else if (km > (*A)->automobile->chilometri)
        rimuovi_auto(&((*A)->dx), km, modello, marca, colore, carburante, anno, cambio);

    else if(strcmp((*A)->automobile->modello, modello) == 0 &&
            strcmp((*A)->automobile->marca, marca) == 0 &&
            strcmp((*A)->automobile->colore, colore) == 0 &&
            strcmp((*A)->automobile->carburante, carburante) == 0 &&
            (*A)->automobile->anno == anno &&
            strcmp((*A)->automobile->cambio, cambio) == 0)
    {
        elimina_nodo(A);
    }
}

void dealloca_albero(Albero *A) {
    if (*A == NULL)
        return;

    dealloca_albero(&((*A)->sx));
    dealloca_albero(&((*A)->dx));

    if ((*A)->automobile != NULL)
        free((*A)->automobile);

    free(*A);
    *A = NULL;
}

// ricerca in-order
void cerca_Auto_marca(Albero A, const char* marca, int *trovate){

    if(A==NULL){
        return;
    }

    cerca_Auto_marca(A->sx, marca, trovate);

    if(strcmp(A->automobile->marca, marca)==0){
        printf("Auto trovata:\n");
        printf("Marca & Modello: %s  %s\n", A->automobile->marca, A->automobile->modello);
        printf("Chilometri: %d\n", A->automobile->chilometri);
        printf("Anno di Immatricolazione: %d\n", A->automobile->anno);
        printf("Cilindrata motore(cc): %d\n", A->automobile->cilindrata);
        printf("Potenza(CV): %d\n", A->automobile->cavalli);
        printf("Peso(KG): %.2f\n", A->automobile->peso);
        printf("Tipo di carburante: %s\n", A->automobile->carburante);
        printf("Tipo di cambio: %s\n", A->automobile->cambio);
        printf("Colore carrozzeria: %s\n ", A->automobile->colore);
        printf("N porte: %d\n", A->automobile->porte);
        printf("N posti: %d\n", A->automobile->posti);
        printf("Prezzo: %.2f\n", A->automobile->prezzo);
        printf("\n\n");
        (*trovate)++;
    }

    cerca_Auto_marca(A->dx, marca, trovate);
}

void cerca_Auto_chilometri(Albero A, int km, int *trovate){
    if(A==NULL){
        return;
    }

    cerca_Auto_chilometri(A->sx, km, trovate);

    if(A->automobile->chilometri <= km){
        printf("Auto trovata:\n");
        printf("Marca & Modello: %s  %s\n", A->automobile->marca, A->automobile->modello);
        printf("Chilometri: %d\n", A->automobile->chilometri);
        printf("Anno di Immatricolazione: %d\n", A->automobile->anno);
        printf("Cilindrata motore(cc): %d\n", A->automobile->cilindrata);
        printf("Potenza(CV): %d\n", A->automobile->cavalli);
        printf("Peso(KG): %.2f\n", A->automobile->peso);
        printf("Tipo di carburante: %s\n", A->automobile->carburante);
        printf("Tipo di cambio: %s\n", A->automobile->cambio);
        printf("Colore carrozzeria: %s\n ", A->automobile->colore);
        printf("N porte: %d\n", A->automobile->porte);
        printf("N posti: %d\n", A->automobile->posti);
        printf("Prezzo: %.2f\n", A->automobile->prezzo);
        printf("\n\n");
        (*trovate)++;
    }

    cerca_Auto_chilometri(A->dx, km, trovate);

}

void cerca_Auto_anno(Albero A, int anno_MIN, int anno_MAX, int *trovate){
    if(A==NULL){
        return;
    }

    cerca_Auto_anno(A->sx, anno_MIN, anno_MAX, trovate);

    if(A->automobile->anno <= anno_MAX && A->automobile->anno >= anno_MIN){
        printf("Auto trovata:\n\n");
        printf("Marca & Modello: %s  %s\n", A->automobile->marca, A->automobile->modello);
        printf("Chilometri: %d\n", A->automobile->chilometri);
        printf("Anno di Immatricolazione: %d\n", A->automobile->anno);
        printf("Cilindrata motore(cc): %d\n", A->automobile->cilindrata);
        printf("Potenza(CV): %d\n", A->automobile->cavalli);
        printf("Peso(KG): %.2f\n", A->automobile->peso);
        printf("Tipo di carburante: %s\n", A->automobile->carburante);
        printf("Tipo di cambio: %s\n", A->automobile->cambio);
        printf("Colore carrozzeria: %s\n ", A->automobile->colore);
        printf("N porte: %d\n", A->automobile->porte);
        printf("N posti: %d\n", A->automobile->posti);
        printf("Prezzo: %.2f\n", A->automobile->prezzo);
        printf("\n\n");
        (*trovate)++;
    }

    cerca_Auto_anno(A->dx, anno_MIN, anno_MAX, trovate);
}

void cerca_Auto_prezzo(Albero A, float prezzo_MIN, float prezzo_MAX, int *trovate){
    if(A==NULL){
        return;
    }

    cerca_Auto_prezzo(A->sx, prezzo_MIN, prezzo_MAX, trovate);

    if(A->automobile->prezzo <= prezzo_MAX && A->automobile->prezzo >= prezzo_MIN){
        printf("Auto trovata:\n\n");
        printf("Marca & Modello: %s  %s\n", A->automobile->marca, A->automobile->modello);
        printf("Chilometri: %d\n", A->automobile->chilometri);
        printf("Anno di Immatricolazione: %d\n", A->automobile->anno);
        printf("Cilindrata motore(cc): %d\n", A->automobile->cilindrata);
        printf("Potenza(CV): %d\n", A->automobile->cavalli);
        printf("Peso(KG): %.2f\n", A->automobile->peso);
        printf("Tipo di carburante: %s\n", A->automobile->carburante);
        printf("Tipo di cambio: %s\n", A->automobile->cambio);
        printf("Colore carrozzeria: %s\n ", A->automobile->colore);
        printf("N porte: %d\n", A->automobile->porte);
        printf("N posti: %d\n", A->automobile->posti);
        printf("Prezzo: %.2f\n", A->automobile->prezzo);
        printf("\n\n");
        (*trovate)++;
    }

    cerca_Auto_prezzo(A->dx, prezzo_MIN, prezzo_MAX, trovate);
}

void stampa_albero_inorder(Albero A){
    if(A == NULL)
        return;

    stampa_albero_inorder(A->sx);

    printf("Caratteristiche Auto -->\nMarca & Modello: %s %s,\n"
           "Anno di immatricolazione: %d, \nChilometri: %d, \nCilindrata motore(cc): %d,\n"
           "Potenza(CV): %d,\nPeso(KG): %.2f,\n"
           "Tipo di carburante: %s,\nTipo di cambio: %s,\nColore carrozzeria: %s, \nPrezzo: %.2f \n\n",
           A->automobile->marca,
           A->automobile->modello,
           A->automobile->anno,
           A->automobile->chilometri,
           A->automobile->cilindrata,
           A->automobile->cavalli,
           A->automobile->peso,
           A->automobile->carburante,
           A->automobile->cambio,
           A->automobile->colore,
           A->automobile->prezzo
    );

    stampa_albero_inorder(A->dx);
}