#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
                            printf("Nessuna auto trovata nell'intervallo %.2f - %.2f.\n", prezzo_MIN, prezzo_MAX);
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
