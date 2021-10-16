NAME = philo

INCS =  incs/philo.h

SRCS =	main_copy.c utils.c init.c

OBJS = $(SRCS:.c=.o)

CC = gcc
RM = rm -rf

CFLAGS = -Wall -Wextra -Werror -g

all:		$(NAME)

$(NAME):	$(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)

re:			fclean all

# run: all
# 			./philo 3 400 400 200
