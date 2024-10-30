#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "functions.h"

int get_query_param(const char *query_string, const char *param, char *value, int value_len)
{
    if(query_string == NULL || param == NULL || value == NULL || value_len <= 0)
    {
        return 0;
    }

    const char *start = strstr(query_string, param);
    if(start == NULL)
    {
        return 0;
    }

    start = start + strlen(param) + 1;
    const char *end = strchr(start, '&');

    if(end == NULL)
    {
        end = start + strlen(start);
    }

    int len = end - start;

    if(len >= value_len)
    {
        len = value_len - 1;
    }

    strncpy(value, start, len);
    value[len] = '\0';
    return 1;

}


const char* index_page(const char *query_string)
{
    if(get_query_param(query_string, NULL, NULL,0))
    {
        ;
    }

    return "This is the index page \n";
}

const char* square(const char *query_string)
{
    static char result[128];
    char number_str[12];
    int number = 1;

    if(get_query_param(query_string, "num", number_str, sizeof(number_str)))
    {
        number = atoi(number_str);
    }

    int square = number * number;
    snprintf(result, sizeof(result), "Square of %d is %d \n", number, square);
    return result;
}

const char* cube(const char *query_string)
{
    static char result[128];
    char number_str[12];
    int number = 1;

    if(get_query_param(query_string, "num", number_str, sizeof(number_str)))
    {
        number = atoi(number_str);
    }

    int cube = number * number * number;
    snprintf(result, sizeof(result), "Square of %d is %d \n", number, cube);
    return result;
}

const char* hello(const char *query_string)
{
    if(get_query_param(query_string, NULL, NULL, 0))
    {
        ;
    }

    return "Hello World \n";
}

const char* prime(const char *query_string)
{
    char number_str[12];
    int number = 1;

    if(get_query_param(query_string, NULL, number_str, sizeof(number_str)))
    {
        number = atoi(number_str);
    }
    return "This is the prime page \n";
}

const char* pingpong(const char *query_string)
{
    if(get_query_param(query_string, NULL, NULL, 0))
    {
        ;
    }

    return "This is the pingpong page \n";
}