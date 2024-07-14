#ifndef USER_INPUT_H
#define USER_INPUT_H

/**
 * @file user_input.h
 * @brief header with user input handler
 */

#include "tetris.h"
/**
 * @brief User input
 *
 * User input handler, depending on user input (ch), updates UserAction_t of the
 * game
 *
 * @param argc 1
 * @param ch User input
 *
 *
 */
void UserInput(int ch);

#endif