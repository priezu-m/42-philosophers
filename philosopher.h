/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher.h                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 15:13:37                                            */
/*   Updated:  2023/09/18 19:36:32                                            */
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

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"
# pragma clang diagnostic ignored "-Wc11-extensions"

typedef struct s_philosopher
{
	volatile _Atomic bool	*simulation_over;
	t_parameters			parameters;
	t_schedueler_data		schedueler_data;
	t_loger_queque			loger_queque;
	pthread_t				thread_id;
	int						philosopher_number;
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

# pragma clang diagnostic pop

#endif
