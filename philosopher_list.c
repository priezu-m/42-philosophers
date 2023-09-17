/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher_list.c                                             */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 16:47:27                                            */
/*   Updated:  2023/09/17 16:51:58                                            */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>
#include "philosopher.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

t_philosopher	*get_philosopher_list(volatile _Atomic bool *simulation_over,
					t_parameters parameters, t_schedueler_data schedueler_data,
					t_loger_queque loger_queque)
{
	t_philosopher	*philosopher_list;
	int				i;

	philosopher_list = calloc((unsigned)parameters.number_of_philosophers,
			sizeof(t_philosopher));
	if (philosopher_list == NULL)
		return (philosopher_list);
	i = 0;
	while (i < parameters.number_of_philosophers)
	{
		philosopher_list[i].philosopher_number = i + 1;
		philosopher_list[i].launch_aborted = false;
		philosopher_list[i].loger_queque = loger_queque;
		philosopher_list[i].parameters = parameters;
		philosopher_list[i].schedueler_data = schedueler_data;
		philosopher_list[i].simulation_over = simulation_over;
		i++;
	}
	return (philosopher_list);
}

bool	philosopher_list_valid(t_philosopher *philosopher_list)
{
	if (philosopher_list == NULL)
		return (false);
	return (true);
}

void	destroy_philosopher_list(t_philosopher *philosopher_list)
{
	free(philosopher_list);
}

#pragma clang diagnostic pop
