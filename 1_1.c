#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int *arr = NULL;
int n = 0;

void initArray(int size) {
    n = size;
    arr = (int*)malloc(n * sizeof(int));
    srand(time(NULL));
    for(int i=0; i<n; i++) arr[i] = rand() % 1000;
    printf("Tabloul a fost inițializat cu %d elemente.\n", n);
}

void printArray() {
    if(arr == NULL) {
        printf("Tabloul nu este inițializat.\n");
        return;
    }
    for(int i=0; i<n; i++) printf("%d ", arr[i]);
    printf("\n");
}

void freeArray() {
    if(arr != NULL) {
        free(arr);
        arr = NULL;
        n = 0;
        printf("Memoria a fost eliberată.\n");
    } else {
        printf("Nu există tablou de eliberat.\n");
    }
}

// Bubble Sort
void bubbleSort() {
    if(arr == NULL) {
        printf("Tabloul nu este inițializat.\n");
        return;
    }

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Bubble sort executat în %.9f secunde.\n", elapsed);
}

void heapify(int a[], int n, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < n && a[left] > a[largest]) largest = left;
    if(right < n && a[right] > a[largest]) largest = right;

    if(largest != i) {
        int tmp = a[i];
        a[i] = a[largest];
        a[largest] = tmp;
        heapify(a, n, largest);
    }
}

// Heap Sort
void heapSort() {
    if(arr == NULL) {
        printf("Tabloul nu este inițializat.\n");
        return;
    }

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for(int i = n/2 - 1; i >= 0; i--) heapify(arr, n, i);
    for(int i = n-1; i > 0; i--) {
        int tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        heapify(arr, i, 0);
    }

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Heap sort executat în %.9f secunde.\n", elapsed);
}

int main() {
    int opt, size;
    do {
        printf("\n--- MENIU ---\n");
        printf("1. Inițializare tablou\n");
        printf("2. Afișare tablou\n");
        printf("3. Eliberare memorie\n");
        printf("4. Sortare Bubble Sort\n");
        printf("5. Sortare Heap Sort\n");
        printf("0. Ieșire\n");
        printf("Alege opțiunea: ");
        scanf("%d", &opt);

        switch(opt) {
            case 1:
                printf("Introdu dimensiunea tabloului: ");
                scanf("%d", &size);
                initArray(size);
                break;
            case 2:
                printArray();
                break;
            case 3:
                freeArray();
                break;
            case 4:
                bubbleSort();
                break;
            case 5:
                heapSort();
                break;
            case 0:
                printf("Program terminat.\n");
                break;
        }
    } while(opt != 0);

    return 0;
}
