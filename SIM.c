
/*
    Solution TP systemes d'exploitation fait par Imed Boumalek de groupe 3
    Tout le code est le mien sauf si indiqué autrement
    Tous les autres commentaires sont en anglais car je me sont plus à l'aise avec l'anglais
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

struct ram_type
{
    int end;
    bool empty;
    int size;
};

typedef struct ram_type ram;

// functions for quicksort, source: geeksforgeeks.org, edited//

// A utility function to swap two elements
void swap(ram *a, ram *b)
{
    ram t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(ram arr[], int low, int high)
{
    int pivot = arr[high].end; // pivot
    int i = (low - 1);         // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j].end < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(ram arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}
//end of quicksort

// function to generate and sort an array (ram) of X length devided to random sized sections
void genRam(ram tab[], int sections, int space)
{
    int i = 0;
    time_t t;
    srand((unsigned)time(&t));
    for (i = 0; i < sections; i++)
    { //generates a random number between 0 and space
        tab[i].end = rand() % (space - 1);
        tab[i].empty = rand() & 1;
    }
    quickSort(tab, 0, sections - 1);
    tab[0].size = tab[0].end;
    for (i = 1; i < sections; i++)
    {
        tab[i].size = tab[i].end - tab[i - 1].end;
    }
}

void firstFit(int job_size, ram tab[], int sections)
{
    int i = 0;
    while (i < sections && (job_size > tab[i].size || !tab[i].empty))
    {
        i++;
    }
    if (i == sections)
    {
        printf("memoire pleine\n");
    }
    else
    {
        tab[i].empty = false;
        printf("partition numero %d de taille %d a ete allouee pour le job de taille %d\n", i, tab[i].size, job_size);
    }
}

void bestFit(int job_size, ram tab[], int sections)
{
    int min = tab[0].size, min_index = 0;
    for (int i = 1; i < sections; i++)
    {
        if (tab[i].empty && tab[i].size < min)
        {
            min_index = i;
            min = tab[i].size;
        }
    }
    tab[min_index].empty = false;
    printf("partition numero %d de taille %d a ete allouee pour le job de taille %d\n", min_index, tab[min_index].size, job_size);
}
void worstFit(int job_size, ram tab[], int sections)
{
    int max = tab[0].size, max_index = 0;
    for (int i = 1; i < sections; i++)
    {
        if (tab[i].empty && tab[i].size > max)
        {
            max_index = i;
            max = tab[i].size;
        }
    }
    tab[max_index].empty = false;
    printf("partition numero %d de taille %d a ete allouee pour le job de taille %d\n", max_index, tab[max_index].size, job_size);
}

int main()
{
    ram *tab;
    genRam(tab, 10, 1000);

    printf("partitionement de la ram...\n");
    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            printf("partition %d est de l'adresse %d jusqu'a l'adresse  %d || taille: %d Mo || vide: %s \n", i, 0, tab[i].end, tab[i].size, tab[i].empty ? "true" : "false");
            continue;
        }

        printf("partition %d est de l'adresse %d jusqu'a l'adresse  %d || taille: %d Mo || vide: %s \n", i, tab[i - 1].end, tab[i].end, tab[i].size, tab[i].empty ? "true" : "false");
    }
    printf("\n\n selectionnez la politique d'allocation: 1- first fit, 2- best fit, 3- worst fit \n");
    int c;
    scanf("%d", &c);
    switch (c)
    {
    case 1:
        firstFit(100, tab, 10);
        printf("\n\n");
        break;
    case 2:
        bestFit(100, tab, 10);
        printf("\n\n");
        break;
    case 3:
        worstFit(100, tab, 10);
        printf("\n\n");
        break;

    default:
        break;
    }

    for (int i = 0; i < 10; i++)
    {
        if (i == 0)
        {
            printf("partition %d est de l'adresse %d jusqu'a l'adresse  %d || taille: %d Mo || vide: %s \n", i, 0, tab[i].end, tab[i].size, tab[i].empty ? "true" : "false");
            continue;
        }

        printf("partition %d est de l'adresse %d jusqu'a l'adresse  %d || taille: %d Mo || vide: %s \n", i, tab[i - 1].end, tab[i].end, tab[i].size, tab[i].empty ? "true" : "false");
    }
    system("pause");
    return 0;
}
