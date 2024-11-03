#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url_map.h"

static unsigned int hash_function(const char *str) 
{
    unsigned int hash = 0;
    int count = 0;
    while (*str && count < 10)
    {
        hash = (hash * 13) + (unsigned char)(*str++);
        count++;
    }
    return hash % HASH_MAP_SIZE;
}

void init_url_map(url_map_t *map) 
{
    for (int i = 0; i < HASH_MAP_SIZE; i++) 
    {
        map->buckets[i] = NULL;
    }
}

void add_url(url_map_t *map, const char *url, int index) 
{
    unsigned int bucket = hash_function(url);

    url_map_entry_t *new_entry = malloc(sizeof(url_map_entry_t));
    if (new_entry == NULL) 
    {
        perror("Failed to allocate memory for new URL map entry");
        exit(EXIT_FAILURE);
    }
    new_entry->url = url;
    new_entry->index = index;
    new_entry->next = NULL;

    if (map->buckets[bucket] == NULL) 
    {
        map->buckets[bucket] = new_entry;
    } 
    else 
    {
        new_entry->next = map->buckets[bucket];
        map->buckets[bucket] = new_entry;
    }
}

int get_index(url_map_t *map, const char *url) 
{
    unsigned int bucket = hash_function(url);
    url_map_entry_t *entry = map->buckets[bucket];

    while (entry != NULL) 
    {
        if (strcmp(entry->url, url) == 0) {
            return entry->index;
        }
        entry = entry->next;
    }

    return -1;
}

void free_url_map(url_map_t *map) 
{
    for (int i = 0; i < HASH_MAP_SIZE; i++) 
    {
        url_map_entry_t *entry = map->buckets[i];
        while (entry != NULL) {
            url_map_entry_t *temp = entry;
            entry = entry->next;
            free(temp);
        }
        map->buckets[i] = NULL;
    }
}