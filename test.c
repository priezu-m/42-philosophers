/* ************************************************************************** */
/*                                                                            */
/*                                                                            */
/*   Filename: test.c                                                         */
/*   Author:   Peru Riezu <riezumunozperu@gmail.com>                          */
/*   github:   https://github.com/priezu-m                                    */
/*   Licence:  GPLv3                                                          */
/*   Created:  2023/08/02 18:02:30                                            */
/*   Updated:  2023/08/04 14:42:33                                            */
/*                                                                            */
/* ************************************************************************** */

#pragma GCC diagnostic warning "-Weverything"
#pragma GCC diagnostic ignored "-Wempty-translation-unit"

#include <pthread.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

static void	*procedure(pthread_mutex_t	*mutex)
{
	struct timeval	tv;
	pthread_mutex_lock(mutex);
	gettimeofday(&tv, NULL);
	printf("%ld, %ld\n", tv.tv_sec, tv.tv_usec);
	pthread_mutex_unlock(mutex + 6);
	return (NULL);
}

int	main(void)
{
	pthread_t		threads[100];
	pthread_mutex_t	mutex[106] = {[0 ... 105] = PTHREAD_MUTEX_INITIALIZER};
	int				i;

	i = 0;
	while (i < 106)
	{
		if (i > 5)
			pthread_mutex_lock(&mutex[i]);
		i++;
	}
	i = 0;
	while (i < 100)
	{
		pthread_create(&threads[i], NULL, procedure, &mutex[i]);
		i++;
	}
	i = 0;
	while (i < 100)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (0);
}
