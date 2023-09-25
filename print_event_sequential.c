/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_event_sequential.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:52:52 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/25 16:52:54 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loger.h"
#include "time.h"
#include <limits.h>

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
		loger_queque.request_queque[aux].event_data.event_id
			= e_simulation_aborted;
	loger_queque.request_queque[aux].requests_comleted = false;
	local_mutex--;
}
