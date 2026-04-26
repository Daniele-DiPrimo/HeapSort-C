/*
*
*  Heap Sort Algorithm Implementation in C
*  Concetti Fondamentali: 
*  - Heap: Struttura dati ad albero binario. Per essere definita tale deve rispettare 4 proprietà. 
*  - Max-Heap: Heap in cui ogni nodo è maggiore o uguale ai suoi figli.
*  - Max-Heapify: Procedura che, dato un nodo i, assicura che il sottoalbero radicato in i sia un max-heap(confronto + eventuale switch). Per essere eseguito correttamente, i sottoalberi radicati nei nodi figli di i devono essere già in max-heap.
*  - Build-Max-Heap: Procedura che, dato un array A, costruisce un max-heap. Viene eseguita chiamando Max-Heapify su tutti i nodi non foglia a partire dall'ultimo nodo non foglia (n/2 - 1) fino alla radice.
*  - Heap-Sort: Algoritmo di ordinamento che utilizza un max-heap. Viene eseguito costruendo un max-heap dall'array da ordinare, quindi scambiando il primo elemento (il massimo) con l'ultimo elemento dell'heap (che viene inserito nell'array ordinato a partire dall'ultimo elemento), riducendo la dimensione dell'heap di 1. Infine, viene chiamato Max-Heapify sulla radice per ripristinare la proprietà del max-heap. Questo processo viene ripetuto fino a quando l'heap è vuoto.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

void MaxHeapify(int arr[], int n, int i, int heapSize);
void BuildMaxHeap(int arr[], int n);
void RandomicInizialize(int arr[], int n); 
void ManualInizialize(int arr[], int n); 
void SwitchValues(int arr[], int j, int k);
void HeapSort(int arr[], int n);

int main(void){

    int n, n_tmp, choice; 
    char term;


    printf("Benvenuto nell'implementazione dell'HeapSort in C!\n"); 

    printf("Quanti elementi sono presenti nell'array che vuoi ordinare? N:  "); 

    while (scanf("%d%c", &n_tmp, &term) != 2 || term != '\n') {
        printf("No! Solo interi puri. Riprova: ");
        // Pulisci il buffer fino alla fine della riga
        while (getchar() != '\n');
    }

    n = n_tmp + 1;
    int v[n]; 
    v[0] = -1;
    
    printf("\n* Premi 1 se vuoi riempire l'array con valori casuali (Range 0 - 1000).\n"); 
    printf("* Premi 2 se vuoi riempire l'array manualmente.\n");
    printf("* Premi qualsiasi altro numero per uscire dal programma.\n");
    printf("* L'ordinamento partira' in automatico!\n");
    printf("Choice: ");  
    scanf("%d", &choice);

    switch(choice){
        case 1:
            srand(time(NULL));
            RandomicInizialize(v, n); 
            break;

        case 2: 
            ManualInizialize(v, n);
            break;
        
        default:
            return 0;
            break; 
        
    }


    printf("\n\narray ordinato = [ ");
    for (int i=1; i < n; i++){
        printf("%d  ", v[i]);
    }
    printf("]\n\n");

}

void ManualInizialize(int arr[], int n){

    // --- INIZIO FASE DI RIEMPIMENTO DELL'ARRAY ---
    for (int i=1; i < n; i++){
        printf("\nValore di indice %d : ", i);
        scanf("%d", &arr[i]);
    }
    // --- FINE FASE DI RIEMPIMENTO DELL'ARRAY ---

    printf("\n");

    // STAMPA
    printf("array = [ ");
    for (int i=1; i < n; i++){
        printf("%d  ", arr[i]);
    }
    printf("]\n");

    // --- INIZIO ORDINAMENTO
    HeapSort(arr, n);
    // --- FINE ORDINAMENTO

}

void RandomicInizialize(int arr[], int n){

    // --- INIZIO FASE DI RIEMPIMENTO DELL'ARRAY ---
    for (int i = 1; i < n; i++) {
        arr[i] = rand() % 1001; 
    }
    // --- FINE FASE DI RIEMPIMENTO DELL'ARRAY ---
    
    printf("\n");

    // STAMPA

    printf("array = [ ");
    for (int i=1; i < n; i++){
        printf("%d  ", arr[i]);
    }
    printf("]\n");

    // --- INIZIO ORDINAMENTO
    HeapSort(arr, n);
    // --- FINE ORDINAMENTO

}

void SwitchValues(int arr[], int j, int k){

    int tmp; 
    tmp = arr[j];
    
    arr[j] = arr[k];
    arr[k] = tmp;

}

void MaxHeapify(int arr[], int n, int i, int heapSize){
    // L'obiettivo è ripristinare le proprietà di max-heap su un sottoalbero avente radice in i. Ricorsivamente si insegue il nodo i fino a quando non viene inserito alla giust posizione
    
    int l, r, largest; 

    l = i * 2;
    r = i * 2 + 1;
    largest = i; 

    /* STAMPA INFO MAX-HEAPIFY
    printf("\nMAX-HEAPIFY SUL SOTTO ALBERO: radice %d, left %d, right %d", i, l, r);
    */

    //Controlliamo che l e r abbiano indice all'interno della struttura heap, poi cerchiamo il valore più grande tra padre e figli, nel caso in cui uno dei figli era più grande scambiamo i valori e chiamiamo ricorsivamente la f
    if(l <= heapSize && arr[l] > arr[i]){
        largest = l;
    }
       
    if(r <= heapSize && arr[r] > arr[largest]){
        largest = r; 
    }

    if(largest != i){
        SwitchValues(arr, i, largest);
        MaxHeapify(arr, n, largest, heapSize);
    }
   
}

void BuildMaxHeap(int arr[], int n){
    // l'obiettivo è costruire una struttura max-heap a partire dall'array dato. 
    // Il build-max-heap utilizza il Max-Heapify a partire dall'elemento di indice i = n/2 (arrotondato per difetto)
    int heapSize = n-1; 
    
    for(int i = ((n-1)/2) ; i >= 1; i--){
        MaxHeapify(arr, n, i, heapSize);
    }
    
    printf("\narray BUILD-MAX-HEAP = [ ");
    for (int i=1; i < n; i++){
        printf("%d  ", arr[i]);
    }
    printf("]");
    
}

void HeapSort(int arr[], int n){

    int heapSize = n-1;

    // Costruisco il MAX-HEAP
    BuildMaxHeap(arr, n);

    // Faccio partire l'ordinamento sul MAX-HEAP
    for(int i = n-1; i >= 2; i--){
        SwitchValues(arr, 1, i); 
    
        heapSize --;
        MaxHeapify(arr, n, 1, heapSize);
    }

}
