/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: philosopher_routine_functions.c                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 17:15:47                                            */
/*   Updated:  2023/09/19 17:17:24                                            */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher.h"
#include "time.h"
#include "mutex_sequential_action.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

void	think(t_philosopher *self)
{
	if (simulation_over(self) == true)
		return ;
	//print thinking
}

void	eat(t_philosopher *self)
{
	int						aux;
	const int				id = self->philosopher_number;
	const unsigned long int	current_time
		= get_set_current_time(e_get_current_time);

	if (simulation_over(self))
		return ;
	self->time_of_death = current_time
		+ (((unsigned)self->parameters.time_to_starve) * 1000ul);
	aux = (*self->schedueler_data.times_of_death.list_index)++;
	*self->schedueler_data.times_of_death.list_index
		%= self->schedueler_data.times_of_death.list_size;
	aux %= self->schedueler_data.times_of_death.list_size;
	self->schedueler_data.times_of_death.times[aux] = self->time_of_death;
	self->schedueler_data.times_of_death.philosophers_id[aux] = id;
	aux = (*self->schedueler_data.times_of_finishing_meal.list_index)++;
	*self->schedueler_data.times_of_finishing_meal.list_index
		%= self->schedueler_data.times_of_finishing_meal.list_size;
	aux %= self->schedueler_data.times_of_finishing_meal.list_size;
	self->schedueler_data.times_of_finishing_meal.times[aux]
		= current_time + (((unsigned)self->parameters.time_eating) * 1000ul);
	self->schedueler_data.times_of_finishing_meal.philosophers_id[aux] = id;
	//print eat
	block_self(self);
}

void	sleep_self(t_philosopher *self)
{
	int						aux;
	const int				id = self->philosopher_number;
	const unsigned long int	current_time
		= get_set_current_time(e_get_current_time);

	if (simulation_over(self))
		return ;
	aux = (*self->schedueler_data.times_of_awaking.list_index)++;
	*self->schedueler_data.times_of_awaking.list_index
		%= self->schedueler_data.times_of_awaking.list_size;
	aux %= self->schedueler_data.times_of_awaking.list_size;
	self->schedueler_data.times_of_awaking.times[aux]
		= current_time + (((unsigned)self->parameters.time_sleeping) * 1000ul);
	self->schedueler_data.times_of_awaking.philosophers_id[aux] = id;
	//print sleep
	block_self(self);
}

#pragma clang diagnostic pop
