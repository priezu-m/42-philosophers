/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_join_loger.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:19:46 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:20:01 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "loger.h"
#include <pthread.h>
#include <stdbool.h>

void	launch_loger(t_loger_data *loger_data)
{
	if (pthread_create(&loger_data->thread_id, NULL, loger_routine, loger_data)
		!= 0)
		loger_data->launch_aborted = true;
}

void	join_loger(t_loger_data loger_data)
{
	pthread_join(loger_data.thread_id, NULL);
}
