#ifndef GUI_DESKTOP_GUI_H
#define GUI_DESKTOP_GUI_H

#include <string>
#include <gtkmm.h>
#include "../../brick_game/common/common.h"

std::string update_field_label (GameInfo_t* GameInfo) {
    std::string str = "";
    for (int i = 2; i < 22; i++) {
      for (int j = 0; j < FIELD_WIDTH; j++) {
        if (GameInfo->field[i][j] == 0) {
          str += "\u2B1B"; // black
        }
        else if (GameInfo->field[i][j] == 1) {
          str += "\U0001F7E9"; // green
        }
        else if (GameInfo->field[i][j] == 2) {
          str += "\U0001F7E5"; // red
        }
        else if (GameInfo->field[i][j] == 3) {
          str += "\U0001F7E8"; // yellow
        }
      }
      str += '\n';
    }
    return str;
  }

std::string update_info_label (GameInfo_t* GameInfo, FSM_t FSM) {
  std::string str = "";
  str+= "SCORE\n";
  str+= std::to_string(GameInfo->score);
  str+= "\nHIGHSCORE\n";
  str+= std::to_string(GameInfo->high_score);
  if (GameInfo->next!=nullptr) {
    str+= "\nNEXT\n";
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (GameInfo->next[i][j] == 1) {
                str += "\U0001F7E9"; // green
            } else {
                str += "      ";
            }
        }   
        str+="\n";
    }
  }
  else {
    str+= "\n\n\n\n\n";
  }
  str+= "\n\n\n\n\nLEVEL\n";
  str+= std::to_string(GameInfo->level);
  if (GameInfo->pause==1) {
    str+= "\n\n\nPAUSE\n";
  }
  else if (FSM == GAMEOVER) {
    str+= "\n\n\nGAME OVER\n";
  }
  else if (FSM == START){
    str+= "\n\n\nPRESS ENTER\n";
  }
  return str;
}

#endif //GUI_DESKTOP_GUI_H