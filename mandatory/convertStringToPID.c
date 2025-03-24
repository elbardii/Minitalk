/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convertStringToPID.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 16:53:55 by isel-bar          #+#    #+#             */
/*   Updated: 2025/03/21 20:18:19 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>


// Function to convert a string representation of a PID (Process ID) into an integer.
// The function assumes the PID is a numeric string with up to 5 digits.
// If the input string is invalid (e.g., contains non-numeric characters or is too long),
// the function returns 0 to indicate an error.
unsigned int convertStringToPID(const char *inputString) {
    unsigned int processID = 0; // Variable to store the resulting PID.
    unsigned char Index = 0; // Index to iterate through the input string.

    // Loop through the string, character by character.
    // Stop if we reach a non-numeric character or exceed 5 characters.
    while (Index < 5 && inputString[Index] >= '0' && inputString[Index] <= '9') {
        // Convert the current character to its numeric value and add it to the PID.
        processID = processID * 10 + (inputString[Index] - '0');
        Index++; // Move to the next character.
    }

    // Check if the input string is valid:
    // - It should not exceed 5 characters.
    // - It should not contain any non-numeric characters.
    // - It should end with a null terminator ('\0').
    if (Index == 5 || inputString[Index] != '\0') {
        return 0; // Return 0 to indicate an invalid input.
    }

    // Return the valid PID as an integer.
    return processID;
}
