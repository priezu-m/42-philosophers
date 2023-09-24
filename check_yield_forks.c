/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_yield_forks.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:17:11 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:18:53 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include "mutex_action_no_ownership_transfer.h"

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
		(*schedueler_data->number_of_active_philosophers)++;
		mutex_action_no_ownership_transfer(e_mutex_unlock,
			&schedueler_data->mutexs[reciver - 1],
			&schedueler_data->mutex_locked_check[reciver - 1]);
	}
	else if (forks[1] == e_requested_and_gotten)
	{
		(*schedueler_data->number_of_active_philosophers)++;
		mutex_action_no_ownership_transfer(e_mutex_unlock,
			&schedueler_data->mutexs[reciver - 1],
			&schedueler_data->mutex_locked_check[reciver - 1]);
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
		(*schedueler_data->number_of_active_philosophers)++;
		mutex_action_no_ownership_transfer(e_mutex_unlock,
			&schedueler_data->mutexs[reciver - 1],
			&schedueler_data->mutex_locked_check[reciver - 1]);
	}
	else if (forks[0] == e_requested_and_gotten)
	{
		(*schedueler_data->number_of_active_philosophers)++;
		mutex_action_no_ownership_transfer(e_mutex_unlock,
			&schedueler_data->mutexs[reciver - 1],
			&schedueler_data->mutex_locked_check[reciver - 1]);
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
	if (id == 1)
	{
		yield_left_fork(schedueler_data,
			schedueler_data->number_of_philosophers);
	}
	else
		yield_left_fork(schedueler_data, id - 1);
	schedueler_data->yields.yielder_ids[i] = 0;
	schedueler_data->yields.private_queque_index++;
	schedueler_data->yields.private_queque_index
		%= schedueler_data->yields.queque_size;
}
