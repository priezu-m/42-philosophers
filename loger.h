/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: loger.h                                                        */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 14:23:18                                            */
/*   Updated:  2023/09/15 20:14:40                                            */
/*                                                                            */
/* ************************************************************************** */

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Wc11-extensions"

#ifndef LOGER_H
# define LOGER_H

# include "events.h"
# include <stdbool.h>

typedef struct s_event_data
{
	t_events_e			event_id;
	int					issuer_id;
	unsigned long int	time_of_issuing;
}t_event_data;

//requests_comleted must be initialized to true at the beginning of the simulation
typedef struct s_log_request
{
	volatile _Atomic bool	requests_comleted;
	volatile t_event_data	event_data;
}t_log_request;

typedef struct s_loger_queque
{
	int						queque_size;
	t_log_request			*request_queque;
	volatile _Atomic int	queque_index;
	int						private_queque_index;
}t_loger_queque;

typedef struct loger_data
{
	volatile _Atomic bool	*simulation_over;
	t_loger_queque			loger_queque;
	int						last_needed_meals_needed;
	bool					launch_aborted;
}t_loger_data;

#endif

#pragma clang diagnostic pop
