#include <unistd.h>

#include "../../gui/cli/ui.h"
#include "snake.h"
#include "user_input.h"

int main(void) {
  s21::GameData_t *game = s21::GetSingletone();
  initscr();
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  system("echo -e \"\\e[8;50;50t\"");
  noecho();
  keypad(stdscr, TRUE);
  timeout(game->data.speed);
  int ch;
  int exit = 0;
  while (game->FSM != EXIT) {
    if (game->FSM == START) {
      PrintGame(&(game->data), &(game->FSM));
      while (game->FSM == START) {
        ch = getch();
        if (ch == 10) {
          game->FSM = PLAYING;
        }
        flushinp();
      }
    } else if (game->FSM == PLAYING) {
      while (game->FSM != GAMEOVER && game->FSM != EXIT && exit != 1) {
        s21::score_check(&(game->data), game->Snake, game->FSM);
        s21::level_check(&(game->data));
        s21::high_score_check(&(game->data));
        clear();
        game->Snake.add_snake_to_field(game->data.field);
        PrintGame(&(game->data), &(game->FSM));
        ch = getch();
        s21::UserInputHandler(ch);
        game->Snake.remove_snake_from_field(game->data.field);
        game->Snake.move_snake(&(game->FSM));
        flushinp();
        timeout(game->data.speed);
      }
    } else if (game->FSM == GAMEOVER) {
      clear();
      game->Snake.add_snake_to_field(game->data.field);
      PrintGame(&(game->data), &(game->FSM));
      while (game->FSM != EXIT) {
        clear();
        game->Snake.add_snake_to_field(game->data.field);
        PrintGame(&(game->data), &(game->FSM));
        s21::UserInputHandler(getch());
      }
    }
  }
  s21::RemoveGameData();
  char command[50];
  sprintf(command, "echo -e \"\\e[8;%d;%dt\"", rows, cols);
  system(command);
  endwin();
  return 0;
}