#ifndef GUI_DESKTOP_SNAKE_WINDOW_H
#define GUI_DESKTOP_SNAKE_WINDOW_H

#include "../../brick_game/snake/snake.h"
#include "gui.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow() : m_VPaned(Gtk::Orientation::HORIZONTAL), m_Label_Field("FIELD"), m_Label_Info("INFO")  
{
  set_title ("SNAKE");
  set_default_size(380, 200);
  set_can_focus(true);
  m_VPaned.set_margin(1);

  set_child(m_VPaned);

  game = s21::GetSingletone();

  m_VPaned.set_start_child(m_Label_Field);
  m_VPaned.set_end_child(m_Label_Info);
  update_labels(&(game->data));

  // timer 
  m_key_press_timeout_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ExampleWindow::on_no_key_press), 500);

  // keyboard events
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_window_key_pressed), false);
  add_controller(controller);
}
  virtual ~ExampleWindow() {
    s21::RemoveGameData();
  }

void update_labels(GameInfo_t* GameInfo) {
  FSM_t FSM = s21::GetSingletone()->FSM;
  m_Label_Field.set_text(update_field_label (GameInfo));
  m_Label_Info.set_text(update_info_label (GameInfo, FSM));
}

void update_window(GameInfo_t* GameInfo) {
  update_labels(GameInfo);
  timer_update();
}

void tick() {
  s21::GameData_t *game = s21::GetSingletone();
  game->Snake.remove_snake_from_field(game->data.field);
  game->Snake.move_snake(&(game->FSM));
  game->Snake.add_snake_to_field(game->data.field);
  s21::score_check(&(game->data), game->Snake, game->FSM);
  s21::level_check(&(game->data));
}

bool on_window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state) {
  UserAction_t action;
  switch (keyval) {
    case GDK_KEY_Up:
      action = Up;
      s21::userInput(action, false);
      break;
    case GDK_KEY_Down:
      action = Down;
      s21::userInput(action, false);
      break;
    case GDK_KEY_Left:
      action = Left;
      s21::userInput(action, false);
      break;
    case GDK_KEY_Right:
      action = Right;
      s21::userInput(action, false);
      break;
    case GDK_KEY_Return:
      if (game->FSM==START) { 
        game->FSM = PLAYING;
      }
      break;
    case GDK_KEY_p:
      if (game->data.pause == 0) {
        game->data.pause = 1;
        game->FSM=PAUSE;}
      else {
        game->data.pause = 0;
        game->FSM=PLAYING;
      };
      break;
    case GDK_KEY_q:
      game->FSM = EXIT;
      close();
      break;
    default:
      return false;
  }
  tick();
  update_window(&(game->data));
  return true;
}

bool on_no_key_press()
{ 
  timer_update();
  tick();
  update_labels(&(game->data));
  return true;
}

void timer_update () {
  s21::GameData_t *game = s21::GetSingletone();
  m_key_press_timeout_conn.disconnect();
  m_key_press_timeout_conn = Glib::signal_timeout().connect(sigc::mem_fun(*this, &ExampleWindow::on_no_key_press), game->data.speed);
}

protected:

  Gtk::Paned m_VPaned;
  Gtk::Label m_Label_Field;
  Gtk::Label m_Label_Info;
  s21::GameData_t *game;
  sigc::connection m_key_press_timeout_conn;
};


#endif //GUI_DESKTOP_SNAKE_WINDOW_H
