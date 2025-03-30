
#include "minitalk.h"

/**
 * Main function for the client program
 * 
 * This program sends a message to a server process using signals.
 * It requires two command-line arguments:
 * 1. The server's process ID (PID)
 * 2. The message to send to the server
 * 
 * @param argc Number of command-line arguments
 * @param argv Array of command-line argument strings
 * @return 0 on success, 1 on error
 */
int	main(int argc, char **argv)
{
	unsigned int	server_process_id;  // Stores the server's process ID

	// Check if the user provided exactly 2 arguments (plus program name)
	if (argc != 3)
	{
		// Display an error message explaining the correct usage
		ft_putstr_fd("[ParametersError] :\n"
			"The client takes two parameters:\n"
			"\t* The server PID. <unsigned int>\n"
			"\t* The string to send. <char *>\n", 2);
		return (1);  // Return error code
	}

	// Convert the first argument (server PID) from string to unsigned int
	server_process_id = convertStringToPID(argv[1]);

	// Check if the PID conversion was successful
	if (server_process_id == 0)
	{
		// Display an error message about the invalid PID
		ft_putstr_fd("[PIDError] : Invalid Server PID: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		return (1);  // Return error code
	}

	// If all checks pass, send the message to the server
	// The second argument (argv[2]) contains the message to send
	return (ft_upload(server_process_id, argv[2]));
}
