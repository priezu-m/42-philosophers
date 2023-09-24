/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: mutex_action_no_ownership_transfer.c                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 16:56:32                                            */
/*   Updated:  2023/09/23 22:55:48                                            */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_action_no_ownership_transfer.h"
#include <pthread.h>
#include <stdbool.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

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

#pragma clang diagnostic pop
