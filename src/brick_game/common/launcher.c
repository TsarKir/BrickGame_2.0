#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

void print_menu(int option_number);
int user_input(int ch, int option_number);
void game_launcher(int option_number);

int main() {
  initscr();
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLUE);
  keypad(stdscr, TRUE);
  int option_number = 0;
  int ch;
  print_menu(option_number);
  while ((ch = getch()) != 10) {
    option_number = user_input(ch, option_number);
    clear();
    print_menu(option_number);
  }
  endwin();
  game_launcher(option_number);
  return 0;
}

void print_menu(int option_number) {
  switch (option_number) {
    case 0:
      printw("CHOOSE GAME:\n");
      attron(COLOR_PAIR(1));
      printw("1.SNAKE CLI\n");
      attroff(COLOR_PAIR(1));
      printw("2.SNAKE DESKTOP\n");
      printw("3.TETRIS CLI\n");
      printw("4.TETRIS DESKTOP\n");
      break;
    case 1:
      printw("CHOOSE GAME:\n");
      printw("1.SNAKE CLI\n");
      attron(COLOR_PAIR(1));
      printw("2.SNAKE DESKTOP\n");
      attroff(COLOR_PAIR(1));
      printw("3.TETRIS CLI\n");
      printw("4.TETRIS DESKTOP\n");
      break;
    case 2:
      printw("CHOOSE GAME:\n");
      printw("1.SNAKE CLI\n");
      printw("2.SNAKE DESKTOP\n");
      attron(COLOR_PAIR(1));
      printw("3.TETRIS CLI\n");
      attroff(COLOR_PAIR(1));
      printw("4.TETRIS DESKTOP\n");
      break;
    case 3:
      printw("CHOOSE GAME:\n");
      printw("1.SNAKE CLI\n");
      printw("2.SNAKE DESKTOP\n");
      printw("3.TETRIS CLI\n");
      attron(COLOR_PAIR(1));
      printw("4.TETRIS DESKTOP\n");
      attroff(COLOR_PAIR(1));
      break;
  }
}

int user_input(int ch, int option_number) {
  switch (ch) {
    case KEY_UP:
      if (option_number > 0) {
        option_number--;
      }
      break;
    case KEY_DOWN:
      if (option_number < 3) {
        option_number++;
      }
      break;
    default:
      break;
  }
  return option_number;
}

void game_launcher(int option_number) {
  switch (option_number) {
    case 0:
      system("./Snake_Cli");
      break;
    case 1:
      system("./Snake_Gui");
      break;
    case 2:
      system("./Tetris_Cli");
      break;
    case 3:
      system("./Tetris_Gui");
      break;
  }
}