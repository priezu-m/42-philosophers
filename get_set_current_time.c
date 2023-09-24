/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set_current_time.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:57 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:22:00 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"
#include "time.h"
#include "loger.h"
#include <sys/time.h>
#include <limits.h>

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
	if (((ULONG_MAX / 1000000ul) < ((unsigned long)diff.tv_sec))
		|| ((ULONG_MAX - (unsigned long)diff.tv_usec)
			<= ((unsigned long)diff.tv_sec * 1000000ul)))
	{
		return (ULONG_MAX);
	}
	return (((unsigned long)diff.tv_sec * 1000000ul)
		+ ((unsigned long)diff.tv_usec));
}
