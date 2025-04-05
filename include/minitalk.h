/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:48:26 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/03 21:00:07 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <stddef.h>
# include <signal.h>
# include <unistd.h>

# define USLEEP_DT 100

typedef struct s_client
{
	int			pid;
	size_t		offset;
	char		message[4];
	int			nbites;
	size_t		base;
}	t_client;

typedef struct s_server
{
	size_t			pid;
	unsigned char	bit_offset;
	size_t			message_bit;
	size_t			message_pos;
	size_t			message_len;
	const char		*message;
	int				running;
}	t_server;

unsigned int		convert_string_to_pid(const char *str);
void				ft_putchar_fd(char character, int file_descriptor);
void				ft_putstr_fd(const char *str, int file_descriptor);
void				write_pid_to_fd(unsigned int pid, int fd);
int					ft_upload(unsigned int pid, const char *msg);
void				ft_reset_client(t_client *client);
void				show_client_message(t_client *client);
size_t				ft_strlen(const char *str);

#endif