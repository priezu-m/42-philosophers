/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: loger.h                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 14:23:18                                            */
/*   Updated:  2023/09/23 19:33:26                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOGER_H
# define LOGER_H

# include "events.h"
# include <stdbool.h>
# include <pthread.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"
# pragma clang diagnostic ignored "-Wc11-extensions"

# define BUFFER_SIZE 10000

typedef enum e_buffer_action
{
	e_flush_buffer,
	e_push_to_buffer
}t_buffer_action;

typedef struct s_event_data
{
	t_event				event_id;
	int					issuer_id;
	unsigned long int	time_of_issuing;
}t_event_data;

typedef struct s_log_request
{
	volatile _Atomic bool	requests_comleted;
	volatile t_event_data	event_data;
}t_log_request;

typedef struct s_loger_queque
{
	int						queque_size;
	t_log_request			*request_queque;
	volatile _Atomic int	*queque_index;
	int						private_queque_index;
}t_loger_queque;

typedef struct loger_data
{
	volatile _Atomic bool	*simulation_over;
	t_loger_queque			loger_queque;
	pthread_t				thread_id;
	int						last_needed_meals_needed;
	bool					launch_aborted;
}t_loger_data;

t_loger_data	get_loger_data(volatile _Atomic bool *simulation_over,
					int number_of_philosophers);
void			destroy_loger_data(t_loger_data loger_data);
bool			loger_data_valid(t_loger_data loger_data);
void			launch_loger(t_loger_data *loger_data);
void			join_loger(t_loger_data loger_data);
void			*loger_routine(void *arg);
void			print_event_sequential(t_loger_queque loger_queque,
					t_event event,
					int issuer_id);
void			log_buffer(t_buffer_action action, char *msg, int msg_size);
void			push_data_to_buffer(t_event_data data);

# pragma clang diagnostic pop

#endif
