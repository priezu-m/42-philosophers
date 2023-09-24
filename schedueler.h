/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: schedueler.h                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 14:40:25                                            */
/*   Updated:  2023/09/24 17:44:27                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCHEDUELER_H
# define SCHEDUELER_H

# include <pthread.h>
# include <stdbool.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"
# pragma clang diagnostic ignored "-Wc11-extensions"

# define NUMBER_OF_ACTIVE_PHILOSOPHERS_WANTED 4

typedef enum e_fork_state
{
	e_default_fork_state = 0,
	e_requested = -1,
	e_gotten = 1,
	e_requested_and_gotten = 2,
	e_gotten_and_requested = 3
}t_fork_state;

typedef struct s_fork_yield_queque
{
	volatile _Atomic int	*yielder_ids;
	int						queque_size;
	volatile _Atomic int	*queque_index;
	int						private_queque_index;
}t_fork_yield_queque;

typedef struct s_time_list
{
	volatile _Atomic unsigned long int	*times;
	volatile _Atomic int				*philosophers_id;
	unsigned int						list_size;
	volatile _Atomic int				*list_index;
	int									private_list_index;
}t_time_list;

typedef struct s_schedueler_data
{
	volatile _Atomic int				*number_of_active_philosophers;
	pthread_mutex_t						*mutexs;
	bool								*mutex_initialized;
	volatile _Atomic bool				*mutex_locked_check;
	volatile _Atomic bool				*simulation_over;
	volatile _Atomic	t_fork_state	(*fork_sate)[2];
	t_fork_yield_queque					yields;
	t_time_list							times_of_death;
	t_time_list							times_of_awaking;
	t_time_list							times_of_finishing_meal;
	pthread_t							thread_id;
	int									number_of_philosophers;
	bool								launch_aborted;
}t_schedueler_data;

t_schedueler_data	get_schedueler_data(int number_of_philosophers,
						volatile _Atomic bool *simulation_over);
void				destroy_schedueler_data(t_schedueler_data schedueler_data);
bool				schedueler_data_valid(t_schedueler_data schedueler_data);
void				launch_schedueler(t_schedueler_data *schedueler_data);
void				join_schedueler(t_schedueler_data schedueler_data);
void				*schedueler_routine(void *schedueler_data);
void				give_initial_forks(
						volatile _Atomic t_fork_state (*fork_sate)[2],
						int number_of_philosophers);
void				check_fork_yields(t_schedueler_data *schedueler_data);
void				yield_left_fork(t_schedueler_data *schedueler_data,
						int reciver);
void				yield_right_fork(t_schedueler_data *schedueler_data,
						int reciver);
void				check_time_list(
						t_time_list *time_list,
						int volatile _Atomic *number_of_active_philosophers,
						pthread_mutex_t *mutexs,
						volatile _Atomic bool *mutex_locked_check);
void				schedueler_loop(t_schedueler_data *schedueler_data);

# pragma clang diagnostic pop

#endif
