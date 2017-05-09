SRC_NAME = serveur.c signal.c tools.c cmd.c get.c put.c tools2.c

NAME = "serveur"

OBJ_NAME = $(SRC_NAME:.c=.o)

all : $(NAME)

$(NAME) :
	@gcc -c -Wall -Werror -Wextra $(SRC_NAME)
	@gcc $(OBJ_NAME) -o $(NAME) -L../libft_files -lft
	@echo "\033[1;34m ---FTP--- :\033[m \033[1;32m DONE !\033[m"

debug :
	@gcc -g -c $(SRC_NAME)
	@gcc -o $(NAME) $(OBJ_NAME) -L../libft_files -lft
	@echo "\033[1;31m --DEBUG--MODE-- :\033[m \033[1;32m DONE !\033[m"

clean :
	@rm -rf $(OBJ_NAME)
	@make clean -C ../libft_files/
	@echo "\033[1;34m ---FTP--- :\033[m \033[1;32m DELETE OBJ FILES !\033[m"

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C ../libft_files/
	@echo "\033[1;34m ---FTP--- :\033[m \033[1;32m DELETE project !\033[m"

re : fclean all

.PHONY : all re clean fclean
