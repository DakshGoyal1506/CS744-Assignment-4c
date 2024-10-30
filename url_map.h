
#ifndef URL_MAP_H
#define URL_MAP_H

typedef struct
{
    const char *url;
    int index;
}url_map_entry_t;

typedef struct 
{
    url_map_entry_t *entries;
    int size;
}url_map_t;

void init_url_map(url_map_t *map);
void add_url(url_map_t *map, const char *url, int index);
int get_index(url_map_t *map, const char *url);
void free_url_map(url_map_t *map);


#endif