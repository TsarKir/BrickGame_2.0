/**
 * @file main_loop.c
 * @brief file with game loop functions
 */

#include "main_loop.h"

void UserInputLoop(GameInfo_t* GameField, Figure_t* CurrentFigure, int exit,
                   FSM_t* FSM) {
  struct timespec start = {0, 0};
  struct timespec end = {0, 0};
  double time;
  int ddown = 0;
  clock_gettime(1, &start);
  time = TimeCalculator(GameField->level);
  timeout(START_SPEED * time);
  FigureAdd(GameField, CurrentFigure);
  PrintGame(GameField, FSM);
  int ch;
  int ch2;
  ddown = 0;
  while (exit == 0 && *FSM != EXIT) {
    ch = getch();
    if (ch == KEY_DOWN && ch2 == KEY_DOWN && ddown == 0) {
      UserInput('d');
      flushinp();
      ddown = 1;
    } else if (ch == KEY_DOWN && ch2 == KEY_DOWN && ddown == 1) {
      flushinp();
    } else {
      UserInput(ch);
      flushinp();
      ddown = 0;
    }
    while (*FSM == PAUSE) {
      clear();
      PrintGame(GameField, FSM);
      ch = getch();
      if (ch == 'p') {
        UserInput(ch);
      }
      flushinp();
    }
    ch2 = ch;
    clear();
    DelFigure(GameField, CurrentFigure);
    FigureAdd(GameField, CurrentFigure);
    PrintGame(GameField, FSM);
    clock_gettime(1, &end);
    if (((end.tv_sec - start.tv_sec) * 1000000000LL +
         (end.tv_nsec - start.tv_nsec)) /
            1000000 >
        (long)START_SPEED * time) {
      exit = 1;
    }
  }
}

void MainLoop(GameInfo_t* GameField, Figure_t* CurrentFigure, FSM_t* FSM) {
  while (*FSM != GAMEOVER && *FSM != EXIT) {
    int exit = 0;
    UserInputLoop(GameField, CurrentFigure, exit, FSM);
    exit = 0;
    DelFigure(GameField, CurrentFigure);
    MoveDown(GameField, CurrentFigure, FSM);
    clear();
    LineChecker(GameField);
    SpeedChecker(GameField);
    HighscoreChecker(GameField);
  }
}