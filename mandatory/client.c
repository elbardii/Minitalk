/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/05 02:28:38 by isel-bar          #+#    #+#             */
/*   Updated: 2025/04/05 02:29:02 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	main(int argc, char **argv)
{
	unsigned int	server_process_id;

	if (argc != 3)
	{
		ft_putstr_fd("[ParametersError] :\n"
			"The client takes two parameters:\n"
			"\t* The server PID. <unsigned int>\n"
			"\t* The string to send. <char *>\n", 2);
		return (1);
	}
	server_process_id = convertStringToPID(argv[1]);
	if (server_process_id == 0)
	{
		ft_putstr_fd("[PIDError] : Invalid Server PID: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
		return (1);
	}
	return (ft_upload(server_process_id, argv[2]));
}
