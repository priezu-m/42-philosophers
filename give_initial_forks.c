/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   give_initial_forks.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 18:16:27 by priezu-m          #+#    #+#             */
/*   Updated: 2023/09/24 18:16:34 by priezu-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"

void	give_initial_forks(volatile _Atomic t_fork_state (*fork_sate)[2],
		int number_of_philosophers)
{
	int	i;

	i = 0;
	while (i < number_of_philosophers)
	{
		fork_sate[i][0] = e_gotten;
		fork_sate[i][1] = e_gotten;
		i += 2;
	}
	if ((number_of_philosophers % 2) == 1)
	{
		i -= 2;
		fork_sate[i][0] = e_default_fork_state;
		fork_sate[i][1] = e_default_fork_state;
		i--;
		if (i == -1)
			i = 0;
		fork_sate[i][1] = e_gotten;
	}
}
