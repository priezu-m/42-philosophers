/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:50:19 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/25 16:50:22 by priezu-m         ###   ########.fr       */
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
