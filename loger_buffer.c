/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filename: loger_buffer.c                                                 */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:57 by priezu-m          #+#    #+#             */
/*   Updated:  2023/09/24 19:20:43                                            */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "loger.h"
#include <unistd.h>

static int	handle_zero(char *tab)
{
	tab[0] = '0';
	tab[1] = ' ';
	return (2);
}

static int	put_nbr_in_tab(unsigned long int nbr, char *tab)
{
	int					i;
	unsigned long int	magnitude;
	unsigned long int	aux;

	if (nbr == 0)
		return (handle_zero(tab));
	i = 0;
	aux = nbr;
	magnitude = 0;
	while (aux)
	{
		aux /= 10;
		magnitude *= 10;
		if (magnitude == 0)
			magnitude = 1;
		i++;
	}
	while (magnitude)
	{
		*tab = ((nbr / magnitude) % 10) + '0';
		tab++;
		magnitude /= 10;
	}
	*tab = ' ';
	return (i + 1);
}

void	push_data_to_buffer(t_event_data data)
{
	static char	msg[100];
	int			i;
	const char	*event_descriptions[]
		= {
	[e_took_forks] = "took his forks\n",
	[e_left_forks] = "lef his forks\n",
	[e_began_to_eat] = "began to eat\n",
	[e_finished_last_needed_meal] = "you should not see this message\n",
	[e_began_to_sleep] = "began to sleep\n",
	[e_began_to_think] = "began to think\n",
	[e_simulation_aborted]
		= "simulation has gone on for too long, aborting\n",
	[e_philosopher_died] = "died\n"
	};

	i = put_nbr_in_tab(data.time_of_issuing, msg);
	i += put_nbr_in_tab((unsigned)data.issuer_id, &msg[i]);
	while (*event_descriptions[data.event_id] != '\0')
	{
		msg[i] = *event_descriptions[data.event_id];
		i++;
		event_descriptions[data.event_id]++;
	}
	log_buffer(e_push_to_buffer, msg, i);
}

void	log_buffer(t_buffer_action action, char *msg, int msg_size)
{
	static char	buffer[BUFFER_SIZE];
	static int	index;

	if (action == e_push_to_buffer)
	{
		if ((index + msg_size) > BUFFER_SIZE)
			log_buffer(e_flush_buffer, NULL, 0);
		while (msg_size)
		{
			buffer[index] = *msg;
			msg++;
			index++;
			msg_size--;
		}
		return ;
	}
	write(STDOUT_FILENO, buffer, (unsigned)(index));
	index = 0;
}
