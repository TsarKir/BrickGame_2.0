#ifndef GUI_DESKTOP_TETRIS_WINDOW_H
#define GUI_DESKTOP_TETRIS_WINDOW_H

#include "../../brick_game/tetris/tetris.h"
#include "gui.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow() : m_VPaned(Gtk::Orientation::HORIZONTAL), m_Label_Field("FIELD"), m_Label_Info("INFO")  
{
  set_title ("TETRIS");
  set_default_size(380, 200);
  set_can_focus(true);
  m_VPaned.set_margin(1);

  set_child(m_VPaned);
  previous_down = false;

  game = GetSingletone();

  m_VPaned.set_start_child(m_Label_Field);
  m_VPaned.set_end_child(m_Label_Info);
  update_labels(&(game->data));

  // timer 
  m_key_press_timeout_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ExampleWindow::on_no_key_press), START_SPEED);

  // keyboard events
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_window_key_pressed), false);
  add_controller(controller);
}
  virtual ~ExampleWindow() {
    RemoveGameData();
  }

void update_labels(GameInfo_t* GameInfo) {
  FSM_t FSM = GetSingletone()->FSM;
  m_Label_Field.set_text(update_field_label (GameInfo));
  m_Label_Info.set_text(update_info_label (GameInfo, FSM));
}

void update_window(GameInfo_t* GameInfo) {
  update_labels(GameInfo);
  timer_update();
}

void tick() {
  GameData_t *game = GetSingletone();
  DelFigure(&(game->data), &(game->current_figure));
  MoveDown(&(game->data), &(game->current_figure), &(game->FSM));
  LineChecker(&(game->data));
  FigureAdd(&(game->data), &(game->current_figure));
  SpeedChecker(&(game->data));
  HighscoreChecker(&(game->data));
  previous_down = false;
}

bool on_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {
  if (game->FSM==GAMEOVER && keyval!=GDK_KEY_q) {
      return false;
  }
  key_pressed = true;
  UserAction_t action;
  switch (keyval) {
    case GDK_KEY_space:
      action = Action;
      userInput(action, false);
      break;
    case GDK_KEY_Down:
      action = Down;
      if (!previous_down) {
        userInput(action, false);
        previous_down = true;
      }
      else {
        userInput(action, true);
      }
      break;
    case GDK_KEY_Left:
      action = Left;
      userInput(action, false);
      break;
    case GDK_KEY_Right:
      action = Right;
      userInput(action, false);
      break;
    case GDK_KEY_Return:
      if (game->FSM == START) {
        game->FSM = PLAYING;
      }
      FromNextToCurrent(&(game->current_figure),&(game->data),&(game->FSM));
      break;
    case GDK_KEY_p:
      if (game->data.pause == 0) {
        game->data.pause = 1;
        game->FSM = PAUSE;
      } else {
        game->data.pause = 0;
        game->FSM = PLAYING;
      }
      break;
    case GDK_KEY_q:
      game->FSM = EXIT;
      close();
      break;
    default:
      return false;
  }
  FigureAdd(&(game->data), &(game->current_figure));
  update_labels(&(game->data));

  return true;
}

bool on_no_key_press() {
  tick();
  update_window(&(game->data));
  key_pressed = false;
  previous_down = false;
  return true;
}

void timer_update () {
  GameData_t *game = GetSingletone();
  m_key_press_timeout_conn.disconnect();
  m_key_press_timeout_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ExampleWindow::on_no_key_press), game->data.speed);
}

protected:

  Gtk::Paned m_VPaned;
  Gtk::Label m_Label_Field;
  Gtk::Label m_Label_Info;
  GameData_t *game;
  sigc::connection m_key_press_timeout_conn;
  bool key_pressed;
  bool previous_down;
  
};


#endif //GUI_DESKTOP_TETRIS_WINDOW_H
