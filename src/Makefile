DATE = $(shell date -R)
CC_TETRIS = gcc
CC_SNAKE = g++
FLAGS = -Wall -Wextra -Werror -std=c17
SOURCES_TETRIS = $(wildcard brick_game/tetris/*.c gui/cli/*.c)
OBJECTS_TETRIS = $(patsubst %.c, $(OBJDIR)%.o, $(SOURCES_TETRIS))
NAME_TETRIS = s21_tetris
SOURCES_SNAKE = $(wildcard brick_game/snake/cli_engine.cc gui/cli/*.c)
OBJECTS_SNAKE = $(patsubst %.cc, $(OBJDIR)%.o, $(SOURCES_SNAKE))
NAME_SNAKE = s21_snake

all: $(NAME_TETRIS).a $(NAME_SNAKE).a

build: all

install: clean $(NAME_TETRIS).a $(NAME_SNAKE).a
	$(CC_TETRIS) $(FLAGS) $(NAME_TETRIS).a gui/cli/*.o -lm -lncurses -o Tetris_Cli 
	$(CC_SNAKE) $(FLAGS) $(NAME_SNAKE).a gui/cli/*.o -lm -lncurses -o Snake_Cli 
	g++  brick_game/tetris/gui_engine.cc $(NAME_TETRIS).a -o Tetris_Gui `pkg-config --cflags --libs gtkmm-4.0` -std=c++17 -lm 
	$(CC_SNAKE)  brick_game/snake/gui_engine.cc -o Snake_Gui `pkg-config --cflags --libs gtkmm-4.0` -std=c++17 -lm
	gcc brick_game/common/launcher.c -lncurses -o ./Game
	./Game
uninstall: clean
	rm -rf Tetris_Cli Tetris_Gui Snake_Cli Snake_Gui Game
dist:
	tar czvf Brick_Game.tar.gz --ignore-failed-read \
		../src
dvi:
	doxygen
	$(OPEN) doxy/html/index.html
clean:
	rm -rf  brick_game/snake/*.o brick_game/tetris/*.o gui/cli/*.o *.a brick_game/common/*.o
	echo "0" > highscore_tetris.txt
	echo "0" > highscore_snake.txt
	reset
$(NAME_TETRIS).a: $(OBJECTS_TETRIS)
	ar rcs $(NAME_TETRIS).a brick_game/tetris/*.o
	ranlib $(NAME_TETRIS).a
$(NAME_SNAKE).a: $(OBJECTS_SNAKE)
	ar rcs $(NAME_SNAKE).a brick_game/snake/*.o
	ranlib $(NAME_SNAKE).a
