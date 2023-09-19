/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: time.h                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 14:51:08                                            */
/*   Updated:  2023/09/19 17:06:59                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

;
# pragma clang diagnostic push
# pragma clang diagnostic warning "-Weverything"
# pragma clang diagnostic ignored "-Wempty-translation-unit"
# pragma clang diagnostic ignored "-Wunused-macros"

typedef enum e_get_or_set_current_time
{
	e_get_current_time,
	e_set_current_time_as_origin
}t_get_or_set_current_time;

unsigned long int	get_set_current_time(t_get_or_set_current_time	get_or_set);

# pragma clang diagnostic pop

#endif
