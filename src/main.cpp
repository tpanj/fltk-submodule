//
// Simple test of the Fl_Native_File_Chooser.
//
// Copyright 1998-2016 by Bill Spitzak and others.
// Copyright 2004 Greg Ercolano.
//
// This library is free software. Distribution and use rights are outlined in
// the file "COPYING" which should have been included with this file.  If this
// file is missing or damaged, see the license at:
//
//     https://www.fltk.org/COPYING.php
//
// Please see the following page on how to report bugs and issues:
//
//     https://www.fltk.org/bugs.php
//
#include <stdio.h>
#include <string.h>             /* strstr() */
#include <FL/Fl.H>
#include <FL/fl_ask.H>          /* fl_beep() */
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Native_File_Chooser.H>

#include <FL/Fl_Shared_Image.H>

#define TERMINAL_HEIGHT 120

// GLOBALS
Fl_Input *G_filename = NULL;
Fl_Input *G_filename2 = NULL;
// Fl_Multiline_Input *G_filter = NULL;
// Fl_Terminal *G_tty = NULL;

void PickFile_CB(Fl_Widget*, void*) {
  // Create native chooser
  Fl_Native_File_Chooser native;
  native.title("Pick a file");
  native.type(Fl_Native_File_Chooser::BROWSE_FILE);
//   native.filter(G_filter->value());
  native.preset_file(G_filename->value());
  // Show native chooser
  switch ( native.show() ) {
//     case -1: G_tty->printf("ERROR: %s\n", native.errmsg()); break;      // ERROR
//     case  1: G_tty->printf("*** CANCEL\n"); fl_beep(); break;           // CANCEL
    default:                                                            // PICKED FILE
      if ( native.filename() ) {
        G_filename->value(native.filename());
//         G_tty->printf("filename='%s'\n", native.filename());
      } else {
        G_filename->value("NULL");
//         G_tty->printf("filename='(null)'\n");
      }
      break;
  }
}

void PickDir_CB(Fl_Widget*, void*) {
  // Create native chooser
  Fl_Native_File_Chooser native;
  native.title("Pick a Directory");
  native.directory(G_filename->value());
  native.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
  // Show native chooser
  switch ( native.show() ) {
//     case -1: G_tty->printf("ERROR: %s\n", native.errmsg()); break;      // ERROR
//     case  1: G_tty->printf("*** CANCEL\n"); fl_beep(); break;           // CANCEL
    default:                                                            // PICKED DIR
      if ( native.filename() ) {
        G_filename->value(native.filename());
//         G_tty->printf("dirname='%s'\n", native.filename());
      } else {
        G_filename->value("NULL");
//         G_tty->printf("dirname='(null)'\n");
      }
      break;
  }
}

int main(int argc, char **argv) {
  /* For a nicer looking browser under linux/unix, call fl_register_images()
    (If you do this, you'll need to link with fltk_images).
    That's required for the preview option of the GTK filechooser.
    In the unlikely situation where no native filechooser is found on
    the active Linux system, FLTK reverts to using its own file chooser
    (Fl_File_Chooser) which looks best if you also call
    Fl_File_Icon::load_system_icons().

    None of that is useful for the native file chooser under macOS or Windows.
   */
#if defined(FLTK_USE_X11) || defined(FLTK_USE_WAYLAND)
  fl_register_images();
  Fl_File_Icon::load_system_icons();
#endif

  int argn = 1;
#ifdef __APPLE__
  // OS X may add the process number as the first argument - ignore
  if (argc>argn && strncmp(argv[argn], "-psn_", 5)==0) ++argn;
#endif

  // Parse preset filename (if any)
  char *filename = 0;
  if ( argc>argn && argv[argn][0] != '-' ) {
    filename = argv[argn++];
  }

  Fl_Window *win = new Fl_Window(640+640+60, 512+20+TERMINAL_HEIGHT, "Native File Chooser Test");
    Fl_Box box(30,40,30+640,40+512);
    box.box(FL_THIN_DOWN_BOX);

    Fl_Box box2(30+640,40,30+640,40+512);
    box2.box(FL_THIN_DOWN_BOX);
  win->size_range(win->w(), win->h(), 0, 0);
  win->begin();
  {

    int x = 80, y = 10;
    G_filename = new Fl_Input(x, y, 640-40, 25, "Filename");
    G_filename->value(filename ? filename : ".");
    G_filename->tooltip("Default filename");

    G_filename2 = new Fl_Input(x+640, y, 640-20, 25, "File2");
    G_filename2->value(filename ? filename : ".");

    y += G_filename->h() + 10;
//     G_filter = new Fl_Multiline_Input(x, y, G_filename->w(), 100, "Filter");
//     G_filter->value("Text\t*.txt\n"
//                     "C Files\t*.{cxx,h,c,cpp}\n"
//                     "Tars\t*.{tar,tar.gz}\n"
//                     "Apps\t*.app");
//     G_filter->tooltip("Filter to be used for browser.\n"
//                       "An empty string may be used.\n");

//     y += G_filter->h() + 10;


    Fl_Button *but = new Fl_Button(20, 10, 60, 25, "Pick File");
    but->callback(PickFile_CB);

    Fl_Button *but2 = new Fl_Button(20+640, 10, 60, 25, "File2");
    but2->callback(PickFile_CB);

//    Fl_Button *butdir = new Fl_Button(but->x()-x-10, win->h()-TERMINAL_HEIGHT-25-10, 80, 25, "Pick Dir");
//    butdir->callback(PickDir_CB);

//     win->resizable(G_filter);
  }
  win->end();
  // Pass show() remaining args we haven't already parsed..
  {
    char **args = argv+(argn-1);
    int   nargs = argc-(argn-1);
    win->show(nargs, args);
  }
  return(Fl::run());
}
