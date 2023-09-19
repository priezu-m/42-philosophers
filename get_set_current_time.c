/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: get_set_current_time.c                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 14:36:04                                            */
/*   Updated:  2023/09/19 17:19:35                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include "time.h"
#include <sys/time.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

unsigned long int	get_set_current_time(t_get_or_set_current_time get_or_set)
{
	static struct timeval	origin;
	struct timeval			current;
	struct timeval			diff;

	if (get_or_set == e_set_current_time_as_origin)
	{
		gettimeofday(&origin, NULL);
		return (0);
	}
	gettimeofday(&current, NULL);
	timersub(&current, &origin, &diff);
	//todo add check that we can handle the amount of time that has passed,
	//else end the simulation
	return (((unsigned long)diff.tv_sec * 1000000ul)
		+ ((unsigned long)diff.tv_usec));
}

#pragma clang diagnostic pop
