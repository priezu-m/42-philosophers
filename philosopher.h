/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher.h                                                  */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 15:13:37                                            */
/*   Updated:  2023/09/17 14:08:42                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include "loger.h"
# include "schedueler.h"
# include "parameters.h"
# include "events.h"
# include <stdbool.h>

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
	int						philosopher_number;
	bool					launch_aborted;
}t_philosopher;

# pragma clang diagnostic pop

#endif
