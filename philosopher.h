/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:18:41 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:18:48 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "loger.h"
# include "schedueler.h"
# include "parameters.h"
# include "events.h"
# include <stdbool.h>
# include <pthread.h>

typedef struct s_philosopher
{
	volatile _Atomic bool	*simulation_over;
	t_parameters			parameters;
	t_schedueler_data		schedueler_data;
	t_loger_queque			loger_queque;
	unsigned long int		time_of_death;
	pthread_t				thread_id;
	int						philosopher_number;
	int						time_of_death_position;
	bool					launch_aborted;
}t_philosopher;

t_philosopher	*get_philosopher_list(volatile _Atomic bool *simulation_over,
					t_parameters parameters, t_schedueler_data schedueler_data,
					t_loger_queque loger_queque);
void			destroy_philosopher_list(t_philosopher *philosopher_list);
bool			philosopher_list_valid(t_philosopher *philosopher_list);
void			launch_and_join_philosophers(t_philosopher *philosopher_list);
void			*philosopher_routine(void *arg);
void			initial_block(t_schedueler_data schedueler_data,
					int philosopher_number);
void			get_forks(t_philosopher *self);
void			block_self(t_philosopher *self);
bool			simulation_over(t_philosopher *self);
void			yield_forks_internal(t_fork_yield_queque yield_queque,
					int philo_number);
void			yield_forks(t_philosopher *self);
void			eat(t_philosopher *self);
void			sleep_self(t_philosopher *self);
void			think(t_philosopher *self);

#endif
