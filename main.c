/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.c                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 20:12:31                                            */
/*   Updated:  2023/09/17 14:10:55                                            */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "schedueler.h"
#include <stdlib.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

int	main(int argc, char **argv)
{
	const t_parameters		parameters = get_parameters(argc, argv);
	_Atomic volatile bool	simulation_over;
	t_schedueler_data		schedueler_data;
	t_loger_data			loger_data;

	if (parameters.parameters_valid == false)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	simulation_over = false;
	schedueler_data = get_schedueler_data(parameters.number_of_philosophers,
			&simulation_over);
//	loger_data = 
	if (schedueler_data_valid(schedueler_data) == false)
	{
		printf("Not enough resources to run the simulation.\n");
		destroy_schedueler_data(schedueler_data);
		return (EXIT_FAILURE);
	}
	destroy_schedueler_data(schedueler_data);
}

#pragma clang diagnostic pop
