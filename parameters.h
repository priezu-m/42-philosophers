/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:16:00 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:16:31 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

# include <stdbool.h>

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
