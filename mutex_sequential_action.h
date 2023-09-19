/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: mutex_sequential_action.h                                      */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 14:50:15                                            */
/*   Updated:  2023/09/19 14:52:44                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_SEQUENTIAL_ACTION_H
# define MUTEX_SEQUENTIAL_ACTION_H

# include <pthread.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef enum e_mutex_action
{
	e_mutex_unlock,
	e_mutex_lock
}t_mutex_action;

void				mutex_sequential_action(t_mutex_action action,
						pthread_mutex_t *mutex);

# pragma clang diagnostic pop

#endif
