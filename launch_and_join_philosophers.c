/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_and_join_philosophers.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:18:33 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:18:52 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

void	launch_and_join_philosophers(t_philosopher *philosopher_list)
{
	const int	number_of_philosophers
		= philosopher_list[0].parameters.number_of_philosophers;
	int			i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_create(&philosopher_list[i].thread_id, NULL,
				philosopher_routine, &philosopher_list[i]) != 0)
		{
			printf("Failed to launch philosopher %d, aborting.\n", i + 1);
			*philosopher_list[i].simulation_over = true;
			philosopher_list[i].launch_aborted = true;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		if (philosopher_list[i].launch_aborted == true)
			return ;
		pthread_join(philosopher_list[i].thread_id, NULL);
		i++;
	}
}
