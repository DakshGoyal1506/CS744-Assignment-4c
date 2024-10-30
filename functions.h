
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#define NUM_FUNCTIONS 7

typedef struct
{
    const char *url;
    int index;
}url_mapping_t;


static const url_mapping_t url_mappings[NUM_FUNCTIONS]=
{
    {"/", 0},
    {"/square", 1},
    {"/cube", 2},
    {"/helloworld", 3},
    {"/pingpong", 4},
    {"/arithmetic/prime", 5},
    {"/arithmetic/fibonacci", 6},
};


#endif