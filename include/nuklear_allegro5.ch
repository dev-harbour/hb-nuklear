/*
 *
 */

#ifndef NUKLEAR_ALLEGRO5_CH_
#define NUKLEAR_ALLEGRO5_CH_

#include "nuklear.ch"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* Allegro */

/* Possible bit combinations for the flags parameter of al_create_display. */
#define ALLEGRO_WINDOWED                    1
#define ALLEGRO_FULLSCREEN                  2
#define ALLEGRO_OPENGL                      4
#define ALLEGRO_DIRECT3D_INTERNAL           8
#define ALLEGRO_RESIZABLE                   16
#define ALLEGRO_FRAMELESS                   32
#define ALLEGRO_NOFRAME                     ALLEGRO_FRAMELESS /* older synonym */
#define ALLEGRO_GENERATE_EXPOSE_EVENTS      64
#define ALLEGRO_OPENGL_3_0                  128
#define ALLEGRO_OPENGL_FORWARD_COMPATIBLE   256
#define ALLEGRO_FULLSCREEN_WINDOW           512
#define ALLEGRO_MINIMIZED                   1024
#define ALLEGRO_PROGRAMMABLE_PIPELINE       2048
#define ALLEGRO_GTK_TOPLEVEL_INTERNAL       4096
#define ALLEGRO_MAXIMIZED                   8192
#define ALLEGRO_OPENGL_ES_PROFILE           16384

#define ALLEGRO_OPENGL_CORE_PROFILE         32768

/* Possible parameters for al_set_display_option.
 * Make sure to update ALLEGRO_EXTRA_DISPLAY_SETTINGS if you modify
 * anything here.
 */
#define ALLEGRO_RED_SIZE                 0
#define ALLEGRO_GREEN_SIZE               1
#define ALLEGRO_BLUE_SIZE                2
#define ALLEGRO_ALPHA_SIZE               3
#define ALLEGRO_RED_SHIFT                4
#define ALLEGRO_GREEN_SHIFT              5
#define ALLEGRO_BLUE_SHIFT               6
#define ALLEGRO_ALPHA_SHIFT              7
#define ALLEGRO_ACC_RED_SIZE             8
#define ALLEGRO_ACC_GREEN_SIZE           9
#define ALLEGRO_ACC_BLUE_SIZE            10
#define ALLEGRO_ACC_ALPHA_SIZE           11
#define ALLEGRO_STEREO                   12
#define ALLEGRO_AUX_BUFFERS              13
#define ALLEGRO_COLOR_SIZE               14
#define ALLEGRO_DEPTH_SIZE               15
#define ALLEGRO_STENCIL_SIZE             16
#define ALLEGRO_SAMPLE_BUFFERS           17
#define ALLEGRO_SAMPLES                  18
#define ALLEGRO_RENDER_METHOD            19
#define ALLEGRO_FLOAT_COLOR              20
#define ALLEGRO_FLOAT_DEPTH              21
#define ALLEGRO_SINGLE_BUFFER            22
#define ALLEGRO_SWAP_METHOD              23
#define ALLEGRO_COMPATIBLE_DISPLAY       24
#define ALLEGRO_UPDATE_DISPLAY_REGION    25
#define ALLEGRO_VSYNC                    26
#define ALLEGRO_MAX_BITMAP_SIZE          27
#define ALLEGRO_SUPPORT_NPOT_BITMAP      28
#define ALLEGRO_CAN_DRAW_INTO_BITMAP     29
#define ALLEGRO_SUPPORT_SEPARATE_ALPHA   30
#define ALLEGRO_AUTO_CONVERT_BITMAPS     31
#define ALLEGRO_SUPPORTED_ORIENTATIONS   32
#define ALLEGRO_OPENGL_MAJOR_VERSION     33
#define ALLEGRO_OPENGL_MINOR_VERSION     34
#define ALLEGRO_DISPLAY_OPTIONS_COUNT    35

#define ALLEGRO_DONTCARE 0
#define ALLEGRO_REQUIRE  1
#define ALLEGRO_SUGGEST  2



/* Bitflags so they can be used for the ALLEGRO_SUPPORTED_ORIENTATIONS option. */
#define ALLEGRO_DISPLAY_ORIENTATION_UNKNOWN       0
#define ALLEGRO_DISPLAY_ORIENTATION_0_DEGREES     1
#define ALLEGRO_DISPLAY_ORIENTATION_90_DEGREES    2
#define ALLEGRO_DISPLAY_ORIENTATION_180_DEGREES   4
#define ALLEGRO_DISPLAY_ORIENTATION_270_DEGREES   8
#define ALLEGRO_DISPLAY_ORIENTATION_PORTRAIT      5
#define ALLEGRO_DISPLAY_ORIENTATION_LANDSCAPE     10
#define ALLEGRO_DISPLAY_ORIENTATION_ALL           15
#define ALLEGRO_DISPLAY_ORIENTATION_FACE_UP       16
#define ALLEGRO_DISPLAY_ORIENTATION_FACE_DOWN     32

/* Formally part of the primitives addon. */
#define ALLEGRO_PRIM_MAX_USER_ATTR                10

/* Type: ALLEGRO_EVENT_TYPE
 */


#define ALLEGRO_EVENT_JOYSTICK_AXIS               1
#define ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN        2
#define ALLEGRO_EVENT_JOYSTICK_BUTTON_UP          3
#define ALLEGRO_EVENT_JOYSTICK_CONFIGURATION      4

#define ALLEGRO_EVENT_KEY_DOWN                    10
#define ALLEGRO_EVENT_KEY_CHAR                    11
#define ALLEGRO_EVENT_KEY_UP                      12

#define ALLEGRO_EVENT_MOUSE_AXES                  20
#define ALLEGRO_EVENT_MOUSE_BUTTON_DOWN           21
#define ALLEGRO_EVENT_MOUSE_BUTTON_UP             22
#define ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY         23
#define ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY         24
#define ALLEGRO_EVENT_MOUSE_WARPED                25

#define ALLEGRO_EVENT_TIMER                       30

#define ALLEGRO_EVENT_DISPLAY_EXPOSE              40
#define ALLEGRO_EVENT_DISPLAY_RESIZE              41
#define ALLEGRO_EVENT_DISPLAY_CLOSE               42
#define ALLEGRO_EVENT_DISPLAY_LOST                43
#define ALLEGRO_EVENT_DISPLAY_FOUND               44
#define ALLEGRO_EVENT_DISPLAY_SWITCH_IN           45
#define ALLEGRO_EVENT_DISPLAY_SWITCH_OUT          46
#define ALLEGRO_EVENT_DISPLAY_ORIENTATION         47
#define ALLEGRO_EVENT_DISPLAY_HALT_DRAWING        48
#define ALLEGRO_EVENT_DISPLAY_RESUME_DRAWING      49

#define ALLEGRO_EVENT_TOUCH_BEGIN                 50
#define ALLEGRO_EVENT_TOUCH_END                   51
#define ALLEGRO_EVENT_TOUCH_MOVE                  52
#define ALLEGRO_EVENT_TOUCH_CANCEL                53

#define ALLEGRO_EVENT_DISPLAY_CONNECTED           60
#define ALLEGRO_EVENT_DISPLAY_DISCONNECTED        61

#endif /* end NUKLEAR_ALLEGRO5_CH_ */
