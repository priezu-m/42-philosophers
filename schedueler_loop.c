/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: schedueler_loop.c                                              */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/24 17:44:01                                            */
/*   Updated:  2023/09/24 17:44:58                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	schedueler_loop(t_schedueler_data *schedueler_data)
{
	while (*schedueler_data->simulation_over != true)
	{
		if (*schedueler_data->number_of_active_philosophers
			>= NUMBER_OF_ACTIVE_PHILOSOPHERS_WANTED)
		{
			continue ;
		}
		check_fork_yields(schedueler_data);
		check_time_list(&schedueler_data->times_of_finishing_meal,
			schedueler_data->number_of_active_philosophers,
			schedueler_data->mutexs, schedueler_data->mutex_locked_check);
		check_time_list(&schedueler_data->times_of_awaking,
			schedueler_data->number_of_active_philosophers,
			schedueler_data->mutexs, schedueler_data->mutex_locked_check);
		check_time_list(&schedueler_data->times_of_death,
			schedueler_data->number_of_active_philosophers,
			schedueler_data->mutexs, schedueler_data->mutex_locked_check);
	}
}

#pragma clang diagnostic pop
