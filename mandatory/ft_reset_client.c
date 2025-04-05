/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reset_client.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:33:27 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:33:28 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

void ft_reset_client(t_client *client)
{
    client->nbites = 0;
    client->base = 1;
    client->offset = 0;
    client->message[0] = 0;
}