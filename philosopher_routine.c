/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher_routine.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:26:11                                            */
/*   Updated:  2023/09/23 23:32:50                                            */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_action_no_ownership_transfer.h"
#include "philosopher.h"
#include "schedueler.h"
#include "time.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

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
		yield_forks(self);
		sleep_self(self);
	}
	return (NULL);
}

#pragma clang diagnostic pop
