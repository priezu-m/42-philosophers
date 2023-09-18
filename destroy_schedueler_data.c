/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: destroy_schedueler_data.c                                      */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/16 16:24:59                                            */
/*   Updated:  2023/09/17 22:46:27                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

static void	destroy_mutexs(pthread_mutex_t *mutexs, bool *mutex_initialized,
		volatile _Atomic bool *mutex_locked_check, int number_of_philosophers)
{
	int	i;

	if (mutexs == NULL || mutex_initialized == NULL
		|| mutex_locked_check == NULL)
	{
		return ;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		if (mutex_initialized[i] == false)
			return ;
		if (mutex_locked_check[i] == true)
			pthread_mutex_unlock(&mutexs[i]);
		pthread_mutex_destroy(&mutexs[i]);
		i++;
	}
}

static void	destroy_time_list(t_time_list time_list)
{
	free((void *)(intptr_t)time_list.list_index);
	free((void *)(intptr_t)time_list.times);
}

static void	destroy_yield_queque(t_fork_yield_queque yield_queque)
{
	free((void *)(intptr_t)yield_queque.queque_index);
	free((void *)(intptr_t)yield_queque.yielder_ids);
}

void	destroy_schedueler_data(t_schedueler_data schedueler_data)
{
	destroy_mutexs(schedueler_data.mutexs, schedueler_data.mutex_initialized,
		schedueler_data.mutex_locked_check,
		schedueler_data.number_of_philosophers);
	free((void *)(intptr_t)schedueler_data.mutex_initialized); 
	free((void *)(intptr_t)schedueler_data.number_of_active_philosophers);
	free((void *)(intptr_t)schedueler_data.mutexs);
	free((void *)(intptr_t)schedueler_data.mutex_locked_check);
	free((void *)(intptr_t)schedueler_data.fork_sate);
	destroy_yield_queque(schedueler_data.yields);
	destroy_time_list(schedueler_data.times_of_death);
	destroy_time_list(schedueler_data.times_of_awaking);
	destroy_time_list(schedueler_data.times_of_finishing_meal);
}

#pragma clang diagnostic pop
