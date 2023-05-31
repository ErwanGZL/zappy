#include "server.h"

server_t *server_new(int argc, char *argv[])
{
    server_t *server = calloc(1, sizeof(server_t));
    server->options = options_new(argc, argv);
    server->netctl = netctl_new(server->options->port);
    return server;
}

void server_select(server_t *server)
{
    fd_set readfds = server->netctl->readfds;
    select(0, &readfds, NULL, NULL, NULL);
    if (FD_ISSET(server->netctl->entrypoint.fd, &readfds))
    {
        int fd = netctl_accept(server->netctl);
        printf("New connection\n");
        server_handshake(server, fd);
    }
    for (list_t head = server->netctl->clients; head != NULL; head = head->next)
    {
        if (FD_ISSET(((socket_t *)head->value)->fd, &readfds))
        {
            printf("New message\n");
        }
    }
}

void server_destroy(server_t *server)
{
    options_destroy(server->options);
    netctl_destroy(server->netctl);
    free(server);
}

void server_handshake(server_t *server, int fd)
{
    send(fd, "WELCOME\n", 8, 0);
    char buffer[1024];
    recv(fd, NULL, 0, 0);
    printf("Handshake done\n");
    printf("Client is on team %s\n", buffer);
}
