/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:08:06 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:32:13 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"


void	ft_putstr_fd(const char *str, int file_descriptor)
{
    int	char_index; 

    
    char_index = 0;

    
    while (str != NULL && str[char_index] != '\0')
    {
        
        ft_putchar_fd(str[char_index], file_descriptor);

        
        char_index++;
    }
}