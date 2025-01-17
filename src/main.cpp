#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main() {
    Fl_Window window(400, 300, "Hello FLTK");
    Fl_Box box(100, 100, 200, 100, "Hello, World!");
    window.show();
    return Fl::run();
}
