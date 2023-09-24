/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_action_no_ownership_transfer.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:17 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:21:21 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_action_no_ownership_transfer.h"
#include <pthread.h>
#include <stdbool.h>

void	mutex_action_no_ownership_transfer(t_mutex_action action,
		pthread_mutex_t *mutex,
		volatile _Atomic bool *mutex_locked)
{
	if (action == e_mutex_lock)
	{
		while (*mutex_locked == false)
			;
		pthread_mutex_lock(mutex);
		pthread_mutex_unlock(mutex);
		*mutex_locked = false;
		return ;
	}
	pthread_mutex_unlock(mutex);
	while (*mutex_locked == true)
		;
	pthread_mutex_lock(mutex);
	*mutex_locked = true;
}
