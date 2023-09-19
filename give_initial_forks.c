/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: give_initial_forks.c                                           */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/19 14:33:28                                            */
/*   Updated:  2023/09/19 14:34:09                                            */
/*                                                                            */
/* ************************************************************************** */

#include "schedueler.h"

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"
#pragma clang diagnostic ignored "-Watomic-implicit-seq-cst"

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

#pragma clang diagnostic pop
