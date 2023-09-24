/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   schedueler_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:19:57 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:19:59 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"

void	schedueler_loop(t_schedueler_data *schedueler_data)
{
	while (*schedueler_data->simulation_over != true)
	{
		if (*schedueler_data->number_of_active_philosophers
			>= NUMBER_OF_ACTIVE_PHILOSOPHERS_WANTED)
		{
			continue ;
		}
		check_fork_yields(schedueler_data);
		check_time_list(&schedueler_data->times_of_finishing_meal,
			schedueler_data->number_of_active_philosophers,
			schedueler_data->mutexs, schedueler_data->mutex_locked_check);
		check_time_list(&schedueler_data->times_of_awaking,
			schedueler_data->number_of_active_philosophers,
			schedueler_data->mutexs, schedueler_data->mutex_locked_check);
		check_time_list(&schedueler_data->times_of_death,
			schedueler_data->number_of_active_philosophers,
			schedueler_data->mutexs, schedueler_data->mutex_locked_check);
	}
}
