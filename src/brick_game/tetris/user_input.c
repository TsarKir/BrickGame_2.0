/**
 * @file user_input.c
 * @brief file with user input handler
 */

#include "user_input.h"

#include <ncurses.h>

void UserInput(int ch) {
  UserAction_t action;
  bool hold = false;
  keypad(stdscr, TRUE);
  switch (ch) {
    case 10:
      action = Start;
      break;
    case ' ':
      action = Action;
      break;
    case KEY_LEFT:
      action = Left;
      break;
    case KEY_RIGHT:
      action = Right;
      break;
    case KEY_DOWN:
      action = Down;
      break;
    case 'd':
      action = Down;
      hold = true;
      break;
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
  }

  userInput(action, hold);
}