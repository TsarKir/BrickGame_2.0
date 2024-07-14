#ifndef TETRIS_H
#define TETRIS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file tetris.h
 * @brief header with tetris game logic
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../common/common.h"

/**
 * @brief Figure structure
 *
 * @param field 2D array of figure
 * @param x x coordinate of figure
 * @param y y coordinate of figure
 *
 */
typedef struct {
  int **field;
  int x;
  int y;
} Figure_t;
/**
 * @brief All game data structure
 *
 * @param data GameInfo_t structure
 * @param current_figure Figure_t structure
 * @param FSM FSM_t structure
 *
 */
typedef struct {
  GameInfo_t data;
  Figure_t current_figure;
  FSM_t FSM;

} GameData_t;
/**
 * @brief User input func
 *
 * Controller, depends on action and hold params make game moves
 *
 * @param argc 2
 * @param action player action
 * @param hold bool is key holded
 *
 *
 *
 */
void userInput(UserAction_t action, bool hold);
/**
 * @brief Field initialization
 *
 * Creates game field with initial parametres and memory allocation
 * score = 0
 * pause = 0
 * high_score = takes from highscore_tetris.txt
 * level = 1
 *
 * @param argc 1
 * @param GameField Game field
 *
 *
 *
 */
void InitializeField(GameInfo_t *GameField);
/**
 * @brief Next figure spawn
 *
 * Spawns next figure on game field
 *
 * @param argc 1
 * @param StartingField Game field
 *
 *
 *
 */
void NextFigureSpawn(GameInfo_t *StaringField);
/**
 * @brief Figure initialization
 *
 * Creates figure with initial parametres and memory allocation
 *
 * @param argc 1
 * @param CurrentFigure Figure
 *
 *
 *
 */
void InitializeFigure(Figure_t *CurrentFigure);
/**
 * @brief Singleton returner
 *
 */
GameData_t *GetSingletone();
/**
 * @brief Updates current game state
 *
 */
GameInfo_t updateCurrentState();
/**
 * @brief Clear figure
 *
 * All elements of figure will set 0
 *
 * @param argc 1
 * @param CurrentFigure Figure
 *
 *
 *
 */
void ClearFigure(Figure_t *CurrentFigure);
/**
 * @brief From next to current
 *
 * Moves next figure to current figure
 * @param argc 3
 * @param StartingField Game field
 * @param CurrentFigure Current figure
 * @param FSM Finite state machine
 *
 *
 */
void FromNextToCurrent(Figure_t *CurrentFigure, GameInfo_t *StaringField,
                       FSM_t *FSM);
/**
 * @brief Is it square?
 *
 * Checks if figure is square
 *
 * @param argc 1
 * @param CurrentFigure Figure
 *
 * @return 1 if square, 0 if not
 *
 */
int IsSquare(Figure_t *CurrentFigure);
/**
 * @brief Figure rotation
 *
 * Rotates current figure
 *
 * @param argc 2
 * @param GameField Game field
 * @param CurrentFigure Figure
 *
 *
 */
void Rotation(GameInfo_t *GameField, Figure_t *CurrentFigure);
/**
 * @brief Add figure
 *
 * Adds figure to the game field
 * @param argc 2
 * @param StartingField Game field
 * @param CurrentFigure Current figure
 *
 *
 */
void FigureAdd(GameInfo_t *StartitingField, Figure_t *CurrentFigure);
/**
 * @brief Del figure
 *
 * Deletes figure from the game field
 * @param argc 2
 * @param GameField Game field
 * @param CurrentFigure Current figure
 *
 *
 */
void DelFigure(GameInfo_t *GameField, Figure_t *CurrentFigure);
/**
 * @brief Collision check
 *
 * Checks if there is a collision of the figure with the game field
 * @param argc 2
 * @param GameField Game field
 * @param NewFigure Current figure
 *
 * @return 1 if there is a collision, 0 if not
 */
int CollisionCheck(GameInfo_t *GameField, Figure_t *NewFigure);
/**
 * @brief Copy figure
 *
 * Makes a copy of the figure to new figure
 * @param argc 2
 * @param CurrentFigure Current figure
 * @param NewFigure New figure
 *
 */
void CopyFigure(Figure_t *CurrentFigure, Figure_t *NewFigure);
/**
 * @brief Move left
 *
 * Moves figure to the left by 1 pixel
 * @param argc 2
 * @param GameField Game field
 * @param CurrentFigure Current figure
 *
 *
 */
void MoveLeft(GameInfo_t *GameField, Figure_t *CurrentFigure);
/**
 * @brief Move right
 *
 * Moves figure to the right by 1 pixel
 * @param argc 2
 * @param GameField Game field
 * @param CurrentFigure Current figure
 *
 *
 */
void MoveRight(GameInfo_t *GameField, Figure_t *CurrentFigure);
/**
 * @brief Move down
 *
 * Moves figure down by 1 pixel
 * @param argc 3
 * @param GameField Game field
 * @param CurrentFigure Current figure
 * @param FSM Finite state machine
 *
 * @return exit code 1 or 0
 *
 */
int MoveDown(GameInfo_t *GameField, Figure_t *CurrentFigure, FSM_t *FSM);
/**
 * @brief Drop line
 *
 * Erase i-line from the field, moves all lines above it down by 1 pixel
 * @param argc 2
 * @param GameField Game field
 * @param i Line number
 *
 *
 */
void DropLine(GameInfo_t *GameField, int i);
/**
 * @brief Is line filled?
 *
 * Checks if i-line is filled
 * @param argc 2
 * @param GameField Game field
 * @param i Line number
 *
 * @return 1 if line is filled, 0 if not
 *
 */
int IsLineFilled(GameInfo_t *GameField, int i);
/**
 * @brief Score updater
 *
 * Updates score when line(or lines) is droped
 * @param argc 2
 * @param GameField Game field
 * @param lines_counter How many lines are droped
 *
 *
 */
void ScoreUpdater(GameInfo_t *GameField, int lines_counter);
/**
 * @brief Line checker
 *
 * Checks if there is a line(or lines) that is filled, if yes, erases it and
 * updates score
 * @param argc 1
 * @param GameField Game field
 *
 *
 */
void LineChecker(GameInfo_t *GameField);
/**
 * @brief Highscore checker
 *
 * Checks is score is higher than highscore, if yes, updates highscore
 * @param argc 1
 * @param GameField Game field
 *
 *
 */
void HighscoreChecker(GameInfo_t *GameField);
/**
 * @brief Time calculator
 *
 * Updates speed of the game depending on level
 * @param argc 1
 * @param level level of the game
 *
 * @return double with speed of the game
 *
 */
double TimeCalculator(int level);
/**
 * @brief Speed checker
 *
 * Updates speed of the game depending on level and updates level depending on
 * score
 * @param argc 1
 * @param GameField Game field
 *
 *
 */
void SpeedChecker(GameInfo_t *GameField);
/**
 * @brief Game close
 *
 * Closes game and frees memory
 * @param argc 2
 * @param GameField Game field
 * @param CurrentFigure Current figure
 *
 *
 */
void GameClose(GameInfo_t *GameField, Figure_t *CurrentFigure);
void RemoveGameData();

#ifdef __cplusplus
}
#endif

#endif