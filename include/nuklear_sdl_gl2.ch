/*
 *
 */

#ifndef NUKLEAR_SDL_GL2_CH_
#define NUKLEAR_SDL_GL2_CH_

#include "nuklear.ch"

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* SDL */

/* SDL_events.h */
#define SDL_RELEASED 0
#define SDL_PRESSED  1

#define SDL_TEXTEDITINGEVENT_TEXT_SIZE (32)
#define SDL_TEXTINPUTEVENT_TEXT_SIZE (32)

#define SDL_QUERY   -1
#define SDL_IGNORE   0
#define SDL_DISABLE  0
#define SDL_ENABLE   1

// #define SDL_GetEventState(type) SDL_EventState(type, SDL_QUERY)

#define SDL_FIRSTEVENT               0       /**< Unused (do not remove) */
#define SDL_QUIT                     0x100   /**< User-requested quit */
#define SDL_APP_TERMINATING          0x101   /**< The application is being terminated by the OS Called on iOS in applicationWillTerminate() Called on Android in onDestroy() */
#define SDL_APP_LOWMEMORY            0x102   /**< The application is low on memory, free memory if possible. Called on iOS in applicationDidReceiveMemoryWarning() Called on Android in onLowMemory() */
#define SDL_APP_WILLENTERBACKGROUND  0x103   /**< The application is about to enter the background Called on iOS in applicationWillResignActive() Called on Android in onPause() */
#define SDL_APP_DIDENTERBACKGROUND   0x104   /**< The application did enter the background and may not get CPU for some time Called on iOS in applicationDidEnterBackground() Called on Android in onPause() */
#define SDL_APP_WILLENTERFOREGROUND  0x105   /**< The application is about to enter the foreground Called on iOS in applicationWillEnterForeground() Called on Android in onResume() */
#define SDL_APP_DIDENTERFOREGROUND   0x106   /**< The application is now interactive Called on iOS in applicationDidBecomeActive() Called on Android in onResume() */
#define SDL_LOCALECHANGED            0x107   /**< The user's locale preferences have changed. */
#define SDL_DISPLAYEVENT             0x150   /**< Display state change */
#define SDL_WINDOWEVENT              0x200   /**< Window state change */
#define SDL_SYSWMEVENT               0x200   /**< System specific event */
#define SDL_KEYDOWN                  0x300   /**< Key pressed */
#define SDL_KEYUP                    0x301   /**< Key released */
#define SDL_TEXTEDITING              0x302   /**< Keyboard text editing (composition) */
#define SDL_TEXTINPUT                0x303   /**< Keyboard text input */
#define SDL_KEYMAPCHANGED            0x304   /**< Keymap changed due to a system event such as an input language or keyboard layout change. */
#define SDL_MOUSEMOTION              0x400   /**< Mouse moved */
#define SDL_MOUSEBUTTONDOWN          0x401   /**< Mouse button pressed */
#define SDL_MOUSEBUTTONUP            0x402   /**< Mouse button released */
#define SDL_MOUSEWHEEL               0x403   /**< Mouse wheel motion */
#define SDL_JOYAXISMOTION            0x600   /**< Joystick axis motion */
#define SDL_JOYBALLMOTION            0x601   /**< Joystick trackball motion */
#define SDL_JOYHATMOTION             0x602   /**< Joystick hat position change */
#define SDL_JOYBUTTONDOWN            0x603   /**< Joystick button pressed */
#define SDL_JOYBUTTONUP              0x604   /**< Joystick button released */
#define SDL_JOYDEVICEADDED           0x605   /**< A new joystick has been inserted into the system */
#define SDL_JOYDEVICEREMOVED         0x606   /**< An opened joystick has been removed */
#define SDL_CONTROLLERAXISMOTION     0x650   /**< Game controller axis motion */
#define SDL_CONTROLLERBUTTONDOWN     0x651   /**< Game controller button pressed */
#define SDL_CONTROLLERBUTTONUP       0x652   /**< Game controller button released */
#define SDL_CONTROLLERDEVICEADDED    0x653   /**< A new Game controller has been inserted into the system */
#define SDL_CONTROLLERDEVICEREMOVED  0x654   /**< An opened Game controller has been removed */
#define SDL_CONTROLLERDEVICEREMAPPED 0x655   /**< The controller mapping was updated */
#define SDL_CONTROLLERTOUCHPADDOWN   0x656   /**< Game controller touchpad was touched */
#define SDL_CONTROLLERTOUCHPADMOTION 0x657   /**< Game controller touchpad finger was moved */
#define SDL_CONTROLLERTOUCHPADUP     0x658   /**< Game controller touchpad finger was lifted */
#define SDL_CONTROLLERSENSORUPDATE   0x659   /**< Game controller sensor was updated */
#define SDL_FINGERDOWN               0x700
#define SDL_FINGERUP                 0x701
#define SDL_FINGERMOTION             0x702
#define SDL_DOLLARGESTURE            0x800
#define SDL_DOLLARRECORD             0x801
#define SDL_MULTIGESTURE             0x802
#define SDL_CLIPBOARDUPDATE          0x900   /**< The clipboard changed */
#define SDL_DROPFILE                 0x1000  /**< The system requests a file open */
#define SDL_DROPTEXT                 0x1001  /**< text/plain drag-and-drop event */
#define SDL_DROPBEGIN                0x1002  /**< A new set of drops is beginning (NULL filename) */
#define SDL_DROPCOMPLETE             0x1003  /**< Current set of drops is now complete (NULL filename) */
#define SDL_AUDIODEVICEADDED         0x1100  /**< A new audio device is available */
#define SDL_AUDIODEVICEREMOVED       0x1101  /**< An audio device has been removed. */
#define SDL_SENSORUPDATE             0x1200  /**< A sensor was updated */
#define SDL_RENDER_TARGETS_RESET     0x2000  /**< The render targets have been reset and their contents need to be updated */
#define SDL_RENDER_DEVICE_RESET      0x2000  /**< The device has been reset and all textures need to be recreated */
#define SDL_POLLSENTINEL             0x7F00  /**< Signals the end of an event poll cycle */
#define SDL_USEREVENT                0x8000
#define SDL_LASTEVENT                0xFFFF

#define SDL_ADDEVENT  0
#define SDL_PEEKEVENT 1
#define SDL_GETEVENT  2

#define TYPE      1    /**< Event type, shared with all events */
#define COMMON    2    /**< Common event data */
#define DISPLAY   3    /**< Display event data */
#define WINDOW    4    /**< Window event data */
#define KEY       5    /**< Keyboard event data */
#define EDIT      6    /**< Text editing event data */
#define TEXT      7    /**< Text input event data */
#define MOTION    8    /**< Mouse motion event data */
#define BUTTON    9    /**< Mouse button event data */
#define WHEEL     10   /**< Mouse wheel event data */
#define JAXIS     11   /**< Joystick axis event data */
#define JBALL     12   /**< Joystick ball event data */
#define JHAT      13   /**< Joystick hat event data */
#define JBUTTON   14   /**< Joystick button event data */
#define JDEVICE   15   /**< Joystick device change event data */
#define CAXIS     16   /**< Game Controller axis event data */
#define CBUTTON   17   /**< Game Controller button event data */
#define CDEVICE   18   /**< Game Controller device event data */
#define CTOUCHPAD 19   /**< Game Controller touchpad event data */
#define CSENSOR   20   /**< Game Controller sensor event data */
#define ADEVICE   21   /**< Audio device event data */
#define SENSOR    22   /**< Sensor event data */
#define QUIT      23   /**< Quit request event data */
#define USER      24   /**< Custom event data */
#define SYSWM     25   /**< System dependent window event data */
#define TFINGER   26   /**< Touch finger event data */
#define MGESTURE  27   /**< Gesture event data */
#define DGESTURE  28   /**< Gesture event data */
#define DROP      29   /**< Drag and drop event data */
#define PADDING   30
/* SDL_events.h */

/* SDL.h */
#define SDL_INIT_TIMER          0x00000001
#define SDL_INIT_AUDIO          0x00000010
#define SDL_INIT_VIDEO          0x00000020
#define SDL_INIT_JOYSTICK       0x00000200
#define SDL_INIT_HAPTIC         0x00001000
#define SDL_INIT_GAMECONTROLLER 0x00002000
#define SDL_INIT_EVENTS         0x00004000
#define SDL_INIT_SENSOR         0x00008000
#define SDL_INIT_NOPARACHUTE    0x00100000
#define SDL_INIT_EVERYTHING     hb_BitOr( SDL_INIT_TIMER, SDL_INIT_AUDIO, SDL_INIT_VIDEO, SDL_INIT_EVENTS, SDL_INIT_JOYSTICK, SDL_INIT_HAPTIC, SDL_INIT_GAMECONTROLLER, SDL_INIT_SENSOR )
/* End SDL.h */

/* SDL_video.h */
#define SDL_WINDOW_FULLSCREEN               0x00000001
#define SDL_WINDOW_OPENGL                   0x00000002
#define SDL_WINDOW_SHOWN                    0x00000004
#define SDL_WINDOW_HIDDEN                   0x00000008
#define SDL_WINDOW_BORDERLESS               0x00000010
#define SDL_WINDOW_RESIZABLE                0x00000020
#define SDL_WINDOW_MINIMIZED                0x00000040
#define SDL_WINDOW_MAXIMIZED                0x00000080
#define SDL_WINDOW_MOUSE_GRABBED            0x00000100
#define SDL_WINDOW_INPUT_FOCUS              0x00000200
#define SDL_WINDOW_MOUSE_FOCUS              0x00000400
#define SDL_WINDOW_FULLSCREEN_DESKTOP       ( SDL_WINDOW_FULLSCREEN + 0x00001000 )
#define SDL_WINDOW_FOREIGN                  0x00000800
#define SDL_WINDOW_ALLOW_HIGHDPI            0x00002000

#define SDL_WINDOWPOS_CENTERED_MASK         0x2FFF0000
#define SDL_WINDOWPOS_CENTERED_DISPLAY(X)   (hb_bitOR(SDL_WINDOWPOS_CENTERED_MASK,(X)))
#define SDL_WINDOWPOS_CENTERED              SDL_WINDOWPOS_CENTERED_DISPLAY(0)
#define SDL_WINDOWPOS_ISCENTERED(X)         (((X)0xFFFF0000) == SDL_WINDOWPOS_CENTERED_MASK)

#define SDL_GL_RED_SIZE                     0
#define SDL_GL_GREEN_SIZE                   1
#define SDL_GL_BLUE_SIZE                    2
#define SDL_GL_ALPHA_SIZE                   3
#define SDL_GL_BUFFER_SIZE                  4
#define SDL_GL_DOUBLEBUFFER                 5
#define SDL_GL_DEPTH_SIZE                   6
#define SDL_GL_STENCIL_SIZE                 7
#define SDL_GL_ACCUM_RED_SIZE               8
#define SDL_GL_ACCUM_GREEN_SIZE             9
#define SDL_GL_ACCUM_BLUE_SIZE              10
#define SDL_GL_ACCUM_ALPHA_SIZE             11
#define SDL_GL_STEREO                       12
#define SDL_GL_MULTISAMPLEBUFFERS           13
#define SDL_GL_MULTISAMPLESAMPLES           14
#define SDL_GL_ACCELERATED_VISUAL           15
#define SDL_GL_RETAINED_BACKING             16
#define SDL_GL_CONTEXT_MAJOR_VERSION        17
#define SDL_GL_CONTEXT_MINOR_VERSION        18
#define SDL_GL_CONTEXT_EGL                  19
#define SDL_GL_CONTEXT_FLAGS                20
#define SDL_GL_CONTEXT_PROFILE_MASK         21
#define SDL_GL_SHARE_WITH_CURRENT_CONTEXT   22
#define SDL_GL_FRAMEBUFFER_SRGB_CAPABLE     23
#define SDL_GL_CONTEXT_RELEASE_BEHAVIOR     24
#define SDL_GL_CONTEXT_RESET_NOTIFICATION   25
#define SDL_GL_CONTEXT_NO_ERROR             26
/* End SDL_video.h */


/* SDL_hints.h */
#define SDL_HINT_VIDEO_HIGHDPI_DISABLED     "SDL_VIDEO_HIGHDPI_DISABLED"
/* End SDL_hints.h */

/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
/* GL */
#define GL_DEPTH_BUFFER_BIT           0x00000100
#define GL_STENCIL_BUFFER_BIT         0x00000400
#define GL_COLOR_BUFFER_BIT           0x00004000

#endif /* end NUKLEAR_SDL_GL2_CH_ */
