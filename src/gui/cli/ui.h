#ifndef UI_H
#define UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../brick_game/common/common.h"

void DrawSideBar(int i, GameInfo_t* GameField, FSM_t* FSM);
void DrawNext(GameInfo_t* GameField, int i);
void DrawEmptyLine();
void DrawSideBorder();
void DrawBorder();
void DrawField(GameInfo_t* GameField, FSM_t* FSM);
void PrintGame(GameInfo_t* GameField, FSM_t* FSM);
void DrawTitle(GameInfo_t* GameField);
void DrawBottomBar();

#ifdef __cplusplus
}
#endif

#endif  // UI_H