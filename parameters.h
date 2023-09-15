/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parameters.h                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 15:08:46                                            */
/*   Updated:  2023/09/15 20:24:02                                            */
/*                                                                            */
/* ************************************************************************** */

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

#ifndef PARAMETERS_H
# define PARAMETERS_H

#include <stdbool.h>

typedef struct s_parameters
{
	int		number_of_philosophers;
	int		time_to_starve;
	int		time_eating;
	int		time_sleeping;
	int		number_of_meals_needed;
	bool	parameters_valid;
}t_parameters;

t_parameters	get_parameters(int argc, char **argv);
void			print_usage(void);

#endif

#pragma clang diagnostic pop
