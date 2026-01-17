#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auto.h"  // include l'header con typedef e dichiarazione

Auto crea_auto(int cc, int cv, float kg, int porte, int km,
                const char* modello, const char* marca, int anno,
                const char* colore, const char* cambio,
                const char* carburante, int posti, float prezzo) {

    Auto nuovo = malloc(sizeof(struct caratteristiche));
    if (nuovo == NULL) {
        printf("Errore allocazione Auto\n");
        return NULL; // non exit per permettere gestione errori da main
    }

    nuovo->cilindrata = cc;
    nuovo->cavalli = cv;
    nuovo->peso = kg;
    nuovo->porte = porte;
    nuovo->chilometri = km;
    nuovo->anno = anno;
    nuovo->posti = posti;
    nuovo->prezzo = prezzo;

    strncpy(nuovo->modello, modello, sizeof(nuovo->modello) - 1);
    nuovo->modello[sizeof(nuovo->modello) - 1] = '\0';
    strncpy(nuovo->marca, marca, sizeof(nuovo->marca) - 1);
    nuovo->marca[sizeof(nuovo->marca) - 1] = '\0';
    strncpy(nuovo->colore, colore, sizeof(nuovo->colore) - 1);
    nuovo->colore[sizeof(nuovo->colore) - 1] = '\0';
    strncpy(nuovo->cambio, cambio, sizeof(nuovo->cambio) - 1);
    nuovo->cambio[sizeof(nuovo->cambio) - 1] = '\0';
    strncpy(nuovo->carburante, carburante, sizeof(nuovo->carburante) - 1);
    nuovo->carburante[sizeof(nuovo->carburante) - 1] = '\0';

    return nuovo;
}
