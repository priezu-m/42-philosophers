/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: loger_routine.c                                                */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/09/17 20:23:00                                            */
/*   Updated:  2023/09/17 20:35:38                                            */
/*                                                                            */
/* ************************************************************************** */

#include "loger.h"
#include <stdio.h>

;
#pragma clang diagnostic push
#pragma clang diagnostic warning "-Weverything"
#pragma clang diagnostic ignored "-Wempty-translation-unit"
#pragma clang diagnostic ignored "-Wunused-macros"

void	*loger_routine(void *loger_data)
{
	printf("loger routine entered\n");
	(void)loger_data;
	return (NULL);
}

#pragma clang diagnostic pop
