# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: priezu-m <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/25 16:54:37 by priezu-m          #+#    #+#              #
#    Updated: 2023/09/25 16:54:42 by priezu-m         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror -flto -O2 -pthread -g3
SRC = check_time_list.c give_initial_forks.c loger_data.c \
	  check_yield_forks.c launch_and_join_philosophers.c \
	  loger_routine.c schedueler_data_valid.c \
	  destroy_schedueler_data.c launch_join_loger.c main.c philosopher_list.c \
	  schedueler_loop.c launch_join_schedueler.c \
	  mutex_action_no_ownership_transfer.c philosopher_routine.c \
	  schedueler_routine.c get_schedueler_data.c \
	  philosopher_routine_functions1.c \
	  get_set_current_time.c loger_buffer.c parameters.c \
	  philosopher_routine_functions2.c print_event_sequential.c

$(NAME): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(NAME)

all: $(NAME)

clean:

fclean:
	rm -f $(NAME)

re: fclean all

