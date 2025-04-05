/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:33:19 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 03:26:46 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minitalk.h"

size_t ft_strlen(const char *inputString)
{
    size_t length; 
    length = 0; 
    
    while (inputString[length] != '\0')
    {
        length++; 
    }

    return (length);
}