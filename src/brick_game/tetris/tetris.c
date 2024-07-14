/**
 * @file tetris.c
 * @brief file with game logic
 */

#include "tetris.h"

void InitializeField(GameInfo_t *StaringField) {
  StaringField->score = 0;
  StaringField->pause = 0;
  StaringField->high_score = 0;
  StaringField->level = 1;
  // StaringField->speed = START_SPEED;

  FILE *hs_file;
  hs_file = fopen("highscore_tetris.txt", "r");
  fscanf(hs_file, "%d", &(StaringField->high_score));
  fclose(hs_file);

  StaringField->field = (int **)calloc(FIELD_HEIGHT, sizeof(int *));
  if (StaringField->field != NULL) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      StaringField->field[i] = (int *)calloc(FIELD_WIDTH, sizeof(int));
    }
  }

  StaringField->next = (int **)calloc(5, sizeof(int *));
  if (StaringField->next != NULL) {
    for (int i = 0; i < 5; i++) {
      StaringField->next[i] = (int *)calloc(5, sizeof(int));
    }
  }
  NextFigureSpawn(StaringField);
}

GameData_t *GetSingletone() {
  static GameData_t *game_structure = NULL;
  if (game_structure == NULL) {
    game_structure = (GameData_t *)malloc(sizeof(GameData_t));
    if (game_structure != NULL) {
      InitializeField(&(game_structure->data));
      InitializeFigure(&(game_structure->current_figure));
      game_structure->FSM = START;
    }
  }
  return game_structure;
}

GameInfo_t updateCurrentState() {
  GameData_t *gameInfo = GetSingletone();
  return gameInfo->data;
}

void userInput(UserAction_t action, bool hold) {
  GameData_t *game = GetSingletone();
  switch (action) {
    case Start:
      game->FSM = PLAYING;
      FigureAdd(&(game->data), &(game->current_figure));
      break;
    case Action:
      DelFigure(&(game->data), &(game->current_figure));
      Rotation(&(game->data), &(game->current_figure));
      break;
    case Up:
      break;
    case Left:
      MoveLeft(&(game->data), &(game->current_figure));
      break;
    case Right:
      MoveRight(&(game->data), &(game->current_figure));
      break;
    case Down:
      if (!hold) {
        MoveDown(&(game->data), &(game->current_figure), &(game->FSM));
      } else {
        while (
            !MoveDown(&(game->data), &(game->current_figure), &(game->FSM))) {
        }
      }
      break;
    case Pause:
      if (game->FSM == PAUSE) {
        game->FSM = PLAYING;
        game->data.pause = 0;
      } else {
        game->data.pause = 1;
        game->FSM = PAUSE;
      }
      break;
    case Terminate:
      game->FSM = EXIT;
      break;
  }
}

void InitializeFigure(Figure_t *CurrentFigure) {
  CurrentFigure->field = (int **)calloc(5, sizeof(int *));
  if (CurrentFigure->field != NULL) {
    for (int i = 0; i < 5; i++) {
      CurrentFigure->field[i] = (int *)calloc(5, sizeof(int));
    }
  }
}

void ClearFigure(Figure_t *CurrentFigure) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      CurrentFigure->field[i][j] = 0;
    }
  }
}

void FigureAdd(GameInfo_t *GameField, Figure_t *CurrentFigure) {
  DelFigure(GameField, CurrentFigure);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (CurrentFigure->field[i][j] == 1) {
        GameField->field[CurrentFigure->x - 2 + i][CurrentFigure->y - 2 + j] =
            1;
      }
    }
  }
}

void FromNextToCurrent(Figure_t *CurrentFigure, GameInfo_t *GameField,
                       FSM_t *FSM) {
  CurrentFigure->x = 3;
  CurrentFigure->y = 4;
  ClearFigure(CurrentFigure);
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (GameField->next[i][j] == 1) {
        CurrentFigure->field[i][j] = 1;
      } else {
        CurrentFigure->field[i][j] = 0;
      }
    }
  }
  if (!CollisionCheck(GameField, CurrentFigure)) {
    NextFigureSpawn(GameField);
  } else {
    *FSM = GAMEOVER;
  }
}

void NextFigureSpawn(GameInfo_t *GameField) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      GameField->next[i][j] = 0;
    }
  }
  switch (rand() % 7) {
    case 0:
      for (int i = 0; i < 4; i++) {
        GameField->next[2][i] = 1;
      }
      break;
    case 1:
      GameField->next[1][1] = 1;
      GameField->next[2][1] = 1;
      GameField->next[2][2] = 1;
      GameField->next[2][3] = 1;
      break;
    case 2:
      GameField->next[1][3] = 1;
      GameField->next[2][1] = 1;
      GameField->next[2][2] = 1;
      GameField->next[2][3] = 1;
      break;
    case 3:
      GameField->next[1][1] = 1;
      GameField->next[1][2] = 1;
      GameField->next[2][1] = 1;
      GameField->next[2][2] = 1;
      break;
    case 4:
      GameField->next[1][2] = 1;
      GameField->next[1][3] = 1;
      GameField->next[2][1] = 1;
      GameField->next[2][2] = 1;
      break;
    case 5:
      GameField->next[1][1] = 1;
      GameField->next[1][2] = 1;
      GameField->next[2][2] = 1;
      GameField->next[2][3] = 1;
      break;
    case 6:
      GameField->next[1][2] = 1;
      GameField->next[2][1] = 1;
      GameField->next[2][2] = 1;
      GameField->next[2][3] = 1;
      break;
  }
}

int IsSquare(Figure_t *CurrentFigure) {
  int exit = 0;
  if (CurrentFigure->field[1][1] && CurrentFigure->field[1][2] &&
      CurrentFigure->field[2][1] && CurrentFigure->field[2][2]) {
    exit = 1;
  }
  return exit;
}

void Rotation(GameInfo_t *GameField, Figure_t *CurrentFigure) {
  if (!IsSquare(CurrentFigure)) {
    Figure_t NewFigure;
    InitializeFigure(&NewFigure);
    NewFigure.y = CurrentFigure->y;
    NewFigure.x = CurrentFigure->x;
    CopyFigure(CurrentFigure, &NewFigure);
    DelFigure(GameField, CurrentFigure);
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        NewFigure.field[i][j] = CurrentFigure->field[4 - j][i];
      }
    }
    if (!CollisionCheck(GameField, &NewFigure)) {
      CopyFigure(&NewFigure, CurrentFigure);
    }
    for (int i = 0; i < 5; i++) {
      free(NewFigure.field[i]);
    }
    free(NewFigure.field);
  }
}

void DelFigure(GameInfo_t *GameField, Figure_t *CurrentFigure) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (CurrentFigure->field[i][j] == 1) {
        GameField->field[CurrentFigure->x - 2 + i][CurrentFigure->y - 2 + j] =
            0;
      }
    }
  }
}

int CollisionCheck(GameInfo_t *GameField, Figure_t *NewFigure) {
  int exit = 0;
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      if (NewFigure->field[i][j] == 1) {
        if ((GameField->field[NewFigure->x - 2 + i][NewFigure->y - 2 + j] ==
             1) ||
            (NewFigure->x - 2 + i == 22)) {
          exit = 1;
        }
        if ((NewFigure->y - 2 + j == -1) ||
            (NewFigure->y - 2 + j == FIELD_WIDTH)) {
          exit = 1;
        }
      }
    }
  }

  return exit;
}

void CopyFigure(Figure_t *CurrentFigure, Figure_t *NewFigure) {
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      NewFigure->field[i][j] = CurrentFigure->field[i][j];
    }
  }
}

void MoveLeft(GameInfo_t *GameField, Figure_t *CurrentFigure) {
  Figure_t NewFigure;
  InitializeFigure(&NewFigure);
  NewFigure.y = CurrentFigure->y;
  NewFigure.x = CurrentFigure->x;
  CopyFigure(CurrentFigure, &NewFigure);
  NewFigure.y--;
  DelFigure(GameField, CurrentFigure);
  if (!CollisionCheck(GameField, &NewFigure)) {
    CopyFigure(&NewFigure, CurrentFigure);
    CurrentFigure->y--;
  }
  for (int i = 0; i < 5; i++) {
    free(NewFigure.field[i]);
  }
  free(NewFigure.field);
}

void MoveRight(GameInfo_t *GameField, Figure_t *CurrentFigure) {
  Figure_t NewFigure;
  InitializeFigure(&NewFigure);
  NewFigure.y = CurrentFigure->y;
  NewFigure.x = CurrentFigure->x;
  CopyFigure(CurrentFigure, &NewFigure);
  NewFigure.y++;
  DelFigure(GameField, CurrentFigure);
  if (!CollisionCheck(GameField, &NewFigure)) {
    CopyFigure(&NewFigure, CurrentFigure);
    CurrentFigure->y++;
  }
  for (int i = 0; i < 5; i++) {
    free(NewFigure.field[i]);
  }
  free(NewFigure.field);
}

int MoveDown(GameInfo_t *GameField, Figure_t *CurrentFigure, FSM_t *FSM) {
  int exit = 0;
  if (*FSM == PLAYING) {
    Figure_t NewFigure;
    InitializeFigure(&NewFigure);
    NewFigure.y = CurrentFigure->y;
    NewFigure.x = CurrentFigure->x;
    CopyFigure(CurrentFigure, &NewFigure);
    if (NewFigure.x < FIELD_HEIGHT) {
      NewFigure.x++;
      DelFigure(GameField, CurrentFigure);
      if (!CollisionCheck(GameField, &NewFigure)) {
        CopyFigure(&NewFigure, CurrentFigure);
        CurrentFigure->x++;
      } else {
        FigureAdd(GameField, CurrentFigure);
        FromNextToCurrent(CurrentFigure, GameField, FSM);
        exit = 1;
      }
    }
    for (int i = 0; i < 5; i++) {
      free(NewFigure.field[i]);
    }
    free(NewFigure.field);
  }
  return exit;
}

void DropLine(GameInfo_t *GameField, int i) {
  for (int j = i; j > 2; j--) {
    for (int k = 0; k < FIELD_WIDTH; k++) {
      GameField->field[j][k] = GameField->field[j - 1][k];
    }
  }
}

int IsLineFilled(GameInfo_t *GameField, int i) {
  int exit = 1;
  for (int j = 0; j < FIELD_WIDTH; j++) {
    if (GameField->field[i][j] == 0) {
      exit = 0;
    }
  }
  return exit;
}

void ScoreUpdater(GameInfo_t *GameField, int lines_counter) {
  switch (lines_counter) {
    case 1:
      GameField->score += 100;
      break;
    case 2:
      GameField->score += 300;
      break;
    case 3:
      GameField->score += 700;
      break;
    case 4:
      GameField->score += 1500;
  }
  if (GameField->score > GameField->high_score) {
    GameField->high_score = GameField->score;
  }
}

void LineChecker(GameInfo_t *GameField) {
  int lines_counter = 0;
  for (int i = 22; i >= 2; i--) {
    int j = 0;
    while (j != FIELD_WIDTH) {
      if (IsLineFilled(GameField, i)) {
        lines_counter++;
        DropLine(GameField, i);
        j = 0;
      } else {
        j++;
      }
    }
  }
  if (lines_counter != 0) {
    ScoreUpdater(GameField, lines_counter);
  }
}

void HighscoreChecker(GameInfo_t *GameField) {
  FILE *hs_file;
  hs_file = fopen("highscore_tetris.txt", "r");
  int hs;
  fscanf(hs_file, "%d", &hs);
  if (GameField->high_score > hs) {
    fclose(hs_file);
    hs_file = fopen("highscore_tetris.txt", "w");
    fprintf(hs_file, "%d", GameField->high_score);
  }
  fclose(hs_file);
}

double TimeCalculator(int level) {
  return (pow(0.8 - ((level - 1) * 0.007), level - 1));
}

void SpeedChecker(GameInfo_t *GameField) {
  if (GameField->level <= 10) {
    GameField->speed = TimeCalculator(GameField->level) * 500;
    GameField->level = GameField->score / 600 + 1;
  }
}

void GameClose(GameInfo_t *GameField, Figure_t *CurrentFigure) {
  for (int i = 0; i < FIELD_HEIGHT; i++) {
    free(GameField->field[i]);
  }
  free(GameField->field);
  for (int i = 0; i < 5; i++) {
    free(GameField->next[i]);
  }
  free(GameField->next);
  for (int i = 0; i < 5; i++) {
    free(CurrentFigure->field[i]);
  }
  free(CurrentFigure->field);
}

void RemoveGameData() {
  GameData_t *game = GetSingletone();
  GameClose(&(game->data), &(game->current_figure));
  free(game);
}