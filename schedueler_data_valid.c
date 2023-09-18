/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: schedueler_data_valid.c                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 13:22:00                                            */
/*   Updated:  2023/09/17 22:51:00                                            */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "schedueler.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

bool	schedueler_data_valid(t_schedueler_data schedueler_data)
{
	const int	number_of_philosophers = schedueler_data.number_of_philosophers;

	if (
		schedueler_data.number_of_active_philosophers == NULL 
		|| schedueler_data.mutex_initialized == NULL
		|| schedueler_data.mutex_locked_check == NULL
		|| schedueler_data.simulation_over == NULL
		|| schedueler_data.fork_sate == NULL
		|| schedueler_data.yields.queque_index == NULL
		|| schedueler_data.yields.yielder_ids == NULL
		|| schedueler_data.times_of_death.list_index == NULL
		|| schedueler_data.times_of_death.times == NULL
		|| schedueler_data.times_of_awaking.list_index == NULL
		|| schedueler_data.times_of_awaking.times == NULL
		|| schedueler_data.times_of_finishing_meal.list_index == NULL
		|| schedueler_data.times_of_finishing_meal.times == NULL
	)
	{
		return (false);
	}
	if (schedueler_data.mutex_initialized[number_of_philosophers - 1] == false)
		return (false);
	return (true);
}

#pragma clang diagnostic pop
