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
    // if(get_query_param(query_string, NULL, NULL,0))
    // {
    //     ;
    // }

    // return "This is the index page \n";
    return "Hello World \n";
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

const char* helloworld(const char *query_string)
{
    static char result[150];
    char name[100];

    if(get_query_param(query_string, "str", name, sizeof(name)))
    {
        snprintf(result, sizeof(result), "Hello, %s \n", name);
        return result;
    }

    return "Hello\n";
}

const char* prime(const char *query_string)
{
    char number_str[12];
    int number = 1;

    if(get_query_param(query_string, "num", number_str, sizeof(number_str)))
    {
        number = atoi(number_str);
    }

    if(number <= 1)
    {
        return "False \n";
    }
    else
    {
        for(int i = 2; i <= sqrt(number); i++)
        {
            if(number % i == 0)
            {
                return "False \n";
            }
        }
    }

    return "True \n";
    // return "This is the prime page \n";
}

const char* pingpong(const char *query_string)
{
    static char result[128];
    char str[125];

    if(get_query_param(query_string, "str", str, sizeof(str)))
    {
        snprintf(result, sizeof(result), "%s \n", str);
        return result;
    }

    // return "This is the pingpong page \n";
    return "PingPong \n";
}

const char* fibonnaci(const char *query_string)
{
    static char result[128];
    char number_str[12];
    int number = 1;

    if(get_query_param(query_string, /*"num"*/ "k", number_str, sizeof(number_str)))
    {
        number = atoi(number_str);
    }

    long long int a = 0, b = 1, c;

    if(number == 1)
    {
        snprintf(result, sizeof(result), "%lld \n", a);
        printf("Fibonacci of %d is %lld \n", number, a);
        return result;
    }
    if(number == 2)
    {
        snprintf(result, sizeof(result), "%lld \n", b);
        return result;
    }

    for(int i = 3; i <= number; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }

    snprintf(result, sizeof(result), "%lld \n", b);
    return result;
}