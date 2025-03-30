#include "minitalk.h"

/**
 * Calculates the length of a string by counting its characters
 *
 * This function counts the number of characters in a string until it reaches
 * the null terminator ('\0' or 0). It uses iteration to count each character
 * until reaching the end of the string.
 *
 * @param inputString A pointer to the string we want to measure
 * @return The number of characters in the string (size_t type)
 */
size_t ft_strlen(const char *inputString)
{
    size_t length; // Variable to store the string length

    length = 0; // Initialize length counter to 0

    // Loop through string until we hit null terminator
    while (inputString[length] != '\0')
    {
        length++; // Increment length for each character
    }

    return (length); // Return the final length
}