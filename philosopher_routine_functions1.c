/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filename: philosopher_routine_functions1.c                               */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:40 by priezu-m          #+#    #+#             */
/*   Updated:  2023/09/24 19:22:46                                            */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "loger.h"
#include "philosopher.h"
#include "time.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static unsigned long int	get_new_time_trunc(unsigned long int current_time,
		int time_to_add)
{
	const unsigned long int	time_to_add_new = ((unsigned)time_to_add) * 1000;

	if ((ULONG_MAX - time_to_add_new) < current_time)
		return (ULONG_MAX);
	return (time_to_add_new + current_time);
}

static void	update_time_of_death(t_philosopher *self,
		unsigned long int current_time)
{
	int			aux;
	const int	id = self->philosopher_number;
	int			i;

	self->time_of_death = get_new_time_trunc(current_time,
			self->parameters.time_to_starve);
	aux = (*self->schedueler_data.times_of_death.list_index)++;
	*self->schedueler_data.times_of_death.list_index
		%= self->schedueler_data.times_of_death.list_size;
	aux %= self->schedueler_data.times_of_death.list_size;
	self->schedueler_data.times_of_death.times[aux] = self->time_of_death;
	self->schedueler_data.times_of_death.philosophers_id[aux] = id;
	i = self->time_of_death_position;
	if (i == 0)
		i = self->philosopher_number;
	self->schedueler_data.times_of_death.times[i - 1] = ULONG_MAX;
	self->time_of_death_position = aux + 1;
}

static void	print_began_to_eat(t_philosopher *self)
{
	if (self->parameters.number_of_meals_needed != -1)
		self->parameters.number_of_meals_needed--;
	print_event_sequential(self->loger_queque, e_began_to_eat,
		self->philosopher_number);
}

void	eat(t_philosopher *self)
{
	int						aux;
	const int				id = self->philosopher_number;
	const unsigned long int	current_time
		= get_set_current_time(e_get_current_time);
	const unsigned long int	last_time_of_death = self->time_of_death;

	if (simulation_over(self))
		return ;
	update_time_of_death(self, current_time);
	aux = (*self->schedueler_data.times_of_finishing_meal.list_index)++;
	*self->schedueler_data.times_of_finishing_meal.list_index
		%= self->schedueler_data.times_of_finishing_meal.list_size;
	aux %= self->schedueler_data.times_of_finishing_meal.list_size;
	self->schedueler_data.times_of_finishing_meal.times[aux]
		= get_new_time_trunc(current_time, self->parameters.time_eating);
	self->schedueler_data.times_of_finishing_meal.philosophers_id[aux] = id;
	if (last_time_of_death <= get_set_current_time(e_get_current_time))
	{
		print_event_sequential(self->loger_queque, e_philosopher_died,
			self->philosopher_number);
	}
	print_began_to_eat(self);
	block_self(self);
}

void	sleep_self(t_philosopher *self)
{
	int						aux;
	const int				id = self->philosopher_number;
	const unsigned long int	current_time
		= get_set_current_time(e_get_current_time);

	if (simulation_over(self))
		return ;
	aux = (*self->schedueler_data.times_of_awaking.list_index)++;
	*self->schedueler_data.times_of_awaking.list_index
		%= self->schedueler_data.times_of_awaking.list_size;
	aux %= self->schedueler_data.times_of_awaking.list_size;
	self->schedueler_data.times_of_awaking.times[aux]
		= get_new_time_trunc(current_time, self->parameters.time_sleeping);
	self->schedueler_data.times_of_awaking.philosophers_id[aux] = id;
	print_event_sequential(self->loger_queque, e_began_to_sleep,
		self->philosopher_number);
	block_self(self);
}
