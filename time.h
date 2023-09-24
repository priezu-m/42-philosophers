/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:40 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:21:44 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

typedef enum e_get_or_set_current_time
{
	e_get_current_time,
	e_set_current_time_as_origin
}t_get_or_set_current_time;

unsigned long int	get_set_current_time(t_get_or_set_current_time	get_or_set);

#endif
