NAME = ft_ls

FLAGS = -Wall -Wextra -Werror

SRC = allign.c bytes.c date.c flags.c ft_ls.c ftree.c ids.c main.c misc.c \
	mode.c params.c

OBJ = allign.o bytes.o date.o flags.o ft_ls.o ftree.o ids.o main.o misc.o \
	mode.o params.o

INC = ./

LIB = libft/libft.a

all : $(NAME)

$(NAME) :
	make -C libft/
	gcc $(FLAGS) -c $(SRC)
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LIB) -I $(INC)

clean :
	rm -rf $(OBJ)
	make clean -C libft/

fclean : clean
	rm -rf $(NAME)
	make fclean -C libft/

re : fclean all
