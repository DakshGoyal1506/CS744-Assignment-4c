
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define NUM_FUNCTIONS 6

typedef struct
{
    const char *url;
    int index;
}url_mapping_t;


static const url_mapping_t url_mappings[NUM_FUNCTIONS]=
{
    {"/", 0},
    {"/arithmetic/square", 1},
    {"/arithmetic/cube", 2},
    {"/hello", 3},
    {"/prime", 4},
    {"/pingpong", 5},

};


#endif