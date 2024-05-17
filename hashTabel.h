#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include <stdlib.h>
#include <stdbool.h>

#define Type int

typedef struct HashTable_t *HashTable;

typedef char *Key;

HashTable createHashTable(unsigned int size);

void insert(HashTable ht, Key key, Type value);

Type getValue(HashTable ht, Key key);

bool existsKey(HashTable ht, Key key);

void destroyHashTable(HashTable ht);

#endif // HASH_TABLE_H