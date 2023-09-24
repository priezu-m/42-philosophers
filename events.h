/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Filename: events.h                                                       */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:21:17 by priezu-m          #+#    #+#             */
/*   Updated:  2023/09/24 19:11:25                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

typedef enum e_event
{
	e_default_event = 0,
	e_took_forks,
	e_left_forks,
	e_began_to_eat,
	e_finished_last_needed_meal,
	e_began_to_sleep,
	e_began_to_think,
	e_simulation_began,
	e_simulation_aborted,
	e_philosopher_died
}t_event;

#endif
