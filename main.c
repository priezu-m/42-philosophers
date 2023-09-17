/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.c                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 20:12:31                                            */
/*   Updated:  2023/09/17 17:18:57                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include "philosopher.h"
#include "schedueler.h"
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

typedef struct s_simulation_data
{
	t_parameters			parameters;
	t_schedueler_data		schedueler_data;
	t_loger_data			loger_data;
	t_philosopher			*philosopher_list;
}t_simulation_data;

static t_simulation_data	get_simulation_data(int argc, char **argv)
{
	static _Atomic volatile bool	simulation_over = false;
	t_simulation_data				simulation_data;

	simulation_data.parameters = get_parameters(argc, argv);
	if (simulation_data.parameters.parameters_valid == false)
		return (simulation_data);
	simulation_data.schedueler_data = get_schedueler_data(
			simulation_data.parameters.number_of_philosophers,
			&simulation_over);
	simulation_data.loger_data = get_loger_data(&simulation_over,
			simulation_data.parameters.number_of_meals_needed,
			simulation_data.parameters.number_of_philosophers);
	simulation_data.philosopher_list = get_philosopher_list(&simulation_over,
			simulation_data.parameters,
			simulation_data.schedueler_data,
			simulation_data.loger_data.loger_queque);
	return (simulation_data);
}

static bool	simulation_data_valid(t_simulation_data simulation_data)
{
	if ((schedueler_data_valid(simulation_data.schedueler_data) == false)
		|| (loger_data_valid(simulation_data.loger_data) == false)
		|| (philosopher_list_valid(simulation_data.philosopher_list) == false))
	{
		return (false);
	}
	return (true);
}

static void	destroy_simulation_data(t_simulation_data simulation_data)
{
	destroy_philosopher_list(simulation_data.philosopher_list);
	destroy_loger_data(simulation_data.loger_data);
	destroy_schedueler_data(simulation_data.schedueler_data);
}

static void	launch_and_join_threads(t_simulation_data simulation_data)
{
	launch_schedueler(&simulation_data.schedueler_data);
	if (simulation_data.schedueler_data.launch_aborted == true)
	{
		printf("Failed to launch schedueler thread, aborting.\n");
		return ;
	}
	launch_loger(&simulation_data.loger_data);
	if (simulation_data.loger_data.launch_aborted == true)
	{
		*simulation_data.schedueler_data.simulation_over = true;
		printf("Failed to launch loger thread, aborting.\n");
		join_schedueler(simulation_data.schedueler_data);
		return ;
	}
	launch_and_join_philosophers(simulation_data.philosopher_list);
	join_schedueler(simulation_data.schedueler_data);
	join_loger(simulation_data.loger_data);
}

int	main(int argc, char **argv)
{
	t_simulation_data	simulation_data;

	simulation_data = get_simulation_data(argc, argv);
	if (simulation_data.parameters.parameters_valid == false)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
	if (simulation_data_valid(simulation_data) == false)
	{
		destroy_simulation_data(simulation_data);
		printf("Not enough resources to run the simulation.\n");
		return (EXIT_FAILURE);
	}
	launch_and_join_threads(simulation_data);
	destroy_simulation_data(simulation_data);
}

#pragma clang diagnostic pop
