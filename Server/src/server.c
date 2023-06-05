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
    fd_set readfds = server->netctl->watched_fd;
    int activity = select(FD_SETSIZE, &readfds, NULL, NULL, NULL);
    printf("Activity: %d\n", activity);
    if (FD_ISSET(server->netctl->entrypoint.fd, &readfds))
    {
        printf("New connection\n");
        int fd = netctl_accept(server->netctl);
        server_handshake(server, fd);
    }
    for (list_t head = server->netctl->clients; head != NULL;)
    {
        if (FD_ISSET(((socket_t *)head->value)->fd, &readfds))
        {
            char buffer[1024] = {0};
            ssize_t rbytes = recv(((socket_t *)head->value)->fd, buffer, 1024, 0);
            if (rbytes == 0)
            {
                printf("Client disconnected\n");
                close(((socket_t *)head->value)->fd);
                FD_CLR(((socket_t *)head->value)->fd, &server->netctl->watched_fd);
                list_del_elem_at_front(&head);
                continue;
            }
            else
            {
                printf("Received %ld bytes\n", rbytes);
                printf("Received: %s\n", buffer);
            }
        }
        head = head->next;
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
    char buffer[1024] = {0};
    recv(fd, buffer, 1024, 0);
    printf("Handshake done\n");
    printf("Client is on team %s\n", buffer);
    int clients_left = server->options->clientsNb - list_get_size(server->netctl->clients);
    dprintf(fd, "%d\n" "%d %d\n", clients_left, server->options->width, server->options->height);
    if (clients_left == 0)
    {
        printf("No places left\n");
        close(fd);
    }
}

int server_run(server_t *server)
{
    while (1)
    {
        server_select(server);
    }

    return 0;
}
