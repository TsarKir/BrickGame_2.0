#ifndef SRC_BRICK_GAME_SNAKE_SNAKE_H
#define SRC_BRICK_GAME_SNAKE_SNAKE_H

/**
 * @file snake.h
 * @brief header with snake game logic
 */

#include <cmath>
#include <deque>
#include <fstream>
#include <iostream>

#include "../common/common.h"

namespace s21 {
/**
 * @brief direction enumeration
 *
 */
typedef enum { UP, DOWN, LEFT, RIGHT } direction_t;
/**
 * @brief Snake class
 *
 * Class with snake game
 *
 */
class snake {
  /**
   * @brief private attributes
   * @param size_ snake size
   * @param body_ deque with snake body segments
   * @param direction_ snake directions
   *
   */
 private:
  std::deque<std::pair<int, int>> body_;
  int size_;
  direction_t direction_;

  /**
   * @brief public attributes
   * @param apple_ int pair with x and y coord of apple
   */
  std::pair<int, int> apple_;
  /**
   * @brief snake constructor
   *
   */
 public:
  snake() {
    add_segment_back(5, 4);
    add_segment_back(4, 4);
    add_segment_back(3, 4);
    add_segment_back(2, 4);
    size_ = 4;
    direction_ = DOWN;
    spawn_apple();
  }
  /**
   * @brief snake destructor
   *
   */
  ~snake() {}
  /**
   * @brief apple spawner
   * Spawns apple in random place of the field
   *
   */
  void spawn_apple() {
    srand(time(0));
    int newX;
    int newY;
    bool not_snake = false;
    while (!not_snake) {
      not_snake = true;
      newX = 2 + rand() % (FIELD_HEIGHT - 5);
      newY = rand() % (FIELD_WIDTH - 1);
      for (int i = 0; i < size_; i++) {
        if (body_[i].first == newX && body_[i].second == newY) {
          not_snake = false;
          break;
        }
      }
    }
    apple_.first = newX;
    apple_.second = newY;
  }
  /**
   * @brief setting direction
   * Sets direction of the snake
   *
   */
  void set_direction(direction_t new_dir) {
    switch (new_dir) {
      case DOWN:
        if (this->direction_ != UP) {
          this->direction_ = new_dir;
        }
        break;
      case UP:
        if (this->direction_ != DOWN) {
          this->direction_ = new_dir;
        }
        break;
      case LEFT:
        if (this->direction_ != RIGHT) {
          this->direction_ = new_dir;
        }
        break;
      case RIGHT:
        if (this->direction_ != LEFT) {
          this->direction_ = new_dir;
        }
        break;
    }
  }
  /**
   * @brief size getter
   *
   */
  int get_size() { return size_; }
  /**
   * @brief adding new segment to snake end
   *
   * Adds new segment to snake end
   *
   * @param argc 2
   * @param x int with x coordinates of new segment
   * @param y int with y coordinates of new segment
   *
   *
   */
  void add_segment_back(int x, int y) { body_.push_back({x, y}); }
  /**
   * @brief adding new segment to snake head
   *
   * Adds new segment to snake head
   *
   * @param argc 2
   * @param x int with x coordinates of new segment
   * @param y int with y coordinates of new segment
   *
   *
   */
  void add_segment_front(int x, int y) { body_.push_front({x, y}); }
  /**
   * @brief snake moving
   *
   * Moves snake
   *
   * @param argc 1
   * @param FSM current state of the game
   *
   */
  void move_snake(FSM_t *FSM) {
    if (*FSM == PLAYING) {
      int newX = body_[0].first;
      int newY = body_[0].second;
      switch (direction_) {
        case DOWN:
          newX = body_[0].first + 1;
          break;
        case UP:
          newX = body_[0].first - 1;
          break;
        case LEFT:
          newY = body_[0].second - 1;
          break;
        case RIGHT:
          newY = body_[0].second + 1;
          break;
      }

      if (newX < 2 || newX >= FIELD_HEIGHT - 2 || newY < 0 ||
          newY >= FIELD_WIDTH) {
        *FSM = GAMEOVER;
        return;
      }

      for (size_t i = 1; i < body_.size(); i++) {
        if (body_[i].first == newX && body_[i].second == newY) {
          *FSM = GAMEOVER;
          return;
        }
      }
      add_segment_front(newX, newY);
      bool ate = false;
      if (body_[0].first == apple_.first && body_[0].second == apple_.second) {
        spawn_apple();
        ate = true;
        size_++;
      }
      if (!ate) {
        body_.pop_back();
      }
    }
  }
  /**
   * @brief adding snake to field
   *
   * Adds snake to the game field
   *
   * @param argc 1
   * @param field game field
   *
   */
  void add_snake_to_field(int **field) {
    field[apple_.first][apple_.second] = 2;
    for (auto &i : body_) {
      if (field[i.first][i.second] == 0) {
        if (i.first == body_[0].first && i.second == body_[0].second) {
          field[i.first][i.second] = 3;
        } else {
          field[i.first][i.second] = 1;
        }
      }
    }
  }
  /**
   * @brief removing snake to field
   *
   * Removes snake from the game field
   *
   * @param argc 1
   * @param field game field
   *
   */
  void remove_snake_from_field(int **field) {
    for (auto &i : body_) {
      field[i.first][i.second] = 0;
    }
    field[apple_.first][apple_.second] = 0;
  }

};  // snake class

/**
 * @brief GameData_t structure
 *
 * @param data GameInfo_t structure
 * @param FSM FSM_t structure
 * @param snake snake object
 *
 */
typedef struct {
  GameInfo_t data;
  FSM_t FSM;
  snake Snake;
} GameData_t;
/**
 * @brief reading highscore from the file
 *
 * Reads highscore from the file
 *
 * @param argc 1
 * @param field game field
 *
 */
void ReadHighScore(GameInfo_t *GameInfo) {
  std::ifstream hs_file("highscore_snake.txt");
  if (hs_file.is_open()) {
    hs_file >> GameInfo->high_score;
    hs_file.close();
  } else {
    std::cerr << "Unable to open highscore_snake.txt" << std::endl;
  }
}
/**
 * @brief Game info initialization
 *
 * Creates game info with initial parametres and memory allocation
 * score = 0
 * pause = 0
 * high_score = takes from highscore_snake.txt
 * level = 1
 *
 * @param argc 1
 * @param GameInfo Game info
 *
 *
 *
 */
void InitializeGameInfo(GameInfo_t *GameInfo) {
  GameInfo->score = 0;
  GameInfo->pause = 0;
  GameInfo->high_score = 0;
  GameInfo->level = 1;
  GameInfo->next = nullptr;
  GameInfo->speed = START_SPEED;

  ReadHighScore(GameInfo);

  GameInfo->field = new int *[FIELD_HEIGHT];
  if (GameInfo->field != nullptr) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      GameInfo->field[i] = new int[FIELD_WIDTH]();
    }
  }
}
/**
 * @brief Singleton returner
 *
 */
GameData_t *GetSingletone() {
  static GameData_t *game_structure = NULL;
  if (game_structure == NULL) {
    game_structure = new GameData_t;
    if (game_structure != NULL) {
      InitializeGameInfo(&(game_structure->data));
      game_structure->FSM = START;
      game_structure->Snake = snake();
    }
  }
  return game_structure;
}
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
void userInput(UserAction_t action, bool hold) {
  GameData_t *game = GetSingletone();
  switch (action) {
    case Start:
      game->FSM = PLAYING;
      break;
    case Left:
      game->Snake.set_direction(s21::LEFT);
      break;
    case Right:
      game->Snake.set_direction(s21::RIGHT);
      break;
    case Down:
      game->Snake.set_direction(s21::DOWN);
      break;
    case Up:
      game->Snake.set_direction(s21::UP);
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
/**
 * @brief Updates current game state
 *
 */
GameInfo_t updateCurrentState() {
  GameData_t *gameInfo = GetSingletone();
  return gameInfo->data;
}
/**
 * @brief Field remover
 *
 * Deletes memory allocated for gamefield
 * @param argc 1
 * @param GameInfo Game info
 *
 *
 */
void RemoveField(GameInfo_t *GameInfo) {
  if (GameInfo->field != nullptr) {
    for (int i = 0; i < FIELD_HEIGHT; i++) {
      delete[] GameInfo->field[i];
    }
    delete[] GameInfo->field;
  }
}

void RemoveGameData() {
  GameData_t *gameInfo = GetSingletone();
  RemoveField(&(gameInfo->data));
  delete gameInfo;
}
/**
 * @brief Score checker
 *
 * Updates score depends on size
 * @param argc 3
 * @param GameInfo Game Info
 * @param Snake snake object
 * @param FSM game states
 *
 *
 */
void score_check(GameInfo_t *GameInfo, snake Snake, FSM_t FSM) {
  GameInfo->score = Snake.get_size() - 4;
  if (GameInfo->score == 200) {
    FSM = GAMEOVER;
  }
}
/**
 * @brief Time calculator
 *
 * Calculates speed, depends on level
 * @param argc 1
 * @param level level of the game
 *
 * @return double with speed of the game
 *
 */
double time_calculator(int level) {
  return (pow(0.8 - ((level - 1) * 0.007), level - 1));
}
/**
 * @brief Highscore checker
 *
 * Checks is score is higher than highscore, if yes, updates highscore
 * @param argc 1
 * @param GameInfo Game Info
 *
 *
 */
void high_score_check(GameInfo_t *GameInfo) {
  if (GameInfo->score > GameInfo->high_score) {
    GameInfo->high_score = GameInfo->score;
    std::ofstream hs_file("highscore_snake.txt");
    if (hs_file.is_open()) {
      hs_file << GameInfo->high_score;
      hs_file.close();
    } else {
      std::cerr << "Unable to open highscore_snake.txt" << std::endl;
    }
  }
}
/**
 * @brief Speed checker
 *
 * Updates speed of the game depending on level and updates level depending on
 * score
 * @param argc 1
 * @param GameInfo Game Info
 *
 *
 */
void level_check(GameInfo_t *GameInfo) {
  if (GameInfo->level < 10) {
    GameInfo->speed = START_SPEED * time_calculator(GameInfo->level);
    GameInfo->level = GameInfo->score / 5 + 1;
  }
}

}  // namespace s21

#endif  // SRC_BRICK_GAME_SNAKE_SNAKE_H