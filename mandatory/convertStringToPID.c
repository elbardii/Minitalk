/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertStringToPID.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:53:55 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 03:26:22 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

unsigned int convertStringToPID(const char *inputString) {
    unsigned int processID = 0; 
    unsigned char Index = 0; 

    
    while (Index < 5 && inputString[Index] >= '0' && inputString[Index] <= '9') {
        
        processID = processID * 10 + (inputString[Index] - '0');
        Index++; 
    }

    
    if (Index == 5 || inputString[Index] != '\0') {
        return 0; 
    }

    
    return processID;
}
