#include "minitalk.h"

void ft_reset_client(t_client *client)
{
    client->nbites = 0;
    client->base = 1;
    client->offset = 0;
    client->message[0] = 0;
}