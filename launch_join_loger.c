/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: launch_join_loger.c                                            */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 17:41:10                                            */
/*   Updated:  2023/09/17 22:44:23                                            */
/*                                                                            */
/* ************************************************************************** */

#include "loger.h"
#include <pthread.h>
#include <stdbool.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

void	launch_loger(t_loger_data *loger_data)
{
	if (pthread_create(&loger_data->thread_id, NULL, loger_routine, loger_data)
		!= 0)
		loger_data->launch_aborted = true;
}

void	join_loger(t_loger_data loger_data)
{
	pthread_join(loger_data.thread_id, NULL);
}

#pragma clang diagnostic pop
