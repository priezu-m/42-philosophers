/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: launch_and_join_philosophers.c                                 */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 17:56:15                                            */
/*   Updated:  2023/09/17 18:06:32                                            */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	launch_and_join_philosophers(t_philosopher *philosopher_list)
{
	const int	number_of_philosophers = philosopher_list[0].philosopher_number;
	int			i;

	i = 0;
	while (i < number_of_philosophers)
	{
		if (pthread_create(&philosopher_list[i].thread_id, NULL,
				philosopher_routine, &philosopher_list[i]) != 0)
		{
			printf("Failed to launch philosopher %d's thread, aborting.\n", i + 1);
			*philosopher_list[i].simulation_over = true;
			philosopher_list[i].launch_aborted = true;
			break ;
		}
		i++;
	}
	i = 0;
	while (i < number_of_philosophers)
	{
		if (philosopher_list[i].launch_aborted == true)
			return ;
		pthread_join(philosopher_list[i].thread_id, NULL);
		i++;
	}
}

#pragma clang diagnostic pop
