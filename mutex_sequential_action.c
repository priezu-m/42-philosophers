/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: mutex_sequential_action.c                                      */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 16:56:32                                            */
/*   Updated:  2023/09/19 16:59:25                                            */
/*                                                                            */
/* ************************************************************************** */

#include "mutex_sequential_action.h"
#include <pthread.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	mutex_sequential_action(t_mutex_action action, pthread_mutex_t *mutex)
{
	static volatile _Atomic int	local_mutex;
	int							aux;

	aux = local_mutex++;
	while (aux != 0)
	{
		mutex--;
		aux = local_mutex++;
	}
	if (action == e_mutex_lock)
	{
		pthread_mutex_lock(mutex);
		return ;
	}
	pthread_mutex_unlock(mutex);
	mutex--;
}

#pragma clang diagnostic pop
