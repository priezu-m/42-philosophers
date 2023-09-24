/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loger_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:15:46 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:16:33 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loger.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

static t_loger_queque	get_loger_queque(int number_of_philosophers)
{
	t_loger_queque	loger_queque;
	int				i;

	loger_queque.private_queque_index = 0;
	loger_queque.queque_size = number_of_philosophers;
	loger_queque.queque_index = calloc(1, sizeof(volatile _Atomic int));
	loger_queque.request_queque = calloc((unsigned)number_of_philosophers,
			sizeof(t_log_request));
	if (loger_queque.request_queque == NULL)
		return (loger_queque);
	i = 0;
	while (i < number_of_philosophers)
	{
		loger_queque.request_queque[i].requests_comleted = true;
		i++;
	}
	return (loger_queque);
}

t_loger_data	get_loger_data(volatile _Atomic bool *simulation_over,
		int number_of_philosophers)
{
	t_loger_data	loger_data;

	loger_data.loger_queque = get_loger_queque(number_of_philosophers);
	loger_data.last_needed_meals_needed = number_of_philosophers;
	loger_data.launch_aborted = false;
	loger_data.simulation_over = simulation_over;
	return (loger_data);
}

void	destroy_loger_data(t_loger_data loger_data)
{
	free((void *)(intptr_t)loger_data.loger_queque.request_queque);
	free((void *)(intptr_t)loger_data.loger_queque.queque_index);
}

bool	loger_data_valid(t_loger_data loger_data)
{
	if (loger_data.loger_queque.request_queque == NULL)
		return (false);
	return (true);
}
