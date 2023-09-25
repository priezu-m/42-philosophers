/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_time_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:59 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/25 16:50:06 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_action_no_ownership_transfer.h"
#include "events.h"
#include "loger.h"
#include "schedueler.h"
#include "time.h"
#include "mutex_action_no_ownership_transfer.h"
#include <limits.h>
#include <stdbool.h>

void	check_time_list(t_time_list *time_list,
		int volatile _Atomic *number_of_active_philosophers,
		pthread_mutex_t *mutexs,
		bool volatile _Atomic *mutex_locked_check)
{
	int	i;
	int	id;

	i = time_list->private_list_index;
	id = time_list->philosophers_id[i];
	if (id == 0)
		return ;
	if ((time_list->times[i]
			> get_set_current_time(e_get_current_time))
		&& (time_list->times[i] != ULONG_MAX))
	{
		return ;
	}
	time_list->philosophers_id[i] = 0;
	time_list->private_list_index++;
	time_list->private_list_index %= time_list->list_size;
	if (time_list->times[i] == ULONG_MAX)
		return ;
	(*number_of_active_philosophers)++;
	mutex_action_no_ownership_transfer(e_mutex_unlock,
		&mutexs[id - 1], &mutex_locked_check[id - 1]);
}

static bool	check_time_of_death_list_internal(t_time_list *time_list)
{
	int	i;
	int	id;

	i = time_list->private_list_index;
	id = time_list->philosophers_id[i];
	if (id == 0)
		return (false);
	if ((time_list->times[i]
			> get_set_current_time(e_get_current_time))
		&& (time_list->times[i] != ULONG_MAX))
	{
		return (false);
	}
	if (time_list->times[i] == ULONG_MAX)
	{
		time_list->philosophers_id[i] = 0;
		time_list->private_list_index++;
		time_list->private_list_index %= time_list->list_size;
		return (false);
	}
	return (true);
}

void	check_time_of_death_list(t_schedueler_data *schedueler_data)
{
	if (check_time_of_death_list_internal(&schedueler_data->times_of_death)
		== true)
	{
		print_event_sequential(schedueler_data->loger_data.loger_queque,
			e_philosopher_died,
			schedueler_data->times_of_death.philosophers_id
		[schedueler_data->times_of_death.private_list_index]);
		while (*schedueler_data->simulation_over == false)
			;
	}
}
