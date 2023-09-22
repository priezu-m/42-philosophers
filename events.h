/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: events.h                                                       */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 12:03:08                                            */
/*   Updated:  2023/09/19 17:30:45                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENTS_H
# define EVENTS_H

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef enum e_event
{
	e_default_event = 0,
	e_took_forks,
	e_left_forks,
	e_began_to_eat,
	e_began_to_eat_last_needed_meal,
	e_began_to_sleep,
	e_began_to_think,
	e_simulation_began,
	e_simulation_aborted,
	e_philosopher_died
}t_event;

# pragma clang diagnostic pop

#endif
