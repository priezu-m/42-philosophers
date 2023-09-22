/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: parameters.c                                                   */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/16 14:24:48                                            */
/*   Updated:  2023/09/20 21:21:47                                            */
/*                                                                            */
/* ************************************************************************** */

#include "parameters.h"
#include <limits.h>
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

static void	print_usage_part_one(void)
{
	printf(
		"Usage: ./philo NUMBER_OF_PHILOSOPHERS TIME_TO_STARVE TIME_EATING\n"
		"\tTIME_SLEEPING [NUMBER_OF_MEALS_EACH_PHILOSOPHER_MUST_EAT]\n\n"
		"Simulate NUMBER_OF_PHILOSOPHERS philosophers, with each philosopher\n"
		"in a round table alternating between eating, sleeping, and thinking.\n"
		"At the beginning of the simulation, each philosopher has a fork on\n"
		"their right. Since the table is round, if at least two philosophers\n"
		"are sitting, each philosopher starts with a fork on their right and\n"
		"left. Philosophers need to take two forks before they can begin\n"
		"eating. Philosophers can only take the forks to their right and\n"
		"left and must return them to their original positions after they\n"
		"finish eating. Philosophers eat for TIME_EATING milliseconds,\n"
		"then sleep for TIME_SLEEPING milliseconds, and finally, they\n"
		"think until they can eat again. Philosophers are unaware of the\n"
		"state (eating, sleeping, thinking) of the other philosophers. If\n"
		"TIME_TO_STARVE milliseconds pass since a philosopher last started\n"
		"eating (or since the simulation began), the philosopher dies, and\n"
		);
}

static void	print_usage_part_two(void)
{
	printf(
		"the simulation ends. If all philosophers have eaten\n"
		"NUMBER_OF_MEALS_EACH_PHILOSOPHER_MUST_EAT meals, the simulation\n"
		"ends. If this argument is not specified, the simulation will run\n"
		"until a philosopher dies. Each philosopher is simulated whit a\n"
		"different thread of execution.\n\n"
		"Note: All parameters must be strings of digits forming a number\n"
		"less than 2^32. And NUMBER_OF_PHILOSOPHERS must be at least one.\n"
		);
}

void	print_usage(void)
{
	print_usage_part_one();
	print_usage_part_two();
}

static int	trunc_atoi(char *str)
{
	int	res;

	res = 0;
	if (*str == '\0')
		return (INT_MIN);
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (INT_MIN);
		if ((INT_MAX / 10) < res)
			return (INT_MIN);
		if ((INT_MAX - (*str - '0')) < (res * 10))
			return (INT_MIN);
		res *= 10;
		res += *str - '0';
		str++;
	}
	return (res);
}

t_parameters	get_parameters(int argc, char **argv)
{
	t_parameters	parameters;

	if (argc < 5 || argc > 6)
		return ((t_parameters){.parameters_valid = false});
	parameters.number_of_philosophers = trunc_atoi(argv[1]);
	parameters.time_to_starve = trunc_atoi(argv[2]);
	parameters.time_eating = trunc_atoi(argv[3]);
	parameters.time_sleeping = trunc_atoi(argv[4]);
	if (argc == 6)
		parameters.number_of_meals_needed = trunc_atoi(argv[5]);
	else
		parameters.number_of_meals_needed = -1;
	if (parameters.number_of_philosophers < 1
		|| parameters.time_to_starve == INT_MIN
		|| parameters.time_eating == INT_MIN
		|| parameters.time_sleeping == INT_MIN
		|| parameters.number_of_meals_needed == INT_MIN)
	{
		return ((t_parameters){.parameters_valid = false});
	}
	parameters.parameters_valid = true;
	return (parameters);
}

#pragma clang diagnostic pop
