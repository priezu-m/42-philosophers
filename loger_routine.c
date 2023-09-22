/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: loger_routine.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:23:00                                            */
/*   Updated:  2023/09/22 13:26:45                                            */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "loger.h"
#include "time.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	print_event_sequential(t_loger_queque loger_queque, t_event event,
		int issuer_id)
{
	static _Atomic int	local_mutex;
	int					aux;
	unsigned long int	current_time;

	aux = local_mutex++;
	while (aux != 0)
	{
		local_mutex--;
		aux = local_mutex++;
	}
	aux = (*loger_queque.queque_index)++;
	aux %= loger_queque.queque_size;
	*loger_queque.queque_index %= loger_queque.queque_size;
	while (loger_queque.request_queque[aux].requests_comleted == false)
		;
	loger_queque.request_queque[aux].event_data.event_id = event;
	loger_queque.request_queque[aux].event_data.issuer_id = issuer_id;
	current_time = get_set_current_time(e_get_current_time);
	loger_queque.request_queque[aux].event_data.time_of_issuing
		= current_time / 1000;
	if (current_time == ULONG_MAX)
	{
		loger_queque.request_queque[aux].event_data.event_id
			= e_simulation_aborted;
	}
	loger_queque.request_queque[aux].requests_comleted = false;
	local_mutex--;
}

static void	check_special_events(t_loger_data *loger_data)
{
	int		i;
	t_event	event;

	i = loger_data->loger_queque.private_queque_index;
	event = loger_data->loger_queque.request_queque[i].event_data.event_id;
	if (event == e_simulation_aborted || event == e_philosopher_died)
	{
		*loger_data->simulation_over = true;
		return ;
	}
	if (event == e_began_to_eat_last_needed_meal)
	{
		loger_data->last_needed_meals_needed--;
		if (loger_data->last_needed_meals_needed == 0)
		{
			*loger_data->simulation_over = true;
			return ;
		}
	}
}

static void	increment_private_index(t_loger_data *loger_data)
{
	loger_data->loger_queque.private_queque_index++;
	loger_data->loger_queque.private_queque_index
		%= loger_data->loger_queque.queque_size;
}

static void	set_all_to_completed(t_loger_queque *loger_queque)
{
	int	i;

	i = 0;
	while (i < loger_queque->queque_size)
	{
		loger_queque->request_queque[i].requests_comleted = true;
		i++;
	}
}

void	*loger_routine(void *arg)
{
	t_loger_data	*loger_data;
	int				i;

	loger_data = arg;
	while (*(loger_data->simulation_over) != true)
	{
		i = loger_data->loger_queque.private_queque_index;
		if ((loger_data->loger_queque.request_queque[i].requests_comleted)
			== true)
		{
			log_buffer(e_flush_buffer, NULL, 0);
			continue ;
		}
		push_data_to_buffer(
			loger_data->loger_queque.request_queque[i].event_data);
		check_special_events(loger_data);
		loger_data->loger_queque.request_queque[i].requests_comleted = true;
		increment_private_index(loger_data);
	}
	log_buffer(e_flush_buffer, NULL, 0);
	set_all_to_completed(&loger_data->loger_queque);
	return (NULL);
}

#pragma clang diagnostic pop
