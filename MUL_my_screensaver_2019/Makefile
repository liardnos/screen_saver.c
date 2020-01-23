##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## hello
##

NAME =			"my_screensaver"

SOURCE =		main.c \
				3d_screen/bootstrap_3d_coding_style.c \
				3d_screen/screen1.c \
				3d_screen/screen2.c \
				3d_screen/screen3.c \
				3d_screen/screen4.c \
				3d_screen/screen5.c \
				3d_screen/screen6.c \
				2d_screen/bootstrap_coding_style.c \
				2d_screen/screen1.c \
				2d_screen/screen2.c \
				2d_screen/screen3.c \
				2d_screen/screen4.c \
				2d_screen/screen5.c

LIBPATH =		./lib

LIB = 			my

all:
	gcc $(SOURCE) -O4 $(NAME) -l csfml-graphics -l m

all2:
	clear
	gcc $(SOURCE) -O4 -o $(NAME) -l csfml-graphics -l m

all04:
	clear
	gcc $(SOURCE) -O4 -o $(NAME) -l csfml-graphics -l m


clean: fclean

fclean:
	rm -f $(NAME)
	rm -f *.gcno
	rm -f *.gcda
	rm -f vgcore.*

re:		fclean all

re2: fclean all2

run: re
	./$(NAME)

run3D: re2
	./$(NAME)


valgrind3D: fclean
	clear
	gcc $(SOURCE) -O4 -g -o $(NAME) -l csfml-graphics -lm
	valgrind --track-origins=yes --leak-check=full ./$(NAME) #&> valgrind_log

valgrind: fclean
	clear
	gcc $(SOURCE) -g -O4 -o $(NAME) -l csfml-graphics -lm
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./$(NAME) #&> valgrind_log
#-s --leak-check=full

callgrind: fclean
	rm -f callgrind.*
	clear
	gcc $(SOURCE) -g -o $(NAME) -l csfml-graphics -lm
	valgrind --tool=callgrind ./$(NAME) 3 #&> valgrind_log
	kcachegrind callgrind.*

callgrind3D: fclean
	rm -f callgrind.*
	clear
	gcc $(SOURCE) -g -O4 -o $(NAME) -l csfml-graphics -lm
	valgrind --tool=callgrind ./$(NAME) #&> valgrind_log
	kcachegrind callgrind.*

time_test:
	gcc $(SOURCE) -o $(NAME) -l csfml-graphics -lm
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	gcc $(SOURCE) -O1 -o $(NAME) -l csfml-graphics -lm
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	gcc $(SOURCE) -O2 -o $(NAME) -l csfml-graphics -lm
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	gcc $(SOURCE) -O3 -o $(NAME) -l csfml-graphics -lm
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	gcc $(SOURCE) -O4 -o $(NAME) -l csfml-graphics -lm
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
	time ./$(NAME) 4 > log
