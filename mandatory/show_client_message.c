/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_client_message.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 20:47:38 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/03 20:47:43 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
#include <unistd.h>


size_t	ft_unicode_len(const char *c)
{
	if (0 <= c[0])
		return (1);
	else if (-16 <= c[0])
		return (4);
	else if (-32 <= c[0])
		return (3);
	return (2);
}

void	show_client_message(t_client *c)
{
	if (c->message[0] >= 0)
	{
		write(1, c->message, 1);
	}
	else
	{
		if (c->message[c->offset] >= 0)
			c->offset = 0;
		c->offset++;
		if (c->offset == ft_unicode_len(c->message))
		{
			write(1, c->message, c->offset);
			c->offset = 0;
		}
	}
}