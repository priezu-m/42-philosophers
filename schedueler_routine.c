/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: schedueler_routine.c                                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:27:52                                            */
/*   Updated:  2023/09/24 17:44:59                                            */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_action_no_ownership_transfer.h"
#include "schedueler.h"
#include "time.h"
#include "mutex_action_no_ownership_transfer.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

static void	unlock_uneven(t_schedueler_data *schedueler_data)
{
	int	i;

	i = 0;
	while (i < schedueler_data->number_of_philosophers
		&& *schedueler_data->simulation_over != true)
	{
		if (*schedueler_data->number_of_active_philosophers
			>= NUMBER_OF_ACTIVE_PHILOSOPHERS_WANTED)
		{
			continue ;
		}
		(*schedueler_data->number_of_active_philosophers)++;
		mutex_action_no_ownership_transfer(e_mutex_unlock,
			&schedueler_data->mutexs[i],
			&schedueler_data->mutex_locked_check[i]);
		i += 2;
	}
}

static void	unlock_even(t_schedueler_data *schedueler_data)
{
	int	i;

	i = 1;
	while (i < schedueler_data->number_of_philosophers
		&& *schedueler_data->simulation_over != true)
	{
		if (*schedueler_data->number_of_active_philosophers
			>= NUMBER_OF_ACTIVE_PHILOSOPHERS_WANTED)
		{
			continue ;
		}
		(*schedueler_data->number_of_active_philosophers)++;
		mutex_action_no_ownership_transfer(e_mutex_unlock,
			&schedueler_data->mutexs[i],
			&schedueler_data->mutex_locked_check[i]);
		i += 2;
	}
}

static void	unlock_all(t_schedueler_data *schedueler_data)
{
	int	i;

	i = 0;
	while (i < schedueler_data->number_of_philosophers)
	{
		pthread_mutex_unlock(&schedueler_data->mutexs[i]);
		i++;
	}
}

static void	lock_mutexs(t_schedueler_data *schedueler_data)
{
	int	i;

	i = 0;
	while (i < schedueler_data->number_of_philosophers)
	{
		pthread_mutex_lock(&schedueler_data->mutexs[i]);
		schedueler_data->mutex_locked_check[i] = true;
		i++;
	}
}

void	*schedueler_routine(void *arg)
{
	t_schedueler_data	*schedueler_data;

	schedueler_data = arg;
	lock_mutexs(schedueler_data);
	give_initial_forks(schedueler_data->fork_sate,
		schedueler_data->number_of_philosophers);
	while ((*schedueler_data->number_of_active_philosophers != 0)
		&& (*schedueler_data->simulation_over != true))
		;
	get_set_current_time(e_set_current_time_as_origin);
	unlock_uneven(schedueler_data);
	unlock_even(schedueler_data);
	schedueler_loop(schedueler_data);
	unlock_all(schedueler_data);
	return (NULL);
}

#pragma clang diagnostic pop
