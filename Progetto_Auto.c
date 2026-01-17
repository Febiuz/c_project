#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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

typedef struct nodo* Albero;
struct nodo{
    Auto automobile;
    Albero sx;
    Albero dx;
};

Auto crea_auto(int cc, int cv, float kg, int porte, int km, const char* modello, const char* marca, int anno, const char* colore, const char* cambio, const char* carburante, int posti, float prezzo){
    Auto nuovo = malloc(sizeof(struct caratteristiche));
    if (nuovo == NULL) {
        printf("Errore allocazione Auto\n");
        return NULL; // invece di exit
    }
    nuovo->cilindrata = cc;
    nuovo->cavalli = cv;
    nuovo->peso = kg;
    nuovo->porte = porte;
    nuovo->chilometri = km;
    nuovo->anno = anno;
    nuovo->posti = posti;
    nuovo->prezzo = prezzo;

    strncpy(nuovo->modello, modello, sizeof(nuovo->modello)-1);
    nuovo->modello[sizeof(nuovo->modello)-1] = '\0';
    strncpy(nuovo->marca, marca, sizeof(nuovo->marca)-1);
    nuovo->marca[sizeof(nuovo->marca)-1] = '\0';
    strncpy(nuovo->colore, colore, sizeof(nuovo->colore)-1);
    nuovo->colore[sizeof(nuovo->colore)-1] = '\0';
    strncpy(nuovo->cambio, cambio, sizeof(nuovo->cambio)-1);
    nuovo->cambio[sizeof(nuovo->cambio)-1] = '\0';
    strncpy(nuovo->carburante, carburante, sizeof(nuovo->carburante)-1);
    nuovo->carburante[sizeof(nuovo->carburante)-1] = '\0';

    return nuovo;
}

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
           "Anno di immatricolazione: %d, \nChilomeetri: %d, \nCilindrata motore(cc): %d,\n"
           "Potenza(CV): %d,\nPeso(KG): %.2f,\n"
           "Tipo di carburante: %s,\nTipo di cambio: %s,\nColore carrozzeria: %s, \nPrezzo: %.2f \n\n",
           A->automobile->marca,
           A->automobile->modello,
           A->automobile->anno,
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


int main(){

    Albero A = NULL;
    int scelta = 0, ricerca = 0, km_MAX = 0, anno_MIN = 0, anno_MAX = 0;
    int cc=0, cv=0, porte=0, km=0, anno=0, posti=0;
    float kg = 0, prezzo = 0, prezzo_MIN = 0, prezzo_MAX = 0;
    char modello[30], marca[30], colore[30], cambio[30], carburante[30]; 
    char risposta;

    Auto a1 = crea_auto(1399, 90, 1000.0, 5, 68456, "Panda", "fiat", 2015, "Bianco", "Manuale", "Benzina", 4, 4000.0);
    Auto a2 = crea_auto(1900, 120, 1100.0, 5, 289000, "Golf", "vw", 2018, "Nero", "Manuale", "Diesel", 5, 8000.0);
    Auto a3 = crea_auto(1199, 69, 1000.0, 5, 221678, "Punto", "fiat", 2013, "Grigio", "manuale", "Benzina", 5, 2550.0);
    Auto a4 = crea_auto(1600, 204, 1265.0, 5, 6789, "I20 N", "hyundai", 2022, "Azzurro Performance", "Manuale", "Benzina", 5, 31000.0);
    Auto a5 = crea_auto(6200, 659, 1880.0, 3, 13229, "FF", "ferrari", 2014, "Rosso Imola", "Automatico", "Benzina", 2, 134990.0);
    Auto a6 = crea_auto(7000, 513, 1420.0, 3, 43655, "C6", "corvette", 2023, "Blu", "Automatico", "Benzina", 2, 89000.0);
    Auto a7 = crea_auto(1999, 179, 1829.0, 5, 139157, "Velar", "range rover", 2015, "Nero", "Automatico", "Benzina", 5, 30560.0);
    Auto a8 = crea_auto(2755, 177, 2600.0, 5, 195992, "Land Cruiser", "toyota", 2018, "Grigio", "Automatico", "Diesel", 5, 81250.0);
    Auto a9 = crea_auto(1984, 252, 2140.0, 5, 187944, "A7", "audi", 2020, "Grigio", "Automatico", "Benzina", 5, 39990.0);
    Auto a10 = crea_auto(1998, 245, 1775.0, 5, 14998, "Serie 4", "bmw", 2025, "Bianco", "Automatico", "Benzina", 5, 42890.0);

    Albero n1 = crea_nodo(a1);
    Albero n2 = crea_nodo(a2);
    Albero n3 = crea_nodo(a3);
    Albero n4 = crea_nodo(a4);
    Albero n5 = crea_nodo(a5);
    Albero n6 = crea_nodo(a6);
    Albero n7 = crea_nodo(a7);
    Albero n8 = crea_nodo(a8);
    Albero n9 = crea_nodo(a9);
    Albero n10 = crea_nodo(a10);

    inserisci_auto(&A, n1);
    inserisci_auto(&A, n2);
    inserisci_auto(&A, n3);
    inserisci_auto(&A, n4);
    inserisci_auto(&A, n5);
    inserisci_auto(&A, n6);
    inserisci_auto(&A, n7);
    inserisci_auto(&A, n8);
    inserisci_auto(&A, n9);
    inserisci_auto(&A, n10);

    do {
        printf("--- AUTOSALONE ---\n");
        printf("1. Inserisci nuova auto\n");
        printf("2. Visualizza tutte le auto\n");
        printf("3. Cerca auto\n");
        printf("4. Compra auto\n");
        printf("0. Esci\n");

        printf("Scelta: ");
        scanf("%d", &scelta);
        switch (scelta)
        {
            case 1:
                printf("Inserimento nuova auto:\n");

                getchar(); // pulisce buffer

                printf("Marca: ");
                fgets(marca, 30, stdin);
                marca[strcspn(marca, "\n")] = '\0'; // tolgo il \n messo da fgets 

                printf("Modello: ");
                fgets(modello, 30, stdin);
                modello[strcspn(modello, "\n")] = '\0';

                printf("Cilindrata (cc): ");
                scanf("%d", &cc);

                printf("Potenza (cv): ");
                scanf("%d", &cv);

                printf("Peso (kg): ");
                scanf("%f", &kg);

                getchar(); // pulisce buffer

                printf("Carburante: ");
                fgets(carburante, 30, stdin);
                carburante[strcspn(carburante, "\n")] = '\0';

                printf("Colore: ");
                fgets(colore, 30, stdin);
                colore[strcspn(colore, "\n")] = '\0';

                printf("Tipo di cambio: ");
                fgets(cambio, 30, stdin);
                cambio[strcspn(cambio, "\n")] = '\0';

                printf("Numero porte: ");
                scanf("%d", &porte);

                printf("Anno di immatricolazione: ");
                scanf("%d", &anno);

                printf("Numero posti: ");
                scanf("%d", &posti);

                printf("Chilometraggio: ");
                scanf("%d", &km);

                printf("Prezzo (euro): ");
                scanf("%f", &prezzo);

                Auto nuova = crea_auto(cc, cv, kg, porte, km, modello, marca, anno, colore, cambio, carburante, posti, prezzo);

                if(nuova!=NULL){
                    Albero nodo = crea_nodo(nuova);
                    inserisci_auto(&A, nodo);
                    printf("Auto inserita correttamente.\n");
                }

                stampa_albero_inorder(A); // stampo tutto verificare l'avvenuta aggiunta dell'auto

                break;

            case 2:
                
                stampa_albero_inorder(A);
                break;

            case 3: {
                int trovate = 0;

                printf("Inserisci il tipo di ricerca: \n");
                printf("1. per MARCA\n");
                printf("2. per CHILOMETRI\n");
                printf("3. per ANNO\n");
                printf("4. per PREZZO\n");
                scanf("%d", &ricerca);
                getchar(); // pulisce buffer dopo scanf

                switch(ricerca){

                    case 1: {
                        printf("Inserisci la marca da cercare: ");
                        fgets(marca, 30, stdin);
                        marca[strcspn(marca, "\n")] = '\0';

                        cerca_Auto_marca(A, marca, &trovate);
                        if (trovate == 0) {
                            printf("Nessuna auto trovata per la marca inserita.\n");
                        }
                        break;
                    }

                    case 2: {
                        printf("Inserisci i chilometri massimi di ricerca: ");
                        scanf("%d", &km_MAX);
                        

                        cerca_Auto_chilometri(A, km_MAX, &trovate);
                        if (trovate == 0) {
                            printf("Nessuna auto trovata con chilometri minori o uguali a %d.\n", km_MAX);
                        }
                        break;
                    }

                    case 3: {
                        printf("Inserisci l'anno minimo: ");
                        scanf("%d", &anno_MIN);
                        printf("Inserisci l'anno massimo: ");
                        scanf("%d", &anno_MAX);
                        

                        cerca_Auto_anno(A, anno_MIN, anno_MAX, &trovate);
                        if (trovate == 0) {
                            printf("Nessuna auto trovata nell'intervallo %d - %d.\n", anno_MIN, anno_MAX);
                        }
                        break;
                    }

                    case 4: {
                        printf("Inserisci il prezzo minimo: ");
                        scanf("%f", &prezzo_MIN);
                        printf("Inserisci il prezzo massimo: ");
                        scanf("%f", &prezzo_MAX);
                        

                        cerca_Auto_prezzo(A, prezzo_MIN, prezzo_MAX, &trovate);
                        if (trovate == 0) {
                            printf("Nessuna auto trovata nell'intervallo %d - %d.\n", prezzo_MIN, prezzo_MAX);
                        }
                        break;
                    }

                    default:
                        printf("Inserisci un numero valido per scegliere il tipo di ricerca (1-3).\n");
                        break;
                }
                break;
            }


            case 4:
                printf("Per comprare un'auto inserisci i dati della vettura di seguito: \n");
                printf("Marca: \n");

                getchar();

                fgets(marca, 30, stdin);
                marca[strcspn(marca, "\n")] = '\0';

                printf("Modello: \n");
                fgets(modello, 30, stdin);
                modello[strcspn(modello, "\n")] = '\0';

                printf("Anno: \n");
                scanf("%d", &anno);

                printf("Chilometri: \n");
                scanf("%d", &km);

                getchar();

                printf("Cambio: \n");
                fgets(cambio, 30, stdin);
                cambio[strcspn(cambio, "\n")] = '\0';

                printf("Carburante: \n");
                fgets(carburante, 30, stdin);
                carburante[strcspn(carburante, "\n")] = '\0';

                printf("Colore: \n");
                fgets(colore, 30, stdin);
                colore[strcspn(colore, "\n")] = '\0';

                printf("Sei sicuro di voler comprare questa auto? inserisci Y per si oppure N per no: \n");
                scanf(" %c", &risposta);

                risposta = tolower(risposta);
                if(risposta =='y'){
                    rimuovi_auto(&A, km, modello, marca, colore, carburante, anno, cambio);
                    printf("Hai effettuato l'acquisto della tua nuova vettura !!\n");
                }

                if(risposta == 'n'){
                    printf("Hai annullato correttamente l'acquisto\n");
                }

                break;

            case 0:
                
                break;
            
            default:
                printf("inserisci un numero per scegliere cosa eseguire da 0 a 5 !!\n");
                break;
        }

    } while (scelta != 0);


    dealloca_albero(&A);

    return 0;
}
