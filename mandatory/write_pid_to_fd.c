/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_pid_to_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 20:20:26 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:34:00 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> 
#include "minitalk.h"

void write_pid_to_fd(unsigned int processId, int fileDescriptor)
{

    if (processId > 9)
    {
        write_pid_to_fd(processId / 10, fileDescriptor);
    }

    char digitCharacter = '0' + (processId % 10);
    ft_putchar_fd(digitCharacter, fileDescriptor);
}