/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:28:38 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:29:02 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_server	g_server;

static void	handle_client_error(t_server *server)
{
	if (server->bit_offset == 0 && server->message_pos == 0)
		ft_putstr_fd("[PIDError] : This Process is Unavailable!\n", 2);
	else
		ft_putstr_fd("[CommunicationError] : Connection lost!\n", 2);
	server->running = 0;
}

static void	send_next_bit(void)
{
	unsigned char	signal;

	if (g_server.bit_offset < 8)
	{
		signal = SIGUSR1;
		if (g_server.message_bit % 2)
			signal = SIGUSR2;
		if (kill(g_server.pid, signal) < 0)
			return (handle_client_error(&g_server));
		g_server.message_bit = g_server.message_bit / 2;
		g_server.bit_offset++;
	}
}

static void	handle_signal(int sig)
{
	usleep(USLEEP_DT);
	if (g_server.message_pos >= g_server.message_len)
	{
		g_server.running = 0;
		return ;
	}
	if (sig == SIGUSR2)
	{
		g_server.bit_offset = 0;
		g_server.message_pos++;
		if (g_server.message_pos >= g_server.message_len)
		{
			g_server.running = 0;
			return ;
		}
		g_server.message_bit = g_server.message[g_server.message_pos];
		return (send_next_bit());
	}
	if (sig == SIGUSR1)
		return (send_next_bit());
}

static void	init_server(t_server *server, int pid, const char *msg)
{
	server->pid = pid;
	server->bit_offset = 0;
	server->message_bit = msg[0];
	server->message_pos = 0;
	server->message_len = ft_strlen(msg);
	server->message = msg;
	server->running = 1;
}

int	ft_upload(unsigned int pid, const char *msg)
{
	init_server(&g_server, pid, msg);
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	handle_signal(SIGUSR1);
	while (g_server.running)
		usleep(30 * 1000);
	return (0);
}
