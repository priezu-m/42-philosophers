/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher_routine.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:26:11                                            */
/*   Updated:  2023/09/21 00:14:46                                            */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "schedueler.h"
#include "mutex_sequential_action.h"
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

void	initial_block(t_schedueler_data schedueler_data,
		int philosopher_number)
{
	if (*schedueler_data.simulation_over == true)
		return ;
	(*schedueler_data.number_of_active_philosophers)--;
	pthread_mutex_lock(&schedueler_data.mutexs[philosopher_number - 1]);
	schedueler_data.mutex_locked_check[philosopher_number - 1] = true;
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
