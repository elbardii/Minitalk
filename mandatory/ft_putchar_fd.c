/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:44:13 by isel-bar          #+#    #+#             */
/*   Updated: 2025/03/20 21:00:53 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// This function writes a single character to the specified file descriptor.
// Parameters:
// - character: The character to be written.
// - fileDescriptor: The file descriptor where the character will be written.
// Example: To write a character to the standard output, pass 1 as the file descriptor.
void	ft_putchar_fd(char character, int fileDescriptor)
{
    // The write function is used to output the character.
    // It takes three arguments: the file descriptor, a pointer to the data, and the number of bytes to write.
    write(fileDescriptor, &character, 1);
}
