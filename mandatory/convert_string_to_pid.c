/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_string_to_pid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:28:38 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:29:02 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int	convert_string_to_pid(const char *str)
{
	unsigned int	result;
	int				i;

	result = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && result <= 99999)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0' || result > 99999)
	{
		return (0);
	}
	return (result);
}
