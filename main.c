#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./hashTabel.h"

#define ht(key) getValue(ht, key)

int main()
{
    // This file is only for testing the hash table.
    HashTable ht = createHashTable(20);

    insert(ht, "tomas", 1);
    insert(ht, "sofia", 2);
    insert(ht, "maria", 3);
    insert(ht, "juan", 5);
    insert(ht, "ramiro", 7);

    printf("Number of 'tomas': %d\n", ht("tomas"));
    printf("Number of 'sofia': %d\n", ht("sofia"));
    printf("Number of 'maria: %d\n", ht("maria"));
    printf("Number of 'juan: %d\n", ht("juan"));
    printf("Number of 'ramiro: %d\n", ht("ramiro"));

    destroyHashTable(ht);
}