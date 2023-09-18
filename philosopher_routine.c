/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher_routine.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:26:11                                            */
/*   Updated:  2023/09/18 19:36:09                                            */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "schedueler.h"
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

void	get_forks(t_philosopher *self)
{
	volatile _Atomic t_fork_state	*forks;
	t_fork_state					aux;
	bool							needs_to_block;
	const int						philo_number = self->philosopher_number;

	needs_to_block = false;
	forks = &self->schedueler_data.fork_sate[philo_number - 1][0];
	aux = forks[0]--;
	if (aux == e_gotten)
		forks[0] = e_gotten_and_requested;
	else
		needs_to_block = true;
	aux = forks[1]--;
	if (aux == e_gotten)
		forks[1] = e_gotten_and_requested;
	else
		needs_to_block = true;
	if (needs_to_block == true)
	{
		//mutex_sequential_action(e_mutex_lock,
			//&self->schedueler_data.mutexs[philo_number - 1]);
		self->schedueler_data.mutex_locked_check[philo_number - 1] = true;
	}
	forks[0] = e_default_fork_state;
	forks[1] = e_default_fork_state;
}

void	*philosopher_routine(void *arg)
{
	t_philosopher	*self;

	self = arg;
	initial_block(self->schedueler_data, self->philosopher_number);
	while (*self->schedueler_data.simulation_over != true)
	{
		think();
		get_forks(self);
		eat();
		yield_forks();
		sleep_self();
	}
	return (NULL);
}

#pragma clang diagnostic pop
