/*
** EPITECH PROJECT, 2023
** B-YEP-400-MAR-4-1-zappy-erwan.gonzales
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "zserv.h"
#include <string.h>

int main(int argc, char *argv[])
{
    zserv_opt_t options = {0};

    static struct option long_options[] = {
        {"port", required_argument, 0, 'p'},
        {"width", required_argument, 0, 'x'},
        {"height", required_argument, 0, 'y'},
        {"name", required_argument, 0, 'n'},
        {"clientsNb", required_argument, 0, 'c'},
        {"freq", required_argument, 0, 'f'},
        {0, 0, 0, 0}};

    int option_index = 0;
    int opt = 0;
    while ((opt = getopt_long(argc, argv, "p:x:y:n:c:f:", long_options, &option_index)) != -1)
    {
        switch (opt)
        {
        case 'p':
            options.port = atoi(optarg);
            break;
        case 'x':
            options.width = atoi(optarg);
            break;
        case 'y':
            options.height = atoi(optarg);
            break;
        case 'n':
            {
                char *tok = tok = strtok(optarg, ",");
                while (tok != NULL)
                {
                    list_add_elem_at_back(&options.teams, strdup(tok));
                    tok = strtok(NULL, ",");
                }
            }
            break;
        case 'c':
            options.clientsNb = atoi(optarg);
            break;
        case 'f':
            options.freq = atof(optarg);
            break;
        case '?':
            exit(84);
        }
    }

    if (!options.port ||
        !options.width ||
        !options.height ||
        !options.clientsNb ||
        !options.freq ||
        list_is_empty(options.teams))
    {
        fprintf(stderr, "Error: missing arguments\n");
        exit(84);
    }

    printf("port: %d\n", options.port);
    printf("width: %d\n", options.width);
    printf("height: %d\n", options.height);
    printf("clientsNb: %d\n", options.clientsNb);
    printf("freq: %f\n", options.freq);
    for (list_t head = options.teams; head != NULL; head = head->next)
        printf("team: %s\n", (char *)head->value);
    for (list_t head = options.teams; head != NULL; head = head->next)
        free(head->value);
    list_clear(&options.teams);
    return 0;
}
