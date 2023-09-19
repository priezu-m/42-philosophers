/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_schedueler_data.c                                          */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/16 14:51:38                                            */
/*   Updated:  2023/09/19 13:49:02                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include "stdlib.h"
#include <bits/types.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

static t_fork_yield_queque	get_yield_queque(int number_of_philosophers)
{
	t_fork_yield_queque	yield_queque;

	yield_queque.private_queque_index = 0;
	yield_queque.queque_size = number_of_philosophers;
	yield_queque.queque_index = calloc(1, sizeof(volatile _Atomic int));
	yield_queque.yielder_ids = calloc((unsigned)number_of_philosophers,
			sizeof(volatile _Atomic int));
	return (yield_queque);
}

static t_time_list	get_time_list(int number_of_philosophers)
{
	t_time_list	time_list;

	time_list.private_list_index = 0;
	time_list.list_size = ((unsigned)number_of_philosophers) * 2;
	time_list.list_index = calloc(1, sizeof(volatile _Atomic int));
	time_list.times = calloc(((unsigned)number_of_philosophers) * 2,
			sizeof(volatile unsigned long int));
	time_list.philosophers_id = calloc(((unsigned)number_of_philosophers) * 2,
			sizeof(volatile _Atomic int));
	return (time_list);
}

static void	init_mutexs(pthread_mutex_t *mutexs, bool *mutex_initialized,
		volatile _Atomic bool *mutex_locked_check, int number_of_philosophers)
{
	int	i;

	if (mutexs == NULL || mutex_initialized == NULL
		|| mutex_locked_check == NULL)
		return ;
	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_mutex_init(&mutexs[i], NULL) != 0)
			return ;
		pthread_mutex_lock(&mutexs[i]);
		mutex_locked_check[i] = true;
		mutex_initialized[i] = true;
		i++;
	}
}

t_schedueler_data	get_schedueler_data(int number_of_philosophers,
						volatile _Atomic bool *simulation_over)
{
	t_schedueler_data	schedueler_data;

	schedueler_data.number_of_active_philosophers = calloc(1,
			sizeof(volatile _Atomic int));
	schedueler_data.mutexs = calloc((unsigned)number_of_philosophers,
			sizeof(pthread_mutex_t));
	schedueler_data.mutex_initialized = calloc((unsigned)number_of_philosophers,
			sizeof(bool));
	schedueler_data.mutex_locked_check = calloc(
			(unsigned)number_of_philosophers,
			sizeof(volatile _Atomic bool));
	schedueler_data.simulation_over = simulation_over;
	schedueler_data.fork_sate = calloc((unsigned)number_of_philosophers,
			sizeof(volatile _Atomic t_fork_state) * 2);
	schedueler_data.yields = get_yield_queque(number_of_philosophers);
	schedueler_data.times_of_death = get_time_list(number_of_philosophers);
	schedueler_data.times_of_awaking = get_time_list(number_of_philosophers);
	schedueler_data.times_of_finishing_meal
		= get_time_list(number_of_philosophers);
	schedueler_data.number_of_philosophers = number_of_philosophers;
	schedueler_data.launch_aborted = false;
	*schedueler_data.number_of_active_philosophers = number_of_philosophers;
	init_mutexs(schedueler_data.mutexs, schedueler_data.mutex_initialized,
		schedueler_data.mutex_locked_check, number_of_philosophers);
	return (schedueler_data);
}

#pragma clang diagnostic pop
