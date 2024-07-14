#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file common.h
 * @brief header with common structures and defines
 */

#define FIELD_HEIGHT 24
#define FIELD_WIDTH 10
#define START_SPEED 500

/**
 * @brief UserAction enumeration
 *
 */
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;
/**
 * @brief FSM enumeration
 *
 */
typedef enum { START, PLAYING, PAUSE, GAMEOVER, EXIT } FSM_t;
/**
 * @brief Game info structure
 *
 * @param field 2D array of game field
 * @param next 2D array of next figure
 * @param score Current score
 * @param high_score High score
 * @param level Current level
 * @param speed Current speed
 * @param pause Is game paused?
 *
 */
typedef struct {
  int **field;
  int **next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

#ifdef __cplusplus
}
#endif

#endif