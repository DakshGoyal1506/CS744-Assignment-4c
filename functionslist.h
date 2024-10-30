
#ifndef FUNCTIONSLIST_H
#define FUNCTIONSLIST_H

#include "functions.h"

typedef const char *(*func_ptr_t)();

const char* index_page(const char *query_string);
const char* square(const char *query_string);
const char* cube(const char *query_string);
const char* hello(const char *query_string);
const char* prime(const char *query_string);
const char* pingpong(const char *query_string);

static const func_ptr_t functions_list[NUM_FUNCTIONS] = {
    index_page,
    square,
    cube,
    hello,
    prime,
    pingpong
};

#endif