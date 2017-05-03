all : serveur client

libft :
	@make fclean -C libft_files/
	@make -C libft_files/

serveur : libft
	@make -C serveur_files/
	@cp serveur_files/./serveur .

client : libft
	@make -C client_files/
	@cp client_files/./client .

debug :
	@make -C libft_files/
	@make debug -C client_files/
	@cp client_files/./client .
	@make debug -C serveur_files/
	@cp serveur_files/./serveur .

clean :
	@make clean -C libft_files/
	@make clean -C client_files/
	@make clean -C serveur_files/

fclean :
	@make fclean -C libft_files/
	@make fclean -C client_files/
	@make fclean -C serveur_files/
	@rm -rf client
	@rm -rf serveur

re : fclean all

.PHONY : all re clean fclean serveur client
