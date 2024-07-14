#include "../../gui/desktop/tetris_window.h"

int main(int argc, char* argv[])
{ 
  srand(time(NULL));
  auto app = Gtk::Application::create("Game.window");

  return app->make_window_and_run<ExampleWindow>(argc, argv);
}