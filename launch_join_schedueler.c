/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: launch_join_schedueler.c                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 17:29:26                                            */
/*   Updated:  2023/09/17 17:35:49                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include <pthread.h>
#include <stdbool.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

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

#pragma clang diagnostic pop
