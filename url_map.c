#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "url_map.h"

void init_url_map(url_map_t *map)
{
    map -> entries = NULL;
    map -> size = 0;
}


void add_url(url_map_t *map, const char *url, int index)
{
    map -> entries = realloc(map -> entries, (map -> size + 1) * sizeof(url_map_entry_t));
    map -> entries[map -> size].url = url;
    map -> entries[map -> size].index = index;
    map -> size = map -> size + 1;
}


int get_index(url_map_t *map, const char *url)
{
    for(int i = 0; i < map -> size; i++)
    {
        if(strcmp(url, map -> entries[i].url) == 0)
        {
            return map -> entries[i].index;
        }
    }

    return -1;
}


void free_url_map(url_map_t *map)
{
    free(map -> entries);
    map -> entries = NULL;
    map -> size = 0;
}