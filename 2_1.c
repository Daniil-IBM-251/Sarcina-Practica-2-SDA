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
    for(int i=0; i<n; i++) arr[i] = rand() % (n*10);
    printf("Tabloul a fost inițializat cu %d elemente.\n", n);
}

void printArray() {
    if(arr == NULL) {
        printf("Tabloul nu este inițializat.\n");
        return;
    }
    for(int i=0; i<n; i++) {
        printf("%d ", arr[i]);
    }
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

void linearSearchTest() {
    if(arr == NULL) {
        printf("Tabloul nu este inițializat.\n");
        return;
    }

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for(int i=0; i<10000; i++) {
        int key = rand() % (n*10);
        int found = -1;
        for(int j=0; j<n; j++) {
            if(arr[j] == key) {
                found = j;
                break;
            }
        }
    }

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Linear Search: 10000 căutări în tabloul cu %d elemente au durat %.6f secunde.\n", n, elapsed);
}

void binarySearchTest() {
    if(arr == NULL) {
        printf("Tabloul nu este inițializat.\n");
        return;
    }

     for(int i=0; i<n-1; i++) {
        for(int j=0; j<n-i-1; j++) {
            if(arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }

    LARGE_INTEGER start, end, freq;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);

    for(int i=0; i<10000; i++) {
        int key = rand() % (n*10);
        int left = 0, right = n-1, found = -1;
        while(left <= right) {
            int mid = (left + right) / 2;
            if(arr[mid] == key) { found = mid; break; }
            if(arr[mid] < key) left = mid + 1;
            else right = mid - 1;
        }
    }

    QueryPerformanceCounter(&end);
    double elapsed = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart;
    printf("Binary Search: 10000 căutări în tabloul cu %d elemente au durat %.6f secunde.\n", n, elapsed);
}

int main() {
    int opt, size;
    do {
        printf("\n--- MENIU ---\n");
        printf("1. Inițializare tablou\n");
        printf("2. Afișare tablou\n");
        printf("3. Eliberare memorie\n");
        printf("4. Linear Search\n");
        printf("5. Binary Search\n");
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
                linearSearchTest();
                break;
            case 5:
                binarySearchTest();
                break;
            case 0:
                printf("Program terminat.\n");
                break;
        }
    } while(opt != 0);

    return 0;
}
