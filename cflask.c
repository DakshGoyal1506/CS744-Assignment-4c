#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "civetweb.h"
#include "functionslist.h"
#include "functions.h"
#include "url_map.h"

url_map_t map;

int request_handler(struct mg_connection *conn, void *cbdata)
{
    const struct mg_request_info *req_info = mg_get_request_info(conn);
    const char *request_url = req_info -> local_uri;
    const char *query_string = req_info -> query_string;

    printf("Request URL: %s\n", request_url);

    // int function_index = -1;
    // for(int i = 0; i < NUM_FUNCTIONS; i++)
    // {
    //     if(strcmp(request_url, url_mappings[i].url) == 0)
    //     {
    //         function_index = url_mappings[i].index;
    //         break;
    //     }
    // }

    int function_index = get_index(&map, request_url);

    if(function_index != -1)
    {
        const char *response = functions_list[function_index](query_string);

        mg_printf(conn,
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: text/html\r\n"
                    "Content-Length: %zu\r\n"
                    "\r\n"
                    "%s",
                    strlen(response), response);

        // mg_printf(conn, "HTTP/1.1 200 OK\r\n Content-Type: text/html\r\n Content-Length: %zu\r\n\r\n %s", strlen(response), response);
        
        return 1;
    }
    else
    {
        mg_printf(conn,
                    "HTTP/1.1 404 Not Found\r\n"
                    "Content-Length: 0\r\n"
                    "\r\n");
        
        return 1;
    }
}

int main(int argc, char* argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s <listening_port> <num_threads>\n", argv[0]);
        return 1;
    }

    const char *port = argv[1];
    const char *num_threads = argv[2];
    init_url_map(&map);

    for(int i = 0; i < NUM_FUNCTIONS; i++)
    {
        add_url(&map, url_mappings[i].url, url_mappings[i].index);
    }

    const char *options[] = {
        "listening_ports", port,
        "num_threads", num_threads,
        NULL
    };

    struct mg_callbacks callbacks;
    memset(&callbacks, 0, sizeof(callbacks));

    struct mg_context *ctx = mg_start(&callbacks, NULL, options);

    if(ctx == NULL)
    {
        printf("Failed to start the server\n");
        return 1;
    }

    mg_set_request_handler(ctx, "**", request_handler, NULL);

    printf("Server started on port %s with %s threads, Press enter to stop\n", port, num_threads);
    getchar();

    mg_stop(ctx);
    free_url_map(&map);
    printf("Server stopped\n");

    return EXIT_SUCCESS;

}