#include <assert.h>
#include "./hashTabel.h"
#include "./utilities.h"

// -------------------------

typedef struct NodeEntry_t
{
    Key key;
    Type value;
    struct NodeEntry_t *next;
} NodeEntry;

typedef struct Entry_t
{
    NodeEntry *valuesEntry;
} Entry;

typedef struct HashTable_t
{
    unsigned int size;
    Entry *entrys;
} HashTable_t;

// -------------------------

static Key createKey(Key key)
{
    if (key == NULL)
        return NULL;

    Key k = (Key)malloc(strlen(key) + 1);
    if (k == NULL)
        return NULL;

    strcpy(k, key);

    ASSERT(k != NULL, "Memory allocation failed.");
    ASSERT(strcmp(k, key) == 0, "Key not set correctly.");
    return k;
}

static NodeEntry *createNodeEntry(Key key, Type value)
{
    NodeEntry *ne = (NodeEntry *)malloc(sizeof(NodeEntry));
    if (ne == NULL)
        return NULL;

    ne->key = createKey(key);
    ne->value = value;
    ne->next = NULL;

    ASSERT(ne != NULL, "Memory allocation failed.");
    return ne;
}

static unsigned int hash(Key key, unsigned int size)
{
    ASSERT(key != NULL, "Key is NULL.");

    unsigned int hash = 0;
    for (unsigned int i = 0; i < strlen(key); i++)
        hash = (hash * 31) + key[i];

    hash = hash % size;

    ASSERT(hash < size, "Hash out of bounds.")
    return hash;
}

// -------------------------

HashTable createHashTable(unsigned int size)
{

    // Allocate memory for the hash table
    HashTable ht = (HashTable)malloc(sizeof(HashTable_t));
    if (ht == NULL)
        return NULL;

    // Allocate memory for the values
    ht->entrys = (Entry *)malloc(size * sizeof(Entry));
    if (ht->entrys == NULL)
    {
        free(ht);
        return NULL;
    }
    // Initialize all keys to NULL
    for (unsigned int i = 0; i < size; i++)
        ht->entrys[i].valuesEntry = NULL;

    ht->size = size;

    ASSERT(ht != NULL, "Memory allocation failed in createHashTable().");
    ASSERT(ht->entrys != NULL, "Memory allocation failed in createHashTable().");
    return ht;
}

void insert(HashTable ht, Key key, Type value)
{
    ASSERT(ht != NULL, "HashTable is NULL int insert().");
    ASSERT(key != NULL, "Key is NULL in insert().");

    unsigned int index = hash(key, ht->size);

    // If the key already exists, update the value
    NodeEntry *current = ht->entrys[index].valuesEntry;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            current->value = value;
            return;
        }

        if (current->next == NULL)
            break;

        current = current->next;
    }

    // If the key does not exist, create a new entry
    NodeEntry *newEntry = createNodeEntry(key, value);

    if (ht->entrys[index].valuesEntry == NULL)
    {
        ht->entrys[index].valuesEntry = newEntry;
    }
    else
    {
        current->next = newEntry;
    }
}

Type getValue(HashTable ht, Key key)
{
    ASSERT(ht != NULL, "HashTable is NULL in getValue().");
    ASSERT(key != NULL, "Key is NULL in getValue().");

    unsigned int index = hash(key, ht->size);

    NodeEntry *current = ht->entrys[index].valuesEntry;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
            return current->value;

        current = current->next;
    }

    return 0;
}

bool existsKey(HashTable ht, Key key)
{
    ASSERT(ht != NULL, "HashTable is NULL in existsKey().");
    ASSERT(key != NULL, "Key is NULL in existsKey().");

    unsigned int index = hash(key, ht->size);

    NodeEntry *current = ht->entrys[index].valuesEntry;

    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
            return true;

        current = current->next;
    }

    return false;
}

void destroyHashTable(HashTable ht)
{
    ASSERT(ht != NULL, "HashTable is NULL in destroyHashTable().");

    for (unsigned int i = 0; i < ht->size; i++)
    {
        NodeEntry *current = ht->entrys[i].valuesEntry;
        NodeEntry *next = NULL;

        while (current != NULL)
        {
            next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }

    free(ht->entrys);
    free(ht);
}