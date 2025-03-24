/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpid_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:20:26 by isel-bar          #+#    #+#             */
/*   Updated: 2025/03/22 22:44:50 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// This function writes a process ID (PID) to a file descriptor.
// It takes an unsigned integer 'pid' and an integer 'fileDescriptor' as arguments.
// The function recursively breaks down the PID into individual digits and writes them one by one.

#include <unistd.h> // For the write function

// Helper function to write a single character to a file descriptor.
void write_character_to_fd(char character, int fileDescriptor)
{
    write(fileDescriptor, &character, 1);
}

// Main function to write the PID to a file descriptor.
void write_pid_to_fd(unsigned int processId, int fileDescriptor)
{
    // If the process ID has more than one digit, recursively call the function
    // with the number divided by 10 (to process all digits except the last one).
    if (processId > 9)
    {
        write_pid_to_fd(processId / 10, fileDescriptor);
    }

    // Write the last digit of the process ID to the file descriptor.
    // '0123456789' is used to map the digit to its corresponding character.
    char digitCharacter = '0' + (processId % 10);
    write_character_to_fd(digitCharacter, fileDescriptor);
}