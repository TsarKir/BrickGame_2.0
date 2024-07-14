#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

/**
 * @file main_loop.h
 * @brief header with game loop functions
 */

#include <unistd.h>

#include "../../gui/cli/ui.h"
#include "tetris.h"
#include "user_input.h"

/*!
 * @brief MainLoop
 *
 * Starts main loop of the game
 *
 * @param argc 3
 * @param GameFileld Game field
 * @param CurrentFigure Current figure
 * @param FSM Finite state machine
 *
 *
 */
void MainLoop(GameInfo_t* GameField, Figure_t* CurrentFigure, FSM_t* FSM);

/*!
 * @brief UserInputLoop
 *
 * Starts user input loop of the game
 *
 * @param argc 4
 * @param GameFileld Game field
 * @param CurrentFigure Current figure
 * @param exit Exit flag
 * @param FSM Finite state machine
 *
 *
 */
void UserInputLoop(GameInfo_t* GameField, Figure_t* CurrentFigure, int exit,
                   FSM_t* FSM);

#endif
