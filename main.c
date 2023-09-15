/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: main.c                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/15 20:12:31                                            */
/*   Updated:  2023/09/15 20:36:50                                            */
/*                                                                            */
/* ************************************************************************** */

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

#include "philosopher.h"
#include "schedueler.h"
#include <stdlib.h>

int	main(int argc, char **argv)
{
	const t_parameters parameters = get_parameters(argc, argv);

	if (parameters.parameters_valid == false)
	{
		print_usage();
		return (EXIT_FAILURE);
	}
}

#pragma clang diagnostic pop
