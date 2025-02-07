SRC = fdf.c parsing_fdf.c pixel.c \
	  keyhook.c

LBS = libft/libft.a

OBJ = $(SRC:.c=.o)

NAME = fdf

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

AR = ar rc

all : $(NAME)

$(NAME): $(OBJ)
	make bonus -C libft
	$(CC) -o $(NAME) $(OBJ) $(CFLAGS) $(LBS)  -lmlx -Lminilibx-linux -lXext -lX11 -lm 

$(OBJ) : $(SRC)
	$(CC) $(CFLAGS) -c $(SRC)

libft/libft.a :
	make -C libft

clean :
	make clean -C libft
	rm -rf *.o

fclean : clean
	make fclean -C libft
	rm -rf *.a

re : fclean all

bonus : all

clean_libft :
	make clean -C $(LBSDIR)

fclean_libft :
	make fclean -C $(LBSDIR)

re_libft :
	make re -C $(LBSDIR)

clean_all : clean clean_libft

fclean_all : clean_all fclean fclean_libft

re_all : re_libft re

test : all clean
	@echo "real one"
	@cc specifiercheck.c -L. libftprintf.a && ./a.out  1 | cat -e
	@echo "mine"
	@cc specifiercheck.c -L. libftprintf.a && ./a.out  | cat -e
vtest : all
	cc main.c -L. libftprintf.a && valgrind ./a.out
