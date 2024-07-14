#include "main_loop.h"

/**
 * @file game.c
 * @brief Entry point
 *
 * Execution of the program
 * starts here.
 *
 *
 * @return Program exit status
 */

int main() {
  srand(time(NULL));
  GameData_t *game = GetSingletone();
  GameInfo_t current_state;
  FromNextToCurrent(&(game->current_figure), &(game->data), &(game->FSM));
  initscr();
  noecho();
  int rows, cols;
  getmaxyx(stdscr, rows, cols);
  system("echo -e \"\\e[8;50;50t\"");
  int ch;
  while (game->FSM != EXIT) {
    current_state = updateCurrentState();
    if (game->FSM == START) {
      PrintGame(&current_state, &(game->FSM));
      while (game->FSM != PLAYING) {
        ch = getch();
        if (ch == 10) {
          game->FSM = PLAYING;
        }
        flushinp();
      }
    } else if (game->FSM == PLAYING) {
      clear();
      MainLoop(&current_state, &(game->current_figure), &(game->FSM));

    } else if (game->FSM == GAMEOVER) {
      PrintGame(&current_state, &(game->FSM));
      while (game->FSM != EXIT) {
        ch = getch();
        UserInput(ch);
        flushinp();
      }
    }
  }
  RemoveGameData();
  char command[50];
  sprintf(command, "echo -e \"\\e[8;%d;%dt\"", rows, cols);
  system(command);
  endwin();
  return 0;
}