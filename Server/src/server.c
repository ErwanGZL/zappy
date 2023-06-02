#include "server.h"

server_t *server_new(int argc, char *argv[])
{
    server_t *server = calloc(1, sizeof(server_t));
    server->options = options_new(argc, argv);
    server->netctl = netctl_new(server->options->port);
    server->game = init_game(server->options);
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
    for (list_t head = server->netctl->clients; head != NULL; head = head->next)
    {
        list_dump(head, &socket_dump);
        if (FD_ISSET(((socket_t *)head->value)->fd, &readfds))
        {
            char buffer[1024] = {0};
            ssize_t rbytes = recv(((socket_t *)head->value)->fd, buffer, 1024, 0);
            if (rbytes == 0)
            {
                printf("Client disconnected\n");
                netctl_disconnect(server->netctl, ((socket_t *)head->value)->fd);
                list_dump(head, &socket_dump);
            }
            else
            {
                printf("Received %ld bytes\n", rbytes);
                printf("Received: %s\n", buffer);
            }
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
    char buffer[1024] = {0};
    recv(fd, buffer, 1024, 0);
    printf("Handshake done\n");
    printf("Client is on team %s\n", buffer);
    for (list_t head = server->game->teams; head != NULL; head = head->next)
    {
        team_t *team = (team_t *)head->value;
        if (strncmp(team->name, buffer, strlen(team->name)) == 0 && team->nb_players < team->max_players)
        {
            dprintf(fd, "%d\n"
                        "%d %d\n",
                    team->max_players - team->nb_players,
                    server->options->width,
                    server->options->height);
            return;
        }
    }
    printf("Team not found\n");
    dprintf(fd, "0\n"
                "0 0\n");
    netctl_disconnect(server->netctl, fd);
}

int server_run(server_t *server)
{
    while (1)
    {
        server_select(server);
    }

    return 0;
}
