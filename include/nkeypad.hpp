/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *

nkeypad - nkeypad.hpp

Copyright (c) 2017 Christopher M. Short

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

#ifndef _NKEYPAD_HPP
#define _NKEYPAD_HPP

// ------- INCLUDES ------- //

#include <curses.h>

#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

// ------- DEFINES ------- //

#define CTRL_KEY(x) ((x) & 0x1f)

// ------- keypad Class ------- //

class nKeypad {
private:
  bool initialized;
  int height;
  int width;
  int min_x;
  int min_y;
  int max_x;
  int max_y;

  int key;

  void drawFrame();
  void drawText();

public:
  nKeypad() {}
  ~nKeypad() {}

  void initialize();
  void update();
  void finalize();

  void setInit(const bool& value) { initialized = value; }
  const bool& getInit() { return initialized; }

};

#endif // _NKEYPAD_HPP
