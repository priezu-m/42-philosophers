/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:52:03 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/25 16:52:06 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_action_no_ownership_transfer.h"
#include "philosopher.h"
#include "schedueler.h"
#include "time.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

void	think(t_philosopher *self)
{
	if (simulation_over(self) == true)
		return ;
	print_event_sequential(self->loger_queque, e_began_to_think,
		self->philosopher_number);
}

void	initial_block(t_schedueler_data schedueler_data,
		int philosopher_number)
{
	while (schedueler_data.mutex_locked_check[philosopher_number - 1] == false)
		;
	(*schedueler_data.number_of_active_philosophers)--;
	mutex_action_no_ownership_transfer(e_mutex_lock,
		&schedueler_data.mutexs[philosopher_number - 1],
		&schedueler_data.mutex_locked_check[philosopher_number - 1]);
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*self;

	self = arg;
	initial_block(self->schedueler_data, self->philosopher_number);
	while (*self->schedueler_data.simulation_over != true)
	{
		think(self);
		get_forks(self);
		if (simulation_over(self) == false)
		{
			print_event_sequential(self->loger_queque, e_took_forks,
				self->philosopher_number);
		}
		eat(self);
		if (self->parameters.number_of_meals_needed == 0)
		{
			print_event_sequential(self->loger_queque,
				e_finished_last_needed_meal, self->philosopher_number);
		}
		yield_forks(self);
		sleep_self(self);
	}
	return (NULL);
}
