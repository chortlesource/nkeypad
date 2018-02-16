# nkeypad

## C++ Ncurses keycode translator
nkeypad is a simple ncurses tool that provider the user with the translation of individual keystrokes into Decimal, Binary, Hexadecimal values. It also detects when the modifier key (Ctrl) is depressed with keys that can be modified.

![nkeypad running in terminal](gfx/nkeypad.jpg?raw=true "nKeypad")

## Dependencies
* C++11
* ncurses

## Build
* git clone git@github.com:chortlesource/nkeypad.git
* cd nkeypad
* mkdir build && cd build
* cmake ..
* make

## Copyright
Copyright (c) 2017 C. M. Short

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
