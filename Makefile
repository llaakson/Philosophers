NAME = philo

SOURCES =	main.c \
		thread.c \
		free.c	\
		monitor.c \
		utils.c \
		thread2.c \
		input.c 
		  
HEADF	=	philo.h

OBJECTS = $(SOURCES:%.c=%.o)

CC	=	cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o:	%.c	$(HEADF)
	$(CC)	$(CFLAGS)	-c	$<	-o	$@

$(NAME): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
