/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_action_no_ownership_transfer.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:40 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:21:44 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_ACTION_NO_OWNERSHIP_TRANSFER_H
# define MUTEX_ACTION_NO_OWNERSHIP_TRANSFER_H

# include <pthread.h>
# include <stdbool.h>

typedef enum e_mutex_action
{
	e_mutex_unlock,
	e_mutex_lock
}t_mutex_action;

void				mutex_action_no_ownership_transfer(t_mutex_action action,
						pthread_mutex_t *mutex,
						volatile _Atomic bool *mutex_locked);

#endif
