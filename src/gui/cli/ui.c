/**
 * @file ui.c
 * @brief file of user interface module
 */

#include "ui.h"

void InitColorPairs() {
  init_pair(1, COLOR_RED, COLOR_GREEN);
  init_pair(2, COLOR_RED, COLOR_YELLOW);
  init_pair(3, COLOR_RED, COLOR_RED);
  init_pair(4, COLOR_RED, COLOR_BLUE);
}

void DrawSideBar(int i, GameInfo_t* GameField, FSM_t* FSM) {
  switch (i) {
    case 2:
      printw("      Score:   ");
      break;
    case 3:
      printw("%9d ", GameField->score);
      printw("     ");
      break;
    case 4:
      printw("    Highscore: ");
      break;
    case 5:
      printw("%9d ", GameField->high_score);
      printw("     ");
      break;
    case 7:
      if (GameField->next != NULL) {
        printw("     Next:     ");
      } else
        DrawEmptyLine();
      break;
    case 8:
      DrawNext(GameField, 0);
      break;
    case 9:
      DrawNext(GameField, 1);
      break;
    case 10:
      DrawNext(GameField, 2);
      break;
    case 11:
      DrawNext(GameField, 3);
      break;
    case 12:
      DrawNext(GameField, 4);
      break;
    case 15:
      printw("     Level:    ");
      break;
    case 16:
      printw("%8d  ", GameField->level);
      printw("     ");
      break;
    case 18:
      if (*FSM == GAMEOVER) {
        printw("    GAME OVER  ");
      } else if (*FSM == PAUSE) {
        printw("     PAUSE     ");
      } else if (*FSM == START) {
        printw("  PRESS ENTER  ");
      } else {
        DrawEmptyLine();
      }
      break;
    default:
      DrawEmptyLine();
  }
  DrawSideBorder();
}

void DrawNext(GameInfo_t* GameField, int i) {
  printw("  ");
  if (GameField->next == NULL) {
    for (int j = 0; j < 5; j++) {
      printw("  ");
    }
  } else {
    for (int j = 0; j < 5; j++) {
      if (GameField->next[i][j] == 1) {
        attron(COLOR_PAIR(2));
        printw("  ");
        attroff(COLOR_PAIR(2));
      } else {
        printw("  ");
      }
    }
  }
  printw("   ");
}

void DrawEmptyLine() {
  for (int i = 0; i < FIELD_WIDTH + 5; i++) {
    printw(" ");
  }
}

void DrawSideBorder() {
  attron(COLOR_PAIR(1));
  printw("  ");
  attroff(COLOR_PAIR(1));
}

void DrawBorder() {
  attron(COLOR_PAIR(1));

  for (int i = 0; i < 4 * FIELD_WIDTH + 1; i++) {
    printw(" ");
  }
  attroff(COLOR_PAIR(1));
  printw("\n");
}

void DrawField(GameInfo_t* GameField, FSM_t* FSM) {
  for (int i = 2; i < 22; i++) {
    DrawSideBorder();
    for (int j = 0; j < FIELD_WIDTH; j++) {
      if (GameField->field[i][j] == 0) {
        printw("  ");
      } else if (GameField->field[i][j] == 1) {
        attron(COLOR_PAIR(2));
        printw("  ");
        attroff(COLOR_PAIR(2));
      } else if (GameField->field[i][j] == 3) {
        attron(COLOR_PAIR(4));
        printw("  ");
        attroff(COLOR_PAIR(4));
      } else {
        attron(COLOR_PAIR(3));
        printw("  ");
        attroff(COLOR_PAIR(3));
      }
    }
    DrawSideBorder();
    DrawSideBar(i, GameField, FSM);
    printw("\n");
  }
}

void DrawBottomBar(GameInfo_t* GameField) {
  if (GameField->next == NULL) {
    printw("ENTER - Start the game\n");
    printw("KEY LEFT - Change snake direction to left\n");
    printw("KEY RIGHT - Change snake direction to right\n");
    printw("KEY UP - Change snake direction to up\n");
    printw("KEY DOWN - Change snake direction to down\n");
    printw("P - Pause\n");
    printw("Q - Quit\n");
  } else {
    printw("ENTER - Start the game\n");
    printw("KEY LEFT - Move figure to the left\n");
    printw("KEY RIGHT - Move figure to the  right\n");
    printw("KEY DOWN - Move figure down\n");
    printw("HOLD KEY DOWN - Move figure all the way down\n");
    printw("SPACE - Rotate figure\n");
    printw("P - Pause\n");
    printw("Q - Quit\n");
  }
}

void DrawTitle(GameInfo_t* GameField) {
  char title[7];
  if (GameField->next == NULL) {
    strcpy(title, "SNAKE");
  } else {
    strcpy(title, "TETRIS");
  }
  printw("           %s by ogdengum\n", title);
}

void PrintGame(GameInfo_t* GameField, FSM_t* FSM) {
  start_color();
  InitColorPairs();
  DrawTitle(GameField);
  DrawBorder();
  DrawField(GameField, FSM);
  DrawBorder();
  DrawBottomBar(GameField);
}
