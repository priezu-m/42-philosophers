/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:19:54 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:20:00 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "philosopher.h"

t_philosopher	*get_philosopher_list(volatile _Atomic bool *simulation_over,
					t_parameters parameters, t_schedueler_data schedueler_data,
					t_loger_queque loger_queque)
{
	t_philosopher	*philosopher_list;
	int				i;

	philosopher_list = calloc((unsigned)parameters.number_of_philosophers,
			sizeof(t_philosopher));
	if (philosopher_list == NULL)
		return (philosopher_list);
	i = 0;
	while (i < parameters.number_of_philosophers)
	{
		philosopher_list[i].philosopher_number = i + 1;
		philosopher_list[i].launch_aborted = false;
		philosopher_list[i].loger_queque = loger_queque;
		philosopher_list[i].parameters = parameters;
		philosopher_list[i].schedueler_data = schedueler_data;
		philosopher_list[i].simulation_over = simulation_over;
		philosopher_list[i].time_of_death
			= (unsigned)parameters.time_to_starve * 1000ul;
		schedueler_data.times_of_death.philosophers_id[i] = i + 1;
		schedueler_data.times_of_death.times[i]
			= (unsigned long)parameters.time_to_starve * 1000ul;
		i++;
	}
	*schedueler_data.times_of_death.list_index = i;
	return (philosopher_list);
}

bool	philosopher_list_valid(t_philosopher *philosopher_list)
{
	if (philosopher_list == NULL)
		return (false);
	return (true);
}

void	destroy_philosopher_list(t_philosopher *philosopher_list)
{
	free(philosopher_list);
}
