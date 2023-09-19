/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: check_time_list.c                                              */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 14:35:10                                            */
/*   Updated:  2023/09/19 17:12:47                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include "time.h"
#include "mutex_sequential_action.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	check_time_list(t_time_list *time_list,
		int volatile _Atomic *number_of_active_philosophers,
		pthread_mutex_t *mutexs)
{
	int	i;
	int	id;

	i = time_list->private_list_index;
	id = time_list->philosophers_id[i];
	if (id == 0)
		return ;
	if (time_list->times[i]
		< get_set_current_time(e_get_current_time))
	{
		return ;
	}
	time_list->philosophers_id[i] = 0;
	time_list->private_list_index++;
	time_list->private_list_index %= time_list->list_size;
	(*number_of_active_philosophers)++;
	mutex_sequential_action(e_mutex_unlock,
		&mutexs[id - 1]);
}

#pragma clang diagnostic pop
