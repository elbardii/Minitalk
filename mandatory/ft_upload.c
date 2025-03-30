/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_upload.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 22:46:47 by isel-bar          #+#    #+#             */
/*   Updated: 2025/03/23 22:10:36 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "minitalk.h"

// Global server state variable that stores information about the current communication session
t_server	g_server;

/**
 * Handles error conditions that occur during client-server communication
 * 
 * This function displays appropriate error messages when communication fails:
 * - If we haven't started sending any data yet (bit_offset and message_pos are 0),
 *   it means the server process ID (PID) is invalid or unreachable
 * - Otherwise, it means we lost connection with a previously working server
 *
 * @param serverState Pointer to the server state structure containing communication details
 */
void	handle_client_error(t_server *serverState)
{
    // Check if we haven't started sending any data yet
    if (serverState->bit_offset == 0 && serverState->message_pos == 0)
    {
        // Display PID error message to standard error (file descriptor 2)
        ft_putstr_fd("[PIDError] : "
            "This Process is Unavailable!\n", 2);
    }
    else
    {
        // Display communication error message to standard error
        ft_putstr_fd("[CommunicationError] : "
            "The server connection was lost!\n", 2);
    }

    // Set the running flag to 0 to stop the communication loop
    serverState->running = 0;
}

/**
 * Sends a single bit of data to the server using signals
 * 
 * This function handles the bit-by-bit transmission of a character:
 * - Each character is sent as 8 bits (1 byte)
 * - SIGUSR1 represents a 0 bit
 * - SIGUSR2 represents a 1 bit
 * - We use modulo 2 to check if the current bit is 0 or 1
 * - After sending each bit, we divide by 2 to get ready for the next bit
 */
void	ft_send_bit(void)
{
	unsigned char	signal_to_send;  // Signal we'll use to send the bit

	// Only process if we haven't sent all 8 bits of the current character yet
	if (g_server.bit_offset < 8)
	{
		// Default to SIGUSR1 (represents binary 0)
		signal_to_send = SIGUSR1;

		// If current bit is 1, use SIGUSR2 instead
		if (g_server.message_bit % 2)
		{
			signal_to_send = SIGUSR2;
		}

		// Try to send the signal to the server process
		// If sending fails (kill returns -1), report the error
		if (kill(g_server.pid, signal_to_send) < 0)
		{
			return (handle_client_error(&g_server));
		}

		// Prepare for next bit:
		// - Shift right by dividing by 2 to get the next bit ready
		// - Increment our bit counter
		g_server.message_bit = g_server.message_bit / 2;
		g_server.bit_offset++;
	}
}

/**
 * Handles signal responses from the server during message transmission
 * 
 * This function is called whenever we receive a signal from the server:
 * - SIGUSR1: Server is ready for the next bit of the current character
 * - SIGUSR2: Server has successfully received a complete character and is ready for the next one
 * 
 * @param receivedSignal The signal received from the server (SIGUSR1 or SIGUSR2)
 */
void	ft_send(int receivedSignal)
{
	// Add a small delay to prevent signal overload
	usleep(USLEEP_DT);
	
	// Check if we've reached the end of our message
	if (g_server.message_pos >= g_server.message_len)
	{
		// If yes, stop the communication loop
		g_server.running = 0;
		return ;
	}
	
	// If we received SIGUSR2, it means the server has received a complete character
	if (receivedSignal == SIGUSR2)
	{
		// Reset bit counter for the next character
		g_server.bit_offset = 0;
		
		// Move to the next character in our message
		g_server.message_pos++;
		
		// Check again if we've reached the end of our message
		if (g_server.message_pos >= g_server.message_len)
		{
			// If yes, stop the communication loop
			g_server.running = 0;
			return ;
		}
		
		// Load the next character to be sent
		g_server.message_bit = g_server.message[g_server.message_pos];
		
		// Send the first bit of this new character
		return (ft_send_bit());
	}
	
	// If we received SIGUSR1, the server is ready for the next bit
	if (receivedSignal == SIGUSR1)
	{
		// Send the next bit of the current character
		return (ft_send_bit());
	}
}

/**
 * Initializes or resets the server structure with new communication parameters
 *
 * This function prepares the server structure for a new message transmission by:
 * - Setting the destination process ID
 * - Resetting bit counters and message position
 * - Storing the message to be sent and its length
 * - Setting the server to "running" state
 *
 * @param server Pointer to the server structure to initialize
 * @param destinationPid Process ID of the receiving server
 * @param messageToSend The message string that will be transmitted
 */
void	ft_server_reset(t_server *server, int destinationPid, const char *messageToSend)
{
	// Store the destination process ID
	server->pid = destinationPid;
	
	// Reset the bit counter for the first character
	server->bit_offset = 0;
	
	// Load the first character of the message
	server->message_bit = messageToSend[0];
	
	// Start from the beginning of the message
	server->message_pos = 0;
	
	// Calculate and store the total length of the message
	server->message_len = ft_strlen(messageToSend);
	
	// Store a reference to the message
	server->message = messageToSend;
	
	// Set the server to "running" state to begin transmission
	server->running = 1;
}

/**
 * Uploads a message to another process using signals
 *
 * This function handles the entire process of sending a message to another
 * process identified by its PID. It uses UNIX signals for communication:
 * - SIGUSR1 and SIGUSR2 are used for bit-by-bit transmission
 * - The function waits until the entire message is sent
 *
 * @param destinationPid The process ID of the receiving server
 * @param messageToSend The string message to transmit
 * @return 0 when the transmission is complete
 */
int	ft_upload(unsigned int destinationPid, const char *messageToSend)
{
	// Initialize the server structure with the message details
	ft_server_reset(&g_server, destinationPid, messageToSend);
	
	// Set up signal handlers for receiving acknowledgments from the server
	signal(SIGUSR1, ft_send);  // Server is ready for next bit
	signal(SIGUSR2, ft_send);  // Server received a complete character
	
	// Start the transmission process with the first bit
	ft_send(SIGUSR1);
	
	// Wait until the entire message has been transmitted
	// The loop continues until g_server.running is set to 0 (in ft_send)
	while (g_server.running)
		usleep(30 * 1000);  // Sleep for 30 milliseconds between checks
	
	// Return success when transmission is complete
	return (0);
}