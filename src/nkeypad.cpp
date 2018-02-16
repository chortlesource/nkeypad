/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

nkeypad - nkeypad.cpp

Copyright (c) 2017 Christopher M. Short

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#include <nkeypad.hpp>

// ------- nKeypad Implementation ------- //

void nKeypad::drawFrame() {
  char padding = ' ';
  wattron(stdscr, COLOR_PAIR(2));
  for(int a = min_x; a < max_x; a++) {
    for(int b = min_y; b < max_y; b++)
      mvwaddch(stdscr, b, a, padding);
  }
  wattroff(stdscr, COLOR_PAIR(2));
  std::string banner = " | nkeypad - 0.01-B | ";

  mvwprintw(stdscr, min_y - 2, max_x - banner.size(), banner.c_str());
  mvwprintw(stdscr, max_y + 1, min_x + 1, "Press ENTER to Quit");
}

void nKeypad::drawText() {
  std::string charstr = "KEY: ";
  std::string intstr = "INT: ";
  std::string hexstr = "HEX: ";
  std::string binstr = "BIN: ";
  std::string ctrlstr = "CTRL: ";

  if(key > 0) {
    // Add key character
    charstr.push_back(static_cast<char>(key));

    // Handle Ctrl
    if((key & 0xE0) == 0)
      ctrlstr.append("YES");
    else
      ctrlstr.append("NO");

    // Display keycode
    intstr.append(std::to_string(key));

    // Display the hex
    std::stringstream hss;
    hss << std::uppercase << std::setfill('0') << std::setw(2) << std::hex << key;
    hexstr.append(hss.str());

    // Binary
    std::bitset<8> k(key);
    binstr.append(k.to_string<char,std::string::traits_type, std::string::allocator_type>());
  }
  
  // Display the text
  int pos_x = min_x + 1;
  int pos_y = min_y + 2;

  const char *message1 = "Note that Ctrl does not affect certain special characters and may";
  const char *message2 = "not be detected as in use when depressed. You should compare binary";
  const char *message3 = "and integer output to ensure that Ctrl influences the key.";

  wattron(stdscr, COLOR_PAIR(2));
  mvwprintw(stdscr, pos_y + 1, pos_x, charstr.c_str());
  mvwprintw(stdscr, pos_y + 2, pos_x, intstr.c_str());
  mvwprintw(stdscr, pos_y + 3, pos_x, hexstr.c_str());
  mvwprintw(stdscr, pos_y + 4, pos_x, binstr.c_str());
  mvwprintw(stdscr, pos_y + 6, pos_x, ctrlstr.c_str());
  mvwprintw(stdscr, pos_y + 8, pos_x, message1);
  mvwprintw(stdscr, pos_y + 9, pos_x, message2);
  mvwprintw(stdscr, pos_y + 10, pos_x, message3);
  wattroff(stdscr, COLOR_PAIR(2));

}

void nKeypad::initialize() {
  initialized = false;

  // Initialize basic variables
  key = 0;
  curs_set(0);
  init_pair(2, COLOR_BLACK, COLOR_WHITE);
  getmaxyx(stdscr, height, width);
  min_x = 2;
  min_y = 2;
  max_x = width - 2;
  max_y = height - 2;

  //

  initialized = true;
}

void nKeypad::update() {
  drawFrame();
  drawText();
  key = getch();
  switch(key) {
    case '\n':
    case '\r':
    case KEY_ENTER:
      {
        initialized = false;
        break;
      }
      default:
        break;
  }
}

void nKeypad::finalize() {

}

// ------- MAIN FUNCTION ------- //

int main(int argc, const char *argv[]) {
  initscr();
  keypad(stdscr, true);
  cbreak();
  noecho();

  // Check terminal for colours
  if(has_colors() == false) {
    endwin();
    std::cerr << "[ERROR]: This terminal does not support colours.\n" << std::endl;
    return 1;
  }

  start_color();

  nKeypad *pad = new nKeypad();
  pad->initialize();

  while(pad->getInit() == true) {
    // Main application loop
    pad->update();
  }

  endwin();
  pad->finalize();
  delete pad;
  return 0;
}
