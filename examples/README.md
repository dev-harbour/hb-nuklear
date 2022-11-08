# hb-nuklear

1. Browse to the file `src/nuklear.c` and select backend:

   ```
   #define NK_ALLEGRO5_IMPLEMENTATION
   #include "hb_nuklear_allegro5.h"

   #define NK_GLFW_GL2_IMPLEMENTATION
   #include "hb_nuklear_glfw_gl2.h"

   #define NK_SDL_GL2_IMPLEMENTATION
   #include "hb_nuklear_sdl_gl2.h"

   #define NK_XLIB_IMPLEMENTATION
   #include "hb_nuklear_xlib.h"
   ```

## Installing on Windows

- mingw-w64

   ```
   pacman -S mingw-w64-x86_64-glfw
   ```
   necessary packages and environment variable

   e.g.

   ```
   export HB_WITH_GLFW=/mingw64/include/GLFW
   ```

## Installing on Linux

- Debian

   ```
   sudo apt-get install liballegro5-dev
   ```

   ```
   sudo apt-get install libcsfml-dev
   ```

   ```
   sudo apt-get install libglfw3-dev
   ```

   ```
   sudo apt-get install libsdl2-dev
   ```

   ```
   sudo apt-get install -y libx11-dev
   ```

## Installing on Mac OSX

