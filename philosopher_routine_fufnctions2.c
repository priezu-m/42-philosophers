/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher_routine_fufnctions2.c                              */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 17:18:25                                            */
/*   Updated:  2023/09/19 17:18:59                                            */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "time.h"
#include "mutex_sequential_action.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	block_self(t_philosopher *self)
{
	const int	philo_number = self->philosopher_number;

	(*self->schedueler_data.number_of_active_philosophers)--;
	mutex_sequential_action(e_mutex_lock,
		&self->schedueler_data.mutexs[philo_number - 1]);
	self->schedueler_data.mutex_locked_check[philo_number - 1] = true;
}

bool	simulation_over(t_philosopher *self)
{
	if (*self->schedueler_data.simulation_over == true)
		return (true);
	if (self->time_of_death >= get_set_current_time(e_get_current_time))
	{
		//print died
		return (true);
	}
	return (false);
}

void	get_forks(t_philosopher *self)
{
	volatile _Atomic t_fork_state	*forks;
	t_fork_state					aux;
	bool							needs_to_block;
	const int						philo_number = self->philosopher_number;

	if (simulation_over(self) == true)
		return ;
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
		block_self(self);
	forks[0] = e_default_fork_state;
	forks[1] = e_default_fork_state;
}

void	yield_forks_internal(t_fork_yield_queque yield_queque,
		int philo_number)
{
	int	aux;

	aux = (*yield_queque.queque_index)++;
	aux %= yield_queque.queque_size;
	(*yield_queque.queque_index) %= yield_queque.queque_size;
	yield_queque.yielder_ids[aux] = philo_number;
}

void	yield_forks(t_philosopher *self)
{
	if (simulation_over(self) == true)
		return ;
	yield_forks_internal(self->schedueler_data.yields,
		self->philosopher_number);
}

#pragma clang diagnostic pop
