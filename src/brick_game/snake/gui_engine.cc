#include "../../gui/desktop/snake_window.h"

int main(int argc, char* argv[]) {
  auto app = Gtk::Application::create("Game.window");

  return app->make_window_and_run<ExampleWindow>(argc, argv);
}