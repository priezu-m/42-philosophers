/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_join_schedueler.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:17 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:21:21 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include <pthread.h>
#include <stdbool.h>

void	launch_schedueler(t_schedueler_data *schedueler_data)
{
	if (pthread_create(&schedueler_data->thread_id, NULL, schedueler_routine,
			schedueler_data) != 0)
		schedueler_data->launch_aborted = true;
}

void	join_schedueler(t_schedueler_data schedueler_data)
{
	pthread_join(schedueler_data.thread_id, NULL);
}
