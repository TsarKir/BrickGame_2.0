#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <ncurses.h>

#include "snake.h"
/**
 * @file user_input.h
 * @brief header with user input handler
 */

/**
 * @brief User input
 *
 * User input handler, depending on user input (ch), updates UserAction_t of the
 * game
 *
 * @param ch User input
 *
 *
 */
namespace s21 {
void UserInputHandler(int ch) {
  UserAction_t action;
  keypad(stdscr, TRUE);
  switch (ch) {
    case 10:
      action = Start;
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
    case KEY_UP:
      action = Up;
      break;
    case 'p':
      action = Pause;
      break;
    case 'q':
      action = Terminate;
      break;
  }
  userInput(action, false);
}
}  // namespace s21

#endif