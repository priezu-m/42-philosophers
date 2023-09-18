/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: schedueler_routine.c                                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:27:52                                            */
/*   Updated:  2023/09/18 19:38:51                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include <stdbool.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

//todo: give below functions external linkage

void	yield_right_fork(t_schedueler_data *schedueler_data, int reciver)
{
	volatile _Atomic t_fork_state	*forks;
	t_fork_state					aux;

	forks = &schedueler_data->fork_sate[reciver - 1][0];
	aux = forks[0]++;
	if (aux == e_requested)
	{
		forks[0] = e_requested_and_gotten;
		if (forks[1] == e_default_fork_state || forks[1] == e_requested)
			return ;
		schedueler_data->mutex_locked_check[reciver - 1] = false;
		//mutex_sequential_action(e_mutex_unlock,
			//&self->schedueler_data.mutexs[reciver - 1]);
		(*schedueler_data->number_of_active_philosophers)++;
	}
	else if (forks[1] == e_requested_and_gotten)
	{
		schedueler_data->mutex_locked_check[reciver - 1] = false;
		//mutex_sequential_action(e_mutex_unlock,
			//&self->schedueler_data.mutexs[reciver - 1]);
		(*schedueler_data->number_of_active_philosophers)++;
	}
}

void	yield_left_fork(t_schedueler_data *schedueler_data, int reciver)
{
	volatile _Atomic t_fork_state	*forks;
	t_fork_state					aux;

	forks = &schedueler_data->fork_sate[reciver - 1][0];
	aux = forks[1]++;
	if (aux == e_requested)
	{
		forks[1] = e_requested_and_gotten;
		if (forks[0] == e_default_fork_state || forks[0] == e_requested)
			return ;
		schedueler_data->mutex_locked_check[reciver - 1] = false;
		//mutex_sequential_action(e_mutex_unlock,
			//&self->schedueler_data.mutexs[reciver - 1]);
		(*schedueler_data->number_of_active_philosophers)++;
	}
	else if (forks[0] == e_requested_and_gotten)
	{
		schedueler_data->mutex_locked_check[reciver - 1] = false;
		//mutex_sequential_action(e_mutex_unlock,
			//&self->schedueler_data.mutexs[reciver - 1]);
		(*schedueler_data->number_of_active_philosophers)++;
	}
}

void	check_fork_yields(t_schedueler_data *schedueler_data)
{
	const int	i = schedueler_data->yields.private_queque_index;
	int			id;

	if (i == *schedueler_data->yields.queque_index)
		return ;
	if (schedueler_data->yields.yielder_ids[i] == 0)
		return ;
	id = schedueler_data->yields.yielder_ids[i];
	if (id == schedueler_data->number_of_philosophers)
		yield_right_fork(schedueler_data, 1);
	else
		yield_right_fork(schedueler_data, id + 1);
	if (id == 0)
	{
		yield_left_fork(schedueler_data,
				schedueler_data->number_of_philosophers);
	}
	else
		yield_left_fork(schedueler_data, id - 1);
	schedueler_data->yields.yielder_ids[i] = 0;
	schedueler_data->yields.private_queque_index++;
}

void	give_initial_forks(volatile _Atomic t_fork_state (*fork_sate)[2],
		int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		fork_sate[i][0] = e_gotten;
		fork_sate[i][1] = e_gotten;
		i += 2;
	}
	if ((number_of_philosophers % 2) == 1)
	{
		i -= 2;
		fork_sate[i][0] = e_default_fork_state;
		fork_sate[i][1] = e_default_fork_state;
		i--;
		if (i == -1)
			i = 0;
		fork_sate[i][1] = e_gotten;
	}
}

void	*schedueler_routine(void *arg)
{
	t_schedueler_data	*schedueler_data;

	schedueler_data	= arg;
	give_initial_forks(schedueler_data->fork_sate,
		schedueler_data->number_of_philosophers);
	while ((*schedueler_data->number_of_active_philosophers != 0)
			&& (*schedueler_data->simulation_over != true))
		;
	while (*schedueler_data->simulation_over != true)
	{
		check_fork_yields(schedueler_data);
		check_eating();
		check_sleeping();
		check_deaths();
	}
	unlock_all();
	return (NULL);
}

#pragma clang diagnostic pop
