Autosalone – Progetto in C

Questo progetto è una applicazione da terminale scritta in linguaggio C che simula la gestione di un autosalone.
È pensato come esercizio completo su strutture dati dinamiche, alberi binari di ricerca, gestione della memoria e interazione con l’utente tramite menu testuale.

L’obiettivo è dimostrare competenze pratiche di programmazione in C, tipiche di un contesto universitario ma già orientate a una logica applicativa reale.

Funzionalità principali
L’applicazione permette di:

-1 Inserire nuove auto nel sistema
-2 Visualizzare tutte le auto disponibili (visita in-order dell’albero)

-3 Cercare auto tramite diversi criteri:
- Marca
- Chilometraggio massimo
- Intervallo di anni
- Intervallo di prezzo
- Comprare un’auto (rimozione dall’albero)

-4 Gestire correttamente la memoria dinamica (malloc / free)

Le auto sono memorizzate in un albero binario di ricerca ordinato per chilometraggio.

Struttura dei dati:

Ogni auto è rappresentata da una struttura contenente:

-> Marca e modello
-> Anno di immatricolazione
-> Chilometri
-> Cilindrata, cavalli, peso
-> Carburante, cambio, colore
-> Numero di porte e posti
-> Prezzo

L’albero binario permette inserimenti, ricerche e cancellazioni efficienti.

Requisiti:

-> Compilatore C (consigliato: gcc)
-> Sistema operativo Windows, Linux o macOS
-> Terminale / PowerShell

Compilazione ed esecuzione:

Aprire il terminale nella cartella contenente il file .c e digitare:

Su Windows (PowerShell):

gcc nome_file.c -o autosalone


.\autosalone

Utilizzo del programma, All’avvio viene mostrato un menu testuale:

--- AUTOSALONE ---
1. Inserisci nuova auto
2. Visualizza tutte le auto
3. Cerca auto
4. Compra auto
0. Esci

Questo progetto è stato realizzato a scopo didattico e dimostrativo, è pensato come portfolio tecnico per aziende e recruiter interessati a valutare capacità di problem solving, logica e gestione delle strutture dati.