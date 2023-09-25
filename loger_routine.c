/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loger_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:51:12 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/25 16:51:15 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "loger.h"
#include "time.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

static void	check_special_events(t_loger_data *loger_data)
{
	int		i;
	t_event	event;

	i = loger_data->loger_queque.private_queque_index;
	event = loger_data->loger_queque.request_queque[i].event_data.event_id;
	if (event == e_simulation_aborted || event == e_philosopher_died)
	{
		*loger_data->simulation_over = true;
		return ;
	}
}

static void	increment_private_index(t_loger_data *loger_data)
{
	loger_data->loger_queque.private_queque_index++;
	loger_data->loger_queque.private_queque_index
		%= loger_data->loger_queque.queque_size;
}

static void	set_all_to_completed(t_loger_queque *loger_queque)
{
	int	i;

	i = 0;
	while (i < loger_queque->queque_size)
	{
		loger_queque->request_queque[i].requests_comleted = true;
		i++;
	}
}

static bool	loger_subroutine(t_loger_data *loger_data)
{
	const int	i = loger_data->loger_queque.private_queque_index;

	if (loger_data->loger_queque.request_queque[i].event_data.event_id
		== e_finished_last_needed_meal)
	{
		loger_data->last_needed_meals_needed--;
		if (loger_data->last_needed_meals_needed == 0)
		{
			*loger_data->simulation_over = true;
			return (true);
		}
	}
	else
	{
		push_data_to_buffer(
			loger_data->loger_queque.request_queque[i].event_data);
		check_special_events(loger_data);
	}
	loger_data->loger_queque.request_queque[i].requests_comleted = true;
	increment_private_index(loger_data);
	return (false);
}

void	*loger_routine(void *arg)
{
	t_loger_data	*loger_data;
	int				i;

	loger_data = arg;
	while (*(loger_data->simulation_over) != true)
	{
		i = loger_data->loger_queque.private_queque_index;
		if ((loger_data->loger_queque.request_queque[i].requests_comleted)
			== true)
			log_buffer(e_flush_buffer, NULL, 0);
		else
		{
			if (loger_subroutine(loger_data) == true)
				break ;
		}
	}
	log_buffer(e_flush_buffer, NULL, 0);
	set_all_to_completed(&loger_data->loger_queque);
	return (NULL);
}
