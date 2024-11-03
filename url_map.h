#ifndef URL_MAP_H
#define URL_MAP_H

#define HASH_MAP_SIZE 17 

typedef struct url_map_entry 
{
    const char *url;
    int index;
    struct url_map_entry *next;
} url_map_entry_t;

typedef struct 
{
    url_map_entry_t *buckets[HASH_MAP_SIZE];
} url_map_t;

void init_url_map(url_map_t *map);
void add_url(url_map_t *map, const char *url, int index);
int get_index(url_map_t *map, const char *url);
void free_url_map(url_map_t *map);

#endif