/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:46:47 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:36:47 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "minitalk.h"


t_server g_server;


void handle_client_error(t_server *serverState)
{
	
	if (serverState->bit_offset == 0 && serverState->message_pos == 0)
	{
		
		ft_putstr_fd("[PIDError] : "
					 "This Process is Unavailable!\n",
					 2);
	}
	else
	{
		
		ft_putstr_fd("[CommunicationError] : "
					 "The server connection was lost!\n",
					 2);
	}

	
	serverState->running = 0;
}


void ft_send_bit(void)
{
	unsigned char signal_to_send;
	
	if (g_server.bit_offset < 8)
	{
		
		signal_to_send = SIGUSR1;

		
		if (g_server.message_bit % 2)
		{
			signal_to_send = SIGUSR2;
		}

		
		if (kill(g_server.pid, signal_to_send) < 0)
		{
			return (handle_client_error(&g_server));
		}

		g_server.message_bit = g_server.message_bit / 2;
		g_server.bit_offset++;
	}
}


void ft_send(int receivedSignal)
{
	
	usleep(USLEEP_DT);

	
	if (g_server.message_pos >= g_server.message_len)
	{
		
		g_server.running = 0;
		return;
	}

	
	if (receivedSignal == SIGUSR2)
	{
		
		g_server.bit_offset = 0;

		
		g_server.message_pos++;

		
		if (g_server.message_pos >= g_server.message_len)
		{
			
			g_server.running = 0;
			return;
		}

		
		g_server.message_bit = g_server.message[g_server.message_pos];

		
		return (ft_send_bit());
	}

	
	if (receivedSignal == SIGUSR1)
	{
		
		return (ft_send_bit());
	}
}


void ft_server_reset(t_server *server, int destinationPid, const char *messageToSend)
{
	
	server->pid = destinationPid;

	
	server->bit_offset = 0;

	
	server->message_bit = messageToSend[0];

	
	server->message_pos = 0;

	
	server->message_len = ft_strlen(messageToSend);

	
	server->message = messageToSend;

	
	server->running = 1;
}


int ft_upload(unsigned int destinationPid, const char *messageToSend)
{
	
	ft_server_reset(&g_server, destinationPid, messageToSend);
	signal(SIGUSR1, ft_send); 
	signal(SIGUSR2, ft_send); 
	ft_send(SIGUSR1);
	while (g_server.running)
		usleep(30 * 1000); 
	return (0);
}