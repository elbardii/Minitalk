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

// Global variable to store server state
t_server g_server;

// Function to handle errors during communication with the server
void handle_client_error(t_server *server_state)
{
    if (server_state->current_bit == 0 && server_state->current_message_index == 0)
    {
        ft_putstr_fd("[Error] : Unable to communicate with the server. Process unavailable!\n", 2);
    }
    else
    {
        ft_putstr_fd("[Error] : Communication failed. The server might have terminated unexpectedly!\n", 2);
    }
    server_state->is_running = 0; // Stop the client process
}

// Function to send a single bit to the server
void send_bit_to_server(void)
{
    unsigned char signal_to_send;

    // Check if there are bits left to send for the current character
    if (g_server.current_bit < 8)
    {
        // Determine which signal to send based on the current bit
        signal_to_send = (g_server.current_character_bit % 2) ? SIGUSR2 : SIGUSR1;

        // Attempt to send the signal to the server
        if (kill(g_server.server_pid, signal_to_send) < 0)
        {
            handle_client_error(&g_server); // Handle error if signal sending fails
            return;
        }

        // Move to the next bit
        g_server.current_character_bit /= 2;
        g_server.current_bit++;
    }
}

// Function to handle signals received from the server
void handle_server_response(int signal)
{
    usleep(USLEEP_DT); // Small delay to avoid overwhelming the server

    // Check if all characters in the message have been sent
    if (g_server.current_message_index >= g_server.message_length)
    {
        g_server.is_running = 0; // Stop the client process
        return;
    }

    // Handle server acknowledgment signals
    if (signal == SIGUSR2) // Server acknowledged the end of a character
    {
        g_server.current_bit = 0; // Reset bit counter for the next character
        g_server.current_message_index++; // Move to the next character

        // Check if the entire message has been sent
        if (g_server.current_message_index >= g_server.message_length)
        {
            g_server.is_running = 0; // Stop the client process
            return;
        }

        // Load the next character to send
        g_server.current_character_bit = g_server.message[g_server.current_message_index];
        send_bit_to_server(); // Start sending the next character
    }
    else if (signal == SIGUSR1) // Server acknowledged a single bit
    {
        send_bit_to_server(); // Continue sending the current character
    }
}

// Function to initialize the server state for a new message
void initialize_server_state(t_server *server_state, int server_pid, const char *message)
{
    server_state->server_pid = server_pid; // Store the server's process ID
    server_state->current_bit = 0; // Start with the first bit of the first character
    server_state->current_character_bit = message[0]; // Load the first character
    server_state->current_message_index = 0; // Start with the first character
    server_state->message_length = ft_strlen(message); // Calculate the message length
    server_state->message = message; // Store the message to be sent
    server_state->is_running = 1; // Set the client process as running
}

// Function to send a message to the server
int upload_message_to_server(unsigned int server_pid, const char *message)
{
    // Initialize the server state
    initialize_server_state(&g_server, server_pid, message);

    // Set up signal handlers for server responses
    signal(SIGUSR1, handle_server_response);
    signal(SIGUSR2, handle_server_response);

    // Start sending the first bit of the message
    handle_server_response(SIGUSR1);

    // Wait until the entire message is sent
    while (g_server.is_running)
    {
        usleep(30 * 1000); // Small delay to avoid busy-waiting
    }

    return 0; // Indicate successful completion
}