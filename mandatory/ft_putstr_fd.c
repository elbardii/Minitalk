/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:28:38 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:29:02 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_putstr_fd(const char *str, int file_descriptor)
{
	int	i;

	i = 0;
	while (str[i])
	{
		ft_putchar_fd(str[i], file_descriptor);
		i++;
	}
}
