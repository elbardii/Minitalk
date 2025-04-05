/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_client_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:28:38 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:29:02 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	show_client_message(t_client *client)
{
	if (client->message[client->offset] == '\0')
	{
		ft_putchar_fd('\n', 1);
		client->offset = 0;
		return ;
	}
	ft_putchar_fd(client->message[client->offset], 1);
	client->offset++;
}
