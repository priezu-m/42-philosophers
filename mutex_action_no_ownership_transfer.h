/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: mutex_action_no_ownership_transfer.h                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 14:50:15                                            */
/*   Updated:  2023/09/24 17:43:14                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef MUTEX_ACTION_NO_OWNERSHIP_TRANSFER_H
# define MUTEX_ACTION_NO_OWNERSHIP_TRANSFER_H

# include <pthread.h>
# include <stdbool.h>

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"
# pragma clang diagnostic ignored "-Wc11-extensions"

typedef enum e_mutex_action
{
	e_mutex_unlock,
	e_mutex_lock
}t_mutex_action;

void				mutex_action_no_ownership_transfer(t_mutex_action action,
						pthread_mutex_t *mutex,
						volatile _Atomic bool *mutex_locked);

# pragma clang diagnostic pop

#endif
