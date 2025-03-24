/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:08:06 by isel-bar          #+#    #+#             */
/*   Updated: 2025/03/21 20:09:19 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// This function writes a string to the specified file descriptor.
// Parameters:
// - str: The string to be written. If it is NULL, the function does nothing.
// - fd: The file descriptor where the string will be written.
void	ft_putstr_fd(const char *str, int file_descriptor)
{
    int	char_index; // Variable to keep track of the current character index.

    // Initialize the character index to 0.
    char_index = 0;

    // Check if the string is not NULL and iterate through each character.
    while (str != NULL && str[char_index] != '\0')
    {
        // Write the current character to the file descriptor.
        ft_putchar_fd(str[char_index], file_descriptor);

        // Move to the next character in the string.
        char_index++;
    }
}